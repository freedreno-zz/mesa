
/* Some nasty stuff still hanging on here.  
 *
 * TODO - remove VB->ColorPtr, etc and just use the AttrPtr's.
 */
static void _tnl_vb_bind_immediate( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);
   struct vertex_buffer *VB = &tnl->vb;
   struct tnl_vertex_arrays *tmp = &tnl->imm_inputs;
   const GLuint count = IM->Count - start;

   /* Setup constant data in the VB.
    */
   VB->Count = count;
   VB->Primitive = tnl->vtx.prim;
   VB->PrimitiveNr = tnl->vtx.prim_nr;
   VB->Elts = NULL;
   VB->NormalLengthPtr = NULL;

   GLuint attr;
   for (attr = 0; attr < VERT_ATTRIB_EVALFLAG; attr++) {
      tmp->Attribs[attr].count = count;
      tmp->Attribs[attr].data = IM->Attrib[attr] + start;
      tmp->Attribs[attr].start = (GLfloat *) (IM->Attrib[attr] + start);
      tmp->Attribs[attr].size = 4;
      tmp->Attribs[attr].stride = sz * sizeof(GLfloat);
      VB->AttribPtr[attr] = &(tmp->Attribs[attr]);
   }

   /* Index and edgeflag require special treatment, as usual:
    */
   {
      tmp->Index.count = count;
      tmp->Index.data = IM->Index;
      tmp->Index.start = IM->Index;
      tmp->Index.stride = sz * sizeof(GLfloat);
      VB->IndexPtr[0] = &tmp->Index;
      VB->IndexPtr[1] = NULL;
   }
   
   /* Copy and translate EdgeFlag to a contiguous array of GLbooleans
    */
   {
      VB->EdgeFlag = IM->EdgeFlag + start;
   }

   /* Legacy pointers -- remove one day.
    */
   VB->ObjPtr = &tmp->Attribs[VERT_ATTRIB_POS];
   VB->NormalPtr = &tmp->Attribs[VERT_ATTRIB_NORMAL];
   VB->ColorPtr[0] = &tmp->Attribs[VERT_ATTRIB_COLOR0];
   VB->ColorPtr[1] = NULL;
   VB->SecondaryColorPtr[0] = &tmp->Attribs[VERT_ATTRIB_COLOR1];
   VB->SecondaryColorPtr[1] = NULL;

   for (i = 0; i < ctx->Const.MaxTextureCoordUnits; i++) {
      VB->TexCoordPtr[i] = &tmp->Attribs[VERT_ATTRIB_TEX0 + i];
   }
}




static void copy_vertex( r200ContextPtr rmesa, GLuint n, GLfloat *dst )
{
   GLuint i;
   GLfloat *src = (GLfloat *)(rmesa->dma.current.address + 
			      rmesa->dma.current.ptr + 
			      (rmesa->vb.primlist[rmesa->vb.nrprims].start + n) * 
			      rmesa->vb.vertex_size * 4);

   if (R200_DEBUG & DEBUG_VFMT) 
      fprintf(stderr, "copy_vertex %d\n", rmesa->vb.primlist[rmesa->vb.nrprims].start + n);

   for (i = 0 ; i < rmesa->vb.vertex_size; i++) {
      dst[i] = src[i];
   }
}

/*
 * NOTE: Need to have calculated primitives by this point -- do it on the fly.
 * NOTE: Old 'parity' issue is gone.
 */
static GLuint _tnl_copy_vertices( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT( ctx );
   GLuint nr = tnl->vtx.primlist[tnl->vtx.nrprims-1].nr;
   GLuint ovf, i;
   GLfloat *src = (tnl->vtx.buffer + 
		   tnl->vtx.primlist[tnl->vtx.nrprims].start * 
		   tnl->vtx.vertex_size);


   switch( ctx->Driver.CurrentExecPrimitive )
   {
   case GL_POINTS:
      return 0;
   case GL_LINES:
      ovf = nr&1;
      for (i = 0 ; i < ovf ; i++)
	 memcpy( dst+i*sz, src+(nr-ovf+i)*sz, sz*4 );
      return i;
   case GL_TRIANGLES:
      ovf = nr%3;
      for (i = 0 ; i < ovf ; i++)
	 memcpy( dst+i*sz, src+(nr-ovf+i)*sz, sz*4 );
      return i;
   case GL_QUADS:
      ovf = nr&3;
      for (i = 0 ; i < ovf ; i++)
	 memcpy( dst+i*sz, src+(nr-ovf+i)*sz, sz*4 );
      return i;
   case GL_LINE_STRIP:
      if (nr == 0) 
	 return 0;
      else {
	 memcpy( dst, src+(nr-1)*sz, sz*4 );
	 return 1;
      }
   case GL_LINE_LOOP:
   case GL_TRIANGLE_FAN:
   case GL_POLYGON:
      if (nr == 0) 
	 return 0;
      else if (nr == 1) {
	 memcpy( dst, src+0, sz*4 );
	 return 1;
      } else {
	 memcpy( dst, src+0, sz*4 );
	 memcpy( dst+sz, src+(nr-1)*sz, sz*4 );
	 return 2;
      }
   case GL_TRIANGLE_STRIP:
   case GL_QUAD_STRIP:
      switch (nr) {
      case 0: ovf = 0; break;
      case 1: ovf = 1; break;
      default: ovf = 2 + (nr&1); break;
      }
      for (i = 0 ; i < ovf ; i++)
	 memcpy( dst+i*sz, src+(nr-ovf+i)*sz, sz*4 );
      return i;
   case GL_POLYGON+1:
      return 0;
   default:
      assert(0);
      return 0;
   }
}






/**
 * Execute the buffer and save copied verts.
 */
void _tnl_flush_immediate( GLcontext *ctx )
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);

   if (!tnl->vtx.prim_nr) 
      return;

   tnl->copied_verts.nr = _tnl_copy_vertices( ctx ); 
   
   if (tnl->pipeline.build_state_changes)
      _tnl_validate_pipeline( ctx );

   _tnl_vb_bind_immediate( ctx );

   if (tnl->vtx.attrsz[VERT_ATTRIB_EVALFLAG])
      _tnl_eval_immediate( ctx );

   /* Invalidate all stored data before and after run:
    */
   tnl->pipeline.run_input_changes |= tnl->pipeline.inputs;
   tnl->Driver.RunPipeline( ctx );
   tnl->pipeline.run_input_changes |= tnl->pipeline.inputs;
}





void _tnl_flush_vertices( GLcontext *ctx, GLuint flags )
{
   if (ctx->Driver.CurrentExecPrimitive != PRIM_OUTSIDE_BEGIN_END)
      return;

   if (tnl->vtx.counter != tnl->vtx.initial_counter)
      _tnl_flush_immediate( ctx );

   if (flags & FLUSH_UPDATE_CURRENT) {
      _tnl_copy_to_current( ctx );
      _tnl_reset_vtxfmt( ctx );

      /* DO THIS IN _tnl_reset_vtxfmt:
       */
      tnl->vtx.vertex_size = 0;
      for (i = 0 ; i < TNL_MAX_ATTRIB ; i++) 
	 tnl->vtx.attrib[i].sz = 0;
   }
}
