#ifndef EGLTYPEDEFS_INCLUDED
#define EGLTYPEDEFS_INCLUDED

#define EGL_EGLEXT_PROTOTYPES

#include <EGL/egl.h>
#include <EGL/eglext.h>

#ifndef EGL_MESA_screen_surface
#define EGL_MESA_screen_surface 1

#define EGL_BAD_SCREEN_MESA                    0x4000
#define EGL_BAD_MODE_MESA                      0x4001
#define EGL_SCREEN_COUNT_MESA                  0x4002
#define EGL_SCREEN_POSITION_MESA               0x4003
#define EGL_SCREEN_POSITION_GRANULARITY_MESA   0x4004
#define EGL_MODE_ID_MESA                       0x4005
#define EGL_REFRESH_RATE_MESA                  0x4006
#define EGL_OPTIMAL_MESA                       0x4007
#define EGL_INTERLACED_MESA                    0x4008
#define EGL_SCREEN_BIT_MESA                    0x08

typedef uint32_t EGLScreenMESA;
typedef uint32_t EGLModeMESA;

#ifdef EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglChooseModeMESA(EGLDisplay dpy, EGLScreenMESA screen, const EGLint *attrib_list, EGLModeMESA *modes, EGLint modes_size, EGLint *num_modes);
EGLAPI EGLBoolean EGLAPIENTRY eglGetModesMESA(EGLDisplay dpy, EGLScreenMESA screen, EGLModeMESA *modes, EGLint modes_size, EGLint *num_modes);
EGLAPI EGLBoolean EGLAPIENTRY eglGetModeAttribMESA(EGLDisplay dpy, EGLModeMESA mode, EGLint attribute, EGLint *value);
EGLAPI EGLBoolean EGLAPIENTRY eglGetScreensMESA(EGLDisplay dpy, EGLScreenMESA *screens, EGLint max_screens, EGLint *num_screens);
EGLAPI EGLSurface EGLAPIENTRY eglCreateScreenSurfaceMESA(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list);
EGLAPI EGLBoolean EGLAPIENTRY eglShowScreenSurfaceMESA(EGLDisplay dpy, EGLint screen, EGLSurface surface, EGLModeMESA mode);
EGLAPI EGLBoolean EGLAPIENTRY eglScreenPositionMESA(EGLDisplay dpy, EGLScreenMESA screen, EGLint x, EGLint y);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryScreenMESA(EGLDisplay dpy, EGLScreenMESA screen, EGLint attribute, EGLint *value);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryScreenSurfaceMESA(EGLDisplay dpy, EGLScreenMESA screen, EGLSurface *surface);
EGLAPI EGLBoolean EGLAPIENTRY eglQueryScreenModeMESA(EGLDisplay dpy, EGLScreenMESA screen, EGLModeMESA *mode);
EGLAPI const char * EGLAPIENTRY eglQueryModeStringMESA(EGLDisplay dpy, EGLModeMESA mode);
#endif /* EGL_EGLEXT_PROTOTYPES */

typedef EGLBoolean (EGLAPIENTRYP PFNEGLCHOOSEMODEMESA) (EGLDisplay dpy, EGLScreenMESA screen, const EGLint *attrib_list, EGLModeMESA *modes, EGLint modes_size, EGLint *num_modes);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETMODESMESA) (EGLDisplay dpy, EGLScreenMESA screen, EGLModeMESA *modes, EGLint modes_size, EGLint *num_modes);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGetModeATTRIBMESA) (EGLDisplay dpy, EGLModeMESA mode, EGLint attribute, EGLint *value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLGETSCRREENSMESA) (EGLDisplay dpy, EGLScreenMESA *screens, EGLint max_screens, EGLint *num_screens);
typedef EGLSurface (EGLAPIENTRYP PFNEGLCREATESCREENSURFACEMESA) (EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSHOWSCREENSURFACEMESA) (EGLDisplay dpy, EGLint screen, EGLSurface surface, EGLModeMESA mode);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLSCREENPOSIITONMESA) (EGLDisplay dpy, EGLScreenMESA screen, EGLint x, EGLint y);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSCREENMESA) (EGLDisplay dpy, EGLScreenMESA screen, EGLint attribute, EGLint *value);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSCREENSURFACEMESA) (EGLDisplay dpy, EGLScreenMESA screen, EGLSurface *surface);
typedef EGLBoolean (EGLAPIENTRYP PFNEGLQUERYSCREENMODEMESA) (EGLDisplay dpy, EGLScreenMESA screen, EGLModeMESA *mode);
typedef const char * (EGLAPIENTRYP PFNEGLQUERYMODESTRINGMESA) (EGLDisplay dpy, EGLModeMESA mode);

#endif /* EGL_MESA_screen_surface */

#ifndef EGL_MESA_copy_context
#define EGL_MESA_copy_context 1

#ifdef EGL_EGLEXT_PROTOTYPES
EGLAPI EGLBoolean EGLAPIENTRY eglCopyContextMESA(EGLDisplay dpy, EGLContext source, EGLContext dest, EGLint mask);
#endif /* EGL_EGLEXT_PROTOTYPES */

typedef EGLBoolean (EGLAPIENTRYP PFNEGLCOPYCONTEXTMESA) (EGLDisplay dpy, EGLContext source, EGLContext dest, EGLint mask);

#endif /* EGL_MESA_copy_context */

#include "eglcompiler.h"

typedef struct _egl_api _EGLAPI;

typedef struct _egl_config _EGLConfig;

typedef struct _egl_context _EGLContext;

typedef struct _egl_display _EGLDisplay;

typedef struct _egl_driver _EGLDriver;

typedef struct _egl_extensions _EGLExtensions;

typedef struct _egl_mode _EGLMode;

typedef struct _egl_screen _EGLScreen;

typedef struct _egl_surface _EGLSurface;

typedef struct _egl_thread_info _EGLThreadInfo;

typedef struct _egl_image _EGLImage;


typedef _EGLDriver *(*_EGLMain_t)(const char *args);


#endif /* EGLTYPEDEFS_INCLUDED */
