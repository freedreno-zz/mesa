/**
 * \file miniglxP.h
 * \brief Define replacements for some X datatypes and define the DRI-related
 * data structures.
 *
 * \note Cut down version of glxclient.h.
 *
 */

#ifndef _mini_GLX_client_h_
#define _mini_GLX_client_h_

#include <signal.h>
#include <linux/fb.h>

#include <GL/miniglx.h>
#include "glheader.h"
#include "mtypes.h"


typedef unsigned long XID;

/**
 * \brief GLX-specific attributes.
 */
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


typedef struct __DRIscreenRec   __DRIscreen;   /**< \copydoc __DRIscreenRec */
typedef struct __DRIcontextRec  __DRIcontext;  /**< \copydoc __DRIcontextRec */
typedef struct __DRIdrawableRec __DRIdrawable; /**< \copydoc __DRIdrawableRec */


typedef void *(*CreateScreenFunc)(Display *dpy, int scrn, __DRIscreen *psc,
                                  int numConfigs, __GLXvisualConfig *config);



/**
 * \brief Screen dependent methods.
 *
 * This structure is initialized during the MiniGLXDisplayRec::createScreen
 * call.
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
 * This structure is initialized during the __DRIscreenRec::createContext call.
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
 * This structure is initialized during the __DRIscreenRec::createDrawable call.
 *
 * __DRIscreenRec::createDrawable is not called by libGL at this time.  It's
 * currently used via the dri_util.c utility code instead.
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
 * \brief DRIDriverContext type.
 */
struct DRIDriverContextRec {
   const char *pciBusID;
   int pciBus;
   int pciDevice;
   int pciFunc;
   int chipset;
   int bpp; 
   int cpp;  
   
   unsigned long FBStart;   /**< \brief physical address of the framebuffer */
   unsigned long MMIOStart; /**< \brief physical address of the MMIO region */
   
   int FBSize;              /**< \brief size of the mmap'd framebuffer in bytes */
   int MMIOSize;            /**< \brief size of the mmap'd MMIO region in bytes */

   void *FBAddress;         /**< \brief start of the mmap'd framebuffer */
   void *MMIOAddress;       /**< \brief start of the mmap'd MMIO region */
   
   /**
    * \name Client configuration details
    *
    * These are computed on the server and sent to clients as part of
    * the initial handshaking.
    */
   /*@{*/
   struct {
      unsigned long hSAREA;
      int SAREASize;
      unsigned long hFrameBuffer;
      int fbOrigin;
      int fbSize;
      int fbStride;
      int virtualWidth;
      int virtualHeight;
   } shared;
   
   /*@}*/
   /**
    * \name From DRIInfoRec
    */
   /*@{*/
   int drmFD;  /**< \brief DRM device file descriptor */
   struct _XF86DRISAREA *pSAREA;
   unsigned int serverContext;	/**< \brief DRM context only active on server */
   /*@}*/
   
   
   /**
    * \name Driver private
    *
    * Populated by __driInitFBDev()
    */
   /*@{*/
   void *driverPrivate;
   void *driverClientMsg;
   int driverClientMsgSize;
   /*@}*/
};

/**
 * \brief Interface to the DRI driver.
 *
 * This structure is retrieved from the loadable driver by the \e
 * __driDriver symbol to access the Mini GLX specific hardware
 * initialization and take down routines.
 */
struct DRIDriverRec { 
   /**
    * \brief Get the list of supported visuals.
    */
   int (*initScreenConfigs)( struct DRIDriverContextRec *dpy,
			     int *numConfigs, __GLXvisualConfig **configs );
   /**
    * \brief Validate the framebuffer device mode
    */
   int (*validateMode)( struct DRIDriverContextRec *dpy );

   /**
    * \brief Examine mode returned by fbdev (may differ from the one
    * requested), restore any hw regs clobbered by fbdev.
    */
   int (*postValidateMode)( struct DRIDriverContextRec *dpy );

   /**
    * \brief Initialize the framebuffer device.
    */
   int (*initFBDev)( struct DRIDriverContextRec *dpy );

   /**
    * \brief Halt the framebuffer device.
    */
   void (*haltFBDev)( struct DRIDriverContextRec *dpy );


   /**
    * \brief Idle and shutdown hardware in preparation for a vt switch.
    */
   int (*shutdownHardware)(  struct DRIDriverContextRec *dpy );

   /**
    * \brief Restore hardware state after regaining the vt.
    */
   int (*restoreHardware)(  struct DRIDriverContextRec *dpy );

   /**
    * \brief Notify hardware driver of gain/loose focus.  May be zero
    * as this is of limited utility for most drivers.  
    */
   void (*notifyFocus)( int have_focus );
};



/**
 * \brief Supported pixel formats.
 */
enum PixelFormat {
   PF_B8G8R8,    /**< \brief 24-bit BGR */
   PF_B8G8R8A8,  /**< \brief 32-bit BGRA */
   PF_B5G6R5,    /**< \brief 16-bit BGR */
   PF_B5G5R5,    /**< \brief 15-bit BGR */
   PF_CI8        /**< \brief 8-bit color index */
};



/**
 * \brief X Visual type.
 *
 * \sa ::Visual, \ref datatypes.
 */
struct MiniGLXVisualRec {
   /** \brief GLX visual information */
   const __GLXvisualConfig *glxConfig;

   /** \brief pointer back to corresponding ::XVisualInfo */
   XVisualInfo *visInfo;               

   /** \brief display handle */
   Display *dpy;

   /** \brief pixel format */
   enum PixelFormat pixelFormat;       
};



/**
 * \brief X Window type.
 *
 * \sa ::Window, \ref datatypes.
 */
struct MiniGLXWindowRec {
   Visual *visual;
                                   /** \brief position (always 0,0) */
   int x, y;
                                   /** \brief size */
   unsigned int w, h;
   void *frontStart;               /**< \brief start of front color buffer */
   void *backStart;                /**< \brief start of back color buffer */
   size_t size;                    /**< \brief color buffer size, in bytes */
   GLuint bytesPerPixel;
   GLuint rowStride;               /**< \brief in bytes */
   GLubyte *frontBottom;           /**< \brief pointer to last row */
   GLubyte *backBottom;            /**< \brief pointer to last row */
   GLubyte *curBottom;             /**<  = frontBottom or backBottom */
   __DRIdrawable driDrawable;
   GLuint ismapped;
};


/**
 * \brief GLXContext type.
 *
 * \sa ::GLXContext, \ref datatypes.
 */
struct MiniGLXContextRec {
   Window drawBuffer;       /**< \brief drawing buffer */
   Window curBuffer;        /**< \brief current buffer */
   VisualID vid;            /**< \brief visual ID */
   __DRIcontext driContext; /**< \brief context dependent methods */
};

#define MINIGLX_BUF_SIZE 512
#define MINIGLX_MAX_SERVER_FDS 10
#define MINIGLX_MAX_CLIENT_FDS 1
#define MINIGLX_EVENT_QUEUE_SZ 16
#define MINIGLX_EVENT_QUEUE_MASK (MINIGLX_EVENT_QUEUE_SZ-1)

struct MiniGLXConnection {
   int fd;
   char readbuf[MINIGLX_BUF_SIZE];
   char writebuf[MINIGLX_BUF_SIZE];
   int readbuf_count;
   int writebuf_count;
};


/**
 * \brief X Display type
 *
 * \sa ::Display, \ref datatypes.
 */
struct MiniGLXDisplayRec {
   /** \brief fixed framebuffer screen info */
   struct fb_fix_screeninfo FixedInfo; 
   /** \brief original and current variable frambuffer screen info */
   struct fb_var_screeninfo OrigVarInfo, VarInfo;
   struct sigaction OrigSigUsr1;
   struct sigaction OrigSigUsr2;
   int OriginalVT;
   int ConsoleFD;        /**< \brief console TTY device file descriptor */
   int FrameBufferFD;    /**< \brief framebuffer device file descriptor */
   int NumWindows;       /**< \brief number of open windows */
   Window TheWindow;     /**< \brief open window - only allow one window for now */
   int rotateMode;


   volatile int vtSignalFlag, haveVT;
   int hwActive;


   int IsClient, clientID;
   int nrFds;
   struct MiniGLXConnection *fd;

   struct {
      int nr, head, tail;
      XEvent queue[MINIGLX_EVENT_QUEUE_SZ];
   } eventqueue;
   

   /**
    * \name Visual configurations
    */
   /*@{*/
   int numConfigs;             /**< \brief number of visuals */
   __GLXvisualConfig *configs; /**< \brief list of visuals */
   /*@}*/

   /**
    * \name From __GLXdisplayPrivate
    */
   /*@{*/
   CreateScreenFunc createScreen; /**< \brief \e __driCreateScreen hook */
   __DRIscreen driScreen;         /**< \brief Screen dependent methods */
   void *dlHandle;                /**<
				   * \brief handle to the client dynamic
				   * library 
				   */
   /*@}*/

   /**
    * \brief Mini GLX specific driver hooks
    */
   struct DRIDriverRec *driver;
   struct DRIDriverContextRec driverContext;

   /**
    * \name Configuration details
    *
    * They are read from a configuration file by __read_config_file().
    */
   /*@{*/
   const char *fbdevDevice;
   const char *clientDriverName;
   /*@}*/
};

/**
 * \brief Clip rectangle definition.
 */
typedef struct _XF86DRIClipRect {
    unsigned short	x1; /**< \brief Upper: inclusive */
    unsigned short	y1; /**< \brief Left: inclusive */
    unsigned short	x2; /**< \brief Lower: exclusive */
    unsigned short	y2; /**< \brief Right: exclusive */
} XF86DRIClipRectRec, *XF86DRIClipRectPtr;


extern __DRIscreen *__glXFindDRIScreen(Display *dpy, int scrn);

extern Bool __glXWindowExists(Display *dpy, GLXDrawable draw);

extern int __miniglx_open_connections( Display *dpy );
extern void __miniglx_close_connections( Display *dpy );

#define MALLOC(N) malloc(N)
#define CALLOC(N) calloc(1, N)
#define CALLOC_STRUCT(T) ((struct T *) calloc(1, sizeof(struct T)))
#define FREE(P)   free(P)
#define STRCMP(A, B)  strcmp(A, B)

#endif /* !_mini_GLX_client_h_ */
