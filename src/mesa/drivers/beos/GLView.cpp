/* $Id: GLView.cpp,v 1.5.2.1 2002/09/19 16:29:49 brianp Exp $ */

/*
 * Mesa 3-D graphics library
 * Version:  3.5
 * 
 * Copyright (C) 1999-2000  Brian Paul   All Rights Reserved.
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


/*
 * $Log: GLView.cpp,v $
 * Revision 1.5.2.1  2002/09/19 16:29:49  brianp
 * updated BeOS support (Philippe Houdoin)
 *
 * Revision 1.5  2000/11/17 21:01:26  brianp
 * Minor header file changes to silence warnings.
 * Added _mesa_enable_sw_extensions(), called by software-only drivers
 * to enable all s/w-supported GL extensions.
 *
 * Revision 1.4  2000/11/14 17:51:15  brianp
 * more Driver.Color, Driver.Index updates
 *
 * Revision 1.3  2000/09/26 20:54:09  brianp
 * First batch of OpenGL SI related changes:
 * Renamed struct gl_context to struct __GLcontextRec.
 * Include glcore.h, setup GL imports/exports.
 * Replaced gl_ prefix with _mesa_ prefix in context.[ch] functions.
 * GLcontext's Visual field is no longer a pointer.
 *
 * Revision 1.2  2000/03/19 01:13:13  brianp
 * updated for Mesa 3.3
 *
 * Revision 1.1.1.1  1999/08/19 00:55:41  jtg
 * Imported sources
 *
 * Revision 1.7  1999/03/28 21:08:17  brianp
 * updated SetBuffer driver function
 *
 * Revision 1.6  1999/02/14 03:44:37  brianp
 * new copyright
 *
 * Revision 1.5  1999/02/11 03:50:57  brianp
 * added CopySubBufferMESA()
 *
 * Revision 1.4  1999/02/06 17:44:59  brianp
 * code clean-up and bug fixes
 *
 * Revision 1.3  1999/02/04 04:13:15  brianp
 * implemented double buffering
 *
 * Revision 1.2  1999/02/03 04:23:28  brianp
 * basic device driver functions now work (yeah!)
 *
 * Revision 1.1  1999/02/02 04:40:46  brianp
 * Initial revision
 */

#include <assert.h>
#include <stdio.h>

#include <GLView.h>
#include "MesaDriver.h"


//------------------------------------------------------------------
// Public interface methods
//------------------------------------------------------------------


//
// Input:  rect - initial rectangle
//         name - window name
//         resizingMode - example: B_FOLLOW_NONE
//         mode - usually 0 ?
//         options - Bitwise-OR of BGL_* tokens
//
BGLView::BGLView(BRect rect, char *name,
                 ulong resizingMode, ulong mode,
                 ulong options)
   :BView(rect, name, resizingMode, mode | B_WILL_DRAW | B_FRAME_EVENTS) //  | B_FULL_UPDATE_ON_RESIZE)
{
   const GLboolean rgbFlag = (options & BGL_RGB) == BGL_RGB;
   const GLboolean alphaFlag = (options & BGL_ALPHA) == BGL_ALPHA;
   const GLboolean dblFlag = (options & BGL_DOUBLE) == BGL_DOUBLE;
   const GLboolean stereoFlag = false;
   const GLint depth = (options & BGL_DEPTH) ? 16 : 0;
   const GLint stencil = (options & BGL_STENCIL) ? 8 : 0;
   const GLint accum = (options & BGL_ACCUM) ? 16 : 0;
   const GLint index = (options & BGL_INDEX) ? 32 : 0;
   const GLint red = (options & BGL_RGB) ? 8 : 0;
   const GLint green = (options & BGL_RGB) ? 8 : 0;
   const GLint blue = (options & BGL_RGB) ? 8 : 0;
   const GLint alpha = (options & BGL_RGB) ? 8 : 0;

   if (!rgbFlag) {
      fprintf(stderr, "Mesa Warning: color index mode not supported\n");
   }

   // Allocate auxiliary data object
   MesaDriver * md = new MesaDriver;

   // examine option flags and create gl_context struct
   GLvisual * visual = _mesa_create_visual( rgbFlag,
                                            dblFlag,
                                            stereoFlag,
                                            red, green, blue, alpha,
                                            index,
                                            depth,
                                            stencil,
                                            accum, accum, accum, accum,
                                            1
                                            );

   // create core framebuffer
   GLframebuffer * buffer = _mesa_create_framebuffer(visual,
                                              depth > 0 ? GL_TRUE : GL_FALSE,
                                              stencil > 0 ? GL_TRUE: GL_FALSE,
                                              accum > 0 ? GL_TRUE : GL_FALSE,
                                              alphaFlag
                                              );

   // create core context
   const GLboolean direct = GL_TRUE;
   GLcontext * ctx = _mesa_create_context( visual, NULL, md, direct );

   _mesa_enable_sw_extensions(ctx);
   // _mesa_enable_1_3_extensions(ctx);

   /* Initialize the software rasterizer and helper modules.
       */

	_swrast_CreateContext(ctx);
	_ac_CreateContext(ctx);
	_tnl_CreateContext(ctx);
	_swsetup_CreateContext(ctx);
	
	_swsetup_Wakeup(ctx);

   md->Init(this, ctx, visual, buffer );

   // Hook aux data into BGLView object
   m_gc = md;
}


BGLView::~BGLView()
{
   printf("BGLView destructor\n");
   MesaDriver * md = (MesaDriver *) m_gc;
   assert(md);
   delete md;
}

void BGLView::LockGL()
{
   MesaDriver * md = (MesaDriver *) m_gc;
   assert(md);
   md->LockGL();
}

void BGLView::UnlockGL()
{
   MesaDriver * md = (MesaDriver *) m_gc;
   assert(md);
   md->UnlockGL();
}

void BGLView::SwapBuffers()
{
   MesaDriver * md = (MesaDriver *) m_gc;
   assert(md);
   md->SwapBuffers();
}


void BGLView::CopySubBufferMESA(GLint x, GLint y, GLuint width, GLuint height)
{
   MesaDriver * md = (MesaDriver *) m_gc;
   assert(md);
   md->CopySubBuffer(x, y, width, height);
}


BView *	BGLView::EmbeddedView()
{
   // XXX to do
	return NULL;
}

status_t BGLView::CopyPixelsOut(BPoint source, BBitmap *dest)
{
   // XXX to do
	printf("BGLView::CopyPixelsOut() not implemented yet!\n");
	return B_UNSUPPORTED;
}


status_t BGLView::CopyPixelsIn(BBitmap *source, BPoint dest)
{
   // XXX to do
	printf("BGLView::CopyPixelsIn() not implemented yet!\n");
	return B_UNSUPPORTED;
}

void BGLView::ErrorCallback(unsigned long errorCode) // GLenum errorCode)
{
   // XXX to do
	printf("BGLView::ErrorCallback() not implemented yet!\n");
	return;
}

void BGLView::Draw(BRect updateRect)
{
   // printf("BGLView::Draw()\n");
   MesaDriver * md = (MesaDriver *) m_gc;
   assert(md);
   md->Draw(updateRect);
}

void BGLView::AttachedToWindow()
{
   BView::AttachedToWindow();

   // don't paint window background white when resized
   SetViewColor(B_TRANSPARENT_32_BIT);
}

void BGLView::AllAttached()
{
   BView::AllAttached();
//   printf("BGLView AllAttached\n");
}

void BGLView::DetachedFromWindow()
{
   BView::DetachedFromWindow();
}

void BGLView::AllDetached()
{
   BView::AllDetached();
//   printf("BGLView AllDetached");
}

void BGLView::FrameResized(float width, float height)
{
   return BView::FrameResized(width, height);
}

status_t BGLView::Perform(perform_code d, void *arg)
{
   return BView::Perform(d, arg);
}


status_t BGLView::Archive(BMessage *data, bool deep) const
{
   return BView::Archive(data, deep);
}

void BGLView::MessageReceived(BMessage *msg)
{
   BView::MessageReceived(msg);
}

void BGLView::SetResizingMode(uint32 mode)
{
   BView::SetResizingMode(mode);
}

void BGLView::Show()
{
//   printf("BGLView Show\n");
   BView::Show();
}

void BGLView::Hide()
{
//   printf("BGLView Hide\n");
   BView::Hide();
}

BHandler *BGLView::ResolveSpecifier(BMessage *msg, int32 index,
                                    BMessage *specifier, int32 form,
                                    const char *property)
{
   return BView::ResolveSpecifier(msg, index, specifier, form, property);
}

status_t BGLView::GetSupportedSuites(BMessage *data)
{
   return BView::GetSupportedSuites(data);
}

void BGLView::DirectConnected( direct_buffer_info *info )
{
   // XXX to do
}

void BGLView::EnableDirectMode( bool enabled )
{
   // XXX to do
}



//---- private methods ----------

void BGLView::_ReservedGLView1() {}
void BGLView::_ReservedGLView2() {}
void BGLView::_ReservedGLView3() {}
void BGLView::_ReservedGLView4() {}
void BGLView::_ReservedGLView5() {}
void BGLView::_ReservedGLView6() {}
void BGLView::_ReservedGLView7() {}
void BGLView::_ReservedGLView8() {}

#if 0
BGLView::BGLView(const BGLView &v)
	: BView(v)
{
   // XXX not sure how this should work
   printf("Warning BGLView::copy constructor not implemented\n");
}
#endif


BGLView &BGLView::operator=(const BGLView &v)
{
   printf("Warning BGLView::operator= not implemented\n");
	return *this;
}

void BGLView::dither_front()
{
   // no-op
}

bool BGLView::confirm_dither()
{
   // no-op
   return false;
}

void BGLView::draw(BRect r)
{
   // XXX no-op ???
}

/* Direct Window stuff */
void BGLView::drawScanline( int x1, int x2, int y, void *data )
{
   // no-op
}

void BGLView::scanlineHandler(struct rasStateRec *state,
                              GLint x1, GLint x2)
{
   // no-op
}

void BGLView::lock_draw()
{
   // no-op
}

void BGLView::unlock_draw()
{
   // no-op
}

bool BGLView::validateView()
{
   // no-op
   return true;
}

