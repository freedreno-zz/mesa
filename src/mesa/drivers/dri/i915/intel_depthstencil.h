
#ifndef INTEL_DEPTH_STENCIL_H
#define INTEL_DEPTH_STENCIL_H


extern void
intel_undo_depth_stencil_pairing(GLcontext *ctx,
                                 struct intel_renderbuffer *driRb);

extern void
intel_validate_depth_stencil(GLcontext *ctx, struct gl_framebuffer *fb);


#endif /* INTEL_DEPTH_STENCIL_H */
