/*
 * Copyright (C) 2009 Chia-I Wu <olvaffe@gmail.com>
 *
 * This is based on the work of eagle, by
 * Copyright © 2008, 2009 Kristian Høgsberg
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef _DROID_H_
#define _DROID_H_

#include "GL/gl.h"
#include "GL/internal/dri_interface.h"

#include "eglcurrent.h"
#include "egldisplay.h"
#include "eglcontext.h"
#include "eglsurface.h"
#include "eglconfig.h"

/* opaque types */
struct droid_loader;
struct droid_context;
struct droid_drawable;
struct droid_image;
struct droid_surface;

struct droid_backend {
   /* these are usually used by a loader */
   const char *driver_name;
   int (*initialize)(struct droid_backend *backend, int *fd, int *screen_number);
   int (*process_config)(struct droid_backend *backend, _EGLConfig *conf);
   void (*destroy)(struct droid_backend *backend);

   __DRIbuffer *(*get_native_buffer)(struct droid_backend *backend,
                                     struct droid_surface *surf,
                                     int *width, int *height);
   __DRIbuffer *(*get_surface_buffers)(struct droid_backend *backend,
                                       struct droid_surface *surf,
                                       int *width, int *height,
                                       unsigned int *attachments, int count,
                                       int *out_count, int has_format);

   /* public methods */
   struct droid_surface *(*create_window_surface)(struct droid_backend *backend,
                                                  _EGLSurface *surf,
                                                  NativeWindowType win);
   struct droid_surface *(*create_image_surface)(struct droid_backend *backend,
                                                 NativePixmapType pix);
   void (*destroy_surface)(struct droid_backend *backend, struct droid_surface *surf);
   void (*swap_native_buffers)(struct droid_backend *backend,
                               struct droid_surface *surf);

   int (*match_pixmap)(struct droid_backend *backend, _EGLConfig *conf,
                       NativePixmapType pix);
};

struct droid_screen {
   struct droid_loader *loader;

   __DRIscreen *dri_screen;
   __DRItexBufferExtension *tex_buffer;
   __DRIcopyBufferExtension *copy_buffer;

   const __DRIconfig **dri_configs;
   int num_dri_configs;
};

struct droid_backend *
droid_backend_create_intel(const char *dev);

void
droid_backend_destroy(struct droid_backend *backend);

struct droid_screen *
droid_screen_create(struct droid_backend *backend);

void
droid_screen_destroy(struct droid_screen *screen);

int
droid_screen_convert_config(struct droid_screen *screen,
                            const __DRIconfig *conf, _EGLConfig *egl_conf);

struct droid_context *
droid_screen_create_context(struct droid_screen *screen,
                            const __DRIconfig *conf,
                            struct droid_context *shared);

void
droid_screen_destroy_context(struct droid_screen *screen,
                             struct droid_context *ctx);

struct droid_drawable *
droid_screen_create_drawable(struct droid_screen *screen,
                             const __DRIconfig *conf,
                             struct droid_surface *surf);

void *
droid_screen_get_drawable_data(struct droid_screen *screen,
                               struct droid_drawable *drawable);

void
droid_screen_destroy_drawable(struct droid_screen *screen,
                              struct droid_drawable *drawable);

int
droid_screen_bind_context(struct droid_screen *screen,
                          struct droid_drawable *draw,
                          struct droid_drawable *read,
                          struct droid_context *ctx);

int
droid_screen_swap_buffers(struct droid_screen *screen,
                          struct droid_context *ctx,
                          struct droid_drawable *drawable);

#endif /* _DROID_H_ */
