/**
 * \file radeon_ioctl.c
 * \brief DRM interface functions.
 *
 * \author Kevin E. Martin <martin@valinux.com>
 * \author Gareth Hughes <gareth@valinux.com>
 * \author Keith Whitwell <keith@tungstengraphics.com>
 */

/*
 * Copyright 2000, 2001 ATI Technologies Inc., Ontario, Canada, and
 *                      VA Linux Systems Inc., Fremont, California.
 * 
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * on the rights to use, copy, modify, merge, publish, distribute, sub
 * license, and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * ATI, VA LINUX SYSTEMS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* $XFree86: xc/lib/GL/mesa/src/drv/radeon/radeon_ioctl.c,v 1.7 2002/09/16 18:05:19 eich Exp $ */

#include "glheader.h"
#include "imports.h"
#include "simple_list.h"
#include "radeon_context.h"
#include "radeon_state.h"
#include "radeon_ioctl.h"
#include "radeon_macros.h"  /* for INREG() */
#include <unistd.h>  /* for usleep() */
#include <errno.h>

#if _HAVE_SWRAST
#include "swrast/swrast.h"
#endif
#if _HAVE_SANITY
#include "radeon_sanity.h"
#endif

#define RADEON_TIMEOUT             512
#define RADEON_IDLE_RETRY           16


static void radeonWaitForIdle( radeonContextPtr rmesa );

/***************************************************************/
/** \name Kernel command buffer handling
 */
/*@{*/

/**
 * \brief Print state atom information.
 *
 * For debugging purposes only.
 *
 * \param state state atom.
 */
static void print_state_atom( struct radeon_state_atom *state )
{
   int i;

   fprintf(stderr, "emit %s/%d\n", state->name, state->cmd_size);

   if (RADEON_DEBUG & DEBUG_VERBOSE) 
      for (i = 0 ; i < state->cmd_size ; i++) 
	 fprintf(stderr, "\t%s[%d]: %x\n", state->name, i, state->cmd[i]);

}

/**
 * \brief Emit a list of state atoms.
 *
 * \param rmesa Radeon context.
 * \param list state atom list.
 * 
 * For each active state in the list copies the associated commands into the
 * command buffer, and moves the atom into the clean list.
 *
 */
static void radeon_emit_state_list( radeonContextPtr rmesa, 
				    struct radeon_state_atom *list )
{
   struct radeon_state_atom *state, *tmp;
   char *dest;

   foreach_s( state, tmp, list ) {
      if (state->check( rmesa->glCtx )) {
	 dest = radeonAllocCmdBuf( rmesa, state->cmd_size * 4, __FUNCTION__);
	 memcpy( dest, state->cmd, state->cmd_size * 4);
	 move_to_head( &(rmesa->hw.clean), state );
	 if (RADEON_DEBUG & DEBUG_STATE) 
	    print_state_atom( state );
      }
      else if (RADEON_DEBUG & DEBUG_STATE)
	 fprintf(stderr, "skip state %s\n", state->name);
   }
}


/**
 * \brief Emit dirty state.
 *
 * \param rmesa Radeon context.
 *
 * Calls radeon_emit_state_list() with the radeon_hw_state::dirty list. 
 *
 * If radeon_context::lost_context is set then all state is emited by moving
 * everything in radeon_hw_state::dirty prior to the radeon_emit_state_list()
 * call. 
 *
 * \note For working around a Quake3 lock-up radeon_hw_state::zbs is always
 * made \e dirty.
 */
void radeonEmitState( radeonContextPtr rmesa )
{
   struct radeon_state_atom *state, *tmp;

   if (RADEON_DEBUG & (DEBUG_STATE|DEBUG_PRIMS))
      fprintf(stderr, "%s\n", __FUNCTION__);

   /* Somewhat overkill:
    */
   if (rmesa->lost_context) {
      if (RADEON_DEBUG & (DEBUG_STATE|DEBUG_PRIMS|DEBUG_IOCTL))
	 fprintf(stderr, "%s - lost context\n", __FUNCTION__); 

      foreach_s( state, tmp, &(rmesa->hw.clean) ) 
	 move_to_tail(&(rmesa->hw.dirty), state );

      rmesa->lost_context = 0;
   }
   else {
      /* Work around q3 lockup:
       */
      move_to_tail(&(rmesa->hw.dirty), &(rmesa->hw.zbs) );
   }

   if (!(rmesa->radeonScreen->chipset & RADEON_CHIPSET_TCL)) {
      foreach_s( state, tmp, &(rmesa->hw.dirty) ) {
	 if (state->is_tcl) {
	    move_to_head( &(rmesa->hw.clean), state );
	 }
      }
   }

   radeon_emit_state_list( rmesa, &rmesa->hw.dirty );
}



/**
 * \brief Fire a section of the retained buffer as a regular
 * primitive.  
 *
 * \param rmesa Radeon context.
 * \param vertex_format vertex format.
 * \param primitive primitive.
 * \param vertex_nr number of vertices.
 *
 * Emits the dirty state and adds a new command to the command buffer for
 * firing the vertices pointed by radeon_context::ioctl.
 */
extern void radeonEmitVbufPrim( radeonContextPtr rmesa,
				GLuint vertex_format,
				GLuint primitive,
				GLuint vertex_nr )
{
   drmRadeonCmdHeader *cmd;


   assert(rmesa->dri.drmMinor >= 3); 
   assert(!(primitive & RADEON_CP_VC_CNTL_PRIM_WALK_IND));
   
   radeonEmitState( rmesa );

   if (RADEON_DEBUG & DEBUG_IOCTL)
      fprintf(stderr, "%s cmd_used/4: %d\n", __FUNCTION__,
	      rmesa->store.cmd_used/4);
   
   cmd = (drmRadeonCmdHeader *)radeonAllocCmdBuf( rmesa, 6 * sizeof(*cmd),
						  __FUNCTION__ );
   cmd[0].header.cmd_type = RADEON_CMD_PACKET3_CLIP;
   cmd[1].i = RADEON_CP_PACKET3_3D_RNDR_GEN_INDX_PRIM | (3 << 16);
   cmd[2].i = rmesa->ioctl.vertex_offset;
   cmd[3].i = vertex_nr;
   cmd[4].i = vertex_format;
   cmd[5].i = (primitive | 
	       RADEON_CP_VC_CNTL_PRIM_WALK_LIST |
	       RADEON_CP_VC_CNTL_COLOR_ORDER_RGBA |
	       RADEON_CP_VC_CNTL_VTX_FMT_RADEON_MODE |
	       (vertex_nr << RADEON_CP_VC_CNTL_NUM_SHIFT));

   if (RADEON_DEBUG & DEBUG_PRIMS)
      fprintf(stderr, "%s: header 0x%x offt 0x%x vfmt 0x%x vfcntl %x \n",
	      __FUNCTION__,
	      cmd[1].i, cmd[2].i, cmd[4].i, cmd[5].i);
}


#if _HAVE_FULL_GL
void radeonFlushElts( radeonContextPtr rmesa )
{
   int *cmd = (int *)(rmesa->store.cmd_buf + rmesa->store.elts_start);
   int dwords;
   int nr = (rmesa->store.cmd_used - (rmesa->store.elts_start + 24)) / 2;

   if (RADEON_DEBUG & DEBUG_IOCTL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   assert( rmesa->dma.flush == radeonFlushElts );
   rmesa->dma.flush = 0;

   /* Cope with odd number of elts:
    */
   rmesa->store.cmd_used = (rmesa->store.cmd_used + 2) & ~2;
   dwords = (rmesa->store.cmd_used - rmesa->store.elts_start) / 4;

   cmd[1] |= (dwords - 3) << 16;
   cmd[5] |= nr << RADEON_CP_VC_CNTL_NUM_SHIFT;
}


GLushort *radeonAllocEltsOpenEnded( radeonContextPtr rmesa,
				    GLuint vertex_format,
				    GLuint primitive,
				    GLuint min_nr )
{
   drmRadeonCmdHeader *cmd;
   GLushort *retval;

   if (RADEON_DEBUG & DEBUG_IOCTL)
      fprintf(stderr, "%s %d\n", __FUNCTION__, min_nr);

   assert(rmesa->dri.drmMinor >= 3); 
   assert((primitive & RADEON_CP_VC_CNTL_PRIM_WALK_IND));
   
   radeonEmitState( rmesa );
   
   cmd = (drmRadeonCmdHeader *)radeonAllocCmdBuf( rmesa, 
						  24 + min_nr*2,
						  __FUNCTION__ );
   cmd[0].i = 0;
   cmd[0].header.cmd_type = RADEON_CMD_PACKET3_CLIP;
   cmd[1].i = RADEON_CP_PACKET3_3D_RNDR_GEN_INDX_PRIM;
   cmd[2].i = rmesa->ioctl.vertex_offset;
   cmd[3].i = 0xffff;
   cmd[4].i = vertex_format;
   cmd[5].i = (primitive | 
	       RADEON_CP_VC_CNTL_PRIM_WALK_IND |
	       RADEON_CP_VC_CNTL_COLOR_ORDER_RGBA |
	       RADEON_CP_VC_CNTL_VTX_FMT_RADEON_MODE);

   retval = (GLushort *)(cmd+6);

   if (RADEON_DEBUG & DEBUG_PRIMS)
      fprintf(stderr, "%s: header 0x%x vfmt 0x%x prim %x \n",
	      __FUNCTION__,
	      cmd[1].i, vertex_format, primitive);

   assert(!rmesa->dma.flush);
   rmesa->dma.flush = radeonFlushElts;

   rmesa->store.elts_start = ((char *)cmd) - rmesa->store.cmd_buf;

   return retval;
}

void radeonEmitAOS( radeonContextPtr rmesa,
		    struct radeon_dma_region **component,
		    GLuint nr,
		    GLuint offset )
{
   assert( nr == 1 );
   assert( component[0]->aos_size == component[0]->aos_stride );
   rmesa->ioctl.vertex_size = component[0]->aos_size;
   rmesa->ioctl.vertex_offset = 
      (component[0]->aos_start + offset * component[0]->aos_stride * 4);
}
#endif


/**
 * \brief Emit vertex array of structures.
 *
 * \param rmesa Radeon context.
 * \param vertex_size size of the vertex buffer.
 * \param offset offset of the vertex buffer.
 * 
 * Updates radeon_context::ioctl with the given parameters.
 */
void radeonEmitVertexAOS( radeonContextPtr rmesa,
			  GLuint vertex_size,
			  GLuint offset )
{
   rmesa->ioctl.vertex_size = vertex_size;
   rmesa->ioctl.vertex_offset = offset;
}
		       

/**
 * \brief Flush the command buffer while holding the hardware lock.
 *
 * \param rmesa Radeon context.
 * \param caller name of the calling function for debugging purposes.
 *
 * \return zero on success, non-zero otherwise.
 *
 * Issues a DRM_RADEON_CMDBUF command to the DRM passing a drmRadeonCmdBuffer
 * structure as argument. The command buffer is reset before returning.
 *
 * If debugging is enabled, it prints several debug information and performs a
 * sanity check before.
 * 
 * \note Does not emit any commands to avoid recursion on radeonAllocCmdBuf().
 */ 
static int radeonFlushCmdBufLocked( radeonContextPtr rmesa, 
				    const char * caller )
{
   int ret, i;
   drmRadeonCmdBuffer cmd;

   if (RADEON_DEBUG & DEBUG_IOCTL) {
      fprintf(stderr, "%s from %s\n", __FUNCTION__, caller); 

      if (RADEON_DEBUG & DEBUG_VERBOSE) 
	 for (i = 0 ; i < rmesa->store.cmd_used ; i += 4 )
	    fprintf(stderr, "%d: %x\n", i/4, 
		    *(int *)(&rmesa->store.cmd_buf[i]));
   }

   if (RADEON_DEBUG & DEBUG_DMA)
      fprintf(stderr, "%s: Releasing %d buffers\n", __FUNCTION__,
	      rmesa->dma.nr_released_bufs);


   if (RADEON_DEBUG & DEBUG_SANITY) {
#if _HAVE_SANITY
      if (rmesa->state.scissor.enabled) 
	 ret = radeonSanityCmdBuffer( rmesa, 
				      rmesa->state.scissor.numClipRects,
				      rmesa->state.scissor.pClipRects);
      else
	 ret = radeonSanityCmdBuffer( rmesa, 
				      rmesa->numClipRects,
				      rmesa->pClipRects);
#endif
   }

   cmd.bufsz = rmesa->store.cmd_used;
   cmd.buf = rmesa->store.cmd_buf;

   if (rmesa->state.scissor.enabled) {
      cmd.nbox = rmesa->state.scissor.numClipRects;
      cmd.boxes = (drmClipRect *)rmesa->state.scissor.pClipRects;
   } else {
      cmd.nbox = rmesa->numClipRects;
      cmd.boxes = (drmClipRect *)rmesa->pClipRects;
   }

   ret = drmCommandWrite( rmesa->dri.fd,
			  DRM_RADEON_CMDBUF,
			  &cmd, sizeof(cmd) );

   rmesa->store.primnr = 0;
   rmesa->store.statenr = 0;
   rmesa->store.cmd_used = 0;
   rmesa->dma.nr_released_bufs = 0;
   rmesa->lost_context = 1;	
   return ret;
}


/**
 * \brief Flush the command buffer.
 *
 * \param rmesa Radeon context.
 * \param caller name of the calling function for debugging purposes.
 *
 * Locks the hardware and calls radeonFlushCmdBufLocked(), aborting in case of
 * failure.
 */
void radeonFlushCmdBuf( radeonContextPtr rmesa, const char *caller )
{
   int ret;
   assert (rmesa->dri.drmMinor >= 3);

   LOCK_HARDWARE( rmesa );
   ret = radeonFlushCmdBufLocked( rmesa, caller );
   UNLOCK_HARDWARE( rmesa );

   if (ret) {
      fprintf(stderr, "drmRadeonCmdBuffer: %d\n", ret);
      exit(ret);
   }
}

/*@}*/


/***************************************************************/
/** \name Hardware vertex buffer handling
 */
/*@{*/

/**
 * \brief Refill the current DMA region.
 *
 * \param rmesa Radeon context.
 *
 * Releases and eventually flushes the current DMA region (if the number of
 * released buffers is greater than 4). Locks the hardware and requests a new
 * DMA buffer as the new current DMA region. 
 *
 * In case of failure in the first try to get a new DMA buffer, flushes any
 * previously released buffers, waits for engine is idle and tries once more,
 * aborting if it fails.
 */
void radeonRefillCurrentDmaRegion( radeonContextPtr rmesa )
{
   struct radeon_dma_buffer *dmabuf;
   int fd = rmesa->dri.fd;
   int index = 0;
   int size = 0;
   drmDMAReq dma;
   int ret;

   if (RADEON_DEBUG & (DEBUG_IOCTL|DEBUG_DMA))
      fprintf(stderr, "%s\n", __FUNCTION__);  

   if (rmesa->dma.flush) {
      rmesa->dma.flush( rmesa );
   }

   if (rmesa->dma.current.buf)
      radeonReleaseDmaRegion( rmesa, &rmesa->dma.current, __FUNCTION__ );

   if (rmesa->dma.nr_released_bufs > 4)
      radeonFlushCmdBuf( rmesa, __FUNCTION__ );

   dma.context = rmesa->dri.hwContext;
   dma.send_count = 0;
   dma.send_list = NULL;
   dma.send_sizes = NULL;
   dma.flags = 0;
   dma.request_count = 1;
   dma.request_size = RADEON_BUFFER_SIZE;
   dma.request_list = &index;
   dma.request_sizes = &size;
   dma.granted_count = 0;

   LOCK_HARDWARE(rmesa);	/* no need to validate */

   ret = drmDMA( fd, &dma );
      
   if (ret != 0) {
      /* Free some up this way?
       */
      if (rmesa->dma.nr_released_bufs) {
	 radeonFlushCmdBufLocked( rmesa, __FUNCTION__ );
      }
      
      if (RADEON_DEBUG & DEBUG_DMA)
	 fprintf(stderr, "Waiting for buffers\n");

      radeonWaitForIdleLocked( rmesa );
      ret = drmDMA( fd, &dma );

      if ( ret != 0 ) {
	 UNLOCK_HARDWARE( rmesa );
	 fprintf( stderr, "Error: Could not get dma buffer... exiting\n" );
	 exit( -1 );
      }
   }

   UNLOCK_HARDWARE(rmesa);

   if (RADEON_DEBUG & DEBUG_DMA)
      fprintf(stderr, "Allocated buffer %d\n", index);

   dmabuf = CALLOC_STRUCT( radeon_dma_buffer );
   dmabuf->buf = &rmesa->radeonScreen->buffers->list[index];
   dmabuf->refcount = 1;

   rmesa->dma.current.buf = dmabuf;
   rmesa->dma.current.address = dmabuf->buf->address;
   rmesa->dma.current.end = dmabuf->buf->total;
   rmesa->dma.current.start = 0;
   rmesa->dma.current.ptr = 0;
}

/**
 * \brief Release DMA region.
 *
 * \param rmesa Radeon context.
 * \param region ragion to be released.
 * \param caller caller's name for debugging purposes.
 *
 * Decreases the region reference count, and if it reaches zero sends the
 * RADEON_CMD_DMA_DISCARD with its buffer index.
 */
void radeonReleaseDmaRegion( radeonContextPtr rmesa,
			     struct radeon_dma_region *region,
			     const char *caller )
{
   if (RADEON_DEBUG & DEBUG_IOCTL)
      fprintf(stderr, "%s from %s\n", __FUNCTION__, caller); 
   
   if (!region->buf)
      return;

   if (rmesa->dma.flush)
      rmesa->dma.flush( rmesa );

   if (--region->buf->refcount == 0) {
      drmRadeonCmdHeader *cmd;

      if (RADEON_DEBUG & (DEBUG_IOCTL|DEBUG_DMA))
	 fprintf(stderr, "%s -- DISCARD BUF %d\n", __FUNCTION__,
		 region->buf->buf->idx);  
      
      cmd = (drmRadeonCmdHeader *)radeonAllocCmdBuf( rmesa, sizeof(*cmd), 
						     __FUNCTION__ );
      cmd->dma.cmd_type = RADEON_CMD_DMA_DISCARD;
      cmd->dma.buf_idx = region->buf->buf->idx;
      FREE(region->buf);
      rmesa->dma.nr_released_bufs++;
   }

   region->buf = 0;
   region->start = 0;
}

/**
 * \brief Allocates a new region from radeon_dma::current.
 *
 * \param rmesa Radeon context.
 * \param region region will received the allocated region.
 * \param bytes size.
 * \param alignment alignment.
 * 
 * If there isn't enough space in the current DMA buffer, grab a new buffer
 * (and discard what was left of it).
 */
void radeonAllocDmaRegion( radeonContextPtr rmesa, 
			   struct radeon_dma_region *region,
			   int bytes,
			   int alignment )
{
   if (RADEON_DEBUG & DEBUG_IOCTL)
      fprintf(stderr, "%s %d\n", __FUNCTION__, bytes);

   if (rmesa->dma.flush)
      rmesa->dma.flush( rmesa );

   if (region->buf)
      radeonReleaseDmaRegion( rmesa, region, __FUNCTION__ );

   alignment--;
   rmesa->dma.current.start = rmesa->dma.current.ptr = 
      (rmesa->dma.current.ptr + alignment) & ~alignment;

   if ( rmesa->dma.current.ptr + bytes > rmesa->dma.current.end ) 
      radeonRefillCurrentDmaRegion( rmesa );

   region->start = rmesa->dma.current.start;
   region->ptr = rmesa->dma.current.start;
   region->end = rmesa->dma.current.start + bytes;
   region->address = rmesa->dma.current.address;
   region->buf = rmesa->dma.current.buf;
   region->buf->refcount++;

   rmesa->dma.current.ptr += bytes; /* bug - if alignment > 7 */
   rmesa->dma.current.start = 
      rmesa->dma.current.ptr = (rmesa->dma.current.ptr + 0x7) & ~0x7;  

   if ( rmesa->dri.drmMinor < 3 ) 
      radeonRefillCurrentDmaRegion( rmesa );
}

/**
 * \brief Allocate a DMA region for vertices.
 * 
 * Calls radeonAllocDmaRegion() with \p bytes = \p vertsize * \p numverts.
 */
void radeonAllocDmaRegionVerts( radeonContextPtr rmesa, 
				struct radeon_dma_region *region,
				int numverts,
				int vertsize,
				int alignment )
{
   radeonAllocDmaRegion( rmesa, region, vertsize * numverts, alignment );
}

/*@}*/


/******************************************************************/
/** \name SwapBuffers with client-side throttling
 */
/*@{*/

/**
 * \brief Get last frame.
 *
 * \param rmesa Radeon context.
 *
 * \return last frame number.
 * 
 * Gets the last frame number via the DRM_RADEON_GETPARAM command in recent
 * DRMs, or via the RADEON_LAST_FRAME_REG register.
 */
static GLuint radeonGetLastFrame (radeonContextPtr rmesa) 
{
   unsigned char *RADEONMMIO = rmesa->radeonScreen->mmio.map;
   int ret;
   GLuint frame;

   if (rmesa->dri.screen->drmMinor >= 4) {
      drmRadeonGetParam gp;

      gp.param = RADEON_PARAM_LAST_FRAME;
      gp.value = (int *)&frame;
      ret = drmCommandWriteRead( rmesa->dri.fd, DRM_RADEON_GETPARAM,
				 &gp, sizeof(gp) );
   } 
   else
      ret = -EINVAL;

   if ( ret == -EINVAL ) {
      frame = INREG( RADEON_LAST_FRAME_REG );
   } 
   else if ( ret ) {
      fprintf( stderr, "%s: drmRadeonGetParam: %d\n", __FUNCTION__, ret );
      exit(1);
   }

   return frame;
}


/**
 * \brief Emit an IRQ while holding the hardware lock.
 *
 * \param rmesa Radeon context.
 *
 * Sends the DRM_RADEON_IRQ_EMIT command, aborting on failure.
 */
static void radeonEmitIrqLocked( radeonContextPtr rmesa )
{
   drmRadeonIrqEmit ie;
   int ret;

   ie.irq_seq = &rmesa->iw.irq_seq;
   ret = drmCommandWriteRead( rmesa->dri.fd, DRM_RADEON_IRQ_EMIT, 
			      &ie, sizeof(ie) );
   if ( ret ) {
      fprintf( stderr, "%s: drmRadeonIrqEmit: %d\n", __FUNCTION__, ret );
      exit(1);
   }
}


/**
 * \brief Wait on IRQ.
 *
 * \param rmesa Radeon context.
 *
 * Sends the DRM_RADEON_IRQ_WAIT command, aborting on failure.
 */
static void radeonWaitIrq( radeonContextPtr rmesa )
{
   int ret;

   do {
      ret = drmCommandWrite( rmesa->dri.fd, DRM_RADEON_IRQ_WAIT,
			     &rmesa->iw, sizeof(rmesa->iw) );
   } while (ret && (errno == EINTR || errno == EAGAIN));

   if ( ret ) {
      fprintf( stderr, "%s: drmRadeonIrqWait: %d\n", __FUNCTION__, ret );
      exit(1);
   }
}


/**
 * \brief Wait for frame completion.
 *
 * \param rmesa Radeon context.
 *
 * Waits until the number of processed frames reaches RADEONSAREAPriv::last_frame in the
 * SAREA.
 *
 * The idea is to only emit IRQ's if the graphics card is the bottleneck -- ie
 * only do it if we find that the previous frame hasn't completed. When the
 * card is the bottlneck one'd like to do something like:
 *
 *\code
 * render frame 0
 * swap buffers
 * emit IRQ 0
 * render frame 1
 * wait on IRQ 0 (i.e. wait for last frame to complete)
 * swap buffers
 * emit IRQ 1,
 * ...
 * \endcode
 *
 * But, if there's no need to wait for hardware (i.e., the application/driver
 * is bottleneck), then one'd prefer:
 *
 * \code
 * render frame 0
 * swapbuffers
 * render frame 1
 * swapbuffers
 * ...
 * \endcode
 *
 * without any doing any IRQ or waiting.
 *
 * The radeon_context::irqsEmitted determines transition between these modes.
 * It is set to 10 if it ever has to wait, and decremented otherwise.  If it
 * finds it has to wait, checks radeon_context::irqsEmitted to determine if
 * there is an IRQ pending that we can wait on -- otherwise do busy wait.
 * Finally, after the waiting/not-waiting is over, checks
 * radeon_context::irqsEmitted, if non-zero, emits an IRQ.
 *
 * If IRQ's aren't supported for whatever reason, it always busy waits.
 *
 * This function assumes that the hardware was locked prior to the call but
 * all waits are internally done with the hardware unlocked.
 */
static void radeonWaitForFrameCompletion( radeonContextPtr rmesa )
{
   RADEONSAREAPrivPtr sarea = rmesa->sarea;

   if (rmesa->do_irqs) {
      if (radeonGetLastFrame(rmesa) < sarea->last_frame) {
	 if (!rmesa->irqsEmitted) {
	    while (radeonGetLastFrame (rmesa) < sarea->last_frame)
	       ;
	 }
	 else {
	    UNLOCK_HARDWARE( rmesa ); 
	    radeonWaitIrq( rmesa );	
	    LOCK_HARDWARE( rmesa ); 
	 }
	 rmesa->irqsEmitted = 10;
      }

      if (rmesa->irqsEmitted) {
	 radeonEmitIrqLocked( rmesa );
	 rmesa->irqsEmitted--;
      }
   } 
   else {
      while (radeonGetLastFrame (rmesa) < sarea->last_frame) {
	 UNLOCK_HARDWARE( rmesa ); 
	 if (rmesa->do_usleeps) 
	    usleep(1); 
	 LOCK_HARDWARE( rmesa ); 
      }
   }
}

/**
 * \brief Copy the back color buffer to the front color buffer.
 *
 * \param dPriv DRI specific drawable data.
 * 
 * Fires the existing vertices and waits for frame completion and vertical
 * retrace. Sends the DRM_RADEON_SWAP command for each set of existing
 * cliprects.
 */
void radeonCopyBuffer( const __DRIdrawablePrivate *dPriv )
{
   radeonContextPtr rmesa;
   GLint nbox, i, ret;

   assert(dPriv);
   assert(dPriv->driContextPriv);
   assert(dPriv->driContextPriv->driverPrivate);

   rmesa = (radeonContextPtr) dPriv->driContextPriv->driverPrivate;
   if (!rmesa->radeonScreen->buffers)
      return;


   if ( RADEON_DEBUG & DEBUG_IOCTL ) {
      fprintf( stderr, "\n%s( %p )\n\n", __FUNCTION__, rmesa->glCtx );
   }

   RADEON_FIREVERTICES( rmesa );
   LOCK_HARDWARE( rmesa );

   /* Throttle the frame rate -- only allow one pending swap buffers
    * request at a time.
    */
   radeonWaitForFrameCompletion( rmesa );
   radeonWaitForVBlank( rmesa );

   nbox = rmesa->dri.drawable->numClipRects; /* must be in locked region */

   for ( i = 0 ; i < nbox ; ) {
      GLint nr = MIN2( i + RADEON_NR_SAREA_CLIPRECTS , nbox );
      XF86DRIClipRectPtr box = rmesa->dri.drawable->pClipRects;
      XF86DRIClipRectPtr b = rmesa->sarea->boxes;
      GLint n = 0;

      for ( ; i < nr ; i++ ) {
	 *b++ = box[i];
	 n++;
      }
      rmesa->sarea->nbox = n;

      ret = drmCommandNone( rmesa->dri.fd, DRM_RADEON_SWAP );

      if ( ret ) {
	 fprintf( stderr, "DRM_RADEON_SWAP_BUFFERS: return = %d\n", ret );
	 UNLOCK_HARDWARE( rmesa );
	 exit( 1 );
      }
   }

   UNLOCK_HARDWARE( rmesa );
}


/**
 * \brief Do page flipping.
 *
 * \param dPriv DRI drawable speficic data.
 *
 * Fires the existing vertices and waits for frame completion and vertical
 * retrace. Sends the DRM_RADEON_FLIP command and updates the value of
 * radeon_colorbuffer_state::drawOffset and
 * radeon_colorbuffer_state::drawPitch to point to the front or back color
 * buffer.
 */
void radeonPageFlip( const __DRIdrawablePrivate *dPriv )
{
   radeonContextPtr rmesa;
   GLint ret;

   assert(dPriv);
   assert(dPriv->driContextPriv);
   assert(dPriv->driContextPriv->driverPrivate);

   rmesa = (radeonContextPtr) dPriv->driContextPriv->driverPrivate;

   if (!rmesa->radeonScreen->buffers)
      return;


   if ( RADEON_DEBUG & DEBUG_IOCTL ) {
      fprintf(stderr, "%s %d\n", __FUNCTION__, 
	      rmesa->sarea->pfCurrentPage );
   }

   RADEON_FIREVERTICES( rmesa );

   LOCK_HARDWARE( rmesa );

   /* Need to do this for the perf box placement:
    */
   if (rmesa->dri.drawable->numClipRects)
   {
      XF86DRIClipRectPtr box = rmesa->dri.drawable->pClipRects;
      XF86DRIClipRectPtr b = rmesa->sarea->boxes;
      b[0] = box[0];
      rmesa->sarea->nbox = 1;
   }
   else {
      UNLOCK_HARDWARE( rmesa );
      return;
   }

   /* Throttle the frame rate -- only allow one pending swap buffers
    * request at a time.
    */
   radeonWaitForFrameCompletion( rmesa );
   radeonWaitForVBlank( rmesa );

   ret = drmCommandNone( rmesa->dri.fd, DRM_RADEON_FLIP );

   UNLOCK_HARDWARE( rmesa );

   if ( ret ) {
      fprintf( stderr, "DRM_RADEON_FLIP: return = %d\n", ret );
      exit( 1 );
   }

   if ( rmesa->sarea->pfCurrentPage == 1 ) {
	 rmesa->state.color.drawOffset = rmesa->radeonScreen->frontOffset;
	 rmesa->state.color.drawPitch  = rmesa->radeonScreen->frontPitch;
   } else {
	 rmesa->state.color.drawOffset = rmesa->radeonScreen->backOffset;
	 rmesa->state.color.drawPitch  = rmesa->radeonScreen->backPitch;
   }

   RADEON_STATECHANGE( rmesa, ctx );
   rmesa->hw.ctx.cmd[CTX_RB3D_COLOROFFSET] = rmesa->state.color.drawOffset;
   rmesa->hw.ctx.cmd[CTX_RB3D_COLORPITCH]  = rmesa->state.color.drawPitch;
}

/*@}*/


/******************************************************************/
/* \name Buffer clear
 */
/*@{*/

/**
 * \brief Maximum number of clears to buffer.
 */
#define RADEON_MAX_CLEARS	256

/**
 * \brief Clear buffers.
 *
 * \param ctx GL context.
 * \param mask buffer clear mask.
 * \param all whether to clear them all or just a rectangle.
 * \param cx clearing rectangle abcissa.
 * \param cy clearing rectangle ordinate.
 * \param cw clearing rectangle width.
 * \param ch clearing rectangle height.
 *
 * First emits the current state, fires the vertices and calculate the clearing
 * flags to pass to the clear ioctl later.
 *
 * Locks the hardware and throttles the number of clear ioctl's done, allowing
 * up to #RADEON_MAX_CLEARS. For each set of cliprects, intersects them with
 * the clearing rectangle (if not clearing all) and uploads them to the SAREA,
 * setups a drmRadeonClearT structure sends it to the DRM_RADEON_CLEAR
 * command.
 */
static void radeonClear( GLcontext *ctx, GLbitfield mask, GLboolean all,
			 GLint cx, GLint cy, GLint cw, GLint ch )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   __DRIdrawablePrivate *dPriv = rmesa->dri.drawable;
   RADEONSAREAPrivPtr sarea = rmesa->sarea;
   unsigned char *RADEONMMIO = rmesa->radeonScreen->mmio.map;
   GLuint clear;
   GLuint flags = 0;
   GLuint color_mask = 0;
   GLint ret, i;

   if (!rmesa->radeonScreen->buffers)
      return;
   
   if ( RADEON_DEBUG & DEBUG_IOCTL ) {
      fprintf( stderr, "%s:  all=%d cx=%d cy=%d cw=%d ch=%d\n",
	       __FUNCTION__, all, cx, cy, cw, ch );
   }

   radeonEmitState( rmesa );

   /* Need to cope with lostcontext here as kernel relies on
    * some residual state:
    */
   RADEON_FIREVERTICES( rmesa ); 

   if ( mask & DD_FRONT_LEFT_BIT ) {
      flags |= RADEON_FRONT;
      color_mask = rmesa->hw.msk.cmd[MSK_RB3D_PLANEMASK];
      mask &= ~DD_FRONT_LEFT_BIT;
   }

   if ( mask & DD_BACK_LEFT_BIT ) {
      flags |= RADEON_BACK;
      color_mask = rmesa->hw.msk.cmd[MSK_RB3D_PLANEMASK];
      mask &= ~DD_BACK_LEFT_BIT;
   }

   if ( mask & DD_DEPTH_BIT ) {
      if ( ctx->Depth.Mask ) flags |= RADEON_DEPTH; /* FIXME: ??? */
      mask &= ~DD_DEPTH_BIT;
   }

   if ( (mask & DD_STENCIL_BIT) && rmesa->state.stencil.hwBuffer ) {
      flags |= RADEON_STENCIL;
      mask &= ~DD_STENCIL_BIT;
   }

#if _HAVE_SWRAST
   if ( mask )
      _swrast_Clear( ctx, mask, all, cx, cy, cw, ch );
#endif

   if ( !flags ) 
      return;


   /* Flip top to bottom */
   cx += dPriv->x;
   cy  = dPriv->y + dPriv->h - cy - ch;

   LOCK_HARDWARE( rmesa );

   /* Throttle the number of clear ioctls we do.
    */
   while ( 1 ) {
      int ret;

      if (rmesa->dri.screen->drmMinor >= 4) {
	drmRadeonGetParam gp;

	gp.param = RADEON_PARAM_LAST_CLEAR;
	gp.value = (int *)&clear;
	ret = drmCommandWriteRead( rmesa->dri.fd,
				   DRM_RADEON_GETPARAM, &gp, sizeof(gp) );
      } else
	ret = -EINVAL;

      if ( ret == -EINVAL ) {
	 clear = INREG( RADEON_LAST_CLEAR_REG );
      } else if ( ret ) {
	 fprintf( stderr, "%s: drmRadeonGetParam: %d\n", __FUNCTION__, ret );
	 exit(1);
      }
      if ( RADEON_DEBUG & DEBUG_IOCTL ) {
	 fprintf( stderr, "%s( %d )\n", __FUNCTION__, (int)clear );
	 if ( ret ) fprintf( stderr, " ( RADEON_LAST_CLEAR register read directly )\n" );
      }

      if ( sarea->last_clear - clear <= RADEON_MAX_CLEARS ) {
	 break;
      }

      if ( rmesa->do_usleeps ) {
	 UNLOCK_HARDWARE( rmesa );
	 usleep(1);
	 LOCK_HARDWARE( rmesa );
      }
   }

   for ( i = 0 ; i < dPriv->numClipRects ; ) {
      GLint nr = MIN2( i + RADEON_NR_SAREA_CLIPRECTS, dPriv->numClipRects );
      XF86DRIClipRectPtr box = dPriv->pClipRects;
      XF86DRIClipRectPtr b = rmesa->sarea->boxes;
      drmRadeonClearType clear;
      drmRadeonClearRect depth_boxes[RADEON_NR_SAREA_CLIPRECTS];
      GLint n = 0;

      if ( !all ) {
	 for ( ; i < nr ; i++ ) {
	    GLint x = box[i].x1;
	    GLint y = box[i].y1;
	    GLint w = box[i].x2 - x;
	    GLint h = box[i].y2 - y;

	    if ( x < cx ) w -= cx - x, x = cx;
	    if ( y < cy ) h -= cy - y, y = cy;
	    if ( x + w > cx + cw ) w = cx + cw - x;
	    if ( y + h > cy + ch ) h = cy + ch - y;
	    if ( w <= 0 ) continue;
	    if ( h <= 0 ) continue;

	    b->x1 = x;
	    b->y1 = y;
	    b->x2 = x + w;
	    b->y2 = y + h;
	    b++;
	    n++;
	 }
      } else {
	 for ( ; i < nr ; i++ ) {
	    *b++ = box[i];
	    n++;
	 }
      }

      rmesa->sarea->nbox = n;

      clear.flags       = flags;
      clear.clear_color = rmesa->state.color.clear;
      clear.clear_depth = rmesa->state.depth.clear;
      clear.color_mask  = rmesa->hw.msk.cmd[MSK_RB3D_PLANEMASK];
      clear.depth_mask  = rmesa->state.stencil.clear;
      clear.depth_boxes = depth_boxes;

      n--;
      b = rmesa->sarea->boxes;
      for ( ; n >= 0 ; n-- ) {
	 depth_boxes[n].f[RADEON_CLEAR_X1] = (float)b[n].x1;
	 depth_boxes[n].f[RADEON_CLEAR_Y1] = (float)b[n].y1;
	 depth_boxes[n].f[RADEON_CLEAR_X2] = (float)b[n].x2;
	 depth_boxes[n].f[RADEON_CLEAR_Y2] = (float)b[n].y2;
	 depth_boxes[n].f[RADEON_CLEAR_DEPTH] = 
	    (float)rmesa->state.depth.clear;
      }

      ret = drmCommandWrite( rmesa->dri.fd, DRM_RADEON_CLEAR,
			     &clear, sizeof(drmRadeonClearType));

      if ( ret ) {
	 UNLOCK_HARDWARE( rmesa );
	 fprintf( stderr, "DRM_RADEON_CLEAR: return = %d\n", ret );
	 exit( 1 );
      }
   }

   UNLOCK_HARDWARE( rmesa );
}


/**
 * \brief Wait for engine idle while holding the hardware lock.
 *
 * \param rmesa Radeon context.
 *
 * Sends the DRM_RADEON_CP_IDLE command until the engine is reported as idle or
 * a timeout occurs.
 */
void radeonWaitForIdleLocked( radeonContextPtr rmesa )
{
    int fd = rmesa->dri.fd;
    int to = 0;
    int ret, i = 0;

    do {
        do {
            ret = drmCommandNone( fd, DRM_RADEON_CP_IDLE);
        } while ( ret && errno == EBUSY && i++ < RADEON_IDLE_RETRY );
    } while ( ( ret == -EBUSY ) && ( to++ < RADEON_TIMEOUT ) );

    if ( ret < 0 ) {
	UNLOCK_HARDWARE( rmesa );
	fprintf( stderr, "Error: Radeon timed out... exiting\n" );
	exit( -1 );
    }
}


/**
 * \brief Wait for engine idle.
 *
 * \param rmesa Radeon context.
 *
 * Locks the hardware and calls radeonWaitForIdleLocked().
 */
static void radeonWaitForIdle( radeonContextPtr rmesa )
{
    LOCK_HARDWARE(rmesa);
    radeonWaitForIdleLocked( rmesa );
    UNLOCK_HARDWARE(rmesa);
}


/**
 * \brief Wait for vertical retrace.
 *
 * \param rmesa Radeon context.
 *
 * Disabled - no-op.
 */
void radeonWaitForVBlank( radeonContextPtr rmesa )
{
#if 0
    drmVBlank vbl;
    int ret;

    if ( !rmesa->radeonScreen->irq )
	return;

    if ( getenv("LIBGL_SYNC_REFRESH") ) {
	/* Wait for until the next vertical blank */
	vbl.request.type = DRM_VBLANK_RELATIVE;
	vbl.request.sequence = 1;
    } else if ( getenv("LIBGL_THROTTLE_REFRESH") ) {
	/* Wait for at least one vertical blank since the last call */
	vbl.request.type = DRM_VBLANK_ABSOLUTE;
	vbl.request.sequence = rmesa->vbl_seq + 1;
    } else {
	return;
    }

    UNLOCK_HARDWARE( rmesa );

    if ((ret = drmWaitVBlank( rmesa->dri.fd, &vbl ))) {
	fprintf(stderr, "%s: drmWaitVBlank returned %d, IRQs don't seem to be"
		" working correctly.\nTry running with LIBGL_THROTTLE_REFRESH"
		" and LIBL_SYNC_REFRESH unset.\n", __FUNCTION__, ret);
	exit(1);
    } else if (RADEON_DEBUG & DEBUG_IOCTL)
	fprintf(stderr, "%s: drmWaitVBlank returned %d\n", __FUNCTION__, ret);

    rmesa->vbl_seq = vbl.reply.sequence;

    LOCK_HARDWARE( rmesa );
#endif
}

/**
 * \brief Flush all dirty state and pending buffers.
 * 
 * \param ctx GL context.
 *
 * Calls radeonEmitState() with the dirty state list if not empty, and
 * radeonFlushCmdBuf() if the command buffer has been used.
 */
void radeonFlush( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT( ctx );

   if (RADEON_DEBUG & DEBUG_IOCTL)
      fprintf(stderr, "%s\n", __FUNCTION__);

   if (!rmesa->radeonScreen->buffers)
      return;

   if (rmesa->dma.flush)
      rmesa->dma.flush( rmesa );

   if (rmesa->dri.drmMinor >= 3) {
      if (!is_empty_list(&rmesa->hw.dirty)) 
	 radeonEmitState( rmesa );
   
      if (rmesa->store.cmd_used)
	 radeonFlushCmdBuf( rmesa, __FUNCTION__ );
   }
}

/**
 * \brief Make sure all commands have been sent to the hardware and have
 * completed processing.
 *
 * \param ctx GL context.
 *
 * If IRQs are enabled then emits and waits on the IRQ, otherwise waits for
 * engine idle.
 */
void radeonFinish( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);

   if (!rmesa->radeonScreen->buffers)
      return;

   radeonFlush( ctx );

   if (rmesa->do_irqs) {
      LOCK_HARDWARE( rmesa );
      radeonEmitIrqLocked( rmesa );
      UNLOCK_HARDWARE( rmesa );
      radeonWaitIrq( rmesa );
   }
   else
      radeonWaitForIdle( rmesa );
}


/**
 * \brief Setup the GL context callbacks.
 *
 * \param ctx GL context.
 *
 * \sa Called by radeonCreateContext().
 */
void radeonInitIoctlFuncs( GLcontext *ctx )
{
    ctx->Driver.Clear = radeonClear;
    ctx->Driver.Finish = radeonFinish;
    ctx->Driver.Flush = radeonFlush;
}

/*@}*/
