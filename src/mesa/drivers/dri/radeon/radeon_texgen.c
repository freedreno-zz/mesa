static void set_texgen_matrix( radeonContextPtr rmesa, 
			       GLuint unit,
			       GLfloat *s_plane,
			       GLfloat *t_plane )
{
   static const GLfloat scale_identity[4] = { 1,1,1,1 };

   if (!TEST_EQ_4V( s_plane, scale_identity) ||
      !(TEST_EQ_4V( t_plane, scale_identity))) {
      rmesa->TexGenEnabled |= RADEON_TEXMAT_0_ENABLE<<unit;
      rmesa->TexGenMatrix[unit].m[0]  = s_plane[0];
      rmesa->TexGenMatrix[unit].m[4]  = s_plane[1];
      rmesa->TexGenMatrix[unit].m[8]  = s_plane[2];
      rmesa->TexGenMatrix[unit].m[12] = s_plane[3];

      rmesa->TexGenMatrix[unit].m[1]  = t_plane[0];
      rmesa->TexGenMatrix[unit].m[5]  = t_plane[1];
      rmesa->TexGenMatrix[unit].m[9]  = t_plane[2];
      rmesa->TexGenMatrix[unit].m[13] = t_plane[3];
      rmesa->NewGLState |= _NEW_TEXTURE_MATRIX;
   }
}

/* Ignoring the Q texcoord for now.
 *
 * Returns GL_FALSE if fallback required.  
 */
static GLboolean radeon_validate_texgen( GLcontext *ctx, GLuint unit )
{  
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   struct gl_texture_unit *texUnit = &ctx->Texture.Unit[unit];
   GLuint inputshift = RADEON_TEXGEN_0_INPUT_SHIFT + unit*4;
   GLuint tmp = rmesa->TexGenEnabled;

   rmesa->TexGenEnabled &= ~(RADEON_TEXGEN_TEXMAT_0_ENABLE<<unit);
   rmesa->TexGenEnabled &= ~(RADEON_TEXMAT_0_ENABLE<<unit);
   rmesa->TexGenEnabled &= ~(RADEON_TEXGEN_INPUT_MASK<<inputshift);
   rmesa->TexGenNeedNormals[unit] = 0;

   if (0)
   fprintf(stderr, "%s unit %d cleared texgenEnabled %x\n", __FUNCTION__,
	   unit, rmesa->TexGenEnabled);

   if ((texUnit->TexGenEnabled & (S_BIT|T_BIT)) == 0) {
      /* Disabled, no fallback:
       */
      rmesa->TexGenEnabled |= 
	 (RADEON_TEXGEN_INPUT_TEXCOORD_0+unit) << inputshift;
      return GL_TRUE;
   }
   else if (texUnit->TexGenEnabled & Q_BIT) {
      /* Very easy to do this, in fact would remove a fallback case
       * elsewhere, but I haven't done it yet...  Fallback: 
       */
      fprintf(stderr, "fallback Q_BIT\n");
      return GL_FALSE;
   }
   else if ((texUnit->TexGenEnabled & (S_BIT|T_BIT)) != (S_BIT|T_BIT) ||
	    texUnit->GenModeS != texUnit->GenModeT) {
      /* Mixed modes, fallback:
       */
/*        fprintf(stderr, "fallback mixed texgen\n"); */
      return GL_FALSE;
   }
   else
      rmesa->TexGenEnabled |= RADEON_TEXGEN_TEXMAT_0_ENABLE << unit;

   switch (texUnit->GenModeS) {
   case GL_OBJECT_LINEAR:
      rmesa->TexGenEnabled |= RADEON_TEXGEN_INPUT_OBJ << inputshift;
      set_texgen_matrix( rmesa, unit, 
			 texUnit->ObjectPlaneS,
			 texUnit->ObjectPlaneT);
      break;

   case GL_EYE_LINEAR:
      rmesa->TexGenEnabled |= RADEON_TEXGEN_INPUT_EYE << inputshift;
      set_texgen_matrix( rmesa, unit, 
			 texUnit->EyePlaneS,
			 texUnit->EyePlaneT);
      break;

   case GL_REFLECTION_MAP_NV:
      rmesa->TexGenNeedNormals[unit] = GL_TRUE;
      rmesa->TexGenEnabled |= RADEON_TEXGEN_INPUT_EYE_REFLECT<<inputshift;
      break;

   case GL_NORMAL_MAP_NV:
      rmesa->TexGenNeedNormals[unit] = GL_TRUE;
      rmesa->TexGenEnabled |= RADEON_TEXGEN_INPUT_EYE_NORMAL<<inputshift;
      break;

   case GL_SPHERE_MAP:
   default:
      /* Unsupported mode, fallback:
       */
      /*  fprintf(stderr, "fallback unsupported texgen\n"); */
      return GL_FALSE;
   }

   if (tmp != rmesa->TexGenEnabled) {
      rmesa->NewGLState |= _NEW_TEXTURE_MATRIX;
   }

/*     fprintf(stderr, "%s unit %d texgenEnabled %x\n", __FUNCTION__, */
/*  	   unit, rmesa->TexGenEnabled); */
   return GL_TRUE;
}



static void update_texturematrix( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT( ctx );
   GLuint tpc = rmesa->hw.tcl.cmd[TCL_TEXTURE_PROC_CTL];
   GLuint vs = rmesa->hw.tcl.cmd[TCL_OUTPUT_VTXSEL];
   int unit;

   rmesa->TexMatEnabled = 0;

   for (unit = 0 ; unit < 2; unit++) {
      if (!ctx->Texture.Unit[unit]._ReallyEnabled) {
      }
      else if (ctx->TextureMatrixStack[unit].Top->type != MATRIX_IDENTITY) {
	 GLuint inputshift = RADEON_TEXGEN_0_INPUT_SHIFT + unit*4;
	 
	 rmesa->TexMatEnabled |= (RADEON_TEXGEN_TEXMAT_0_ENABLE|
				  RADEON_TEXMAT_0_ENABLE) << unit;

	 if (rmesa->TexGenEnabled & (RADEON_TEXMAT_0_ENABLE << unit)) {
	    /* Need to preconcatenate any active texgen 
	     * obj/eyeplane matrices:
	     */
	    _math_matrix_mul_matrix( &rmesa->tmpmat, 
				     &rmesa->TexGenMatrix[unit],
				     ctx->TextureMatrixStack[unit].Top );
	    upload_matrix( rmesa, rmesa->tmpmat.m, TEXMAT_0+unit );
	 } 
	 else {
	    rmesa->TexMatEnabled |= 
	       (RADEON_TEXGEN_INPUT_TEXCOORD_0+unit) << inputshift;
	    upload_matrix( rmesa, ctx->TextureMatrixStack[unit].Top->m, 
			   TEXMAT_0+unit );
	 }
      }
      else if (rmesa->TexGenEnabled & (RADEON_TEXMAT_0_ENABLE << unit)) {
	 upload_matrix( rmesa, rmesa->TexGenMatrix[unit].m, 
			TEXMAT_0+unit );
      }
   }


   tpc = (rmesa->TexMatEnabled | rmesa->TexGenEnabled);

   vs &= ~((0xf << RADEON_TCL_TEX_0_OUTPUT_SHIFT) |
	   (0xf << RADEON_TCL_TEX_1_OUTPUT_SHIFT));

   if (tpc & RADEON_TEXGEN_TEXMAT_0_ENABLE)
      vs |= RADEON_TCL_TEX_COMPUTED_TEX_0 << RADEON_TCL_TEX_0_OUTPUT_SHIFT;
   else
      vs |= RADEON_TCL_TEX_INPUT_TEX_0 << RADEON_TCL_TEX_0_OUTPUT_SHIFT;

   if (tpc & RADEON_TEXGEN_TEXMAT_1_ENABLE)
      vs |= RADEON_TCL_TEX_COMPUTED_TEX_1 << RADEON_TCL_TEX_1_OUTPUT_SHIFT;
   else
      vs |= RADEON_TCL_TEX_INPUT_TEX_1 << RADEON_TCL_TEX_1_OUTPUT_SHIFT;

   if (tpc != rmesa->hw.tcl.cmd[TCL_TEXTURE_PROC_CTL] ||
       vs != rmesa->hw.tcl.cmd[TCL_OUTPUT_VTXSEL]) {
      
      RADEON_STATECHANGE(rmesa, tcl);
      rmesa->hw.tcl.cmd[TCL_TEXTURE_PROC_CTL] = tpc;
      rmesa->hw.tcl.cmd[TCL_OUTPUT_VTXSEL] = vs;
   }
}



void radeonInitTexTransform( GLcontext *ctx )
{
   _math_matrix_ctr( &rmesa->TexGenMatrix[0] );
   _math_matrix_ctr( &rmesa->TexGenMatrix[1] );
   _math_matrix_ctr( &rmesa->tmpmat );
   _math_matrix_set_identity( &rmesa->TexGenMatrix[0] );
   _math_matrix_set_identity( &rmesa->TexGenMatrix[1] );
   _math_matrix_set_identity( &rmesa->tmpmat );
}
