#ifndef BUFMGR_H
#define BUFMGR_H

#include "intel_context.h"

/* Note that this is destined to be external to Mesa, so don't use GL
 * types like GLuint, etc.
 */

/* The buffer manager context.  Opaque.
 */
struct bufmgr;

struct bufmgr *bm_fake_intel_Attach( struct intel_context *intel );


/* struct bufmgr *bmCreate( ... ); */
/* struct bufmgr *bmAttach( ... ); */

void bmInitPool( struct bufmgr *, 
		 unsigned pool, 
		 unsigned long low_offset,
		 unsigned long high_offset,
		 void *virtual_base );


#define BM_READ        0x1
#define BM_DRAW        0x2
#define BM_MEM_SYS     0x4
#define BM_MEM_GTT     0x8
#define BM_MEM_VRAM    0x10
#define BM_MEM_CACHED  0x20 

/* Maximum number of buffers to pass to bmValidateBufferList:
 */
#define BM_VALIDATE_MAX 32

/* As in ARB_vbo, use integers to talk about buffers.  Hopefully this
 * facilitates sharing them between processes.
 */
struct buffer_usage {
   unsigned buffer;
   unsigned flags:16;
   unsigned alignment:16;
   unsigned offset;
   unsigned pool;
};


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

void bmUnmapBuffer( struct bufmgr * );

/* To be called prior to emitting commands to hardware which reference
 * these buffers.  The buffer_usage list provides information on where
 * the buffers should be placed and whether their contents need to be
 * preserved on copying.  The offset and pool data elements are return
 * values from this function telling the driver exactly where the
 * buffers are currently located.
 */
unsigned bmValidateBufferList( struct bufmgr *,
			       struct buffer_usage *,
			       unsigned nr );


/* After commands are emitted but before unlocking, this must be
 * called so that the buffer manager can correctly age the buffers.
 * The buffer manager keeps track of the list of validated buffers, so
 * already knows what to apply the fence to.
 *
 * The buffer manager knows how to emit and test fences directly
 * through the drm and without callbacks or whatever into the driver.
 */
void bmFenceValidatedBuffers( struct bufmgr * );


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
