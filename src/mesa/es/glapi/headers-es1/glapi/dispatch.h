/* DO NOT EDIT - This file generated automatically by gl_table.py (from Mesa) script */

/*
 * (C) Copyright IBM Corporation 2005
 * All Rights Reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sub license,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.  IN NO EVENT SHALL
 * IBM,
 * AND/OR THEIR SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#if !defined( _DISPATCH_H_ )
#  define _DISPATCH_H_


#include "glapitable.h"
/**
 * \file dispatch.h
 * Macros for handling GL dispatch tables.
 *
 * For each known GL function, there are 3 macros in this file.  The first
 * macro is named CALL_FuncName and is used to call that GL function using
 * the specified dispatch table.  The other 2 macros, called GET_FuncName
 * can SET_FuncName, are used to get and set the dispatch pointer for the
 * named function in the specified dispatch table.
 */

#define CALL_by_offset(disp, cast, offset, parameters) \
    (*(cast (GET_by_offset(disp, offset)))) parameters
#define GET_by_offset(disp, offset) \
    (offset >= 0) ? (((_glapi_proc *)(disp))[offset]) : NULL
#define SET_by_offset(disp, offset, fn) \
    do { \
        if ( (offset) < 0 ) { \
            /* fprintf( stderr, "[%s:%u] SET_by_offset(%p, %d, %s)!\n", */ \
            /*         __func__, __LINE__, disp, offset, # fn); */ \
            /* abort(); */ \
        } \
        else { \
            ( (_glapi_proc *) (disp) )[offset] = (_glapi_proc) fn; \
        } \
    } while(0)

#define CALL_NewList(disp, parameters) (*((disp)->NewList)) parameters
#define GET_NewList(disp) ((disp)->NewList)
#define SET_NewList(disp, fn) ((disp)->NewList = fn)
#define CALL_EndList(disp, parameters) (*((disp)->EndList)) parameters
#define GET_EndList(disp) ((disp)->EndList)
#define SET_EndList(disp, fn) ((disp)->EndList = fn)
#define CALL_CallList(disp, parameters) (*((disp)->CallList)) parameters
#define GET_CallList(disp) ((disp)->CallList)
#define SET_CallList(disp, fn) ((disp)->CallList = fn)
#define CALL_CallLists(disp, parameters) (*((disp)->CallLists)) parameters
#define GET_CallLists(disp) ((disp)->CallLists)
#define SET_CallLists(disp, fn) ((disp)->CallLists = fn)
#define CALL_DeleteLists(disp, parameters) (*((disp)->DeleteLists)) parameters
#define GET_DeleteLists(disp) ((disp)->DeleteLists)
#define SET_DeleteLists(disp, fn) ((disp)->DeleteLists = fn)
#define CALL_GenLists(disp, parameters) (*((disp)->GenLists)) parameters
#define GET_GenLists(disp) ((disp)->GenLists)
#define SET_GenLists(disp, fn) ((disp)->GenLists = fn)
#define CALL_ListBase(disp, parameters) (*((disp)->ListBase)) parameters
#define GET_ListBase(disp) ((disp)->ListBase)
#define SET_ListBase(disp, fn) ((disp)->ListBase = fn)
#define CALL_Begin(disp, parameters) (*((disp)->Begin)) parameters
#define GET_Begin(disp) ((disp)->Begin)
#define SET_Begin(disp, fn) ((disp)->Begin = fn)
#define CALL_Bitmap(disp, parameters) (*((disp)->Bitmap)) parameters
#define GET_Bitmap(disp) ((disp)->Bitmap)
#define SET_Bitmap(disp, fn) ((disp)->Bitmap = fn)
#define CALL_Color3b(disp, parameters) (*((disp)->Color3b)) parameters
#define GET_Color3b(disp) ((disp)->Color3b)
#define SET_Color3b(disp, fn) ((disp)->Color3b = fn)
#define CALL_Color3bv(disp, parameters) (*((disp)->Color3bv)) parameters
#define GET_Color3bv(disp) ((disp)->Color3bv)
#define SET_Color3bv(disp, fn) ((disp)->Color3bv = fn)
#define CALL_Color3d(disp, parameters) (*((disp)->Color3d)) parameters
#define GET_Color3d(disp) ((disp)->Color3d)
#define SET_Color3d(disp, fn) ((disp)->Color3d = fn)
#define CALL_Color3dv(disp, parameters) (*((disp)->Color3dv)) parameters
#define GET_Color3dv(disp) ((disp)->Color3dv)
#define SET_Color3dv(disp, fn) ((disp)->Color3dv = fn)
#define CALL_Color3f(disp, parameters) (*((disp)->Color3f)) parameters
#define GET_Color3f(disp) ((disp)->Color3f)
#define SET_Color3f(disp, fn) ((disp)->Color3f = fn)
#define CALL_Color3fv(disp, parameters) (*((disp)->Color3fv)) parameters
#define GET_Color3fv(disp) ((disp)->Color3fv)
#define SET_Color3fv(disp, fn) ((disp)->Color3fv = fn)
#define CALL_Color3i(disp, parameters) (*((disp)->Color3i)) parameters
#define GET_Color3i(disp) ((disp)->Color3i)
#define SET_Color3i(disp, fn) ((disp)->Color3i = fn)
#define CALL_Color3iv(disp, parameters) (*((disp)->Color3iv)) parameters
#define GET_Color3iv(disp) ((disp)->Color3iv)
#define SET_Color3iv(disp, fn) ((disp)->Color3iv = fn)
#define CALL_Color3s(disp, parameters) (*((disp)->Color3s)) parameters
#define GET_Color3s(disp) ((disp)->Color3s)
#define SET_Color3s(disp, fn) ((disp)->Color3s = fn)
#define CALL_Color3sv(disp, parameters) (*((disp)->Color3sv)) parameters
#define GET_Color3sv(disp) ((disp)->Color3sv)
#define SET_Color3sv(disp, fn) ((disp)->Color3sv = fn)
#define CALL_Color3ub(disp, parameters) (*((disp)->Color3ub)) parameters
#define GET_Color3ub(disp) ((disp)->Color3ub)
#define SET_Color3ub(disp, fn) ((disp)->Color3ub = fn)
#define CALL_Color3ubv(disp, parameters) (*((disp)->Color3ubv)) parameters
#define GET_Color3ubv(disp) ((disp)->Color3ubv)
#define SET_Color3ubv(disp, fn) ((disp)->Color3ubv = fn)
#define CALL_Color3ui(disp, parameters) (*((disp)->Color3ui)) parameters
#define GET_Color3ui(disp) ((disp)->Color3ui)
#define SET_Color3ui(disp, fn) ((disp)->Color3ui = fn)
#define CALL_Color3uiv(disp, parameters) (*((disp)->Color3uiv)) parameters
#define GET_Color3uiv(disp) ((disp)->Color3uiv)
#define SET_Color3uiv(disp, fn) ((disp)->Color3uiv = fn)
#define CALL_Color3us(disp, parameters) (*((disp)->Color3us)) parameters
#define GET_Color3us(disp) ((disp)->Color3us)
#define SET_Color3us(disp, fn) ((disp)->Color3us = fn)
#define CALL_Color3usv(disp, parameters) (*((disp)->Color3usv)) parameters
#define GET_Color3usv(disp) ((disp)->Color3usv)
#define SET_Color3usv(disp, fn) ((disp)->Color3usv = fn)
#define CALL_Color4b(disp, parameters) (*((disp)->Color4b)) parameters
#define GET_Color4b(disp) ((disp)->Color4b)
#define SET_Color4b(disp, fn) ((disp)->Color4b = fn)
#define CALL_Color4bv(disp, parameters) (*((disp)->Color4bv)) parameters
#define GET_Color4bv(disp) ((disp)->Color4bv)
#define SET_Color4bv(disp, fn) ((disp)->Color4bv = fn)
#define CALL_Color4d(disp, parameters) (*((disp)->Color4d)) parameters
#define GET_Color4d(disp) ((disp)->Color4d)
#define SET_Color4d(disp, fn) ((disp)->Color4d = fn)
#define CALL_Color4dv(disp, parameters) (*((disp)->Color4dv)) parameters
#define GET_Color4dv(disp) ((disp)->Color4dv)
#define SET_Color4dv(disp, fn) ((disp)->Color4dv = fn)
#define CALL_Color4fv(disp, parameters) (*((disp)->Color4fv)) parameters
#define GET_Color4fv(disp) ((disp)->Color4fv)
#define SET_Color4fv(disp, fn) ((disp)->Color4fv = fn)
#define CALL_Color4i(disp, parameters) (*((disp)->Color4i)) parameters
#define GET_Color4i(disp) ((disp)->Color4i)
#define SET_Color4i(disp, fn) ((disp)->Color4i = fn)
#define CALL_Color4iv(disp, parameters) (*((disp)->Color4iv)) parameters
#define GET_Color4iv(disp) ((disp)->Color4iv)
#define SET_Color4iv(disp, fn) ((disp)->Color4iv = fn)
#define CALL_Color4s(disp, parameters) (*((disp)->Color4s)) parameters
#define GET_Color4s(disp) ((disp)->Color4s)
#define SET_Color4s(disp, fn) ((disp)->Color4s = fn)
#define CALL_Color4sv(disp, parameters) (*((disp)->Color4sv)) parameters
#define GET_Color4sv(disp) ((disp)->Color4sv)
#define SET_Color4sv(disp, fn) ((disp)->Color4sv = fn)
#define CALL_Color4ubv(disp, parameters) (*((disp)->Color4ubv)) parameters
#define GET_Color4ubv(disp) ((disp)->Color4ubv)
#define SET_Color4ubv(disp, fn) ((disp)->Color4ubv = fn)
#define CALL_Color4ui(disp, parameters) (*((disp)->Color4ui)) parameters
#define GET_Color4ui(disp) ((disp)->Color4ui)
#define SET_Color4ui(disp, fn) ((disp)->Color4ui = fn)
#define CALL_Color4uiv(disp, parameters) (*((disp)->Color4uiv)) parameters
#define GET_Color4uiv(disp) ((disp)->Color4uiv)
#define SET_Color4uiv(disp, fn) ((disp)->Color4uiv = fn)
#define CALL_Color4us(disp, parameters) (*((disp)->Color4us)) parameters
#define GET_Color4us(disp) ((disp)->Color4us)
#define SET_Color4us(disp, fn) ((disp)->Color4us = fn)
#define CALL_Color4usv(disp, parameters) (*((disp)->Color4usv)) parameters
#define GET_Color4usv(disp) ((disp)->Color4usv)
#define SET_Color4usv(disp, fn) ((disp)->Color4usv = fn)
#define CALL_EdgeFlag(disp, parameters) (*((disp)->EdgeFlag)) parameters
#define GET_EdgeFlag(disp) ((disp)->EdgeFlag)
#define SET_EdgeFlag(disp, fn) ((disp)->EdgeFlag = fn)
#define CALL_EdgeFlagv(disp, parameters) (*((disp)->EdgeFlagv)) parameters
#define GET_EdgeFlagv(disp) ((disp)->EdgeFlagv)
#define SET_EdgeFlagv(disp, fn) ((disp)->EdgeFlagv = fn)
#define CALL_End(disp, parameters) (*((disp)->End)) parameters
#define GET_End(disp) ((disp)->End)
#define SET_End(disp, fn) ((disp)->End = fn)
#define CALL_Indexd(disp, parameters) (*((disp)->Indexd)) parameters
#define GET_Indexd(disp) ((disp)->Indexd)
#define SET_Indexd(disp, fn) ((disp)->Indexd = fn)
#define CALL_Indexdv(disp, parameters) (*((disp)->Indexdv)) parameters
#define GET_Indexdv(disp) ((disp)->Indexdv)
#define SET_Indexdv(disp, fn) ((disp)->Indexdv = fn)
#define CALL_Indexf(disp, parameters) (*((disp)->Indexf)) parameters
#define GET_Indexf(disp) ((disp)->Indexf)
#define SET_Indexf(disp, fn) ((disp)->Indexf = fn)
#define CALL_Indexfv(disp, parameters) (*((disp)->Indexfv)) parameters
#define GET_Indexfv(disp) ((disp)->Indexfv)
#define SET_Indexfv(disp, fn) ((disp)->Indexfv = fn)
#define CALL_Indexi(disp, parameters) (*((disp)->Indexi)) parameters
#define GET_Indexi(disp) ((disp)->Indexi)
#define SET_Indexi(disp, fn) ((disp)->Indexi = fn)
#define CALL_Indexiv(disp, parameters) (*((disp)->Indexiv)) parameters
#define GET_Indexiv(disp) ((disp)->Indexiv)
#define SET_Indexiv(disp, fn) ((disp)->Indexiv = fn)
#define CALL_Indexs(disp, parameters) (*((disp)->Indexs)) parameters
#define GET_Indexs(disp) ((disp)->Indexs)
#define SET_Indexs(disp, fn) ((disp)->Indexs = fn)
#define CALL_Indexsv(disp, parameters) (*((disp)->Indexsv)) parameters
#define GET_Indexsv(disp) ((disp)->Indexsv)
#define SET_Indexsv(disp, fn) ((disp)->Indexsv = fn)
#define CALL_Normal3b(disp, parameters) (*((disp)->Normal3b)) parameters
#define GET_Normal3b(disp) ((disp)->Normal3b)
#define SET_Normal3b(disp, fn) ((disp)->Normal3b = fn)
#define CALL_Normal3bv(disp, parameters) (*((disp)->Normal3bv)) parameters
#define GET_Normal3bv(disp) ((disp)->Normal3bv)
#define SET_Normal3bv(disp, fn) ((disp)->Normal3bv = fn)
#define CALL_Normal3d(disp, parameters) (*((disp)->Normal3d)) parameters
#define GET_Normal3d(disp) ((disp)->Normal3d)
#define SET_Normal3d(disp, fn) ((disp)->Normal3d = fn)
#define CALL_Normal3dv(disp, parameters) (*((disp)->Normal3dv)) parameters
#define GET_Normal3dv(disp) ((disp)->Normal3dv)
#define SET_Normal3dv(disp, fn) ((disp)->Normal3dv = fn)
#define CALL_Normal3fv(disp, parameters) (*((disp)->Normal3fv)) parameters
#define GET_Normal3fv(disp) ((disp)->Normal3fv)
#define SET_Normal3fv(disp, fn) ((disp)->Normal3fv = fn)
#define CALL_Normal3i(disp, parameters) (*((disp)->Normal3i)) parameters
#define GET_Normal3i(disp) ((disp)->Normal3i)
#define SET_Normal3i(disp, fn) ((disp)->Normal3i = fn)
#define CALL_Normal3iv(disp, parameters) (*((disp)->Normal3iv)) parameters
#define GET_Normal3iv(disp) ((disp)->Normal3iv)
#define SET_Normal3iv(disp, fn) ((disp)->Normal3iv = fn)
#define CALL_Normal3s(disp, parameters) (*((disp)->Normal3s)) parameters
#define GET_Normal3s(disp) ((disp)->Normal3s)
#define SET_Normal3s(disp, fn) ((disp)->Normal3s = fn)
#define CALL_Normal3sv(disp, parameters) (*((disp)->Normal3sv)) parameters
#define GET_Normal3sv(disp) ((disp)->Normal3sv)
#define SET_Normal3sv(disp, fn) ((disp)->Normal3sv = fn)
#define CALL_RasterPos2d(disp, parameters) (*((disp)->RasterPos2d)) parameters
#define GET_RasterPos2d(disp) ((disp)->RasterPos2d)
#define SET_RasterPos2d(disp, fn) ((disp)->RasterPos2d = fn)
#define CALL_RasterPos2dv(disp, parameters) (*((disp)->RasterPos2dv)) parameters
#define GET_RasterPos2dv(disp) ((disp)->RasterPos2dv)
#define SET_RasterPos2dv(disp, fn) ((disp)->RasterPos2dv = fn)
#define CALL_RasterPos2f(disp, parameters) (*((disp)->RasterPos2f)) parameters
#define GET_RasterPos2f(disp) ((disp)->RasterPos2f)
#define SET_RasterPos2f(disp, fn) ((disp)->RasterPos2f = fn)
#define CALL_RasterPos2fv(disp, parameters) (*((disp)->RasterPos2fv)) parameters
#define GET_RasterPos2fv(disp) ((disp)->RasterPos2fv)
#define SET_RasterPos2fv(disp, fn) ((disp)->RasterPos2fv = fn)
#define CALL_RasterPos2i(disp, parameters) (*((disp)->RasterPos2i)) parameters
#define GET_RasterPos2i(disp) ((disp)->RasterPos2i)
#define SET_RasterPos2i(disp, fn) ((disp)->RasterPos2i = fn)
#define CALL_RasterPos2iv(disp, parameters) (*((disp)->RasterPos2iv)) parameters
#define GET_RasterPos2iv(disp) ((disp)->RasterPos2iv)
#define SET_RasterPos2iv(disp, fn) ((disp)->RasterPos2iv = fn)
#define CALL_RasterPos2s(disp, parameters) (*((disp)->RasterPos2s)) parameters
#define GET_RasterPos2s(disp) ((disp)->RasterPos2s)
#define SET_RasterPos2s(disp, fn) ((disp)->RasterPos2s = fn)
#define CALL_RasterPos2sv(disp, parameters) (*((disp)->RasterPos2sv)) parameters
#define GET_RasterPos2sv(disp) ((disp)->RasterPos2sv)
#define SET_RasterPos2sv(disp, fn) ((disp)->RasterPos2sv = fn)
#define CALL_RasterPos3d(disp, parameters) (*((disp)->RasterPos3d)) parameters
#define GET_RasterPos3d(disp) ((disp)->RasterPos3d)
#define SET_RasterPos3d(disp, fn) ((disp)->RasterPos3d = fn)
#define CALL_RasterPos3dv(disp, parameters) (*((disp)->RasterPos3dv)) parameters
#define GET_RasterPos3dv(disp) ((disp)->RasterPos3dv)
#define SET_RasterPos3dv(disp, fn) ((disp)->RasterPos3dv = fn)
#define CALL_RasterPos3f(disp, parameters) (*((disp)->RasterPos3f)) parameters
#define GET_RasterPos3f(disp) ((disp)->RasterPos3f)
#define SET_RasterPos3f(disp, fn) ((disp)->RasterPos3f = fn)
#define CALL_RasterPos3fv(disp, parameters) (*((disp)->RasterPos3fv)) parameters
#define GET_RasterPos3fv(disp) ((disp)->RasterPos3fv)
#define SET_RasterPos3fv(disp, fn) ((disp)->RasterPos3fv = fn)
#define CALL_RasterPos3i(disp, parameters) (*((disp)->RasterPos3i)) parameters
#define GET_RasterPos3i(disp) ((disp)->RasterPos3i)
#define SET_RasterPos3i(disp, fn) ((disp)->RasterPos3i = fn)
#define CALL_RasterPos3iv(disp, parameters) (*((disp)->RasterPos3iv)) parameters
#define GET_RasterPos3iv(disp) ((disp)->RasterPos3iv)
#define SET_RasterPos3iv(disp, fn) ((disp)->RasterPos3iv = fn)
#define CALL_RasterPos3s(disp, parameters) (*((disp)->RasterPos3s)) parameters
#define GET_RasterPos3s(disp) ((disp)->RasterPos3s)
#define SET_RasterPos3s(disp, fn) ((disp)->RasterPos3s = fn)
#define CALL_RasterPos3sv(disp, parameters) (*((disp)->RasterPos3sv)) parameters
#define GET_RasterPos3sv(disp) ((disp)->RasterPos3sv)
#define SET_RasterPos3sv(disp, fn) ((disp)->RasterPos3sv = fn)
#define CALL_RasterPos4d(disp, parameters) (*((disp)->RasterPos4d)) parameters
#define GET_RasterPos4d(disp) ((disp)->RasterPos4d)
#define SET_RasterPos4d(disp, fn) ((disp)->RasterPos4d = fn)
#define CALL_RasterPos4dv(disp, parameters) (*((disp)->RasterPos4dv)) parameters
#define GET_RasterPos4dv(disp) ((disp)->RasterPos4dv)
#define SET_RasterPos4dv(disp, fn) ((disp)->RasterPos4dv = fn)
#define CALL_RasterPos4f(disp, parameters) (*((disp)->RasterPos4f)) parameters
#define GET_RasterPos4f(disp) ((disp)->RasterPos4f)
#define SET_RasterPos4f(disp, fn) ((disp)->RasterPos4f = fn)
#define CALL_RasterPos4fv(disp, parameters) (*((disp)->RasterPos4fv)) parameters
#define GET_RasterPos4fv(disp) ((disp)->RasterPos4fv)
#define SET_RasterPos4fv(disp, fn) ((disp)->RasterPos4fv = fn)
#define CALL_RasterPos4i(disp, parameters) (*((disp)->RasterPos4i)) parameters
#define GET_RasterPos4i(disp) ((disp)->RasterPos4i)
#define SET_RasterPos4i(disp, fn) ((disp)->RasterPos4i = fn)
#define CALL_RasterPos4iv(disp, parameters) (*((disp)->RasterPos4iv)) parameters
#define GET_RasterPos4iv(disp) ((disp)->RasterPos4iv)
#define SET_RasterPos4iv(disp, fn) ((disp)->RasterPos4iv = fn)
#define CALL_RasterPos4s(disp, parameters) (*((disp)->RasterPos4s)) parameters
#define GET_RasterPos4s(disp) ((disp)->RasterPos4s)
#define SET_RasterPos4s(disp, fn) ((disp)->RasterPos4s = fn)
#define CALL_RasterPos4sv(disp, parameters) (*((disp)->RasterPos4sv)) parameters
#define GET_RasterPos4sv(disp) ((disp)->RasterPos4sv)
#define SET_RasterPos4sv(disp, fn) ((disp)->RasterPos4sv = fn)
#define CALL_Rectd(disp, parameters) (*((disp)->Rectd)) parameters
#define GET_Rectd(disp) ((disp)->Rectd)
#define SET_Rectd(disp, fn) ((disp)->Rectd = fn)
#define CALL_Rectdv(disp, parameters) (*((disp)->Rectdv)) parameters
#define GET_Rectdv(disp) ((disp)->Rectdv)
#define SET_Rectdv(disp, fn) ((disp)->Rectdv = fn)
#define CALL_Rectf(disp, parameters) (*((disp)->Rectf)) parameters
#define GET_Rectf(disp) ((disp)->Rectf)
#define SET_Rectf(disp, fn) ((disp)->Rectf = fn)
#define CALL_Rectfv(disp, parameters) (*((disp)->Rectfv)) parameters
#define GET_Rectfv(disp) ((disp)->Rectfv)
#define SET_Rectfv(disp, fn) ((disp)->Rectfv = fn)
#define CALL_Recti(disp, parameters) (*((disp)->Recti)) parameters
#define GET_Recti(disp) ((disp)->Recti)
#define SET_Recti(disp, fn) ((disp)->Recti = fn)
#define CALL_Rectiv(disp, parameters) (*((disp)->Rectiv)) parameters
#define GET_Rectiv(disp) ((disp)->Rectiv)
#define SET_Rectiv(disp, fn) ((disp)->Rectiv = fn)
#define CALL_Rects(disp, parameters) (*((disp)->Rects)) parameters
#define GET_Rects(disp) ((disp)->Rects)
#define SET_Rects(disp, fn) ((disp)->Rects = fn)
#define CALL_Rectsv(disp, parameters) (*((disp)->Rectsv)) parameters
#define GET_Rectsv(disp) ((disp)->Rectsv)
#define SET_Rectsv(disp, fn) ((disp)->Rectsv = fn)
#define CALL_TexCoord1d(disp, parameters) (*((disp)->TexCoord1d)) parameters
#define GET_TexCoord1d(disp) ((disp)->TexCoord1d)
#define SET_TexCoord1d(disp, fn) ((disp)->TexCoord1d = fn)
#define CALL_TexCoord1dv(disp, parameters) (*((disp)->TexCoord1dv)) parameters
#define GET_TexCoord1dv(disp) ((disp)->TexCoord1dv)
#define SET_TexCoord1dv(disp, fn) ((disp)->TexCoord1dv = fn)
#define CALL_TexCoord1f(disp, parameters) (*((disp)->TexCoord1f)) parameters
#define GET_TexCoord1f(disp) ((disp)->TexCoord1f)
#define SET_TexCoord1f(disp, fn) ((disp)->TexCoord1f = fn)
#define CALL_TexCoord1fv(disp, parameters) (*((disp)->TexCoord1fv)) parameters
#define GET_TexCoord1fv(disp) ((disp)->TexCoord1fv)
#define SET_TexCoord1fv(disp, fn) ((disp)->TexCoord1fv = fn)
#define CALL_TexCoord1i(disp, parameters) (*((disp)->TexCoord1i)) parameters
#define GET_TexCoord1i(disp) ((disp)->TexCoord1i)
#define SET_TexCoord1i(disp, fn) ((disp)->TexCoord1i = fn)
#define CALL_TexCoord1iv(disp, parameters) (*((disp)->TexCoord1iv)) parameters
#define GET_TexCoord1iv(disp) ((disp)->TexCoord1iv)
#define SET_TexCoord1iv(disp, fn) ((disp)->TexCoord1iv = fn)
#define CALL_TexCoord1s(disp, parameters) (*((disp)->TexCoord1s)) parameters
#define GET_TexCoord1s(disp) ((disp)->TexCoord1s)
#define SET_TexCoord1s(disp, fn) ((disp)->TexCoord1s = fn)
#define CALL_TexCoord1sv(disp, parameters) (*((disp)->TexCoord1sv)) parameters
#define GET_TexCoord1sv(disp) ((disp)->TexCoord1sv)
#define SET_TexCoord1sv(disp, fn) ((disp)->TexCoord1sv = fn)
#define CALL_TexCoord2d(disp, parameters) (*((disp)->TexCoord2d)) parameters
#define GET_TexCoord2d(disp) ((disp)->TexCoord2d)
#define SET_TexCoord2d(disp, fn) ((disp)->TexCoord2d = fn)
#define CALL_TexCoord2dv(disp, parameters) (*((disp)->TexCoord2dv)) parameters
#define GET_TexCoord2dv(disp) ((disp)->TexCoord2dv)
#define SET_TexCoord2dv(disp, fn) ((disp)->TexCoord2dv = fn)
#define CALL_TexCoord2f(disp, parameters) (*((disp)->TexCoord2f)) parameters
#define GET_TexCoord2f(disp) ((disp)->TexCoord2f)
#define SET_TexCoord2f(disp, fn) ((disp)->TexCoord2f = fn)
#define CALL_TexCoord2fv(disp, parameters) (*((disp)->TexCoord2fv)) parameters
#define GET_TexCoord2fv(disp) ((disp)->TexCoord2fv)
#define SET_TexCoord2fv(disp, fn) ((disp)->TexCoord2fv = fn)
#define CALL_TexCoord2i(disp, parameters) (*((disp)->TexCoord2i)) parameters
#define GET_TexCoord2i(disp) ((disp)->TexCoord2i)
#define SET_TexCoord2i(disp, fn) ((disp)->TexCoord2i = fn)
#define CALL_TexCoord2iv(disp, parameters) (*((disp)->TexCoord2iv)) parameters
#define GET_TexCoord2iv(disp) ((disp)->TexCoord2iv)
#define SET_TexCoord2iv(disp, fn) ((disp)->TexCoord2iv = fn)
#define CALL_TexCoord2s(disp, parameters) (*((disp)->TexCoord2s)) parameters
#define GET_TexCoord2s(disp) ((disp)->TexCoord2s)
#define SET_TexCoord2s(disp, fn) ((disp)->TexCoord2s = fn)
#define CALL_TexCoord2sv(disp, parameters) (*((disp)->TexCoord2sv)) parameters
#define GET_TexCoord2sv(disp) ((disp)->TexCoord2sv)
#define SET_TexCoord2sv(disp, fn) ((disp)->TexCoord2sv = fn)
#define CALL_TexCoord3d(disp, parameters) (*((disp)->TexCoord3d)) parameters
#define GET_TexCoord3d(disp) ((disp)->TexCoord3d)
#define SET_TexCoord3d(disp, fn) ((disp)->TexCoord3d = fn)
#define CALL_TexCoord3dv(disp, parameters) (*((disp)->TexCoord3dv)) parameters
#define GET_TexCoord3dv(disp) ((disp)->TexCoord3dv)
#define SET_TexCoord3dv(disp, fn) ((disp)->TexCoord3dv = fn)
#define CALL_TexCoord3f(disp, parameters) (*((disp)->TexCoord3f)) parameters
#define GET_TexCoord3f(disp) ((disp)->TexCoord3f)
#define SET_TexCoord3f(disp, fn) ((disp)->TexCoord3f = fn)
#define CALL_TexCoord3fv(disp, parameters) (*((disp)->TexCoord3fv)) parameters
#define GET_TexCoord3fv(disp) ((disp)->TexCoord3fv)
#define SET_TexCoord3fv(disp, fn) ((disp)->TexCoord3fv = fn)
#define CALL_TexCoord3i(disp, parameters) (*((disp)->TexCoord3i)) parameters
#define GET_TexCoord3i(disp) ((disp)->TexCoord3i)
#define SET_TexCoord3i(disp, fn) ((disp)->TexCoord3i = fn)
#define CALL_TexCoord3iv(disp, parameters) (*((disp)->TexCoord3iv)) parameters
#define GET_TexCoord3iv(disp) ((disp)->TexCoord3iv)
#define SET_TexCoord3iv(disp, fn) ((disp)->TexCoord3iv = fn)
#define CALL_TexCoord3s(disp, parameters) (*((disp)->TexCoord3s)) parameters
#define GET_TexCoord3s(disp) ((disp)->TexCoord3s)
#define SET_TexCoord3s(disp, fn) ((disp)->TexCoord3s = fn)
#define CALL_TexCoord3sv(disp, parameters) (*((disp)->TexCoord3sv)) parameters
#define GET_TexCoord3sv(disp) ((disp)->TexCoord3sv)
#define SET_TexCoord3sv(disp, fn) ((disp)->TexCoord3sv = fn)
#define CALL_TexCoord4d(disp, parameters) (*((disp)->TexCoord4d)) parameters
#define GET_TexCoord4d(disp) ((disp)->TexCoord4d)
#define SET_TexCoord4d(disp, fn) ((disp)->TexCoord4d = fn)
#define CALL_TexCoord4dv(disp, parameters) (*((disp)->TexCoord4dv)) parameters
#define GET_TexCoord4dv(disp) ((disp)->TexCoord4dv)
#define SET_TexCoord4dv(disp, fn) ((disp)->TexCoord4dv = fn)
#define CALL_TexCoord4f(disp, parameters) (*((disp)->TexCoord4f)) parameters
#define GET_TexCoord4f(disp) ((disp)->TexCoord4f)
#define SET_TexCoord4f(disp, fn) ((disp)->TexCoord4f = fn)
#define CALL_TexCoord4fv(disp, parameters) (*((disp)->TexCoord4fv)) parameters
#define GET_TexCoord4fv(disp) ((disp)->TexCoord4fv)
#define SET_TexCoord4fv(disp, fn) ((disp)->TexCoord4fv = fn)
#define CALL_TexCoord4i(disp, parameters) (*((disp)->TexCoord4i)) parameters
#define GET_TexCoord4i(disp) ((disp)->TexCoord4i)
#define SET_TexCoord4i(disp, fn) ((disp)->TexCoord4i = fn)
#define CALL_TexCoord4iv(disp, parameters) (*((disp)->TexCoord4iv)) parameters
#define GET_TexCoord4iv(disp) ((disp)->TexCoord4iv)
#define SET_TexCoord4iv(disp, fn) ((disp)->TexCoord4iv = fn)
#define CALL_TexCoord4s(disp, parameters) (*((disp)->TexCoord4s)) parameters
#define GET_TexCoord4s(disp) ((disp)->TexCoord4s)
#define SET_TexCoord4s(disp, fn) ((disp)->TexCoord4s = fn)
#define CALL_TexCoord4sv(disp, parameters) (*((disp)->TexCoord4sv)) parameters
#define GET_TexCoord4sv(disp) ((disp)->TexCoord4sv)
#define SET_TexCoord4sv(disp, fn) ((disp)->TexCoord4sv = fn)
#define CALL_Vertex2d(disp, parameters) (*((disp)->Vertex2d)) parameters
#define GET_Vertex2d(disp) ((disp)->Vertex2d)
#define SET_Vertex2d(disp, fn) ((disp)->Vertex2d = fn)
#define CALL_Vertex2dv(disp, parameters) (*((disp)->Vertex2dv)) parameters
#define GET_Vertex2dv(disp) ((disp)->Vertex2dv)
#define SET_Vertex2dv(disp, fn) ((disp)->Vertex2dv = fn)
#define CALL_Vertex2f(disp, parameters) (*((disp)->Vertex2f)) parameters
#define GET_Vertex2f(disp) ((disp)->Vertex2f)
#define SET_Vertex2f(disp, fn) ((disp)->Vertex2f = fn)
#define CALL_Vertex2fv(disp, parameters) (*((disp)->Vertex2fv)) parameters
#define GET_Vertex2fv(disp) ((disp)->Vertex2fv)
#define SET_Vertex2fv(disp, fn) ((disp)->Vertex2fv = fn)
#define CALL_Vertex2i(disp, parameters) (*((disp)->Vertex2i)) parameters
#define GET_Vertex2i(disp) ((disp)->Vertex2i)
#define SET_Vertex2i(disp, fn) ((disp)->Vertex2i = fn)
#define CALL_Vertex2iv(disp, parameters) (*((disp)->Vertex2iv)) parameters
#define GET_Vertex2iv(disp) ((disp)->Vertex2iv)
#define SET_Vertex2iv(disp, fn) ((disp)->Vertex2iv = fn)
#define CALL_Vertex2s(disp, parameters) (*((disp)->Vertex2s)) parameters
#define GET_Vertex2s(disp) ((disp)->Vertex2s)
#define SET_Vertex2s(disp, fn) ((disp)->Vertex2s = fn)
#define CALL_Vertex2sv(disp, parameters) (*((disp)->Vertex2sv)) parameters
#define GET_Vertex2sv(disp) ((disp)->Vertex2sv)
#define SET_Vertex2sv(disp, fn) ((disp)->Vertex2sv = fn)
#define CALL_Vertex3d(disp, parameters) (*((disp)->Vertex3d)) parameters
#define GET_Vertex3d(disp) ((disp)->Vertex3d)
#define SET_Vertex3d(disp, fn) ((disp)->Vertex3d = fn)
#define CALL_Vertex3dv(disp, parameters) (*((disp)->Vertex3dv)) parameters
#define GET_Vertex3dv(disp) ((disp)->Vertex3dv)
#define SET_Vertex3dv(disp, fn) ((disp)->Vertex3dv = fn)
#define CALL_Vertex3f(disp, parameters) (*((disp)->Vertex3f)) parameters
#define GET_Vertex3f(disp) ((disp)->Vertex3f)
#define SET_Vertex3f(disp, fn) ((disp)->Vertex3f = fn)
#define CALL_Vertex3fv(disp, parameters) (*((disp)->Vertex3fv)) parameters
#define GET_Vertex3fv(disp) ((disp)->Vertex3fv)
#define SET_Vertex3fv(disp, fn) ((disp)->Vertex3fv = fn)
#define CALL_Vertex3i(disp, parameters) (*((disp)->Vertex3i)) parameters
#define GET_Vertex3i(disp) ((disp)->Vertex3i)
#define SET_Vertex3i(disp, fn) ((disp)->Vertex3i = fn)
#define CALL_Vertex3iv(disp, parameters) (*((disp)->Vertex3iv)) parameters
#define GET_Vertex3iv(disp) ((disp)->Vertex3iv)
#define SET_Vertex3iv(disp, fn) ((disp)->Vertex3iv = fn)
#define CALL_Vertex3s(disp, parameters) (*((disp)->Vertex3s)) parameters
#define GET_Vertex3s(disp) ((disp)->Vertex3s)
#define SET_Vertex3s(disp, fn) ((disp)->Vertex3s = fn)
#define CALL_Vertex3sv(disp, parameters) (*((disp)->Vertex3sv)) parameters
#define GET_Vertex3sv(disp) ((disp)->Vertex3sv)
#define SET_Vertex3sv(disp, fn) ((disp)->Vertex3sv = fn)
#define CALL_Vertex4d(disp, parameters) (*((disp)->Vertex4d)) parameters
#define GET_Vertex4d(disp) ((disp)->Vertex4d)
#define SET_Vertex4d(disp, fn) ((disp)->Vertex4d = fn)
#define CALL_Vertex4dv(disp, parameters) (*((disp)->Vertex4dv)) parameters
#define GET_Vertex4dv(disp) ((disp)->Vertex4dv)
#define SET_Vertex4dv(disp, fn) ((disp)->Vertex4dv = fn)
#define CALL_Vertex4f(disp, parameters) (*((disp)->Vertex4f)) parameters
#define GET_Vertex4f(disp) ((disp)->Vertex4f)
#define SET_Vertex4f(disp, fn) ((disp)->Vertex4f = fn)
#define CALL_Vertex4fv(disp, parameters) (*((disp)->Vertex4fv)) parameters
#define GET_Vertex4fv(disp) ((disp)->Vertex4fv)
#define SET_Vertex4fv(disp, fn) ((disp)->Vertex4fv = fn)
#define CALL_Vertex4i(disp, parameters) (*((disp)->Vertex4i)) parameters
#define GET_Vertex4i(disp) ((disp)->Vertex4i)
#define SET_Vertex4i(disp, fn) ((disp)->Vertex4i = fn)
#define CALL_Vertex4iv(disp, parameters) (*((disp)->Vertex4iv)) parameters
#define GET_Vertex4iv(disp) ((disp)->Vertex4iv)
#define SET_Vertex4iv(disp, fn) ((disp)->Vertex4iv = fn)
#define CALL_Vertex4s(disp, parameters) (*((disp)->Vertex4s)) parameters
#define GET_Vertex4s(disp) ((disp)->Vertex4s)
#define SET_Vertex4s(disp, fn) ((disp)->Vertex4s = fn)
#define CALL_Vertex4sv(disp, parameters) (*((disp)->Vertex4sv)) parameters
#define GET_Vertex4sv(disp) ((disp)->Vertex4sv)
#define SET_Vertex4sv(disp, fn) ((disp)->Vertex4sv = fn)
#define CALL_ClipPlane(disp, parameters) (*((disp)->ClipPlane)) parameters
#define GET_ClipPlane(disp) ((disp)->ClipPlane)
#define SET_ClipPlane(disp, fn) ((disp)->ClipPlane = fn)
#define CALL_ColorMaterial(disp, parameters) (*((disp)->ColorMaterial)) parameters
#define GET_ColorMaterial(disp) ((disp)->ColorMaterial)
#define SET_ColorMaterial(disp, fn) ((disp)->ColorMaterial = fn)
#define CALL_Fogi(disp, parameters) (*((disp)->Fogi)) parameters
#define GET_Fogi(disp) ((disp)->Fogi)
#define SET_Fogi(disp, fn) ((disp)->Fogi = fn)
#define CALL_Fogiv(disp, parameters) (*((disp)->Fogiv)) parameters
#define GET_Fogiv(disp) ((disp)->Fogiv)
#define SET_Fogiv(disp, fn) ((disp)->Fogiv = fn)
#define CALL_Lighti(disp, parameters) (*((disp)->Lighti)) parameters
#define GET_Lighti(disp) ((disp)->Lighti)
#define SET_Lighti(disp, fn) ((disp)->Lighti = fn)
#define CALL_Lightiv(disp, parameters) (*((disp)->Lightiv)) parameters
#define GET_Lightiv(disp) ((disp)->Lightiv)
#define SET_Lightiv(disp, fn) ((disp)->Lightiv = fn)
#define CALL_LightModeli(disp, parameters) (*((disp)->LightModeli)) parameters
#define GET_LightModeli(disp) ((disp)->LightModeli)
#define SET_LightModeli(disp, fn) ((disp)->LightModeli = fn)
#define CALL_LightModeliv(disp, parameters) (*((disp)->LightModeliv)) parameters
#define GET_LightModeliv(disp) ((disp)->LightModeliv)
#define SET_LightModeliv(disp, fn) ((disp)->LightModeliv = fn)
#define CALL_LineStipple(disp, parameters) (*((disp)->LineStipple)) parameters
#define GET_LineStipple(disp) ((disp)->LineStipple)
#define SET_LineStipple(disp, fn) ((disp)->LineStipple = fn)
#define CALL_Materiali(disp, parameters) (*((disp)->Materiali)) parameters
#define GET_Materiali(disp) ((disp)->Materiali)
#define SET_Materiali(disp, fn) ((disp)->Materiali = fn)
#define CALL_Materialiv(disp, parameters) (*((disp)->Materialiv)) parameters
#define GET_Materialiv(disp) ((disp)->Materialiv)
#define SET_Materialiv(disp, fn) ((disp)->Materialiv = fn)
#define CALL_PolygonMode(disp, parameters) (*((disp)->PolygonMode)) parameters
#define GET_PolygonMode(disp) ((disp)->PolygonMode)
#define SET_PolygonMode(disp, fn) ((disp)->PolygonMode = fn)
#define CALL_PolygonStipple(disp, parameters) (*((disp)->PolygonStipple)) parameters
#define GET_PolygonStipple(disp) ((disp)->PolygonStipple)
#define SET_PolygonStipple(disp, fn) ((disp)->PolygonStipple = fn)
#define CALL_TexImage1D(disp, parameters) (*((disp)->TexImage1D)) parameters
#define GET_TexImage1D(disp) ((disp)->TexImage1D)
#define SET_TexImage1D(disp, fn) ((disp)->TexImage1D = fn)
#define CALL_TexGend(disp, parameters) (*((disp)->TexGend)) parameters
#define GET_TexGend(disp) ((disp)->TexGend)
#define SET_TexGend(disp, fn) ((disp)->TexGend = fn)
#define CALL_TexGendv(disp, parameters) (*((disp)->TexGendv)) parameters
#define GET_TexGendv(disp) ((disp)->TexGendv)
#define SET_TexGendv(disp, fn) ((disp)->TexGendv = fn)
#define CALL_FeedbackBuffer(disp, parameters) (*((disp)->FeedbackBuffer)) parameters
#define GET_FeedbackBuffer(disp) ((disp)->FeedbackBuffer)
#define SET_FeedbackBuffer(disp, fn) ((disp)->FeedbackBuffer = fn)
#define CALL_SelectBuffer(disp, parameters) (*((disp)->SelectBuffer)) parameters
#define GET_SelectBuffer(disp) ((disp)->SelectBuffer)
#define SET_SelectBuffer(disp, fn) ((disp)->SelectBuffer = fn)
#define CALL_RenderMode(disp, parameters) (*((disp)->RenderMode)) parameters
#define GET_RenderMode(disp) ((disp)->RenderMode)
#define SET_RenderMode(disp, fn) ((disp)->RenderMode = fn)
#define CALL_InitNames(disp, parameters) (*((disp)->InitNames)) parameters
#define GET_InitNames(disp) ((disp)->InitNames)
#define SET_InitNames(disp, fn) ((disp)->InitNames = fn)
#define CALL_LoadName(disp, parameters) (*((disp)->LoadName)) parameters
#define GET_LoadName(disp) ((disp)->LoadName)
#define SET_LoadName(disp, fn) ((disp)->LoadName = fn)
#define CALL_PassThrough(disp, parameters) (*((disp)->PassThrough)) parameters
#define GET_PassThrough(disp) ((disp)->PassThrough)
#define SET_PassThrough(disp, fn) ((disp)->PassThrough = fn)
#define CALL_PopName(disp, parameters) (*((disp)->PopName)) parameters
#define GET_PopName(disp) ((disp)->PopName)
#define SET_PopName(disp, fn) ((disp)->PopName = fn)
#define CALL_PushName(disp, parameters) (*((disp)->PushName)) parameters
#define GET_PushName(disp) ((disp)->PushName)
#define SET_PushName(disp, fn) ((disp)->PushName = fn)
#define CALL_DrawBuffer(disp, parameters) (*((disp)->DrawBuffer)) parameters
#define GET_DrawBuffer(disp) ((disp)->DrawBuffer)
#define SET_DrawBuffer(disp, fn) ((disp)->DrawBuffer = fn)
#define CALL_ClearAccum(disp, parameters) (*((disp)->ClearAccum)) parameters
#define GET_ClearAccum(disp) ((disp)->ClearAccum)
#define SET_ClearAccum(disp, fn) ((disp)->ClearAccum = fn)
#define CALL_ClearIndex(disp, parameters) (*((disp)->ClearIndex)) parameters
#define GET_ClearIndex(disp) ((disp)->ClearIndex)
#define SET_ClearIndex(disp, fn) ((disp)->ClearIndex = fn)
#define CALL_ClearDepth(disp, parameters) (*((disp)->ClearDepth)) parameters
#define GET_ClearDepth(disp) ((disp)->ClearDepth)
#define SET_ClearDepth(disp, fn) ((disp)->ClearDepth = fn)
#define CALL_IndexMask(disp, parameters) (*((disp)->IndexMask)) parameters
#define GET_IndexMask(disp) ((disp)->IndexMask)
#define SET_IndexMask(disp, fn) ((disp)->IndexMask = fn)
#define CALL_Accum(disp, parameters) (*((disp)->Accum)) parameters
#define GET_Accum(disp) ((disp)->Accum)
#define SET_Accum(disp, fn) ((disp)->Accum = fn)
#define CALL_PopAttrib(disp, parameters) (*((disp)->PopAttrib)) parameters
#define GET_PopAttrib(disp) ((disp)->PopAttrib)
#define SET_PopAttrib(disp, fn) ((disp)->PopAttrib = fn)
#define CALL_PushAttrib(disp, parameters) (*((disp)->PushAttrib)) parameters
#define GET_PushAttrib(disp) ((disp)->PushAttrib)
#define SET_PushAttrib(disp, fn) ((disp)->PushAttrib = fn)
#define CALL_Map1d(disp, parameters) (*((disp)->Map1d)) parameters
#define GET_Map1d(disp) ((disp)->Map1d)
#define SET_Map1d(disp, fn) ((disp)->Map1d = fn)
#define CALL_Map1f(disp, parameters) (*((disp)->Map1f)) parameters
#define GET_Map1f(disp) ((disp)->Map1f)
#define SET_Map1f(disp, fn) ((disp)->Map1f = fn)
#define CALL_Map2d(disp, parameters) (*((disp)->Map2d)) parameters
#define GET_Map2d(disp) ((disp)->Map2d)
#define SET_Map2d(disp, fn) ((disp)->Map2d = fn)
#define CALL_Map2f(disp, parameters) (*((disp)->Map2f)) parameters
#define GET_Map2f(disp) ((disp)->Map2f)
#define SET_Map2f(disp, fn) ((disp)->Map2f = fn)
#define CALL_MapGrid1d(disp, parameters) (*((disp)->MapGrid1d)) parameters
#define GET_MapGrid1d(disp) ((disp)->MapGrid1d)
#define SET_MapGrid1d(disp, fn) ((disp)->MapGrid1d = fn)
#define CALL_MapGrid1f(disp, parameters) (*((disp)->MapGrid1f)) parameters
#define GET_MapGrid1f(disp) ((disp)->MapGrid1f)
#define SET_MapGrid1f(disp, fn) ((disp)->MapGrid1f = fn)
#define CALL_MapGrid2d(disp, parameters) (*((disp)->MapGrid2d)) parameters
#define GET_MapGrid2d(disp) ((disp)->MapGrid2d)
#define SET_MapGrid2d(disp, fn) ((disp)->MapGrid2d = fn)
#define CALL_MapGrid2f(disp, parameters) (*((disp)->MapGrid2f)) parameters
#define GET_MapGrid2f(disp) ((disp)->MapGrid2f)
#define SET_MapGrid2f(disp, fn) ((disp)->MapGrid2f = fn)
#define CALL_EvalCoord1d(disp, parameters) (*((disp)->EvalCoord1d)) parameters
#define GET_EvalCoord1d(disp) ((disp)->EvalCoord1d)
#define SET_EvalCoord1d(disp, fn) ((disp)->EvalCoord1d = fn)
#define CALL_EvalCoord1dv(disp, parameters) (*((disp)->EvalCoord1dv)) parameters
#define GET_EvalCoord1dv(disp) ((disp)->EvalCoord1dv)
#define SET_EvalCoord1dv(disp, fn) ((disp)->EvalCoord1dv = fn)
#define CALL_EvalCoord1f(disp, parameters) (*((disp)->EvalCoord1f)) parameters
#define GET_EvalCoord1f(disp) ((disp)->EvalCoord1f)
#define SET_EvalCoord1f(disp, fn) ((disp)->EvalCoord1f = fn)
#define CALL_EvalCoord1fv(disp, parameters) (*((disp)->EvalCoord1fv)) parameters
#define GET_EvalCoord1fv(disp) ((disp)->EvalCoord1fv)
#define SET_EvalCoord1fv(disp, fn) ((disp)->EvalCoord1fv = fn)
#define CALL_EvalCoord2d(disp, parameters) (*((disp)->EvalCoord2d)) parameters
#define GET_EvalCoord2d(disp) ((disp)->EvalCoord2d)
#define SET_EvalCoord2d(disp, fn) ((disp)->EvalCoord2d = fn)
#define CALL_EvalCoord2dv(disp, parameters) (*((disp)->EvalCoord2dv)) parameters
#define GET_EvalCoord2dv(disp) ((disp)->EvalCoord2dv)
#define SET_EvalCoord2dv(disp, fn) ((disp)->EvalCoord2dv = fn)
#define CALL_EvalCoord2f(disp, parameters) (*((disp)->EvalCoord2f)) parameters
#define GET_EvalCoord2f(disp) ((disp)->EvalCoord2f)
#define SET_EvalCoord2f(disp, fn) ((disp)->EvalCoord2f = fn)
#define CALL_EvalCoord2fv(disp, parameters) (*((disp)->EvalCoord2fv)) parameters
#define GET_EvalCoord2fv(disp) ((disp)->EvalCoord2fv)
#define SET_EvalCoord2fv(disp, fn) ((disp)->EvalCoord2fv = fn)
#define CALL_EvalMesh1(disp, parameters) (*((disp)->EvalMesh1)) parameters
#define GET_EvalMesh1(disp) ((disp)->EvalMesh1)
#define SET_EvalMesh1(disp, fn) ((disp)->EvalMesh1 = fn)
#define CALL_EvalPoint1(disp, parameters) (*((disp)->EvalPoint1)) parameters
#define GET_EvalPoint1(disp) ((disp)->EvalPoint1)
#define SET_EvalPoint1(disp, fn) ((disp)->EvalPoint1 = fn)
#define CALL_EvalMesh2(disp, parameters) (*((disp)->EvalMesh2)) parameters
#define GET_EvalMesh2(disp) ((disp)->EvalMesh2)
#define SET_EvalMesh2(disp, fn) ((disp)->EvalMesh2 = fn)
#define CALL_EvalPoint2(disp, parameters) (*((disp)->EvalPoint2)) parameters
#define GET_EvalPoint2(disp) ((disp)->EvalPoint2)
#define SET_EvalPoint2(disp, fn) ((disp)->EvalPoint2 = fn)
#define CALL_PixelZoom(disp, parameters) (*((disp)->PixelZoom)) parameters
#define GET_PixelZoom(disp) ((disp)->PixelZoom)
#define SET_PixelZoom(disp, fn) ((disp)->PixelZoom = fn)
#define CALL_PixelTransferf(disp, parameters) (*((disp)->PixelTransferf)) parameters
#define GET_PixelTransferf(disp) ((disp)->PixelTransferf)
#define SET_PixelTransferf(disp, fn) ((disp)->PixelTransferf = fn)
#define CALL_PixelTransferi(disp, parameters) (*((disp)->PixelTransferi)) parameters
#define GET_PixelTransferi(disp) ((disp)->PixelTransferi)
#define SET_PixelTransferi(disp, fn) ((disp)->PixelTransferi = fn)
#define CALL_PixelStoref(disp, parameters) (*((disp)->PixelStoref)) parameters
#define GET_PixelStoref(disp) ((disp)->PixelStoref)
#define SET_PixelStoref(disp, fn) ((disp)->PixelStoref = fn)
#define CALL_PixelMapfv(disp, parameters) (*((disp)->PixelMapfv)) parameters
#define GET_PixelMapfv(disp) ((disp)->PixelMapfv)
#define SET_PixelMapfv(disp, fn) ((disp)->PixelMapfv = fn)
#define CALL_PixelMapuiv(disp, parameters) (*((disp)->PixelMapuiv)) parameters
#define GET_PixelMapuiv(disp) ((disp)->PixelMapuiv)
#define SET_PixelMapuiv(disp, fn) ((disp)->PixelMapuiv = fn)
#define CALL_PixelMapusv(disp, parameters) (*((disp)->PixelMapusv)) parameters
#define GET_PixelMapusv(disp) ((disp)->PixelMapusv)
#define SET_PixelMapusv(disp, fn) ((disp)->PixelMapusv = fn)
#define CALL_ReadBuffer(disp, parameters) (*((disp)->ReadBuffer)) parameters
#define GET_ReadBuffer(disp) ((disp)->ReadBuffer)
#define SET_ReadBuffer(disp, fn) ((disp)->ReadBuffer = fn)
#define CALL_CopyPixels(disp, parameters) (*((disp)->CopyPixels)) parameters
#define GET_CopyPixels(disp) ((disp)->CopyPixels)
#define SET_CopyPixels(disp, fn) ((disp)->CopyPixels = fn)
#define CALL_DrawPixels(disp, parameters) (*((disp)->DrawPixels)) parameters
#define GET_DrawPixels(disp) ((disp)->DrawPixels)
#define SET_DrawPixels(disp, fn) ((disp)->DrawPixels = fn)
#define CALL_GetClipPlane(disp, parameters) (*((disp)->GetClipPlane)) parameters
#define GET_GetClipPlane(disp) ((disp)->GetClipPlane)
#define SET_GetClipPlane(disp, fn) ((disp)->GetClipPlane = fn)
#define CALL_GetDoublev(disp, parameters) (*((disp)->GetDoublev)) parameters
#define GET_GetDoublev(disp) ((disp)->GetDoublev)
#define SET_GetDoublev(disp, fn) ((disp)->GetDoublev = fn)
#define CALL_GetLightiv(disp, parameters) (*((disp)->GetLightiv)) parameters
#define GET_GetLightiv(disp) ((disp)->GetLightiv)
#define SET_GetLightiv(disp, fn) ((disp)->GetLightiv = fn)
#define CALL_GetMapdv(disp, parameters) (*((disp)->GetMapdv)) parameters
#define GET_GetMapdv(disp) ((disp)->GetMapdv)
#define SET_GetMapdv(disp, fn) ((disp)->GetMapdv = fn)
#define CALL_GetMapfv(disp, parameters) (*((disp)->GetMapfv)) parameters
#define GET_GetMapfv(disp) ((disp)->GetMapfv)
#define SET_GetMapfv(disp, fn) ((disp)->GetMapfv = fn)
#define CALL_GetMapiv(disp, parameters) (*((disp)->GetMapiv)) parameters
#define GET_GetMapiv(disp) ((disp)->GetMapiv)
#define SET_GetMapiv(disp, fn) ((disp)->GetMapiv = fn)
#define CALL_GetMaterialiv(disp, parameters) (*((disp)->GetMaterialiv)) parameters
#define GET_GetMaterialiv(disp) ((disp)->GetMaterialiv)
#define SET_GetMaterialiv(disp, fn) ((disp)->GetMaterialiv = fn)
#define CALL_GetPixelMapfv(disp, parameters) (*((disp)->GetPixelMapfv)) parameters
#define GET_GetPixelMapfv(disp) ((disp)->GetPixelMapfv)
#define SET_GetPixelMapfv(disp, fn) ((disp)->GetPixelMapfv = fn)
#define CALL_GetPixelMapuiv(disp, parameters) (*((disp)->GetPixelMapuiv)) parameters
#define GET_GetPixelMapuiv(disp) ((disp)->GetPixelMapuiv)
#define SET_GetPixelMapuiv(disp, fn) ((disp)->GetPixelMapuiv = fn)
#define CALL_GetPixelMapusv(disp, parameters) (*((disp)->GetPixelMapusv)) parameters
#define GET_GetPixelMapusv(disp) ((disp)->GetPixelMapusv)
#define SET_GetPixelMapusv(disp, fn) ((disp)->GetPixelMapusv = fn)
#define CALL_GetPolygonStipple(disp, parameters) (*((disp)->GetPolygonStipple)) parameters
#define GET_GetPolygonStipple(disp) ((disp)->GetPolygonStipple)
#define SET_GetPolygonStipple(disp, fn) ((disp)->GetPolygonStipple = fn)
#define CALL_GetTexGendv(disp, parameters) (*((disp)->GetTexGendv)) parameters
#define GET_GetTexGendv(disp) ((disp)->GetTexGendv)
#define SET_GetTexGendv(disp, fn) ((disp)->GetTexGendv = fn)
#define CALL_GetTexImage(disp, parameters) (*((disp)->GetTexImage)) parameters
#define GET_GetTexImage(disp) ((disp)->GetTexImage)
#define SET_GetTexImage(disp, fn) ((disp)->GetTexImage = fn)
#define CALL_GetTexLevelParameterfv(disp, parameters) (*((disp)->GetTexLevelParameterfv)) parameters
#define GET_GetTexLevelParameterfv(disp) ((disp)->GetTexLevelParameterfv)
#define SET_GetTexLevelParameterfv(disp, fn) ((disp)->GetTexLevelParameterfv = fn)
#define CALL_GetTexLevelParameteriv(disp, parameters) (*((disp)->GetTexLevelParameteriv)) parameters
#define GET_GetTexLevelParameteriv(disp) ((disp)->GetTexLevelParameteriv)
#define SET_GetTexLevelParameteriv(disp, fn) ((disp)->GetTexLevelParameteriv = fn)
#define CALL_IsList(disp, parameters) (*((disp)->IsList)) parameters
#define GET_IsList(disp) ((disp)->IsList)
#define SET_IsList(disp, fn) ((disp)->IsList = fn)
#define CALL_DepthRange(disp, parameters) (*((disp)->DepthRange)) parameters
#define GET_DepthRange(disp) ((disp)->DepthRange)
#define SET_DepthRange(disp, fn) ((disp)->DepthRange = fn)
#define CALL_Frustum(disp, parameters) (*((disp)->Frustum)) parameters
#define GET_Frustum(disp) ((disp)->Frustum)
#define SET_Frustum(disp, fn) ((disp)->Frustum = fn)
#define CALL_LoadMatrixd(disp, parameters) (*((disp)->LoadMatrixd)) parameters
#define GET_LoadMatrixd(disp) ((disp)->LoadMatrixd)
#define SET_LoadMatrixd(disp, fn) ((disp)->LoadMatrixd = fn)
#define CALL_MultMatrixd(disp, parameters) (*((disp)->MultMatrixd)) parameters
#define GET_MultMatrixd(disp) ((disp)->MultMatrixd)
#define SET_MultMatrixd(disp, fn) ((disp)->MultMatrixd = fn)
#define CALL_Ortho(disp, parameters) (*((disp)->Ortho)) parameters
#define GET_Ortho(disp) ((disp)->Ortho)
#define SET_Ortho(disp, fn) ((disp)->Ortho = fn)
#define CALL_Rotated(disp, parameters) (*((disp)->Rotated)) parameters
#define GET_Rotated(disp) ((disp)->Rotated)
#define SET_Rotated(disp, fn) ((disp)->Rotated = fn)
#define CALL_Scaled(disp, parameters) (*((disp)->Scaled)) parameters
#define GET_Scaled(disp) ((disp)->Scaled)
#define SET_Scaled(disp, fn) ((disp)->Scaled = fn)
#define CALL_Translated(disp, parameters) (*((disp)->Translated)) parameters
#define GET_Translated(disp) ((disp)->Translated)
#define SET_Translated(disp, fn) ((disp)->Translated = fn)
#define CALL_ArrayElement(disp, parameters) (*((disp)->ArrayElement)) parameters
#define GET_ArrayElement(disp) ((disp)->ArrayElement)
#define SET_ArrayElement(disp, fn) ((disp)->ArrayElement = fn)
#define CALL_EdgeFlagPointer(disp, parameters) (*((disp)->EdgeFlagPointer)) parameters
#define GET_EdgeFlagPointer(disp) ((disp)->EdgeFlagPointer)
#define SET_EdgeFlagPointer(disp, fn) ((disp)->EdgeFlagPointer = fn)
#define CALL_IndexPointer(disp, parameters) (*((disp)->IndexPointer)) parameters
#define GET_IndexPointer(disp) ((disp)->IndexPointer)
#define SET_IndexPointer(disp, fn) ((disp)->IndexPointer = fn)
#define CALL_Indexub(disp, parameters) (*((disp)->Indexub)) parameters
#define GET_Indexub(disp) ((disp)->Indexub)
#define SET_Indexub(disp, fn) ((disp)->Indexub = fn)
#define CALL_Indexubv(disp, parameters) (*((disp)->Indexubv)) parameters
#define GET_Indexubv(disp) ((disp)->Indexubv)
#define SET_Indexubv(disp, fn) ((disp)->Indexubv = fn)
#define CALL_InterleavedArrays(disp, parameters) (*((disp)->InterleavedArrays)) parameters
#define GET_InterleavedArrays(disp) ((disp)->InterleavedArrays)
#define SET_InterleavedArrays(disp, fn) ((disp)->InterleavedArrays = fn)
#define CALL_AreTexturesResident(disp, parameters) (*((disp)->AreTexturesResident)) parameters
#define GET_AreTexturesResident(disp) ((disp)->AreTexturesResident)
#define SET_AreTexturesResident(disp, fn) ((disp)->AreTexturesResident = fn)
#define CALL_CopyTexImage1D(disp, parameters) (*((disp)->CopyTexImage1D)) parameters
#define GET_CopyTexImage1D(disp) ((disp)->CopyTexImage1D)
#define SET_CopyTexImage1D(disp, fn) ((disp)->CopyTexImage1D = fn)
#define CALL_CopyTexSubImage1D(disp, parameters) (*((disp)->CopyTexSubImage1D)) parameters
#define GET_CopyTexSubImage1D(disp) ((disp)->CopyTexSubImage1D)
#define SET_CopyTexSubImage1D(disp, fn) ((disp)->CopyTexSubImage1D = fn)
#define CALL_PrioritizeTextures(disp, parameters) (*((disp)->PrioritizeTextures)) parameters
#define GET_PrioritizeTextures(disp) ((disp)->PrioritizeTextures)
#define SET_PrioritizeTextures(disp, fn) ((disp)->PrioritizeTextures = fn)
#define CALL_TexSubImage1D(disp, parameters) (*((disp)->TexSubImage1D)) parameters
#define GET_TexSubImage1D(disp) ((disp)->TexSubImage1D)
#define SET_TexSubImage1D(disp, fn) ((disp)->TexSubImage1D = fn)
#define CALL_PopClientAttrib(disp, parameters) (*((disp)->PopClientAttrib)) parameters
#define GET_PopClientAttrib(disp) ((disp)->PopClientAttrib)
#define SET_PopClientAttrib(disp, fn) ((disp)->PopClientAttrib = fn)
#define CALL_PushClientAttrib(disp, parameters) (*((disp)->PushClientAttrib)) parameters
#define GET_PushClientAttrib(disp) ((disp)->PushClientAttrib)
#define SET_PushClientAttrib(disp, fn) ((disp)->PushClientAttrib = fn)
#define CALL_DrawRangeElements(disp, parameters) (*((disp)->DrawRangeElements)) parameters
#define GET_DrawRangeElements(disp) ((disp)->DrawRangeElements)
#define SET_DrawRangeElements(disp, fn) ((disp)->DrawRangeElements = fn)
#define CALL_ColorTable(disp, parameters) (*((disp)->ColorTable)) parameters
#define GET_ColorTable(disp) ((disp)->ColorTable)
#define SET_ColorTable(disp, fn) ((disp)->ColorTable = fn)
#define CALL_ColorTableParameterfv(disp, parameters) (*((disp)->ColorTableParameterfv)) parameters
#define GET_ColorTableParameterfv(disp) ((disp)->ColorTableParameterfv)
#define SET_ColorTableParameterfv(disp, fn) ((disp)->ColorTableParameterfv = fn)
#define CALL_ColorTableParameteriv(disp, parameters) (*((disp)->ColorTableParameteriv)) parameters
#define GET_ColorTableParameteriv(disp) ((disp)->ColorTableParameteriv)
#define SET_ColorTableParameteriv(disp, fn) ((disp)->ColorTableParameteriv = fn)
#define CALL_CopyColorTable(disp, parameters) (*((disp)->CopyColorTable)) parameters
#define GET_CopyColorTable(disp) ((disp)->CopyColorTable)
#define SET_CopyColorTable(disp, fn) ((disp)->CopyColorTable = fn)
#define CALL_GetColorTable(disp, parameters) (*((disp)->GetColorTable)) parameters
#define GET_GetColorTable(disp) ((disp)->GetColorTable)
#define SET_GetColorTable(disp, fn) ((disp)->GetColorTable = fn)
#define CALL_GetColorTableParameterfv(disp, parameters) (*((disp)->GetColorTableParameterfv)) parameters
#define GET_GetColorTableParameterfv(disp) ((disp)->GetColorTableParameterfv)
#define SET_GetColorTableParameterfv(disp, fn) ((disp)->GetColorTableParameterfv = fn)
#define CALL_GetColorTableParameteriv(disp, parameters) (*((disp)->GetColorTableParameteriv)) parameters
#define GET_GetColorTableParameteriv(disp) ((disp)->GetColorTableParameteriv)
#define SET_GetColorTableParameteriv(disp, fn) ((disp)->GetColorTableParameteriv = fn)
#define CALL_ColorSubTable(disp, parameters) (*((disp)->ColorSubTable)) parameters
#define GET_ColorSubTable(disp) ((disp)->ColorSubTable)
#define SET_ColorSubTable(disp, fn) ((disp)->ColorSubTable = fn)
#define CALL_CopyColorSubTable(disp, parameters) (*((disp)->CopyColorSubTable)) parameters
#define GET_CopyColorSubTable(disp) ((disp)->CopyColorSubTable)
#define SET_CopyColorSubTable(disp, fn) ((disp)->CopyColorSubTable = fn)
#define CALL_ConvolutionFilter1D(disp, parameters) (*((disp)->ConvolutionFilter1D)) parameters
#define GET_ConvolutionFilter1D(disp) ((disp)->ConvolutionFilter1D)
#define SET_ConvolutionFilter1D(disp, fn) ((disp)->ConvolutionFilter1D = fn)
#define CALL_ConvolutionFilter2D(disp, parameters) (*((disp)->ConvolutionFilter2D)) parameters
#define GET_ConvolutionFilter2D(disp) ((disp)->ConvolutionFilter2D)
#define SET_ConvolutionFilter2D(disp, fn) ((disp)->ConvolutionFilter2D = fn)
#define CALL_ConvolutionParameterf(disp, parameters) (*((disp)->ConvolutionParameterf)) parameters
#define GET_ConvolutionParameterf(disp) ((disp)->ConvolutionParameterf)
#define SET_ConvolutionParameterf(disp, fn) ((disp)->ConvolutionParameterf = fn)
#define CALL_ConvolutionParameterfv(disp, parameters) (*((disp)->ConvolutionParameterfv)) parameters
#define GET_ConvolutionParameterfv(disp) ((disp)->ConvolutionParameterfv)
#define SET_ConvolutionParameterfv(disp, fn) ((disp)->ConvolutionParameterfv = fn)
#define CALL_ConvolutionParameteri(disp, parameters) (*((disp)->ConvolutionParameteri)) parameters
#define GET_ConvolutionParameteri(disp) ((disp)->ConvolutionParameteri)
#define SET_ConvolutionParameteri(disp, fn) ((disp)->ConvolutionParameteri = fn)
#define CALL_ConvolutionParameteriv(disp, parameters) (*((disp)->ConvolutionParameteriv)) parameters
#define GET_ConvolutionParameteriv(disp) ((disp)->ConvolutionParameteriv)
#define SET_ConvolutionParameteriv(disp, fn) ((disp)->ConvolutionParameteriv = fn)
#define CALL_CopyConvolutionFilter1D(disp, parameters) (*((disp)->CopyConvolutionFilter1D)) parameters
#define GET_CopyConvolutionFilter1D(disp) ((disp)->CopyConvolutionFilter1D)
#define SET_CopyConvolutionFilter1D(disp, fn) ((disp)->CopyConvolutionFilter1D = fn)
#define CALL_CopyConvolutionFilter2D(disp, parameters) (*((disp)->CopyConvolutionFilter2D)) parameters
#define GET_CopyConvolutionFilter2D(disp) ((disp)->CopyConvolutionFilter2D)
#define SET_CopyConvolutionFilter2D(disp, fn) ((disp)->CopyConvolutionFilter2D = fn)
#define CALL_GetConvolutionFilter(disp, parameters) (*((disp)->GetConvolutionFilter)) parameters
#define GET_GetConvolutionFilter(disp) ((disp)->GetConvolutionFilter)
#define SET_GetConvolutionFilter(disp, fn) ((disp)->GetConvolutionFilter = fn)
#define CALL_GetConvolutionParameterfv(disp, parameters) (*((disp)->GetConvolutionParameterfv)) parameters
#define GET_GetConvolutionParameterfv(disp) ((disp)->GetConvolutionParameterfv)
#define SET_GetConvolutionParameterfv(disp, fn) ((disp)->GetConvolutionParameterfv = fn)
#define CALL_GetConvolutionParameteriv(disp, parameters) (*((disp)->GetConvolutionParameteriv)) parameters
#define GET_GetConvolutionParameteriv(disp) ((disp)->GetConvolutionParameteriv)
#define SET_GetConvolutionParameteriv(disp, fn) ((disp)->GetConvolutionParameteriv = fn)
#define CALL_GetSeparableFilter(disp, parameters) (*((disp)->GetSeparableFilter)) parameters
#define GET_GetSeparableFilter(disp) ((disp)->GetSeparableFilter)
#define SET_GetSeparableFilter(disp, fn) ((disp)->GetSeparableFilter = fn)
#define CALL_SeparableFilter2D(disp, parameters) (*((disp)->SeparableFilter2D)) parameters
#define GET_SeparableFilter2D(disp) ((disp)->SeparableFilter2D)
#define SET_SeparableFilter2D(disp, fn) ((disp)->SeparableFilter2D = fn)
#define CALL_GetHistogram(disp, parameters) (*((disp)->GetHistogram)) parameters
#define GET_GetHistogram(disp) ((disp)->GetHistogram)
#define SET_GetHistogram(disp, fn) ((disp)->GetHistogram = fn)
#define CALL_GetHistogramParameterfv(disp, parameters) (*((disp)->GetHistogramParameterfv)) parameters
#define GET_GetHistogramParameterfv(disp) ((disp)->GetHistogramParameterfv)
#define SET_GetHistogramParameterfv(disp, fn) ((disp)->GetHistogramParameterfv = fn)
#define CALL_GetHistogramParameteriv(disp, parameters) (*((disp)->GetHistogramParameteriv)) parameters
#define GET_GetHistogramParameteriv(disp) ((disp)->GetHistogramParameteriv)
#define SET_GetHistogramParameteriv(disp, fn) ((disp)->GetHistogramParameteriv = fn)
#define CALL_GetMinmax(disp, parameters) (*((disp)->GetMinmax)) parameters
#define GET_GetMinmax(disp) ((disp)->GetMinmax)
#define SET_GetMinmax(disp, fn) ((disp)->GetMinmax = fn)
#define CALL_GetMinmaxParameterfv(disp, parameters) (*((disp)->GetMinmaxParameterfv)) parameters
#define GET_GetMinmaxParameterfv(disp) ((disp)->GetMinmaxParameterfv)
#define SET_GetMinmaxParameterfv(disp, fn) ((disp)->GetMinmaxParameterfv = fn)
#define CALL_GetMinmaxParameteriv(disp, parameters) (*((disp)->GetMinmaxParameteriv)) parameters
#define GET_GetMinmaxParameteriv(disp) ((disp)->GetMinmaxParameteriv)
#define SET_GetMinmaxParameteriv(disp, fn) ((disp)->GetMinmaxParameteriv = fn)
#define CALL_Histogram(disp, parameters) (*((disp)->Histogram)) parameters
#define GET_Histogram(disp) ((disp)->Histogram)
#define SET_Histogram(disp, fn) ((disp)->Histogram = fn)
#define CALL_Minmax(disp, parameters) (*((disp)->Minmax)) parameters
#define GET_Minmax(disp) ((disp)->Minmax)
#define SET_Minmax(disp, fn) ((disp)->Minmax = fn)
#define CALL_ResetHistogram(disp, parameters) (*((disp)->ResetHistogram)) parameters
#define GET_ResetHistogram(disp) ((disp)->ResetHistogram)
#define SET_ResetHistogram(disp, fn) ((disp)->ResetHistogram = fn)
#define CALL_ResetMinmax(disp, parameters) (*((disp)->ResetMinmax)) parameters
#define GET_ResetMinmax(disp) ((disp)->ResetMinmax)
#define SET_ResetMinmax(disp, fn) ((disp)->ResetMinmax = fn)
#define CALL_MultiTexCoord1dARB(disp, parameters) (*((disp)->MultiTexCoord1dARB)) parameters
#define GET_MultiTexCoord1dARB(disp) ((disp)->MultiTexCoord1dARB)
#define SET_MultiTexCoord1dARB(disp, fn) ((disp)->MultiTexCoord1dARB = fn)
#define CALL_MultiTexCoord1dvARB(disp, parameters) (*((disp)->MultiTexCoord1dvARB)) parameters
#define GET_MultiTexCoord1dvARB(disp) ((disp)->MultiTexCoord1dvARB)
#define SET_MultiTexCoord1dvARB(disp, fn) ((disp)->MultiTexCoord1dvARB = fn)
#define CALL_MultiTexCoord1fARB(disp, parameters) (*((disp)->MultiTexCoord1fARB)) parameters
#define GET_MultiTexCoord1fARB(disp) ((disp)->MultiTexCoord1fARB)
#define SET_MultiTexCoord1fARB(disp, fn) ((disp)->MultiTexCoord1fARB = fn)
#define CALL_MultiTexCoord1fvARB(disp, parameters) (*((disp)->MultiTexCoord1fvARB)) parameters
#define GET_MultiTexCoord1fvARB(disp) ((disp)->MultiTexCoord1fvARB)
#define SET_MultiTexCoord1fvARB(disp, fn) ((disp)->MultiTexCoord1fvARB = fn)
#define CALL_MultiTexCoord1iARB(disp, parameters) (*((disp)->MultiTexCoord1iARB)) parameters
#define GET_MultiTexCoord1iARB(disp) ((disp)->MultiTexCoord1iARB)
#define SET_MultiTexCoord1iARB(disp, fn) ((disp)->MultiTexCoord1iARB = fn)
#define CALL_MultiTexCoord1ivARB(disp, parameters) (*((disp)->MultiTexCoord1ivARB)) parameters
#define GET_MultiTexCoord1ivARB(disp) ((disp)->MultiTexCoord1ivARB)
#define SET_MultiTexCoord1ivARB(disp, fn) ((disp)->MultiTexCoord1ivARB = fn)
#define CALL_MultiTexCoord1sARB(disp, parameters) (*((disp)->MultiTexCoord1sARB)) parameters
#define GET_MultiTexCoord1sARB(disp) ((disp)->MultiTexCoord1sARB)
#define SET_MultiTexCoord1sARB(disp, fn) ((disp)->MultiTexCoord1sARB = fn)
#define CALL_MultiTexCoord1svARB(disp, parameters) (*((disp)->MultiTexCoord1svARB)) parameters
#define GET_MultiTexCoord1svARB(disp) ((disp)->MultiTexCoord1svARB)
#define SET_MultiTexCoord1svARB(disp, fn) ((disp)->MultiTexCoord1svARB = fn)
#define CALL_MultiTexCoord2dARB(disp, parameters) (*((disp)->MultiTexCoord2dARB)) parameters
#define GET_MultiTexCoord2dARB(disp) ((disp)->MultiTexCoord2dARB)
#define SET_MultiTexCoord2dARB(disp, fn) ((disp)->MultiTexCoord2dARB = fn)
#define CALL_MultiTexCoord2dvARB(disp, parameters) (*((disp)->MultiTexCoord2dvARB)) parameters
#define GET_MultiTexCoord2dvARB(disp) ((disp)->MultiTexCoord2dvARB)
#define SET_MultiTexCoord2dvARB(disp, fn) ((disp)->MultiTexCoord2dvARB = fn)
#define CALL_MultiTexCoord2fARB(disp, parameters) (*((disp)->MultiTexCoord2fARB)) parameters
#define GET_MultiTexCoord2fARB(disp) ((disp)->MultiTexCoord2fARB)
#define SET_MultiTexCoord2fARB(disp, fn) ((disp)->MultiTexCoord2fARB = fn)
#define CALL_MultiTexCoord2fvARB(disp, parameters) (*((disp)->MultiTexCoord2fvARB)) parameters
#define GET_MultiTexCoord2fvARB(disp) ((disp)->MultiTexCoord2fvARB)
#define SET_MultiTexCoord2fvARB(disp, fn) ((disp)->MultiTexCoord2fvARB = fn)
#define CALL_MultiTexCoord2iARB(disp, parameters) (*((disp)->MultiTexCoord2iARB)) parameters
#define GET_MultiTexCoord2iARB(disp) ((disp)->MultiTexCoord2iARB)
#define SET_MultiTexCoord2iARB(disp, fn) ((disp)->MultiTexCoord2iARB = fn)
#define CALL_MultiTexCoord2ivARB(disp, parameters) (*((disp)->MultiTexCoord2ivARB)) parameters
#define GET_MultiTexCoord2ivARB(disp) ((disp)->MultiTexCoord2ivARB)
#define SET_MultiTexCoord2ivARB(disp, fn) ((disp)->MultiTexCoord2ivARB = fn)
#define CALL_MultiTexCoord2sARB(disp, parameters) (*((disp)->MultiTexCoord2sARB)) parameters
#define GET_MultiTexCoord2sARB(disp) ((disp)->MultiTexCoord2sARB)
#define SET_MultiTexCoord2sARB(disp, fn) ((disp)->MultiTexCoord2sARB = fn)
#define CALL_MultiTexCoord2svARB(disp, parameters) (*((disp)->MultiTexCoord2svARB)) parameters
#define GET_MultiTexCoord2svARB(disp) ((disp)->MultiTexCoord2svARB)
#define SET_MultiTexCoord2svARB(disp, fn) ((disp)->MultiTexCoord2svARB = fn)
#define CALL_MultiTexCoord3dARB(disp, parameters) (*((disp)->MultiTexCoord3dARB)) parameters
#define GET_MultiTexCoord3dARB(disp) ((disp)->MultiTexCoord3dARB)
#define SET_MultiTexCoord3dARB(disp, fn) ((disp)->MultiTexCoord3dARB = fn)
#define CALL_MultiTexCoord3dvARB(disp, parameters) (*((disp)->MultiTexCoord3dvARB)) parameters
#define GET_MultiTexCoord3dvARB(disp) ((disp)->MultiTexCoord3dvARB)
#define SET_MultiTexCoord3dvARB(disp, fn) ((disp)->MultiTexCoord3dvARB = fn)
#define CALL_MultiTexCoord3fARB(disp, parameters) (*((disp)->MultiTexCoord3fARB)) parameters
#define GET_MultiTexCoord3fARB(disp) ((disp)->MultiTexCoord3fARB)
#define SET_MultiTexCoord3fARB(disp, fn) ((disp)->MultiTexCoord3fARB = fn)
#define CALL_MultiTexCoord3fvARB(disp, parameters) (*((disp)->MultiTexCoord3fvARB)) parameters
#define GET_MultiTexCoord3fvARB(disp) ((disp)->MultiTexCoord3fvARB)
#define SET_MultiTexCoord3fvARB(disp, fn) ((disp)->MultiTexCoord3fvARB = fn)
#define CALL_MultiTexCoord3iARB(disp, parameters) (*((disp)->MultiTexCoord3iARB)) parameters
#define GET_MultiTexCoord3iARB(disp) ((disp)->MultiTexCoord3iARB)
#define SET_MultiTexCoord3iARB(disp, fn) ((disp)->MultiTexCoord3iARB = fn)
#define CALL_MultiTexCoord3ivARB(disp, parameters) (*((disp)->MultiTexCoord3ivARB)) parameters
#define GET_MultiTexCoord3ivARB(disp) ((disp)->MultiTexCoord3ivARB)
#define SET_MultiTexCoord3ivARB(disp, fn) ((disp)->MultiTexCoord3ivARB = fn)
#define CALL_MultiTexCoord3sARB(disp, parameters) (*((disp)->MultiTexCoord3sARB)) parameters
#define GET_MultiTexCoord3sARB(disp) ((disp)->MultiTexCoord3sARB)
#define SET_MultiTexCoord3sARB(disp, fn) ((disp)->MultiTexCoord3sARB = fn)
#define CALL_MultiTexCoord3svARB(disp, parameters) (*((disp)->MultiTexCoord3svARB)) parameters
#define GET_MultiTexCoord3svARB(disp) ((disp)->MultiTexCoord3svARB)
#define SET_MultiTexCoord3svARB(disp, fn) ((disp)->MultiTexCoord3svARB = fn)
#define CALL_MultiTexCoord4dARB(disp, parameters) (*((disp)->MultiTexCoord4dARB)) parameters
#define GET_MultiTexCoord4dARB(disp) ((disp)->MultiTexCoord4dARB)
#define SET_MultiTexCoord4dARB(disp, fn) ((disp)->MultiTexCoord4dARB = fn)
#define CALL_MultiTexCoord4dvARB(disp, parameters) (*((disp)->MultiTexCoord4dvARB)) parameters
#define GET_MultiTexCoord4dvARB(disp) ((disp)->MultiTexCoord4dvARB)
#define SET_MultiTexCoord4dvARB(disp, fn) ((disp)->MultiTexCoord4dvARB = fn)
#define CALL_MultiTexCoord4fvARB(disp, parameters) (*((disp)->MultiTexCoord4fvARB)) parameters
#define GET_MultiTexCoord4fvARB(disp) ((disp)->MultiTexCoord4fvARB)
#define SET_MultiTexCoord4fvARB(disp, fn) ((disp)->MultiTexCoord4fvARB = fn)
#define CALL_MultiTexCoord4iARB(disp, parameters) (*((disp)->MultiTexCoord4iARB)) parameters
#define GET_MultiTexCoord4iARB(disp) ((disp)->MultiTexCoord4iARB)
#define SET_MultiTexCoord4iARB(disp, fn) ((disp)->MultiTexCoord4iARB = fn)
#define CALL_MultiTexCoord4ivARB(disp, parameters) (*((disp)->MultiTexCoord4ivARB)) parameters
#define GET_MultiTexCoord4ivARB(disp) ((disp)->MultiTexCoord4ivARB)
#define SET_MultiTexCoord4ivARB(disp, fn) ((disp)->MultiTexCoord4ivARB = fn)
#define CALL_MultiTexCoord4sARB(disp, parameters) (*((disp)->MultiTexCoord4sARB)) parameters
#define GET_MultiTexCoord4sARB(disp) ((disp)->MultiTexCoord4sARB)
#define SET_MultiTexCoord4sARB(disp, fn) ((disp)->MultiTexCoord4sARB = fn)
#define CALL_MultiTexCoord4svARB(disp, parameters) (*((disp)->MultiTexCoord4svARB)) parameters
#define GET_MultiTexCoord4svARB(disp) ((disp)->MultiTexCoord4svARB)
#define SET_MultiTexCoord4svARB(disp, fn) ((disp)->MultiTexCoord4svARB = fn)

#if !defined(IN_DRI_DRIVER)

#define CALL_Color4f(disp, parameters) (*((disp)->Color4f)) parameters
#define GET_Color4f(disp) ((disp)->Color4f)
#define SET_Color4f(disp, fn) ((disp)->Color4f = fn)
#define CALL_Color4ub(disp, parameters) (*((disp)->Color4ub)) parameters
#define GET_Color4ub(disp) ((disp)->Color4ub)
#define SET_Color4ub(disp, fn) ((disp)->Color4ub = fn)
#define CALL_Normal3f(disp, parameters) (*((disp)->Normal3f)) parameters
#define GET_Normal3f(disp) ((disp)->Normal3f)
#define SET_Normal3f(disp, fn) ((disp)->Normal3f = fn)
#define CALL_CullFace(disp, parameters) (*((disp)->CullFace)) parameters
#define GET_CullFace(disp) ((disp)->CullFace)
#define SET_CullFace(disp, fn) ((disp)->CullFace = fn)
#define CALL_Fogf(disp, parameters) (*((disp)->Fogf)) parameters
#define GET_Fogf(disp) ((disp)->Fogf)
#define SET_Fogf(disp, fn) ((disp)->Fogf = fn)
#define CALL_Fogfv(disp, parameters) (*((disp)->Fogfv)) parameters
#define GET_Fogfv(disp) ((disp)->Fogfv)
#define SET_Fogfv(disp, fn) ((disp)->Fogfv = fn)
#define CALL_FrontFace(disp, parameters) (*((disp)->FrontFace)) parameters
#define GET_FrontFace(disp) ((disp)->FrontFace)
#define SET_FrontFace(disp, fn) ((disp)->FrontFace = fn)
#define CALL_Hint(disp, parameters) (*((disp)->Hint)) parameters
#define GET_Hint(disp) ((disp)->Hint)
#define SET_Hint(disp, fn) ((disp)->Hint = fn)
#define CALL_Lightf(disp, parameters) (*((disp)->Lightf)) parameters
#define GET_Lightf(disp) ((disp)->Lightf)
#define SET_Lightf(disp, fn) ((disp)->Lightf = fn)
#define CALL_Lightfv(disp, parameters) (*((disp)->Lightfv)) parameters
#define GET_Lightfv(disp) ((disp)->Lightfv)
#define SET_Lightfv(disp, fn) ((disp)->Lightfv = fn)
#define CALL_LightModelf(disp, parameters) (*((disp)->LightModelf)) parameters
#define GET_LightModelf(disp) ((disp)->LightModelf)
#define SET_LightModelf(disp, fn) ((disp)->LightModelf = fn)
#define CALL_LightModelfv(disp, parameters) (*((disp)->LightModelfv)) parameters
#define GET_LightModelfv(disp) ((disp)->LightModelfv)
#define SET_LightModelfv(disp, fn) ((disp)->LightModelfv = fn)
#define CALL_LineWidth(disp, parameters) (*((disp)->LineWidth)) parameters
#define GET_LineWidth(disp) ((disp)->LineWidth)
#define SET_LineWidth(disp, fn) ((disp)->LineWidth = fn)
#define CALL_Materialf(disp, parameters) (*((disp)->Materialf)) parameters
#define GET_Materialf(disp) ((disp)->Materialf)
#define SET_Materialf(disp, fn) ((disp)->Materialf = fn)
#define CALL_Materialfv(disp, parameters) (*((disp)->Materialfv)) parameters
#define GET_Materialfv(disp) ((disp)->Materialfv)
#define SET_Materialfv(disp, fn) ((disp)->Materialfv = fn)
#define CALL_PointSize(disp, parameters) (*((disp)->PointSize)) parameters
#define GET_PointSize(disp) ((disp)->PointSize)
#define SET_PointSize(disp, fn) ((disp)->PointSize = fn)
#define CALL_Scissor(disp, parameters) (*((disp)->Scissor)) parameters
#define GET_Scissor(disp) ((disp)->Scissor)
#define SET_Scissor(disp, fn) ((disp)->Scissor = fn)
#define CALL_ShadeModel(disp, parameters) (*((disp)->ShadeModel)) parameters
#define GET_ShadeModel(disp) ((disp)->ShadeModel)
#define SET_ShadeModel(disp, fn) ((disp)->ShadeModel = fn)
#define CALL_TexParameterf(disp, parameters) (*((disp)->TexParameterf)) parameters
#define GET_TexParameterf(disp) ((disp)->TexParameterf)
#define SET_TexParameterf(disp, fn) ((disp)->TexParameterf = fn)
#define CALL_TexParameterfv(disp, parameters) (*((disp)->TexParameterfv)) parameters
#define GET_TexParameterfv(disp) ((disp)->TexParameterfv)
#define SET_TexParameterfv(disp, fn) ((disp)->TexParameterfv = fn)
#define CALL_TexParameteri(disp, parameters) (*((disp)->TexParameteri)) parameters
#define GET_TexParameteri(disp) ((disp)->TexParameteri)
#define SET_TexParameteri(disp, fn) ((disp)->TexParameteri = fn)
#define CALL_TexParameteriv(disp, parameters) (*((disp)->TexParameteriv)) parameters
#define GET_TexParameteriv(disp) ((disp)->TexParameteriv)
#define SET_TexParameteriv(disp, fn) ((disp)->TexParameteriv = fn)
#define CALL_TexImage2D(disp, parameters) (*((disp)->TexImage2D)) parameters
#define GET_TexImage2D(disp) ((disp)->TexImage2D)
#define SET_TexImage2D(disp, fn) ((disp)->TexImage2D = fn)
#define CALL_TexEnvf(disp, parameters) (*((disp)->TexEnvf)) parameters
#define GET_TexEnvf(disp) ((disp)->TexEnvf)
#define SET_TexEnvf(disp, fn) ((disp)->TexEnvf = fn)
#define CALL_TexEnvfv(disp, parameters) (*((disp)->TexEnvfv)) parameters
#define GET_TexEnvfv(disp) ((disp)->TexEnvfv)
#define SET_TexEnvfv(disp, fn) ((disp)->TexEnvfv = fn)
#define CALL_TexEnvi(disp, parameters) (*((disp)->TexEnvi)) parameters
#define GET_TexEnvi(disp) ((disp)->TexEnvi)
#define SET_TexEnvi(disp, fn) ((disp)->TexEnvi = fn)
#define CALL_TexEnviv(disp, parameters) (*((disp)->TexEnviv)) parameters
#define GET_TexEnviv(disp) ((disp)->TexEnviv)
#define SET_TexEnviv(disp, fn) ((disp)->TexEnviv = fn)
#define CALL_TexGenfOES(disp, parameters) (*((disp)->TexGenfOES)) parameters
#define GET_TexGenfOES(disp) ((disp)->TexGenfOES)
#define SET_TexGenfOES(disp, fn) ((disp)->TexGenfOES = fn)
#define CALL_TexGenfvOES(disp, parameters) (*((disp)->TexGenfvOES)) parameters
#define GET_TexGenfvOES(disp) ((disp)->TexGenfvOES)
#define SET_TexGenfvOES(disp, fn) ((disp)->TexGenfvOES = fn)
#define CALL_TexGeniOES(disp, parameters) (*((disp)->TexGeniOES)) parameters
#define GET_TexGeniOES(disp) ((disp)->TexGeniOES)
#define SET_TexGeniOES(disp, fn) ((disp)->TexGeniOES = fn)
#define CALL_TexGenivOES(disp, parameters) (*((disp)->TexGenivOES)) parameters
#define GET_TexGenivOES(disp) ((disp)->TexGenivOES)
#define SET_TexGenivOES(disp, fn) ((disp)->TexGenivOES = fn)
#define CALL_Clear(disp, parameters) (*((disp)->Clear)) parameters
#define GET_Clear(disp) ((disp)->Clear)
#define SET_Clear(disp, fn) ((disp)->Clear = fn)
#define CALL_ClearColor(disp, parameters) (*((disp)->ClearColor)) parameters
#define GET_ClearColor(disp) ((disp)->ClearColor)
#define SET_ClearColor(disp, fn) ((disp)->ClearColor = fn)
#define CALL_ClearStencil(disp, parameters) (*((disp)->ClearStencil)) parameters
#define GET_ClearStencil(disp) ((disp)->ClearStencil)
#define SET_ClearStencil(disp, fn) ((disp)->ClearStencil = fn)
#define CALL_StencilMask(disp, parameters) (*((disp)->StencilMask)) parameters
#define GET_StencilMask(disp) ((disp)->StencilMask)
#define SET_StencilMask(disp, fn) ((disp)->StencilMask = fn)
#define CALL_ColorMask(disp, parameters) (*((disp)->ColorMask)) parameters
#define GET_ColorMask(disp) ((disp)->ColorMask)
#define SET_ColorMask(disp, fn) ((disp)->ColorMask = fn)
#define CALL_DepthMask(disp, parameters) (*((disp)->DepthMask)) parameters
#define GET_DepthMask(disp) ((disp)->DepthMask)
#define SET_DepthMask(disp, fn) ((disp)->DepthMask = fn)
#define CALL_Disable(disp, parameters) (*((disp)->Disable)) parameters
#define GET_Disable(disp) ((disp)->Disable)
#define SET_Disable(disp, fn) ((disp)->Disable = fn)
#define CALL_Enable(disp, parameters) (*((disp)->Enable)) parameters
#define GET_Enable(disp) ((disp)->Enable)
#define SET_Enable(disp, fn) ((disp)->Enable = fn)
#define CALL_Finish(disp, parameters) (*((disp)->Finish)) parameters
#define GET_Finish(disp) ((disp)->Finish)
#define SET_Finish(disp, fn) ((disp)->Finish = fn)
#define CALL_Flush(disp, parameters) (*((disp)->Flush)) parameters
#define GET_Flush(disp) ((disp)->Flush)
#define SET_Flush(disp, fn) ((disp)->Flush = fn)
#define CALL_AlphaFunc(disp, parameters) (*((disp)->AlphaFunc)) parameters
#define GET_AlphaFunc(disp) ((disp)->AlphaFunc)
#define SET_AlphaFunc(disp, fn) ((disp)->AlphaFunc = fn)
#define CALL_BlendFunc(disp, parameters) (*((disp)->BlendFunc)) parameters
#define GET_BlendFunc(disp) ((disp)->BlendFunc)
#define SET_BlendFunc(disp, fn) ((disp)->BlendFunc = fn)
#define CALL_LogicOp(disp, parameters) (*((disp)->LogicOp)) parameters
#define GET_LogicOp(disp) ((disp)->LogicOp)
#define SET_LogicOp(disp, fn) ((disp)->LogicOp = fn)
#define CALL_StencilFunc(disp, parameters) (*((disp)->StencilFunc)) parameters
#define GET_StencilFunc(disp) ((disp)->StencilFunc)
#define SET_StencilFunc(disp, fn) ((disp)->StencilFunc = fn)
#define CALL_StencilOp(disp, parameters) (*((disp)->StencilOp)) parameters
#define GET_StencilOp(disp) ((disp)->StencilOp)
#define SET_StencilOp(disp, fn) ((disp)->StencilOp = fn)
#define CALL_DepthFunc(disp, parameters) (*((disp)->DepthFunc)) parameters
#define GET_DepthFunc(disp) ((disp)->DepthFunc)
#define SET_DepthFunc(disp, fn) ((disp)->DepthFunc = fn)
#define CALL_PixelStorei(disp, parameters) (*((disp)->PixelStorei)) parameters
#define GET_PixelStorei(disp) ((disp)->PixelStorei)
#define SET_PixelStorei(disp, fn) ((disp)->PixelStorei = fn)
#define CALL_ReadPixels(disp, parameters) (*((disp)->ReadPixels)) parameters
#define GET_ReadPixels(disp) ((disp)->ReadPixels)
#define SET_ReadPixels(disp, fn) ((disp)->ReadPixels = fn)
#define CALL_GetBooleanv(disp, parameters) (*((disp)->GetBooleanv)) parameters
#define GET_GetBooleanv(disp) ((disp)->GetBooleanv)
#define SET_GetBooleanv(disp, fn) ((disp)->GetBooleanv = fn)
#define CALL_GetError(disp, parameters) (*((disp)->GetError)) parameters
#define GET_GetError(disp) ((disp)->GetError)
#define SET_GetError(disp, fn) ((disp)->GetError = fn)
#define CALL_GetFloatv(disp, parameters) (*((disp)->GetFloatv)) parameters
#define GET_GetFloatv(disp) ((disp)->GetFloatv)
#define SET_GetFloatv(disp, fn) ((disp)->GetFloatv = fn)
#define CALL_GetIntegerv(disp, parameters) (*((disp)->GetIntegerv)) parameters
#define GET_GetIntegerv(disp) ((disp)->GetIntegerv)
#define SET_GetIntegerv(disp, fn) ((disp)->GetIntegerv = fn)
#define CALL_GetLightfv(disp, parameters) (*((disp)->GetLightfv)) parameters
#define GET_GetLightfv(disp) ((disp)->GetLightfv)
#define SET_GetLightfv(disp, fn) ((disp)->GetLightfv = fn)
#define CALL_GetMaterialfv(disp, parameters) (*((disp)->GetMaterialfv)) parameters
#define GET_GetMaterialfv(disp) ((disp)->GetMaterialfv)
#define SET_GetMaterialfv(disp, fn) ((disp)->GetMaterialfv = fn)
#define CALL_GetString(disp, parameters) (*((disp)->GetString)) parameters
#define GET_GetString(disp) ((disp)->GetString)
#define SET_GetString(disp, fn) ((disp)->GetString = fn)
#define CALL_GetTexEnvfv(disp, parameters) (*((disp)->GetTexEnvfv)) parameters
#define GET_GetTexEnvfv(disp) ((disp)->GetTexEnvfv)
#define SET_GetTexEnvfv(disp, fn) ((disp)->GetTexEnvfv = fn)
#define CALL_GetTexEnviv(disp, parameters) (*((disp)->GetTexEnviv)) parameters
#define GET_GetTexEnviv(disp) ((disp)->GetTexEnviv)
#define SET_GetTexEnviv(disp, fn) ((disp)->GetTexEnviv = fn)
#define CALL_GetTexGenfvOES(disp, parameters) (*((disp)->GetTexGenfvOES)) parameters
#define GET_GetTexGenfvOES(disp) ((disp)->GetTexGenfvOES)
#define SET_GetTexGenfvOES(disp, fn) ((disp)->GetTexGenfvOES = fn)
#define CALL_GetTexGenivOES(disp, parameters) (*((disp)->GetTexGenivOES)) parameters
#define GET_GetTexGenivOES(disp) ((disp)->GetTexGenivOES)
#define SET_GetTexGenivOES(disp, fn) ((disp)->GetTexGenivOES = fn)
#define CALL_GetTexParameterfv(disp, parameters) (*((disp)->GetTexParameterfv)) parameters
#define GET_GetTexParameterfv(disp) ((disp)->GetTexParameterfv)
#define SET_GetTexParameterfv(disp, fn) ((disp)->GetTexParameterfv = fn)
#define CALL_GetTexParameteriv(disp, parameters) (*((disp)->GetTexParameteriv)) parameters
#define GET_GetTexParameteriv(disp) ((disp)->GetTexParameteriv)
#define SET_GetTexParameteriv(disp, fn) ((disp)->GetTexParameteriv = fn)
#define CALL_IsEnabled(disp, parameters) (*((disp)->IsEnabled)) parameters
#define GET_IsEnabled(disp) ((disp)->IsEnabled)
#define SET_IsEnabled(disp, fn) ((disp)->IsEnabled = fn)
#define CALL_LoadIdentity(disp, parameters) (*((disp)->LoadIdentity)) parameters
#define GET_LoadIdentity(disp) ((disp)->LoadIdentity)
#define SET_LoadIdentity(disp, fn) ((disp)->LoadIdentity = fn)
#define CALL_LoadMatrixf(disp, parameters) (*((disp)->LoadMatrixf)) parameters
#define GET_LoadMatrixf(disp) ((disp)->LoadMatrixf)
#define SET_LoadMatrixf(disp, fn) ((disp)->LoadMatrixf = fn)
#define CALL_MatrixMode(disp, parameters) (*((disp)->MatrixMode)) parameters
#define GET_MatrixMode(disp) ((disp)->MatrixMode)
#define SET_MatrixMode(disp, fn) ((disp)->MatrixMode = fn)
#define CALL_MultMatrixf(disp, parameters) (*((disp)->MultMatrixf)) parameters
#define GET_MultMatrixf(disp) ((disp)->MultMatrixf)
#define SET_MultMatrixf(disp, fn) ((disp)->MultMatrixf = fn)
#define CALL_PopMatrix(disp, parameters) (*((disp)->PopMatrix)) parameters
#define GET_PopMatrix(disp) ((disp)->PopMatrix)
#define SET_PopMatrix(disp, fn) ((disp)->PopMatrix = fn)
#define CALL_PushMatrix(disp, parameters) (*((disp)->PushMatrix)) parameters
#define GET_PushMatrix(disp) ((disp)->PushMatrix)
#define SET_PushMatrix(disp, fn) ((disp)->PushMatrix = fn)
#define CALL_Rotatef(disp, parameters) (*((disp)->Rotatef)) parameters
#define GET_Rotatef(disp) ((disp)->Rotatef)
#define SET_Rotatef(disp, fn) ((disp)->Rotatef = fn)
#define CALL_Scalef(disp, parameters) (*((disp)->Scalef)) parameters
#define GET_Scalef(disp) ((disp)->Scalef)
#define SET_Scalef(disp, fn) ((disp)->Scalef = fn)
#define CALL_Translatef(disp, parameters) (*((disp)->Translatef)) parameters
#define GET_Translatef(disp) ((disp)->Translatef)
#define SET_Translatef(disp, fn) ((disp)->Translatef = fn)
#define CALL_Viewport(disp, parameters) (*((disp)->Viewport)) parameters
#define GET_Viewport(disp) ((disp)->Viewport)
#define SET_Viewport(disp, fn) ((disp)->Viewport = fn)
#define CALL_BindTexture(disp, parameters) (*((disp)->BindTexture)) parameters
#define GET_BindTexture(disp) ((disp)->BindTexture)
#define SET_BindTexture(disp, fn) ((disp)->BindTexture = fn)
#define CALL_ColorPointer(disp, parameters) (*((disp)->ColorPointer)) parameters
#define GET_ColorPointer(disp) ((disp)->ColorPointer)
#define SET_ColorPointer(disp, fn) ((disp)->ColorPointer = fn)
#define CALL_DisableClientState(disp, parameters) (*((disp)->DisableClientState)) parameters
#define GET_DisableClientState(disp) ((disp)->DisableClientState)
#define SET_DisableClientState(disp, fn) ((disp)->DisableClientState = fn)
#define CALL_DrawArrays(disp, parameters) (*((disp)->DrawArrays)) parameters
#define GET_DrawArrays(disp) ((disp)->DrawArrays)
#define SET_DrawArrays(disp, fn) ((disp)->DrawArrays = fn)
#define CALL_DrawElements(disp, parameters) (*((disp)->DrawElements)) parameters
#define GET_DrawElements(disp) ((disp)->DrawElements)
#define SET_DrawElements(disp, fn) ((disp)->DrawElements = fn)
#define CALL_EnableClientState(disp, parameters) (*((disp)->EnableClientState)) parameters
#define GET_EnableClientState(disp) ((disp)->EnableClientState)
#define SET_EnableClientState(disp, fn) ((disp)->EnableClientState = fn)
#define CALL_NormalPointer(disp, parameters) (*((disp)->NormalPointer)) parameters
#define GET_NormalPointer(disp) ((disp)->NormalPointer)
#define SET_NormalPointer(disp, fn) ((disp)->NormalPointer = fn)
#define CALL_PolygonOffset(disp, parameters) (*((disp)->PolygonOffset)) parameters
#define GET_PolygonOffset(disp) ((disp)->PolygonOffset)
#define SET_PolygonOffset(disp, fn) ((disp)->PolygonOffset = fn)
#define CALL_TexCoordPointer(disp, parameters) (*((disp)->TexCoordPointer)) parameters
#define GET_TexCoordPointer(disp) ((disp)->TexCoordPointer)
#define SET_TexCoordPointer(disp, fn) ((disp)->TexCoordPointer = fn)
#define CALL_VertexPointer(disp, parameters) (*((disp)->VertexPointer)) parameters
#define GET_VertexPointer(disp) ((disp)->VertexPointer)
#define SET_VertexPointer(disp, fn) ((disp)->VertexPointer = fn)
#define CALL_CopyTexImage2D(disp, parameters) (*((disp)->CopyTexImage2D)) parameters
#define GET_CopyTexImage2D(disp) ((disp)->CopyTexImage2D)
#define SET_CopyTexImage2D(disp, fn) ((disp)->CopyTexImage2D = fn)
#define CALL_CopyTexSubImage2D(disp, parameters) (*((disp)->CopyTexSubImage2D)) parameters
#define GET_CopyTexSubImage2D(disp) ((disp)->CopyTexSubImage2D)
#define SET_CopyTexSubImage2D(disp, fn) ((disp)->CopyTexSubImage2D = fn)
#define CALL_DeleteTextures(disp, parameters) (*((disp)->DeleteTextures)) parameters
#define GET_DeleteTextures(disp) ((disp)->DeleteTextures)
#define SET_DeleteTextures(disp, fn) ((disp)->DeleteTextures = fn)
#define CALL_GenTextures(disp, parameters) (*((disp)->GenTextures)) parameters
#define GET_GenTextures(disp) ((disp)->GenTextures)
#define SET_GenTextures(disp, fn) ((disp)->GenTextures = fn)
#define CALL_GetPointerv(disp, parameters) (*((disp)->GetPointerv)) parameters
#define GET_GetPointerv(disp) ((disp)->GetPointerv)
#define SET_GetPointerv(disp, fn) ((disp)->GetPointerv = fn)
#define CALL_IsTexture(disp, parameters) (*((disp)->IsTexture)) parameters
#define GET_IsTexture(disp) ((disp)->IsTexture)
#define SET_IsTexture(disp, fn) ((disp)->IsTexture = fn)
#define CALL_TexSubImage2D(disp, parameters) (*((disp)->TexSubImage2D)) parameters
#define GET_TexSubImage2D(disp) ((disp)->TexSubImage2D)
#define SET_TexSubImage2D(disp, fn) ((disp)->TexSubImage2D = fn)
#define CALL_BlendColor(disp, parameters) (*((disp)->BlendColor)) parameters
#define GET_BlendColor(disp) ((disp)->BlendColor)
#define SET_BlendColor(disp, fn) ((disp)->BlendColor = fn)
#define CALL_BlendEquationOES(disp, parameters) (*((disp)->BlendEquationOES)) parameters
#define GET_BlendEquationOES(disp) ((disp)->BlendEquationOES)
#define SET_BlendEquationOES(disp, fn) ((disp)->BlendEquationOES = fn)
#define CALL_TexImage3D(disp, parameters) (*((disp)->TexImage3D)) parameters
#define GET_TexImage3D(disp) ((disp)->TexImage3D)
#define SET_TexImage3D(disp, fn) ((disp)->TexImage3D = fn)
#define CALL_TexSubImage3D(disp, parameters) (*((disp)->TexSubImage3D)) parameters
#define GET_TexSubImage3D(disp) ((disp)->TexSubImage3D)
#define SET_TexSubImage3D(disp, fn) ((disp)->TexSubImage3D = fn)
#define CALL_CopyTexSubImage3D(disp, parameters) (*((disp)->CopyTexSubImage3D)) parameters
#define GET_CopyTexSubImage3D(disp) ((disp)->CopyTexSubImage3D)
#define SET_CopyTexSubImage3D(disp, fn) ((disp)->CopyTexSubImage3D = fn)
#define CALL_ActiveTexture(disp, parameters) (*((disp)->ActiveTexture)) parameters
#define GET_ActiveTexture(disp) ((disp)->ActiveTexture)
#define SET_ActiveTexture(disp, fn) ((disp)->ActiveTexture = fn)
#define CALL_ClientActiveTexture(disp, parameters) (*((disp)->ClientActiveTexture)) parameters
#define GET_ClientActiveTexture(disp) ((disp)->ClientActiveTexture)
#define SET_ClientActiveTexture(disp, fn) ((disp)->ClientActiveTexture = fn)
#define CALL_MultiTexCoord4f(disp, parameters) (*((disp)->MultiTexCoord4f)) parameters
#define GET_MultiTexCoord4f(disp) ((disp)->MultiTexCoord4f)
#define SET_MultiTexCoord4f(disp, fn) ((disp)->MultiTexCoord4f = fn)
#define CALL_BlendEquationSeparateOES(disp, parameters) (*((disp)->BlendEquationSeparateOES)) parameters
#define GET_BlendEquationSeparateOES(disp) ((disp)->BlendEquationSeparateOES)
#define SET_BlendEquationSeparateOES(disp, fn) ((disp)->BlendEquationSeparateOES = fn)
#define CALL_BlendFuncSeparateOES(disp, parameters) (*((disp)->BlendFuncSeparateOES)) parameters
#define GET_BlendFuncSeparateOES(disp) ((disp)->BlendFuncSeparateOES)
#define SET_BlendFuncSeparateOES(disp, fn) ((disp)->BlendFuncSeparateOES = fn)
#define CALL_DrawTexfOES(disp, parameters) (*((disp)->DrawTexfOES)) parameters
#define GET_DrawTexfOES(disp) ((disp)->DrawTexfOES)
#define SET_DrawTexfOES(disp, fn) ((disp)->DrawTexfOES = fn)
#define CALL_DrawTexfvOES(disp, parameters) (*((disp)->DrawTexfvOES)) parameters
#define GET_DrawTexfvOES(disp) ((disp)->DrawTexfvOES)
#define SET_DrawTexfvOES(disp, fn) ((disp)->DrawTexfvOES = fn)
#define CALL_DrawTexiOES(disp, parameters) (*((disp)->DrawTexiOES)) parameters
#define GET_DrawTexiOES(disp) ((disp)->DrawTexiOES)
#define SET_DrawTexiOES(disp, fn) ((disp)->DrawTexiOES = fn)
#define CALL_DrawTexivOES(disp, parameters) (*((disp)->DrawTexivOES)) parameters
#define GET_DrawTexivOES(disp) ((disp)->DrawTexivOES)
#define SET_DrawTexivOES(disp, fn) ((disp)->DrawTexivOES = fn)
#define CALL_DrawTexsOES(disp, parameters) (*((disp)->DrawTexsOES)) parameters
#define GET_DrawTexsOES(disp) ((disp)->DrawTexsOES)
#define SET_DrawTexsOES(disp, fn) ((disp)->DrawTexsOES = fn)
#define CALL_DrawTexsvOES(disp, parameters) (*((disp)->DrawTexsvOES)) parameters
#define GET_DrawTexsvOES(disp) ((disp)->DrawTexsvOES)
#define SET_DrawTexsvOES(disp, fn) ((disp)->DrawTexsvOES = fn)
#define CALL_DrawTexxOES(disp, parameters) (*((disp)->DrawTexxOES)) parameters
#define GET_DrawTexxOES(disp) ((disp)->DrawTexxOES)
#define SET_DrawTexxOES(disp, fn) ((disp)->DrawTexxOES = fn)
#define CALL_DrawTexxvOES(disp, parameters) (*((disp)->DrawTexxvOES)) parameters
#define GET_DrawTexxvOES(disp) ((disp)->DrawTexxvOES)
#define SET_DrawTexxvOES(disp, fn) ((disp)->DrawTexxvOES = fn)
#define CALL_BindFramebufferOES(disp, parameters) (*((disp)->BindFramebufferOES)) parameters
#define GET_BindFramebufferOES(disp) ((disp)->BindFramebufferOES)
#define SET_BindFramebufferOES(disp, fn) ((disp)->BindFramebufferOES = fn)
#define CALL_BindRenderbufferOES(disp, parameters) (*((disp)->BindRenderbufferOES)) parameters
#define GET_BindRenderbufferOES(disp) ((disp)->BindRenderbufferOES)
#define SET_BindRenderbufferOES(disp, fn) ((disp)->BindRenderbufferOES = fn)
#define CALL_CheckFramebufferStatusOES(disp, parameters) (*((disp)->CheckFramebufferStatusOES)) parameters
#define GET_CheckFramebufferStatusOES(disp) ((disp)->CheckFramebufferStatusOES)
#define SET_CheckFramebufferStatusOES(disp, fn) ((disp)->CheckFramebufferStatusOES = fn)
#define CALL_DeleteFramebuffersOES(disp, parameters) (*((disp)->DeleteFramebuffersOES)) parameters
#define GET_DeleteFramebuffersOES(disp) ((disp)->DeleteFramebuffersOES)
#define SET_DeleteFramebuffersOES(disp, fn) ((disp)->DeleteFramebuffersOES = fn)
#define CALL_DeleteRenderbuffersOES(disp, parameters) (*((disp)->DeleteRenderbuffersOES)) parameters
#define GET_DeleteRenderbuffersOES(disp) ((disp)->DeleteRenderbuffersOES)
#define SET_DeleteRenderbuffersOES(disp, fn) ((disp)->DeleteRenderbuffersOES = fn)
#define CALL_FramebufferRenderbufferOES(disp, parameters) (*((disp)->FramebufferRenderbufferOES)) parameters
#define GET_FramebufferRenderbufferOES(disp) ((disp)->FramebufferRenderbufferOES)
#define SET_FramebufferRenderbufferOES(disp, fn) ((disp)->FramebufferRenderbufferOES = fn)
#define CALL_FramebufferTexture2DOES(disp, parameters) (*((disp)->FramebufferTexture2DOES)) parameters
#define GET_FramebufferTexture2DOES(disp) ((disp)->FramebufferTexture2DOES)
#define SET_FramebufferTexture2DOES(disp, fn) ((disp)->FramebufferTexture2DOES = fn)
#define CALL_GenFramebuffersOES(disp, parameters) (*((disp)->GenFramebuffersOES)) parameters
#define GET_GenFramebuffersOES(disp) ((disp)->GenFramebuffersOES)
#define SET_GenFramebuffersOES(disp, fn) ((disp)->GenFramebuffersOES = fn)
#define CALL_GenRenderbuffersOES(disp, parameters) (*((disp)->GenRenderbuffersOES)) parameters
#define GET_GenRenderbuffersOES(disp) ((disp)->GenRenderbuffersOES)
#define SET_GenRenderbuffersOES(disp, fn) ((disp)->GenRenderbuffersOES = fn)
#define CALL_GenerateMipmapOES(disp, parameters) (*((disp)->GenerateMipmapOES)) parameters
#define GET_GenerateMipmapOES(disp) ((disp)->GenerateMipmapOES)
#define SET_GenerateMipmapOES(disp, fn) ((disp)->GenerateMipmapOES = fn)
#define CALL_GetFramebufferAttachmentParameterivOES(disp, parameters) (*((disp)->GetFramebufferAttachmentParameterivOES)) parameters
#define GET_GetFramebufferAttachmentParameterivOES(disp) ((disp)->GetFramebufferAttachmentParameterivOES)
#define SET_GetFramebufferAttachmentParameterivOES(disp, fn) ((disp)->GetFramebufferAttachmentParameterivOES = fn)
#define CALL_GetRenderbufferParameterivOES(disp, parameters) (*((disp)->GetRenderbufferParameterivOES)) parameters
#define GET_GetRenderbufferParameterivOES(disp) ((disp)->GetRenderbufferParameterivOES)
#define SET_GetRenderbufferParameterivOES(disp, fn) ((disp)->GetRenderbufferParameterivOES = fn)
#define CALL_IsFramebufferOES(disp, parameters) (*((disp)->IsFramebufferOES)) parameters
#define GET_IsFramebufferOES(disp) ((disp)->IsFramebufferOES)
#define SET_IsFramebufferOES(disp, fn) ((disp)->IsFramebufferOES = fn)
#define CALL_IsRenderbufferOES(disp, parameters) (*((disp)->IsRenderbufferOES)) parameters
#define GET_IsRenderbufferOES(disp) ((disp)->IsRenderbufferOES)
#define SET_IsRenderbufferOES(disp, fn) ((disp)->IsRenderbufferOES = fn)
#define CALL_RenderbufferStorageOES(disp, parameters) (*((disp)->RenderbufferStorageOES)) parameters
#define GET_RenderbufferStorageOES(disp) ((disp)->RenderbufferStorageOES)
#define SET_RenderbufferStorageOES(disp, fn) ((disp)->RenderbufferStorageOES = fn)
#define CALL_PointSizePointerOES(disp, parameters) (*((disp)->PointSizePointerOES)) parameters
#define GET_PointSizePointerOES(disp) ((disp)->PointSizePointerOES)
#define SET_PointSizePointerOES(disp, fn) ((disp)->PointSizePointerOES = fn)
#define CALL_QueryMatrixxOES(disp, parameters) (*((disp)->QueryMatrixxOES)) parameters
#define GET_QueryMatrixxOES(disp) ((disp)->QueryMatrixxOES)
#define SET_QueryMatrixxOES(disp, fn) ((disp)->QueryMatrixxOES = fn)
#define CALL_GetTexGenxvOES(disp, parameters) (*((disp)->GetTexGenxvOES)) parameters
#define GET_GetTexGenxvOES(disp) ((disp)->GetTexGenxvOES)
#define SET_GetTexGenxvOES(disp, fn) ((disp)->GetTexGenxvOES = fn)
#define CALL_TexGenxOES(disp, parameters) (*((disp)->TexGenxOES)) parameters
#define GET_TexGenxOES(disp) ((disp)->TexGenxOES)
#define SET_TexGenxOES(disp, fn) ((disp)->TexGenxOES = fn)
#define CALL_TexGenxvOES(disp, parameters) (*((disp)->TexGenxvOES)) parameters
#define GET_TexGenxvOES(disp) ((disp)->TexGenxvOES)
#define SET_TexGenxvOES(disp, fn) ((disp)->TexGenxvOES = fn)
#define CALL_EGLImageTargetRenderbufferStorageOES(disp, parameters) (*((disp)->EGLImageTargetRenderbufferStorageOES)) parameters
#define GET_EGLImageTargetRenderbufferStorageOES(disp) ((disp)->EGLImageTargetRenderbufferStorageOES)
#define SET_EGLImageTargetRenderbufferStorageOES(disp, fn) ((disp)->EGLImageTargetRenderbufferStorageOES = fn)
#define CALL_EGLImageTargetTexture2DOES(disp, parameters) (*((disp)->EGLImageTargetTexture2DOES)) parameters
#define GET_EGLImageTargetTexture2DOES(disp) ((disp)->EGLImageTargetTexture2DOES)
#define SET_EGLImageTargetTexture2DOES(disp, fn) ((disp)->EGLImageTargetTexture2DOES = fn)
#define CALL_GetBufferPointervOES(disp, parameters) (*((disp)->GetBufferPointervOES)) parameters
#define GET_GetBufferPointervOES(disp) ((disp)->GetBufferPointervOES)
#define SET_GetBufferPointervOES(disp, fn) ((disp)->GetBufferPointervOES = fn)
#define CALL_MapBufferOES(disp, parameters) (*((disp)->MapBufferOES)) parameters
#define GET_MapBufferOES(disp) ((disp)->MapBufferOES)
#define SET_MapBufferOES(disp, fn) ((disp)->MapBufferOES = fn)
#define CALL_UnmapBufferOES(disp, parameters) (*((disp)->UnmapBufferOES)) parameters
#define GET_UnmapBufferOES(disp) ((disp)->UnmapBufferOES)
#define SET_UnmapBufferOES(disp, fn) ((disp)->UnmapBufferOES = fn)
#define CALL_BindVertexArrayAPPLE(disp, parameters) (*((disp)->BindVertexArrayAPPLE)) parameters
#define GET_BindVertexArrayAPPLE(disp) ((disp)->BindVertexArrayAPPLE)
#define SET_BindVertexArrayAPPLE(disp, fn) ((disp)->BindVertexArrayAPPLE = fn)
#define CALL_DeleteVertexArraysAPPLE(disp, parameters) (*((disp)->DeleteVertexArraysAPPLE)) parameters
#define GET_DeleteVertexArraysAPPLE(disp) ((disp)->DeleteVertexArraysAPPLE)
#define SET_DeleteVertexArraysAPPLE(disp, fn) ((disp)->DeleteVertexArraysAPPLE = fn)
#define CALL_GenVertexArraysAPPLE(disp, parameters) (*((disp)->GenVertexArraysAPPLE)) parameters
#define GET_GenVertexArraysAPPLE(disp) ((disp)->GenVertexArraysAPPLE)
#define SET_GenVertexArraysAPPLE(disp, fn) ((disp)->GenVertexArraysAPPLE = fn)
#define CALL_IsVertexArrayAPPLE(disp, parameters) (*((disp)->IsVertexArrayAPPLE)) parameters
#define GET_IsVertexArrayAPPLE(disp) ((disp)->IsVertexArrayAPPLE)
#define SET_IsVertexArrayAPPLE(disp, fn) ((disp)->IsVertexArrayAPPLE = fn)
#define CALL_CompressedTexImage2D(disp, parameters) (*((disp)->CompressedTexImage2D)) parameters
#define GET_CompressedTexImage2D(disp) ((disp)->CompressedTexImage2D)
#define SET_CompressedTexImage2D(disp, fn) ((disp)->CompressedTexImage2D = fn)
#define CALL_CompressedTexSubImage2D(disp, parameters) (*((disp)->CompressedTexSubImage2D)) parameters
#define GET_CompressedTexSubImage2D(disp) ((disp)->CompressedTexSubImage2D)
#define SET_CompressedTexSubImage2D(disp, fn) ((disp)->CompressedTexSubImage2D = fn)
#define CALL_SampleCoverage(disp, parameters) (*((disp)->SampleCoverage)) parameters
#define GET_SampleCoverage(disp) ((disp)->SampleCoverage)
#define SET_SampleCoverage(disp, fn) ((disp)->SampleCoverage = fn)
#define CALL_BindBuffer(disp, parameters) (*((disp)->BindBuffer)) parameters
#define GET_BindBuffer(disp) ((disp)->BindBuffer)
#define SET_BindBuffer(disp, fn) ((disp)->BindBuffer = fn)
#define CALL_BufferData(disp, parameters) (*((disp)->BufferData)) parameters
#define GET_BufferData(disp) ((disp)->BufferData)
#define SET_BufferData(disp, fn) ((disp)->BufferData = fn)
#define CALL_BufferSubData(disp, parameters) (*((disp)->BufferSubData)) parameters
#define GET_BufferSubData(disp) ((disp)->BufferSubData)
#define SET_BufferSubData(disp, fn) ((disp)->BufferSubData = fn)
#define CALL_DeleteBuffers(disp, parameters) (*((disp)->DeleteBuffers)) parameters
#define GET_DeleteBuffers(disp) ((disp)->DeleteBuffers)
#define SET_DeleteBuffers(disp, fn) ((disp)->DeleteBuffers = fn)
#define CALL_GenBuffers(disp, parameters) (*((disp)->GenBuffers)) parameters
#define GET_GenBuffers(disp) ((disp)->GenBuffers)
#define SET_GenBuffers(disp, fn) ((disp)->GenBuffers = fn)
#define CALL_GetBufferParameteriv(disp, parameters) (*((disp)->GetBufferParameteriv)) parameters
#define GET_GetBufferParameteriv(disp) ((disp)->GetBufferParameteriv)
#define SET_GetBufferParameteriv(disp, fn) ((disp)->GetBufferParameteriv = fn)
#define CALL_IsBuffer(disp, parameters) (*((disp)->IsBuffer)) parameters
#define GET_IsBuffer(disp) ((disp)->IsBuffer)
#define SET_IsBuffer(disp, fn) ((disp)->IsBuffer = fn)
#define CALL_AlphaFuncx(disp, parameters) (*((disp)->AlphaFuncx)) parameters
#define GET_AlphaFuncx(disp) ((disp)->AlphaFuncx)
#define SET_AlphaFuncx(disp, fn) ((disp)->AlphaFuncx = fn)
#define CALL_ClearColorx(disp, parameters) (*((disp)->ClearColorx)) parameters
#define GET_ClearColorx(disp) ((disp)->ClearColorx)
#define SET_ClearColorx(disp, fn) ((disp)->ClearColorx = fn)
#define CALL_ClearDepthf(disp, parameters) (*((disp)->ClearDepthf)) parameters
#define GET_ClearDepthf(disp) ((disp)->ClearDepthf)
#define SET_ClearDepthf(disp, fn) ((disp)->ClearDepthf = fn)
#define CALL_ClearDepthx(disp, parameters) (*((disp)->ClearDepthx)) parameters
#define GET_ClearDepthx(disp) ((disp)->ClearDepthx)
#define SET_ClearDepthx(disp, fn) ((disp)->ClearDepthx = fn)
#define CALL_Color4x(disp, parameters) (*((disp)->Color4x)) parameters
#define GET_Color4x(disp) ((disp)->Color4x)
#define SET_Color4x(disp, fn) ((disp)->Color4x = fn)
#define CALL_DepthRangef(disp, parameters) (*((disp)->DepthRangef)) parameters
#define GET_DepthRangef(disp) ((disp)->DepthRangef)
#define SET_DepthRangef(disp, fn) ((disp)->DepthRangef = fn)
#define CALL_DepthRangex(disp, parameters) (*((disp)->DepthRangex)) parameters
#define GET_DepthRangex(disp) ((disp)->DepthRangex)
#define SET_DepthRangex(disp, fn) ((disp)->DepthRangex = fn)
#define CALL_Fogx(disp, parameters) (*((disp)->Fogx)) parameters
#define GET_Fogx(disp) ((disp)->Fogx)
#define SET_Fogx(disp, fn) ((disp)->Fogx = fn)
#define CALL_Fogxv(disp, parameters) (*((disp)->Fogxv)) parameters
#define GET_Fogxv(disp) ((disp)->Fogxv)
#define SET_Fogxv(disp, fn) ((disp)->Fogxv = fn)
#define CALL_Frustumf(disp, parameters) (*((disp)->Frustumf)) parameters
#define GET_Frustumf(disp) ((disp)->Frustumf)
#define SET_Frustumf(disp, fn) ((disp)->Frustumf = fn)
#define CALL_Frustumx(disp, parameters) (*((disp)->Frustumx)) parameters
#define GET_Frustumx(disp) ((disp)->Frustumx)
#define SET_Frustumx(disp, fn) ((disp)->Frustumx = fn)
#define CALL_LightModelx(disp, parameters) (*((disp)->LightModelx)) parameters
#define GET_LightModelx(disp) ((disp)->LightModelx)
#define SET_LightModelx(disp, fn) ((disp)->LightModelx = fn)
#define CALL_LightModelxv(disp, parameters) (*((disp)->LightModelxv)) parameters
#define GET_LightModelxv(disp) ((disp)->LightModelxv)
#define SET_LightModelxv(disp, fn) ((disp)->LightModelxv = fn)
#define CALL_Lightx(disp, parameters) (*((disp)->Lightx)) parameters
#define GET_Lightx(disp) ((disp)->Lightx)
#define SET_Lightx(disp, fn) ((disp)->Lightx = fn)
#define CALL_Lightxv(disp, parameters) (*((disp)->Lightxv)) parameters
#define GET_Lightxv(disp) ((disp)->Lightxv)
#define SET_Lightxv(disp, fn) ((disp)->Lightxv = fn)
#define CALL_LineWidthx(disp, parameters) (*((disp)->LineWidthx)) parameters
#define GET_LineWidthx(disp) ((disp)->LineWidthx)
#define SET_LineWidthx(disp, fn) ((disp)->LineWidthx = fn)
#define CALL_LoadMatrixx(disp, parameters) (*((disp)->LoadMatrixx)) parameters
#define GET_LoadMatrixx(disp) ((disp)->LoadMatrixx)
#define SET_LoadMatrixx(disp, fn) ((disp)->LoadMatrixx = fn)
#define CALL_Materialx(disp, parameters) (*((disp)->Materialx)) parameters
#define GET_Materialx(disp) ((disp)->Materialx)
#define SET_Materialx(disp, fn) ((disp)->Materialx = fn)
#define CALL_Materialxv(disp, parameters) (*((disp)->Materialxv)) parameters
#define GET_Materialxv(disp) ((disp)->Materialxv)
#define SET_Materialxv(disp, fn) ((disp)->Materialxv = fn)
#define CALL_MultMatrixx(disp, parameters) (*((disp)->MultMatrixx)) parameters
#define GET_MultMatrixx(disp) ((disp)->MultMatrixx)
#define SET_MultMatrixx(disp, fn) ((disp)->MultMatrixx = fn)
#define CALL_MultiTexCoord4x(disp, parameters) (*((disp)->MultiTexCoord4x)) parameters
#define GET_MultiTexCoord4x(disp) ((disp)->MultiTexCoord4x)
#define SET_MultiTexCoord4x(disp, fn) ((disp)->MultiTexCoord4x = fn)
#define CALL_Normal3x(disp, parameters) (*((disp)->Normal3x)) parameters
#define GET_Normal3x(disp) ((disp)->Normal3x)
#define SET_Normal3x(disp, fn) ((disp)->Normal3x = fn)
#define CALL_Orthof(disp, parameters) (*((disp)->Orthof)) parameters
#define GET_Orthof(disp) ((disp)->Orthof)
#define SET_Orthof(disp, fn) ((disp)->Orthof = fn)
#define CALL_Orthox(disp, parameters) (*((disp)->Orthox)) parameters
#define GET_Orthox(disp) ((disp)->Orthox)
#define SET_Orthox(disp, fn) ((disp)->Orthox = fn)
#define CALL_PointSizex(disp, parameters) (*((disp)->PointSizex)) parameters
#define GET_PointSizex(disp) ((disp)->PointSizex)
#define SET_PointSizex(disp, fn) ((disp)->PointSizex = fn)
#define CALL_PolygonOffsetx(disp, parameters) (*((disp)->PolygonOffsetx)) parameters
#define GET_PolygonOffsetx(disp) ((disp)->PolygonOffsetx)
#define SET_PolygonOffsetx(disp, fn) ((disp)->PolygonOffsetx = fn)
#define CALL_Rotatex(disp, parameters) (*((disp)->Rotatex)) parameters
#define GET_Rotatex(disp) ((disp)->Rotatex)
#define SET_Rotatex(disp, fn) ((disp)->Rotatex = fn)
#define CALL_SampleCoveragex(disp, parameters) (*((disp)->SampleCoveragex)) parameters
#define GET_SampleCoveragex(disp) ((disp)->SampleCoveragex)
#define SET_SampleCoveragex(disp, fn) ((disp)->SampleCoveragex = fn)
#define CALL_Scalex(disp, parameters) (*((disp)->Scalex)) parameters
#define GET_Scalex(disp) ((disp)->Scalex)
#define SET_Scalex(disp, fn) ((disp)->Scalex = fn)
#define CALL_TexEnvx(disp, parameters) (*((disp)->TexEnvx)) parameters
#define GET_TexEnvx(disp) ((disp)->TexEnvx)
#define SET_TexEnvx(disp, fn) ((disp)->TexEnvx = fn)
#define CALL_TexEnvxv(disp, parameters) (*((disp)->TexEnvxv)) parameters
#define GET_TexEnvxv(disp) ((disp)->TexEnvxv)
#define SET_TexEnvxv(disp, fn) ((disp)->TexEnvxv = fn)
#define CALL_TexParameterx(disp, parameters) (*((disp)->TexParameterx)) parameters
#define GET_TexParameterx(disp) ((disp)->TexParameterx)
#define SET_TexParameterx(disp, fn) ((disp)->TexParameterx = fn)
#define CALL_Translatex(disp, parameters) (*((disp)->Translatex)) parameters
#define GET_Translatex(disp) ((disp)->Translatex)
#define SET_Translatex(disp, fn) ((disp)->Translatex = fn)
#define CALL_ClipPlanef(disp, parameters) (*((disp)->ClipPlanef)) parameters
#define GET_ClipPlanef(disp) ((disp)->ClipPlanef)
#define SET_ClipPlanef(disp, fn) ((disp)->ClipPlanef = fn)
#define CALL_ClipPlanex(disp, parameters) (*((disp)->ClipPlanex)) parameters
#define GET_ClipPlanex(disp) ((disp)->ClipPlanex)
#define SET_ClipPlanex(disp, fn) ((disp)->ClipPlanex = fn)
#define CALL_GetClipPlanef(disp, parameters) (*((disp)->GetClipPlanef)) parameters
#define GET_GetClipPlanef(disp) ((disp)->GetClipPlanef)
#define SET_GetClipPlanef(disp, fn) ((disp)->GetClipPlanef = fn)
#define CALL_GetClipPlanex(disp, parameters) (*((disp)->GetClipPlanex)) parameters
#define GET_GetClipPlanex(disp) ((disp)->GetClipPlanex)
#define SET_GetClipPlanex(disp, fn) ((disp)->GetClipPlanex = fn)
#define CALL_GetFixedv(disp, parameters) (*((disp)->GetFixedv)) parameters
#define GET_GetFixedv(disp) ((disp)->GetFixedv)
#define SET_GetFixedv(disp, fn) ((disp)->GetFixedv = fn)
#define CALL_GetLightxv(disp, parameters) (*((disp)->GetLightxv)) parameters
#define GET_GetLightxv(disp) ((disp)->GetLightxv)
#define SET_GetLightxv(disp, fn) ((disp)->GetLightxv = fn)
#define CALL_GetMaterialxv(disp, parameters) (*((disp)->GetMaterialxv)) parameters
#define GET_GetMaterialxv(disp) ((disp)->GetMaterialxv)
#define SET_GetMaterialxv(disp, fn) ((disp)->GetMaterialxv = fn)
#define CALL_GetTexEnvxv(disp, parameters) (*((disp)->GetTexEnvxv)) parameters
#define GET_GetTexEnvxv(disp) ((disp)->GetTexEnvxv)
#define SET_GetTexEnvxv(disp, fn) ((disp)->GetTexEnvxv = fn)
#define CALL_GetTexParameterxv(disp, parameters) (*((disp)->GetTexParameterxv)) parameters
#define GET_GetTexParameterxv(disp) ((disp)->GetTexParameterxv)
#define SET_GetTexParameterxv(disp, fn) ((disp)->GetTexParameterxv = fn)
#define CALL_PointParameterx(disp, parameters) (*((disp)->PointParameterx)) parameters
#define GET_PointParameterx(disp) ((disp)->PointParameterx)
#define SET_PointParameterx(disp, fn) ((disp)->PointParameterx = fn)
#define CALL_PointParameterxv(disp, parameters) (*((disp)->PointParameterxv)) parameters
#define GET_PointParameterxv(disp) ((disp)->PointParameterxv)
#define SET_PointParameterxv(disp, fn) ((disp)->PointParameterxv = fn)
#define CALL_TexParameterxv(disp, parameters) (*((disp)->TexParameterxv)) parameters
#define GET_TexParameterxv(disp) ((disp)->TexParameterxv)
#define SET_TexParameterxv(disp, fn) ((disp)->TexParameterxv = fn)
#define CALL_PointParameterf(disp, parameters) (*((disp)->PointParameterf)) parameters
#define GET_PointParameterf(disp) ((disp)->PointParameterf)
#define SET_PointParameterf(disp, fn) ((disp)->PointParameterf = fn)
#define CALL_PointParameterfv(disp, parameters) (*((disp)->PointParameterfv)) parameters
#define GET_PointParameterfv(disp) ((disp)->PointParameterfv)
#define SET_PointParameterfv(disp, fn) ((disp)->PointParameterfv = fn)

#else

#define driDispatchRemapTable_size 194
extern int driDispatchRemapTable[ driDispatchRemapTable_size ];

#define Color4f_remap_index 0
#define Color4ub_remap_index 1
#define Normal3f_remap_index 2
#define CullFace_remap_index 3
#define Fogf_remap_index 4
#define Fogfv_remap_index 5
#define FrontFace_remap_index 6
#define Hint_remap_index 7
#define Lightf_remap_index 8
#define Lightfv_remap_index 9
#define LightModelf_remap_index 10
#define LightModelfv_remap_index 11
#define LineWidth_remap_index 12
#define Materialf_remap_index 13
#define Materialfv_remap_index 14
#define PointSize_remap_index 15
#define Scissor_remap_index 16
#define ShadeModel_remap_index 17
#define TexParameterf_remap_index 18
#define TexParameterfv_remap_index 19
#define TexParameteri_remap_index 20
#define TexParameteriv_remap_index 21
#define TexImage2D_remap_index 22
#define TexEnvf_remap_index 23
#define TexEnvfv_remap_index 24
#define TexEnvi_remap_index 25
#define TexEnviv_remap_index 26
#define TexGenfOES_remap_index 27
#define TexGenfvOES_remap_index 28
#define TexGeniOES_remap_index 29
#define TexGenivOES_remap_index 30
#define Clear_remap_index 31
#define ClearColor_remap_index 32
#define ClearStencil_remap_index 33
#define StencilMask_remap_index 34
#define ColorMask_remap_index 35
#define DepthMask_remap_index 36
#define Disable_remap_index 37
#define Enable_remap_index 38
#define Finish_remap_index 39
#define Flush_remap_index 40
#define AlphaFunc_remap_index 41
#define BlendFunc_remap_index 42
#define LogicOp_remap_index 43
#define StencilFunc_remap_index 44
#define StencilOp_remap_index 45
#define DepthFunc_remap_index 46
#define PixelStorei_remap_index 47
#define ReadPixels_remap_index 48
#define GetBooleanv_remap_index 49
#define GetError_remap_index 50
#define GetFloatv_remap_index 51
#define GetIntegerv_remap_index 52
#define GetLightfv_remap_index 53
#define GetMaterialfv_remap_index 54
#define GetString_remap_index 55
#define GetTexEnvfv_remap_index 56
#define GetTexEnviv_remap_index 57
#define GetTexGenfvOES_remap_index 58
#define GetTexGenivOES_remap_index 59
#define GetTexParameterfv_remap_index 60
#define GetTexParameteriv_remap_index 61
#define IsEnabled_remap_index 62
#define LoadIdentity_remap_index 63
#define LoadMatrixf_remap_index 64
#define MatrixMode_remap_index 65
#define MultMatrixf_remap_index 66
#define PopMatrix_remap_index 67
#define PushMatrix_remap_index 68
#define Rotatef_remap_index 69
#define Scalef_remap_index 70
#define Translatef_remap_index 71
#define Viewport_remap_index 72
#define BindTexture_remap_index 73
#define ColorPointer_remap_index 74
#define DisableClientState_remap_index 75
#define DrawArrays_remap_index 76
#define DrawElements_remap_index 77
#define EnableClientState_remap_index 78
#define NormalPointer_remap_index 79
#define PolygonOffset_remap_index 80
#define TexCoordPointer_remap_index 81
#define VertexPointer_remap_index 82
#define CopyTexImage2D_remap_index 83
#define CopyTexSubImage2D_remap_index 84
#define DeleteTextures_remap_index 85
#define GenTextures_remap_index 86
#define GetPointerv_remap_index 87
#define IsTexture_remap_index 88
#define TexSubImage2D_remap_index 89
#define BlendColor_remap_index 90
#define BlendEquationOES_remap_index 91
#define TexImage3D_remap_index 92
#define TexSubImage3D_remap_index 93
#define CopyTexSubImage3D_remap_index 94
#define ActiveTexture_remap_index 95
#define ClientActiveTexture_remap_index 96
#define MultiTexCoord4f_remap_index 97
#define BlendEquationSeparateOES_remap_index 98
#define BlendFuncSeparateOES_remap_index 99
#define DrawTexfOES_remap_index 100
#define DrawTexfvOES_remap_index 101
#define DrawTexiOES_remap_index 102
#define DrawTexivOES_remap_index 103
#define DrawTexsOES_remap_index 104
#define DrawTexsvOES_remap_index 105
#define DrawTexxOES_remap_index 106
#define DrawTexxvOES_remap_index 107
#define BindFramebufferOES_remap_index 108
#define BindRenderbufferOES_remap_index 109
#define CheckFramebufferStatusOES_remap_index 110
#define DeleteFramebuffersOES_remap_index 111
#define DeleteRenderbuffersOES_remap_index 112
#define FramebufferRenderbufferOES_remap_index 113
#define FramebufferTexture2DOES_remap_index 114
#define GenFramebuffersOES_remap_index 115
#define GenRenderbuffersOES_remap_index 116
#define GenerateMipmapOES_remap_index 117
#define GetFramebufferAttachmentParameterivOES_remap_index 118
#define GetRenderbufferParameterivOES_remap_index 119
#define IsFramebufferOES_remap_index 120
#define IsRenderbufferOES_remap_index 121
#define RenderbufferStorageOES_remap_index 122
#define PointSizePointerOES_remap_index 123
#define QueryMatrixxOES_remap_index 124
#define GetTexGenxvOES_remap_index 125
#define TexGenxOES_remap_index 126
#define TexGenxvOES_remap_index 127
#define EGLImageTargetRenderbufferStorageOES_remap_index 128
#define EGLImageTargetTexture2DOES_remap_index 129
#define GetBufferPointervOES_remap_index 130
#define MapBufferOES_remap_index 131
#define UnmapBufferOES_remap_index 132
#define BindVertexArrayAPPLE_remap_index 133
#define DeleteVertexArraysAPPLE_remap_index 134
#define GenVertexArraysAPPLE_remap_index 135
#define IsVertexArrayAPPLE_remap_index 136
#define CompressedTexImage2D_remap_index 137
#define CompressedTexSubImage2D_remap_index 138
#define SampleCoverage_remap_index 139
#define BindBuffer_remap_index 140
#define BufferData_remap_index 141
#define BufferSubData_remap_index 142
#define DeleteBuffers_remap_index 143
#define GenBuffers_remap_index 144
#define GetBufferParameteriv_remap_index 145
#define IsBuffer_remap_index 146
#define AlphaFuncx_remap_index 147
#define ClearColorx_remap_index 148
#define ClearDepthf_remap_index 149
#define ClearDepthx_remap_index 150
#define Color4x_remap_index 151
#define DepthRangef_remap_index 152
#define DepthRangex_remap_index 153
#define Fogx_remap_index 154
#define Fogxv_remap_index 155
#define Frustumf_remap_index 156
#define Frustumx_remap_index 157
#define LightModelx_remap_index 158
#define LightModelxv_remap_index 159
#define Lightx_remap_index 160
#define Lightxv_remap_index 161
#define LineWidthx_remap_index 162
#define LoadMatrixx_remap_index 163
#define Materialx_remap_index 164
#define Materialxv_remap_index 165
#define MultMatrixx_remap_index 166
#define MultiTexCoord4x_remap_index 167
#define Normal3x_remap_index 168
#define Orthof_remap_index 169
#define Orthox_remap_index 170
#define PointSizex_remap_index 171
#define PolygonOffsetx_remap_index 172
#define Rotatex_remap_index 173
#define SampleCoveragex_remap_index 174
#define Scalex_remap_index 175
#define TexEnvx_remap_index 176
#define TexEnvxv_remap_index 177
#define TexParameterx_remap_index 178
#define Translatex_remap_index 179
#define ClipPlanef_remap_index 180
#define ClipPlanex_remap_index 181
#define GetClipPlanef_remap_index 182
#define GetClipPlanex_remap_index 183
#define GetFixedv_remap_index 184
#define GetLightxv_remap_index 185
#define GetMaterialxv_remap_index 186
#define GetTexEnvxv_remap_index 187
#define GetTexParameterxv_remap_index 188
#define PointParameterx_remap_index 189
#define PointParameterxv_remap_index 190
#define TexParameterxv_remap_index 191
#define PointParameterf_remap_index 192
#define PointParameterfv_remap_index 193

#define CALL_Color4f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat)), driDispatchRemapTable[Color4f_remap_index], parameters)
#define GET_Color4f(disp) GET_by_offset(disp, driDispatchRemapTable[Color4f_remap_index])
#define SET_Color4f(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Color4f_remap_index], fn)
#define CALL_Color4ub(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLubyte, GLubyte, GLubyte, GLubyte)), driDispatchRemapTable[Color4ub_remap_index], parameters)
#define GET_Color4ub(disp) GET_by_offset(disp, driDispatchRemapTable[Color4ub_remap_index])
#define SET_Color4ub(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Color4ub_remap_index], fn)
#define CALL_Normal3f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat)), driDispatchRemapTable[Normal3f_remap_index], parameters)
#define GET_Normal3f(disp) GET_by_offset(disp, driDispatchRemapTable[Normal3f_remap_index])
#define SET_Normal3f(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Normal3f_remap_index], fn)
#define CALL_CullFace(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[CullFace_remap_index], parameters)
#define GET_CullFace(disp) GET_by_offset(disp, driDispatchRemapTable[CullFace_remap_index])
#define SET_CullFace(disp, fn) SET_by_offset(disp, driDispatchRemapTable[CullFace_remap_index], fn)
#define CALL_Fogf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat)), driDispatchRemapTable[Fogf_remap_index], parameters)
#define GET_Fogf(disp) GET_by_offset(disp, driDispatchRemapTable[Fogf_remap_index])
#define SET_Fogf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Fogf_remap_index], fn)
#define CALL_Fogfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfloat *)), driDispatchRemapTable[Fogfv_remap_index], parameters)
#define GET_Fogfv(disp) GET_by_offset(disp, driDispatchRemapTable[Fogfv_remap_index])
#define SET_Fogfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Fogfv_remap_index], fn)
#define CALL_FrontFace(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[FrontFace_remap_index], parameters)
#define GET_FrontFace(disp) GET_by_offset(disp, driDispatchRemapTable[FrontFace_remap_index])
#define SET_FrontFace(disp, fn) SET_by_offset(disp, driDispatchRemapTable[FrontFace_remap_index], fn)
#define CALL_Hint(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum)), driDispatchRemapTable[Hint_remap_index], parameters)
#define GET_Hint(disp) GET_by_offset(disp, driDispatchRemapTable[Hint_remap_index])
#define SET_Hint(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Hint_remap_index], fn)
#define CALL_Lightf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), driDispatchRemapTable[Lightf_remap_index], parameters)
#define GET_Lightf(disp) GET_by_offset(disp, driDispatchRemapTable[Lightf_remap_index])
#define SET_Lightf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Lightf_remap_index], fn)
#define CALL_Lightfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), driDispatchRemapTable[Lightfv_remap_index], parameters)
#define GET_Lightfv(disp) GET_by_offset(disp, driDispatchRemapTable[Lightfv_remap_index])
#define SET_Lightfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Lightfv_remap_index], fn)
#define CALL_LightModelf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat)), driDispatchRemapTable[LightModelf_remap_index], parameters)
#define GET_LightModelf(disp) GET_by_offset(disp, driDispatchRemapTable[LightModelf_remap_index])
#define SET_LightModelf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[LightModelf_remap_index], fn)
#define CALL_LightModelfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfloat *)), driDispatchRemapTable[LightModelfv_remap_index], parameters)
#define GET_LightModelfv(disp) GET_by_offset(disp, driDispatchRemapTable[LightModelfv_remap_index])
#define SET_LightModelfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[LightModelfv_remap_index], fn)
#define CALL_LineWidth(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat)), driDispatchRemapTable[LineWidth_remap_index], parameters)
#define GET_LineWidth(disp) GET_by_offset(disp, driDispatchRemapTable[LineWidth_remap_index])
#define SET_LineWidth(disp, fn) SET_by_offset(disp, driDispatchRemapTable[LineWidth_remap_index], fn)
#define CALL_Materialf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), driDispatchRemapTable[Materialf_remap_index], parameters)
#define GET_Materialf(disp) GET_by_offset(disp, driDispatchRemapTable[Materialf_remap_index])
#define SET_Materialf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Materialf_remap_index], fn)
#define CALL_Materialfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), driDispatchRemapTable[Materialfv_remap_index], parameters)
#define GET_Materialfv(disp) GET_by_offset(disp, driDispatchRemapTable[Materialfv_remap_index])
#define SET_Materialfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Materialfv_remap_index], fn)
#define CALL_PointSize(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat)), driDispatchRemapTable[PointSize_remap_index], parameters)
#define GET_PointSize(disp) GET_by_offset(disp, driDispatchRemapTable[PointSize_remap_index])
#define SET_PointSize(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PointSize_remap_index], fn)
#define CALL_Scissor(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLsizei, GLsizei)), driDispatchRemapTable[Scissor_remap_index], parameters)
#define GET_Scissor(disp) GET_by_offset(disp, driDispatchRemapTable[Scissor_remap_index])
#define SET_Scissor(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Scissor_remap_index], fn)
#define CALL_ShadeModel(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[ShadeModel_remap_index], parameters)
#define GET_ShadeModel(disp) GET_by_offset(disp, driDispatchRemapTable[ShadeModel_remap_index])
#define SET_ShadeModel(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ShadeModel_remap_index], fn)
#define CALL_TexParameterf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), driDispatchRemapTable[TexParameterf_remap_index], parameters)
#define GET_TexParameterf(disp) GET_by_offset(disp, driDispatchRemapTable[TexParameterf_remap_index])
#define SET_TexParameterf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexParameterf_remap_index], fn)
#define CALL_TexParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), driDispatchRemapTable[TexParameterfv_remap_index], parameters)
#define GET_TexParameterfv(disp) GET_by_offset(disp, driDispatchRemapTable[TexParameterfv_remap_index])
#define SET_TexParameterfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexParameterfv_remap_index], fn)
#define CALL_TexParameteri(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint)), driDispatchRemapTable[TexParameteri_remap_index], parameters)
#define GET_TexParameteri(disp) GET_by_offset(disp, driDispatchRemapTable[TexParameteri_remap_index])
#define SET_TexParameteri(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexParameteri_remap_index], fn)
#define CALL_TexParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLint *)), driDispatchRemapTable[TexParameteriv_remap_index], parameters)
#define GET_TexParameteriv(disp) GET_by_offset(disp, driDispatchRemapTable[TexParameteriv_remap_index])
#define SET_TexParameteriv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexParameteriv_remap_index], fn)
#define CALL_TexImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid *)), driDispatchRemapTable[TexImage2D_remap_index], parameters)
#define GET_TexImage2D(disp) GET_by_offset(disp, driDispatchRemapTable[TexImage2D_remap_index])
#define SET_TexImage2D(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexImage2D_remap_index], fn)
#define CALL_TexEnvf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), driDispatchRemapTable[TexEnvf_remap_index], parameters)
#define GET_TexEnvf(disp) GET_by_offset(disp, driDispatchRemapTable[TexEnvf_remap_index])
#define SET_TexEnvf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexEnvf_remap_index], fn)
#define CALL_TexEnvfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), driDispatchRemapTable[TexEnvfv_remap_index], parameters)
#define GET_TexEnvfv(disp) GET_by_offset(disp, driDispatchRemapTable[TexEnvfv_remap_index])
#define SET_TexEnvfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexEnvfv_remap_index], fn)
#define CALL_TexEnvi(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint)), driDispatchRemapTable[TexEnvi_remap_index], parameters)
#define GET_TexEnvi(disp) GET_by_offset(disp, driDispatchRemapTable[TexEnvi_remap_index])
#define SET_TexEnvi(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexEnvi_remap_index], fn)
#define CALL_TexEnviv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLint *)), driDispatchRemapTable[TexEnviv_remap_index], parameters)
#define GET_TexEnviv(disp) GET_by_offset(disp, driDispatchRemapTable[TexEnviv_remap_index])
#define SET_TexEnviv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexEnviv_remap_index], fn)
#define CALL_TexGenfOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), driDispatchRemapTable[TexGenfOES_remap_index], parameters)
#define GET_TexGenfOES(disp) GET_by_offset(disp, driDispatchRemapTable[TexGenfOES_remap_index])
#define SET_TexGenfOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexGenfOES_remap_index], fn)
#define CALL_TexGenfvOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), driDispatchRemapTable[TexGenfvOES_remap_index], parameters)
#define GET_TexGenfvOES(disp) GET_by_offset(disp, driDispatchRemapTable[TexGenfvOES_remap_index])
#define SET_TexGenfvOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexGenfvOES_remap_index], fn)
#define CALL_TexGeniOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint)), driDispatchRemapTable[TexGeniOES_remap_index], parameters)
#define GET_TexGeniOES(disp) GET_by_offset(disp, driDispatchRemapTable[TexGeniOES_remap_index])
#define SET_TexGeniOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexGeniOES_remap_index], fn)
#define CALL_TexGenivOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLint *)), driDispatchRemapTable[TexGenivOES_remap_index], parameters)
#define GET_TexGenivOES(disp) GET_by_offset(disp, driDispatchRemapTable[TexGenivOES_remap_index])
#define SET_TexGenivOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexGenivOES_remap_index], fn)
#define CALL_Clear(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLbitfield)), driDispatchRemapTable[Clear_remap_index], parameters)
#define GET_Clear(disp) GET_by_offset(disp, driDispatchRemapTable[Clear_remap_index])
#define SET_Clear(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Clear_remap_index], fn)
#define CALL_ClearColor(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampf, GLclampf, GLclampf, GLclampf)), driDispatchRemapTable[ClearColor_remap_index], parameters)
#define GET_ClearColor(disp) GET_by_offset(disp, driDispatchRemapTable[ClearColor_remap_index])
#define SET_ClearColor(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ClearColor_remap_index], fn)
#define CALL_ClearStencil(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint)), driDispatchRemapTable[ClearStencil_remap_index], parameters)
#define GET_ClearStencil(disp) GET_by_offset(disp, driDispatchRemapTable[ClearStencil_remap_index])
#define SET_ClearStencil(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ClearStencil_remap_index], fn)
#define CALL_StencilMask(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), driDispatchRemapTable[StencilMask_remap_index], parameters)
#define GET_StencilMask(disp) GET_by_offset(disp, driDispatchRemapTable[StencilMask_remap_index])
#define SET_StencilMask(disp, fn) SET_by_offset(disp, driDispatchRemapTable[StencilMask_remap_index], fn)
#define CALL_ColorMask(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLboolean, GLboolean, GLboolean, GLboolean)), driDispatchRemapTable[ColorMask_remap_index], parameters)
#define GET_ColorMask(disp) GET_by_offset(disp, driDispatchRemapTable[ColorMask_remap_index])
#define SET_ColorMask(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ColorMask_remap_index], fn)
#define CALL_DepthMask(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLboolean)), driDispatchRemapTable[DepthMask_remap_index], parameters)
#define GET_DepthMask(disp) GET_by_offset(disp, driDispatchRemapTable[DepthMask_remap_index])
#define SET_DepthMask(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DepthMask_remap_index], fn)
#define CALL_Disable(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[Disable_remap_index], parameters)
#define GET_Disable(disp) GET_by_offset(disp, driDispatchRemapTable[Disable_remap_index])
#define SET_Disable(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Disable_remap_index], fn)
#define CALL_Enable(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[Enable_remap_index], parameters)
#define GET_Enable(disp) GET_by_offset(disp, driDispatchRemapTable[Enable_remap_index])
#define SET_Enable(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Enable_remap_index], fn)
#define CALL_Finish(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), driDispatchRemapTable[Finish_remap_index], parameters)
#define GET_Finish(disp) GET_by_offset(disp, driDispatchRemapTable[Finish_remap_index])
#define SET_Finish(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Finish_remap_index], fn)
#define CALL_Flush(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), driDispatchRemapTable[Flush_remap_index], parameters)
#define GET_Flush(disp) GET_by_offset(disp, driDispatchRemapTable[Flush_remap_index])
#define SET_Flush(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Flush_remap_index], fn)
#define CALL_AlphaFunc(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLclampf)), driDispatchRemapTable[AlphaFunc_remap_index], parameters)
#define GET_AlphaFunc(disp) GET_by_offset(disp, driDispatchRemapTable[AlphaFunc_remap_index])
#define SET_AlphaFunc(disp, fn) SET_by_offset(disp, driDispatchRemapTable[AlphaFunc_remap_index], fn)
#define CALL_BlendFunc(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum)), driDispatchRemapTable[BlendFunc_remap_index], parameters)
#define GET_BlendFunc(disp) GET_by_offset(disp, driDispatchRemapTable[BlendFunc_remap_index])
#define SET_BlendFunc(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BlendFunc_remap_index], fn)
#define CALL_LogicOp(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[LogicOp_remap_index], parameters)
#define GET_LogicOp(disp) GET_by_offset(disp, driDispatchRemapTable[LogicOp_remap_index])
#define SET_LogicOp(disp, fn) SET_by_offset(disp, driDispatchRemapTable[LogicOp_remap_index], fn)
#define CALL_StencilFunc(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLuint)), driDispatchRemapTable[StencilFunc_remap_index], parameters)
#define GET_StencilFunc(disp) GET_by_offset(disp, driDispatchRemapTable[StencilFunc_remap_index])
#define SET_StencilFunc(disp, fn) SET_by_offset(disp, driDispatchRemapTable[StencilFunc_remap_index], fn)
#define CALL_StencilOp(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum)), driDispatchRemapTable[StencilOp_remap_index], parameters)
#define GET_StencilOp(disp) GET_by_offset(disp, driDispatchRemapTable[StencilOp_remap_index])
#define SET_StencilOp(disp, fn) SET_by_offset(disp, driDispatchRemapTable[StencilOp_remap_index], fn)
#define CALL_DepthFunc(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[DepthFunc_remap_index], parameters)
#define GET_DepthFunc(disp) GET_by_offset(disp, driDispatchRemapTable[DepthFunc_remap_index])
#define SET_DepthFunc(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DepthFunc_remap_index], fn)
#define CALL_PixelStorei(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint)), driDispatchRemapTable[PixelStorei_remap_index], parameters)
#define GET_PixelStorei(disp) GET_by_offset(disp, driDispatchRemapTable[PixelStorei_remap_index])
#define SET_PixelStorei(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PixelStorei_remap_index], fn)
#define CALL_ReadPixels(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid *)), driDispatchRemapTable[ReadPixels_remap_index], parameters)
#define GET_ReadPixels(disp) GET_by_offset(disp, driDispatchRemapTable[ReadPixels_remap_index])
#define SET_ReadPixels(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ReadPixels_remap_index], fn)
#define CALL_GetBooleanv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLboolean *)), driDispatchRemapTable[GetBooleanv_remap_index], parameters)
#define GET_GetBooleanv(disp) GET_by_offset(disp, driDispatchRemapTable[GetBooleanv_remap_index])
#define SET_GetBooleanv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetBooleanv_remap_index], fn)
#define CALL_GetError(disp, parameters) CALL_by_offset(disp, (GLenum (GLAPIENTRYP)(void)), driDispatchRemapTable[GetError_remap_index], parameters)
#define GET_GetError(disp) GET_by_offset(disp, driDispatchRemapTable[GetError_remap_index])
#define SET_GetError(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetError_remap_index], fn)
#define CALL_GetFloatv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat *)), driDispatchRemapTable[GetFloatv_remap_index], parameters)
#define GET_GetFloatv(disp) GET_by_offset(disp, driDispatchRemapTable[GetFloatv_remap_index])
#define SET_GetFloatv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetFloatv_remap_index], fn)
#define CALL_GetIntegerv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint *)), driDispatchRemapTable[GetIntegerv_remap_index], parameters)
#define GET_GetIntegerv(disp) GET_by_offset(disp, driDispatchRemapTable[GetIntegerv_remap_index])
#define SET_GetIntegerv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetIntegerv_remap_index], fn)
#define CALL_GetLightfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), driDispatchRemapTable[GetLightfv_remap_index], parameters)
#define GET_GetLightfv(disp) GET_by_offset(disp, driDispatchRemapTable[GetLightfv_remap_index])
#define SET_GetLightfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetLightfv_remap_index], fn)
#define CALL_GetMaterialfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), driDispatchRemapTable[GetMaterialfv_remap_index], parameters)
#define GET_GetMaterialfv(disp) GET_by_offset(disp, driDispatchRemapTable[GetMaterialfv_remap_index])
#define SET_GetMaterialfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetMaterialfv_remap_index], fn)
#define CALL_GetString(disp, parameters) CALL_by_offset(disp, (const GLubyte * (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[GetString_remap_index], parameters)
#define GET_GetString(disp) GET_by_offset(disp, driDispatchRemapTable[GetString_remap_index])
#define SET_GetString(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetString_remap_index], fn)
#define CALL_GetTexEnvfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), driDispatchRemapTable[GetTexEnvfv_remap_index], parameters)
#define GET_GetTexEnvfv(disp) GET_by_offset(disp, driDispatchRemapTable[GetTexEnvfv_remap_index])
#define SET_GetTexEnvfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetTexEnvfv_remap_index], fn)
#define CALL_GetTexEnviv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), driDispatchRemapTable[GetTexEnviv_remap_index], parameters)
#define GET_GetTexEnviv(disp) GET_by_offset(disp, driDispatchRemapTable[GetTexEnviv_remap_index])
#define SET_GetTexEnviv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetTexEnviv_remap_index], fn)
#define CALL_GetTexGenfvOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), driDispatchRemapTable[GetTexGenfvOES_remap_index], parameters)
#define GET_GetTexGenfvOES(disp) GET_by_offset(disp, driDispatchRemapTable[GetTexGenfvOES_remap_index])
#define SET_GetTexGenfvOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetTexGenfvOES_remap_index], fn)
#define CALL_GetTexGenivOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), driDispatchRemapTable[GetTexGenivOES_remap_index], parameters)
#define GET_GetTexGenivOES(disp) GET_by_offset(disp, driDispatchRemapTable[GetTexGenivOES_remap_index])
#define SET_GetTexGenivOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetTexGenivOES_remap_index], fn)
#define CALL_GetTexParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), driDispatchRemapTable[GetTexParameterfv_remap_index], parameters)
#define GET_GetTexParameterfv(disp) GET_by_offset(disp, driDispatchRemapTable[GetTexParameterfv_remap_index])
#define SET_GetTexParameterfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetTexParameterfv_remap_index], fn)
#define CALL_GetTexParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), driDispatchRemapTable[GetTexParameteriv_remap_index], parameters)
#define GET_GetTexParameteriv(disp) GET_by_offset(disp, driDispatchRemapTable[GetTexParameteriv_remap_index])
#define SET_GetTexParameteriv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetTexParameteriv_remap_index], fn)
#define CALL_IsEnabled(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[IsEnabled_remap_index], parameters)
#define GET_IsEnabled(disp) GET_by_offset(disp, driDispatchRemapTable[IsEnabled_remap_index])
#define SET_IsEnabled(disp, fn) SET_by_offset(disp, driDispatchRemapTable[IsEnabled_remap_index], fn)
#define CALL_LoadIdentity(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), driDispatchRemapTable[LoadIdentity_remap_index], parameters)
#define GET_LoadIdentity(disp) GET_by_offset(disp, driDispatchRemapTable[LoadIdentity_remap_index])
#define SET_LoadIdentity(disp, fn) SET_by_offset(disp, driDispatchRemapTable[LoadIdentity_remap_index], fn)
#define CALL_LoadMatrixf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), driDispatchRemapTable[LoadMatrixf_remap_index], parameters)
#define GET_LoadMatrixf(disp) GET_by_offset(disp, driDispatchRemapTable[LoadMatrixf_remap_index])
#define SET_LoadMatrixf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[LoadMatrixf_remap_index], fn)
#define CALL_MatrixMode(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[MatrixMode_remap_index], parameters)
#define GET_MatrixMode(disp) GET_by_offset(disp, driDispatchRemapTable[MatrixMode_remap_index])
#define SET_MatrixMode(disp, fn) SET_by_offset(disp, driDispatchRemapTable[MatrixMode_remap_index], fn)
#define CALL_MultMatrixf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), driDispatchRemapTable[MultMatrixf_remap_index], parameters)
#define GET_MultMatrixf(disp) GET_by_offset(disp, driDispatchRemapTable[MultMatrixf_remap_index])
#define SET_MultMatrixf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[MultMatrixf_remap_index], fn)
#define CALL_PopMatrix(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), driDispatchRemapTable[PopMatrix_remap_index], parameters)
#define GET_PopMatrix(disp) GET_by_offset(disp, driDispatchRemapTable[PopMatrix_remap_index])
#define SET_PopMatrix(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PopMatrix_remap_index], fn)
#define CALL_PushMatrix(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), driDispatchRemapTable[PushMatrix_remap_index], parameters)
#define GET_PushMatrix(disp) GET_by_offset(disp, driDispatchRemapTable[PushMatrix_remap_index])
#define SET_PushMatrix(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PushMatrix_remap_index], fn)
#define CALL_Rotatef(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat)), driDispatchRemapTable[Rotatef_remap_index], parameters)
#define GET_Rotatef(disp) GET_by_offset(disp, driDispatchRemapTable[Rotatef_remap_index])
#define SET_Rotatef(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Rotatef_remap_index], fn)
#define CALL_Scalef(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat)), driDispatchRemapTable[Scalef_remap_index], parameters)
#define GET_Scalef(disp) GET_by_offset(disp, driDispatchRemapTable[Scalef_remap_index])
#define SET_Scalef(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Scalef_remap_index], fn)
#define CALL_Translatef(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat)), driDispatchRemapTable[Translatef_remap_index], parameters)
#define GET_Translatef(disp) GET_by_offset(disp, driDispatchRemapTable[Translatef_remap_index])
#define SET_Translatef(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Translatef_remap_index], fn)
#define CALL_Viewport(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLsizei, GLsizei)), driDispatchRemapTable[Viewport_remap_index], parameters)
#define GET_Viewport(disp) GET_by_offset(disp, driDispatchRemapTable[Viewport_remap_index])
#define SET_Viewport(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Viewport_remap_index], fn)
#define CALL_BindTexture(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint)), driDispatchRemapTable[BindTexture_remap_index], parameters)
#define GET_BindTexture(disp) GET_by_offset(disp, driDispatchRemapTable[BindTexture_remap_index])
#define SET_BindTexture(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BindTexture_remap_index], fn)
#define CALL_ColorPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLenum, GLsizei, const GLvoid *)), driDispatchRemapTable[ColorPointer_remap_index], parameters)
#define GET_ColorPointer(disp) GET_by_offset(disp, driDispatchRemapTable[ColorPointer_remap_index])
#define SET_ColorPointer(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ColorPointer_remap_index], fn)
#define CALL_DisableClientState(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[DisableClientState_remap_index], parameters)
#define GET_DisableClientState(disp) GET_by_offset(disp, driDispatchRemapTable[DisableClientState_remap_index])
#define SET_DisableClientState(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DisableClientState_remap_index], fn)
#define CALL_DrawArrays(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLsizei)), driDispatchRemapTable[DrawArrays_remap_index], parameters)
#define GET_DrawArrays(disp) GET_by_offset(disp, driDispatchRemapTable[DrawArrays_remap_index])
#define SET_DrawArrays(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DrawArrays_remap_index], fn)
#define CALL_DrawElements(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, GLenum, const GLvoid *)), driDispatchRemapTable[DrawElements_remap_index], parameters)
#define GET_DrawElements(disp) GET_by_offset(disp, driDispatchRemapTable[DrawElements_remap_index])
#define SET_DrawElements(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DrawElements_remap_index], fn)
#define CALL_EnableClientState(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[EnableClientState_remap_index], parameters)
#define GET_EnableClientState(disp) GET_by_offset(disp, driDispatchRemapTable[EnableClientState_remap_index])
#define SET_EnableClientState(disp, fn) SET_by_offset(disp, driDispatchRemapTable[EnableClientState_remap_index], fn)
#define CALL_NormalPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, const GLvoid *)), driDispatchRemapTable[NormalPointer_remap_index], parameters)
#define GET_NormalPointer(disp) GET_by_offset(disp, driDispatchRemapTable[NormalPointer_remap_index])
#define SET_NormalPointer(disp, fn) SET_by_offset(disp, driDispatchRemapTable[NormalPointer_remap_index], fn)
#define CALL_PolygonOffset(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat)), driDispatchRemapTable[PolygonOffset_remap_index], parameters)
#define GET_PolygonOffset(disp) GET_by_offset(disp, driDispatchRemapTable[PolygonOffset_remap_index])
#define SET_PolygonOffset(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PolygonOffset_remap_index], fn)
#define CALL_TexCoordPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLenum, GLsizei, const GLvoid *)), driDispatchRemapTable[TexCoordPointer_remap_index], parameters)
#define GET_TexCoordPointer(disp) GET_by_offset(disp, driDispatchRemapTable[TexCoordPointer_remap_index])
#define SET_TexCoordPointer(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexCoordPointer_remap_index], fn)
#define CALL_VertexPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLenum, GLsizei, const GLvoid *)), driDispatchRemapTable[VertexPointer_remap_index], parameters)
#define GET_VertexPointer(disp) GET_by_offset(disp, driDispatchRemapTable[VertexPointer_remap_index])
#define SET_VertexPointer(disp, fn) SET_by_offset(disp, driDispatchRemapTable[VertexPointer_remap_index], fn)
#define CALL_CopyTexImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint)), driDispatchRemapTable[CopyTexImage2D_remap_index], parameters)
#define GET_CopyTexImage2D(disp) GET_by_offset(disp, driDispatchRemapTable[CopyTexImage2D_remap_index])
#define SET_CopyTexImage2D(disp, fn) SET_by_offset(disp, driDispatchRemapTable[CopyTexImage2D_remap_index], fn)
#define CALL_CopyTexSubImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)), driDispatchRemapTable[CopyTexSubImage2D_remap_index], parameters)
#define GET_CopyTexSubImage2D(disp) GET_by_offset(disp, driDispatchRemapTable[CopyTexSubImage2D_remap_index])
#define SET_CopyTexSubImage2D(disp, fn) SET_by_offset(disp, driDispatchRemapTable[CopyTexSubImage2D_remap_index], fn)
#define CALL_DeleteTextures(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *)), driDispatchRemapTable[DeleteTextures_remap_index], parameters)
#define GET_DeleteTextures(disp) GET_by_offset(disp, driDispatchRemapTable[DeleteTextures_remap_index])
#define SET_DeleteTextures(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DeleteTextures_remap_index], fn)
#define CALL_GenTextures(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), driDispatchRemapTable[GenTextures_remap_index], parameters)
#define GET_GenTextures(disp) GET_by_offset(disp, driDispatchRemapTable[GenTextures_remap_index])
#define SET_GenTextures(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GenTextures_remap_index], fn)
#define CALL_GetPointerv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLvoid **)), driDispatchRemapTable[GetPointerv_remap_index], parameters)
#define GET_GetPointerv(disp) GET_by_offset(disp, driDispatchRemapTable[GetPointerv_remap_index])
#define SET_GetPointerv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetPointerv_remap_index], fn)
#define CALL_IsTexture(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), driDispatchRemapTable[IsTexture_remap_index], parameters)
#define GET_IsTexture(disp) GET_by_offset(disp, driDispatchRemapTable[IsTexture_remap_index])
#define SET_IsTexture(disp, fn) SET_by_offset(disp, driDispatchRemapTable[IsTexture_remap_index], fn)
#define CALL_TexSubImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *)), driDispatchRemapTable[TexSubImage2D_remap_index], parameters)
#define GET_TexSubImage2D(disp) GET_by_offset(disp, driDispatchRemapTable[TexSubImage2D_remap_index])
#define SET_TexSubImage2D(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexSubImage2D_remap_index], fn)
#define CALL_BlendColor(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampf, GLclampf, GLclampf, GLclampf)), driDispatchRemapTable[BlendColor_remap_index], parameters)
#define GET_BlendColor(disp) GET_by_offset(disp, driDispatchRemapTable[BlendColor_remap_index])
#define SET_BlendColor(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BlendColor_remap_index], fn)
#define CALL_BlendEquationOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[BlendEquationOES_remap_index], parameters)
#define GET_BlendEquationOES(disp) GET_by_offset(disp, driDispatchRemapTable[BlendEquationOES_remap_index])
#define SET_BlendEquationOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BlendEquationOES_remap_index], fn)
#define CALL_TexImage3D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid *)), driDispatchRemapTable[TexImage3D_remap_index], parameters)
#define GET_TexImage3D(disp) GET_by_offset(disp, driDispatchRemapTable[TexImage3D_remap_index])
#define SET_TexImage3D(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexImage3D_remap_index], fn)
#define CALL_TexSubImage3D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *)), driDispatchRemapTable[TexSubImage3D_remap_index], parameters)
#define GET_TexSubImage3D(disp) GET_by_offset(disp, driDispatchRemapTable[TexSubImage3D_remap_index])
#define SET_TexSubImage3D(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexSubImage3D_remap_index], fn)
#define CALL_CopyTexSubImage3D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)), driDispatchRemapTable[CopyTexSubImage3D_remap_index], parameters)
#define GET_CopyTexSubImage3D(disp) GET_by_offset(disp, driDispatchRemapTable[CopyTexSubImage3D_remap_index])
#define SET_CopyTexSubImage3D(disp, fn) SET_by_offset(disp, driDispatchRemapTable[CopyTexSubImage3D_remap_index], fn)
#define CALL_ActiveTexture(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[ActiveTexture_remap_index], parameters)
#define GET_ActiveTexture(disp) GET_by_offset(disp, driDispatchRemapTable[ActiveTexture_remap_index])
#define SET_ActiveTexture(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ActiveTexture_remap_index], fn)
#define CALL_ClientActiveTexture(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[ClientActiveTexture_remap_index], parameters)
#define GET_ClientActiveTexture(disp) GET_by_offset(disp, driDispatchRemapTable[ClientActiveTexture_remap_index])
#define SET_ClientActiveTexture(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ClientActiveTexture_remap_index], fn)
#define CALL_MultiTexCoord4f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat, GLfloat, GLfloat, GLfloat)), driDispatchRemapTable[MultiTexCoord4f_remap_index], parameters)
#define GET_MultiTexCoord4f(disp) GET_by_offset(disp, driDispatchRemapTable[MultiTexCoord4f_remap_index])
#define SET_MultiTexCoord4f(disp, fn) SET_by_offset(disp, driDispatchRemapTable[MultiTexCoord4f_remap_index], fn)
#define CALL_BlendEquationSeparateOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum)), driDispatchRemapTable[BlendEquationSeparateOES_remap_index], parameters)
#define GET_BlendEquationSeparateOES(disp) GET_by_offset(disp, driDispatchRemapTable[BlendEquationSeparateOES_remap_index])
#define SET_BlendEquationSeparateOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BlendEquationSeparateOES_remap_index], fn)
#define CALL_BlendFuncSeparateOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLenum)), driDispatchRemapTable[BlendFuncSeparateOES_remap_index], parameters)
#define GET_BlendFuncSeparateOES(disp) GET_by_offset(disp, driDispatchRemapTable[BlendFuncSeparateOES_remap_index])
#define SET_BlendFuncSeparateOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BlendFuncSeparateOES_remap_index], fn)
#define CALL_DrawTexfOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat)), driDispatchRemapTable[DrawTexfOES_remap_index], parameters)
#define GET_DrawTexfOES(disp) GET_by_offset(disp, driDispatchRemapTable[DrawTexfOES_remap_index])
#define SET_DrawTexfOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DrawTexfOES_remap_index], fn)
#define CALL_DrawTexfvOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), driDispatchRemapTable[DrawTexfvOES_remap_index], parameters)
#define GET_DrawTexfvOES(disp) GET_by_offset(disp, driDispatchRemapTable[DrawTexfvOES_remap_index])
#define SET_DrawTexfvOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DrawTexfvOES_remap_index], fn)
#define CALL_DrawTexiOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint, GLint, GLint)), driDispatchRemapTable[DrawTexiOES_remap_index], parameters)
#define GET_DrawTexiOES(disp) GET_by_offset(disp, driDispatchRemapTable[DrawTexiOES_remap_index])
#define SET_DrawTexiOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DrawTexiOES_remap_index], fn)
#define CALL_DrawTexivOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), driDispatchRemapTable[DrawTexivOES_remap_index], parameters)
#define GET_DrawTexivOES(disp) GET_by_offset(disp, driDispatchRemapTable[DrawTexivOES_remap_index])
#define SET_DrawTexivOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DrawTexivOES_remap_index], fn)
#define CALL_DrawTexsOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort, GLshort, GLshort)), driDispatchRemapTable[DrawTexsOES_remap_index], parameters)
#define GET_DrawTexsOES(disp) GET_by_offset(disp, driDispatchRemapTable[DrawTexsOES_remap_index])
#define SET_DrawTexsOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DrawTexsOES_remap_index], fn)
#define CALL_DrawTexsvOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), driDispatchRemapTable[DrawTexsvOES_remap_index], parameters)
#define GET_DrawTexsvOES(disp) GET_by_offset(disp, driDispatchRemapTable[DrawTexsvOES_remap_index])
#define SET_DrawTexsvOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DrawTexsvOES_remap_index], fn)
#define CALL_DrawTexxOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed, GLfixed, GLfixed, GLfixed, GLfixed)), driDispatchRemapTable[DrawTexxOES_remap_index], parameters)
#define GET_DrawTexxOES(disp) GET_by_offset(disp, driDispatchRemapTable[DrawTexxOES_remap_index])
#define SET_DrawTexxOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DrawTexxOES_remap_index], fn)
#define CALL_DrawTexxvOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfixed *)), driDispatchRemapTable[DrawTexxvOES_remap_index], parameters)
#define GET_DrawTexxvOES(disp) GET_by_offset(disp, driDispatchRemapTable[DrawTexxvOES_remap_index])
#define SET_DrawTexxvOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DrawTexxvOES_remap_index], fn)
#define CALL_BindFramebufferOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint)), driDispatchRemapTable[BindFramebufferOES_remap_index], parameters)
#define GET_BindFramebufferOES(disp) GET_by_offset(disp, driDispatchRemapTable[BindFramebufferOES_remap_index])
#define SET_BindFramebufferOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BindFramebufferOES_remap_index], fn)
#define CALL_BindRenderbufferOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint)), driDispatchRemapTable[BindRenderbufferOES_remap_index], parameters)
#define GET_BindRenderbufferOES(disp) GET_by_offset(disp, driDispatchRemapTable[BindRenderbufferOES_remap_index])
#define SET_BindRenderbufferOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BindRenderbufferOES_remap_index], fn)
#define CALL_CheckFramebufferStatusOES(disp, parameters) CALL_by_offset(disp, (GLenum (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[CheckFramebufferStatusOES_remap_index], parameters)
#define GET_CheckFramebufferStatusOES(disp) GET_by_offset(disp, driDispatchRemapTable[CheckFramebufferStatusOES_remap_index])
#define SET_CheckFramebufferStatusOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[CheckFramebufferStatusOES_remap_index], fn)
#define CALL_DeleteFramebuffersOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *)), driDispatchRemapTable[DeleteFramebuffersOES_remap_index], parameters)
#define GET_DeleteFramebuffersOES(disp) GET_by_offset(disp, driDispatchRemapTable[DeleteFramebuffersOES_remap_index])
#define SET_DeleteFramebuffersOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DeleteFramebuffersOES_remap_index], fn)
#define CALL_DeleteRenderbuffersOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *)), driDispatchRemapTable[DeleteRenderbuffersOES_remap_index], parameters)
#define GET_DeleteRenderbuffersOES(disp) GET_by_offset(disp, driDispatchRemapTable[DeleteRenderbuffersOES_remap_index])
#define SET_DeleteRenderbuffersOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DeleteRenderbuffersOES_remap_index], fn)
#define CALL_FramebufferRenderbufferOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLuint)), driDispatchRemapTable[FramebufferRenderbufferOES_remap_index], parameters)
#define GET_FramebufferRenderbufferOES(disp) GET_by_offset(disp, driDispatchRemapTable[FramebufferRenderbufferOES_remap_index])
#define SET_FramebufferRenderbufferOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[FramebufferRenderbufferOES_remap_index], fn)
#define CALL_FramebufferTexture2DOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLuint, GLint)), driDispatchRemapTable[FramebufferTexture2DOES_remap_index], parameters)
#define GET_FramebufferTexture2DOES(disp) GET_by_offset(disp, driDispatchRemapTable[FramebufferTexture2DOES_remap_index])
#define SET_FramebufferTexture2DOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[FramebufferTexture2DOES_remap_index], fn)
#define CALL_GenFramebuffersOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), driDispatchRemapTable[GenFramebuffersOES_remap_index], parameters)
#define GET_GenFramebuffersOES(disp) GET_by_offset(disp, driDispatchRemapTable[GenFramebuffersOES_remap_index])
#define SET_GenFramebuffersOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GenFramebuffersOES_remap_index], fn)
#define CALL_GenRenderbuffersOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), driDispatchRemapTable[GenRenderbuffersOES_remap_index], parameters)
#define GET_GenRenderbuffersOES(disp) GET_by_offset(disp, driDispatchRemapTable[GenRenderbuffersOES_remap_index])
#define SET_GenRenderbuffersOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GenRenderbuffersOES_remap_index], fn)
#define CALL_GenerateMipmapOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[GenerateMipmapOES_remap_index], parameters)
#define GET_GenerateMipmapOES(disp) GET_by_offset(disp, driDispatchRemapTable[GenerateMipmapOES_remap_index])
#define SET_GenerateMipmapOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GenerateMipmapOES_remap_index], fn)
#define CALL_GetFramebufferAttachmentParameterivOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLint *)), driDispatchRemapTable[GetFramebufferAttachmentParameterivOES_remap_index], parameters)
#define GET_GetFramebufferAttachmentParameterivOES(disp) GET_by_offset(disp, driDispatchRemapTable[GetFramebufferAttachmentParameterivOES_remap_index])
#define SET_GetFramebufferAttachmentParameterivOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetFramebufferAttachmentParameterivOES_remap_index], fn)
#define CALL_GetRenderbufferParameterivOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), driDispatchRemapTable[GetRenderbufferParameterivOES_remap_index], parameters)
#define GET_GetRenderbufferParameterivOES(disp) GET_by_offset(disp, driDispatchRemapTable[GetRenderbufferParameterivOES_remap_index])
#define SET_GetRenderbufferParameterivOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetRenderbufferParameterivOES_remap_index], fn)
#define CALL_IsFramebufferOES(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), driDispatchRemapTable[IsFramebufferOES_remap_index], parameters)
#define GET_IsFramebufferOES(disp) GET_by_offset(disp, driDispatchRemapTable[IsFramebufferOES_remap_index])
#define SET_IsFramebufferOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[IsFramebufferOES_remap_index], fn)
#define CALL_IsRenderbufferOES(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), driDispatchRemapTable[IsRenderbufferOES_remap_index], parameters)
#define GET_IsRenderbufferOES(disp) GET_by_offset(disp, driDispatchRemapTable[IsRenderbufferOES_remap_index])
#define SET_IsRenderbufferOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[IsRenderbufferOES_remap_index], fn)
#define CALL_RenderbufferStorageOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLsizei, GLsizei)), driDispatchRemapTable[RenderbufferStorageOES_remap_index], parameters)
#define GET_RenderbufferStorageOES(disp) GET_by_offset(disp, driDispatchRemapTable[RenderbufferStorageOES_remap_index])
#define SET_RenderbufferStorageOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[RenderbufferStorageOES_remap_index], fn)
#define CALL_PointSizePointerOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, const GLvoid *)), driDispatchRemapTable[PointSizePointerOES_remap_index], parameters)
#define GET_PointSizePointerOES(disp) GET_by_offset(disp, driDispatchRemapTable[PointSizePointerOES_remap_index])
#define SET_PointSizePointerOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PointSizePointerOES_remap_index], fn)
#define CALL_QueryMatrixxOES(disp, parameters) CALL_by_offset(disp, (GLbitfield (GLAPIENTRYP)(GLfixed *, GLint *)), driDispatchRemapTable[QueryMatrixxOES_remap_index], parameters)
#define GET_QueryMatrixxOES(disp) GET_by_offset(disp, driDispatchRemapTable[QueryMatrixxOES_remap_index])
#define SET_QueryMatrixxOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[QueryMatrixxOES_remap_index], fn)
#define CALL_GetTexGenxvOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfixed *)), driDispatchRemapTable[GetTexGenxvOES_remap_index], parameters)
#define GET_GetTexGenxvOES(disp) GET_by_offset(disp, driDispatchRemapTable[GetTexGenxvOES_remap_index])
#define SET_GetTexGenxvOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetTexGenxvOES_remap_index], fn)
#define CALL_TexGenxOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint)), driDispatchRemapTable[TexGenxOES_remap_index], parameters)
#define GET_TexGenxOES(disp) GET_by_offset(disp, driDispatchRemapTable[TexGenxOES_remap_index])
#define SET_TexGenxOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexGenxOES_remap_index], fn)
#define CALL_TexGenxvOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfixed *)), driDispatchRemapTable[TexGenxvOES_remap_index], parameters)
#define GET_TexGenxvOES(disp) GET_by_offset(disp, driDispatchRemapTable[TexGenxvOES_remap_index])
#define SET_TexGenxvOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexGenxvOES_remap_index], fn)
#define CALL_EGLImageTargetRenderbufferStorageOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLeglImageOES)), driDispatchRemapTable[EGLImageTargetRenderbufferStorageOES_remap_index], parameters)
#define GET_EGLImageTargetRenderbufferStorageOES(disp) GET_by_offset(disp, driDispatchRemapTable[EGLImageTargetRenderbufferStorageOES_remap_index])
#define SET_EGLImageTargetRenderbufferStorageOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[EGLImageTargetRenderbufferStorageOES_remap_index], fn)
#define CALL_EGLImageTargetTexture2DOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLeglImageOES)), driDispatchRemapTable[EGLImageTargetTexture2DOES_remap_index], parameters)
#define GET_EGLImageTargetTexture2DOES(disp) GET_by_offset(disp, driDispatchRemapTable[EGLImageTargetTexture2DOES_remap_index])
#define SET_EGLImageTargetTexture2DOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[EGLImageTargetTexture2DOES_remap_index], fn)
#define CALL_GetBufferPointervOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLvoid **)), driDispatchRemapTable[GetBufferPointervOES_remap_index], parameters)
#define GET_GetBufferPointervOES(disp) GET_by_offset(disp, driDispatchRemapTable[GetBufferPointervOES_remap_index])
#define SET_GetBufferPointervOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetBufferPointervOES_remap_index], fn)
#define CALL_MapBufferOES(disp, parameters) CALL_by_offset(disp, (GLvoid * (GLAPIENTRYP)(GLenum, GLenum)), driDispatchRemapTable[MapBufferOES_remap_index], parameters)
#define GET_MapBufferOES(disp) GET_by_offset(disp, driDispatchRemapTable[MapBufferOES_remap_index])
#define SET_MapBufferOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[MapBufferOES_remap_index], fn)
#define CALL_UnmapBufferOES(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLenum)), driDispatchRemapTable[UnmapBufferOES_remap_index], parameters)
#define GET_UnmapBufferOES(disp) GET_by_offset(disp, driDispatchRemapTable[UnmapBufferOES_remap_index])
#define SET_UnmapBufferOES(disp, fn) SET_by_offset(disp, driDispatchRemapTable[UnmapBufferOES_remap_index], fn)
#define CALL_BindVertexArrayAPPLE(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), driDispatchRemapTable[BindVertexArrayAPPLE_remap_index], parameters)
#define GET_BindVertexArrayAPPLE(disp) GET_by_offset(disp, driDispatchRemapTable[BindVertexArrayAPPLE_remap_index])
#define SET_BindVertexArrayAPPLE(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BindVertexArrayAPPLE_remap_index], fn)
#define CALL_DeleteVertexArraysAPPLE(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *)), driDispatchRemapTable[DeleteVertexArraysAPPLE_remap_index], parameters)
#define GET_DeleteVertexArraysAPPLE(disp) GET_by_offset(disp, driDispatchRemapTable[DeleteVertexArraysAPPLE_remap_index])
#define SET_DeleteVertexArraysAPPLE(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DeleteVertexArraysAPPLE_remap_index], fn)
#define CALL_GenVertexArraysAPPLE(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), driDispatchRemapTable[GenVertexArraysAPPLE_remap_index], parameters)
#define GET_GenVertexArraysAPPLE(disp) GET_by_offset(disp, driDispatchRemapTable[GenVertexArraysAPPLE_remap_index])
#define SET_GenVertexArraysAPPLE(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GenVertexArraysAPPLE_remap_index], fn)
#define CALL_IsVertexArrayAPPLE(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), driDispatchRemapTable[IsVertexArrayAPPLE_remap_index], parameters)
#define GET_IsVertexArrayAPPLE(disp) GET_by_offset(disp, driDispatchRemapTable[IsVertexArrayAPPLE_remap_index])
#define SET_IsVertexArrayAPPLE(disp, fn) SET_by_offset(disp, driDispatchRemapTable[IsVertexArrayAPPLE_remap_index], fn)
#define CALL_CompressedTexImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const GLvoid *)), driDispatchRemapTable[CompressedTexImage2D_remap_index], parameters)
#define GET_CompressedTexImage2D(disp) GET_by_offset(disp, driDispatchRemapTable[CompressedTexImage2D_remap_index])
#define SET_CompressedTexImage2D(disp, fn) SET_by_offset(disp, driDispatchRemapTable[CompressedTexImage2D_remap_index], fn)
#define CALL_CompressedTexSubImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid *)), driDispatchRemapTable[CompressedTexSubImage2D_remap_index], parameters)
#define GET_CompressedTexSubImage2D(disp) GET_by_offset(disp, driDispatchRemapTable[CompressedTexSubImage2D_remap_index])
#define SET_CompressedTexSubImage2D(disp, fn) SET_by_offset(disp, driDispatchRemapTable[CompressedTexSubImage2D_remap_index], fn)
#define CALL_SampleCoverage(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampf, GLboolean)), driDispatchRemapTable[SampleCoverage_remap_index], parameters)
#define GET_SampleCoverage(disp) GET_by_offset(disp, driDispatchRemapTable[SampleCoverage_remap_index])
#define SET_SampleCoverage(disp, fn) SET_by_offset(disp, driDispatchRemapTable[SampleCoverage_remap_index], fn)
#define CALL_BindBuffer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint)), driDispatchRemapTable[BindBuffer_remap_index], parameters)
#define GET_BindBuffer(disp) GET_by_offset(disp, driDispatchRemapTable[BindBuffer_remap_index])
#define SET_BindBuffer(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BindBuffer_remap_index], fn)
#define CALL_BufferData(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizeiptr, const GLvoid *, GLenum)), driDispatchRemapTable[BufferData_remap_index], parameters)
#define GET_BufferData(disp) GET_by_offset(disp, driDispatchRemapTable[BufferData_remap_index])
#define SET_BufferData(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BufferData_remap_index], fn)
#define CALL_BufferSubData(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLintptr, GLsizeiptr, const GLvoid *)), driDispatchRemapTable[BufferSubData_remap_index], parameters)
#define GET_BufferSubData(disp) GET_by_offset(disp, driDispatchRemapTable[BufferSubData_remap_index])
#define SET_BufferSubData(disp, fn) SET_by_offset(disp, driDispatchRemapTable[BufferSubData_remap_index], fn)
#define CALL_DeleteBuffers(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *)), driDispatchRemapTable[DeleteBuffers_remap_index], parameters)
#define GET_DeleteBuffers(disp) GET_by_offset(disp, driDispatchRemapTable[DeleteBuffers_remap_index])
#define SET_DeleteBuffers(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DeleteBuffers_remap_index], fn)
#define CALL_GenBuffers(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), driDispatchRemapTable[GenBuffers_remap_index], parameters)
#define GET_GenBuffers(disp) GET_by_offset(disp, driDispatchRemapTable[GenBuffers_remap_index])
#define SET_GenBuffers(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GenBuffers_remap_index], fn)
#define CALL_GetBufferParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), driDispatchRemapTable[GetBufferParameteriv_remap_index], parameters)
#define GET_GetBufferParameteriv(disp) GET_by_offset(disp, driDispatchRemapTable[GetBufferParameteriv_remap_index])
#define SET_GetBufferParameteriv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetBufferParameteriv_remap_index], fn)
#define CALL_IsBuffer(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), driDispatchRemapTable[IsBuffer_remap_index], parameters)
#define GET_IsBuffer(disp) GET_by_offset(disp, driDispatchRemapTable[IsBuffer_remap_index])
#define SET_IsBuffer(disp, fn) SET_by_offset(disp, driDispatchRemapTable[IsBuffer_remap_index], fn)
#define CALL_AlphaFuncx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLclampx)), driDispatchRemapTable[AlphaFuncx_remap_index], parameters)
#define GET_AlphaFuncx(disp) GET_by_offset(disp, driDispatchRemapTable[AlphaFuncx_remap_index])
#define SET_AlphaFuncx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[AlphaFuncx_remap_index], fn)
#define CALL_ClearColorx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampx, GLclampx, GLclampx, GLclampx)), driDispatchRemapTable[ClearColorx_remap_index], parameters)
#define GET_ClearColorx(disp) GET_by_offset(disp, driDispatchRemapTable[ClearColorx_remap_index])
#define SET_ClearColorx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ClearColorx_remap_index], fn)
#define CALL_ClearDepthf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampf)), driDispatchRemapTable[ClearDepthf_remap_index], parameters)
#define GET_ClearDepthf(disp) GET_by_offset(disp, driDispatchRemapTable[ClearDepthf_remap_index])
#define SET_ClearDepthf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ClearDepthf_remap_index], fn)
#define CALL_ClearDepthx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampx)), driDispatchRemapTable[ClearDepthx_remap_index], parameters)
#define GET_ClearDepthx(disp) GET_by_offset(disp, driDispatchRemapTable[ClearDepthx_remap_index])
#define SET_ClearDepthx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ClearDepthx_remap_index], fn)
#define CALL_Color4x(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed, GLfixed, GLfixed, GLfixed)), driDispatchRemapTable[Color4x_remap_index], parameters)
#define GET_Color4x(disp) GET_by_offset(disp, driDispatchRemapTable[Color4x_remap_index])
#define SET_Color4x(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Color4x_remap_index], fn)
#define CALL_DepthRangef(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampf, GLclampf)), driDispatchRemapTable[DepthRangef_remap_index], parameters)
#define GET_DepthRangef(disp) GET_by_offset(disp, driDispatchRemapTable[DepthRangef_remap_index])
#define SET_DepthRangef(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DepthRangef_remap_index], fn)
#define CALL_DepthRangex(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampx, GLclampx)), driDispatchRemapTable[DepthRangex_remap_index], parameters)
#define GET_DepthRangex(disp) GET_by_offset(disp, driDispatchRemapTable[DepthRangex_remap_index])
#define SET_DepthRangex(disp, fn) SET_by_offset(disp, driDispatchRemapTable[DepthRangex_remap_index], fn)
#define CALL_Fogx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfixed)), driDispatchRemapTable[Fogx_remap_index], parameters)
#define GET_Fogx(disp) GET_by_offset(disp, driDispatchRemapTable[Fogx_remap_index])
#define SET_Fogx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Fogx_remap_index], fn)
#define CALL_Fogxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfixed *)), driDispatchRemapTable[Fogxv_remap_index], parameters)
#define GET_Fogxv(disp) GET_by_offset(disp, driDispatchRemapTable[Fogxv_remap_index])
#define SET_Fogxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Fogxv_remap_index], fn)
#define CALL_Frustumf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat)), driDispatchRemapTable[Frustumf_remap_index], parameters)
#define GET_Frustumf(disp) GET_by_offset(disp, driDispatchRemapTable[Frustumf_remap_index])
#define SET_Frustumf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Frustumf_remap_index], fn)
#define CALL_Frustumx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed, GLfixed, GLfixed, GLfixed, GLfixed, GLfixed)), driDispatchRemapTable[Frustumx_remap_index], parameters)
#define GET_Frustumx(disp) GET_by_offset(disp, driDispatchRemapTable[Frustumx_remap_index])
#define SET_Frustumx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Frustumx_remap_index], fn)
#define CALL_LightModelx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfixed)), driDispatchRemapTable[LightModelx_remap_index], parameters)
#define GET_LightModelx(disp) GET_by_offset(disp, driDispatchRemapTable[LightModelx_remap_index])
#define SET_LightModelx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[LightModelx_remap_index], fn)
#define CALL_LightModelxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfixed *)), driDispatchRemapTable[LightModelxv_remap_index], parameters)
#define GET_LightModelxv(disp) GET_by_offset(disp, driDispatchRemapTable[LightModelxv_remap_index])
#define SET_LightModelxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[LightModelxv_remap_index], fn)
#define CALL_Lightx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfixed)), driDispatchRemapTable[Lightx_remap_index], parameters)
#define GET_Lightx(disp) GET_by_offset(disp, driDispatchRemapTable[Lightx_remap_index])
#define SET_Lightx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Lightx_remap_index], fn)
#define CALL_Lightxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfixed *)), driDispatchRemapTable[Lightxv_remap_index], parameters)
#define GET_Lightxv(disp) GET_by_offset(disp, driDispatchRemapTable[Lightxv_remap_index])
#define SET_Lightxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Lightxv_remap_index], fn)
#define CALL_LineWidthx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed)), driDispatchRemapTable[LineWidthx_remap_index], parameters)
#define GET_LineWidthx(disp) GET_by_offset(disp, driDispatchRemapTable[LineWidthx_remap_index])
#define SET_LineWidthx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[LineWidthx_remap_index], fn)
#define CALL_LoadMatrixx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfixed *)), driDispatchRemapTable[LoadMatrixx_remap_index], parameters)
#define GET_LoadMatrixx(disp) GET_by_offset(disp, driDispatchRemapTable[LoadMatrixx_remap_index])
#define SET_LoadMatrixx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[LoadMatrixx_remap_index], fn)
#define CALL_Materialx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfixed)), driDispatchRemapTable[Materialx_remap_index], parameters)
#define GET_Materialx(disp) GET_by_offset(disp, driDispatchRemapTable[Materialx_remap_index])
#define SET_Materialx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Materialx_remap_index], fn)
#define CALL_Materialxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfixed *)), driDispatchRemapTable[Materialxv_remap_index], parameters)
#define GET_Materialxv(disp) GET_by_offset(disp, driDispatchRemapTable[Materialxv_remap_index])
#define SET_Materialxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Materialxv_remap_index], fn)
#define CALL_MultMatrixx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfixed *)), driDispatchRemapTable[MultMatrixx_remap_index], parameters)
#define GET_MultMatrixx(disp) GET_by_offset(disp, driDispatchRemapTable[MultMatrixx_remap_index])
#define SET_MultMatrixx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[MultMatrixx_remap_index], fn)
#define CALL_MultiTexCoord4x(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfixed, GLfixed, GLfixed, GLfixed)), driDispatchRemapTable[MultiTexCoord4x_remap_index], parameters)
#define GET_MultiTexCoord4x(disp) GET_by_offset(disp, driDispatchRemapTable[MultiTexCoord4x_remap_index])
#define SET_MultiTexCoord4x(disp, fn) SET_by_offset(disp, driDispatchRemapTable[MultiTexCoord4x_remap_index], fn)
#define CALL_Normal3x(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed, GLfixed, GLfixed)), driDispatchRemapTable[Normal3x_remap_index], parameters)
#define GET_Normal3x(disp) GET_by_offset(disp, driDispatchRemapTable[Normal3x_remap_index])
#define SET_Normal3x(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Normal3x_remap_index], fn)
#define CALL_Orthof(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat)), driDispatchRemapTable[Orthof_remap_index], parameters)
#define GET_Orthof(disp) GET_by_offset(disp, driDispatchRemapTable[Orthof_remap_index])
#define SET_Orthof(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Orthof_remap_index], fn)
#define CALL_Orthox(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed, GLfixed, GLfixed, GLfixed, GLfixed, GLfixed)), driDispatchRemapTable[Orthox_remap_index], parameters)
#define GET_Orthox(disp) GET_by_offset(disp, driDispatchRemapTable[Orthox_remap_index])
#define SET_Orthox(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Orthox_remap_index], fn)
#define CALL_PointSizex(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed)), driDispatchRemapTable[PointSizex_remap_index], parameters)
#define GET_PointSizex(disp) GET_by_offset(disp, driDispatchRemapTable[PointSizex_remap_index])
#define SET_PointSizex(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PointSizex_remap_index], fn)
#define CALL_PolygonOffsetx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed, GLfixed)), driDispatchRemapTable[PolygonOffsetx_remap_index], parameters)
#define GET_PolygonOffsetx(disp) GET_by_offset(disp, driDispatchRemapTable[PolygonOffsetx_remap_index])
#define SET_PolygonOffsetx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PolygonOffsetx_remap_index], fn)
#define CALL_Rotatex(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed, GLfixed, GLfixed, GLfixed)), driDispatchRemapTable[Rotatex_remap_index], parameters)
#define GET_Rotatex(disp) GET_by_offset(disp, driDispatchRemapTable[Rotatex_remap_index])
#define SET_Rotatex(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Rotatex_remap_index], fn)
#define CALL_SampleCoveragex(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampx, GLboolean)), driDispatchRemapTable[SampleCoveragex_remap_index], parameters)
#define GET_SampleCoveragex(disp) GET_by_offset(disp, driDispatchRemapTable[SampleCoveragex_remap_index])
#define SET_SampleCoveragex(disp, fn) SET_by_offset(disp, driDispatchRemapTable[SampleCoveragex_remap_index], fn)
#define CALL_Scalex(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed, GLfixed, GLfixed)), driDispatchRemapTable[Scalex_remap_index], parameters)
#define GET_Scalex(disp) GET_by_offset(disp, driDispatchRemapTable[Scalex_remap_index])
#define SET_Scalex(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Scalex_remap_index], fn)
#define CALL_TexEnvx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfixed)), driDispatchRemapTable[TexEnvx_remap_index], parameters)
#define GET_TexEnvx(disp) GET_by_offset(disp, driDispatchRemapTable[TexEnvx_remap_index])
#define SET_TexEnvx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexEnvx_remap_index], fn)
#define CALL_TexEnvxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfixed *)), driDispatchRemapTable[TexEnvxv_remap_index], parameters)
#define GET_TexEnvxv(disp) GET_by_offset(disp, driDispatchRemapTable[TexEnvxv_remap_index])
#define SET_TexEnvxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexEnvxv_remap_index], fn)
#define CALL_TexParameterx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfixed)), driDispatchRemapTable[TexParameterx_remap_index], parameters)
#define GET_TexParameterx(disp) GET_by_offset(disp, driDispatchRemapTable[TexParameterx_remap_index])
#define SET_TexParameterx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexParameterx_remap_index], fn)
#define CALL_Translatex(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfixed, GLfixed, GLfixed)), driDispatchRemapTable[Translatex_remap_index], parameters)
#define GET_Translatex(disp) GET_by_offset(disp, driDispatchRemapTable[Translatex_remap_index])
#define SET_Translatex(disp, fn) SET_by_offset(disp, driDispatchRemapTable[Translatex_remap_index], fn)
#define CALL_ClipPlanef(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfloat *)), driDispatchRemapTable[ClipPlanef_remap_index], parameters)
#define GET_ClipPlanef(disp) GET_by_offset(disp, driDispatchRemapTable[ClipPlanef_remap_index])
#define SET_ClipPlanef(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ClipPlanef_remap_index], fn)
#define CALL_ClipPlanex(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfixed *)), driDispatchRemapTable[ClipPlanex_remap_index], parameters)
#define GET_ClipPlanex(disp) GET_by_offset(disp, driDispatchRemapTable[ClipPlanex_remap_index])
#define SET_ClipPlanex(disp, fn) SET_by_offset(disp, driDispatchRemapTable[ClipPlanex_remap_index], fn)
#define CALL_GetClipPlanef(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat *)), driDispatchRemapTable[GetClipPlanef_remap_index], parameters)
#define GET_GetClipPlanef(disp) GET_by_offset(disp, driDispatchRemapTable[GetClipPlanef_remap_index])
#define SET_GetClipPlanef(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetClipPlanef_remap_index], fn)
#define CALL_GetClipPlanex(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfixed *)), driDispatchRemapTable[GetClipPlanex_remap_index], parameters)
#define GET_GetClipPlanex(disp) GET_by_offset(disp, driDispatchRemapTable[GetClipPlanex_remap_index])
#define SET_GetClipPlanex(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetClipPlanex_remap_index], fn)
#define CALL_GetFixedv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfixed *)), driDispatchRemapTable[GetFixedv_remap_index], parameters)
#define GET_GetFixedv(disp) GET_by_offset(disp, driDispatchRemapTable[GetFixedv_remap_index])
#define SET_GetFixedv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetFixedv_remap_index], fn)
#define CALL_GetLightxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfixed *)), driDispatchRemapTable[GetLightxv_remap_index], parameters)
#define GET_GetLightxv(disp) GET_by_offset(disp, driDispatchRemapTable[GetLightxv_remap_index])
#define SET_GetLightxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetLightxv_remap_index], fn)
#define CALL_GetMaterialxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfixed *)), driDispatchRemapTable[GetMaterialxv_remap_index], parameters)
#define GET_GetMaterialxv(disp) GET_by_offset(disp, driDispatchRemapTable[GetMaterialxv_remap_index])
#define SET_GetMaterialxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetMaterialxv_remap_index], fn)
#define CALL_GetTexEnvxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfixed *)), driDispatchRemapTable[GetTexEnvxv_remap_index], parameters)
#define GET_GetTexEnvxv(disp) GET_by_offset(disp, driDispatchRemapTable[GetTexEnvxv_remap_index])
#define SET_GetTexEnvxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetTexEnvxv_remap_index], fn)
#define CALL_GetTexParameterxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfixed *)), driDispatchRemapTable[GetTexParameterxv_remap_index], parameters)
#define GET_GetTexParameterxv(disp) GET_by_offset(disp, driDispatchRemapTable[GetTexParameterxv_remap_index])
#define SET_GetTexParameterxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[GetTexParameterxv_remap_index], fn)
#define CALL_PointParameterx(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfixed)), driDispatchRemapTable[PointParameterx_remap_index], parameters)
#define GET_PointParameterx(disp) GET_by_offset(disp, driDispatchRemapTable[PointParameterx_remap_index])
#define SET_PointParameterx(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PointParameterx_remap_index], fn)
#define CALL_PointParameterxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfixed *)), driDispatchRemapTable[PointParameterxv_remap_index], parameters)
#define GET_PointParameterxv(disp) GET_by_offset(disp, driDispatchRemapTable[PointParameterxv_remap_index])
#define SET_PointParameterxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PointParameterxv_remap_index], fn)
#define CALL_TexParameterxv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfixed *)), driDispatchRemapTable[TexParameterxv_remap_index], parameters)
#define GET_TexParameterxv(disp) GET_by_offset(disp, driDispatchRemapTable[TexParameterxv_remap_index])
#define SET_TexParameterxv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[TexParameterxv_remap_index], fn)
#define CALL_PointParameterf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat)), driDispatchRemapTable[PointParameterf_remap_index], parameters)
#define GET_PointParameterf(disp) GET_by_offset(disp, driDispatchRemapTable[PointParameterf_remap_index])
#define SET_PointParameterf(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PointParameterf_remap_index], fn)
#define CALL_PointParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfloat *)), driDispatchRemapTable[PointParameterfv_remap_index], parameters)
#define GET_PointParameterfv(disp) GET_by_offset(disp, driDispatchRemapTable[PointParameterfv_remap_index])
#define SET_PointParameterfv(disp, fn) SET_by_offset(disp, driDispatchRemapTable[PointParameterfv_remap_index], fn)

#endif /* !defined(IN_DRI_DRIVER) */

/* define aliases for compatibility */
#define CALL_TexGenf(disp, parameters) CALL_TexGenfOES(disp, parameters)
#define GET_TexGenf(disp) GET_TexGenfOES(disp)
#define SET_TexGenf(disp, fn) SET_TexGenfOES(disp, fn)
#define CALL_TexGenfv(disp, parameters) CALL_TexGenfvOES(disp, parameters)
#define GET_TexGenfv(disp) GET_TexGenfvOES(disp)
#define SET_TexGenfv(disp, fn) SET_TexGenfvOES(disp, fn)
#define CALL_TexGeni(disp, parameters) CALL_TexGeniOES(disp, parameters)
#define GET_TexGeni(disp) GET_TexGeniOES(disp)
#define SET_TexGeni(disp, fn) SET_TexGeniOES(disp, fn)
#define CALL_TexGeniv(disp, parameters) CALL_TexGenivOES(disp, parameters)
#define GET_TexGeniv(disp) GET_TexGenivOES(disp)
#define SET_TexGeniv(disp, fn) SET_TexGenivOES(disp, fn)
#define CALL_GetTexGenfv(disp, parameters) CALL_GetTexGenfvOES(disp, parameters)
#define GET_GetTexGenfv(disp) GET_GetTexGenfvOES(disp)
#define SET_GetTexGenfv(disp, fn) SET_GetTexGenfvOES(disp, fn)
#define CALL_GetTexGeniv(disp, parameters) CALL_GetTexGenivOES(disp, parameters)
#define GET_GetTexGeniv(disp) GET_GetTexGenivOES(disp)
#define SET_GetTexGeniv(disp, fn) SET_GetTexGenivOES(disp, fn)
#define CALL_BlendEquation(disp, parameters) CALL_BlendEquationOES(disp, parameters)
#define GET_BlendEquation(disp) GET_BlendEquationOES(disp)
#define SET_BlendEquation(disp, fn) SET_BlendEquationOES(disp, fn)
#define CALL_ActiveTextureARB(disp, parameters) CALL_ActiveTexture(disp, parameters)
#define GET_ActiveTextureARB(disp) GET_ActiveTexture(disp)
#define SET_ActiveTextureARB(disp, fn) SET_ActiveTexture(disp, fn)
#define CALL_ClientActiveTextureARB(disp, parameters) CALL_ClientActiveTexture(disp, parameters)
#define GET_ClientActiveTextureARB(disp) GET_ClientActiveTexture(disp)
#define SET_ClientActiveTextureARB(disp, fn) SET_ClientActiveTexture(disp, fn)
#define CALL_MultiTexCoord4fARB(disp, parameters) CALL_MultiTexCoord4f(disp, parameters)
#define GET_MultiTexCoord4fARB(disp) GET_MultiTexCoord4f(disp)
#define SET_MultiTexCoord4fARB(disp, fn) SET_MultiTexCoord4f(disp, fn)
#define CALL_AlphaFuncxOES(disp, parameters) CALL_AlphaFuncx(disp, parameters)
#define GET_AlphaFuncxOES(disp) GET_AlphaFuncx(disp)
#define SET_AlphaFuncxOES(disp, fn) SET_AlphaFuncx(disp, fn)
#define CALL_ClearColorxOES(disp, parameters) CALL_ClearColorx(disp, parameters)
#define GET_ClearColorxOES(disp) GET_ClearColorx(disp)
#define SET_ClearColorxOES(disp, fn) SET_ClearColorx(disp, fn)
#define CALL_ClearDepthfOES(disp, parameters) CALL_ClearDepthf(disp, parameters)
#define GET_ClearDepthfOES(disp) GET_ClearDepthf(disp)
#define SET_ClearDepthfOES(disp, fn) SET_ClearDepthf(disp, fn)
#define CALL_ClearDepthxOES(disp, parameters) CALL_ClearDepthx(disp, parameters)
#define GET_ClearDepthxOES(disp) GET_ClearDepthx(disp)
#define SET_ClearDepthxOES(disp, fn) SET_ClearDepthx(disp, fn)
#define CALL_Color4xOES(disp, parameters) CALL_Color4x(disp, parameters)
#define GET_Color4xOES(disp) GET_Color4x(disp)
#define SET_Color4xOES(disp, fn) SET_Color4x(disp, fn)
#define CALL_DepthRangefOES(disp, parameters) CALL_DepthRangef(disp, parameters)
#define GET_DepthRangefOES(disp) GET_DepthRangef(disp)
#define SET_DepthRangefOES(disp, fn) SET_DepthRangef(disp, fn)
#define CALL_DepthRangexOES(disp, parameters) CALL_DepthRangex(disp, parameters)
#define GET_DepthRangexOES(disp) GET_DepthRangex(disp)
#define SET_DepthRangexOES(disp, fn) SET_DepthRangex(disp, fn)
#define CALL_FogxOES(disp, parameters) CALL_Fogx(disp, parameters)
#define GET_FogxOES(disp) GET_Fogx(disp)
#define SET_FogxOES(disp, fn) SET_Fogx(disp, fn)
#define CALL_FogxvOES(disp, parameters) CALL_Fogxv(disp, parameters)
#define GET_FogxvOES(disp) GET_Fogxv(disp)
#define SET_FogxvOES(disp, fn) SET_Fogxv(disp, fn)
#define CALL_FrustumfOES(disp, parameters) CALL_Frustumf(disp, parameters)
#define GET_FrustumfOES(disp) GET_Frustumf(disp)
#define SET_FrustumfOES(disp, fn) SET_Frustumf(disp, fn)
#define CALL_FrustumxOES(disp, parameters) CALL_Frustumx(disp, parameters)
#define GET_FrustumxOES(disp) GET_Frustumx(disp)
#define SET_FrustumxOES(disp, fn) SET_Frustumx(disp, fn)
#define CALL_LightModelxOES(disp, parameters) CALL_LightModelx(disp, parameters)
#define GET_LightModelxOES(disp) GET_LightModelx(disp)
#define SET_LightModelxOES(disp, fn) SET_LightModelx(disp, fn)
#define CALL_LightModelxvOES(disp, parameters) CALL_LightModelxv(disp, parameters)
#define GET_LightModelxvOES(disp) GET_LightModelxv(disp)
#define SET_LightModelxvOES(disp, fn) SET_LightModelxv(disp, fn)
#define CALL_LightxOES(disp, parameters) CALL_Lightx(disp, parameters)
#define GET_LightxOES(disp) GET_Lightx(disp)
#define SET_LightxOES(disp, fn) SET_Lightx(disp, fn)
#define CALL_LightxvOES(disp, parameters) CALL_Lightxv(disp, parameters)
#define GET_LightxvOES(disp) GET_Lightxv(disp)
#define SET_LightxvOES(disp, fn) SET_Lightxv(disp, fn)
#define CALL_LineWidthxOES(disp, parameters) CALL_LineWidthx(disp, parameters)
#define GET_LineWidthxOES(disp) GET_LineWidthx(disp)
#define SET_LineWidthxOES(disp, fn) SET_LineWidthx(disp, fn)
#define CALL_LoadMatrixxOES(disp, parameters) CALL_LoadMatrixx(disp, parameters)
#define GET_LoadMatrixxOES(disp) GET_LoadMatrixx(disp)
#define SET_LoadMatrixxOES(disp, fn) SET_LoadMatrixx(disp, fn)
#define CALL_MaterialxOES(disp, parameters) CALL_Materialx(disp, parameters)
#define GET_MaterialxOES(disp) GET_Materialx(disp)
#define SET_MaterialxOES(disp, fn) SET_Materialx(disp, fn)
#define CALL_MaterialxvOES(disp, parameters) CALL_Materialxv(disp, parameters)
#define GET_MaterialxvOES(disp) GET_Materialxv(disp)
#define SET_MaterialxvOES(disp, fn) SET_Materialxv(disp, fn)
#define CALL_MultMatrixxOES(disp, parameters) CALL_MultMatrixx(disp, parameters)
#define GET_MultMatrixxOES(disp) GET_MultMatrixx(disp)
#define SET_MultMatrixxOES(disp, fn) SET_MultMatrixx(disp, fn)
#define CALL_MultiTexCoord4xOES(disp, parameters) CALL_MultiTexCoord4x(disp, parameters)
#define GET_MultiTexCoord4xOES(disp) GET_MultiTexCoord4x(disp)
#define SET_MultiTexCoord4xOES(disp, fn) SET_MultiTexCoord4x(disp, fn)
#define CALL_Normal3xOES(disp, parameters) CALL_Normal3x(disp, parameters)
#define GET_Normal3xOES(disp) GET_Normal3x(disp)
#define SET_Normal3xOES(disp, fn) SET_Normal3x(disp, fn)
#define CALL_OrthofOES(disp, parameters) CALL_Orthof(disp, parameters)
#define GET_OrthofOES(disp) GET_Orthof(disp)
#define SET_OrthofOES(disp, fn) SET_Orthof(disp, fn)
#define CALL_OrthoxOES(disp, parameters) CALL_Orthox(disp, parameters)
#define GET_OrthoxOES(disp) GET_Orthox(disp)
#define SET_OrthoxOES(disp, fn) SET_Orthox(disp, fn)
#define CALL_PointSizexOES(disp, parameters) CALL_PointSizex(disp, parameters)
#define GET_PointSizexOES(disp) GET_PointSizex(disp)
#define SET_PointSizexOES(disp, fn) SET_PointSizex(disp, fn)
#define CALL_PolygonOffsetxOES(disp, parameters) CALL_PolygonOffsetx(disp, parameters)
#define GET_PolygonOffsetxOES(disp) GET_PolygonOffsetx(disp)
#define SET_PolygonOffsetxOES(disp, fn) SET_PolygonOffsetx(disp, fn)
#define CALL_RotatexOES(disp, parameters) CALL_Rotatex(disp, parameters)
#define GET_RotatexOES(disp) GET_Rotatex(disp)
#define SET_RotatexOES(disp, fn) SET_Rotatex(disp, fn)
#define CALL_SampleCoveragexOES(disp, parameters) CALL_SampleCoveragex(disp, parameters)
#define GET_SampleCoveragexOES(disp) GET_SampleCoveragex(disp)
#define SET_SampleCoveragexOES(disp, fn) SET_SampleCoveragex(disp, fn)
#define CALL_ScalexOES(disp, parameters) CALL_Scalex(disp, parameters)
#define GET_ScalexOES(disp) GET_Scalex(disp)
#define SET_ScalexOES(disp, fn) SET_Scalex(disp, fn)
#define CALL_TexEnvxOES(disp, parameters) CALL_TexEnvx(disp, parameters)
#define GET_TexEnvxOES(disp) GET_TexEnvx(disp)
#define SET_TexEnvxOES(disp, fn) SET_TexEnvx(disp, fn)
#define CALL_TexEnvxvOES(disp, parameters) CALL_TexEnvxv(disp, parameters)
#define GET_TexEnvxvOES(disp) GET_TexEnvxv(disp)
#define SET_TexEnvxvOES(disp, fn) SET_TexEnvxv(disp, fn)
#define CALL_TexParameterxOES(disp, parameters) CALL_TexParameterx(disp, parameters)
#define GET_TexParameterxOES(disp) GET_TexParameterx(disp)
#define SET_TexParameterxOES(disp, fn) SET_TexParameterx(disp, fn)
#define CALL_TranslatexOES(disp, parameters) CALL_Translatex(disp, parameters)
#define GET_TranslatexOES(disp) GET_Translatex(disp)
#define SET_TranslatexOES(disp, fn) SET_Translatex(disp, fn)
#define CALL_ClipPlanefOES(disp, parameters) CALL_ClipPlanef(disp, parameters)
#define GET_ClipPlanefOES(disp) GET_ClipPlanef(disp)
#define SET_ClipPlanefOES(disp, fn) SET_ClipPlanef(disp, fn)
#define CALL_ClipPlanexOES(disp, parameters) CALL_ClipPlanex(disp, parameters)
#define GET_ClipPlanexOES(disp) GET_ClipPlanex(disp)
#define SET_ClipPlanexOES(disp, fn) SET_ClipPlanex(disp, fn)
#define CALL_GetClipPlanefOES(disp, parameters) CALL_GetClipPlanef(disp, parameters)
#define GET_GetClipPlanefOES(disp) GET_GetClipPlanef(disp)
#define SET_GetClipPlanefOES(disp, fn) SET_GetClipPlanef(disp, fn)
#define CALL_GetClipPlanexOES(disp, parameters) CALL_GetClipPlanex(disp, parameters)
#define GET_GetClipPlanexOES(disp) GET_GetClipPlanex(disp)
#define SET_GetClipPlanexOES(disp, fn) SET_GetClipPlanex(disp, fn)
#define CALL_GetFixedvOES(disp, parameters) CALL_GetFixedv(disp, parameters)
#define GET_GetFixedvOES(disp) GET_GetFixedv(disp)
#define SET_GetFixedvOES(disp, fn) SET_GetFixedv(disp, fn)
#define CALL_GetLightxvOES(disp, parameters) CALL_GetLightxv(disp, parameters)
#define GET_GetLightxvOES(disp) GET_GetLightxv(disp)
#define SET_GetLightxvOES(disp, fn) SET_GetLightxv(disp, fn)
#define CALL_GetMaterialxvOES(disp, parameters) CALL_GetMaterialxv(disp, parameters)
#define GET_GetMaterialxvOES(disp) GET_GetMaterialxv(disp)
#define SET_GetMaterialxvOES(disp, fn) SET_GetMaterialxv(disp, fn)
#define CALL_GetTexEnvxvOES(disp, parameters) CALL_GetTexEnvxv(disp, parameters)
#define GET_GetTexEnvxvOES(disp) GET_GetTexEnvxv(disp)
#define SET_GetTexEnvxvOES(disp, fn) SET_GetTexEnvxv(disp, fn)
#define CALL_GetTexParameterxvOES(disp, parameters) CALL_GetTexParameterxv(disp, parameters)
#define GET_GetTexParameterxvOES(disp) GET_GetTexParameterxv(disp)
#define SET_GetTexParameterxvOES(disp, fn) SET_GetTexParameterxv(disp, fn)
#define CALL_PointParameterxOES(disp, parameters) CALL_PointParameterx(disp, parameters)
#define GET_PointParameterxOES(disp) GET_PointParameterx(disp)
#define SET_PointParameterxOES(disp, fn) SET_PointParameterx(disp, fn)
#define CALL_PointParameterxvOES(disp, parameters) CALL_PointParameterxv(disp, parameters)
#define GET_PointParameterxvOES(disp) GET_PointParameterxv(disp)
#define SET_PointParameterxvOES(disp, fn) SET_PointParameterxv(disp, fn)
#define CALL_TexParameterxvOES(disp, parameters) CALL_TexParameterxv(disp, parameters)
#define GET_TexParameterxvOES(disp) GET_TexParameterxv(disp)
#define SET_TexParameterxvOES(disp, fn) SET_TexParameterxv(disp, fn)

#if defined(IN_DRI_DRIVER)
#define TexGenf_remap_index TexGenfOES_remap_index
#define TexGenfv_remap_index TexGenfvOES_remap_index
#define TexGeni_remap_index TexGeniOES_remap_index
#define TexGeniv_remap_index TexGenivOES_remap_index
#define GetTexGenfv_remap_index GetTexGenfvOES_remap_index
#define GetTexGeniv_remap_index GetTexGenivOES_remap_index
#define BlendEquation_remap_index BlendEquationOES_remap_index
#define ActiveTextureARB_remap_index ActiveTexture_remap_index
#define ClientActiveTextureARB_remap_index ClientActiveTexture_remap_index
#define MultiTexCoord4fARB_remap_index MultiTexCoord4f_remap_index
#define AlphaFuncxOES_remap_index AlphaFuncx_remap_index
#define ClearColorxOES_remap_index ClearColorx_remap_index
#define ClearDepthfOES_remap_index ClearDepthf_remap_index
#define ClearDepthxOES_remap_index ClearDepthx_remap_index
#define Color4xOES_remap_index Color4x_remap_index
#define DepthRangefOES_remap_index DepthRangef_remap_index
#define DepthRangexOES_remap_index DepthRangex_remap_index
#define FogxOES_remap_index Fogx_remap_index
#define FogxvOES_remap_index Fogxv_remap_index
#define FrustumfOES_remap_index Frustumf_remap_index
#define FrustumxOES_remap_index Frustumx_remap_index
#define LightModelxOES_remap_index LightModelx_remap_index
#define LightModelxvOES_remap_index LightModelxv_remap_index
#define LightxOES_remap_index Lightx_remap_index
#define LightxvOES_remap_index Lightxv_remap_index
#define LineWidthxOES_remap_index LineWidthx_remap_index
#define LoadMatrixxOES_remap_index LoadMatrixx_remap_index
#define MaterialxOES_remap_index Materialx_remap_index
#define MaterialxvOES_remap_index Materialxv_remap_index
#define MultMatrixxOES_remap_index MultMatrixx_remap_index
#define MultiTexCoord4xOES_remap_index MultiTexCoord4x_remap_index
#define Normal3xOES_remap_index Normal3x_remap_index
#define OrthofOES_remap_index Orthof_remap_index
#define OrthoxOES_remap_index Orthox_remap_index
#define PointSizexOES_remap_index PointSizex_remap_index
#define PolygonOffsetxOES_remap_index PolygonOffsetx_remap_index
#define RotatexOES_remap_index Rotatex_remap_index
#define SampleCoveragexOES_remap_index SampleCoveragex_remap_index
#define ScalexOES_remap_index Scalex_remap_index
#define TexEnvxOES_remap_index TexEnvx_remap_index
#define TexEnvxvOES_remap_index TexEnvxv_remap_index
#define TexParameterxOES_remap_index TexParameterx_remap_index
#define TranslatexOES_remap_index Translatex_remap_index
#define ClipPlanefOES_remap_index ClipPlanef_remap_index
#define ClipPlanexOES_remap_index ClipPlanex_remap_index
#define GetClipPlanefOES_remap_index GetClipPlanef_remap_index
#define GetClipPlanexOES_remap_index GetClipPlanex_remap_index
#define GetFixedvOES_remap_index GetFixedv_remap_index
#define GetLightxvOES_remap_index GetLightxv_remap_index
#define GetMaterialxvOES_remap_index GetMaterialxv_remap_index
#define GetTexEnvxvOES_remap_index GetTexEnvxv_remap_index
#define GetTexParameterxvOES_remap_index GetTexParameterxv_remap_index
#define PointParameterxOES_remap_index PointParameterx_remap_index
#define PointParameterxvOES_remap_index PointParameterxv_remap_index
#define TexParameterxvOES_remap_index TexParameterxv_remap_index
#endif /* defined(IN_DRI_DRIVER) */


#endif /* !defined( _DISPATCH_H_ ) */
