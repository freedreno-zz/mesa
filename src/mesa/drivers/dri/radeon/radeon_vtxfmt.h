/* $XFree86$ */
/**************************************************************************

Copyright 2000, 2001 ATI Technologies Inc., Ontario, Canada, and
                     Tungsten Graphics Inc., Cedar Park, Texas.

All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
on the rights to use, copy, modify, merge, publish, distribute, sub
license, and/or sell copies of the Software, and to permit persons to whom
the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice (including the next
paragraph) shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
ATI, TUNGSTEN GRAPHICS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

/*
 * Authors:
 *   Keith Whitwell <keith@tungstengraphics.com>
 *
 */

#ifndef __RADEON_VTXFMT_H__
#define __RADEON_VTXFMT_H__

#include "radeon_context.h"



#define RADEON_MAX_PRIMS 64


/* Want to keep a cache of these around.  Each is parameterized by
 * only a single value which has only a small range.  Only expect a
 * few, so just rescan the list each time?
 */
struct dynfn {
   struct dynfn *next, *prev;
   int key;
   char *code;
};

struct dfn_lists {
   struct dynfn Vertex2f;
   struct dynfn Vertex2fv;
   struct dynfn Vertex3f;
   struct dynfn Vertex3fv;
   struct dynfn Color4ub;
   struct dynfn Color4ubv;
   struct dynfn Color3ub;
   struct dynfn Color3ubv;
   struct dynfn Color4f;
   struct dynfn Color4fv;
   struct dynfn Color3f;
   struct dynfn Color3fv;
   struct dynfn SecondaryColor3ubEXT;
   struct dynfn SecondaryColor3ubvEXT;
   struct dynfn SecondaryColor3fEXT;
   struct dynfn SecondaryColor3fvEXT;
   struct dynfn Normal3f;
   struct dynfn Normal3fv;
   struct dynfn TexCoord2f;
   struct dynfn TexCoord2fv;
   struct dynfn TexCoord1f;
   struct dynfn TexCoord1fv;
   struct dynfn MultiTexCoord2fARB;
   struct dynfn MultiTexCoord2fvARB;
   struct dynfn MultiTexCoord1fARB;
   struct dynfn MultiTexCoord1fvARB;
};

struct dfn_generators {
   struct dynfn *(*Vertex2f)( GLcontext *, int );
   struct dynfn *(*Vertex2fv)( GLcontext *, int );
   struct dynfn *(*Vertex3f)( GLcontext *, int );
   struct dynfn *(*Vertex3fv)( GLcontext *, int );
   struct dynfn *(*Color4ub)( GLcontext *, int );
   struct dynfn *(*Color4ubv)( GLcontext *, int );
   struct dynfn *(*Color3ub)( GLcontext *, int );
   struct dynfn *(*Color3ubv)( GLcontext *, int );
   struct dynfn *(*Color4f)( GLcontext *, int );
   struct dynfn *(*Color4fv)( GLcontext *, int );
   struct dynfn *(*Color3f)( GLcontext *, int );
   struct dynfn *(*Color3fv)( GLcontext *, int );
   struct dynfn *(*SecondaryColor3ubEXT)( GLcontext *, int );
   struct dynfn *(*SecondaryColor3ubvEXT)( GLcontext *, int );
   struct dynfn *(*SecondaryColor3fEXT)( GLcontext *, int );
   struct dynfn *(*SecondaryColor3fvEXT)( GLcontext *, int );
   struct dynfn *(*Normal3f)( GLcontext *, int );
   struct dynfn *(*Normal3fv)( GLcontext *, int );
   struct dynfn *(*TexCoord2f)( GLcontext *, int );
   struct dynfn *(*TexCoord2fv)( GLcontext *, int );
   struct dynfn *(*TexCoord1f)( GLcontext *, int );
   struct dynfn *(*TexCoord1fv)( GLcontext *, int );
   struct dynfn *(*MultiTexCoord2fARB)( GLcontext *, int );
   struct dynfn *(*MultiTexCoord2fvARB)( GLcontext *, int );
   struct dynfn *(*MultiTexCoord1fARB)( GLcontext *, int );
   struct dynfn *(*MultiTexCoord1fvARB)( GLcontext *, int );
};


struct radeon_prim {
   GLuint start;
   GLuint end;
   GLuint prim;
};

struct radeon_vbinfo {
   GLenum *prim;		/* &ctx->Driver.CurrentExecPrimitive */
   GLuint primflags;
   GLboolean enabled;		/* RADEON_NO_VTXFMT//RADEON_NO_TCL env vars */
   GLboolean installed;
   GLboolean fell_back;
   GLboolean recheck;
   GLint initial_counter;
   GLint nrverts;
   GLuint vertex_format;

   GLuint installed_vertex_format;
   GLuint installed_color_3f_sz;

   struct radeon_prim primlist[RADEON_MAX_PRIMS];
   int nrprims;

   struct dfn_lists dfn_cache;
   struct dfn_generators codegen;
   GLvertexformat vtxfmt;
};

struct radeon_vb {
   /* Keep these first: referenced from codegen templates:
    */
   GLint counter, initial_counter;
   GLint *dmaptr;
   void (*notify)( void );
   GLint vertex_size;

   /* A maximum total of 15 elements per vertex:  3 floats for position, 3
    * floats for normal, 4 floats for color, 4 bytes for secondary color,
    * 2 floats for each texture unit (4 floats total).
    * 
    * As soon as the 3rd TMU is supported or cube maps (or 3D textures) are
    * supported, this value will grow.
    * 
    * The position data is never actually stored here, so 3 elements could be
    * trimmed out of the buffer.
    */
   union { float f; int i; radeon_color_t color; } vertex[15];

   GLfloat *normalptr;
   GLfloat *floatcolorptr;
   radeon_color_t *colorptr;
   GLfloat *floatspecptr;
   radeon_color_t *specptr;
   GLfloat *texcoordptr[2];

   GLcontext *context;		/* current context : Single thread only! */
};


extern struct radeon_vb vb;


extern void radeonVtxfmtUpdate( GLcontext *ctx );
extern void radeonVtxfmtInit( GLcontext *ctx );
extern void radeonVtxfmtInvalidate( GLcontext *ctx );
extern void radeonVtxfmtDestroy( GLcontext *ctx );
extern void radeonVtxfmtInitChoosers( GLvertexformat *vfmt );

extern void radeonVtxfmtMakeCurrent( GLcontext *ctx );
extern void radeonVtxfmtUnbindContext( GLcontext *ctx );

extern void radeon_copy_to_current( GLcontext *ctx );

#define DFN( FUNC, CACHE)				\
do {							\
   char *start = (char *)&FUNC;				\
   char *end = (char *)&FUNC##_end;			\
   insert_at_head( &CACHE, dfn );			\
   dfn->key = key;					\
   dfn->code = ALIGN_MALLOC( end - start, 16 );		\
   memcpy (dfn->code, start, end - start);		\
}							\
while ( 0 )

#define FIXUP( CODE, OFFSET, CHECKVAL, NEWVAL )	\
do {						\
   int *icode = (int *)(CODE+OFFSET);		\
   assert (*icode == CHECKVAL);			\
   *icode = (int)NEWVAL;			\
} while (0)


/* Useful for figuring out the offsets:
 */
#define FIXUP2( CODE, OFFSET, CHECKVAL, NEWVAL )		\
do {								\
   while (*(int *)(CODE+OFFSET) != CHECKVAL) OFFSET++;		\
   fprintf(stderr, "%s/%d CVAL %x OFFSET %d VAL %x\n", __FUNCTION__,	\
	   __LINE__, CHECKVAL, OFFSET, (int)(NEWVAL));			\
   *(int *)(CODE+OFFSET) = (int)(NEWVAL);				\
   OFFSET += 4;							\
} while (0)

/* 
 */
void radeonInitCodegen( struct dfn_generators *gen );
void radeonInitX86Codegen( struct dfn_generators *gen );
void radeonInitSSECodegen( struct dfn_generators *gen );



/* Defined in radeon_vtxfmt_x86.c
 */
struct dynfn *radeon_makeX86Vertex2f( GLcontext *, int );
struct dynfn *radeon_makeX86Vertex2fv( GLcontext *, int );
struct dynfn *radeon_makeX86Vertex3f( GLcontext *, int );
struct dynfn *radeon_makeX86Vertex3fv( GLcontext *, int );
struct dynfn *radeon_makeX86Color4ub( GLcontext *, int );
struct dynfn *radeon_makeX86Color4ubv( GLcontext *, int );
struct dynfn *radeon_makeX86Color3ub( GLcontext *, int );
struct dynfn *radeon_makeX86Color3ubv( GLcontext *, int );
struct dynfn *radeon_makeX86Color4f( GLcontext *, int );
struct dynfn *radeon_makeX86Color4fv( GLcontext *, int );
struct dynfn *radeon_makeX86Color3f( GLcontext *, int );
struct dynfn *radeon_makeX86Color3fv( GLcontext *, int );
struct dynfn *radeon_makeX86SecondaryColor3ubEXT( GLcontext *, int );
struct dynfn *radeon_makeX86SecondaryColor3ubvEXT( GLcontext *, int );
struct dynfn *radeon_makeX86SecondaryColor3fEXT( GLcontext *, int );
struct dynfn *radeon_makeX86SecondaryColor3fvEXT( GLcontext *, int );
struct dynfn *radeon_makeX86Normal3f( GLcontext *, int );
struct dynfn *radeon_makeX86Normal3fv( GLcontext *, int );
struct dynfn *radeon_makeX86TexCoord2f( GLcontext *, int );
struct dynfn *radeon_makeX86TexCoord2fv( GLcontext *, int );
struct dynfn *radeon_makeX86TexCoord1f( GLcontext *, int );
struct dynfn *radeon_makeX86TexCoord1fv( GLcontext *, int );
struct dynfn *radeon_makeX86MultiTexCoord2fARB( GLcontext *, int );
struct dynfn *radeon_makeX86MultiTexCoord2fvARB( GLcontext *, int );
struct dynfn *radeon_makeX86MultiTexCoord1fARB( GLcontext *, int );
struct dynfn *radeon_makeX86MultiTexCoord1fvARB( GLcontext *, int );


#endif
