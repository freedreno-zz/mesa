/**
 * Functions that client APIs can call.
 */


#include "eglcurrent.h"
#include "egldisplay.h"
#include "eglimage.h"
#include "eglclient.h"


/**
 * Return the opaque client data of an image.
 */
void *
_eglClientGetImageData(EGLImageKHR image)
{
   _EGLDisplay *dpy = _eglGetCurrentDisplay();
   _EGLImage *img = _eglLookupImage(image, dpy);
   return (img) ? img->ClientData : NULL;
}
