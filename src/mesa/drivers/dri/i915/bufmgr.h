#ifndef BUFMGR_H
#define BUFMGR_H

#include "intel_context.h"

/* Note that this is destined to be external to Mesa, so don't use GL
 * types like GLuint, etc.
 */

/* The buffer manager context.  Opaque.
 */
struct bufmgr;

#define BM_LIST_MAX 32

/* List of buffers to validate.  Probably better managed by the client:
 */
struct bm_buffer_list {
   struct {
      unsigned buffer;
      unsigned *offset_return;
      unsigned *memtype_return;
   } elem[BM_LIST_MAX];

   unsigned nr;
};


struct bufmgr *bm_fake_intel_Attach( struct intel_context *intel ); 

/* struct bufmgr *bmCreate( ... ); */
/* struct bufmgr *bmAttach( ... ); */

/* Define an address space.  Doesn't really do anything, but the
 * information could be used to validate the bmInitPool() requests.
 */
void bmInitMemType( struct bufmgr *,
		    unsigned mem_type,
		    unsigned long size );


/* Create a pool of a given memory type, from a certain offset and a
 * certain size.  
 *
 * Also passed in is a virtual pointer to the start of the pool.  This
 * is useful in the faked-out version in i915 so that MapBuffer can
 * return a pointer to a buffer residing in AGP space.  
 *
 * Flags passed into a pool are inherited by all buffers allocated in
 * that pool.  So pools representing the static front,back,depth
 * buffer allocations should have MEM_AGP|NO_UPLOAD|NO_EVICT|NO_MOVE to match
 * the behaviour of the legacy allocations.
 *
 * Returns -1 for failure, pool number for success.
 */
int bmInitPool( struct bufmgr *, 
		unsigned long low_offset,
		void *low_virtual,
		unsigned long size,
		unsigned flags);


/* Flags for validate and other calls.  If both NO_UPLOAD and NO_EVICT
 * are specified, ValidateBuffers is essentially a query.
 */
#define BM_MEM_LOCAL   0x1
#define BM_MEM_AGP     0x2
#define BM_MEM_VRAM    0x4	/* not yet used */
#define BM_WRITE       0x8	/* not yet used */
#define BM_READ        0x10	/* not yet used */
#define BM_NO_UPLOAD   0x20
#define BM_NO_EVICT    0x40
#define BM_NO_MOVE     0x80	/* not yet used */
#define BM_NO_ALLOC    0x100	/* legacy "fixed" buffers only */
#define BM_CLIENT      0x200	/* for map - pointer will be accessed
				 * without dri lock */
#define BM_NO_TTM         0x400	 

#define BM_MEM_MASK (BM_MEM_LOCAL|BM_MEM_AGP|BM_MEM_VRAM)



/* Stick closely to ARB_vbo semantics - they're well defined and
 * understood, and drivers can just pass the calls through without too
 * much thunking.
 */
void bmGenBuffers(struct bufmgr *, unsigned n, unsigned *buffers);
void bmDeleteBuffers(struct bufmgr *, unsigned n, unsigned *buffers);


/* Hook to inform faked buffer manager about fixed-position
 * front,depth,back buffers.  These may move to a fully memory-managed
 * scheme, or they may continue to be managed as is.
 */
unsigned bmBufferStatic(struct bufmgr *,
			unsigned buffer,
			unsigned size,
			unsigned pool);



/* The driver has more intimate knowledge of the hardare than a GL
 * client would, so flags here is more proscriptive than the usage
 * values in the ARB_vbo interface:
 */
void bmBufferData(struct bufmgr *, 
		  unsigned buffer, 
		  unsigned size, 
		  const void *data, 
		  unsigned flags );

void bmBufferSubData(struct bufmgr *, 
		     unsigned buffer, 
		     unsigned offset, 
		     unsigned size, 
		     const void *data );

void *bmMapBuffer( struct bufmgr *,
		   unsigned buffer, 
		   unsigned access );

void bmUnmapBuffer( struct bufmgr *,
		    unsigned buffer );

/* To be called prior to emitting commands to hardware which reference
 * these buffers.  
 *
 * NewBufferList() and AddBuffer() build up a list of buffers to be
 * validated.  The buffer list provides information on where the
 * buffers should be placed and whether their contents need to be
 * preserved on copying.  The offset data elements are return values
 * from this function telling the driver exactly where the buffers are
 * currently located.
 *
 * ValidateBufferList() performs the actual validation and returns the
 * buffer pools and offsets within the pools.
 *
 * FenceBufferList() must be called to set fences and other
 * housekeeping before unlocking after a successful call to
 * ValidateBufferList(). The buffer manager knows how to emit and test
 * fences directly through the drm and without callbacks to the
 * driver.
 */
struct bm_buffer_list *bmNewBufferList( void );

void bmAddBuffer( struct bm_buffer_list *list,
		  unsigned buffer,
		  unsigned flags,
		  unsigned *pool_return,
		  unsigned *offset_return );

int bmValidateBufferList( struct bufmgr *, 
			  struct bm_buffer_list *,
			  unsigned flags );

unsigned bmFenceBufferList( struct bufmgr *,
			struct bm_buffer_list * );

void bmFreeBufferList( struct bm_buffer_list * );


/* This functionality is used by the buffer manager, not really sure
 * if we need to be exposing it in this way, probably libdrm will
 * offer equivalent calls.
 *
 * For now they can stay, but will likely change/move before final:
 */
unsigned bmSetFence( struct bufmgr * );
int bmTestFence( struct bufmgr *, unsigned fence );
void bmFinishFence( struct bufmgr *, unsigned fence );

void bmFlushReadCaches( struct bufmgr *bm );
void bmFlushDrawCache( struct bufmgr *bm );

void bm_fake_NotifyContendedLockTake( struct bufmgr * );

extern int INTEL_DEBUG;
#define DEBUG_BUFMGR 0x2000

#define DBG(...)  do { if (INTEL_DEBUG & DEBUG_BUFMGR) _mesa_printf(__VA_ARGS__); } while(0)
#define DBG_BM(...)  do { if (0) _mesa_printf(__VA_ARGS__); } while(0)

#endif
