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

#include "xf86drm.h"		/* drmHandle, etc */

#define PCI_CHIP_RADEON_LW		0x4C57
#define PCI_CHIP_RADEON_LX		0x4C58
#define PCI_CHIP_RADEON_LY		0x4C59
#define PCI_CHIP_RADEON_LZ		0x4C5A
#define PCI_CHIP_RV250_Ld		0x4C64
#define PCI_CHIP_RV250_Le		0x4C65
#define PCI_CHIP_RV250_Lf		0x4C66
#define PCI_CHIP_RV250_Lg		0x4C67
#define PCI_CHIP_R300_ND		0x4E44
#define PCI_CHIP_R300_NE		0x4E45
#define PCI_CHIP_R300_NF		0x4E46
#define PCI_CHIP_R300_NG		0x4E47
#define PCI_CHIP_RADEON_QD		0x5144
#define PCI_CHIP_RADEON_QE		0x5145
#define PCI_CHIP_RADEON_QF		0x5146
#define PCI_CHIP_RADEON_QG		0x5147
#define PCI_CHIP_R200_QL		0x514C
#define PCI_CHIP_R200_QN		0x514E
#define PCI_CHIP_R200_QO		0x514F
#define PCI_CHIP_RV200_QW		0x5157
#define PCI_CHIP_RV200_QX		0x5158
#define PCI_CHIP_RADEON_QY		0x5159
#define PCI_CHIP_RADEON_QZ		0x515A
#define PCI_CHIP_R200_Ql		0x516C


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

typedef unsigned long memType;


typedef struct {
   int               Chipset;
   RADEONChipFamily  ChipFamily;

   unsigned long     LinearAddr;       /* Frame buffer physical address     */
   unsigned long     MMIOAddr;         /* MMIO region physical address      */
   unsigned long     BIOSAddr;         /* BIOS physical address             */

   unsigned char     *MMIO;            /* Map of MMIO region                */
   unsigned char     *FB;              /* Map of frame buffer               */


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

   int               drmMinor;

   int               frontOffset;
   int               frontPitch;
   int               backOffset;
   int               backPitch;
   int               depthOffset;
   int               depthPitch;
   int               textureOffset;
   int               textureSize;
   int               log2TexGran;

   unsigned int            frontPitchOffset;
   unsigned int            backPitchOffset;
   unsigned int            depthPitchOffset;

   unsigned int            dst_pitch_offset;

   int               irq;
   unsigned int            gen_int_cntl;

} RADEONInfoRec, *RADEONInfoPtr;


#endif /* _RADEON_H_ */
