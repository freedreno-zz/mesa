/* Fake version of the buffer manager so that we can prototype the
 * changes in a driver fairly quickly.  Basically wraps the old style
 * memory management in the new programming interface.
 *
 * Version 1:  Just the soggy old dri memory manager.
 *
 * Future:  Import the via memory manager semantics.
 */
#include "bufmgr.h"

#include "intel_context.h"
#include "intel_ioctl.h"

#include "hash.h"
#include "simple_list.h"
#include "mm.h"

struct _mesa_HashTable;


/* Wrapper around mm.c's mem_block, which understands that you must
 * wait for fences to expire before memory can be freed.  This is
 * specific to our use of memcpy for uploads - an upload that was
 * processed through the command queue wouldn't need to care about
 * fences.
 */
struct fenced_block {
   struct fenced_block *next, *prev;
   struct mem_block *mem;
   unsigned fence;
   struct buffer *buf;
};

struct buffer {
   unsigned id;			/* debug only */
   unsigned offset;
   unsigned size;
   unsigned alignment;

   void *local;		/* backing store */
   struct fenced_block *block;	/* uploaded agp */
};

struct pool {
   unsigned size;
   struct mem_block *heap;
   void *virtual;
   struct fenced_block lru;
   struct fenced_block freed;
};

struct bufmgr {
   struct intel_context *intel;
   struct buffer buffer_list;
   struct pool pool;

   struct _mesa_HashTable *hash;
   unsigned buf_nr;		/* for generating ids */

   /* Temporary storage while validating and unvalidating: 
    */
   struct buffer *validated[BM_VALIDATE_MAX];
   unsigned nr_validated;

   /* Context clobbering
    */
   unsigned global_wait_fence;
   unsigned last_fence;
};


static int alloc_agp( struct bufmgr *bm,
		      struct buffer *buf )
{
   struct fenced_block *block = (struct fenced_block *)calloc(sizeof *block, 1);
   if (!block)
      return 0;

   block->mem = mmAllocMem(bm->pool.heap, buf->size, buf->alignment, 0);
   if (!block->mem) {
      free(block);
      return 0;
   }

   make_empty_list(block);
   block->buf = buf;
   buf->block = block;

   return 1;
}

/* Release the card storage associated with buf:
 */
static void free_agp( struct bufmgr *bm,
		      struct buffer *buf )
{
   if (!buf->block)
      return;
   else if (bmTestFence(bm, buf->block->fence)) {
      mmFreeMem(buf->block->mem);
      buf->block = NULL;
   }
   else {
      /* Add an entry to the free list for this range and the fence at
       * which it becomes free.
       */
      move_to_tail(&bm->pool.freed, buf->block);
      buf->block->buf = NULL;
      buf->block = NULL;
   }
}

static int delayed_free( struct bufmgr *bm )
{
   struct fenced_block *s, *tmp;
   int ret = 0;

   foreach_s(s, tmp, &bm->pool.freed ) {
      if (bmTestFence(bm, s->fence)) {
	 remove_from_list(s);
	 mmFreeMem(s->mem);
	 free(s);
	 ret = 1;
      }
   }
   
   return ret;
}


static unsigned evict_lru( struct bufmgr *bm )
{
   if (delayed_free(bm))
      return 1;
   else {
      struct fenced_block *block = bm->pool.lru.next;

      if (block == &bm->pool.lru)
	 return 0;
   
      bmFinishFence(bm, block->fence);
      free_agp(bm, block->buf);   
      return 1;
   }
}


/* This differs slightly from the old dri memory manager as it tries
 * to make sure all allocations are satisfied at once.
 */
static unsigned try_validate( struct bufmgr *bm )
{
   struct buffer *allocs[BM_VALIDATE_MAX];
   unsigned nr_allocs = 0;
   unsigned i;

   for (i = 0; i < bm->nr_validated; i++) {
      struct buffer *buf = bm->validated[i];
      if (buf->block)
	 continue;
      if (!alloc_agp(bm, buf))
	 goto fail;
      allocs[nr_allocs++] = buf;
   }

   /* If that succeeded, upload data to allocated regions:
    */
   for (i = 0; i < nr_allocs; i++) {
      struct buffer *buf = allocs[i];
      void *dst = bm->pool.virtual + buf->block->mem->ofs;
      memcpy(dst, buf->local, buf->size);
   }

   /* Tell hardware that its texture and other caches may be invalid: 
    */
   bmFlushReadCaches(bm);   
   return 1;

   /* Undo allocations if failed:
    */
 fail:
   for (i = 0; i < nr_allocs; i++)
      free_agp(bm, allocs[i]);

   return 0;
}




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

/* The virtual pointer would go away in a true implementation.
 */
void bmInitPool( struct bufmgr *bm, 
		 unsigned pool, 
		 unsigned long low_offset,
		 unsigned long high_offset,
		 void *virtual_base )
{
   if (pool > 0 || low_offset >= high_offset)
      return;
   
   bm->pool.size = high_offset - low_offset;
   bm->pool.heap = mmInit( low_offset, bm->pool.size );
   bm->pool.virtual = virtual_base;
   
   make_empty_list(&bm->pool.lru);
   make_empty_list(&bm->pool.freed);
}



void bmGenBuffers(struct bufmgr *bm, unsigned n, unsigned *buffers)
{
   unsigned i;

   for (i = 0; i < n; i++) {
      buffers[i] = bm->buf_nr++;      
      _mesa_HashInsert(bm->hash, buffers[i], calloc(sizeof(struct buffer), 1));
   }
}


void bmDeleteBuffers(struct bufmgr *bm, unsigned n, unsigned *buffers)
{
   unsigned i;
   
   for (i = 0; i < n; i++) {
      struct buffer *buf = _mesa_HashLookup(bm->hash, buffers[i]);
      if (buf) {
	 free(buf);
	 _mesa_HashRemove(bm->hash, buffers[i]);
      }
   }
}

void bmBufferData(struct bufmgr *bm, 
		  unsigned buffer, 
		  unsigned size, 
		  const void *data, 
		  unsigned flags )
{
   struct buffer *buf = (struct buffer *)_mesa_HashLookup( bm->hash, buffer );

   free_agp(bm, buf);
   free(buf->local);
   buf->size = size;
      
   if (data != NULL) {
      buf->local = malloc(size);     
      memcpy(buf->local, data, size);
   }
}

void bmBufferSubData(struct bufmgr *bm, 
		     unsigned buffer, 
		     unsigned offset, 
		     unsigned size, 
		     const void *data )
{
   struct buffer *buf = (struct buffer *)_mesa_HashLookup( bm->hash, buffer );
   
   if (!buf->local) 
      buf->local = malloc(buf->size);     
   
   memcpy(buf->local + offset, data, size);
   
   if (buf->block) {
      if (1 || !bmTestFence(bm, buf->block->fence))
	 free_agp(bm, buf);
      else {
	 /* LOCK HARDWARE! */
	 memcpy(buf->local + offset, data, size); 
      }
   }
}


void *bmMapBuffer( struct bufmgr *bm,
		   unsigned buffer, 
		   unsigned access )
{
   struct buffer *buf = (struct buffer *)_mesa_HashLookup( bm->hash, buffer );
   
   if (!buf->local) 
      buf->local = malloc(buf->size);     
   
   if (buf->block)
      free_agp(bm, buf);
   
   return buf->local;
}

void bmUnmapBuffer( struct bufmgr *bm )
{
   /* Nothing to do */
}





/* To be called prior to emitting commands to hardware which reference
 * these buffers.  The buffer_usage list provides information on where
 * the buffers should be placed and whether their contents need to be
 * preserved on copying.  The offset and pool data elements are return
 * values from this function telling the driver exactly where the
 * buffers are currently located.
 */
unsigned bmValidateBufferList( struct bufmgr *bm,
			       struct buffer_usage *usage,
			       unsigned nr )
{
   unsigned i;
   unsigned total = 0;
   unsigned align_total = 0;

   if (nr > BM_VALIDATE_MAX)
      return 0;

   /* On context switch, all our buffers invalidated: (Fix by
    * importing global lru if you can be bothered)
    */
   if (bm->global_wait_fence) {
      bmFinishFence(bm, bm->global_wait_fence);
      while (evict_lru(bm))
	 ;
      bm->global_wait_fence = 0;
   }

   /* Build validate list, calculate total size.  Total calculated may
    * underestimate real total because of alignment, packing issues.
    * Only looking at a single pool here.
    */
   for (i = 0; i < nr; i++) {
      bm->validated[i] = (struct buffer *)_mesa_HashLookup( bm->hash, usage[i].buffer );
      
      /* This is a bit odd - but where should alignment be specified?
       */
      if (bm->validated[i]->alignment != usage[i].alignment &&
	  bm->validated[i]->alignment != 0)
	 return 0;		
      
      bm->validated[i]->alignment = usage[i].alignment;

      total += bm->validated[i]->size;
      align_total += 1 << bm->validated[i]->alignment;
   }

   /* Don't need to try allocation in this case:
    */
   if (total > bm->pool.size)
      return 0;
   
   bm->nr_validated = nr;

   /* The old story: evict one texture after another until allocation
    * succeeds.  This is pretty shite but really hard to do better
    * without more infrastucture...  Which is coming - hooray!
    */
   while (!try_validate(bm)) {
      if (!evict_lru(bm))
	 return 0;
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
void bmFenceValidatedBuffers( struct bufmgr *bm )
{
   unsigned i;

   bm->last_fence = bmSetFence( bm );

   /* Move all buffers to head of resident list and set their fences
    */
   for (i = 0; i < bm->nr_validated; i++) {
      move_to_head(&bm->pool.lru, bm->validated[i]->block);
      bm->validated[i]->block->fence = bm->last_fence;
   }

}


/* This functionality is used by the buffer manager, not really sure
 * if we need to be exposing it in this way, probably libdrm will
 * offer equivalent calls.
 *
 * For now they can stay, but will likely change/move before final:
 */
unsigned bmSetFence( struct bufmgr *bm )
{
   assert(bm->intel->batch.space == bm->intel->batch.size);
   assert(bm->intel->locked);

   return intelEmitIrqLocked( bm->intel );
}

int bmTestFence( struct bufmgr *bm, unsigned fence )
{
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
void bmFlushReadCaches( struct bufmgr *bm )
{
}

void bmFlushDrawCache( struct bufmgr *bm )
{
}

/* A full version of this fake memory manager would take the Global
 * LRU into account at this point.  I can't be bothered and will just
 * evict all local textures if it looks like another context has been
 * texturing.  The Global LRU is going away & doesn't have any
 * relevence to the ultimate aims of this code.
 */
void bm_fake_NotifyContendedLockTake( struct bufmgr *bm )
{
   /* Will wait for this value, then evict all local textures.
    */
   if (bm->intel->sarea->last_enqueue != bm->last_fence)
      bm->global_wait_fence = bm->intel->sarea->last_enqueue;
}


