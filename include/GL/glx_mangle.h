/* $Id: glx_mangle.h,v 1.1.1.1.8.2 2002/09/20 18:32:17 kschultz Exp $ */

/*
 * Mesa 3-D graphics library
 * Version:  4.1
 * Copyright (C) 1995-1998  Brian Paul
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#ifndef GLX_MANGLE_H
#define GLX_MANGLE_H

#define glXChooseVisual mglXChooseVisual
#define glXCreateContext mglXCreateContext
#define glXDestroyContext mglXDestroyContext
#define glXMakeCurrent mglXMakeCurrent
#define glXCopyContext mglXCopyContext
#define glXSwapBuffers mglXSwapBuffers
#define glXCreateGLXPixmap mglXCreateGLXPixmap
#define glXDestroyGLXPixmap mglXDestroyGLXPixmap
#define glXQueryExtension mglXQueryExtension
#define glXQueryVersion mglXQueryVersion
#define glXIsDirect mglXIsDirect
#define glXGetConfig mglXGetConfig
#define glXGetCurrentContext mglXGetCurrentContext
#define glXGetCurrentDrawable mglXGetCurrentDrawable
#define glXWaitGL mglXWaitGL
#define glXWaitX mglXWaitX
#define glXUseXFont mglXUseXFont

/* GLX 1.1 */
#define glXQueryExtensionsString mglXQueryExtensionsString
#define glXQueryServerString mglXQueryServerString
#define glXGetClientString mglXGetClientString

/* GLX 1.2 */
#define glXGetCurrentDisplay mglXGetCurrentDisplay

/* GLX 1.3 */
#define glXChooseFBConfig mglXChooseFBConfig
#define glXGetFBConfigAttrib mglXGetFBConfigAttrib
#define glXGetFBConfigs mglXGetFBConfigs 
#define glXGetVisualFromFBConfig mglXGetVisualFromFBConfig
#define glXCreateWindow mglXCreateWindow 
#define glXDestroyWindow mglXDestroyWindow 
#define glXCreatePixmap mglXCreatePixmap 
#define glXDestroyPixmap mglXDestroyPixmap 
#define glXCreatePbuffer mglXCreatePbuffer 
#define glXDestroyPbuffer mglXDestroyPbuffer 
#define glXQueryDrawable mglXQueryDrawable 
#define glXCreateNewContext mglXCreateNewContext 
#define glXMakeContextCurrent mglXMakeContextCurrent
#define glXGetCurrentReadDrawable mglXGetCurrentReadDrawable
#define glXQueryContext mglXQueryContext 
#define glXSelectEvent mglXSelectEvent 
#define glXGetSelectedEvent mglXGetSelectedEvent 

/* GLX 1.4 */
#define glXGetProcAddress mglXGetProcAddress

/*
 * 41. GLX_SGI_video_sync
 */
#define glXGetVideoSyncSGI mglXGetVideoSyncSGI 
#define glXWaitVideoSyncSGI mglXWaitVideoSyncSGI

/*
 * 47. GLX_EXT_import_context
 */
#define glXFreeContextEXT mglXFreeContextEXT 
#define glXGetContextIDEXT mglXGetContextIDEXT 
#define glXGetCurrentDisplayEXT mglXGetCurrentDisplayEXT
#define glXImportContextEXT mglXImportContextEXT 
#define glXQueryContextInfoEXT mglXQueryContextInfoEXT

/*
 * 215. GLX_MESA_copy_sub_buffer
 */
#define glXCopySubBufferMESA mglXCopySubBufferMESA

/*
 * 216. GLX_MESA_pixmap_colormap
 */
#define glXCreateGLXPixmapMESA mglXCreateGLXPixmapMESA

/*
 * 217. GLX_MESA_release_buffers
 */
#define glXReleaseBuffersMESA mglXReleaseBuffersMESA

/*
 * 218. GLX_MESA_set_3dfx_mode
 */
#define glXSet3DfxModeMESA mglXSet3DfxModeMESA 

/*
 * ARB 2. GLX_ARB_get_proc_address
 */
#define glXGetProcAddressARB mglXGetProcAddressARB

/**
 ** The following aren't in glxext.h yet.
 **/

/*
 * ???. GLX_NV_vertex_array_range
 */
#define glXAllocateMemoryNV mglXAllocateMemoryNV 
#define glXFreeMemoryNV mglXFreeMemoryNV

/*
 * ???. GLX_MESA_agp_offset
 */ 
#define glXGetAGPOffsetMESA mglXGetAGPOffsetMESA

/*
 * Other extensions implemented and in glxext.h
 */

#define glXSwapIntervalSGI mglXSwapIntervalSGI 
#define glXGetVideoSyncSGI mglXGetVideoSyncSGI
#define glXWaitVideoSyncSGI mglXWaitVideoSyncSGI
#define glXMakeCurrentReadSGI mglXMakeCurrentReadSGI
#define glXCushionSGI mglXCushionSGI

#define glXCreateGLXPixmapMESA mglXCreateGLXPixmapMESA
#define glXReleaseBuffersMESA mglXReleaseBuffersMESA
#define glXCopySubBufferMESA mglXCopySubBufferMESA

#define glXGetTransparentIndexSUN mglXGetTransparentIndexSUN

#define glXBindChannelToWindowSGIX mglXBindChannelToWindowSGIX
#define glXBindSwapBarrierSGIX mglXBindSwapBarrierSGIX
#define glXChannelRectSGIX mglXChannelRectSGIX 
#define glXChannelRectSyncSGIX mglXChannelRectSyncSGIX
#define glXChooseFBConfigSGIX mglXChooseFBConfigSGIX
#define glXCreateContextWithConfigSGIX mglXCreateContextWithConfigSGIX
#define glXCreateGLXPbufferSGIX mglXCreateGLXPbufferSGIX
#define glXCreateGLXPixmapWithConfigSGIX mglXCreateGLXPixmapWithConfigSGIX
#define glXDestroyGLXPbufferSGIX mglXDestroyGLXPbufferSGIX
#define glXGetCurrentReadDrawableSGI mglXGetCurrentReadDrawableSGI
#define glXGetFBConfigAttribSGIX mglXGetFBConfigAttribSGIX
#define glXGetFBConfigFromVisualSGIX mglXGetFBConfigFromVisualSGIX
#define glXGetSelectedEventSGIX mglXGetSelectedEventSGIX
#define glXGetVisualFromFBConfigSGIX mglXGetVisualFromFBConfigSGIX
#define glXJoinSwapGroupSGIX mglXJoinSwapGroupSGIX
#define glXQueryChannelDeltasSGIX mglXQueryChannelDeltasSGIX
#define glXQueryChannelRectSGIX mglXQueryChannelRectSGIX
#define glXQueryGLXPbufferSGIX mglXQueryGLXPbufferSGIX
#define glXQueryMaxSwapBarriersSGIX mglXQueryMaxSwapBarriersSGIX
#define glXSelectEventSGIX mglXSelectEventSGIX

#endif






