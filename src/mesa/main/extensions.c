/* $Id: extensions.c,v 1.10.2.3 1999/12/12 18:30:47 keithw Exp $ */

/*
 * Mesa 3-D graphics library
 * Version:  3.1
 * 
 * Copyright (C) 1999  Brian Paul   All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef XFree86Server
#include <stdlib.h>
#else
#include "GL/xf86glx.h"
#endif
#include "context.h"
#include "extensions.h"
#include "simple_list.h"
#include "types.h"


#define MAX_EXT_NAMELEN 80

struct extension {
   struct extension *next, *prev;
   int enabled;
   char name[MAX_EXT_NAMELEN+1];
   void (*notify)( GLcontext *, GLboolean ); 
};



static struct { int enabled; const char *name; } default_extensions[] = {
   { ALWAYS_ENABLED, "GL_EXT_blend_color" },
   { DEFAULT_OFF,    "ARB_imaging" },
   { DEFAULT_ON,     "GL_EXT_blend_minmax" },
   { DEFAULT_ON,     "GL_EXT_blend_logic_op" },
   { DEFAULT_ON,     "GL_EXT_blend_subtract" },
   { DEFAULT_ON,     "GL_EXT_paletted_texture" },
   { DEFAULT_ON,     "GL_EXT_point_parameters" },
   { ALWAYS_ENABLED, "GL_EXT_polygon_offset" },
   { ALWAYS_ENABLED, "GL_EXT_vertex_array" },
   { ALWAYS_ENABLED, "GL_EXT_texture_object" },
   { DEFAULT_ON,     "GL_EXT_texture3D" },
   { ALWAYS_ENABLED, "GL_MESA_window_pos" },
   { ALWAYS_ENABLED, "GL_MESA_resize_buffers" },
   { DEFAULT_ON,     "GL_EXT_shared_texture_palette" },
   { ALWAYS_ENABLED, "GL_EXT_rescale_normal" },
   { ALWAYS_ENABLED, "GL_EXT_abgr" },
   { ALWAYS_ENABLED, "GL_SGIS_texture_edge_clamp" },
   { ALWAYS_ENABLED, "GL_EXT_stencil_wrap" },
   { DEFAULT_ON,     "GL_INGR_blend_func_separate" },
   { DEFAULT_ON,     "GL_ARB_multitexture" },
   { ALWAYS_ENABLED, "GL_NV_texgen_reflection" },
   { DEFAULT_ON,     "GL_PGI_misc_hints" },
   { DEFAULT_ON,     "GL_EXT_compiled_vertex_array" },
   { DEFAULT_ON,     "GL_EXT_clip_volume_hint" },
   
   /* These obviously won't make it before 3.3:
    */
   { DEFAULT_OFF,    "GL_EXT_vertex_array_set" },
   { DEFAULT_OFF,    "GL_EXT_texture_env" },
   { DEFAULT_OFF,    "GL_EXT_fog_coord" },
};


int gl_extensions_add( GLcontext *ctx, 
		       int state, 
		       const char *name, 
		       void (*notify)(void) )
{
   (void) notify;

   if (ctx->Extensions.ext_string == 0) 
   {
      struct extension *t = MALLOC_STRUCT(extension);
      t->enabled = state;
      strncpy(t->name, name, MAX_EXT_NAMELEN);
      t->name[MAX_EXT_NAMELEN] = 0;
      t->notify = (void (*)(GLcontext *, GLboolean)) notify;
      insert_at_tail( ctx->Extensions.ext_list, t );
      return 0;
   }
   return 1;
}


static int set_extension( GLcontext *ctx, const char *name, GLuint state )
{
   struct extension *i;
   foreach( i, ctx->Extensions.ext_list ) 
      if (strncmp(i->name, name, MAX_EXT_NAMELEN) == 0) 
	 break;

   if (i == ctx->Extensions.ext_list) return 1;

   if (i->enabled && !(i->enabled & ALWAYS_ENABLED))
   {
      if (i->notify) i->notify( ctx, state );      
      i->enabled = state;
   }

   return 0;
}   


int gl_extensions_enable( GLcontext *ctx, const char *name )
{
   if (ctx->Extensions.ext_string == 0) 
      return set_extension( ctx, name, 1 );
   return 1;
}


int gl_extensions_disable( GLcontext *ctx, const char *name )
{
   if (ctx->Extensions.ext_string == 0) 
      return set_extension( ctx, name, 0 );
   return 1;
}
      

/*
 * Test if the named extension is enabled in this context.
 */
GLboolean gl_extension_is_enabled( GLcontext *ctx, const char *name)
{
   struct extension *i;
   foreach( i, ctx->Extensions.ext_list )
      if (strncmp(i->name, name, MAX_EXT_NAMELEN) == 0) {
         if (i->enabled)
            return GL_TRUE;
         else
            return GL_FALSE;
      }

   return GL_FALSE;
}


void gl_extensions_dtr( GLcontext *ctx )
{
   struct extension *i, *nexti;

   if (ctx->Extensions.ext_string) {
      FREE( ctx->Extensions.ext_string );
      ctx->Extensions.ext_string = 0;
   }

   if (ctx->Extensions.ext_list) {
      foreach_s( i, nexti, ctx->Extensions.ext_list ) {
	 remove_from_list( i );
	 FREE( i );
      }
   
      FREE(ctx->Extensions.ext_list);
      ctx->Extensions.ext_list = 0;
   }      
}


void gl_extensions_ctr( GLcontext *ctx )
{
   GLuint i;

   ctx->Extensions.ext_string = 0;
   ctx->Extensions.ext_list = MALLOC_STRUCT(extension);
   make_empty_list( ctx->Extensions.ext_list );

   for (i = 0 ; i < Elements(default_extensions) ; i++) {
      gl_extensions_add( ctx, 
			 default_extensions[i].enabled,
			 default_extensions[i].name,
			 0 );
   }
}


const char *gl_extensions_get_string( GLcontext *ctx )
{
   if (ctx->Extensions.ext_string == 0) 
   {
      struct extension *i;
      char *str;
      GLuint len = 0;
      foreach (i, ctx->Extensions.ext_list) 
	 if (i->enabled)
	    len += strlen(i->name) + 1;
      
      if (len == 0) 
	 return "";

      str = (char *)MALLOC(len * sizeof(char));
      ctx->Extensions.ext_string = str;

      foreach (i, ctx->Extensions.ext_list) 
	 if (i->enabled) {
	    strcpy(str, i->name);
	    str += strlen(str);
	    *str++ = ' ';
	 }

      *(str-1) = 0;
   }
      
   return ctx->Extensions.ext_string;
}



/*
 * Return the address of an extension function.
 * This is meant to be called by glXGetProcAddress(), wglGetProcAddress(),
 * or similar function.
 * NOTE: this function could be optimized to binary search a sorted
 * list of function names.
 */
void (*gl_get_proc_address( const GLubyte *procName ))()
{
   typedef void (*gl_function)();
   struct proc {
      const char *name;
      gl_function address;
   };
   static struct proc procTable[] = {
      /* OpenGL 1.0 functions */
      { "glAccum", (gl_function) glAccum },
      { "glAlphaFunc", (gl_function) glAlphaFunc },
      { "glBegin", (gl_function) glBegin },
      { "glBitmap", (gl_function) glBitmap },
      { "glAccum", (gl_function) glAccum },
      { "glAlphaFunc", (gl_function) glAlphaFunc },
      { "glBegin", (gl_function) glBegin },
      { "glBitmap", (gl_function) glBitmap },
      { "glBlendFunc", (gl_function) glBlendFunc },
      { "glCallList", (gl_function) glCallList },
      { "glCallLists", (gl_function) glCallLists },
      { "glClear", (gl_function) glClear },
      { "glClearAccum", (gl_function) glClearAccum },
      { "glClearColor", (gl_function) glClearColor },
      { "glClearDepth", (gl_function) glClearDepth },
      { "glClearIndex", (gl_function) glClearIndex },
      { "glClearStencil", (gl_function) glClearStencil },
      { "glClipPlane", (gl_function) glClipPlane },
      { "glColor3b", (gl_function) glColor3b },
      { "glColor3bv", (gl_function) glColor3bv },
      { "glColor3d", (gl_function) glColor3d },
      { "glColor3dv", (gl_function) glColor3dv },
      { "glColor3f", (gl_function) glColor3f },
      { "glColor3fv", (gl_function) glColor3fv },
      { "glColor3i", (gl_function) glColor3i },
      { "glColor3iv", (gl_function) glColor3iv },
      { "glColor3s", (gl_function) glColor3s },
      { "glColor3sv", (gl_function) glColor3sv },
      { "glColor3ub", (gl_function) glColor3ub },
      { "glColor3ubv", (gl_function) glColor3ubv },
      { "glColor3ui", (gl_function) glColor3ui },
      { "glColor3uiv", (gl_function) glColor3uiv },
      { "glColor3us", (gl_function) glColor3us },
      { "glColor3usv", (gl_function) glColor3usv },
      { "glColor4b", (gl_function) glColor4b },
      { "glColor4bv", (gl_function) glColor4bv },
      { "glColor4d", (gl_function) glColor4d },
      { "glColor4dv", (gl_function) glColor4dv },
      { "glColor4f", (gl_function) glColor4f },
      { "glColor4fv", (gl_function) glColor4fv },
      { "glColor4i", (gl_function) glColor4i },
      { "glColor4iv", (gl_function) glColor4iv },
      { "glColor4s", (gl_function) glColor4s },
      { "glColor4sv", (gl_function) glColor4sv },
      { "glColor4ub", (gl_function) glColor4ub },
      { "glColor4ubv", (gl_function) glColor4ubv },
      { "glColor4ui", (gl_function) glColor4ui },
      { "glColor4uiv", (gl_function) glColor4uiv },
      { "glColor4us", (gl_function) glColor4us },
      { "glColor4usv", (gl_function) glColor4usv },
      { "glColorMask", (gl_function) glColorMask },
      { "glColorMaterial", (gl_function) glColorMaterial },
      { "glCopyPixels", (gl_function) glCopyPixels },
      { "glCullFace", (gl_function) glCullFace },
      { "glDeleteLists", (gl_function) glDeleteLists },
      { "glDepthFunc", (gl_function) glDepthFunc },
      { "glDepthMask", (gl_function) glDepthMask },
      { "glDepthRange", (gl_function) glDepthRange },
      { "glDisable", (gl_function) glDisable },
      { "glDrawBuffer", (gl_function) glDrawBuffer },
      { "glDrawPixels", (gl_function) glDrawPixels },
      { "glEdgeFlag", (gl_function) glEdgeFlag },
      { "glEdgeFlagv", (gl_function) glEdgeFlagv },
      { "glEnable", (gl_function) glEnable },
      { "glEnd", (gl_function) glEnd },
      { "glEndList", (gl_function) glEndList },
      { "glEvalCoord1d", (gl_function) glEvalCoord1d },
      { "glEvalCoord1dv", (gl_function) glEvalCoord1dv },
      { "glEvalCoord1f", (gl_function) glEvalCoord1f },
      { "glEvalCoord1fv", (gl_function) glEvalCoord1fv },
      { "glEvalCoord2d", (gl_function) glEvalCoord2d },
      { "glEvalCoord2dv", (gl_function) glEvalCoord2dv },
      { "glEvalCoord2f", (gl_function) glEvalCoord2f },
      { "glEvalCoord2fv", (gl_function) glEvalCoord2fv },
      { "glEvalMesh1", (gl_function) glEvalMesh1 },
      { "glEvalMesh2", (gl_function) glEvalMesh2 },
      { "glEvalPoint1", (gl_function) glEvalPoint1 },
      { "glEvalPoint2", (gl_function) glEvalPoint2 },
      { "glFeedbackBuffer", (gl_function) glFeedbackBuffer },
      { "glFinish", (gl_function) glFinish },
      { "glFlush", (gl_function) glFlush },
      { "glFogf", (gl_function) glFogf },
      { "glFogfv", (gl_function) glFogfv },
      { "glFogi", (gl_function) glFogi },
      { "glFogiv", (gl_function) glFogiv },
      { "glFrontFace", (gl_function) glFrontFace },
      { "glFrustum", (gl_function) glFrustum },
      { "glGenLists", (gl_function) glGenLists },
      { "glGetBooleanv", (gl_function) glGetBooleanv },
      { "glGetClipPlane", (gl_function) glGetClipPlane },
      { "glGetDoublev", (gl_function) glGetDoublev },
      { "glGetError", (gl_function) glGetError },
      { "glGetFloatv", (gl_function) glGetFloatv },
      { "glGetIntegerv", (gl_function) glGetIntegerv },
      { "glGetLightfv", (gl_function) glGetLightfv },
      { "glGetLightiv", (gl_function) glGetLightiv },
      { "glGetMapdv", (gl_function) glGetMapdv },
      { "glGetMapfv", (gl_function) glGetMapfv },
      { "glGetMapiv", (gl_function) glGetMapiv },
      { "glGetMaterialfv", (gl_function) glGetMaterialfv },
      { "glGetMaterialiv", (gl_function) glGetMaterialiv },
      { "glGetPixelMapfv", (gl_function) glGetPixelMapfv },
      { "glGetPixelMapuiv", (gl_function) glGetPixelMapuiv },
      { "glGetPixelMapusv", (gl_function) glGetPixelMapusv },
      { "glGetPolygonStipple", (gl_function) glGetPolygonStipple },
      { "glGetString", (gl_function) glGetString },
      { "glGetTexEnvfv", (gl_function) glGetTexEnvfv },
      { "glGetTexEnviv", (gl_function) glGetTexEnviv },
      { "glGetTexGendv", (gl_function) glGetTexGendv },
      { "glGetTexGenfv", (gl_function) glGetTexGenfv },
      { "glGetTexGeniv", (gl_function) glGetTexGeniv },
      { "glGetTexImage", (gl_function) glGetTexImage },
      { "glGetTexLevelParameterfv", (gl_function) glGetTexLevelParameterfv },
      { "glGetTexLevelParameteriv", (gl_function) glGetTexLevelParameteriv },
      { "glGetTexParameterfv", (gl_function) glGetTexParameterfv },
      { "glGetTexParameteriv", (gl_function) glGetTexParameteriv },
      { "glHint", (gl_function) glHint },
      { "glIndexMask", (gl_function) glIndexMask },
      { "glIndexd", (gl_function) glIndexd },
      { "glIndexdv", (gl_function) glIndexdv },
      { "glIndexf", (gl_function) glIndexf },
      { "glIndexfv", (gl_function) glIndexfv },
      { "glIndexi", (gl_function) glIndexi },
      { "glIndexiv", (gl_function) glIndexiv },
      { "glIndexs", (gl_function) glIndexs },
      { "glIndexsv", (gl_function) glIndexsv },
      { "glInitNames", (gl_function) glInitNames },
      { "glIsEnabled", (gl_function) glIsEnabled },
      { "glIsList", (gl_function) glIsList },
      { "glLightModelf", (gl_function) glLightModelf },
      { "glLightModelfv", (gl_function) glLightModelfv },
      { "glLightModeli", (gl_function) glLightModeli },
      { "glLightModeliv", (gl_function) glLightModeliv },
      { "glLightf", (gl_function) glLightf },
      { "glLightfv", (gl_function) glLightfv },
      { "glLighti", (gl_function) glLighti },
      { "glLightiv", (gl_function) glLightiv },
      { "glLineStipple", (gl_function) glLineStipple },
      { "glLineWidth", (gl_function) glLineWidth },
      { "glListBase", (gl_function) glListBase },
      { "glLoadIdentity", (gl_function) glLoadIdentity },
      { "glLoadMatrixd", (gl_function) glLoadMatrixd },
      { "glLoadMatrixf", (gl_function) glLoadMatrixf },
      { "glLoadName", (gl_function) glLoadName },
      { "glLogicOp", (gl_function) glLogicOp },
      { "glMap1d", (gl_function) glMap1d },
      { "glMap1f", (gl_function) glMap1f },
      { "glMap2d", (gl_function) glMap2d },
      { "glMap2f", (gl_function) glMap2f },
      { "glMapGrid1d", (gl_function) glMapGrid1d },
      { "glMapGrid1f", (gl_function) glMapGrid1f },
      { "glMapGrid2d", (gl_function) glMapGrid2d },
      { "glMapGrid2f", (gl_function) glMapGrid2f },
      { "glMaterialf", (gl_function) glMaterialf },
      { "glMaterialfv", (gl_function) glMaterialfv },
      { "glMateriali", (gl_function) glMateriali },
      { "glMaterialiv", (gl_function) glMaterialiv },
      { "glMatrixMode", (gl_function) glMatrixMode },
      { "glMultMatrixd", (gl_function) glMultMatrixd },
      { "glMultMatrixf", (gl_function) glMultMatrixf },
      { "glNewList", (gl_function) glNewList },
      { "glNormal3b", (gl_function) glNormal3b },
      { "glNormal3bv", (gl_function) glNormal3bv },
      { "glNormal3d", (gl_function) glNormal3d },
      { "glNormal3dv", (gl_function) glNormal3dv },
      { "glNormal3f", (gl_function) glNormal3f },
      { "glNormal3fv", (gl_function) glNormal3fv },
      { "glNormal3i", (gl_function) glNormal3i },
      { "glNormal3iv", (gl_function) glNormal3iv },
      { "glNormal3s", (gl_function) glNormal3s },
      { "glNormal3sv", (gl_function) glNormal3sv },
      { "glOrtho", (gl_function) glOrtho },
      { "glPassThrough", (gl_function) glPassThrough },
      { "glPixelMapfv", (gl_function) glPixelMapfv },
      { "glPixelMapuiv", (gl_function) glPixelMapuiv },
      { "glPixelMapusv", (gl_function) glPixelMapusv },
      { "glPixelStoref", (gl_function) glPixelStoref },
      { "glPixelStorei", (gl_function) glPixelStorei },
      { "glPixelTransferf", (gl_function) glPixelTransferf },
      { "glPixelTransferi", (gl_function) glPixelTransferi },
      { "glPixelZoom", (gl_function) glPixelZoom },
      { "glPointSize", (gl_function) glPointSize },
      { "glPolygonMode", (gl_function) glPolygonMode },
      { "glPolygonOffset", (gl_function) glPolygonOffset },
      { "glPolygonStipple", (gl_function) glPolygonStipple },
      { "glPopAttrib", (gl_function) glPopAttrib },
      { "glPopMatrix", (gl_function) glPopMatrix },
      { "glPopName", (gl_function) glPopName },
      { "glPushAttrib", (gl_function) glPushAttrib },
      { "glPushMatrix", (gl_function) glPushMatrix },
      { "glPushName", (gl_function) glPushName },
      { "glRasterPos2d", (gl_function) glRasterPos2d },
      { "glRasterPos2dv", (gl_function) glRasterPos2dv },
      { "glRasterPos2f", (gl_function) glRasterPos2f },
      { "glRasterPos2fv", (gl_function) glRasterPos2fv },
      { "glRasterPos2i", (gl_function) glRasterPos2i },
      { "glRasterPos2iv", (gl_function) glRasterPos2iv },
      { "glRasterPos2s", (gl_function) glRasterPos2s },
      { "glRasterPos2sv", (gl_function) glRasterPos2sv },
      { "glRasterPos3d", (gl_function) glRasterPos3d },
      { "glRasterPos3dv", (gl_function) glRasterPos3dv },
      { "glRasterPos3f", (gl_function) glRasterPos3f },
      { "glRasterPos3fv", (gl_function) glRasterPos3fv },
      { "glRasterPos3i", (gl_function) glRasterPos3i },
      { "glRasterPos3iv", (gl_function) glRasterPos3iv },
      { "glRasterPos3s", (gl_function) glRasterPos3s },
      { "glRasterPos3sv", (gl_function) glRasterPos3sv },
      { "glRasterPos4d", (gl_function) glRasterPos4d },
      { "glRasterPos4dv", (gl_function) glRasterPos4dv },
      { "glRasterPos4f", (gl_function) glRasterPos4f },
      { "glRasterPos4fv", (gl_function) glRasterPos4fv },
      { "glRasterPos4i", (gl_function) glRasterPos4i },
      { "glRasterPos4iv", (gl_function) glRasterPos4iv },
      { "glRasterPos4s", (gl_function) glRasterPos4s },
      { "glRasterPos4sv", (gl_function) glRasterPos4sv },
      { "glReadBuffer", (gl_function) glReadBuffer },
      { "glReadPixels", (gl_function) glReadPixels },
      { "glRectd", (gl_function) glRectd },
      { "glRectdv", (gl_function) glRectdv },
      { "glRectf", (gl_function) glRectf },
      { "glRectfv", (gl_function) glRectfv },
      { "glRecti", (gl_function) glRecti },
      { "glRectiv", (gl_function) glRectiv },
      { "glRects", (gl_function) glRects },
      { "glRectsv", (gl_function) glRectsv },
      { "glRenderMode", (gl_function) glRenderMode },
      { "glRotated", (gl_function) glRotated },
      { "glRotatef", (gl_function) glRotatef },
      { "glScaled", (gl_function) glScaled },
      { "glScalef", (gl_function) glScalef },
      { "glScissor", (gl_function) glScissor },
      { "glSelectBuffer", (gl_function) glSelectBuffer },
      { "glShadeModel", (gl_function) glShadeModel },
      { "glStencilFunc", (gl_function) glStencilFunc },
      { "glStencilMask", (gl_function) glStencilMask },
      { "glStencilOp", (gl_function) glStencilOp },
      { "glTexCoord1d", (gl_function) glTexCoord1d },
      { "glTexCoord1dv", (gl_function) glTexCoord1dv },
      { "glTexCoord1f", (gl_function) glTexCoord1f },
      { "glTexCoord1fv", (gl_function) glTexCoord1fv },
      { "glTexCoord1i", (gl_function) glTexCoord1i },
      { "glTexCoord1iv", (gl_function) glTexCoord1iv },
      { "glTexCoord1s", (gl_function) glTexCoord1s },
      { "glTexCoord1sv", (gl_function) glTexCoord1sv },
      { "glTexCoord2d", (gl_function) glTexCoord2d },
      { "glTexCoord2dv", (gl_function) glTexCoord2dv },
      { "glTexCoord2f", (gl_function) glTexCoord2f },
      { "glTexCoord2fv", (gl_function) glTexCoord2fv },
      { "glTexCoord2i", (gl_function) glTexCoord2i },
      { "glTexCoord2iv", (gl_function) glTexCoord2iv },
      { "glTexCoord2s", (gl_function) glTexCoord2s },
      { "glTexCoord2sv", (gl_function) glTexCoord2sv },
      { "glTexCoord3d", (gl_function) glTexCoord3d },
      { "glTexCoord3dv", (gl_function) glTexCoord3dv },
      { "glTexCoord3f", (gl_function) glTexCoord3f },
      { "glTexCoord3fv", (gl_function) glTexCoord3fv },
      { "glTexCoord3i", (gl_function) glTexCoord3i },
      { "glTexCoord3iv", (gl_function) glTexCoord3iv },
      { "glTexCoord3s", (gl_function) glTexCoord3s },
      { "glTexCoord3sv", (gl_function) glTexCoord3sv },
      { "glTexCoord4d", (gl_function) glTexCoord4d },
      { "glTexCoord4dv", (gl_function) glTexCoord4dv },
      { "glTexCoord4f", (gl_function) glTexCoord4f },
      { "glTexCoord4fv", (gl_function) glTexCoord4fv },
      { "glTexCoord4i", (gl_function) glTexCoord4i },
      { "glTexCoord4iv", (gl_function) glTexCoord4iv },
      { "glTexCoord4s", (gl_function) glTexCoord4s },
      { "glTexCoord4sv", (gl_function) glTexCoord4sv },
      { "glTexEnvf", (gl_function) glTexEnvf },
      { "glTexEnvfv", (gl_function) glTexEnvfv },
      { "glTexEnvi", (gl_function) glTexEnvi },
      { "glTexEnviv", (gl_function) glTexEnviv },
      { "glTexGend", (gl_function) glTexGend },
      { "glTexGendv", (gl_function) glTexGendv },
      { "glTexGenf", (gl_function) glTexGenf },
      { "glTexGenfv", (gl_function) glTexGenfv },
      { "glTexGeni", (gl_function) glTexGeni },
      { "glTexGeniv", (gl_function) glTexGeniv },
      { "glTexImage1D", (gl_function) glTexImage1D },
      { "glTexImage2D", (gl_function) glTexImage2D },
      { "glTexParameterf", (gl_function) glTexParameterf },
      { "glTexParameterfv", (gl_function) glTexParameterfv },
      { "glTexParameteri", (gl_function) glTexParameteri },
      { "glTexParameteriv", (gl_function) glTexParameteriv },
      { "glTranslated", (gl_function) glTranslated },
      { "glTranslatef", (gl_function) glTranslatef },
      { "glVertex2d", (gl_function) glVertex2d },
      { "glVertex2dv", (gl_function) glVertex2dv },
      { "glVertex2f", (gl_function) glVertex2f },
      { "glVertex2fv", (gl_function) glVertex2fv },
      { "glVertex2i", (gl_function) glVertex2i },
      { "glVertex2iv", (gl_function) glVertex2iv },
      { "glVertex2s", (gl_function) glVertex2s },
      { "glVertex2sv", (gl_function) glVertex2sv },
      { "glVertex3d", (gl_function) glVertex3d },
      { "glVertex3dv", (gl_function) glVertex3dv },
      { "glVertex3f", (gl_function) glVertex3f },
      { "glVertex3fv", (gl_function) glVertex3fv },
      { "glVertex3i", (gl_function) glVertex3i },
      { "glVertex3iv", (gl_function) glVertex3iv },
      { "glVertex3s", (gl_function) glVertex3s },
      { "glVertex3sv", (gl_function) glVertex3sv },
      { "glVertex4d", (gl_function) glVertex4d },
      { "glVertex4dv", (gl_function) glVertex4dv },
      { "glVertex4f", (gl_function) glVertex4f },
      { "glVertex4fv", (gl_function) glVertex4fv },
      { "glVertex4i", (gl_function) glVertex4i },
      { "glVertex4iv", (gl_function) glVertex4iv },
      { "glVertex4s", (gl_function) glVertex4s },
      { "glVertex4sv", (gl_function) glVertex4sv },
      { "glViewport", (gl_function) glViewport },

      /* OpenGL 1.1 functions */
      { "glAreTexturesResident", (gl_function) glAreTexturesResident },
      { "glArrayElement", (gl_function) glArrayElement },
      { "glBindTexture", (gl_function) glBindTexture },
      { "glColorPointer", (gl_function) glColorPointer },
      { "glCopyTexImage1D", (gl_function) glCopyTexImage1D },
      { "glCopyTexImage2D", (gl_function) glCopyTexImage2D },
      { "glCopyTexSubImage1D", (gl_function) glCopyTexSubImage1D },
      { "glCopyTexSubImage2D", (gl_function) glCopyTexSubImage2D },
      { "glDeleteTextures", (gl_function) glDeleteTextures },
      { "glDisableClientState", (gl_function) glDisableClientState },
      { "glDrawArrays", (gl_function) glDrawArrays },
      { "glDrawElements", (gl_function) glDrawElements },
      { "glEdgeFlagPointer", (gl_function) glEdgeFlagPointer },
      { "glEnableClientState", (gl_function) glEnableClientState },
      { "glGenTextures", (gl_function) glGenTextures },
      { "glGetPointerv", (gl_function) glGetPointerv },
      { "glIndexPointer", (gl_function) glIndexPointer },
      { "glIndexub", (gl_function) glIndexub },
      { "glIndexubv", (gl_function) glIndexubv },
      { "glInterleavedArrays", (gl_function) glInterleavedArrays },
      { "glIsTexture", (gl_function) glIsTexture },
      { "glNormalPointer", (gl_function) glNormalPointer },
      { "glPopClientAttrib", (gl_function) glPopClientAttrib },
      { "glPrioritizeTextures", (gl_function) glPrioritizeTextures },
      { "glPushClientAttrib", (gl_function) glPushClientAttrib },
      { "glTexCoordPointer", (gl_function) glTexCoordPointer },
      { "glTexSubImage1D", (gl_function) glTexSubImage1D },
      { "glTexSubImage2D", (gl_function) glTexSubImage2D },
      { "glVertexPointer", (gl_function) glVertexPointer },

      /* OpenGL 1.2 functions */
      { "glCopyTexSubImage3D", (gl_function) glCopyTexSubImage3D },
      { "glDrawRangeElements", (gl_function) glDrawRangeElements },
      { "glTexImage3D", (gl_function) glTexImage3D },
      { "glTexSubImage3D", (gl_function) glTexSubImage3D },

      /* ARB_imaging functions */
      { "glBlendColor", (gl_function) glBlendColor },
      { "glBlendEquation", (gl_function) glBlendEquation },
      { "glColorSubTable", (gl_function) glColorSubTable },
      { "glColorTable", (gl_function) glColorTable },
      { "glColorTableParameterfv", (gl_function) glColorTableParameterfv },
      { "glColorTableParameteriv", (gl_function) glColorTableParameteriv },
      { "glConvolutionFilter1D", (gl_function) glConvolutionFilter1D },
      { "glConvolutionFilter2D", (gl_function) glConvolutionFilter2D },
      { "glConvolutionParameterf", (gl_function) glConvolutionParameterf },
      { "glConvolutionParameterfv", (gl_function) glConvolutionParameterfv },
      { "glConvolutionParameteri", (gl_function) glConvolutionParameteri },
      { "glConvolutionParameteriv", (gl_function) glConvolutionParameteriv },
      { "glCopyColorSubTable", (gl_function) glCopyColorSubTable },
      { "glCopyColorTable", (gl_function) glCopyColorTable },
      { "glCopyConvolutionFilter1D", (gl_function) glCopyConvolutionFilter1D },
      { "glCopyConvolutionFilter2D", (gl_function) glCopyConvolutionFilter2D },
      { "glGetColorTable", (gl_function) glGetColorTable },
      { "glGetColorTableParameterfv", (gl_function) glGetColorTableParameterfv },
      { "glGetColorTableParameteriv", (gl_function) glGetColorTableParameteriv },
      { "glGetConvolutionFilter", (gl_function) glGetConvolutionFilter },
      { "glGetConvolutionParameterfv", (gl_function) glGetConvolutionParameterfv },
      { "glGetConvolutionParameteriv", (gl_function) glGetConvolutionParameteriv },
      { "glGetHistogram", (gl_function) glGetHistogram },
      { "glGetHistogramParameterfv", (gl_function) glGetHistogramParameterfv },
      { "glGetHistogramParameteriv", (gl_function) glGetHistogramParameteriv },
      { "glGetMinmax", (gl_function) glGetMinmax },
      { "glGetMinmaxParameterfv", (gl_function) glGetMinmaxParameterfv },
      { "glGetMinmaxParameteriv", (gl_function) glGetMinmaxParameteriv },
      { "glGetSeparableFilter", (gl_function) glGetSeparableFilter },
      { "glHistogram", (gl_function) glHistogram },
      { "glMinmax", (gl_function) glMinmax },
      { "glResetHistogram", (gl_function) glResetHistogram },
      { "glResetMinmax", (gl_function) glResetMinmax },
      { "glSeparableFilter2D", (gl_function) glSeparableFilter2D },

      /* GL_EXT_paletted_texture */
      { "glColorTableEXT", (gl_function) glColorTableEXT },
      { "glColorSubTableEXT", (gl_function) glColorSubTableEXT },
      { "glGetColorTableEXT", (gl_function) glGetColorTableEXT },
      { "glGetColorTableParameterfvEXT", (gl_function) glGetColorTableParameterfvEXT },
      { "glGetColorTableParameterivEXT", (gl_function) glGetColorTableParameterivEXT },

      /* GL_EXT_compiled_vertex_array */
      { "glLockArraysEXT", (gl_function) glLockArraysEXT },
      { "glUnlockArraysEXT", (gl_function) glUnlockArraysEXT },

      /* GL_EXT_point_parameters */
      { "glPointParameterfEXT", (gl_function) glPointParameterfEXT },
      { "glPointParameterfvEXT", (gl_function) glPointParameterfvEXT },

      /* GL_EXT_polygon_offset */
      { "glPolygonOffsetEXT", (gl_function) glPolygonOffsetEXT },

      /* GL_EXT_blend_minmax */
      { "glBlendEquationEXT", (gl_function) glBlendEquationEXT },

      /* GL_EXT_blend_color */
      { "glBlendColorEXT", (gl_function) glBlendColorEXT },

      /* GL_EXT_vertex_arrays */
      { "glVertexPointerEXT", (gl_function) glVertexPointerEXT },
      { "glNormalPointerEXT", (gl_function) glNormalPointerEXT },
      { "glColorPointerEXT", (gl_function) glColorPointerEXT },
      { "glIndexPointerEXT", (gl_function) glIndexPointerEXT },
      { "glTexCoordPointerEXT", (gl_function) glTexCoordPointerEXT },
      { "glEdgeFlagPointerEXT", (gl_function) glEdgeFlagPointerEXT },
      { "glGetPointervEXT", (gl_function) glGetPointervEXT },
      { "glArrayElementEXT", (gl_function) glArrayElementEXT },
      { "glDrawArraysEXT", (gl_function) glDrawArraysEXT },

      /* GL_EXT_texture_object */
      { "glGenTexturesEXT", (gl_function) glGenTexturesEXT },
      { "glDeleteTexturesEXT", (gl_function) glDeleteTexturesEXT },
      { "glBindTextureEXT", (gl_function) glBindTextureEXT },
      { "glPrioritizeTexturesEXT", (gl_function) glPrioritizeTexturesEXT },
      { "glAreTexturesResidentEXT", (gl_function) glAreTexturesResidentEXT },
      { "glIsTextureEXT", (gl_function) glIsTextureEXT },

      /* GL_EXT_texture3D */
      { "glTexImage3DEXT", (gl_function) glTexImage3DEXT },
      { "glTexSubImage3DEXT", (gl_function) glTexSubImage3DEXT },
      { "glCopyTexSubImage3DEXT", (gl_function) glCopyTexSubImage3DEXT },

      /* GL_ARB_multitexture */
      { "glActiveTextureARB", (gl_function) glActiveTextureARB },
      { "glClientActiveTextureARB", (gl_function) glClientActiveTextureARB },
      { "glMultiTexCoord1dARB", (gl_function) glMultiTexCoord1dARB },
      { "glMultiTexCoord1dvARB", (gl_function) glMultiTexCoord1dvARB },
      { "glMultiTexCoord1fARB", (gl_function) glMultiTexCoord1fARB },
      { "glMultiTexCoord1fvARB", (gl_function) glMultiTexCoord1fvARB },
      { "glMultiTexCoord1iARB", (gl_function) glMultiTexCoord1iARB },
      { "glMultiTexCoord1ivARB", (gl_function) glMultiTexCoord1ivARB },
      { "glMultiTexCoord1sARB", (gl_function) glMultiTexCoord1sARB },
      { "glMultiTexCoord1svARB", (gl_function) glMultiTexCoord1svARB },
      { "glMultiTexCoord2dARB", (gl_function) glMultiTexCoord2dARB },
      { "glMultiTexCoord2dvARB", (gl_function) glMultiTexCoord2dvARB },
      { "glMultiTexCoord2fARB", (gl_function) glMultiTexCoord2fARB },
      { "glMultiTexCoord2fvARB", (gl_function) glMultiTexCoord2fvARB },
      { "glMultiTexCoord2iARB", (gl_function) glMultiTexCoord2iARB },
      { "glMultiTexCoord2ivARB", (gl_function) glMultiTexCoord2ivARB },
      { "glMultiTexCoord2sARB", (gl_function) glMultiTexCoord2sARB },
      { "glMultiTexCoord2svARB", (gl_function) glMultiTexCoord2svARB },
      { "glMultiTexCoord3dARB", (gl_function) glMultiTexCoord3dARB },
      { "glMultiTexCoord3dvARB", (gl_function) glMultiTexCoord3dvARB },
      { "glMultiTexCoord3fARB", (gl_function) glMultiTexCoord3fARB },
      { "glMultiTexCoord3fvARB", (gl_function) glMultiTexCoord3fvARB },
      { "glMultiTexCoord3iARB", (gl_function) glMultiTexCoord3iARB },
      { "glMultiTexCoord3ivARB", (gl_function) glMultiTexCoord3ivARB },
      { "glMultiTexCoord3sARB", (gl_function) glMultiTexCoord3sARB },
      { "glMultiTexCoord3svARB", (gl_function) glMultiTexCoord3svARB },
      { "glMultiTexCoord4dARB", (gl_function) glMultiTexCoord4dARB },
      { "glMultiTexCoord4dvARB", (gl_function) glMultiTexCoord4dvARB },
      { "glMultiTexCoord4fARB", (gl_function) glMultiTexCoord4fARB },
      { "glMultiTexCoord4fvARB", (gl_function) glMultiTexCoord4fvARB },
      { "glMultiTexCoord4iARB", (gl_function) glMultiTexCoord4iARB },
      { "glMultiTexCoord4ivARB", (gl_function) glMultiTexCoord4ivARB },
      { "glMultiTexCoord4sARB", (gl_function) glMultiTexCoord4sARB },
      { "glMultiTexCoord4svARB", (gl_function) glMultiTexCoord4svARB },

      /* GL_INGR_blend_func_separate */
      { "glBlendFuncSeparateINGR", (gl_function) glBlendFuncSeparateINGR },

      /* GL_MESA_window_pos */
      { "glWindowPos2iMESA", (gl_function) glWindowPos2iMESA },
      { "glWindowPos2sMESA", (gl_function) glWindowPos2sMESA },
      { "glWindowPos2fMESA", (gl_function) glWindowPos2fMESA },
      { "glWindowPos2dMESA", (gl_function) glWindowPos2dMESA },
      { "glWindowPos2ivMESA", (gl_function) glWindowPos2ivMESA },
      { "glWindowPos2svMESA", (gl_function) glWindowPos2svMESA },
      { "glWindowPos2fvMESA", (gl_function) glWindowPos2fvMESA },
      { "glWindowPos2dvMESA", (gl_function) glWindowPos2dvMESA },
      { "glWindowPos3iMESA", (gl_function) glWindowPos3iMESA },
      { "glWindowPos3sMESA", (gl_function) glWindowPos3sMESA },
      { "glWindowPos3fMESA", (gl_function) glWindowPos3fMESA },
      { "glWindowPos3dMESA", (gl_function) glWindowPos3dMESA },
      { "glWindowPos3ivMESA", (gl_function) glWindowPos3ivMESA },
      { "glWindowPos3svMESA", (gl_function) glWindowPos3svMESA },
      { "glWindowPos3fvMESA", (gl_function) glWindowPos3fvMESA },
      { "glWindowPos3dvMESA", (gl_function) glWindowPos3dvMESA },
      { "glWindowPos4iMESA", (gl_function) glWindowPos4iMESA },
      { "glWindowPos4sMESA", (gl_function) glWindowPos4sMESA },
      { "glWindowPos4fMESA", (gl_function) glWindowPos4fMESA },
      { "glWindowPos4dMESA", (gl_function) glWindowPos4dMESA },
      { "glWindowPos4ivMESA", (gl_function) glWindowPos4ivMESA },
      { "glWindowPos4svMESA", (gl_function) glWindowPos4svMESA },
      { "glWindowPos4fvMESA", (gl_function) glWindowPos4fvMESA },
      { "glWindowPos4dvMESA", (gl_function) glWindowPos4dvMESA },

      /* GL_MESA_resize_buffers */
      { "glResizeBuffersMESA", (gl_function) glResizeBuffersMESA },

      /* GL_EXT_compiled_vertex_array */
      { "glLockArraysEXT", (gl_function) glLockArraysEXT },
      { "glUnlockArraysEXT", (gl_function) glUnlockArraysEXT },

      { NULL, NULL } /* end of list token */
   };
   GLuint i;

   for (i = 0; procTable[i].address; i++) {
      if (strcmp((const char *) procName, procTable[i].name) == 0)
         return procTable[i].address;
   }

   return NULL;
}
