/* $XFree86$ */
/**************************************************************************

Copyright 2002 Tungsten Graphics Inc., Cedar Park, Texas.

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
TUNGSTEN GRAPHICS AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/

/*
 * Authors:
 *   Keith Whitwell <keith@tungstengraphics.com>
 */


/* Close off the last primitive, execute the buffer, restart the
 * primitive.  
 */
static void _tnl_wrap_buffers( GLcontext *ctx )
{
   if (ctx->Driver.CurrentExecPrimitive != GL_POLYGON+1) {
      GLint i = tnl->vtx.prim_count - 1;
      assert(i >= 0);
      tnl->vtx.prim[i].count = ((tnl->vtx.initial_counter - tnl->vtx.counter) - 
				tnl->vtx.prim[i].start);
   }

   /* Execute the buffer and save copied vertices.
    */
   _tnl_flush_immediate( ctx );

   /* Emit a glBegin to start the new list.
    */
   assert(tnl->vtx.prim_count == 0);

   if (ctx->Driver.CurrentExecPrimitive != GL_POLYGON+1) {
      tnl->vtx.prim[0].mode = ctx->Driver.CurrentExecPrimitive;
      tnl->vtx.prim[0].start = 0;
      tnl->vtx.prim[0].count = -1;
      tnl->vtx.prim_count++;
   }
}


static void _tnl_wrap_filled_vertex( GLcontext *ctx )
{
   int i;

   /* Run pipeline on current vertices, copy wrapped vertices
    * to tnl->copied_verts.
    */
   _tnl_wrap_buffers( ctx );
   
   /* Copy stored stored vertices to start of new list. 
    */
   assert(tnl->vtx.counter > tnl->copied_verts.nr);

   for (i = 0 ; i < tnl->copied_verts.nr ; i++) {
      memcpy( tnl->vtx.vbptr, data, tnl->vtx.vertex_size * sizeof(GLfloat));
      tnl->vtx.vbptr += tnl->vtx.vertex_size;
      data += tnl->vtx.vertex_size;
      tnl->vtx.counter--;
   }

   tnl->copied_verts.nr = 0;
}

static void tnl_copy_to_current( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx); 

   for (i = _TNL_ATTRIB_POS+1 ; i < _TNL_ATTRIB_EVALFLAG ; i++) 
      switch (tnl->vtx.attrib[i].sz) {
      case 4: tnl->vtx.attrib[i].current[3] = tnl->vtx.vbptr[i].fi[3].f;
      case 3: tnl->vtx.attrib[i].current[2] = tnl->vtx.vbptr[i].fi[2].f;
      case 2: tnl->vtx.attrib[i].current[1] = tnl->vtx.vbptr[i].fi[1].f;
      case 1: tnl->vtx.attrib[i].current[0] = tnl->vtx.vbptr[i].fi[0].f;
	 break;
      }

   /* Edgeflag and Index require special treatment:
    */
   if (tnl->vtx.attrib[_TNL_ATTRIB_INDEX].sz) 
      ctx->Current.Index = tnl->vtx.vbptr[_TNL_ATTRIB_INDEX];

   if (tnl->vtx.attrib[_TNL_ATTRIB_EDGEFLAG].sz) 
      ctx->Current.Edgeflag = (tnl->vtx.vbptr[_TNL_ATTRIB_EDGEFLAG] == 1.0);
   

   ctx->Driver.NeedFlush &= ~FLUSH_UPDATE_CURRENT;
}


static void tnl_copy_from_current( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx); 

   for (i = _TNL_ATTRIB_POS+1 ; i < _TNL_ATTRIB_EVALFLAG ; i++) 
      switch (tnl->vtx.attrib[i].sz) {
      case 4: tnl->vtx.vbptr[i].fi[3].f = tnl->vtx.attrib[i].current[3];
      case 3: tnl->vtx.vbptr[i].fi[2].f = tnl->vtx.attrib[i].current[2];
      case 2: tnl->vtx.vbptr[i].fi[1].f = tnl->vtx.attrib[i].current[1];
      case 1: tnl->vtx.vbptr[i].fi[0].f = tnl->vtx.attrib[i].current[0];
	 break;
      }

   /* Edgeflag and Index require special treatment:
    */
   if (tnl->vtx.attrib[_TNL_ATTRIB_INDEX].sz) 
      tnl->vtx.vbptr[_TNL_ATTRIB_INDEX][0] = ctx->Current.Index;

   if (tnl->vtx.attrib[_TNL_ATTRIB_EDGEFLAG].sz) 
      tnl->vtx.vbptr[_TNL_ATTRIB_EDGEFLAG][0] = (GLfloat)ctx->Current.Edgeflag;


   ctx->Driver.NeedFlush |= FLUSH_UPDATE_CURRENT;
}





/* Flush existing data, set new attrib size, replay copied vertices.
 */ 
static void _tnl_wrap_upgrade_vertex( GLcontext *ctx, 
				      GLuint attr,
				      GLuint newsz )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx); 
   GLuint oldsz;
   GLint diff;

   /* Run pipeline on current vertices, copy wrapped vertices
    * to tnl->copied_verts.
    */
   _tnl_wrap_buffers( ctx );

   /* Do a COPY_TO_CURRENT to ensure back-copying works for the case
    * when the attribute already exists in the vertex and is having
    * its size increased.  
    */
   _tnl_copy_to_current( ctx );

   /* Fix up sizes:
    */
   oldsz = tnl->vtx.attrib[attr].sz;
   tnl->vtx.attrib[attr].sz = newsz;

   tnl->vtx.vertex_size += newsz - oldsz;
   tnl->vtx.counter = tnl->vtx.vbsize / tnl->vtx.vertex_size;
   tnl->vtx.initial_counter = tnl->vtx.counter;
   tnl->vtx.vbptr = tnl->vtx.buffer;


   /* Recalculate all the attrptr[] values
    */
   for (i = 0, tmp = tnl->vtx.vertex ; i < TNL_MAX_ATTRIB ; i++) {
      if (tnl->vtx.attrib[i].sz) {
	 tnl->vtx.attrptr[i] = tmp;
	 tmp += tnl->vtx.attrib[i].sz;
      }
      else 
	 tnl->vtx.attrptr[i] = 0; /* will not be dereferenced */
   }

   /* Copy from current to repopulate the vertex with correct values.
    */
   _tnl_copy_from_current( ctx );

   /* Replay stored vertices to translate them
    * to new format here.
    *
    * -- No need to replay - just copy piecewise
    */
   {
      GLfloat *data = tnl->copied_verts.buffer;
      GLfloat *tmp = tnl->vtx.buffer;

      for (i = 0 ; i < tnl->copied_verts.nr ; i++) {
	 for (j = 1 ; j < TNL_MAX_ATTRIB ; j++) {
	    if (tnl->vtx.attrib[j].sz) {
	       if (j == attr) {
		  COPY_SZ_4V( tmp, newsz, tnl->vtx.attrib[attr].current );
		  COPY_SZ_4V( tmp, oldsz, data );
		  data += oldsz;
		  tmp += newsz;
	       }
	       else {
		  GLuint sz = tnl->vtx.attrib[j].sz;
		  COPY_SZ_4V( tmp, sz, data );
		  tmp += sz;
		  data += sz;
	       }
	    }
	 }
      }
   }

   tnl->vtx.vbptr = tmp;
   tnl->vtx.counter -= tnl->copied_verts.nr;
   tnl->copied_verts.nr = 0;
}


static void _tnl_fixup_vertex( )
{
   static float id[4] = { 0, 0, 0, 1 };
   int i;

   if (tnl->vtx.attrib_sz[attr] < sz) {
      /* New size is larger.  Need to flush existing vertices and get
       * an enlarged vertex format.
       */
      _tnl_wrap_upgrade_vertex( tnl, attr, sz );
   }
   else if (tnl->vtx.attrib_sz[attr] > sz) {
      /* New size is smaller - just need to fill in some
       * zeros.  Don't need to flush or wrap.
       */
      for (i = sz ; i <= tnl->vtx.attrib_sz[attr] ; i++)
	 tnl->vtx.attrptr[attr].fi[i-1].f = id[i-1];
   }
}


/* Helper function for 'CHOOSE' macro.  Do what's necessary when an
 * entrypoint is called for the first time.
 */
static void *do_choose( GLuint attr, GLuint sz, 
			void (*fallback_attr_func)( const GLfloat *),
			const GLfloat *v )
{ 
   GET_CURRENT_CONTEXT( ctx ); 
   TNLcontext *tnl = TNL_CONTEXT(ctx); 

   if (tnl->vtx.attrib_sz[attr] != sz)
      _tnl_fixup_vertex( tnl, attr, sz );
 
   /* Does this belong here?  Necessitates resetting vtxfmt on each
    * flush (otherwise flags won't get reset afterwards).
    */
   if (attr == 0)
      ctx->Driver.NeedFlush |= FLUSH_STORED_VERTICES;
   else
      ctx->Driver.NeedFlush |= FLUSH_UPDATE_CURRENT;

   /* Reset any active pointers for this attribute 
    */
   for (i = 1; i <= 4; i++)
      tnl->vtx.tabfv[attr][i-1] = tnl->vtx.initial_tabfv[attr][i-1];

   /* Update the secondary dispatch table with the new function
    */
   tnl->vtx.tabfv[attr][sz-1] = fallback_attr_func;


   (*fallback_attr_func)(v);
}

static void do_flush( void ) 
{
   GET_CURRENT_CONTEXT( ctx ); 
   _tnl_FlushVertices( ctx, FLUSH_STORED_VERTICES );
}


/* Versions of all the entrypoints for situations where codegen isn't
 * available.  
 *
 * Note: Only one size for each attribute may be active at once.
 * Eg. if Color3f is installed/active, then Color4f may not be, even
 * if the vertex actually contains 4 color coordinates.  This is
 * because the 3f version won't otherwise set color[3] to 1.0 -- this
 * is the job of the chooser function when switching between Color4f
 * and Color3f.
 */
#define ATTRFV( ATTR, N )			\
static void attrib_##ATTR##_##N( const GLfloat *v )	\
{							\
   GET_CURRENT_CONTEXT( ctx );				\
   TNLcontext *tnl = TNL_CONTEXT(ctx);			\
							\
   if ((ATTR) == 0) {					\
      int i;						\
							\
      if (N>0) tnl->vtx.vbptr[0] = (V)[0];		\
      if (N>1) tnl->vtx.vbptr[1] = (V)[1];		\
      if (N>2) tnl->vtx.vbptr[2] = (V)[2];		\
      if (N>3) tnl->vtx.vbptr[3] = (V)[3];		\
							\
      for (i = N; i < tnl->vtx.vertex_size; i++)	\
	 tnl->vtx.vbptr[i] = tnl->vtx.vertex[i];	\
							\
      tnl->vtx.vbptr += tnl->vtx.vertex_size;		\
							\
      if (--tnl->vtx.counter == 0)			\
	 do_flush();					\
   }							\
   else {						\
      TNLfi *dest = tnl->vtx.attrptr[ATTR];		\
      if (N>0) dest[0] = (V)[0];			\
      if (N>1) dest[1] = (V)[1];			\
      if (N>2) dest[2] = (V)[2];			\
      if (N>3) dest[3] = (V)[3];			\
   }							\
}

#define CHOOSE( ATTR, N )				\
static void choose_##ATTR##_##N( const GLfloat *v )	\
{							\
   do_choose(ATTR, N, attrib_##ATTR##_##N, v);		\
}

#define ATTRS( ATTRIB )				\
   ATTRFV( ATTRIB, 1 )				\
   ATTRFV( ATTRIB, 2 )				\
   ATTRFV( ATTRIB, 3 )				\
   ATTRFV( ATTRIB, 4 )				\
   CHOOSE( ATTRIB, 1 )				\
   CHOOSE( ATTRIB, 2 )				\
   CHOOSE( ATTRIB, 3 )				\
   CHOOSE( ATTRIB, 4 )				\


/* Generate a lot of functions.  These are the actual worker
 * functions, which are equivalent to those generated via codegen
 * elsewhere.
 */
ATTRS( 0 )
ATTRS( 1 )
ATTRS( 2 )
ATTRS( 3 )
ATTRS( 4 )
ATTRS( 5 )
ATTRS( 6 )
ATTRS( 7 )
ATTRS( 8 )
ATTRS( 9 )
ATTRS( 10 )
ATTRS( 11 )
ATTRS( 12 )
ATTRS( 13 )
ATTRS( 14 )
ATTRS( 15 )


/* These can be made efficient with codegen.  Further, by adding more
 * logic to do_choose(), the double-dispatch for legacy entrypoints
 * like glVertex3f() can be removed.
 */
#define DISPATCH_ATTRFV( ATTR, COUNT, P )	\
do {						\
   GET_CURRENT_CONTEXT( ctx ); 			\
   TNLcontext *tnl = TNL_CONTEXT(ctx); 		\
   tnl->vtx.tabfv[ATTR][COUNT-1]( P );		\
} while (0)

#define DISPATCH_ATTR1FV( ATTR, V ) DISPATCH_ATTRFV( ATTR, 1, V )
#define DISPATCH_ATTR2FV( ATTR, V ) DISPATCH_ATTRFV( ATTR, 2, V )
#define DISPATCH_ATTR3FV( ATTR, V ) DISPATCH_ATTRFV( ATTR, 3, V )
#define DISPATCH_ATTR4FV( ATTR, V ) DISPATCH_ATTRFV( ATTR, 4, V )

#define DISPATCH_ATTR1F( ATTR, S ) DISPATCH_ATTRFV( ATTR, 1, &(S) )

#define DISPATCH_ATTR2F( ATTR, S,T ) 		\
do { 						\
   GLfloat v[2]; 				\
   v[0] = S; v[1] = T;				\
   DISPATCH_ATTR2FV( ATTR, v );			\
} while (0)
#define DISPATCH_ATTR3F( ATTR, S,T,R ) 		\
do { 						\
   GLfloat v[3]; 				\
   v[0] = S; v[1] = T; v[2] = R;		\
   DISPATCH_ATTR3FV( ATTR, v );			\
} while (0)
#define DISPATCH_ATTR4F( ATTR, S,T,R,Q )	\
do { 						\
   GLfloat v[4]; 				\
   v[0] = S; v[1] = T; v[2] = R; v[3] = Q;	\
   DISPATCH_ATTR4FV( ATTR, v );			\
} while (0)


static void enum_error( void )
{
   GET_CURRENT_CONTEXT( ctx );
   _mesa_error( ctx, GL_INVALID_ENUM, __FUNCTION__ );
}

static void op_error( void )
{
   GET_CURRENT_CONTEXT( ctx );
   _mesa_error( ctx, GL_INVALID_OPERATION, __FUNCTION__ );
}


static void _tnl_Vertex2f( GLfloat x, GLfloat y )
{
   DISPATCH_ATTR2F( _TNL_ATTRIB_POS, x, y );
}

static void _tnl_Vertex2fv( const GLfloat *v )
{
   DISPATCH_ATTR2FV( _TNL_ATTRIB_POS, v );
}

static void _tnl_Vertex3f( GLfloat x, GLfloat y, GLfloat z )
{
   DISPATCH_ATTR3F( _TNL_ATTRIB_POS, x, y, z );
}

static void _tnl_Vertex3fv( const GLfloat *v )
{
   DISPATCH_ATTR3FV( _TNL_ATTRIB_POS, v );
}

static void _tnl_Vertex4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
   DISPATCH_ATTR4F( _TNL_ATTRIB_POS, x, y, z, w );
}

static void _tnl_Vertex4fv( const GLfloat *v )
{
   DISPATCH_ATTR4FV( _TNL_ATTRIB_POS, v );
}

static void _tnl_TexCoord1f( GLfloat x )
{
   DISPATCH_ATTR1F( _TNL_ATTRIB_TEX0, x );
}

static void _tnl_TexCoord1fv( const GLfloat *v )
{
   DISPATCH_ATTR1FV( _TNL_ATTRIB_TEX0, v );
}

static void _tnl_TexCoord2f( GLfloat x, GLfloat y )
{
   DISPATCH_ATTR2F( _TNL_ATTRIB_TEX0, x, y );
}

static void _tnl_TexCoord2fv( const GLfloat *v )
{
   DISPATCH_ATTR2FV( _TNL_ATTRIB_TEX0, v );
}

static void _tnl_TexCoord3f( GLfloat x, GLfloat y, GLfloat z )
{
   DISPATCH_ATTR3F( _TNL_ATTRIB_TEX0, x, y, z );
}

static void _tnl_TexCoord3fv( const GLfloat *v )
{
   DISPATCH_ATTR3FV( _TNL_ATTRIB_TEX0, v );
}

static void _tnl_TexCoord4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
   DISPATCH_ATTR4F( _TNL_ATTRIB_TEX0, x, y, z, w );
}

static void _tnl_TexCoord4fv( const GLfloat *v )
{
   DISPATCH_ATTR4FV( _TNL_ATTRIB_TEX0, v );
}

static void _tnl_Normal3f( GLfloat x, GLfloat y, GLfloat z )
{
   DISPATCH_ATTR3F( _TNL_ATTRIB_NORMAL, x, y, z );
}

static void _tnl_Normal3fv( const GLfloat *v )
{
   DISPATCH_ATTR3FV( _TNL_ATTRIB_NORMAL, v );
}

static void _tnl_FogCoordfEXT( GLfloat x )
{
   DISPATCH_ATTR1F( _TNL_ATTRIB_FOG, x );
}

static void _tnl_FogCoordfvEXT( const GLfloat *v )
{
   DISPATCH_ATTR1FV( _TNL_ATTRIB_FOG, v );
}

static void _tnl_Color3f( GLfloat x, GLfloat y, GLfloat z )
{
   DISPATCH_ATTR3F( _TNL_ATTRIB_COLOR0, x, y, z );
}

static void _tnl_Color3fv( const GLfloat *v )
{
   DISPATCH_ATTR3FV( _TNL_ATTRIB_COLOR0, v );
}

static void _tnl_Color4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w )
{
   DISPATCH_ATTR4F( _TNL_ATTRIB_COLOR0, x, y, z, w );
}

static void _tnl_Color4fv( const GLfloat *v )
{
   DISPATCH_ATTR4FV( _TNL_ATTRIB_COLOR0, v );
}

static void _tnl_SecondaryColor3fEXT( GLfloat x, GLfloat y, GLfloat z )
{
   DISPATCH_ATTR3F( _TNL_ATTRIB_COLOR1, x, y, z );
}

static void _tnl_SecondaryColor3fvEXT( const GLfloat *v )
{
   DISPATCH_ATTR3FV( _TNL_ATTRIB_COLOR1, v );
}

static void _tnl_MultiTexCoord1f( GLenum target, GLfloat x  )
{
   GLuint attr = (target & 0x7) + _TNL_ATTRIB_TEX0;
   DISPATCH_ATTR1F( attr, x );
}

static void _tnl_MultiTexCoord1fv( GLenum target, const GLfloat *v )
{
   GLuint attr = (target & 0x7) + _TNL_ATTRIB_TEX0;
   DISPATCH_ATTR1FV( attr, v );
}

static void _tnl_MultiTexCoord2f( GLenum target, GLfloat x, GLfloat y )
{
   GLuint attr = (target & 0x7) + _TNL_ATTRIB_TEX0;
   DISPATCH_ATTR2F( attr, x, y );
}

static void _tnl_MultiTexCoord2fv( GLenum target, const GLfloat *v )
{
   GLuint attr = (target & 0x7) + _TNL_ATTRIB_TEX0;
   DISPATCH_ATTR2FV( attr, v );
}

static void _tnl_MultiTexCoord3f( GLenum target, GLfloat x, GLfloat y,
				    GLfloat z)
{
   GLuint attr = (target & 0x7) + _TNL_ATTRIB_TEX0;
   DISPATCH_ATTR3F( attr, x, y, z );
}

static void _tnl_MultiTexCoord3fv( GLenum target, const GLfloat *v )
{
   GLuint attr = (target & 0x7) + _TNL_ATTRIB_TEX0;
   DISPATCH_ATTR3FV( attr, v );
}

static void _tnl_MultiTexCoord4f( GLenum target, GLfloat x, GLfloat y,
				    GLfloat z, GLfloat w )
{
   GLuint attr = (target & 0x7) + _TNL_ATTRIB_TEX0;
   DISPATCH_ATTR4F( attr, x, y, z, w );
}

static void _tnl_MultiTexCoord4fv( GLenum target, const GLfloat *v )
{
   GLuint attr = (target & 0x7) + _TNL_ATTRIB_TEX0;
   DISPATCH_ATTR4FV( attr, v );
}

static void _tnl_VertexAttrib1fNV( GLuint index, GLfloat x )
{
   if (index >= _TNL_ATTRIB_POS && index < _TNL_ATTRIB_MAX)
      DISPATCH_ATTR1F( index, x );
   else
      enum_error(); 
}

static void _tnl_VertexAttrib1fvNV( GLuint index, const GLfloat *v )
{
   if (index >= _TNL_ATTRIB_POS && index < _TNL_ATTRIB_MAX)
      DISPATCH_ATTR1FV( index, v );
   else
      enum_error();
}

static void _tnl_VertexAttrib2fNV( GLuint index, GLfloat x, GLfloat y )
{
   if (index >= _TNL_ATTRIB_POS && index < _TNL_ATTRIB_MAX)
      DISPATCH_ATTR2F( index, x, y );
   else
      enum_error();
}

static void _tnl_VertexAttrib2fvNV( GLuint index, const GLfloat *v )
{
   if (index >= _TNL_ATTRIB_POS && index < _TNL_ATTRIB_MAX)
      DISPATCH_ATTR2FV( index, v );
   else
      enum_error();
}

static void _tnl_VertexAttrib3fNV( GLuint index, GLfloat x, GLfloat y, 
				  GLfloat z )
{
   if (index >= _TNL_ATTRIB_POS && index < _TNL_ATTRIB_MAX)
      DISPATCH_ATTR3F( index, x, y, z );
   else
      enum_error();
}

static void _tnl_VertexAttrib3fvNV( GLuint index, const GLfloat *v )
{
   if (index >= _TNL_ATTRIB_POS && index < _TNL_ATTRIB_MAX)
      DISPATCH_ATTR3FV( index, v );
   else
      enum_error();
}

static void _tnl_VertexAttrib4fNV( GLuint index, GLfloat x, GLfloat y,
				  GLfloat z, GLfloat w )
{
   if (index >= _TNL_ATTRIB_POS && index < _TNL_ATTRIB_MAX)
      DISPATCH_ATTR4F( index, x, y, z, w );
   else
      enum_error();
}

static void _tnl_VertexAttrib4fvNV( GLuint index, const GLfloat *v )
{
   if (index >= _TNL_ATTRIB_POS && index < _TNL_ATTRIB_MAX)
      DISPATCH_ATTR4FV( index, v );
   else
      enum_error();
}


/* Materials:  
 * 
 * These are treated as per-vertex attributes, at indices above where
 * the NV_vertex_program leaves off.  There are a lot of good things
 * about treating materials this way.  
 *
 * However: I don't want to double the number of generated functions
 * just to cope with this, so I unroll the 'C' varients of CHOOSE and
 * ATTRF into this function, and dispense with codegen and
 * second-level dispatch.
 *
 * There is no aliasing of material attributes with other entrypoints.
 */
#define MAT_ATTR( A, N, params )			\
do {							\
   if (tnl->vtx.attrib_sz[A] != N) {			\
      tnl_fixup_vertex( ctx, A, N );			\
   }							\
							\
   {							\
      TNLfi *dest = tnl->vtx.attrptr[A];	      	\
      if (N>0) dest[0].f = params[0];			\
      if (N>1) dest[1].f = params[1];			\
      if (N>2) dest[2].f = params[2];			\
      if (N>3) dest[3].f = params[3];			\
      ctx->Driver.NeedFlush |= FLUSH_UPDATE_CURRENT;	\
   }							\
} while (0)


#define MAT( ATTR, N, face, params )			\
do {							\
   if (face != GL_BACK)					\
      MAT_ATTR( ATTR, N, params ); /* front */		\
   if (face != GL_FRONT)				\
      MAT_ATTR( ATTR + 1, N, params ); /* back */	\
} while (0)


/* NOTE: Have to remove/deal-with colormaterial crossovers, probably
 * later on - in the meantime just store everything.  
 */
static void _tnl_Materialfv( GLenum face, GLenum pname, 
			       const GLfloat *params )
{
   GET_CURRENT_CONTEXT( ctx ); 
   TNLcontext *tnl = TNL_CONTEXT(ctx);

   switch (face) {
   case GL_FRONT:
   case GL_BACK:
   case GL_FRONT_AND_BACK:
      break;
      
   default:
      _mesa_error( ctx, GL_INVALID_ENUM, __FUNCTION__);
      return;
   }

   switch (pname) {
   case GL_EMISSION:
      MAT( _TNL_ATTRIB_MAT_FRONT_EMISSION, 4, face, params );
      break;
   case GL_AMBIENT:
      MAT( _TNL_ATTRIB_MAT_FRONT_AMBIENT, 4, face, params );
      break;
   case GL_DIFFUSE:
      MAT( _TNL_ATTRIB_MAT_FRONT_DIFFUSE, 4, face, params );
      break;
   case GL_SPECULAR:
      MAT( _TNL_ATTRIB_MAT_FRONT_SPECULAR, 4, face, params );
      break;
   case GL_SHININESS:
      MAT( _TNL_ATTRIB_MAT_FRONT_SHININESS, 1, face, params );
      break;
   case GL_COLOR_INDEXES:
      MAT( _TNL_ATTRIB_MAT_FRONT_INDEXES, 3, face, params );
      break;
   case GL_AMBIENT_AND_DIFFUSE:
      MAT( _TNL_ATTRIB_MAT_FRONT_AMBIENT, 4, face, params );
      MAT( _TNL_ATTRIB_MAT_FRONT_DIFFUSE, 4, face, params );
      break;
   default:
      _mesa_error( ctx, GL_INVALID_ENUM, __FUNCTION__ );
      return;
   }
}


#define IDX_ATTR( A, IDX )				\
do {							\
   GET_CURRENT_CONTEXT( ctx );				\
   TNLcontext *tnl = TNL_CONTEXT(ctx);			\
							\
   if (tnl->vtx.attrib_sz[A] != 1) {			\
      tnl_fixup_vertex( ctx, A, 1 );			\
   }							\
							\
   {							\
      TNLfi *dest = tnl->vtx.attrptr[A];		\
      dest[0].ui = IDX;				\
      ctx->Driver.NeedFlush |= FLUSH_UPDATE_CURRENT;	\
   }							\
} while (0)


static void _tnl_EdgeFlag( GLboolean b )
{
   IDX_ATTR( _TNL_ATTRIB_EDGEFLAG, (GLfloat)b );
}

static void _tnl_EdgeFlagv( const GLboolean *v )
{
   IDX_ATTR( _TNL_ATTRIB_EDGEFLAG, (GLfloat)v[0] );
}

static void _tnl_Indexf( GLfloat f )
{
   IDX_ATTR( _TNL_ATTRIB_INDEX, f );
}

static void _tnl_Indexfv( const GLfloat *v )
{
   IDX_ATTR( _TNL_ATTRIB_INDEX, v[0] );
}


/* EvalCoord 
 *
 * Set a flag to indicate that this vertex is an eval point/coordinate.
 * Emit the vertex with the eval point/coord in attrib 0 (POS).
 * Set the flag back to zero.
 */
static void evalcoord( GLfloat a, GLfloat b, GLuint type ) 
{
   /* Do this with a 'CHOOSE()' function */
   {
      GET_CURRENT_CONTEXT( ctx );
      TNLcontext *tnl = TNL_CONTEXT(ctx); 

      if (tnl->eval.EvalNewState & _NEW_EVAL)
	 _tnl_update_eval( ctx );

      if (type == TNL_EVAL_COORD1 && !tnl->Eval._ActiveMap1Attrib[0].map)
	 return;
      if (type == TNL_EVAL_COORD2 && !tnl->Eval._ActiveMap2Attrib[0].map)
	 return;
   }
    
   IDX_ATTR( _TNL_ATTRIB_EVALFLAG, type );
   ATTR2F( _TNL_ATTRIB_POS, a, b );
   IDX_ATTR( _TNL_ATTRIB_EVALFLAG, TNL_EVAL_NONE );
}


static void _tnl_EvalCoord1f( GLfloat u )
{
   evalcoord( u, 0, TNL_EVAL_COORD1 );
}

static void _tnl_EvalCoord1fv( const GLfloat *v )
{
   evalcoord( v[0], 0, TNL_EVAL_COORD1 );
}

static void _tnl_EvalCoord2f( GLfloat u, GLfloat v )
{
   evalcoord( u, v, TNL_EVAL_COORD2 );
}

static void _tnl_EvalCoord2fv( const GLfloat *v )
{
   evalcoord( v[0], v[1], TNL_EVAL_COORD2 );
}

static void _tnl_EvalPoint1( GLint i )
{
   GET_CURRENT_CONTEXT(ctx);
   GLfloat du = ctx->Eval.MapGrid1du;
   GLfloat u1 = ctx->Eval.MapGrid1u1;
   glEvalCoord1f( i * du + u1 );
}

static void _tnl_EvalPoint2( GLint i, GLint j )
{
   GET_CURRENT_CONTEXT(ctx);
   GLfloat du = ctx->Eval.MapGrid1du;
   GLfloat u1 = ctx->Eval.MapGrid1u1;
   GLfloat dv = ctx->Eval.MapGrid1dv;
   GLfloat v1 = ctx->Eval.MapGrid1v1;
   glEvalCoord2f( i * du + u1, j * dv + v1 );
}


/* Build a list of primitives on the fly.  Keep
 * ctx->Driver.CurrentExecPrimitive uptodate as well.
 */
static void _tnl_Begin( GLenum mode )
{
   GET_CURRENT_CONTEXT( ctx ); 

   if (ctx->Driver.CurrentExecPrimitive == GL_POLYGON+1) {
      TNLcontext *tnl = TNL_CONTEXT(ctx); 
      int i = tnl->vtx.prim_count++;

      tnl->vtx.prim[i].mode = mode | PRIM_BEGIN;
      tnl->vtx.prim[i].start = tnl->vtx.initial_counter - tnl->vtx.counter;
      tnl->vtx.prim[i].nr = 0;

      ctx->Driver.CurrentExecPrimitive = mode;
   }
   else 
      _mesa_error( ctx, GL_INVALID_OPERATION, __FUNCTION__ );
      
}

static void _tnl_End( void )
{
   GET_CURRENT_CONTEXT( ctx ); 

   if (ctx->Driver.CurrentExecPrimitive != GL_POLYGON+1) {
      TNLcontext *tnl = TNL_CONTEXT(ctx); 
      int idx = tnl->vtx.initial_counter - tnl->vtx.counter;
      int i = tnl->vtx.prim_count - 1;

      tnl->vtx.prim[i].mode |= PRIM_END; 
      tnl->vtx.prim[i].nr = idx - tnl->vtx.prim[i].start;

      ctx->Driver.CurrentExecPrimitive = GL_POLYGON+1;

      if (tnl->vtx.prim_count == _TNL_MAX_PRIM)
	 _tnl_flush_immediate( ctx );	
   }
   else 
      _mesa_error( ctx, GL_INVALID_OPERATION, __FUNCTION__ );
}


void _tnl_imm_vtxfmt_init( GLcontext *ctx )
{
   GLvertexformat *vfmt = &(TNL_CONTEXT(ctx)->vtxfmt);
   vfmt->ArrayElement = _ae_loopback_array_elt;	        /* generic helper */
   vfmt->Begin = _tnl_Begin;
   vfmt->CallList = _mesa_CallList;
   vfmt->Color3f = _tnl_Color3f;
   vfmt->Color3fv = _tnl_Color3fv;
   vfmt->Color4f = _tnl_Color4f;
   vfmt->Color4fv = _tnl_Color4fv;
   vfmt->EdgeFlag = _tnl_EdgeFlag;
   vfmt->EdgeFlagv = _tnl_EdgeFlagv;
   vfmt->End = _tnl_End;
   vfmt->EvalCoord1f = _tnl_EvalCoord1f;
   vfmt->EvalCoord1fv = _tnl_EvalCoord1fv;
   vfmt->EvalCoord2f = _tnl_EvalCoord2f;
   vfmt->EvalCoord2fv = _tnl_EvalCoord2fv;
   vfmt->EvalPoint1 = _tnl_EvalPoint1;
   vfmt->EvalPoint2 = _tnl_EvalPoint2;
   vfmt->FogCoordfEXT = _tnl_FogCoordfEXT;
   vfmt->FogCoordfvEXT = _tnl_FogCoordfvEXT;
   vfmt->Indexf = _tnl_Indexf;
   vfmt->Indexfv = _tnl_Indexfv;
   vfmt->Materialfv = _tnl_Materialfv;
   vfmt->MultiTexCoord1fARB = _tnl_MultiTexCoord1f;
   vfmt->MultiTexCoord1fvARB = _tnl_MultiTexCoord1fvARB;
   vfmt->MultiTexCoord2fARB = _tnl_MultiTexCoord2f;
   vfmt->MultiTexCoord2fvARB = _tnl_MultiTexCoord2fvARB;
   vfmt->MultiTexCoord3fARB = _tnl_MultiTexCoord3f;
   vfmt->MultiTexCoord3fvARB = _tnl_MultiTexCoord3fvARB;
   vfmt->MultiTexCoord4fARB = _tnl_MultiTexCoord4f;
   vfmt->MultiTexCoord4fvARB = _tnl_MultiTexCoord4fvARB;
   vfmt->Normal3f = _tnl_Normal3f;
   vfmt->Normal3fv = _tnl_Normal3fv;
   vfmt->Rectf = _tnl_Rectf;
   vfmt->SecondaryColor3fEXT = _tnl_SecondaryColor3fEXT;
   vfmt->SecondaryColor3fvEXT = _tnl_SecondaryColor3fvEXT;
   vfmt->TexCoord1f = _tnl_TexCoord1f;
   vfmt->TexCoord1fv = _tnl_TexCoord1fv;
   vfmt->TexCoord2f = _tnl_TexCoord2f;
   vfmt->TexCoord2fv = _tnl_TexCoord2fv;
   vfmt->TexCoord3f = _tnl_TexCoord3f;
   vfmt->TexCoord3fv = _tnl_TexCoord3fv;
   vfmt->TexCoord4f = _tnl_TexCoord4f;
   vfmt->TexCoord4fv = _tnl_TexCoord4fv;
   vfmt->Vertex2f = _tnl_Vertex2f;
   vfmt->Vertex2fv = _tnl_Vertex2fv;
   vfmt->Vertex3f = _tnl_Vertex3f;
   vfmt->Vertex3fv = _tnl_Vertex3fv;
   vfmt->Vertex4f = _tnl_Vertex4f;
   vfmt->Vertex4fv = _tnl_Vertex4fv;
   vfmt->VertexAttrib1fNV = _tnl_VertexAttrib1fNV;
   vfmt->VertexAttrib1fvNV = _tnl_VertexAttrib1fvNV;
   vfmt->VertexAttrib2fNV = _tnl_VertexAttrib2fNV;
   vfmt->VertexAttrib2fvNV = _tnl_VertexAttrib2fvNV;
   vfmt->VertexAttrib3fNV = _tnl_VertexAttrib3fNV;
   vfmt->VertexAttrib3fvNV = _tnl_VertexAttrib3fvNV;
   vfmt->VertexAttrib4fNV = _tnl_VertexAttrib4fNV;
   vfmt->VertexAttrib4fvNV = _tnl_VertexAttrib4fvNV;
}





void _tnl_vtx_init( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx); 
   _tnl_InitDispatch( tnl->Exec );

   TNLcontext *tnl = TNL_CONTEXT(ctx);
   struct tnl_vertex_arrays *tmp = &tnl->imm_inputs;
   GLuint i;

   _mesa_vector1f_init( &tmp->Index, 0, 0 );
   _mesa_vector1ub_init( &tmp->EdgeFlag, 0, 0 );

   for (i = 0; i < _TNL_ATTRIB_EVALFLAG; i++)
      _mesa_vector4f_init( &tmp->Attrib[i], 0, 0);

   _tnl_imm_vtxfmt_init( ctx );
}



void _tnl_vtx_destroy( GLcontext *ctx )
{
}

