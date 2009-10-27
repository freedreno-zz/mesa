/*
 * Copyright (C) 2009 Chia-I Wu <olvaffe@gmail.com>
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

#include <ui/PixelFormat.h>
#include <ui/ISurfaceComposer.h>

#include "droid_ui.h"

using namespace android;

namespace android {
   const sp<ISurfaceComposer>& _get_surface_manager();
};

int
ui_auth_gpu(drm_magic_t magic)
{
   /*
    * surface flinger itself or root; we might want something like
    * getSurfaceFlinger() from libEGL
    */
   if (getuid() == 1000 || getuid() == 0)
      return 0;

   sp<ISurfaceComposer> sm(_get_surface_manager());
   if (sm == NULL)
      return -ENODEV;
   return sm->authGPU(magic);
}

int ui_bytes_per_pixel(int format)
{
   return bytesPerPixel(format);
}

int ui_get_rgb_format(int red, int green, int blue, int alpha)
{
   PixelFormatInfo info;
   PixelFormat fmt;

   /* look in the RGB range */
   for (fmt = 1; fmt < PIXEL_FORMAT_YCbCr_422_SP; fmt++) {
      status_t err = getPixelFormatInfo(fmt, &info);
      if (err)
         return -1;
      /* bpp must be equal to depth */
      if (info.bytesPerPixel * 8 != info.bitsPerPixel)
         continue;

      if ((info.h_red - info.l_red != red) ||
          (info.h_green - info.l_green != green) ||
          (info.h_blue - info.l_blue != blue) ||
          (info.h_alpha - info.l_alpha != alpha))
         continue;

      /* mask? */
      return fmt;
   }

   return -1;
}
