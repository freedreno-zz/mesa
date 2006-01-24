#ifndef BUFMGR_H
#define BUFMGR_H

#include "intel_context.h"

/* Note that this is destined to be external to Mesa, so don't use GL
 * types like GLuint, etc.
 */

/* The buffer manager context.  Opaque.
 */
struct bufmgr;
struct bm_buffer_list;

struct bufmgr *bm_fake_intel_Attach( struct intel_context *intel );


/* struct bufmgr *bmCreate( ... ); */
/* struct bufmgr *bmAttach( ... ); */

void bmInitPool( struct bufmgr *, 
		 unsigned pool, 
		 unsigned long low_offset,
		 unsigned long high_offset,
		 void *virtual_base );

#define BM_MEM_LOCAL   0x1
#define BM_MEM_AGP     0x2
#define BM_MEM_VRAM    0x4	/* not used */

#define BM_WRITE       0x100	/* not used */
#define BM_READ        0x200	/* not used */


/* Flags for validate.  If both NO_UPLOAD and NO_EVICT are specified,
 * ValidateBuffers is essentially a query.
 */
#define BM_NO_UPLOAD 0x1
#define BM_NO_EVICT  0x2


/* Stick closely to ARB_vbo semantics - they're well defined and
 * understood, and drivers can just pass the calls through without too
 * much thunking.
 */
void bmGenBuffers(struct bufmgr *, unsigned n, unsigned *buffers);
void bmDeleteBuffers(struct bufmgr *, unsigned n, unsigned *buffers);

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

void bmAddBuffer( struct bufmgr *,
		  struct bm_buffer_list *list,
		  unsigned buffer,
		  unsigned flags,
		  unsigned *pool_return,
		  unsigned *offset_return );

int bmValidateBufferList( struct bufmgr *, 
			  struct bm_buffer_list *,
			  unsigned flags );

void bmFenceBufferList( struct bufmgr *,
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

#endif
