#include <assert.h>

#include "eglimage.h"
#include "egldisplay.h"

EGLBoolean
_eglInitImage(_EGLDriver *drv, _EGLImage *img, const EGLint *attrib_list)
{
   EGLint i;

   img->Preserved = EGL_FALSE;

   for (i = 0; attrib_list && attrib_list[i] != EGL_NONE; i++) {
      switch (attrib_list[i]) {
      case EGL_IMAGE_PRESERVED_KHR:
         i++;
         img->Preserved = attrib_list[i];
         break;
      default:
         /* not an error */
         break;
      }
   }

   return EGL_TRUE;
}


_EGLImage *
_eglCreateImageKHR(_EGLDriver *drv, _EGLDisplay *dpy, _EGLContext *ctx,
                   EGLenum target, EGLClientBuffer buffer, const EGLint *attr_list)
{
   /* driver should override this function */
   return NULL;
}


EGLBoolean
_eglDestroyImageKHR(_EGLDriver *drv, _EGLDisplay *dpy, _EGLImage *image)
{
   /* driver should override this function */
   return EGL_FALSE;
}


EGLImageKHR
_eglLinkImage(_EGLImage *img, _EGLDisplay *dpy)
{
   img->Display = dpy;
   img->Next = dpy->ImageList;
   dpy->ImageList = img;
   return (EGLImageKHR) img;
}


void
_eglUnlinkImage(_EGLImage *img)
{
   _EGLImage *prev;

   prev = img->Display->ImageList;
   if (prev != img) {
      while (prev) {
         if (prev->Next == img)
            break;
         prev = prev->Next;
      }
      assert(prev);
      prev->Next = img->Next;
   }
   else {
      img->Display->ImageList = img->Next;
   }

   img->Next = NULL;
   img->Display = NULL;
}


#ifndef _EGL_SKIP_HANDLE_CHECK


/**
 * Return EGL_TRUE if the given handle is a valid handle to an image.
 */
EGLBoolean
_eglCheckImageHandle(EGLImageKHR img, _EGLDisplay *dpy)
{
   _EGLImage *cur = NULL;

   if (dpy)
      cur = dpy->ImageList;
   while (cur) {
      if (cur == (_EGLImage *) img) {
         assert(cur->Display == dpy);
         break;
      }
      cur = cur->Next;
   }
   return (cur != NULL);
}


#endif /* _EGL_SKIP_HANDLE_CHECK */
