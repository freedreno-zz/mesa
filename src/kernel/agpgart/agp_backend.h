/**
 * \file agp_backend.h
 * AGPGART module backend
 * \version 0.99
 * 
 * \author Jeff Hartmann
 */

/*
 * Copyright (C) 1999 Jeff Hartmann
 * Copyright (C) 1999 Precision Insight, Inc.
 * Copyright (C) 1999 Xi Graphics, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * JEFF HARTMANN, OR ANY OTHER CONTRIBUTORS BE LIABLE FOR ANY CLAIM, 
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR 
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef _AGP_BACKEND_H
#define _AGP_BACKEND_H 1

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define AGPGART_VERSION_MAJOR 0
#define AGPGART_VERSION_MINOR 99

/** Supported chipset types */
enum chipset_type {
	NOT_SUPPORTED,
	INTEL_GENERIC,
	INTEL_LX,
	INTEL_BX,
	INTEL_GX,
	INTEL_I810,
	INTEL_I815,
	INTEL_I820,
	INTEL_I830_M,
	INTEL_I845_G,
	INTEL_I840,
	INTEL_I845,
	INTEL_I850,
	INTEL_I860,
	INTEL_460GX,
	VIA_GENERIC,
	VIA_VP3,
	VIA_MVP3,
	VIA_MVP4,
	VIA_APOLLO_PRO,
	VIA_APOLLO_KX133,
	VIA_APOLLO_KT133,
	SIS_GENERIC,
	AMD_GENERIC,
	AMD_IRONGATE,
	AMD_761,
	AMD_762,
	AMD_8151,
	ALI_M1541,
	ALI_M1621,
	ALI_M1631,
	ALI_M1632,
	ALI_M1641,
	ALI_M1644,
	ALI_M1647,
	ALI_M1651,
	ALI_M1671,
	ALI_GENERIC,
	SVWRKS_HE,
	SVWRKS_LE,
	SVWRKS_GENERIC,
	HP_ZX1,
};

struct agp_version {
	u16 major;
	u16 minor;
};

typedef struct _agp_kern_info {
	struct agp_version version;
	struct pci_dev *device;
	enum chipset_type chipset;
	unsigned long mode;
	off_t aper_base;
	size_t aper_size;
	int max_memory;		/**< In pages */
	int current_memory;
	int cant_use_aperture;
	unsigned long page_mask;
} agp_kern_info;

/**
 * The agp_memory structure has information
 * about the block of agp memory allocated.
 * A caller may manipulate the next and prev
 * pointers to link each allocated item into
 * a list.  These pointers are ignored by the 
 * backend.  Everything else should never be
 * written to, but the caller may read any of
 * the items to detrimine the status of this
 * block of agp memory.
 */
typedef struct _agp_memory {
	int key;	/** hash key */
	struct _agp_memory *next;
	struct _agp_memory *prev;
	size_t page_count;
	int num_scratch_pages;
	unsigned long *memory;
	off_t pg_start;
	u32 type;
	u32 physical;
	u8 is_bound;
	u8 is_flushed;
} agp_memory;

#define AGP_NORMAL_MEMORY 0

extern void agp_free_memory(agp_memory *);
extern agp_memory *agp_allocate_memory(size_t, u32);
extern int agp_copy_info(agp_kern_info *);
extern int agp_bind_memory(agp_memory *, off_t);
extern int agp_unbind_memory(agp_memory *);
extern void agp_enable(u32);
extern int agp_backend_acquire(void);

extern void agp_backend_release(void);


/**
 * Interface between DRM and AGP code.  When AGP initializes, it makes
 * this structure available via inter_module_register(), DRM might
 * use it.
 * 
 * \author Keith Owens <kaos@ocs.com.au> 
 * \date 28 Oct 2000.
 */
typedef struct {
	void       (*free_memory)(agp_memory *);
	agp_memory *(*allocate_memory)(size_t, u32);
	int        (*bind_memory)(agp_memory *, off_t);
	int        (*unbind_memory)(agp_memory *);
	void       (*enable)(u32);
	int        (*acquire)(void);
	void       (*release)(void);
	int        (*copy_info)(agp_kern_info *);
} drm_agp_t;

extern const drm_agp_t *drm_agp_p;

#endif				/* _AGP_BACKEND_H */
