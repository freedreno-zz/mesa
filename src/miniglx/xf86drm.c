/* xf86drm.c -- User-level interface to DRM device
 * Created: Tue Jan  5 08:16:21 1999 by faith@precisioninsight.com
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, California.
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
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors: Rickard E. (Rik) Faith <faith@valinux.com>
 *	    Kevin E. Martin <martin@valinux.com>
 *
 * $XFree86: xc/programs/Xserver/hw/xfree86/os-support/linux/drm/xf86drm.c,v 1.28 2002/10/16 01:26:49 dawes Exp $
 *
 */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# define stat_t struct stat
# include <sys/ioctl.h>
# include <sys/mman.h>
# include <sys/time.h>
# include <stdarg.h>
# define _DRM_MALLOC malloc
# define _DRM_FREE   free
# include "drm.h"

/* Not all systems have MAP_FAILED defined */
#ifndef MAP_FAILED
#define MAP_FAILED ((void *)-1)
#endif

#include "xf86drm.h"

#ifndef DRM_MAJOR
#define DRM_MAJOR 226		/* Linux */
#endif

#ifndef __linux__
#undef  DRM_MAJOR
#define DRM_MAJOR 145		/* Should set in drm.h for *BSD */
#endif

#ifndef DRM_MAX_MINOR
#define DRM_MAX_MINOR 16
#endif

#ifdef __linux__
#include <sys/sysmacros.h>	/* for makedev() */
#endif

#ifndef makedev
				/* This definition needs to be changed on
                                   some systems if dev_t is a structure.
                                   If there is a header file we can get it
                                   from, there would be best. */
#define makedev(x,y)    ((dev_t)(((x) << 8) | (y)))
#endif

#define DRM_MSG_VERBOSITY 3

static void
drmMsg(const char *format, ...)
{
    va_list	ap;

    const char *env;
    if ((env = getenv("LIBGL_DEBUG")) && strstr(env, "verbose"))
    {
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
    }
}

#define drmMalloc malloc
#define drmFree free
#define drmStrdup strdup

static unsigned long drmGetKeyFromFd(int fd)
{
    stat_t     st;

    st.st_rdev = 0;
    fstat(fd, &st);
    return st.st_rdev;
}


static int drmOpenDevice(long dev, int minor)
{
    stat_t          st;
    char            buf[64];
    int             fd;
    mode_t          devmode = DRM_DEV_MODE;
    int             isroot  = !geteuid();
#if defined(XFree86Server)
    uid_t           user    = DRM_DEV_UID;
    gid_t           group   = DRM_DEV_GID;
#endif

    drmMsg("drmOpenDevice: minor is %d\n", minor);

#if defined(XFree86Server)
    devmode  = xf86ConfigDRI.mode ? xf86ConfigDRI.mode : DRM_DEV_MODE;
    devmode &= ~(S_IXUSR|S_IXGRP|S_IXOTH);
    group = (xf86ConfigDRI.group >= 0) ? xf86ConfigDRI.group : DRM_DEV_GID;
#endif

    if (stat(DRM_DIR_NAME, &st)) {
	if (!isroot) return DRM_ERR_NOT_ROOT;
	mkdir(DRM_DIR_NAME, DRM_DEV_DIRMODE);
	chown(DRM_DIR_NAME, 0, 0); /* root:root */
	chmod(DRM_DIR_NAME, DRM_DEV_DIRMODE);
    }

    sprintf(buf, DRM_DEV_NAME, DRM_DIR_NAME, minor);
    drmMsg("drmOpenDevice: node name is %s\n", buf);
    if (stat(buf, &st)) {
	if (!isroot) return DRM_ERR_NOT_ROOT;
	remove(buf);
	mknod(buf, S_IFCHR | devmode, dev);
    }
#if defined(XFree86Server)
    chown(buf, user, group);
    chmod(buf, devmode);
#endif

    fd = open(buf, O_RDWR, 0);
    drmMsg("drmOpenDevice: open result is %d, (%s)\n",
		fd, fd < 0 ? strerror(errno) : "OK");
    if (fd >= 0) return fd;

    if (st.st_rdev != dev) {
	if (!isroot) return DRM_ERR_NOT_ROOT;
	remove(buf);
	mknod(buf, S_IFCHR | devmode, dev);
    }
    fd = open(buf, O_RDWR, 0);
    drmMsg("drmOpenDevice: open result is %d, (%s)\n",
		fd, fd < 0 ? strerror(errno) : "OK");

    drmMsg("drmOpenDevice: Open failed\n");
    remove(buf);
    return -errno;
}

static int drmOpenMinor(int minor, int create)
{
    int  fd;
    char buf[64];
    
    if (create) return drmOpenDevice(makedev(DRM_MAJOR, minor), minor);
    
    sprintf(buf, DRM_DEV_NAME, DRM_DIR_NAME, minor);
    if ((fd = open(buf, O_RDWR, 0)) >= 0) return fd;
    return -errno;
}

/* drmAvailable looks for (DRM_MAJOR, 0) and returns 1 if it returns
   information for DRM_IOCTL_VERSION.  For backward compatibility with
   older Linux implementations, /proc/dri is also checked. */

int drmAvailable(void)
{
    drmVersionPtr version;
    int           retval = 0;
    int           fd;

    if ((fd = drmOpenMinor(0, 1)) < 0) {
				/* Try proc for backward Linux compatibility */
	if (!access("/proc/dri/0", R_OK)) return 1;
	return 0;
    }
    
    if ((version = drmGetVersion(fd))) {
	retval = 1;
	drmFreeVersion(version);
    }
    close(fd);

    return retval;
}

static int drmOpenByBusid(const char *busid)
{
    int        i;
    int        fd;
    const char *buf;
    
    drmMsg("drmOpenByBusid: busid is %s\n", busid);
    for (i = 0; i < DRM_MAX_MINOR; i++) {
	fd = drmOpenMinor(i, 1);
	drmMsg("drmOpenByBusid: drmOpenMinor returns %d\n", fd);
	if (fd >= 0) {
	    buf = drmGetBusid(fd);
	    drmMsg("drmOpenByBusid: drmGetBusid reports %s\n", buf);
	    if (buf && !strcmp(buf, busid)) {
		drmFreeBusid(buf);
		return fd;
	    }
	    if (buf) drmFreeBusid(buf);
	    close(fd);
	}
    }
    return -1;
}

static int drmOpenByName(const char *name)
{
    int           i;
    int           fd;
    drmVersionPtr version;
    char *        id;
    
    if (!drmAvailable()) {
#if !defined(XFree86Server)
	return -1;
#else
        /* try to load the kernel module now */
        if (!xf86LoadKernelModule(name)) {
            ErrorF("[drm] failed to load kernel module \"%s\"\n",
		   name);
            return -1;
        }
#endif
    }

    /*
     * Open the first minor number that matches the driver name and isn't
     * already in use.  If it's in use it will have a busid assigned already.
     */
    for (i = 0; i < DRM_MAX_MINOR; i++) {
	if ((fd = drmOpenMinor(i, 1)) >= 0) {
	    if ((version = drmGetVersion(fd))) {
		if (!strcmp(version->name, name)) {
		    drmFreeVersion(version);
		    id = drmGetBusid(fd);
		    drmMsg("drmGetBusid returned '%s'\n", id ? id : "NULL");
		    if (!id || !*id) {
			if (id) {
			    drmFreeBusid(id);
			}
			return fd;
		    } else {
			drmFreeBusid(id);
		    }
		} else {
		    drmFreeVersion(version);
		}
	    }
	    close(fd);
	}
    }

#ifdef __linux__
				/* Backward-compatibility /proc support */
    for (i = 0; i < 8; i++) {
	char proc_name[64], buf[512];
	char *driver, *pt, *devstring;
	int  retcode;
	
	sprintf(proc_name, "/proc/dri/%d/name", i);
	if ((fd = open(proc_name, 0, 0)) >= 0) {
	    retcode = read(fd, buf, sizeof(buf)-1);
	    close(fd);
	    if (retcode) {
		buf[retcode-1] = '\0';
		for (driver = pt = buf; *pt && *pt != ' '; ++pt)
		    ;
		if (*pt) {	/* Device is next */
		    *pt = '\0';
		    if (!strcmp(driver, name)) { /* Match */
			for (devstring = ++pt; *pt && *pt != ' '; ++pt)
			    ;
			if (*pt) { /* Found busid */
			    return drmOpenByBusid(++pt);
			} else {	/* No busid */
			    return drmOpenDevice(strtol(devstring, NULL, 0),i);
			}
		    }
		}
	    }
	}
    }
#endif

    return -1;
}

/* drmOpen looks up the specified name and busid, and opens the device
   found.  The entry in /dev/dri is created if necessary (and if root).
   A file descriptor is returned.  On error, the return value is
   negative. */

int drmOpen(const char *name, const char *busid)
{

    if (busid) return drmOpenByBusid(busid);
    return drmOpenByName(name);
}

void drmFreeVersion(drmVersionPtr v)
{
    if (!v) return;
    if (v->name) drmFree(v->name);
    if (v->date) drmFree(v->date);
    if (v->desc) drmFree(v->desc);
    drmFree(v);
}

static void drmFreeKernelVersion(drm_version_t *v)
{
    if (!v) return;
    if (v->name) drmFree(v->name);
    if (v->date) drmFree(v->date);
    if (v->desc) drmFree(v->desc);
    drmFree(v);
}

static void drmCopyVersion(drmVersionPtr d, const drm_version_t *s)
{
    d->version_major      = s->version_major;
    d->version_minor      = s->version_minor;
    d->version_patchlevel = s->version_patchlevel;
    d->name_len           = s->name_len;
    d->name               = drmStrdup(s->name);
    d->date_len           = s->date_len;
    d->date               = drmStrdup(s->date);
    d->desc_len           = s->desc_len;
    d->desc               = drmStrdup(s->desc);
}

/* drmGet Version obtains the driver version information via an ioctl.  Similar
 * information is available via /proc/dri. */

drmVersionPtr drmGetVersion(int fd)
{
    drmVersionPtr retval;
    drm_version_t *version = drmMalloc(sizeof(*version));

				/* First, get the lengths */
    version->name_len    = 0;
    version->name        = NULL;
    version->date_len    = 0;
    version->date        = NULL;
    version->desc_len    = 0;
    version->desc        = NULL;

    if (ioctl(fd, DRM_IOCTL_VERSION, version)) {
	drmFreeKernelVersion(version);
	return NULL;
    }

				/* Now, allocate space and get the data */
    if (version->name_len)
	version->name    = drmMalloc(version->name_len + 1);
    if (version->date_len)
	version->date    = drmMalloc(version->date_len + 1);
    if (version->desc_len)
	version->desc    = drmMalloc(version->desc_len + 1);

    if (ioctl(fd, DRM_IOCTL_VERSION, version)) {
	drmFreeKernelVersion(version);
	return NULL;
    }

				/* The results might not be null-terminated
                                   strings, so terminate them. */

    if (version->name_len) version->name[version->name_len] = '\0';
    if (version->date_len) version->date[version->date_len] = '\0';
    if (version->desc_len) version->desc[version->desc_len] = '\0';

				/* Now, copy it all back into the
                                   client-visible data structure... */
    retval = drmMalloc(sizeof(*retval));
    drmCopyVersion(retval, version);
    drmFreeKernelVersion(version);
    return retval;
}

/* drmGetLibVersion set version information for the drm user space library.
 * this version number is driver indepedent */

drmVersionPtr drmGetLibVersion(int fd)
{
    drm_version_t *version = drmMalloc(sizeof(*version));

    /* Version history:
     *   revision 1.0.x = original DRM interface with no drmGetLibVersion
     *                    entry point and many drm<Device> extensions
     *   revision 1.1.x = added drmCommand entry points for device extensions
     *                    added drmGetLibVersion to identify libdrm.a version
     */
    version->version_major      = 1;
    version->version_minor      = 1;
    version->version_patchlevel = 0;

    return (drmVersionPtr)version;
}

void drmFreeBusid(const char *busid)
{
    drmFree((void *)busid);
}

char *drmGetBusid(int fd)
{
    drm_unique_t u;

    u.unique_len = 0;
    u.unique     = NULL;

    if (ioctl(fd, DRM_IOCTL_GET_UNIQUE, &u)) return NULL;
    u.unique = drmMalloc(u.unique_len + 1);
    if (ioctl(fd, DRM_IOCTL_GET_UNIQUE, &u)) return NULL;
    u.unique[u.unique_len] = '\0';
    return u.unique;
}

int drmSetBusid(int fd, const char *busid)
{
    drm_unique_t u;

    u.unique     = (char *)busid;
    u.unique_len = strlen(busid);

    if (ioctl(fd, DRM_IOCTL_SET_UNIQUE, &u)) {
	return -errno;
    }
    return 0;
}

int drmGetMagic(int fd, drmMagicPtr magic)
{
    drm_auth_t auth;

    *magic = 0;
    if (ioctl(fd, DRM_IOCTL_GET_MAGIC, &auth)) return -errno;
    *magic = auth.magic;
    return 0;
}

int drmAuthMagic(int fd, drmMagic magic)
{
    drm_auth_t auth;

    auth.magic = magic;
    if (ioctl(fd, DRM_IOCTL_AUTH_MAGIC, &auth)) return -errno;
    return 0;
}

int drmAddMap(int fd,
	      drmHandle offset,
	      drmSize size,
	      drmMapType type,
	      drmMapFlags flags,
	      drmHandlePtr handle)
{
    drm_map_t map;

    map.offset  = offset;
/* No longer needed with CVS kernel modules on alpha
#ifdef __alpha__
    if (type != DRM_SHM)
	map.offset += BUS_BASE;
#endif
*/
    map.size    = size;
    map.handle  = 0;
    map.type    = type;
    map.flags   = flags;
    if (ioctl(fd, DRM_IOCTL_ADD_MAP, &map)) return -errno;
    if (handle) *handle = (drmHandle)map.handle;
    return 0;
}

int drmAddBufs(int fd, int count, int size, drmBufDescFlags flags,
	       int agp_offset)
{
    drm_buf_desc_t request;

    request.count     = count;
    request.size      = size;
    request.low_mark  = 0;
    request.high_mark = 0;
    request.flags     = flags;
    request.agp_start = agp_offset;

    if (ioctl(fd, DRM_IOCTL_ADD_BUFS, &request)) return -errno;
    return request.count;
}


int drmFreeBufs(int fd, int count, int *list)
{
    drm_buf_free_t request;

    request.count = count;
    request.list  = list;
    if (ioctl(fd, DRM_IOCTL_FREE_BUFS, &request)) return -errno;
    return 0;
}

int drmClose(int fd)
{
#if 0
    unsigned long key    = drmGetKeyFromFd(fd);
    drmHashEntry  *entry = drmGetEntry(fd);

    drmHashDestroy(entry->tagTable);
    entry->fd       = 0;
    entry->f        = NULL;
    entry->tagTable = NULL;

    drmHashDelete(drmHashTable, key);
    drmFree(entry);
#endif

    return close(fd);
}

int drmMap(int fd,
	   drmHandle handle,
	   drmSize size,
	   drmAddressPtr address)
{
    static unsigned long pagesize_mask = 0;

    if (fd < 0) return -EINVAL;

    if (!pagesize_mask)
	pagesize_mask = getpagesize() - 1;

    size = (size + pagesize_mask) & ~pagesize_mask;

    *address = mmap(0, size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, handle);
    if (*address == MAP_FAILED) return -errno;
    return 0;
}

int drmUnmap(drmAddress address, drmSize size)
{
    return munmap(address, size);
}


drmBufMapPtr drmMapBufs(int fd)
{
    drm_buf_map_t bufs;
    drmBufMapPtr  retval;
    int           i;

    bufs.count = 0;
    bufs.list  = NULL;
    if (ioctl(fd, DRM_IOCTL_MAP_BUFS, &bufs)) return NULL;

    if (bufs.count) {
	if (!(bufs.list = drmMalloc(bufs.count * sizeof(*bufs.list))))
	    return NULL;

	if (ioctl(fd, DRM_IOCTL_MAP_BUFS, &bufs)) {
	    drmFree(bufs.list);
	    return NULL;
	}
				/* Now, copy it all back into the
                                   client-visible data structure... */
	retval = drmMalloc(sizeof(*retval));
	retval->count = bufs.count;
	retval->list  = drmMalloc(bufs.count * sizeof(*retval->list));
	for (i = 0; i < bufs.count; i++) {
	    retval->list[i].idx     = bufs.list[i].idx;
	    retval->list[i].total   = bufs.list[i].total;
	    retval->list[i].used    = 0;
	    retval->list[i].address = bufs.list[i].address;
	}
	return retval;
    }
    return NULL;
}

int drmUnmapBufs(drmBufMapPtr bufs)
{
    int i;

    for (i = 0; i < bufs->count; i++) {
	munmap(bufs->list[i].address, bufs->list[i].total);
    }
    return 0;
}

#define DRM_DMA_RETRY		16

int drmDMA(int fd, drmDMAReqPtr request)
{
    drm_dma_t dma;
    int ret, i = 0;

				/* Copy to hidden structure */
    dma.context         = request->context;
    dma.send_count      = request->send_count;
    dma.send_indices    = request->send_list;
    dma.send_sizes      = request->send_sizes;
    dma.flags           = request->flags;
    dma.request_count   = request->request_count;
    dma.request_size    = request->request_size;
    dma.request_indices = request->request_list;
    dma.request_sizes   = request->request_sizes;

    do {
	ret = ioctl( fd, DRM_IOCTL_DMA, &dma );
    } while ( ret && errno == EAGAIN && i++ < DRM_DMA_RETRY );

    if ( ret == 0 ) {
	request->granted_count = dma.granted_count;
	return 0;
    } else {
	return -errno;
    }
}

int drmGetLock(int fd, drmContext context, drmLockFlags flags)
{
    drm_lock_t lock;

    lock.context = context;
    lock.flags   = 0;
    if (flags & DRM_LOCK_READY)      lock.flags |= _DRM_LOCK_READY;
    if (flags & DRM_LOCK_QUIESCENT)  lock.flags |= _DRM_LOCK_QUIESCENT;
    if (flags & DRM_LOCK_FLUSH)      lock.flags |= _DRM_LOCK_FLUSH;
    if (flags & DRM_LOCK_FLUSH_ALL)  lock.flags |= _DRM_LOCK_FLUSH_ALL;
    if (flags & DRM_HALT_ALL_QUEUES) lock.flags |= _DRM_HALT_ALL_QUEUES;
    if (flags & DRM_HALT_CUR_QUEUES) lock.flags |= _DRM_HALT_CUR_QUEUES;

    while (ioctl(fd, DRM_IOCTL_LOCK, &lock))
	;
    return 0;
}

int drmUnlock(int fd, drmContext context)
{
    drm_lock_t lock;

    lock.context = context;
    lock.flags   = 0;
    return ioctl(fd, DRM_IOCTL_UNLOCK, &lock);
}

int drmCreateContext(int fd, drmContextPtr handle)
{
    drm_ctx_t ctx;

    ctx.flags = 0;	/* Modified with functions below */
    if (ioctl(fd, DRM_IOCTL_ADD_CTX, &ctx)) return -errno;
    *handle = ctx.handle;
    return 0;
}


int drmDestroyContext(int fd, drmContext handle)
{
    drm_ctx_t ctx;
    ctx.handle = handle;
    if (ioctl(fd, DRM_IOCTL_RM_CTX, &ctx)) return -errno;
    return 0;
}

int drmAgpAcquire(int fd)
{
    if (ioctl(fd, DRM_IOCTL_AGP_ACQUIRE, NULL)) return -errno;
    return 0;
}

int drmAgpRelease(int fd)
{
    if (ioctl(fd, DRM_IOCTL_AGP_RELEASE, NULL)) return -errno;
    return 0;
}

int drmAgpEnable(int fd, unsigned long mode)
{
    drm_agp_mode_t m;

    m.mode = mode;
    if (ioctl(fd, DRM_IOCTL_AGP_ENABLE, &m)) return -errno;
    return 0;
}

int drmAgpAlloc(int fd, unsigned long size, unsigned long type,
		unsigned long *address, unsigned long *handle)
{
    drm_agp_buffer_t b;
    *handle = 0;
    b.size   = size;
    b.handle = 0;
    b.type   = type;
    if (ioctl(fd, DRM_IOCTL_AGP_ALLOC, &b)) return -errno;
    if (address != 0UL) *address = b.physical;
    *handle = b.handle;
    return 0;
}

int drmAgpFree(int fd, unsigned long handle)
{
    drm_agp_buffer_t b;

    b.size   = 0;
    b.handle = handle;
    if (ioctl(fd, DRM_IOCTL_AGP_FREE, &b)) return -errno;
    return 0;
}

int drmAgpBind(int fd, unsigned long handle, unsigned long offset)
{
    drm_agp_binding_t b;

    b.handle = handle;
    b.offset = offset;
    if (ioctl(fd, DRM_IOCTL_AGP_BIND, &b)) return -errno;
    return 0;
}

int drmAgpUnbind(int fd, unsigned long handle)
{
    drm_agp_binding_t b;

    b.handle = handle;
    b.offset = 0;
    if (ioctl(fd, DRM_IOCTL_AGP_UNBIND, &b)) return -errno;
    return 0;
}

int drmAgpVersionMajor(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return -errno;
    return i.agp_version_major;
}

int drmAgpVersionMinor(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return -errno;
    return i.agp_version_minor;
}

unsigned long drmAgpGetMode(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.mode;
}

unsigned long drmAgpBase(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.aperture_base;
}

unsigned long drmAgpSize(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.aperture_size;
}

unsigned long drmAgpMemoryUsed(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.memory_used;
}

unsigned long drmAgpMemoryAvail(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.memory_allowed;
}

unsigned int drmAgpVendorId(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.id_vendor;
}

unsigned int drmAgpDeviceId(int fd)
{
    drm_agp_info_t i;

    if (ioctl(fd, DRM_IOCTL_AGP_INFO, &i)) return 0;
    return i.id_device;
}


int drmWaitVBlank(int fd, drmVBlankPtr vbl)
{
    int ret;

    do {
       ret = ioctl(fd, DRM_IOCTL_WAIT_VBLANK, vbl);
    } while (ret && errno == EINTR);

    return ret;
}


int drmCtlInstHandler(int fd, int irq)
{
    drm_control_t ctl;

    ctl.func  = DRM_INST_HANDLER;
    ctl.irq   = irq;
    if (ioctl(fd, DRM_IOCTL_CONTROL, &ctl)) return -errno;
    return 0;
}

int drmCtlUninstHandler(int fd)
{
    drm_control_t ctl;

    ctl.func  = DRM_UNINST_HANDLER;
    ctl.irq   = 0;
    if (ioctl(fd, DRM_IOCTL_CONTROL, &ctl)) return -errno;
    return 0;
}


int drmGetInterruptFromBusID(int fd, int busnum, int devnum, int funcnum)
{
    drm_irq_busid_t p;

    p.busnum  = busnum;
    p.devnum  = devnum;
    p.funcnum = funcnum;
    if (ioctl(fd, DRM_IOCTL_IRQ_BUSID, &p)) return -errno;
    return p.irq;
}

int drmGetMap(int fd, int idx, drmHandle *offset, drmSize *size,
	      drmMapType *type, drmMapFlags *flags, drmHandle *handle,
	      int *mtrr)
{
    drm_map_t map;

    map.offset = idx;
    if (ioctl(fd, DRM_IOCTL_GET_MAP, &map)) return -errno;
    *offset = map.offset;
    *size   = map.size;
    *type   = map.type;
    *flags  = map.flags;
    *handle = (unsigned long)map.handle;
    *mtrr   = map.mtrr;
    return 0;
}

int drmGetClient(int fd, int idx, int *auth, int *pid, int *uid,
		 unsigned long *magic, unsigned long *iocs)
{
    drm_client_t client;

    client.idx = idx;
    if (ioctl(fd, DRM_IOCTL_GET_CLIENT, &client)) return -errno;
    *auth      = client.auth;
    *pid       = client.pid;
    *uid       = client.uid;
    *magic     = client.magic;
    *iocs      = client.iocs;
    return 0;
}

int drmGetStats(int fd, drmStatsT *stats)
{
    stats->count = 0;
    memset(stats, 0, sizeof(*stats));
    return 0;
}

int drmCommandNone(int fd, unsigned long drmCommandIndex)
{
    void *data = NULL; /* dummy */
    unsigned long request;

    request = DRM_IO( DRM_COMMAND_BASE + drmCommandIndex);

    if (ioctl(fd, request, data)) {
	return -errno;
    }
    return 0;
}

int drmCommandRead(int fd, unsigned long drmCommandIndex,
                   void *data, unsigned long size )
{
    unsigned long request;

    request = DRM_IOC( DRM_IOC_READ, DRM_IOCTL_BASE, 
	DRM_COMMAND_BASE + drmCommandIndex, size);

    if (ioctl(fd, request, data)) {
	return -errno;
    }
    return 0;
}

int drmCommandWrite(int fd, unsigned long drmCommandIndex,
                   void *data, unsigned long size )
{
    unsigned long request;

    request = DRM_IOC( DRM_IOC_WRITE, DRM_IOCTL_BASE, 
	DRM_COMMAND_BASE + drmCommandIndex, size);

    if (ioctl(fd, request, data)) {
	return -errno;
    }
    return 0;
}

int drmCommandWriteRead(int fd, unsigned long drmCommandIndex,
                   void *data, unsigned long size )
{
    unsigned long request;

    request = DRM_IOC( DRM_IOC_READ|DRM_IOC_WRITE, DRM_IOCTL_BASE, 
	DRM_COMMAND_BASE + drmCommandIndex, size);

    if (ioctl(fd, request, data)) {
	return -errno;
    }
    return 0;
}

