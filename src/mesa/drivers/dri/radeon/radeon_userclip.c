static void radeonClipPlane( GLcontext *ctx, GLenum plane, const GLfloat *eq )
{
   GLint p = (GLint) plane - (GLint) GL_CLIP_PLANE0;
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLint *ip = (GLint *)ctx->Transform._ClipUserPlane[p];

   RADEON_STATECHANGE( rmesa, ucp[p] );
   rmesa->hw.ucp[p].cmd[UCP_X] = ip[0];
   rmesa->hw.ucp[p].cmd[UCP_Y] = ip[1];
   rmesa->hw.ucp[p].cmd[UCP_Z] = ip[2];
   rmesa->hw.ucp[p].cmd[UCP_W] = ip[3];
}

void radeonUpdateClipPlanes( GLcontext *ctx )
{
   radeonContextPtr rmesa = RADEON_CONTEXT(ctx);
   GLuint p;

   for (p = 0; p < ctx->Const.MaxClipPlanes; p++) {
      if (ctx->Transform.ClipPlanesEnabled & (1 << p)) {
	 GLint *ip = (GLint *)ctx->Transform._ClipUserPlane[p];

	 RADEON_STATECHANGE( rmesa, ucp[p] );
	 rmesa->hw.ucp[p].cmd[UCP_X] = ip[0];
	 rmesa->hw.ucp[p].cmd[UCP_Y] = ip[1];
	 rmesa->hw.ucp[p].cmd[UCP_Z] = ip[2];
	 rmesa->hw.ucp[p].cmd[UCP_W] = ip[3];
      }
   }
}

void radeonInitUserClip( GLcontext *ctx )
{
   ctx->Driver.ClipPlane		= radeonClipPlane;

   for (i = 0 ; i < 6; i++)
      ctx->Driver.ClipPlane( ctx, GL_CLIP_PLANE0 + i, NULL );

}
