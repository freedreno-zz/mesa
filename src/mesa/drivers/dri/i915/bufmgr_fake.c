/* Fake version of the buffer manager so that we can prototype the
 * changes in a driver fairly quickly.  Basically wraps the old style
 * memory management in the new programming interface.
 *
 * This version imports code from the via memory manager to closer
 * approximate the behaviour of a true memory manager.  In particular,
 * in this version we do not expect to lose texture memory contents on
 * context switches.
 */
#include "bufmgr.h"

#include "intel_context.h"
#include "intel_ioctl.h"

#include "hash.h"
#include "simple_list.h"
#include "mm.h"
#include "imports.h"
#include <sys/ioctl.h>
#include <unistd.h>
#include <drm.h>

static int ttmcount = 0;

/*
 * Define this if the texture TTMs should be cached. If it is not defined,
 * Texture downloads will be slow since the TTM pages are not write-combined.
 * Backdoor mapping will very probably fix this. (texdown-pool)
 */ 

#define CACHED_TTMS

/*
 * Batchbuffer memory location:
 * 0 Is the global texture pool (as without ttms)
 * 1 Is a memory-managed large pinned uncached TTM. Should work as 0, but
 *   doesn't. The only difference is that the TTM memory is accessed 
 *   directly instead of through the aperture. Runs for a while.
 * 2 Is dynamic TTMS. This is what we want. Doesn't work either, but runs
 *   for a while, depending on application. multiarb works fine for example.
 */

#define BATCH_LOCATION 0

#if (BATCH_LOCATION == 2)
#warning Batch buffers using dynamic TTMS. Making TTMS uncached.
#undef CACHED_TTMS
#endif

struct _mesa_HashTable;

static int delayed_free( struct bufmgr *bm );

#define BM_POOL_MAX 8


/* Wrapper around mm.c's mem_block, which understands that you must
 * wait for fences to expire before memory can be freed.  This is
 * specific to our use of memcpy and/or ttms for uploads - an upload
 * that was processed through the command queue wouldn't need to care
 * about fences.
 */
struct block {
   struct block *next, *prev;
   int mem_type;
   struct pool *pool;		/* BM_MEM_AGP */
   struct mem_block *mem;	/* BM_MEM_AGP */
   unsigned fence;		/* BM_MEM_AGP, Split to read_fence, write_fence */
   void *virtual;               
   struct buffer *buf;
   drm_ttm_arg_t drm_ttm;
   drm_ttm_buf_arg_t drm_buf;
   int has_ttm;
};


struct buffer {
   unsigned id;			/* debug only */
   unsigned size;
   unsigned alignment;
   unsigned mapped;
   unsigned flags;
   struct block *block;
};

struct pool {
   unsigned flags;
   struct mem_block *heap;
   void *virtual;
   struct block lru;
   struct block freed;
   drm_ttm_arg_t drm_ttm;
   drm_ttm_buf_arg_t drm_buf;
};

struct bufmgr {
   struct intel_context *intel;
   struct pool pool[BM_POOL_MAX];
   unsigned nr_pools;

   struct _mesa_HashTable *hash;

   unsigned buf_nr;		/* for generating ids */
};



static struct block *alloc_from_pool( struct bufmgr *bm,				
				      unsigned pool_nr,
				      unsigned size, 
				      unsigned align )
{
   struct pool *pool = &bm->pool[pool_nr];
   struct block *block = (struct block *)calloc(sizeof *block, 1);
   if (!block)
      return NULL;

   DBG("alloc_from_pool %d sz 0x%x\n", pool_nr, size);
   assert(align >= 7);

   block->mem = mmAllocMem(pool->heap, size, align, 0);
   if (!block->mem) {
      DBG("\t- failed\n");
      free(block);
      return NULL;
   }

   make_empty_list(block);
   block->pool = pool;
   block->mem_type = pool->flags & BM_MEM_MASK;
   block->virtual = pool->virtual + block->mem->ofs;
   block->has_ttm = 0;

   DBG("\t- offset 0x%x\n", block->mem->ofs);
   return block;
}


static struct block *alloc_local( unsigned size )
{
   struct block *block = (struct block *)calloc(sizeof *block, 1);
   if (!block)
      return NULL;

   DBG("alloc_local 0x%x\n", size);

   block->mem_type = BM_MEM_LOCAL;
   block->virtual = ALIGN_MALLOC(size, 1<<7);
   if (!block->virtual) {
      free(block);
      return NULL;
   }

   return block;
}




static struct block *alloc_block( struct bufmgr *bm,
				  unsigned size,
				  unsigned align,
				  int flags )
{
    GLuint i;
    int ret;
    struct block *block;
    unsigned alignment = ( 1 << align );
    
    if (!(flags & BM_NO_TTM) 
#if (BATCH_LOCATION != 2)
#warning Disabling dynamic batch buffers
	&& !(flags & BM_CLIENT)
#endif
	) {
		
	block = (struct block *)calloc(sizeof *block, 1);
	if (!block) return NULL;
	
	make_empty_list(block);
	block->pool = bm->pool + 0;
	block->mem_type = flags;
	block->has_ttm = 0;
	
	block->drm_ttm.op = ttm_add;
	block->drm_ttm.size = ((size + alignment -1) >> align) << align;
	ret = ioctl(bm->intel->driFd, DRM_IOCTL_TTM, &block->drm_ttm);
	assert(ret == 0);
	block->drm_buf.ttm_handle = block->drm_ttm.handle; 
	block->drm_buf.ttm_page_offset = 0;
	block->drm_buf.num_pages = block->drm_ttm.size / getpagesize(); 
	block->drm_buf.next = NULL;
	
#ifdef CACHED_TTMS
	block->drm_buf.flags = DRM_TTM_FLAG_NEW | DRM_TTM_FLAG_CACHED;
#else
	block->drm_buf.flags = DRM_TTM_FLAG_NEW;
#endif
	block->has_ttm = 2;
	if (block->has_ttm > 1)
	    block->virtual = NULL;
	ttmcount += block->drm_buf.num_pages;
	DBG("ttmcount pages is %d\n", ttmcount);
	DBG("ttm handle is 0x%x\n", block->drm_ttm.handle);
	
	return block;
    }

    if (!(flags & (BM_CLIENT))) {
	for (i = 0; i < bm->nr_pools; i++) {
	    struct block *block;
	    
	    if (bm->pool[i].flags & BM_NO_ALLOC)
		continue;
	    
	    if ((bm->pool[i].flags & flags & BM_MEM_MASK) == 0)
		continue;
	    
	    block = alloc_from_pool(bm, i, size, align);
	    if (block) return block;
	}   
    }


    if (flags & BM_MEM_LOCAL)
      return alloc_local(size);

    return NULL;
}

static int bmAllocMem( struct bufmgr *bm,
		       struct buffer *buf,
		       GLuint flags )	
{
   delayed_free(bm);

   buf->block = alloc_block(bm, 
			    buf->size,
			    buf->alignment, 
			    buf->flags | flags);

   if (buf->block) 
      buf->block->buf = buf;      
   else
      _mesa_printf("bmAllocMem failed memflags %x\n", buf->flags & BM_MEM_MASK);

   /* Sleep here or fail??? 
    */
/*    assert(buf->block); */
   return buf->block != NULL;
}


/* Release the card storage associated with buf:
 */
static void free_block( struct bufmgr *bm, struct block *block )
{
    int ret;

   if (!block) 
      return;

   DBG("free block (mem: %d, sz %d) from buf %d\n",
       block->mem_type,
       block->buf->size,
       block->buf->id);

   switch (block->mem_type) {
   case BM_MEM_AGP:
   case BM_MEM_VRAM:
      remove_from_list(block);

      if (!block->has_ttm)
	DBG("    - offset %x\n", block->mem->ofs);
      else
	DBG("    - offset %x\n", block->drm_buf.aper_offset*getpagesize());
	
      if (bmTestFence(bm, block->fence)) {
	  if (!block->has_ttm) {
	      mmFreeMem(block->mem);
	  } else {
	      block->drm_ttm.op = ttm_remove;
	      ret = ioctl(bm->intel->driFd, DRM_IOCTL_TTM, &block->drm_ttm);
	      ttmcount -= block->drm_buf.num_pages;
	      DBG("ttmcount pages is %d\n", ttmcount);
	      assert(ret == 0);
	  }
         free(block);
      }
      else {
	 DBG("    - place on delayed_free list\n");
	 block->buf = NULL;
         insert_at_tail(&block->pool->freed, block);
      }
      break;

   case BM_MEM_LOCAL:
      DBG("    - free local memory\n");
      ALIGN_FREE(block->virtual);
      free(block);
      break;

   default:
      DBG("    - unknown memory type\n");
      free(block);
      break;
   }
}

static int delayed_free( struct bufmgr *bm )
{
   struct block *block, *tmp;
   int ret = 0;
   int rettm;
   int i;

   for (i = 0; i < bm->nr_pools; i++) {
      foreach_s(block, tmp, &bm->pool[i].freed ) {
	 if (bmTestFence(bm, block->fence)) {
	    remove_from_list(block);
	    if (!block->has_ttm) {
		mmFreeMem(block->mem);
		ret += block->mem->size;
	    } else {
		block->drm_ttm.op = ttm_remove;
		rettm = ioctl(bm->intel->driFd, DRM_IOCTL_TTM, &block->drm_ttm);
		ttmcount -= block->drm_buf.num_pages;
		DBG("ttmcount pages is %d\n", ttmcount);
		assert(rettm == 0);
		ret += block->drm_buf.num_pages*getpagesize();
	    }
	    free(block);
	 }
      }
   }
   
   DBG("%s: %d\n", __FUNCTION__, ret);
   return ret;
}


static int move_buffers( struct bufmgr *bm, 
			 struct buffer *buffers[],
			 int nr,
			 int flags )
{
   struct block *newMem[BM_LIST_MAX];
   GLint i;
   GLuint nr_uploads = 0;
   drm_ttm_arg_t arg;
   struct block *block, *last_block;
   int ret;


   DBG("%s\n", __FUNCTION__);

   memset(newMem, 0, sizeof(newMem));

   /* First do all the allocations (or fail):
    */ 
   for (i = 0; i < nr; i++) {    
      if (!buffers[i]->block) {

 	 if (flags & BM_NO_ALLOC)
 	    goto cleanup;

	 newMem[i] = alloc_block(bm, 
				 buffers[i]->size,
				 buffers[i]->alignment,
				 flags & BM_MEM_MASK);

	 if (!newMem[i]) 
	    goto cleanup;

      } 
   }

   /*
    * Tell kernel where TTMS should be.
    */

   arg.num_bufs = 0;
   last_block = NULL;

   for (i = 0; i <nr; ++i) {
       if (newMem[i] && newMem[i]->has_ttm) {
	   buffers[i]->block = newMem[i];
	   newMem[i] = NULL;
       }
       block = buffers[i]->block;
       if (block->has_ttm) {
	   if ((flags & BM_MEM_MASK) == BM_MEM_AGP || 
	       (((flags & BM_MEM_MASK) == BM_MEM_LOCAL) && 
		(block->mem_type == BM_MEM_AGP))) {
	       if (arg.num_bufs == 0) 
		   arg.first = &block->drm_buf;
	       else
		   last_block->drm_buf.next = &block->drm_buf;
	       arg.num_bufs++;
	       last_block = block;
	       block->drm_buf.op = ((flags & BM_MEM_MASK) == BM_MEM_AGP) ?
		   ttm_validate : ttm_unbind;
	       block->mem_type = flags & BM_MEM_MASK;
	   }
       }
   }
   arg.op = ttm_bufs;
   arg.do_fence = 0;
   DBG("Num validated TTM bufs is %d\n", arg.num_bufs);
   if (arg.num_bufs) {
     ret = ioctl(bm->intel->driFd, DRM_IOCTL_TTM, &arg);
     assert(ret == 0);
   }

   /*
    * End TTM code.
    */

   
   for (i=0; i< nr; ++i) {
       if (!(buffers[i]->block->mem_type & flags)) { 
	   if (flags & BM_NO_UPLOAD)
	       goto cleanup;
	   
	   /* Known issue: this assert will get hit on texture swapping.
	    * There's not much to do about that at this stage - it's a
	    * todo item.
	    */
	   assert(!buffers[i]->mapped);
	   
	   DBG("try to move buffer %d size 0x%x to pools 0x%x\n", 
		  buffers[i]->id, buffers[i]->size, flags & BM_MEM_MASK);
	   
	   newMem[i] = alloc_block(bm, 
				   buffers[i]->size,
				   buffers[i]->alignment,
				   (flags & BM_MEM_MASK) | BM_NO_TTM);
	   
	   if (!newMem[i]) 
	       goto cleanup;
	   
       }
   }


   /* Now copy all the image data and free the old texture memory.
    */
   for (i = 0; i < nr; i++) {    
      if (newMem[i]) {
	 if (buffers[i]->block) {
	    /* XXX: To be replaced with DMA, GTT bind, and other
	       * mechanisms in final version.  Memcpy (or sse_memcpy) is
	       * probably pretty good for local->agp uploads.
	       */
	     DBG("memcpy %d bytes\n", buffers[i]->size);
	      memcpy(newMem[i]->virtual,
		     buffers[i]->block->virtual, 
		     buffers[i]->size);
	      
	      free_block(bm, buffers[i]->block);
	      nr_uploads++;
	  }
	  
	  buffers[i]->block = newMem[i];
	  buffers[i]->block->buf = buffers[i];
      }
   }
   
   /* Tell hardware that its texture and other caches may be invalid: 
    */
   if (nr_uploads && (flags & (BM_MEM_AGP|BM_MEM_VRAM)))
       bmFlushReadCaches(bm);   
   
   DBG("%s - success\n", __FUNCTION__);
   return 1;

 cleanup:
   /* Release any allocations made prior to failure:
    */
   for (i = 0; i < nr; i++) {    
      if (newMem[i]) 
	 free_block(bm, newMem[i]);
   }
   
   _mesa_printf("%s - fail\n", __FUNCTION__);
   return 0;   
}


static unsigned evict_lru( struct bufmgr *bm,
			   unsigned flags)
{
   int i;

   DBG("%s\n", __FUNCTION__);

   if (flags & BM_NO_EVICT)
      return 0;

   /* XXX: this is broken with >1 active pool - all the first pool
    * will be evicted before starting on the second.  Actually, maybe
    * you want that in some situations...
    */
   for (i = 0; i < bm->nr_pools; i++) {
      if ((bm->pool[i].flags & flags & BM_MEM_MASK) && 
	  !(bm->pool[i].flags & BM_NO_EVICT)) {
	 struct block *block = bm->pool[i].lru.next;
	 unsigned size = block->buf->size;

	 if (block == &bm->pool[i].lru ||
	     !bmTestFence(bm, block->fence)) 
	    return 0;
   
	 move_buffers(bm, &block->buf, 1, BM_MEM_LOCAL);
	 return size;
      }
   }

   return 0;
}

#if 0
/* Speculatively move texture images which haven't been used in a
 * while back to local memory.
 */
static void viaSwapOutWork( struct bufmgr *bm )
{
   unsigned total = 0;
   unsigned target;

   if (bm->thrashing) {
      target = 1*1024*1024;
   }
   else if (bmIsTexMemLow(bm)) {
      target = 64*1024;
   }
   else {
      return;
   }

   while (1) {
      unsigned size = evict_lru(bm);
      if (!size)
         return;

      total += size;
      if (total >= target)
         return;
   }
}
#endif












/***********************************************************************
 * Public functions
 */


/* The initialization functions are skewed in the fake implementation.
 * This call would be to attach to an existing manager, rather than to
 * create a local one.
 */
struct bufmgr *bm_fake_intel_Attach( struct intel_context *intel )
{
   struct bufmgr *bm = (struct bufmgr *)calloc(sizeof(*bm), 1);
   
   bm->intel = intel;
   bm->hash = _mesa_NewHashTable();

   return bm;
}


void bmInitMemType( struct bufmgr *bm,
		    unsigned mem_type,
		    unsigned long size )
{
   /* Nothing really to do.  Could store and use to validate
    * bmInitPool requests.
    */
}


/* The virtual pointer would go away in a true implementation.
 */
int bmInitPool( struct bufmgr *bm, 
		unsigned long low_offset,
		void *low_virtual,
		unsigned long size,
		unsigned flags)
{
   GLuint i;
   struct pool *pool;

   if (bm->nr_pools >= BM_POOL_MAX)
      return -1;

   i = bm->nr_pools++;
   
   DBG("bmInitPool %d low_offset %x sz %x\n",
		i, low_offset, size);
   
   pool = bm->pool + i;
   pool->flags = flags;
   
   make_empty_list(&bm->pool[i].lru);
   make_empty_list(&bm->pool[i].freed);

   if (flags == BM_MEM_AGP) {
#if (BATCH_LOCATION == 1)
#warning Replacing pool 0 with a large uncached pinned TTM.
       int ret;
       drmAddress ttmAddress;


       DBG("Creating Pinned ttm.\n");
       pool->drm_ttm.op = ttm_add;
       pool->drm_ttm.size = size;
       ret = ioctl(bm->intel->driFd, DRM_IOCTL_TTM, &pool->drm_ttm);
       if (ret) return -1;
       ret = drmMap(bm->intel->driFd, pool->drm_ttm.handle, size, &ttmAddress);
       DBG("Virtual is 0x%lx\n", (unsigned long) ttmAddress);
       if (ret) {
	   pool->drm_ttm.op = ttm_add;
	   ioctl(bm->intel->driFd, DRM_IOCTL_TTM, &pool->drm_ttm);
	   return -1;
       }
       pool->drm_buf.ttm_handle = pool->drm_ttm.handle;
       pool->drm_buf.ttm_page_offset = 0;
       pool->drm_buf.num_pages = pool->drm_ttm.size / getpagesize();
       pool->drm_buf.next = NULL;
       pool->drm_buf.flags = DRM_TTM_FLAG_NEW | DRM_TTM_FLAG_PINNED;
       pool->drm_buf.op = ttm_validate;
       pool->drm_ttm.op = ttm_bufs;
       pool->drm_ttm.num_bufs = 1;
       pool->drm_ttm.first = &pool->drm_buf;
       drmGetLock(bm->intel->driFd, bm->intel->hHWContext, 0);
       ret = ioctl(bm->intel->driFd, DRM_IOCTL_TTM, &pool->drm_ttm);
       drmUnlock(bm->intel->driFd, bm->intel->hHWContext);
       low_offset = pool->drm_buf.aper_offset * getpagesize();
       pool->heap = mmInit( low_offset , size );
       pool->virtual = (char *) ttmAddress - low_offset;
       DBG("Pinned buf offset is 0x%lx\n", low_offset);
#else 
       pool->heap = mmInit( low_offset , size );
       pool->virtual = low_virtual - low_offset;      
#endif 
   } else {
       pool->heap = mmInit( low_offset, size );
       pool->virtual = low_virtual - low_offset;
   }
   return i;
}

#if 0
void bmAssertTTM(struct bufmgr *bm, unsigned n, unsigned *buffers)
{
   unsigned i;

   for (i = 0; i < n; i++) {
      struct buffer *buf = _mesa_HashLookup(bm->hash, buffers[i]);
      DBG("0x%x\n", buf->flags);
      assert(buf->block);
      assert(buf->block->has_ttm);
   }
}
#endif

void bmGenBuffers(struct bufmgr *bm, unsigned n, unsigned *buffers)
{
   unsigned i;

   for (i = 0; i < n; i++) {
      struct buffer *buf = calloc(sizeof(*buf), 1);
      buf->id = ++bm->buf_nr;
      buf->alignment = 12;	/* page-alignment to fit in with AGP swapping */
      buf->flags = BM_MEM_AGP|BM_MEM_VRAM|BM_MEM_LOCAL;
      buffers[i] = buf->id;
      _mesa_HashInsert(bm->hash, buffers[i], buf);
   }
}


void bmDeleteBuffers(struct bufmgr *bm, unsigned n, unsigned *buffers)
{
   unsigned i;
   
   for (i = 0; i < n; i++) {
      struct buffer *buf = _mesa_HashLookup(bm->hash, buffers[i]);
      if (buf) {
         free_block(bm, buf->block);	
         free(buf);
	 _mesa_HashRemove(bm->hash, buffers[i]);
      }
      assert(_mesa_HashLookup(bm->hash, buffers[i]) == NULL);
   }
}




/* Hook to inform faked buffer manager about fixed-position
 * front,depth,back buffers.  These may move to a fully memory-managed
 * scheme, or they may continue to be managed as is.  It will probably
 * be useful to pass a fixed offset here one day.
 */
unsigned bmBufferStatic(struct bufmgr *bm,
			unsigned buffer,
			unsigned size,
			unsigned pool )
{
   struct buffer *buf = (struct buffer *)_mesa_HashLookup( bm->hash, buffer );
   
   assert(!buf->block);
   assert(bm->pool[pool].flags & BM_NO_EVICT);
   assert(bm->pool[pool].flags & BM_NO_MOVE);

   buf->size = size;
   buf->flags = bm->pool[pool].flags;
   buf->alignment = 12;
   buf->block = alloc_from_pool(bm, pool, buf->size, buf->alignment);
   if (!buf->block)
      return 0;

   buf->block->buf = buf;
   return buf->block->mem->ofs;
}



/* If buffer size changes, free and reallocate.  Otherwise update in
 * place.
 */
void bmBufferData(struct bufmgr *bm, 
		  unsigned buffer, 
		  unsigned size, 
		  const void *data, 
		  unsigned flags )
{
   struct buffer *buf = (struct buffer *)_mesa_HashLookup( bm->hash, buffer );

   DBG("bmBufferData %d sz 0x%x data: %p\n", buffer, size, data);

   assert(!buf->mapped);

   if (buf->block) {
      if ((buf->block->mem_type != BM_MEM_LOCAL && !bmTestFence(bm, buf->block->fence)) ||
	  (buf->size && buf->size != size) ||
	  (data == NULL)) {
	 free_block(bm, buf->block);
	 buf->block = NULL;
      }
   }
   
   buf->size = size;

   if (data != NULL) {      
      bmAllocMem(bm, buf, buf->flags | flags);
#if 0      
      memcpy(buf->block->virtual, data, size);
#else
      /* Do an implicit map/unmap to get this working for now: 
       */
      memcpy(bmMapBuffer(bm, buf->id, flags), data, size);
      bmUnmapBuffer(bm, buf->id);
#endif      
   }
}

/* Update the buffer in place, in whatever space it is currently resident:
 */
void bmBufferSubData(struct bufmgr *bm, 
		     unsigned buffer, 
		     unsigned offset, 
		     unsigned size, 
		     const void *data )
{
   struct buffer *buf = (struct buffer *)_mesa_HashLookup( bm->hash, buffer );

   DBG("bmBufferSubdata %d offset 0x%x sz 0x%x\n", buffer, offset, size);

   if (buf->block == 0)
      bmAllocMem(bm, buf, buf->flags);

   if (buf->block->mem_type != BM_MEM_LOCAL)
      bmFinishFence(bm, buf->block->fence);

   if (size) {
#if 0
      memcpy(buf->block->virtual + offset, data, size); 
#else
      /* Do an implicit map/unmap to get this working for now: 
       */
      memcpy(bmMapBuffer(bm, buf->id, 0) + offset, data, size); 
      bmUnmapBuffer(bm, buf->id);
#endif
   }
}


/* Return a pointer to whatever space the buffer is currently resident in:
 */
void *bmMapBuffer( struct bufmgr *bm,
		   unsigned buffer, 
		   unsigned flags )
{
   struct buffer *buf = (struct buffer *)_mesa_HashLookup( bm->hash, buffer );
   int ret;

   DBG("bmMapBuffer %d\n", buffer);
   DBG("Map: Block is 0x%x\n", &buf->block);


   if (buf->mapped)
      return NULL;

/*
 * Hack to recognize batchbuffers.
 */

   if (buf->block == 0)
      bmAllocMem(bm, buf, flags);

   if (buf->block == 0)
      return NULL;

   buf->mapped = 1;

   /* Finish any outstanding operations to/from this memory:
    */
   if (buf->block->mem_type != BM_MEM_LOCAL) 
      bmFinishFence(bm, buf->block->fence);

   if (buf->block->has_ttm > 0) {
      ret = drmMap(bm->intel->driFd, buf->block->drm_ttm.handle, 
		   buf->block->drm_ttm.size, &buf->block->virtual);
      if (ret) {
	  fprintf(stderr,"TTM Map failed. Handle is 0x%x, size is %lu\n",
		  buf->block->drm_ttm.handle, buf->block->drm_ttm.size);
	  assert(0); 
      }
   }
   DBG("Mapped buf %u 0x%x\n", buffer, buf->block->virtual);
   return buf->block->virtual;
}

void bmUnmapBuffer( struct bufmgr *bm, unsigned buffer )
{
   struct buffer *buf = (struct buffer *)_mesa_HashLookup( bm->hash, buffer );
   if (!buf)
       return;

   DBG("bmUnmapBuffer %d\n", buffer);

   if (buf->block->has_ttm > 0) {
       drmUnmap(buf->block->virtual, buf->size);
       DBG("Unmapped buf %u 0x%x\n", buffer, buf->block->virtual);
       buf->block->virtual = NULL;
   }


   buf->mapped = 0;
}


/* Add a mechanism to tell the manager about some fixed buffers such
 * as the (fixed) front, back and depth buffers.  Something like this
 * may be needed even in a finalized version if we keep the static
 * management of these buffers.
 * 
 * These are excluded from the buffer memory management in this file,
 * but are presented to the driver by the same interface.  In the
 * future they may become managed.
 */
#if 0
void bm_fake_SetFixedBufferParams( struct bufmgr *bm
                                   unsigned buffer,
                                   unsigned offset,
                                   unsigned size )
{
}
#endif


/* Build the list of buffers to validate:
 */
struct bm_buffer_list *bmNewBufferList( void )
{
   struct bm_buffer_list *list = calloc(sizeof(*list), 1);
   DBG("bmNewBufferList\n");
   return list;
}

void bmAddBuffer( struct bm_buffer_list *list,
		  unsigned buffer,
		  unsigned flags,
		  unsigned *memtype_return,
		  unsigned *offset_return )
{
   assert(list->nr < BM_LIST_MAX);


   list->elem[list->nr].buffer = buffer;
   list->elem[list->nr].memtype_return = memtype_return;
   list->elem[list->nr].offset_return = offset_return;

   DBG("bmAddBuffer nr %d buf %d\n", 
		list->nr, buffer);

   list->nr++;
}
		
void bmFreeBufferList( struct bm_buffer_list *list )
{
   free(list);
}




/* To be called prior to emitting commands to hardware which reference
 * these buffers.  The buffer_usage list provides information on where
 * the buffers should be placed and whether their contents need to be
 * preserved on copying.  The offset and pool data elements are return
 * values from this function telling the driver exactly where the
 * buffers are currently located.
 */
int bmValidateBufferList( struct bufmgr *bm,
			  struct bm_buffer_list *list,
			  unsigned flags )
{
   struct buffer *bufs[BM_LIST_MAX];
   unsigned i;

   

   DBG("%s\n", __FUNCTION__);

   if (list->nr > BM_LIST_MAX)
      return 0;

   for (i = 0; i < list->nr; i++) {
      bufs[i] = _mesa_HashLookup(bm->hash, list->elem[i].buffer);
   }
   
   /* The old story: evict one texture after another until allocation
    * succeeds.  This is a pretty poor strategy but really hard to do
    * better without more infrastucture...  Which is coming - hooray!
    */

   while (!move_buffers(bm, bufs, list->nr, flags)) {

       /*
	* We should never get here. The kernel handles this.
	*/
       
       assert(0);
      if (!delayed_free(bm) &&
	  !evict_lru(bm, flags))
	 return 0;
      _mesa_printf("couldn't allocate sufficient texture memory\n");
      exit(1);
   }

   for (i = 0; i < list->nr; i++) {
      if (bufs[i]->block->has_ttm > 1) {
	  if (list->elem[i].offset_return)
	    list->elem[i].offset_return[0] = bufs[i]->block->drm_buf.aper_offset*getpagesize();	  
	  DBG("TTM OFFS 0x%x\n", bufs[i]->block->drm_buf.aper_offset*getpagesize());
      } else {
	  if (list->elem[i].offset_return)
	      list->elem[i].offset_return[0] = bufs[i]->block->mem->ofs;
	  DBG("Pinned Offs 0x%x\n", bufs[i]->block->mem->ofs);
      }
      if (list->elem[i].memtype_return)
	 list->elem[i].memtype_return[0] = bufs[i]->block->mem_type;
   }
   return 1;
}


/* After commands are emitted but before unlocking, this must be
 * called so that the buffer manager can correctly age the buffers.
 * The buffer manager keeps track of the list of validated buffers, so
 * already knows what to apply the fence to.
 *
 * The buffer manager knows how to emit and test fences directly
 * through the drm and without callbacks or whatever into the driver.
 */
unsigned bmFenceBufferList( struct bufmgr *bm, struct bm_buffer_list *list )
{

   drm_ttm_arg_t arg;
   int ret;

   arg.op = ttm_bufs;
   arg.do_fence = 1;
   arg.num_bufs = 0;
   ret = ioctl(bm->intel->driFd, DRM_IOCTL_TTM, &arg);
   assert(ret == 0);

   DBG("%s (%d bufs)\n", __FUNCTION__, list->nr);

   if (list->nr) {
      unsigned i;
      unsigned fence = bmSetFence( bm );

      /* Move all buffers to head of resident list and set their fences
       */
      for (i = 0; i < list->nr; i++) {
	 struct buffer *buf = _mesa_HashLookup(bm->hash, list->elem[i].buffer);

	 if (!buf->block->has_ttm) {
	     move_to_head(&buf->block->pool->lru, buf->block);
	 }
	 buf->block->fence = fence;
      }

      return fence;
   }
   else
      return 0;
}


/* This functionality is used by the buffer manager, not really sure
 * if we need to be exposing it in this way, probably libdrm will
 * offer equivalent calls.
 *
 * For now they can stay, but will likely change/move before final:
 */
unsigned bmSetFence( struct bufmgr *bm )
{
   assert(bm->intel->locked);

   return intelEmitIrqLocked( bm->intel );
}

int bmTestFence( struct bufmgr *bm, unsigned fence )
{
/*    if (fence % 1024 == 0) */
/*       _mesa_printf("%d %d\n", fence, bm->intel->sarea->last_dispatch); */

  DBG("fence: %d %d\n", fence,  bm->intel->sarea->last_dispatch);
   return fence <= bm->intel->sarea->last_dispatch;
}

void bmFinishFence( struct bufmgr *bm, unsigned fence )
{
   if (!bmTestFence(bm, fence))
      intelWaitIrq( bm->intel, fence );
}


/* There is a need to tell the hardware to flush various caches
 * before we can start reading and writing video memory.
 *
 * TODO: Need a flag value to tell hardware which caches have changed?
 * Who would we rely on to populate the flag?
 */


/* If new data is uploaded/mapped to video or agp memory, need to
 * flush the texture and other read caches to ensure the new version
 * is picked up.  Can be done immediately after the upload (ie. within
 * ValidateBuffers).
 */
void bmFlushReadCaches( struct bufmgr *bm )
{
}

/* If a buffer which has been written to is going to be evicted, read
 * by bmGetBufferData or mappped with bmMapBuffer, need to flush the
 * write cache first.  Probably want to make sure this happens
 * immediately after the last write and before the fence (how to
 * tell?).  If we wait until just prior the evict/read/map, would then
 * have to emit another fence and wait for the hw queue to drain to be
 * sure the caches had flushed.
 *
 * A possible strategy:
 * - every once in a while, when there is no last_draw_flush_fence outstanding,
 *     emit a draw-cache flush just prior to the fence.
 * - note the fence (last_draw_flush_fence)
 * - note the most recently retired value of last_draw_flush_fence in
 *      last_retired_draw_flush_fence
 * - keep track of which fence each buffer is last written to in
 *      buffer.last_write_fence
 * - on evict/read/map, check:
 *      - if buffer.last_write_fence > last_draw_flush_fence {
 *            emit_flush
 *            last_draw_flush_fence = emit fence 
 *        }
 *        if last_write_fence > last_retired_draw_flush_fence {
 *            finish_fence(last_draw_flush_fence)
 *            last_retired_draw_flush_fence = last_draw_fence
 *        }
 *   
 */
void bmFlushDrawCache( struct bufmgr *bm )
{
}

/* Specifically ignore texture memory sharing.
 */
void bm_fake_NotifyContendedLockTake( struct bufmgr *bm )
{
   fprintf(stderr, "did we just lose texture memory? oh well, never mind\n");
}


