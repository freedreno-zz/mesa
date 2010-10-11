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

#include "droid.h"

static _EGLImage *
droid_create_image_android_native_buffer(_EGLDisplay *disp,
                                        EGLClientBuffer buffer)
{
   struct droid_egl_display *ddpy = droid_egl_display(disp);
   struct android_native_buffer_t *buf =
      (struct android_native_buffer_t *) buffer;
   struct droid_egl_image *dimg;
   EGLint format, name;

   if (!buf || buf->common.magic != ANDROID_NATIVE_BUFFER_MAGIC ||
       buf->common.version != sizeof(*buf)) {
      _eglError(EGL_BAD_PARAMETER, "eglCreateEGLImageKHR");
      return NULL;
   }

   name = get_native_buffer_name(buf);
   if (!name) {
      _eglError(EGL_BAD_PARAMETER, "eglCreateEGLImageKHR");
      return NULL;
   }

   switch (buf->format) {
   case HAL_PIXEL_FORMAT_BGRA_8888:
      format = __DRI_IMAGE_FORMAT_ARGB8888;
      break;
   case HAL_PIXEL_FORMAT_RGB_565:
      format = __DRI_IMAGE_FORMAT_RGB565;
      break;
   case HAL_PIXEL_FORMAT_RGBA_8888:
   case HAL_PIXEL_FORMAT_RGBX_8888:
   case HAL_PIXEL_FORMAT_RGB_888:
   case HAL_PIXEL_FORMAT_RGBA_5551:
   case HAL_PIXEL_FORMAT_RGBA_4444:
      /* unsupported */
   default:
      _eglLog(_EGL_WARNING, "unsupported native buffer format 0x%x", buf->format);
      return NULL;
      break;
   }

   dimg = calloc(1, sizeof(*dimg));
   if (!dimg) {
      _eglError(EGL_BAD_ALLOC, "droid_create_image_mesa_drm");
      return NULL;
   }

   if (!_eglInitImage(&dimg->base, disp)) {
      free(dimg);
      return NULL;
   }

   dimg->dri_image =
      ddpy->image->createImageFromName(ddpy->dri_screen,
					   buf->width,
					   buf->height,
					   format,
					   name,
					   buf->stride,
					   dimg);
   if (!dimg->dri_image) {
      free(dimg);
      _eglError(EGL_BAD_ALLOC, "droid_create_image_mesa_drm");
      return NULL;
   }

   return &dimg->base;
}

static _EGLImage *
droid_create_image_khr(_EGLDriver *drv, _EGLDisplay *disp,
		      _EGLContext *ctx, EGLenum target,
		      EGLClientBuffer buffer, const EGLint *attr_list)
{
   switch (target) {
   case EGL_NATIVE_BUFFER_ANDROID:
      return droid_create_image_android_native_buffer(disp, buffer);
   default:
      _eglError(EGL_BAD_PARAMETER, "droid_create_image_khr");
      return EGL_NO_IMAGE_KHR;
   }
}

static EGLBoolean
droid_destroy_image_khr(_EGLDriver *drv, _EGLDisplay *disp, _EGLImage *image)
{
   struct droid_egl_display *ddpy = droid_egl_display(disp);
   struct droid_egl_image *dimg = droid_egl_image(image);

   ddpy->image->destroyImage(dimg->dri_image);
   free(dimg);

   return EGL_TRUE;
}

void
droid_init_image_functions(_EGLDriver *drv)
{
   struct droid_egl_driver *ddrv = droid_egl_driver(drv);

   ddrv->base.API.CreateImageKHR = droid_create_image_khr;
   ddrv->base.API.DestroyImageKHR = droid_destroy_image_khr;
}
