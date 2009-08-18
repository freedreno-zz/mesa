#ifndef EGLIMAGE_DRI_INCLUDED
#define EGLIMAGE_DRI_INCLUDED

#include "GL/internal/dri_interface.h"

#define __DRI_EGL_IMAGE_MAGIC \
   (('D' << 24) | \
    ('R' << 16) | \
    ('I' <<  8) | \
    ('0'))

typedef void *__DRIEGLImageHandle;
typedef struct __DRIEGLImageRec __DRIEGLImage;

struct __DRIEGLImageRec {
   GLint magic;

   __DRIdrawable *drawable;

   GLboolean texture_format_rgba;
   GLint level;
   GLint __pad[4];
};

extern __DRIEGLImage *_eglClientGetImageData(__DRIEGLImageHandle handle);

#endif /* EGLIMAGE_DRI_INCLUDED */
