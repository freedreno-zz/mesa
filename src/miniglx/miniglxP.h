
#ifndef _mini_GLX_client_h_
#define _mini_GLX_client_h_

/**
 * \file miniglxP.h
 * \brief Define replacements for some X datatypes and define the DRI-related
 * data structures.
 */
#include <linux/fb.h>

#include <GL/miniglx.h>
#include "glheader.h"
#include "mtypes.h"


typedef unsigned long XID;

typedef struct __GLXvisualConfigRec {
    VisualID vid;
    int class;
    Bool rgba;
    int redSize, greenSize, blueSize, alphaSize;
    unsigned long redMask, greenMask, blueMask, alphaMask;
    int accumRedSize, accumGreenSize, accumBlueSize, accumAlphaSize;
    Bool doubleBuffer;
    Bool stereo;
    int bufferSize;
    int depthSize;
    int stencilSize;
    int auxBuffers;
    int level;
    
    
    /**
     * \name Extended Visual Properties
     */
    /*@{*/
    int visualRating;		/**< \brief visual_rating extension */
    int transparentPixel;	/**< \brief visual_info extension */
				/** \brief colors are floats scaled to ints */
    int transparentRed, transparentGreen, transparentBlue, transparentAlpha;
    int transparentIndex;
    /*@}*/
} __GLXvisualConfig;


typedef struct __DRIscreenRec   __DRIscreen;
typedef struct __DRIcontextRec  __DRIcontext;
typedef struct __DRIdrawableRec __DRIdrawable;


typedef void *(*CreateScreenFunc)(Display *dpy, int scrn, __DRIscreen *psc,
                                  int numConfigs, __GLXvisualConfig *config);

typedef void *(*InitFBDevFunc)( Display *dpy );


/**
 * \brief Screen dependent methods.
 *
 * This structure is initialized during the \c (*createScreen)() call.
 */
struct __DRIscreenRec {
    /**
     * \brief Method to destroy the private DRI screen data.
     */
    void (*destroyScreen)(Display *dpy, int scrn, void *screenPrivate);

    /**
     * \brief Method to create the private DRI context data and initialize the
     * context dependent methods.
     */
    void *(*createContext)(Display *dpy, XVisualInfo *vis, void *sharedPrivate,
			   __DRIcontext *pctx);

    /**
     * \brief Method to create the private DRI drawable data and initialize the
     * drawable dependent methods.
     */
    void *(*createDrawable)(Display *dpy, int scrn, GLXDrawable draw,
			    VisualID vid, __DRIdrawable *pdraw);

    /**
     * \brief Method to return a pointer to the DRI drawable data.
     */
    __DRIdrawable *(*getDrawable)(Display *dpy, GLXDrawable draw,
				  void *drawablePrivate);

    /*
     * XXX in the future, implement this:
    void *(*createPBuffer)(Display *dpy, int scrn, GLXPbuffer pbuffer,
			   GLXFBConfig config, __DRIdrawable *pdraw);
     */

    /**
     * \brief Opaque pointer to private per screen direct rendering data.  
     *
     * \c NULL if direct rendering is not supported on this screen.  Never
     * dereferenced in libGL.
     */
    void *private;
};

/**
 * \brief Context dependent methods. 
 * 
 * This structure is initialized during the (*createContext)() call.
 */
struct __DRIcontextRec {
    /**
     * \brief Method to destroy the private DRI context data.
     */
    void (*destroyContext)(Display *dpy, int scrn, void *contextPrivate);

    /**
     * \brief Method to bind a DRI drawable to a DRI graphics context.
     * 
     * \todo XXX in the future, also pass a 'read' GLXDrawable for
     * glXMakeCurrentReadSGI() and GLX 1.3's glXMakeContextCurrent().
     */
    Bool (*bindContext)(Display *dpy, int scrn, GLXDrawable draw,
			GLXContext gc);

    /**
     * \brief Method to unbind a DRI drawable to a DRI graphics context.
     */
    Bool (*unbindContext)(Display *dpy, int scrn, GLXDrawable draw,
			  GLXContext gc, int will_rebind);

    /**
     * \brief Opaque pointer to private per context direct rendering data.
     * 
     * NULL if direct rendering is not supported on the display or
     * screen used to create this context.  Never dereferenced in libGL.
     */
    void *private;
};

/**
 * \brief Drawable dependent methods.
 *
 * This structure is initialized during the (*createDrawable)() call.
 * createDrawable() is not called by libGL at this time.  It's currently used
 * via the dri_util.c utility code instead.
 */
struct __DRIdrawableRec {
    /**
     * \brief Method to destroy the private DRI drawable data.
     */
    void (*destroyDrawable)(Display *dpy, void *drawablePrivate);

    /**
     * \brief Method to swap the front and back buffers.
     */
    void (*swapBuffers)(Display *dpy, void *drawablePrivate);

    /**
     * \brief Opaque pointer to private per drawable direct rendering data.
     * 
     * \c NULL if direct rendering is not supported on the display or
     * screen used to create this drawable.  Never dereferenced in libGL.
     */
    void *private;
};



/**
 * \brief X Visual type.
 */
struct MiniGLXVisualRec {
   const __GLXvisualConfig *glxConfig;
   XVisualInfo *visInfo;     /**< pointer back to corresponding XVisualInfo */
   Display *dpy;
   GLuint pixelFormat;       /**< one of \c PF_* values */
}; /* Visual */


/**
 * \brief X Window type.
 */
struct MiniGLXWindowRec {
   Visual *visual;
   int x, y;                       /**< pos (always 0,0) */
   unsigned int w, h;              /**< size */
   void *frontStart;               /**< start of front color buffer */
   void *backStart;                /**< start of back color buffer */
   size_t size;                    /**< color buffer size, in bytes */
   GLuint bytesPerPixel;
   GLuint rowStride;               /**< in bytes */
   GLubyte *frontBottom;           /**< pointer to last row */
   GLubyte *backBottom;            /**< pointer to last row */
   GLubyte *curBottom;             /**< = frontBottom or backBottom */
   __DRIdrawable driDrawable;
}; /* Window */


/**
 * \brief GLXContext type.
 */
struct MiniGLXContextRec {
   Window drawBuffer;
   Window curBuffer;
   VisualID vid;
   __DRIcontext driContext;
}; /* GLXContext */


/**
 * \brief X Display type
 */
struct MiniGLXDisplayRec {
   struct fb_fix_screeninfo FixedInfo;
   struct fb_var_screeninfo OrigVarInfo, VarInfo;
   int DesiredDepth;
   int OriginalVT;
   int ConsoleFD;
   int FrameBufferFD;
   caddr_t FrameBuffer;  /**< start of mmap'd framebuffer */
   int FrameBufferSize;  /**< in bytes */
   caddr_t MMIOAddress;  /**< start of mmap'd MMIO region */
   int MMIOSize;         /**< in bytes */
   int NumWindows;
   Window TheWindow;     /**< only allow one window for now */

   int cpp; 

   int numConfigs;
   __GLXvisualConfig *configs;

   /**
    * \name From __GLXdisplayPrivate
    */
   /*@{*/
   InitFBDevFunc driverInitFBDev;
   CreateScreenFunc createScreen;
   __DRIscreen driScreen;
   void *dlHandle;
   /*@}*/


   /**
    * \name Configuration details
    *
    * \todo Will come from a file, hardcoded for now 
    * \todo Can we get chipset from fbdev?  -- kindof, see fbdevhw.c
    */
   /*@{*/
   const char *fbdevDevice;
   const char *clientDriverName;
   const char *drmModuleName;
   const char *pciBusID;
   int pciBus;
   int pciDevice;
   int pciFunc;
   int chipset;
   /*@}*/

   /**
    * \name From DRIInfoRec
    */
   /*@{*/
   int drmFD;
   unsigned long hSAREA;
   unsigned long hFrameBuffer;
   unsigned int serverContext;	/* temporary drm context -- make an auto var? */
   int SAREASize;
   void *pSAREA;
   /*@}*/

   /**
    * \name Driver private
    *
    * Populated by __driInitFBDev()
    */
   /*@{*/
   void *driverPrivate;
   void *driverInfo;
   int driverInfoSize;
   /*@}*/
};

/**
 * \warning Do not change _XF86DRIClipRect without changing the kernel
 * structure!
 */
typedef struct _XF86DRIClipRect {
    unsigned short	x1; /**< \brief Upper: inclusive */
    unsigned short	y1; /**< \brief Left: inclusive */
    unsigned short	x2; /**< \brief Lower: exclusive */
    unsigned short	y2; /**< \brief Right: exclusive */
} XF86DRIClipRectRec, *XF86DRIClipRectPtr;


extern __DRIscreen *__glXFindDRIScreen(Display *dpy, int scrn);

extern Bool __glXWindowExists(Display *dpy, GLXDrawable draw);


#endif /* !_mini_GLX_client_h_ */
