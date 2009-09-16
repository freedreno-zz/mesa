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
