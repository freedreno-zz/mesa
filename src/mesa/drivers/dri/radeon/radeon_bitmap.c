/* Cope with depth operations by drawing individual pixels as points??? 
 */
void
radeonPointsBitmap( GLcontext *ctx, GLint px, GLint py,
		  GLsizei width, GLsizei height,
		  const struct gl_pixelstore_attrib *unpack,
		  const GLubyte *bitmap )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   const GLfloat *rc = ctx->Current.RasterColor; 
   GLint row, col;
   radeonVertex vert;
   GLuint orig_vte;
   GLuint h;


   /* Turn off tcl.  
    */
   TCL_FALLBACK( ctx, RADEON_TCL_FALLBACK_BITMAP, 1 );

   /* Choose tiny vertex format
    */
   radeonSetVertexFormat( ctx, RADEON_XYZW_BIT | RADEON_RGBA_BIT );

   /* Ready for point primitives:
    */
   radeonRenderPrimitive( ctx, GL_POINTS );

   /* Turn off the hw viewport transformation:
    */
   RADEON_STATECHANGE( rmesa, vte );
   orig_vte = rmesa->hw.vte.cmd[VTE_SE_VTE_CNTL];
   rmesa->hw.vte.cmd[VTE_SE_VTE_CNTL] &= ~(RADEON_VPORT_X_SCALE_ENA |
					   RADEON_VPORT_Y_SCALE_ENA |
					   RADEON_VPORT_Z_SCALE_ENA |
					   RADEON_VPORT_X_OFFSET_ENA |
					   RADEON_VPORT_Y_OFFSET_ENA |
					   RADEON_VPORT_Z_OFFSET_ENA); 

   /* Turn off other stuff:  Stipple?, texture?, blending?, etc.
    */


   /* Populate the vertex
    *
    * Incorporate FOG into RGBA
    */
   if (ctx->Fog.Enabled) {
      const GLfloat *fc = ctx->Fog.Color;
      GLfloat color[4];
      GLfloat f;

      if (ctx->Fog.FogCoordinateSource == GL_FOG_COORDINATE_EXT)
         f = _mesa_z_to_fogfactor(ctx, ctx->Current.Attrib[VERT_ATTRIB_FOG][0]);
      else
         f = _mesa_z_to_fogfactor(ctx, ctx->Current.RasterDistance);

      color[0] = f * rc[0] + (1.F - f) * fc[0];
      color[1] = f * rc[1] + (1.F - f) * fc[1];
      color[2] = f * rc[2] + (1.F - f) * fc[2];
      color[3] = rc[3];

      UNCLAMPED_FLOAT_TO_CHAN(vert.tv.color.red,   color[0]);
      UNCLAMPED_FLOAT_TO_CHAN(vert.tv.color.green, color[1]);
      UNCLAMPED_FLOAT_TO_CHAN(vert.tv.color.blue,  color[2]);
      UNCLAMPED_FLOAT_TO_CHAN(vert.tv.color.alpha, color[3]);
   }
   else {
      UNCLAMPED_FLOAT_TO_CHAN(vert.tv.color.red,   rc[0]);
      UNCLAMPED_FLOAT_TO_CHAN(vert.tv.color.green, rc[1]);
      UNCLAMPED_FLOAT_TO_CHAN(vert.tv.color.blue,  rc[2]);
      UNCLAMPED_FLOAT_TO_CHAN(vert.tv.color.alpha, rc[3]);
   }


   vert.tv.z = ctx->Current.RasterPos[2];


   /* Update window height
    */
   LOCK_HARDWARE( rmesa );
   UNLOCK_HARDWARE( rmesa );
   h = rmesa->dri.drawable->h + rmesa->dri.drawable->y;
   px += rmesa->dri.drawable->x;

   /* Clipping handled by existing mechansims in radeon_ioctl.c?
    */
   for (row=0; row<height; row++) {
      const GLubyte *src = (const GLubyte *) 
	 _mesa_image_address( unpack, bitmap, width, height, 
			      GL_COLOR_INDEX, GL_BITMAP, 0, row, 0 );

      if (unpack->LsbFirst) {
         /* Lsb first */
         GLubyte mask = 1U << (unpack->SkipPixels & 0x7);
         for (col=0; col<width; col++) {
            if (*src & mask) {
	       vert.tv.x = px+col;
	       vert.tv.y = h - (py+row) - 1;
	       radeon_point( rmesa, &vert );
            }
	    src += (mask >> 7);
	    mask = ((mask << 1) & 0xff) | (mask >> 7);
         }

         /* get ready for next row */
         if (mask != 1)
            src++;
      }
      else {
         /* Msb first */
         GLubyte mask = 128U >> (unpack->SkipPixels & 0x7);
         for (col=0; col<width; col++) {
            if (*src & mask) {
	       vert.tv.x = px+col;
	       vert.tv.y = h - (py+row) - 1;
	       radeon_point( rmesa, &vert );
            }
	    src += mask & 1;
	    mask = ((mask << 7) & 0xff) | (mask >> 1);
         }
         /* get ready for next row */
         if (mask != 128)
            src++;
      }
   }

   /* Fire outstanding vertices, restore state
    */
   RADEON_STATECHANGE( rmesa, vte );
   rmesa->hw.vte.cmd[VTE_SE_VTE_CNTL] = orig_vte;

   /* Unfallback
    */
   TCL_FALLBACK( ctx, RADEON_TCL_FALLBACK_BITMAP, 0 );

   /* Need to restore vertexformat?
    */
   if (rmesa->TclFallback)
      radeonChooseVertexState( ctx );
}
