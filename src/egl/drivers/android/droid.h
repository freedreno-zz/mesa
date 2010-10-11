/*
 * Copyright © 2010 Intel Corporation
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Kristian Høgsberg <krh@bitplanet.net>
 */

#ifndef  _DROID_H_
#define  _DROID_H_

#include <errno.h>

#include <ui/egl/android_natives.h>
#include <ui/android_native_buffer.h>
#include <pixelflinger/format.h>

#include <GL/gl.h>
#include <GL/internal/dri_interface.h>

#include "egldriver.h"
#include "egldisplay.h"
#include "eglcontext.h"
#include "eglsurface.h"
#include "eglconfig.h"
#include "eglimage.h"
#include "eglcurrent.h"
#include "egllog.h"

struct droid_egl_driver
{
   _EGLDriver base;

   void (*glFlush)(void);
   void (*glFinish)(void);
};

struct droid_egl_display
{
   int fd;

   __DRIscreen *dri_screen;
   const __DRIconfig **dri_configs;
   __DRIcoreExtension *core;
   __DRIdri2Extension *dri2;
   __DRI2flushExtension *flush;
   __DRIimageExtension *image;

   __DRIdri2LoaderExtension loader_extension;
   const __DRIextension *extensions[8];
};

struct droid_egl_context
{
   _EGLContext base;

   __DRIcontext *dri_context;
};

struct droid_egl_surface
{
   _EGLSurface base;

   __DRIdrawable *dri_drawable;
   __DRIbuffer dri_buffer;

   android_native_window_t *window;
   android_native_buffer_t *buffer;
};

struct droid_egl_config
{
   _EGLConfig base;

   const __DRIconfig *dri_config;
};

struct droid_egl_image
{
   _EGLImage base;

   __DRIimage *dri_image;
};

/* standard typecasts */
_EGL_DRIVER_STANDARD_TYPECASTS(droid_egl)
_EGL_DRIVER_TYPECAST(droid_egl_image, _EGLImage, obj)

_EGLDriver *
droid_create_driver(void);

void
droid_init_core_functions(_EGLDriver *drv);

void
droid_init_image_functions(_EGLDriver *drv);

EGLBoolean
droid_dequeue_buffer(struct droid_egl_surface *dsurf);

EGLBoolean
droid_enqueue_buffer(struct droid_egl_surface *dsurf);

int
get_native_buffer_name(struct android_native_buffer_t *buf);

#endif /* _DROID_H_ */
