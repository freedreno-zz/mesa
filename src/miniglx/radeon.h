/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/ati/radeon.h,v 1.29 2002/10/12 01:38:07 martin Exp $ */
/*
 * Copyright 2000 ATI Technologies Inc., Markham, Ontario, and
 *                VA Linux Systems Inc., Fremont, California.
 *
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation on the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON-INFRINGEMENT.  IN NO EVENT SHALL ATI, VA LINUX SYSTEMS AND/OR
 * THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef _RADEON_H_
#define _RADEON_H_

#include "dri.h"

typedef enum {
    CHIP_FAMILY_UNKNOW,
    CHIP_FAMILY_LEGACY,
    CHIP_FAMILY_R128,
    CHIP_FAMILY_M3,
    CHIP_FAMILY_RADEON,
    CHIP_FAMILY_VE,
    CHIP_FAMILY_M6,
    CHIP_FAMILY_RV200,
    CHIP_FAMILY_M7,
    CHIP_FAMILY_R200,
    CHIP_FAMILY_RV250,
    CHIP_FAMILY_M9,
    CHIP_FAMILY_R300
} RADEONChipFamily;

typedef struct {
    RADEONChipFamily  ChipFamily;

    Bool              FBDev;

    unsigned long     LinearAddr;       /* Frame buffer physical address     */
    unsigned long     MMIOAddr;         /* MMIO region physical address      */
    unsigned long     BIOSAddr;         /* BIOS physical address             */

    unsigned char     *MMIO;            /* Map of MMIO region                */
    unsigned char     *FB;              /* Map of frame buffer               */
    CARD8             *VBIOS;           /* Video BIOS pointer                */



    Bool              directRenderingEnabled;
    DRIInfoPtr        pDRIInfo;
    int               drmFD;

    drmHandle         fbHandle;

    drmSize           registerSize;
    drmHandle         registerHandle;

    drmSize           agpSize;
    drmHandle         agpMemHandle;     /* Handle from drmAgpAlloc */
    unsigned long     agpOffset;
    unsigned char     *AGP;             /* Map */
    int               agpMode;
    int               agpFastWrite;

   /* CP ring buffer data */
    unsigned long     ringStart;        /* Offset into AGP space */
    drmHandle         ringHandle;       /* Handle from drmAddMap */
    drmSize           ringMapSize;      /* Size of map */
    int               ringSize;         /* Size of ring (in MB) */
    unsigned char     *ring;            /* Map */
    int               ringSizeLog2QW;

    unsigned long     ringReadOffset;   /* Offset into AGP space */
    drmHandle         ringReadPtrHandle; /* Handle from drmAddMap */
    drmSize           ringReadMapSize;  /* Size of map */
    unsigned char     *ringReadPtr;     /* Map */

   /* CP vertex/indirect buffer data */
    unsigned long     bufStart;         /* Offset into AGP space */
    drmHandle         bufHandle;        /* Handle from drmAddMap */
    drmSize           bufMapSize;       /* Size of map */
    int               bufSize;          /* Size of buffers (in MB) */
    unsigned char     *buf;             /* Map */
    int               bufNumBufs;       /* Number of buffers */
    drmBufMapPtr      buffers;          /* Buffer map */

   /* CP AGP Texture data */
    unsigned long     agpTexStart;      /* Offset into AGP space */
    drmHandle         agpTexHandle;     /* Handle from drmAddMap */
    drmSize           agpTexMapSize;    /* Size of map */
    int               agpTexSize;       /* Size of AGP tex space (in MB) */
    unsigned char     *agpTex;          /* Map */
    int               log2AGPTexGran;


    int               frontOffset;
    int               frontPitch;
    int               backOffset;
    int               backPitch;
    int               depthOffset;
    int               depthPitch;
    int               textureOffset;
    int               textureSize;
    int               log2TexGran;

    CARD32            frontPitchOffset;
    CARD32            backPitchOffset;
    CARD32            depthPitchOffset;

    CARD32            dst_pitch_offset;

    int               irq;
    CARD32            gen_int_cntl;

} RADEONInfoRec, *RADEONInfoPtr;

extern Bool        RADEONDRIScreenInit(ScreenPtr pScreen);
extern void        RADEONDRICloseScreen(ScreenPtr pScreen);
extern Bool        RADEONDRIFinishScreenInit(ScreenPtr pScreen);


#endif /* XF86DRI */

#endif /* _RADEON_H_ */
