/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/mga/mga_dri.c,v 1.28 2003/02/08 21:26:58 dawes Exp $ */

/*
 * Copyright 2000 VA Linux Systems Inc., Fremont, California.
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Keith Whitwell <keith@tungstengraphics.com>
 *    Gareth Hughes <gareth@valinux.com>
 */

#include <errno.h>
#include <unistd.h>

#include "miniglxP.h"
#include "dri_util.h"
#include "drm.h"


#include "mga_reg.h"
#include "mga.h"
#include "mga_macros.h"
#include "mga_dri.h"
#include "mga_sarea.h"

#include "sarea.h"



/* Quiescence, locking
 */
#define MGA_TIMEOUT		2048

static void MGAWaitForIdleDMA( struct MiniGLXDisplayRec *dpy, MGAPtr pMga )
{
   drmMGALock lock;
   int ret;
   int i = 0;

   memset( &lock, 0, sizeof(drmMGALock) );

   for (;;) {
      do {
         /* first ask for quiescent and flush */
         lock.flags = DRM_MGA_LOCK_QUIESCENT | DRM_MGA_LOCK_FLUSH;
         do {
	    ret = drmCommandWrite( dpy->drmFD, DRM_MGA_FLUSH,
                                   &lock, sizeof( drmMGALock ) );
         } while ( ret == -EBUSY && i++ < DRM_MGA_IDLE_RETRY );

         /* if it's still busy just try quiescent */
         if ( ret == -EBUSY ) { 
            lock.flags = DRM_MGA_LOCK_QUIESCENT;
            do {
	       ret = drmCommandWrite( dpy->drmFD, DRM_MGA_FLUSH,
                                      &lock, sizeof( drmMGALock ) );
            } while ( ret == -EBUSY && i++ < DRM_MGA_IDLE_RETRY );
         }
      } while ( ( ret == -EBUSY ) && ( i++ < MGA_TIMEOUT ) );

      if ( ret == 0 )
	 return;

      fprintf( stderr,
               "[dri] Idle timed out, resetting engine...\n" );

      drmCommandNone( dpy->drmFD, DRM_MGA_RESET );
   }
}

static unsigned int mylog2( unsigned int n )
{
   unsigned int log2 = 1;
   while ( n > 1 ) n >>= 1, log2++;
   return log2;
}

static int MGADRIAgpInit(struct MiniGLXDisplayRec *dpy, MGAPtr pMga)
{
   unsigned long mode;
   unsigned int vendor, device;
   int ret, count, i;

   if(pMga->agpSize < 12)pMga->agpSize = 12;
   if(pMga->agpSize > 64)pMga->agpSize = 64; /* cap */

   /* FIXME: Make these configurable...
    */
   pMga->agp.size = pMga->agpSize * 1024 * 1024;

   pMga->warp.offset = 0;
   pMga->warp.size = MGA_WARP_UCODE_SIZE;

   pMga->primary.offset = (pMga->warp.offset +
				    pMga->warp.size);
   pMga->primary.size = 1024 * 1024;

   pMga->buffers.offset = (pMga->primary.offset +
				    pMga->primary.size);
   pMga->buffers.size = MGA_NUM_BUFFERS * MGA_BUFFER_SIZE;


   pMga->agpTextures.offset = (pMga->buffers.offset +
                                    pMga->buffers.size);

   pMga->agpTextures.size = pMga->agp.size -
                                     pMga->agpTextures.offset;

   if ( drmAgpAcquire( dpy->drmFD ) < 0 ) {
     fprintf( stderr, "[agp] AGP not available\n" );
      return 0;
   }

   mode   = drmAgpGetMode( dpy->drmFD );        /* Default mode */
   vendor = drmAgpVendorId( dpy->drmFD );
   device = drmAgpDeviceId( dpy->drmFD );

   mode &= ~MGA_AGP_MODE_MASK;
   switch ( pMga->agpMode ) {
   case 4:
      mode |= MGA_AGP_4X_MODE;
   case 2:
      mode |= MGA_AGP_2X_MODE;
   case 1:
   default:
      mode |= MGA_AGP_1X_MODE;
   }

#if 0
   fprintf( stderr,
            "[agp] Mode 0x%08lx [AGP 0x%04x/0x%04x; Card 0x%04x/0x%04x]\n",
            mode, vendor, device,
            dpy->pciVendor,
            dpy->pciChipType );
#endif

   if ( drmAgpEnable( dpy->drmFD, mode ) < 0 ) {
     fprintf( stderr, "[agp] AGP not enabled\n" );
      drmAgpRelease( dpy->drmFD );
      return 0;
   }

   if ( pMga->Chipset == PCI_CHIP_MGAG200 ) {
      switch ( pMga->agpMode ) {
      case 2:
	 fprintf( stderr,
		     "[drm] Enabling AGP 2x PLL encoding\n" );
	 OUTREG( MGAREG_AGP_PLL, MGA_AGP2XPLL_ENABLE );
	 break;

      case 1:
      default:
	 fprintf( stderr,
		     "[drm] Disabling AGP 2x PLL encoding\n" );
	 OUTREG( MGAREG_AGP_PLL, MGA_AGP2XPLL_DISABLE );
	 pMga->agpMode = 1;
	 break;
      }
   }

   ret = drmAgpAlloc( dpy->drmFD, pMga->agp.size,
		      0, NULL, &pMga->agp.handle );
   if ( ret < 0 ) {
      fprintf( stderr, "[agp] Out of memory (%d)\n", ret );
      drmAgpRelease( dpy->drmFD );
      return 0;
   }
   fprintf( stderr,
	       "[agp] %d kB allocated with handle 0x%08x\n",
	       pMga->agp.size/1024, (unsigned int)pMga->agp.handle );

   if ( drmAgpBind( dpy->drmFD, pMga->agp.handle, 0 ) < 0 ) {
      fprintf( stderr, "[agp] Could not bind memory\n" );
      drmAgpFree( dpy->drmFD, pMga->agp.handle );
      drmAgpRelease( dpy->drmFD );
      return 0;
   }

   /* WARP microcode space
    */
   if ( drmAddMap( dpy->drmFD,
		   pMga->warp.offset,
		   pMga->warp.size,
		   DRM_AGP, DRM_READ_ONLY,
		   &pMga->warp.handle ) < 0 ) {
      fprintf( stderr,
		  "[agp] Could not add WARP microcode mapping\n" );
      return 0;
   }
   fprintf( stderr,
	       "[agp] WARP microcode handle = 0x%08lx\n",
	       pMga->warp.handle );

   if ( drmMap( dpy->drmFD,
		pMga->warp.handle,
		pMga->warp.size,
		&pMga->warp.map ) < 0 ) {
      fprintf( stderr,
		  "[agp] Could not map WARP microcode\n" );
      return 0;
   }
   fprintf( stderr,
	       "[agp] WARP microcode mapped at 0x%08lx\n",
	       (unsigned long)pMga->warp.map );

   /* Primary DMA space
    */
   if ( drmAddMap( dpy->drmFD,
		   pMga->primary.offset,
		   pMga->primary.size,
		   DRM_AGP, DRM_READ_ONLY,
		   &pMga->primary.handle ) < 0 ) {
      fprintf( stderr,
		  "[agp] Could not add primary DMA mapping\n" );
      return 0;
   }
   fprintf( stderr,
	       "[agp] Primary DMA handle = 0x%08lx\n",
	       pMga->primary.handle );

   if ( drmMap( dpy->drmFD,
		pMga->primary.handle,
		pMga->primary.size,
		&pMga->primary.map ) < 0 ) {
      fprintf( stderr,
		  "[agp] Could not map primary DMA\n" );
      return 0;
   }
   fprintf( stderr,
	       "[agp] Primary DMA mapped at 0x%08lx\n",
	       (unsigned long)pMga->primary.map );

   /* DMA buffers
    */
   if ( drmAddMap( dpy->drmFD,
		   pMga->buffers.offset,
		   pMga->buffers.size,
		   DRM_AGP, 0,
		   &pMga->buffers.handle ) < 0 ) {
      fprintf( stderr,
		  "[agp] Could not add DMA buffers mapping\n" );
      return 0;
   }
   fprintf( stderr,
	       "[agp] DMA buffers handle = 0x%08lx\n",
	       pMga->buffers.handle );

   if ( drmMap( dpy->drmFD,
		pMga->buffers.handle,
		pMga->buffers.size,
		&pMga->buffers.map ) < 0 ) {
      fprintf( stderr,
		  "[agp] Could not map DMA buffers\n" );
      return 0;
   }
   fprintf( stderr,
	       "[agp] DMA buffers mapped at 0x%08lx\n",
	       (unsigned long)pMga->buffers.map );

   count = drmAddBufs( dpy->drmFD,
		       MGA_NUM_BUFFERS, MGA_BUFFER_SIZE,
		       DRM_AGP_BUFFER, pMga->buffers.offset );
   if ( count <= 0 ) {
      fprintf( stderr,
		  "[drm] failure adding %d %d byte DMA buffers\n",
		  MGA_NUM_BUFFERS, MGA_BUFFER_SIZE );
      return 0;
   }
   fprintf( stderr,
	       "[drm] Added %d %d byte DMA buffers\n",
	       count, MGA_BUFFER_SIZE );

   i = mylog2(pMga->agpTextures.size / MGA_NR_TEX_REGIONS);
   if(i < MGA_LOG_MIN_TEX_REGION_SIZE)
      i = MGA_LOG_MIN_TEX_REGION_SIZE;
   pMga->agpTextures.size = (pMga->agpTextures.size >> i) << i;

   if ( drmAddMap( dpy->drmFD,
                   pMga->agpTextures.offset,
                   pMga->agpTextures.size,
                   DRM_AGP, 0,
                   &pMga->agpTextures.handle ) < 0 ) {
      fprintf( stderr,
                  "[agp] Could not add agpTexture mapping\n" );
      return 0;
   }
/* should i map it ? */
   fprintf( stderr,
               "[agp] agpTexture handle = 0x%08lx\n",
               pMga->agpTextures.handle );
   fprintf( stderr,
               "[agp] agpTexture size: %d kb\n", pMga->agpTextures.size/1024 );

   return 1;
}

static int MGADRIMapInit( struct MiniGLXDisplayRec *dpy, MGAPtr pMga )
{
   pMga->registers.size = MGAIOMAPSIZE;

   if ( drmAddMap( dpy->drmFD,
		   (drmHandle)pMga->IOAddress,
		   pMga->registers.size,
		   DRM_REGISTERS, DRM_READ_ONLY,
		   &pMga->registers.handle ) < 0 ) {
      fprintf( stderr,
		  "[drm] Could not add MMIO registers mapping\n" );
      return 0;
   }
   fprintf( stderr,
	       "[drm] Registers handle = 0x%08lx\n",
	       pMga->registers.handle );

   pMga->status.size = SAREA_MAX;

   if ( drmAddMap( dpy->drmFD, 0, pMga->status.size,
		   DRM_SHM, DRM_READ_ONLY | DRM_LOCKED | DRM_KERNEL,
		   &pMga->status.handle ) < 0 ) {
      fprintf( stderr,
		  "[drm] Could not add status page mapping\n" );
      return 0;
   }
   fprintf( stderr,
	       "[drm] Status handle = 0x%08lx\n",
	       pMga->status.handle );

   if ( drmMap( dpy->drmFD,
		pMga->status.handle,
		pMga->status.size,
		&pMga->status.map ) < 0 ) {
      fprintf( stderr,
		  "[agp] Could not map status page\n" );
      return 0;
   }
   fprintf( stderr,
	       "[agp] Status page mapped at 0x%08lx\n",
	       (unsigned long)pMga->status.map );

   return 1;
}

static int MGADRIKernelInit( struct MiniGLXDisplayRec *dpy, MGAPtr pMga )
{
   drmMGAInit init;
   int ret;

   memset( &init, 0, sizeof(drmMGAInit) );

   init.func = MGA_INIT_DMA;
   init.sarea_priv_offset = sizeof(XF86DRISAREARec);

   switch ( pMga->Chipset ) {
   case PCI_CHIP_MGAG550:
   case PCI_CHIP_MGAG400:
      init.chipset = MGA_CARD_TYPE_G400;
      break;
   case PCI_CHIP_MGAG200:
   case PCI_CHIP_MGAG200_PCI:
      init.chipset = MGA_CARD_TYPE_G200;
      break;
   default:
      return 0;
   }

   init.sgram = 0; /* FIXME !pMga->HasSDRAM; */


   switch (dpy->bpp)
     {
     case 16:
       init.maccess = MGA_MACCESS_PW16;
       break;
     case 32:
       init.maccess = MGA_MACCESS_PW32;
       break;
     default:
       fprintf( stderr, "[mga] invalid bpp (%d)\n", dpy->bpp );
       return 0;
     }


   init.fb_cpp		= dpy->bpp / 8;
   init.front_offset	= pMga->frontOffset;
   init.front_pitch	= pMga->frontPitch / init.fb_cpp;
   init.back_offset	= pMga->backOffset;
   init.back_pitch	= pMga->backPitch / init.fb_cpp;

   init.depth_cpp	= dpy->bpp / 8;
   init.depth_offset	= pMga->depthOffset;
   init.depth_pitch	= pMga->depthPitch / init.depth_cpp;

   init.texture_offset[0] = pMga->textureOffset;
   init.texture_size[0] = pMga->textureSize;

   init.fb_offset = dpy->shared.hFrameBuffer;
   init.mmio_offset = pMga->registers.handle;
   init.status_offset = pMga->status.handle;

   init.warp_offset = pMga->warp.handle;
   init.primary_offset = pMga->primary.handle;
   init.buffers_offset = pMga->buffers.handle;

   init.texture_offset[1] = pMga->agpTextures.handle;
   init.texture_size[1] = pMga->agpTextures.size;

   ret = drmCommandWrite( dpy->drmFD, DRM_MGA_INIT, &init, sizeof(drmMGAInit));
   if ( ret < 0 ) {
      fprintf( stderr,
		  "[drm] Failed to initialize DMA! (%d)\n", ret );
      return 0;
   }

   return 1;
}

static void MGADRIIrqInit(struct MiniGLXDisplayRec *dpy, MGAPtr pMga)
{
  if (!pMga->irq)
    {
      pMga->irq = drmGetInterruptFromBusID(dpy->drmFD,
                                           dpy->pciBus,
                                           dpy->pciDevice,
                                           dpy->pciFunc);

      fprintf(stderr, "[drm] got IRQ %d\n", pMga->irq);

    if((drmCtlInstHandler(dpy->drmFD, pMga->irq)) != 0)
      {
        fprintf(stderr,
                "[drm] failure adding irq handler, "
                "there is a device already using that irq\n"
                "[drm] falling back to irq-free operation\n");
        pMga->irq = 0;
      }
    else
      {
        pMga->reg_ien = INREG( MGAREG_IEN );
      }
    }

  if (pMga->irq)
    fprintf(stderr,
            "[drm] dma control initialized, using IRQ %d\n",
            pMga->irq);
}

static int MGADRIBuffersInit( struct MiniGLXDisplayRec *dpy, MGAPtr pMga )
{
   pMga->drmBuffers = drmMapBufs( dpy->drmFD );
   if ( !pMga->drmBuffers )
     {
       fprintf( stderr,
                "[drm] Failed to map DMA buffers list\n" );
       return 0;
     }
   
   fprintf( stderr,
            "[drm] Mapped %d DMA buffers\n",
            pMga->drmBuffers->count );

   return 1;
}

static int MGAMemoryInit( struct MiniGLXDisplayRec *dpy, MGAPtr pMga )
{
   int        width_bytes = dpy->shared.virtualWidth * dpy->cpp;
   int        bufferSize  = ((dpy->shared.virtualHeight * width_bytes
			      + MGA_BUFFER_ALIGN)
			     & ~MGA_BUFFER_ALIGN);
   int        depthSize   = ((((dpy->shared.virtualHeight+15) & ~15) * width_bytes
			      + MGA_BUFFER_ALIGN)
			     & ~MGA_BUFFER_ALIGN);
   int        l;

   pMga->frontOffset = 0;
   pMga->frontPitch = dpy->shared.virtualWidth * dpy->cpp;

   fprintf(stderr, 
	   "Using %d MB AGP aperture\n", pMga->agpSize);
   fprintf(stderr, 
	   "Using %d MB for vertex/indirect buffers\n", pMga->buffers.size>>20);
   fprintf(stderr, 
	   "Using %d MB for AGP textures\n", pMga->agpTextures.size>>20);

   /* Front, back and depth buffers - everything else texture??
    */
   pMga->textureSize = dpy->shared.fbSize - 2 * bufferSize - depthSize;

   if (pMga->textureSize < 0) 
      return 0;

   l = mylog2( pMga->textureSize / MGA_NR_TEX_REGIONS );
   if ( l < MGA_LOG_MIN_TEX_REGION_SIZE )
      l = MGA_LOG_MIN_TEX_REGION_SIZE;

   /* Round the texture size up to the nearest whole number of
    * texture regions.  Again, be greedy about this, don't
    * round down.
    */
   pMga->logTextureGranularity = l;
   pMga->textureSize = (pMga->textureSize >> l) << l;

   /* Set a minimum usable local texture heap size.  This will fit
    * two 256x256x32bpp textures.
    */
   if (pMga->textureSize < 512 * 1024) {
      pMga->textureOffset = 0;
      pMga->textureSize = 0;
   }

   /* Reserve space for textures */
   pMga->textureOffset = ((dpy->shared.fbSize - pMga->textureSize +
			   MGA_BUFFER_ALIGN) &
			  ~MGA_BUFFER_ALIGN);

   /* Reserve space for the shared depth
    * buffer.
    */
   pMga->depthOffset = ((pMga->textureOffset - depthSize +
			 MGA_BUFFER_ALIGN) &
			~MGA_BUFFER_ALIGN);
   pMga->depthPitch = dpy->shared.virtualWidth * dpy->cpp;

   pMga->backOffset = ((pMga->depthOffset - bufferSize +
			MGA_BUFFER_ALIGN) &
                        ~MGA_BUFFER_ALIGN);
   pMga->backPitch = dpy->shared.virtualWidth * dpy->cpp;


   fprintf(stderr, 
	   "Will use back buffer at offset 0x%x\n",
	   pMga->backOffset);
   fprintf(stderr, 
	   "Will use depth buffer at offset 0x%x\n",
	   pMga->depthOffset);
   fprintf(stderr, 
	   "Will use %d kb for textures at offset 0x%x\n",
	   pMga->textureSize/1024, pMga->textureOffset);

   return 1;
} 

static int MGACheckDRMVersion( struct MiniGLXDisplayRec *dpy, MGAPtr pMga )
{
  drmVersionPtr version;

  /* Check the MGA DRM version */
  version = drmGetVersion(dpy->drmFD);
  if ( version ) {
    if ( version->version_major != 3 ||
         version->version_minor < 0 ) {
            /* incompatible drm version */
      fprintf( stderr,
               "[dri] MGADRIScreenInit failed because of a version mismatch.\n"
               "[dri] mga.o kernel module version is %d.%d.%d but version 3.0.x is needed.\n"
               "[dri] Disabling DRI.\n",
               version->version_major,
               version->version_minor,
               version->version_patchlevel );
      drmFreeVersion( version );
      return 0;
    }
    drmFreeVersion( version );
  }

  return 1;
}

static void print_client_msg( MGADRIPtr pMGADRI )
{
  fprintf( stderr, "chipset:                  %d\n", pMGADRI->chipset );

  fprintf( stderr, "width:                    %d\n", pMGADRI->width );
  fprintf( stderr, "height:                   %d\n", pMGADRI->height );
  fprintf( stderr, "mem:                      %d\n", pMGADRI->mem );
  fprintf( stderr, "cpp:                      %d\n", pMGADRI->cpp );

  fprintf( stderr, "agpMode:                  %d\n", pMGADRI->agpMode );

  fprintf( stderr, "frontOffset:              %d\n", pMGADRI->frontOffset );
  fprintf( stderr, "frontPitch:               %d\n", pMGADRI->frontPitch );

  fprintf( stderr, "backOffset:               %d\n", pMGADRI->backOffset );
  fprintf( stderr, "backPitch:                %d\n", pMGADRI->backPitch );

  fprintf( stderr, "depthOffset:              %d\n", pMGADRI->depthOffset );
  fprintf( stderr, "depthPitch:               %d\n", pMGADRI->depthPitch );

  fprintf( stderr, "textureOffset:            %d\n", pMGADRI->textureOffset );
  fprintf( stderr, "textureSize:              %d\n", pMGADRI->textureSize );

  fprintf( stderr, "logTextureGranularity:    %d\n", pMGADRI->logTextureGranularity );
  fprintf( stderr, "logAgpTextureGranularity: %d\n", pMGADRI->logAgpTextureGranularity );

  fprintf( stderr, "agpTextureHandle:         %u\n", (unsigned int)pMGADRI->agpTextureOffset );
  fprintf( stderr, "agpTextureSize:           %u\n", (unsigned int)pMGADRI->agpTextureSize );

#if 0
   pMGADRI->registers.handle	= pMga->registers.handle;
   pMGADRI->registers.size	= pMga->registers.size;
   pMGADRI->status.handle	= pMga->status.handle;
   pMGADRI->status.size		= pMga->status.size;
   pMGADRI->primary.handle	= pMga->primary.handle;
   pMGADRI->primary.size	= pMga->primary.size;
   pMGADRI->buffers.handle	= pMga->buffers.handle;
   pMGADRI->buffers.size	= pMga->buffers.size;
   pMGADRI->sarea_priv_offset = sizeof(XF86DRISAREARec);
#endif
}

static int MGAScreenInit( struct MiniGLXDisplayRec *dpy, MGAPtr pMga )
{
  int       i;
  int       err;
  MGADRIPtr pMGADRI;
  unsigned int serverContext;	

  usleep(100);
  assert(!dpy->IsClient);

   {
      int  width_bytes = (dpy->shared.virtualWidth * dpy->cpp);
      int  maxy        = dpy->shared.fbSize / width_bytes;


      if (maxy <= dpy->shared.virtualHeight * 3) {
	 fprintf(stderr, 
		 "Static buffer allocation failed -- "
		 "need at least %d kB video memory (have %d kB)\n",
		 (dpy->shared.virtualWidth * dpy->shared.virtualHeight *
		  dpy->cpp * 3 + 1023) / 1024,
		 dpy->shared.fbSize / 1024);
	 return 0;
      } 
   }

   switch(pMga->Chipset) {
   case PCI_CHIP_MGAG550:
   case PCI_CHIP_MGAG400:
   case PCI_CHIP_MGAG200:
#if 0
   case PCI_CHIP_MGAG200_PCI:
#endif
      break;
   default:
      fprintf(stderr, "[drm] Direct rendering only supported with G200/G400/G550 AGP\n");
      return 0;
   }

   fprintf( stderr,
	       "[drm] bpp: %d depth: %d\n",
            dpy->bpp, dpy->bpp /* FIXME: depth */ );

   if ( (dpy->bpp / 8) != 2 &&
	(dpy->bpp / 8) != 4 ) {
      fprintf( stderr,
		  "[dri] Direct rendering only supported in 16 and 32 bpp modes\n" );
      return 0;
   }

   dpy->shared.SAREASize = SAREA_MAX;


   /* Note that drmOpen will try to load the kernel module, if needed. */
   dpy->drmFD = drmOpen("mga", NULL );
   if (dpy->drmFD < 0) {
      fprintf(stderr, "[drm] drmOpen failed\n");
      return 0;
   }

   if ((err = drmSetBusid(dpy->drmFD, dpy->pciBusID)) < 0) {
      fprintf(stderr, "[drm] drmSetBusid failed (%d, %s), %s\n",
	      dpy->drmFD, dpy->pciBusID, strerror(-err));
      return 0;
   }

     
   if (drmAddMap( dpy->drmFD,
		  0,
		  dpy->shared.SAREASize,
		  DRM_SHM,
		  DRM_CONTAINS_LOCK,
		  &dpy->shared.hSAREA) < 0)
   {
      fprintf(stderr, "[drm] drmAddMap failed\n");
      return 0;
   }
   fprintf(stderr, "[drm] added %d byte SAREA at 0x%08lx\n",
	   dpy->shared.SAREASize, dpy->shared.hSAREA);

   if (drmMap( dpy->drmFD,
	       dpy->shared.hSAREA,
	       dpy->shared.SAREASize,
	       (drmAddressPtr)(&dpy->pSAREA)) < 0)
   {
      fprintf(stderr, "[drm] drmMap failed\n");
      return 0;
   }
   memset(dpy->pSAREA, 0, dpy->shared.SAREASize);
   fprintf(stderr, "[drm] mapped SAREA 0x%08lx to %p, size %d\n",
	   dpy->shared.hSAREA, dpy->pSAREA, dpy->shared.SAREASize);
   
   /* Need to AddMap the framebuffer and mmio regions here:
    */
   if (drmAddMap( dpy->drmFD,
		  (drmHandle)dpy->FixedInfo.smem_start,
		  dpy->FixedInfo.smem_len,
		  DRM_FRAME_BUFFER,
		  0,
		  &dpy->shared.hFrameBuffer) < 0)
   {
      fprintf(stderr, "[drm] drmAddMap framebuffer failed\n");
      return 0;
   }
   fprintf(stderr, "[drm] framebuffer handle = 0x%08lx\n",
	   dpy->shared.hFrameBuffer);


#if 0 /* will be done in MGADRIMapInit */
   if (drmAddMap(dpy->drmFD, 
		 dpy->FixedInfo.mmio_start,
		 dpy->FixedInfo.mmio_len,
		 DRM_REGISTERS, 
		 DRM_READ_ONLY, 
		 &pMga->registers.handle) < 0) {
      fprintf(stderr, "[drm] drmAddMap mmio failed\n");	
      return 0;
   }
   fprintf(stderr,
	   "[drm] register handle = 0x%08lx\n", pMga->registers.handle);
#endif


   /* Check the mga DRM version */
   if (!MGACheckDRMVersion(dpy, pMga)) {
      return 0;
   }

   if ( !MGADRIAgpInit( dpy, pMga ) ) {
      return 0;
   }

   if ( !MGADRIMapInit( dpy, pMga ) ) {
      return 0;
   }

   /* Memory manager setup */
   if (!MGAMemoryInit(dpy, pMga)) {
      return 0;
   }


   /* Create a 'server' context so we can grab the lock for
    * initialization ioctls.
    */
   if ((err = drmCreateContext(dpy->drmFD, &serverContext)) != 0) {
      fprintf(stderr, "%s: drmCreateContext failed %d\n", __FUNCTION__, err);
      return 0;
   }

   DRM_LOCK(dpy->drmFD, dpy->pSAREA, serverContext, 0); 

   /* Initialize the kernel data structures */
   if (!MGADRIKernelInit(dpy, pMga)) {
      fprintf(stderr, "MGADRIKernelInit failed\n");
      DRM_UNLOCK(dpy->drmFD, dpy->pSAREA, serverContext);
      return 0;
   }

   /* Initialize the vertex buffers list */
   if (!MGADRIBuffersInit(dpy, pMga)) {
      fprintf(stderr, "MGADRIBuffersInit failed\n");
      DRM_UNLOCK(dpy->drmFD, dpy->pSAREA, serverContext);
      return 0;
   }

   /* Initialize IRQ */
   MGADRIIrqInit(dpy, pMga);


   /* Initialize the SAREA private data structure */
   {
      MGASAREAPrivPtr pSAREAPriv;
      pSAREAPriv = (MGASAREAPrivPtr)(((char*)dpy->pSAREA) + 
					sizeof(XF86DRISAREARec));
      memset(pSAREAPriv, 0, sizeof(*pSAREAPriv));
   }


   /* Quick hack to clear the front & back buffers.  Could also use
    * the clear ioctl to do this, but would need to setup hw state
    * first.
    */
   memset(dpy->FrameBuffer + pMga->frontOffset,
	  0,
	  pMga->frontPitch * dpy->shared.virtualHeight );

   memset(dpy->FrameBuffer + pMga->backOffset,
	  0,
	  pMga->backPitch * dpy->shared.virtualHeight );


   /* Can release the lock now */
   DRM_UNLOCK(dpy->drmFD, dpy->pSAREA, serverContext);

   /* This is the struct passed to radeon_dri.so for its initialization */
   dpy->driverClientMsg = malloc(sizeof(MGADRIRec));
   dpy->driverClientMsgSize = sizeof(MGADRIRec);

   pMGADRI                    = (MGADRIPtr)dpy->driverClientMsg;


   switch(pMga->Chipset) {
   case PCI_CHIP_MGAG550:
   case PCI_CHIP_MGAG400:
      pMGADRI->chipset = MGA_CARD_TYPE_G400;
      break;
   case PCI_CHIP_MGAG200:
   case PCI_CHIP_MGAG200_PCI:
      pMGADRI->chipset = MGA_CARD_TYPE_G200;
      break;
   default:
      return 0;
   }
   pMGADRI->width		= dpy->shared.virtualWidth;
   pMGADRI->height		= dpy->shared.virtualHeight;
   pMGADRI->mem			= dpy->shared.fbSize;
   pMGADRI->cpp			= dpy->bpp / 8;

   pMGADRI->agpMode		= pMga->agpMode;

   pMGADRI->frontOffset		= pMga->frontOffset;
   pMGADRI->frontPitch		= pMga->frontPitch;
   pMGADRI->backOffset		= pMga->backOffset;
   pMGADRI->backPitch		= pMga->backPitch;
   pMGADRI->depthOffset		= pMga->depthOffset;
   pMGADRI->depthPitch		= pMga->depthPitch;
   pMGADRI->textureOffset	= pMga->textureOffset;
   pMGADRI->textureSize		= pMga->textureSize;
   pMGADRI->logTextureGranularity = pMga->logTextureGranularity;

   i = mylog2( pMga->agpTextures.size / MGA_NR_TEX_REGIONS );
   if ( i < MGA_LOG_MIN_TEX_REGION_SIZE )
      i = MGA_LOG_MIN_TEX_REGION_SIZE;

   pMGADRI->logAgpTextureGranularity = i;
   pMGADRI->agpTextureOffset = (unsigned int)pMga->agpTextures.handle;
   pMGADRI->agpTextureSize = (unsigned int)pMga->agpTextures.size;

   pMGADRI->registers.handle	= pMga->registers.handle;
   pMGADRI->registers.size	= pMga->registers.size;
   pMGADRI->status.handle	= pMga->status.handle;
   pMGADRI->status.size		= pMga->status.size;
   pMGADRI->primary.handle	= pMga->primary.handle;
   pMGADRI->primary.size	= pMga->primary.size;
   pMGADRI->buffers.handle	= pMga->buffers.handle;
   pMGADRI->buffers.size	= pMga->buffers.size;
   pMGADRI->sarea_priv_offset = sizeof(XF86DRISAREARec);

   print_client_msg( pMGADRI );

   return 1;
}


/**
 * \brief Establish the set of visuals available for the display.
 *
 * \param dpy display handle.
 * \param numConfigs will receive the number of supported visuals.
 * \param configs will point to the list of supported visuals.
 *
 * \return one on sucess, or zero on failure.
 * 
 * \note Requires the ::__GLXvisualConfig data type.
 *
 * Allocates a single visual and fills it with information according to the
 * display bit depth. Supports only 16 and 32 bpp bit depths, aborting
 * otherwise.
 */
static int mgaInitScreenConfigs( struct MiniGLXDisplayRec *dpy,
                                 int *numConfigs, __GLXvisualConfig **configs)
{
   int i;

   *numConfigs = 1;
   *configs = (__GLXvisualConfig *) calloc(*numConfigs, 
					   sizeof(__GLXvisualConfig));

   switch (dpy->bpp) {
   case 32:
      for (i = 0; i < *numConfigs; i++) {
	 (*configs)[i].vid = 100 + i;
	 (*configs)[i].class = TrueColor;
	 (*configs)[i].rgba = True;
	 (*configs)[i].redSize = 8;
	 (*configs)[i].greenSize = 8;
	 (*configs)[i].blueSize = 8;
	 (*configs)[i].alphaSize = 8;
	 (*configs)[i].redMask = 0xff0000;
	 (*configs)[i].greenMask = 0xff00;
	 (*configs)[i].blueMask = 0xff;
	 (*configs)[i].alphaMask = 0xff000000;
	 (*configs)[i].doubleBuffer = True;
	 (*configs)[i].stereo = False;
	 (*configs)[i].bufferSize = 32;
	 (*configs)[i].depthSize = 24;
	 (*configs)[i].stencilSize = 8;
	 (*configs)[i].auxBuffers = 0;
	 (*configs)[i].level = 0;
	 /* leave remaining fields zero */
      }
      break;

   case 16:
      for (i = 0; i < *numConfigs; i++) {
	 (*configs)[i].vid = 100 + i;
	 (*configs)[i].class = TrueColor;
	 (*configs)[i].rgba = True;
	 (*configs)[i].redSize = 5;
	 (*configs)[i].greenSize = 6;
	 (*configs)[i].blueSize = 5;
	 (*configs)[i].alphaSize = 0;
	 (*configs)[i].redMask = 0xf800;
	 (*configs)[i].greenMask = 0x07e0;
	 (*configs)[i].blueMask = 0x001f;
	 (*configs)[i].alphaMask = 0x0000;
	 (*configs)[i].doubleBuffer = True;
	 (*configs)[i].stereo = False;
	 (*configs)[i].bufferSize = 16;
	 (*configs)[i].depthSize = 16;
	 (*configs)[i].stencilSize = 0;
	 (*configs)[i].auxBuffers = 0;
	 (*configs)[i].level = 0;
	 /* leave remaining fields zero */
      }
      break;

   default:
      fprintf(stderr, "Unknown bpp in %s: %d\n", __FUNCTION__, 
	      dpy->bpp);
      exit(1);
      break;

   }   
   return 1;
}


/**
 * \brief Validate the fbdev mode.
 * 
 * \param dpy display handle.
 *
 * \return one on success, or zero on failure.
 *
 * Saves some registers and returns 1.
 *
 * \sa mgaValidateMode().
 */
static int mgaValidateMode( struct MiniGLXDisplayRec *dpy )
{
   return 1;
}


/**
 * \brief Examine mode returned by fbdev.
 * 
 * \param dpy display handle.
 *
 * \return one on success, or zero on failure.
 *
 * Restores registers that fbdev has clobbered and returns 1.
 *
 * \sa mgaValidateMode().
 */
static int mgaPostValidateMode( struct MiniGLXDisplayRec *dpy )
{
   return 1;
}


/**
 * \brief Initialize the framebuffer device mode
 *
 * \param dpy display handle.
 *
 * \return one on success, or zero on failure.
 *
 * Fills in \p info with some default values and some information from \p dpy
 * and then calls MGAScreenInit() for the screen initialization.
 * 
 * Before exiting clears the framebuffer memomry accessing it directly.
 */
static int mgaInitFBDev( struct MiniGLXDisplayRec *dpy )
{
   MGAPtr pMga = calloc(1, sizeof(*pMga));

   {
      int  dummy = dpy->shared.virtualWidth;

      switch (dpy->bpp / 8) {
      case 1: dummy = (dpy->shared.virtualWidth + 127) & ~127; break;
      case 2: dummy = (dpy->shared.virtualWidth +  31) &  ~31; break;
      case 3:
      case 4: dummy = (dpy->shared.virtualWidth +  15) &  ~15; break;
      }

      dpy->shared.virtualWidth = dummy;
   }

   dpy->driverInfo = (void *)pMga;
   
   pMga->agpMode       = MGA_DEFAULT_AGP_MODE;
   pMga->agpSize       = MGA_DEFAULT_AGP_SIZE;
  
   pMga->Chipset = dpy->chipset;

   pMga->IOAddress = dpy->FixedInfo.mmio_start;
   pMga->IOBase    = dpy->MMIOAddress;

   pMga->frontPitch = dpy->shared.virtualWidth * dpy->cpp;

   if (!MGAScreenInit( dpy, pMga ))
      return 0;

   return 1;
}


/**
 * \brief The screen is being closed, so clean up any state and free any
 * resources used by the DRI.
 *
 * \param dpy display handle.
 *
 * Unmaps the SAREA, closes the DRM device file descriptor and frees the driver
 * private data.
 */
static void mgaHaltFBDev( struct MiniGLXDisplayRec *dpy )
{
    drmUnmap( dpy->pSAREA, dpy->shared.SAREASize );
    drmClose(dpy->drmFD);

    if (dpy->driverInfo) {
       free(dpy->driverInfo);
       dpy->driverInfo = 0;
    }
}


/**
 * \brief A VT release or aquire signal has been received, and
 * requires some action.  We deal with loosing the VT by setting the
 * cliprects to zero and emitting an event to the application.  
 */
static int mgaVTSwitchHandler( struct MiniGLXDisplayRec *dpy, int have_vt )
{
   int *lock = (int *)dpy->pSAREA;
   int old, new;
   DRM_CAS_RESULT(ret);
   GLXDrawable draw;
   __DRIdrawable *pdraw;
   __DRIdrawablePrivate *pdp;

   /* Indicate cliprects have changed
    */
   draw = dpy->TheWindow;
   if (!draw) return 1;
   pdraw = &draw->driDrawable;
   if (!pdraw) return 1;
   pdp = (__DRIdrawablePrivate *) pdraw->private;
   if (!pdp) return 1;
   pdp->lastStamp++;
   pdp->numClipRects = have_vt ? 1 : 0;

   /* Mark the lock contended.
    */
   if (!dpy->pSAREA) return 0;
   do {
      old = *(int *)dpy->pSAREA;
      new = old | _DRM_LOCK_CONT;
      DRM_CAS( lock, old, new, ret );
      fprintf(stderr, "old %x new %x\n", old, new );
   } while (ret);

   if (have_vt)
      return !(old & _DRM_LOCK_HELD);
   else
      return 1;
}

/**
 * \brief Exported driver interface for Mini GLX.
 *
 * \sa MiniGLXDriverRec.
 */
struct MiniGLXDriverRec __driMiniGLXDriver = {
   mgaInitScreenConfigs,
   mgaValidateMode,
   mgaPostValidateMode,
   mgaInitFBDev,
   mgaHaltFBDev,
   mgaVTSwitchHandler
};




#if 0
void MGADRICloseScreen( ScreenPtr pScreen )
{
   ScrnInfoPtr pScrn = xf86Screens[pScreen->myNum];
   MGAPtr pMga = MGAPTR(pScrn);
   MGADRIServerPrivatePtr pMga = pMga->DRIServerInfo;
   drmMGAInit init;

   if ( pMga->drmBuffers ) {
      drmUnmapBufs( pMga->drmBuffers );
      pMga->drmBuffers = NULL;
   }

   if (pMga->irq) {
      drmCtlUninstHandler(dpy->drmFD);
      pMga->irq = 0;
   }

   /* Cleanup DMA */
   memset( &init, 0, sizeof(drmMGAInit) );
   init.func = MGA_CLEANUP_DMA;
   drmCommandWrite( dpy->drmFD, DRM_MGA_INIT, &init, sizeof(drmMGAInit) );

   if ( pMga->status.map ) {
      drmUnmap( pMga->status.map, pMga->status.size );
      pMga->status.map = NULL;
   }
   if ( pMga->buffers.map ) {
      drmUnmap( pMga->buffers.map, pMga->buffers.size );
      pMga->buffers.map = NULL;
   }
   if ( pMga->primary.map ) {
      drmUnmap( pMga->primary.map, pMga->primary.size );
      pMga->primary.map = NULL;
   }
   if ( pMga->warp.map ) {
      drmUnmap( pMga->warp.map, pMga->warp.size );
      pMga->warp.map = NULL;
   }

   if ( pMga->agpTextures.map ) {
      drmUnmap( pMga->agpTextures.map, pMga->agpTextures.size );
      pMga->agpTextures.map = NULL;
   }

   if ( pMga->agp.handle ) {
      drmAgpUnbind( dpy->drmFD, pMga->agp.handle );
      drmAgpFree( dpy->drmFD, pMga->agp.handle );
      pMga->agp.handle = 0;
      drmAgpRelease( dpy->drmFD );
   }

   DRICloseScreen( pScreen );

   if ( pMga->pDRIInfo ) {
      if ( pMga->pDRIpMga->devPrivate ) {
	 xfree( pMga->pDRIpMga->devPrivate );
	 pMga->pDRIpMga->devPrivate = 0;
      }
      DRIDestroyInfoRec( pMga->pDRIInfo );
      pMga->pDRIInfo = 0;
   }
   if ( pMga->DRIServerInfo ) {
      xfree( pMga->DRIServerInfo );
      pMga->DRIServerInfo = 0;
   }
   if ( pMga->pVisualConfigs ) {
      xfree( pMga->pVisualConfigs );
   }
   if ( pMga->pVisualConfigsPriv ) {
      xfree( pMga->pVisualConfigsPriv );
   }
}
#endif
