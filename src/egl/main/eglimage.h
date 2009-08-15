#ifndef EGLIMAGE_INCLUDED
#define EGLIMAGE_INCLUDED


#include "egltypedefs.h"


/**
 * "Base" class for device driver images.
 */
struct _egl_image
{
   /* Client data that client APIs and the driver agree on */
   void *ClientData;

   /* Managed by EGLDisplay for linking */
   _EGLDisplay *Display;
   _EGLImage *Next;

   EGLBoolean Preserved;
};


extern EGLBoolean
_eglInitImage(_EGLDriver *drv, _EGLImage *img, const EGLint *attrib_list);


extern _EGLImage *
_eglCreateImageKHR(_EGLDriver *drv, _EGLDisplay *dpy, _EGLContext *ctx,
                   EGLenum target, EGLClientBuffer buffer, const EGLint *attr_list);


extern EGLBoolean
_eglDestroyImageKHR(_EGLDriver *drv, _EGLDisplay *dpy, _EGLImage *image);


extern EGLImageKHR
_eglLinkImage(_EGLImage *img, _EGLDisplay *dpy);


extern void
_eglUnlinkImage(_EGLImage *img);


#ifndef _EGL_SKIP_HANDLE_CHECK


extern EGLBoolean
_eglCheckImageHandle(EGLImageKHR img, _EGLDisplay *dpy);


#else


/**
 * Perform a quick check on the handle.
 */
static INLINE EGLBoolean
_eglCheckImageHandle(EGLImageKHR img, _EGLDisplay *dpy)
{
   _EGLImage *i = (_EGLImage *) img;
   return (dpy && i && i->Display == dpy);
}


#endif


/**
 * Lookup a handle to find the linked image.
 * Return NULL if the handle has no corresponding linked image.
 */
static INLINE _EGLImage *
_eglLookupImage(EGLImageKHR image, _EGLDisplay *dpy)
{
   _EGLImage *img = (_EGLImage *) image;
   if (!_eglCheckImageHandle(img, dpy))
      img = NULL;
   return img;
}


/**
 * Return the handle of a linked image.
 */
static INLINE EGLImageKHR
_eglGetImageHandle(_EGLImage *img)
{
   return (EGLImageKHR) ((img && img->Display) ? img : EGL_NO_IMAGE_KHR);
}


#endif /* EGLIMAGE_INCLUDED */
