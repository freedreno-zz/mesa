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

#if !defined( _GLAPI_DISPATCH_H_ )
#  define _GLAPI_DISPATCH_H_


/* this file should not be included directly in mesa */

/**
 * \file glapidispatch.h
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

/* total number of offsets below */
#define _gloffset_COUNT 518

#define _gloffset_NewList 0
#define _gloffset_EndList 1
#define _gloffset_CallList 2
#define _gloffset_CallLists 3
#define _gloffset_DeleteLists 4
#define _gloffset_GenLists 5
#define _gloffset_ListBase 6
#define _gloffset_Begin 7
#define _gloffset_Bitmap 8
#define _gloffset_Color3b 9
#define _gloffset_Color3bv 10
#define _gloffset_Color3d 11
#define _gloffset_Color3dv 12
#define _gloffset_Color3f 13
#define _gloffset_Color3fv 14
#define _gloffset_Color3i 15
#define _gloffset_Color3iv 16
#define _gloffset_Color3s 17
#define _gloffset_Color3sv 18
#define _gloffset_Color3ub 19
#define _gloffset_Color3ubv 20
#define _gloffset_Color3ui 21
#define _gloffset_Color3uiv 22
#define _gloffset_Color3us 23
#define _gloffset_Color3usv 24
#define _gloffset_Color4b 25
#define _gloffset_Color4bv 26
#define _gloffset_Color4d 27
#define _gloffset_Color4dv 28
#define _gloffset_Color4f 29
#define _gloffset_Color4fv 30
#define _gloffset_Color4i 31
#define _gloffset_Color4iv 32
#define _gloffset_Color4s 33
#define _gloffset_Color4sv 34
#define _gloffset_Color4ub 35
#define _gloffset_Color4ubv 36
#define _gloffset_Color4ui 37
#define _gloffset_Color4uiv 38
#define _gloffset_Color4us 39
#define _gloffset_Color4usv 40
#define _gloffset_EdgeFlag 41
#define _gloffset_EdgeFlagv 42
#define _gloffset_End 43
#define _gloffset_Indexd 44
#define _gloffset_Indexdv 45
#define _gloffset_Indexf 46
#define _gloffset_Indexfv 47
#define _gloffset_Indexi 48
#define _gloffset_Indexiv 49
#define _gloffset_Indexs 50
#define _gloffset_Indexsv 51
#define _gloffset_Normal3b 52
#define _gloffset_Normal3bv 53
#define _gloffset_Normal3d 54
#define _gloffset_Normal3dv 55
#define _gloffset_Normal3f 56
#define _gloffset_Normal3fv 57
#define _gloffset_Normal3i 58
#define _gloffset_Normal3iv 59
#define _gloffset_Normal3s 60
#define _gloffset_Normal3sv 61
#define _gloffset_RasterPos2d 62
#define _gloffset_RasterPos2dv 63
#define _gloffset_RasterPos2f 64
#define _gloffset_RasterPos2fv 65
#define _gloffset_RasterPos2i 66
#define _gloffset_RasterPos2iv 67
#define _gloffset_RasterPos2s 68
#define _gloffset_RasterPos2sv 69
#define _gloffset_RasterPos3d 70
#define _gloffset_RasterPos3dv 71
#define _gloffset_RasterPos3f 72
#define _gloffset_RasterPos3fv 73
#define _gloffset_RasterPos3i 74
#define _gloffset_RasterPos3iv 75
#define _gloffset_RasterPos3s 76
#define _gloffset_RasterPos3sv 77
#define _gloffset_RasterPos4d 78
#define _gloffset_RasterPos4dv 79
#define _gloffset_RasterPos4f 80
#define _gloffset_RasterPos4fv 81
#define _gloffset_RasterPos4i 82
#define _gloffset_RasterPos4iv 83
#define _gloffset_RasterPos4s 84
#define _gloffset_RasterPos4sv 85
#define _gloffset_Rectd 86
#define _gloffset_Rectdv 87
#define _gloffset_Rectf 88
#define _gloffset_Rectfv 89
#define _gloffset_Recti 90
#define _gloffset_Rectiv 91
#define _gloffset_Rects 92
#define _gloffset_Rectsv 93
#define _gloffset_TexCoord1d 94
#define _gloffset_TexCoord1dv 95
#define _gloffset_TexCoord1f 96
#define _gloffset_TexCoord1fv 97
#define _gloffset_TexCoord1i 98
#define _gloffset_TexCoord1iv 99
#define _gloffset_TexCoord1s 100
#define _gloffset_TexCoord1sv 101
#define _gloffset_TexCoord2d 102
#define _gloffset_TexCoord2dv 103
#define _gloffset_TexCoord2f 104
#define _gloffset_TexCoord2fv 105
#define _gloffset_TexCoord2i 106
#define _gloffset_TexCoord2iv 107
#define _gloffset_TexCoord2s 108
#define _gloffset_TexCoord2sv 109
#define _gloffset_TexCoord3d 110
#define _gloffset_TexCoord3dv 111
#define _gloffset_TexCoord3f 112
#define _gloffset_TexCoord3fv 113
#define _gloffset_TexCoord3i 114
#define _gloffset_TexCoord3iv 115
#define _gloffset_TexCoord3s 116
#define _gloffset_TexCoord3sv 117
#define _gloffset_TexCoord4d 118
#define _gloffset_TexCoord4dv 119
#define _gloffset_TexCoord4f 120
#define _gloffset_TexCoord4fv 121
#define _gloffset_TexCoord4i 122
#define _gloffset_TexCoord4iv 123
#define _gloffset_TexCoord4s 124
#define _gloffset_TexCoord4sv 125
#define _gloffset_Vertex2d 126
#define _gloffset_Vertex2dv 127
#define _gloffset_Vertex2f 128
#define _gloffset_Vertex2fv 129
#define _gloffset_Vertex2i 130
#define _gloffset_Vertex2iv 131
#define _gloffset_Vertex2s 132
#define _gloffset_Vertex2sv 133
#define _gloffset_Vertex3d 134
#define _gloffset_Vertex3dv 135
#define _gloffset_Vertex3f 136
#define _gloffset_Vertex3fv 137
#define _gloffset_Vertex3i 138
#define _gloffset_Vertex3iv 139
#define _gloffset_Vertex3s 140
#define _gloffset_Vertex3sv 141
#define _gloffset_Vertex4d 142
#define _gloffset_Vertex4dv 143
#define _gloffset_Vertex4f 144
#define _gloffset_Vertex4fv 145
#define _gloffset_Vertex4i 146
#define _gloffset_Vertex4iv 147
#define _gloffset_Vertex4s 148
#define _gloffset_Vertex4sv 149
#define _gloffset_ClipPlane 150
#define _gloffset_ColorMaterial 151
#define _gloffset_CullFace 152
#define _gloffset_Fogf 153
#define _gloffset_Fogfv 154
#define _gloffset_Fogi 155
#define _gloffset_Fogiv 156
#define _gloffset_FrontFace 157
#define _gloffset_Hint 158
#define _gloffset_Lightf 159
#define _gloffset_Lightfv 160
#define _gloffset_Lighti 161
#define _gloffset_Lightiv 162
#define _gloffset_LightModelf 163
#define _gloffset_LightModelfv 164
#define _gloffset_LightModeli 165
#define _gloffset_LightModeliv 166
#define _gloffset_LineStipple 167
#define _gloffset_LineWidth 168
#define _gloffset_Materialf 169
#define _gloffset_Materialfv 170
#define _gloffset_Materiali 171
#define _gloffset_Materialiv 172
#define _gloffset_PointSize 173
#define _gloffset_PolygonMode 174
#define _gloffset_PolygonStipple 175
#define _gloffset_Scissor 176
#define _gloffset_ShadeModel 177
#define _gloffset_TexParameterf 178
#define _gloffset_TexParameterfv 179
#define _gloffset_TexParameteri 180
#define _gloffset_TexParameteriv 181
#define _gloffset_TexImage1D 182
#define _gloffset_TexImage2D 183
#define _gloffset_TexEnvf 184
#define _gloffset_TexEnvfv 185
#define _gloffset_TexEnvi 186
#define _gloffset_TexEnviv 187
#define _gloffset_TexGend 188
#define _gloffset_TexGendv 189
#define _gloffset_TexGenf 190
#define _gloffset_TexGenfv 191
#define _gloffset_TexGeni 192
#define _gloffset_TexGeniv 193
#define _gloffset_FeedbackBuffer 194
#define _gloffset_SelectBuffer 195
#define _gloffset_RenderMode 196
#define _gloffset_InitNames 197
#define _gloffset_LoadName 198
#define _gloffset_PassThrough 199
#define _gloffset_PopName 200
#define _gloffset_PushName 201
#define _gloffset_DrawBuffer 202
#define _gloffset_Clear 203
#define _gloffset_ClearAccum 204
#define _gloffset_ClearIndex 205
#define _gloffset_ClearColor 206
#define _gloffset_ClearStencil 207
#define _gloffset_ClearDepth 208
#define _gloffset_StencilMask 209
#define _gloffset_ColorMask 210
#define _gloffset_DepthMask 211
#define _gloffset_IndexMask 212
#define _gloffset_Accum 213
#define _gloffset_Disable 214
#define _gloffset_Enable 215
#define _gloffset_Finish 216
#define _gloffset_Flush 217
#define _gloffset_PopAttrib 218
#define _gloffset_PushAttrib 219
#define _gloffset_Map1d 220
#define _gloffset_Map1f 221
#define _gloffset_Map2d 222
#define _gloffset_Map2f 223
#define _gloffset_MapGrid1d 224
#define _gloffset_MapGrid1f 225
#define _gloffset_MapGrid2d 226
#define _gloffset_MapGrid2f 227
#define _gloffset_EvalCoord1d 228
#define _gloffset_EvalCoord1dv 229
#define _gloffset_EvalCoord1f 230
#define _gloffset_EvalCoord1fv 231
#define _gloffset_EvalCoord2d 232
#define _gloffset_EvalCoord2dv 233
#define _gloffset_EvalCoord2f 234
#define _gloffset_EvalCoord2fv 235
#define _gloffset_EvalMesh1 236
#define _gloffset_EvalPoint1 237
#define _gloffset_EvalMesh2 238
#define _gloffset_EvalPoint2 239
#define _gloffset_AlphaFunc 240
#define _gloffset_BlendFunc 241
#define _gloffset_LogicOp 242
#define _gloffset_StencilFunc 243
#define _gloffset_StencilOp 244
#define _gloffset_DepthFunc 245
#define _gloffset_PixelZoom 246
#define _gloffset_PixelTransferf 247
#define _gloffset_PixelTransferi 248
#define _gloffset_PixelStoref 249
#define _gloffset_PixelStorei 250
#define _gloffset_PixelMapfv 251
#define _gloffset_PixelMapuiv 252
#define _gloffset_PixelMapusv 253
#define _gloffset_ReadBuffer 254
#define _gloffset_CopyPixels 255
#define _gloffset_ReadPixels 256
#define _gloffset_DrawPixels 257
#define _gloffset_GetBooleanv 258
#define _gloffset_GetClipPlane 259
#define _gloffset_GetDoublev 260
#define _gloffset_GetError 261
#define _gloffset_GetFloatv 262
#define _gloffset_GetIntegerv 263
#define _gloffset_GetLightfv 264
#define _gloffset_GetLightiv 265
#define _gloffset_GetMapdv 266
#define _gloffset_GetMapfv 267
#define _gloffset_GetMapiv 268
#define _gloffset_GetMaterialfv 269
#define _gloffset_GetMaterialiv 270
#define _gloffset_GetPixelMapfv 271
#define _gloffset_GetPixelMapuiv 272
#define _gloffset_GetPixelMapusv 273
#define _gloffset_GetPolygonStipple 274
#define _gloffset_GetString 275
#define _gloffset_GetTexEnvfv 276
#define _gloffset_GetTexEnviv 277
#define _gloffset_GetTexGendv 278
#define _gloffset_GetTexGenfv 279
#define _gloffset_GetTexGeniv 280
#define _gloffset_GetTexImage 281
#define _gloffset_GetTexParameterfv 282
#define _gloffset_GetTexParameteriv 283
#define _gloffset_GetTexLevelParameterfv 284
#define _gloffset_GetTexLevelParameteriv 285
#define _gloffset_IsEnabled 286
#define _gloffset_IsList 287
#define _gloffset_DepthRange 288
#define _gloffset_Frustum 289
#define _gloffset_LoadIdentity 290
#define _gloffset_LoadMatrixf 291
#define _gloffset_LoadMatrixd 292
#define _gloffset_MatrixMode 293
#define _gloffset_MultMatrixf 294
#define _gloffset_MultMatrixd 295
#define _gloffset_Ortho 296
#define _gloffset_PopMatrix 297
#define _gloffset_PushMatrix 298
#define _gloffset_Rotated 299
#define _gloffset_Rotatef 300
#define _gloffset_Scaled 301
#define _gloffset_Scalef 302
#define _gloffset_Translated 303
#define _gloffset_Translatef 304
#define _gloffset_Viewport 305
#define _gloffset_ArrayElement 306
#define _gloffset_BindTexture 307
#define _gloffset_ColorPointer 308
#define _gloffset_DisableClientState 309
#define _gloffset_DrawArrays 310
#define _gloffset_DrawElements 311
#define _gloffset_EdgeFlagPointer 312
#define _gloffset_EnableClientState 313
#define _gloffset_IndexPointer 314
#define _gloffset_Indexub 315
#define _gloffset_Indexubv 316
#define _gloffset_InterleavedArrays 317
#define _gloffset_NormalPointer 318
#define _gloffset_PolygonOffset 319
#define _gloffset_TexCoordPointer 320
#define _gloffset_VertexPointer 321
#define _gloffset_AreTexturesResident 322
#define _gloffset_CopyTexImage1D 323
#define _gloffset_CopyTexImage2D 324
#define _gloffset_CopyTexSubImage1D 325
#define _gloffset_CopyTexSubImage2D 326
#define _gloffset_DeleteTextures 327
#define _gloffset_GenTextures 328
#define _gloffset_GetPointerv 329
#define _gloffset_IsTexture 330
#define _gloffset_PrioritizeTextures 331
#define _gloffset_TexSubImage1D 332
#define _gloffset_TexSubImage2D 333
#define _gloffset_PopClientAttrib 334
#define _gloffset_PushClientAttrib 335
#define _gloffset_BlendColor 336
#define _gloffset_BlendEquation 337
#define _gloffset_DrawRangeElements 338
#define _gloffset_ColorTable 339
#define _gloffset_ColorTableParameterfv 340
#define _gloffset_ColorTableParameteriv 341
#define _gloffset_CopyColorTable 342
#define _gloffset_GetColorTable 343
#define _gloffset_GetColorTableParameterfv 344
#define _gloffset_GetColorTableParameteriv 345
#define _gloffset_ColorSubTable 346
#define _gloffset_CopyColorSubTable 347
#define _gloffset_ConvolutionFilter1D 348
#define _gloffset_ConvolutionFilter2D 349
#define _gloffset_ConvolutionParameterf 350
#define _gloffset_ConvolutionParameterfv 351
#define _gloffset_ConvolutionParameteri 352
#define _gloffset_ConvolutionParameteriv 353
#define _gloffset_CopyConvolutionFilter1D 354
#define _gloffset_CopyConvolutionFilter2D 355
#define _gloffset_GetConvolutionFilter 356
#define _gloffset_GetConvolutionParameterfv 357
#define _gloffset_GetConvolutionParameteriv 358
#define _gloffset_GetSeparableFilter 359
#define _gloffset_SeparableFilter2D 360
#define _gloffset_GetHistogram 361
#define _gloffset_GetHistogramParameterfv 362
#define _gloffset_GetHistogramParameteriv 363
#define _gloffset_GetMinmax 364
#define _gloffset_GetMinmaxParameterfv 365
#define _gloffset_GetMinmaxParameteriv 366
#define _gloffset_Histogram 367
#define _gloffset_Minmax 368
#define _gloffset_ResetHistogram 369
#define _gloffset_ResetMinmax 370
#define _gloffset_TexImage3DOES 371
#define _gloffset_TexSubImage3DOES 372
#define _gloffset_CopyTexSubImage3DOES 373
#define _gloffset_ActiveTexture 374
#define _gloffset_ClientActiveTextureARB 375
#define _gloffset_MultiTexCoord1dARB 376
#define _gloffset_MultiTexCoord1dvARB 377
#define _gloffset_MultiTexCoord1fARB 378
#define _gloffset_MultiTexCoord1fvARB 379
#define _gloffset_MultiTexCoord1iARB 380
#define _gloffset_MultiTexCoord1ivARB 381
#define _gloffset_MultiTexCoord1sARB 382
#define _gloffset_MultiTexCoord1svARB 383
#define _gloffset_MultiTexCoord2dARB 384
#define _gloffset_MultiTexCoord2dvARB 385
#define _gloffset_MultiTexCoord2fARB 386
#define _gloffset_MultiTexCoord2fvARB 387
#define _gloffset_MultiTexCoord2iARB 388
#define _gloffset_MultiTexCoord2ivARB 389
#define _gloffset_MultiTexCoord2sARB 390
#define _gloffset_MultiTexCoord2svARB 391
#define _gloffset_MultiTexCoord3dARB 392
#define _gloffset_MultiTexCoord3dvARB 393
#define _gloffset_MultiTexCoord3fARB 394
#define _gloffset_MultiTexCoord3fvARB 395
#define _gloffset_MultiTexCoord3iARB 396
#define _gloffset_MultiTexCoord3ivARB 397
#define _gloffset_MultiTexCoord3sARB 398
#define _gloffset_MultiTexCoord3svARB 399
#define _gloffset_MultiTexCoord4dARB 400
#define _gloffset_MultiTexCoord4dvARB 401
#define _gloffset_MultiTexCoord4fARB 402
#define _gloffset_MultiTexCoord4fvARB 403
#define _gloffset_MultiTexCoord4iARB 404
#define _gloffset_MultiTexCoord4ivARB 405
#define _gloffset_MultiTexCoord4sARB 406
#define _gloffset_MultiTexCoord4svARB 407

#if !defined(_GLAPI_USE_REMAP_TABLE)

#define _gloffset_GetBufferPointervOES 408
#define _gloffset_MapBufferOES 409
#define _gloffset_UnmapBufferOES 410
#define _gloffset_CompressedTexImage3DOES 411
#define _gloffset_CompressedTexSubImage3DOES 412
#define _gloffset_FramebufferTexture3DOES 413
#define _gloffset_GetProgramBinaryOES 414
#define _gloffset_ProgramBinaryOES 415
#define _gloffset_MultiDrawArraysEXT 416
#define _gloffset_MultiDrawElementsEXT 417
#define _gloffset_BindVertexArrayAPPLE 418
#define _gloffset_DeleteVertexArraysAPPLE 419
#define _gloffset_GenVertexArraysAPPLE 420
#define _gloffset_IsVertexArrayAPPLE 421
#define _gloffset_EGLImageTargetRenderbufferStorageOES 422
#define _gloffset_EGLImageTargetTexture2DOES 423
#define _gloffset_CompressedTexImage2D 424
#define _gloffset_CompressedTexSubImage2D 425
#define _gloffset_SampleCoverage 426
#define _gloffset_BindBuffer 427
#define _gloffset_BufferData 428
#define _gloffset_BufferSubData 429
#define _gloffset_DeleteBuffers 430
#define _gloffset_GenBuffers 431
#define _gloffset_GetBufferParameteriv 432
#define _gloffset_IsBuffer 433
#define _gloffset_AttachShader 434
#define _gloffset_BindAttribLocation 435
#define _gloffset_BlendEquationSeparate 436
#define _gloffset_CompileShader 437
#define _gloffset_CreateProgram 438
#define _gloffset_CreateShader 439
#define _gloffset_DeleteProgram 440
#define _gloffset_DeleteShader 441
#define _gloffset_DetachShader 442
#define _gloffset_DisableVertexAttribArray 443
#define _gloffset_EnableVertexAttribArray 444
#define _gloffset_GetActiveAttrib 445
#define _gloffset_GetActiveUniform 446
#define _gloffset_GetAttachedShaders 447
#define _gloffset_GetAttribLocation 448
#define _gloffset_GetProgramInfoLog 449
#define _gloffset_GetProgramiv 450
#define _gloffset_GetShaderInfoLog 451
#define _gloffset_GetShaderSource 452
#define _gloffset_GetShaderiv 453
#define _gloffset_GetUniformLocation 454
#define _gloffset_GetUniformfv 455
#define _gloffset_GetUniformiv 456
#define _gloffset_GetVertexAttribPointerv 457
#define _gloffset_GetVertexAttribfv 458
#define _gloffset_GetVertexAttribiv 459
#define _gloffset_IsProgram 460
#define _gloffset_IsShader 461
#define _gloffset_LinkProgram 462
#define _gloffset_ShaderSource 463
#define _gloffset_StencilFuncSeparate 464
#define _gloffset_StencilMaskSeparate 465
#define _gloffset_StencilOpSeparate 466
#define _gloffset_Uniform1f 467
#define _gloffset_Uniform1fv 468
#define _gloffset_Uniform1i 469
#define _gloffset_Uniform1iv 470
#define _gloffset_Uniform2f 471
#define _gloffset_Uniform2fv 472
#define _gloffset_Uniform2i 473
#define _gloffset_Uniform2iv 474
#define _gloffset_Uniform3f 475
#define _gloffset_Uniform3fv 476
#define _gloffset_Uniform3i 477
#define _gloffset_Uniform3iv 478
#define _gloffset_Uniform4f 479
#define _gloffset_Uniform4fv 480
#define _gloffset_Uniform4i 481
#define _gloffset_Uniform4iv 482
#define _gloffset_UniformMatrix2fv 483
#define _gloffset_UniformMatrix3fv 484
#define _gloffset_UniformMatrix4fv 485
#define _gloffset_UseProgram 486
#define _gloffset_ValidateProgram 487
#define _gloffset_VertexAttrib1f 488
#define _gloffset_VertexAttrib1fv 489
#define _gloffset_VertexAttrib2f 490
#define _gloffset_VertexAttrib2fv 491
#define _gloffset_VertexAttrib3f 492
#define _gloffset_VertexAttrib3fv 493
#define _gloffset_VertexAttrib4f 494
#define _gloffset_VertexAttrib4fv 495
#define _gloffset_VertexAttribPointer 496
#define _gloffset_BlendFuncSeparate 497
#define _gloffset_BindFramebuffer 498
#define _gloffset_BindRenderbuffer 499
#define _gloffset_CheckFramebufferStatus 500
#define _gloffset_ClearDepthf 501
#define _gloffset_DeleteFramebuffers 502
#define _gloffset_DeleteRenderbuffers 503
#define _gloffset_DepthRangef 504
#define _gloffset_FramebufferRenderbuffer 505
#define _gloffset_FramebufferTexture2D 506
#define _gloffset_GenFramebuffers 507
#define _gloffset_GenRenderbuffers 508
#define _gloffset_GenerateMipmap 509
#define _gloffset_GetFramebufferAttachmentParameteriv 510
#define _gloffset_GetRenderbufferParameteriv 511
#define _gloffset_GetShaderPrecisionFormat 512
#define _gloffset_IsFramebuffer 513
#define _gloffset_IsRenderbuffer 514
#define _gloffset_ReleaseShaderCompiler 515
#define _gloffset_RenderbufferStorage 516
#define _gloffset_ShaderBinary 517

#else /* !_GLAPI_USE_REMAP_TABLE */

#define driDispatchRemapTable_size 110
extern int driDispatchRemapTable[ driDispatchRemapTable_size ];

#define GetBufferPointervOES_remap_index 0
#define MapBufferOES_remap_index 1
#define UnmapBufferOES_remap_index 2
#define CompressedTexImage3DOES_remap_index 3
#define CompressedTexSubImage3DOES_remap_index 4
#define FramebufferTexture3DOES_remap_index 5
#define GetProgramBinaryOES_remap_index 6
#define ProgramBinaryOES_remap_index 7
#define MultiDrawArraysEXT_remap_index 8
#define MultiDrawElementsEXT_remap_index 9
#define BindVertexArrayAPPLE_remap_index 10
#define DeleteVertexArraysAPPLE_remap_index 11
#define GenVertexArraysAPPLE_remap_index 12
#define IsVertexArrayAPPLE_remap_index 13
#define EGLImageTargetRenderbufferStorageOES_remap_index 14
#define EGLImageTargetTexture2DOES_remap_index 15
#define CompressedTexImage2D_remap_index 16
#define CompressedTexSubImage2D_remap_index 17
#define SampleCoverage_remap_index 18
#define BindBuffer_remap_index 19
#define BufferData_remap_index 20
#define BufferSubData_remap_index 21
#define DeleteBuffers_remap_index 22
#define GenBuffers_remap_index 23
#define GetBufferParameteriv_remap_index 24
#define IsBuffer_remap_index 25
#define AttachShader_remap_index 26
#define BindAttribLocation_remap_index 27
#define BlendEquationSeparate_remap_index 28
#define CompileShader_remap_index 29
#define CreateProgram_remap_index 30
#define CreateShader_remap_index 31
#define DeleteProgram_remap_index 32
#define DeleteShader_remap_index 33
#define DetachShader_remap_index 34
#define DisableVertexAttribArray_remap_index 35
#define EnableVertexAttribArray_remap_index 36
#define GetActiveAttrib_remap_index 37
#define GetActiveUniform_remap_index 38
#define GetAttachedShaders_remap_index 39
#define GetAttribLocation_remap_index 40
#define GetProgramInfoLog_remap_index 41
#define GetProgramiv_remap_index 42
#define GetShaderInfoLog_remap_index 43
#define GetShaderSource_remap_index 44
#define GetShaderiv_remap_index 45
#define GetUniformLocation_remap_index 46
#define GetUniformfv_remap_index 47
#define GetUniformiv_remap_index 48
#define GetVertexAttribPointerv_remap_index 49
#define GetVertexAttribfv_remap_index 50
#define GetVertexAttribiv_remap_index 51
#define IsProgram_remap_index 52
#define IsShader_remap_index 53
#define LinkProgram_remap_index 54
#define ShaderSource_remap_index 55
#define StencilFuncSeparate_remap_index 56
#define StencilMaskSeparate_remap_index 57
#define StencilOpSeparate_remap_index 58
#define Uniform1f_remap_index 59
#define Uniform1fv_remap_index 60
#define Uniform1i_remap_index 61
#define Uniform1iv_remap_index 62
#define Uniform2f_remap_index 63
#define Uniform2fv_remap_index 64
#define Uniform2i_remap_index 65
#define Uniform2iv_remap_index 66
#define Uniform3f_remap_index 67
#define Uniform3fv_remap_index 68
#define Uniform3i_remap_index 69
#define Uniform3iv_remap_index 70
#define Uniform4f_remap_index 71
#define Uniform4fv_remap_index 72
#define Uniform4i_remap_index 73
#define Uniform4iv_remap_index 74
#define UniformMatrix2fv_remap_index 75
#define UniformMatrix3fv_remap_index 76
#define UniformMatrix4fv_remap_index 77
#define UseProgram_remap_index 78
#define ValidateProgram_remap_index 79
#define VertexAttrib1f_remap_index 80
#define VertexAttrib1fv_remap_index 81
#define VertexAttrib2f_remap_index 82
#define VertexAttrib2fv_remap_index 83
#define VertexAttrib3f_remap_index 84
#define VertexAttrib3fv_remap_index 85
#define VertexAttrib4f_remap_index 86
#define VertexAttrib4fv_remap_index 87
#define VertexAttribPointer_remap_index 88
#define BlendFuncSeparate_remap_index 89
#define BindFramebuffer_remap_index 90
#define BindRenderbuffer_remap_index 91
#define CheckFramebufferStatus_remap_index 92
#define ClearDepthf_remap_index 93
#define DeleteFramebuffers_remap_index 94
#define DeleteRenderbuffers_remap_index 95
#define DepthRangef_remap_index 96
#define FramebufferRenderbuffer_remap_index 97
#define FramebufferTexture2D_remap_index 98
#define GenFramebuffers_remap_index 99
#define GenRenderbuffers_remap_index 100
#define GenerateMipmap_remap_index 101
#define GetFramebufferAttachmentParameteriv_remap_index 102
#define GetRenderbufferParameteriv_remap_index 103
#define GetShaderPrecisionFormat_remap_index 104
#define IsFramebuffer_remap_index 105
#define IsRenderbuffer_remap_index 106
#define ReleaseShaderCompiler_remap_index 107
#define RenderbufferStorage_remap_index 108
#define ShaderBinary_remap_index 109

#define _gloffset_GetBufferPointervOES driDispatchRemapTable[GetBufferPointervOES_remap_index]
#define _gloffset_MapBufferOES driDispatchRemapTable[MapBufferOES_remap_index]
#define _gloffset_UnmapBufferOES driDispatchRemapTable[UnmapBufferOES_remap_index]
#define _gloffset_CompressedTexImage3DOES driDispatchRemapTable[CompressedTexImage3DOES_remap_index]
#define _gloffset_CompressedTexSubImage3DOES driDispatchRemapTable[CompressedTexSubImage3DOES_remap_index]
#define _gloffset_FramebufferTexture3DOES driDispatchRemapTable[FramebufferTexture3DOES_remap_index]
#define _gloffset_GetProgramBinaryOES driDispatchRemapTable[GetProgramBinaryOES_remap_index]
#define _gloffset_ProgramBinaryOES driDispatchRemapTable[ProgramBinaryOES_remap_index]
#define _gloffset_MultiDrawArraysEXT driDispatchRemapTable[MultiDrawArraysEXT_remap_index]
#define _gloffset_MultiDrawElementsEXT driDispatchRemapTable[MultiDrawElementsEXT_remap_index]
#define _gloffset_BindVertexArrayAPPLE driDispatchRemapTable[BindVertexArrayAPPLE_remap_index]
#define _gloffset_DeleteVertexArraysAPPLE driDispatchRemapTable[DeleteVertexArraysAPPLE_remap_index]
#define _gloffset_GenVertexArraysAPPLE driDispatchRemapTable[GenVertexArraysAPPLE_remap_index]
#define _gloffset_IsVertexArrayAPPLE driDispatchRemapTable[IsVertexArrayAPPLE_remap_index]
#define _gloffset_EGLImageTargetRenderbufferStorageOES driDispatchRemapTable[EGLImageTargetRenderbufferStorageOES_remap_index]
#define _gloffset_EGLImageTargetTexture2DOES driDispatchRemapTable[EGLImageTargetTexture2DOES_remap_index]
#define _gloffset_CompressedTexImage2D driDispatchRemapTable[CompressedTexImage2D_remap_index]
#define _gloffset_CompressedTexSubImage2D driDispatchRemapTable[CompressedTexSubImage2D_remap_index]
#define _gloffset_SampleCoverage driDispatchRemapTable[SampleCoverage_remap_index]
#define _gloffset_BindBuffer driDispatchRemapTable[BindBuffer_remap_index]
#define _gloffset_BufferData driDispatchRemapTable[BufferData_remap_index]
#define _gloffset_BufferSubData driDispatchRemapTable[BufferSubData_remap_index]
#define _gloffset_DeleteBuffers driDispatchRemapTable[DeleteBuffers_remap_index]
#define _gloffset_GenBuffers driDispatchRemapTable[GenBuffers_remap_index]
#define _gloffset_GetBufferParameteriv driDispatchRemapTable[GetBufferParameteriv_remap_index]
#define _gloffset_IsBuffer driDispatchRemapTable[IsBuffer_remap_index]
#define _gloffset_AttachShader driDispatchRemapTable[AttachShader_remap_index]
#define _gloffset_BindAttribLocation driDispatchRemapTable[BindAttribLocation_remap_index]
#define _gloffset_BlendEquationSeparate driDispatchRemapTable[BlendEquationSeparate_remap_index]
#define _gloffset_CompileShader driDispatchRemapTable[CompileShader_remap_index]
#define _gloffset_CreateProgram driDispatchRemapTable[CreateProgram_remap_index]
#define _gloffset_CreateShader driDispatchRemapTable[CreateShader_remap_index]
#define _gloffset_DeleteProgram driDispatchRemapTable[DeleteProgram_remap_index]
#define _gloffset_DeleteShader driDispatchRemapTable[DeleteShader_remap_index]
#define _gloffset_DetachShader driDispatchRemapTable[DetachShader_remap_index]
#define _gloffset_DisableVertexAttribArray driDispatchRemapTable[DisableVertexAttribArray_remap_index]
#define _gloffset_EnableVertexAttribArray driDispatchRemapTable[EnableVertexAttribArray_remap_index]
#define _gloffset_GetActiveAttrib driDispatchRemapTable[GetActiveAttrib_remap_index]
#define _gloffset_GetActiveUniform driDispatchRemapTable[GetActiveUniform_remap_index]
#define _gloffset_GetAttachedShaders driDispatchRemapTable[GetAttachedShaders_remap_index]
#define _gloffset_GetAttribLocation driDispatchRemapTable[GetAttribLocation_remap_index]
#define _gloffset_GetProgramInfoLog driDispatchRemapTable[GetProgramInfoLog_remap_index]
#define _gloffset_GetProgramiv driDispatchRemapTable[GetProgramiv_remap_index]
#define _gloffset_GetShaderInfoLog driDispatchRemapTable[GetShaderInfoLog_remap_index]
#define _gloffset_GetShaderSource driDispatchRemapTable[GetShaderSource_remap_index]
#define _gloffset_GetShaderiv driDispatchRemapTable[GetShaderiv_remap_index]
#define _gloffset_GetUniformLocation driDispatchRemapTable[GetUniformLocation_remap_index]
#define _gloffset_GetUniformfv driDispatchRemapTable[GetUniformfv_remap_index]
#define _gloffset_GetUniformiv driDispatchRemapTable[GetUniformiv_remap_index]
#define _gloffset_GetVertexAttribPointerv driDispatchRemapTable[GetVertexAttribPointerv_remap_index]
#define _gloffset_GetVertexAttribfv driDispatchRemapTable[GetVertexAttribfv_remap_index]
#define _gloffset_GetVertexAttribiv driDispatchRemapTable[GetVertexAttribiv_remap_index]
#define _gloffset_IsProgram driDispatchRemapTable[IsProgram_remap_index]
#define _gloffset_IsShader driDispatchRemapTable[IsShader_remap_index]
#define _gloffset_LinkProgram driDispatchRemapTable[LinkProgram_remap_index]
#define _gloffset_ShaderSource driDispatchRemapTable[ShaderSource_remap_index]
#define _gloffset_StencilFuncSeparate driDispatchRemapTable[StencilFuncSeparate_remap_index]
#define _gloffset_StencilMaskSeparate driDispatchRemapTable[StencilMaskSeparate_remap_index]
#define _gloffset_StencilOpSeparate driDispatchRemapTable[StencilOpSeparate_remap_index]
#define _gloffset_Uniform1f driDispatchRemapTable[Uniform1f_remap_index]
#define _gloffset_Uniform1fv driDispatchRemapTable[Uniform1fv_remap_index]
#define _gloffset_Uniform1i driDispatchRemapTable[Uniform1i_remap_index]
#define _gloffset_Uniform1iv driDispatchRemapTable[Uniform1iv_remap_index]
#define _gloffset_Uniform2f driDispatchRemapTable[Uniform2f_remap_index]
#define _gloffset_Uniform2fv driDispatchRemapTable[Uniform2fv_remap_index]
#define _gloffset_Uniform2i driDispatchRemapTable[Uniform2i_remap_index]
#define _gloffset_Uniform2iv driDispatchRemapTable[Uniform2iv_remap_index]
#define _gloffset_Uniform3f driDispatchRemapTable[Uniform3f_remap_index]
#define _gloffset_Uniform3fv driDispatchRemapTable[Uniform3fv_remap_index]
#define _gloffset_Uniform3i driDispatchRemapTable[Uniform3i_remap_index]
#define _gloffset_Uniform3iv driDispatchRemapTable[Uniform3iv_remap_index]
#define _gloffset_Uniform4f driDispatchRemapTable[Uniform4f_remap_index]
#define _gloffset_Uniform4fv driDispatchRemapTable[Uniform4fv_remap_index]
#define _gloffset_Uniform4i driDispatchRemapTable[Uniform4i_remap_index]
#define _gloffset_Uniform4iv driDispatchRemapTable[Uniform4iv_remap_index]
#define _gloffset_UniformMatrix2fv driDispatchRemapTable[UniformMatrix2fv_remap_index]
#define _gloffset_UniformMatrix3fv driDispatchRemapTable[UniformMatrix3fv_remap_index]
#define _gloffset_UniformMatrix4fv driDispatchRemapTable[UniformMatrix4fv_remap_index]
#define _gloffset_UseProgram driDispatchRemapTable[UseProgram_remap_index]
#define _gloffset_ValidateProgram driDispatchRemapTable[ValidateProgram_remap_index]
#define _gloffset_VertexAttrib1f driDispatchRemapTable[VertexAttrib1f_remap_index]
#define _gloffset_VertexAttrib1fv driDispatchRemapTable[VertexAttrib1fv_remap_index]
#define _gloffset_VertexAttrib2f driDispatchRemapTable[VertexAttrib2f_remap_index]
#define _gloffset_VertexAttrib2fv driDispatchRemapTable[VertexAttrib2fv_remap_index]
#define _gloffset_VertexAttrib3f driDispatchRemapTable[VertexAttrib3f_remap_index]
#define _gloffset_VertexAttrib3fv driDispatchRemapTable[VertexAttrib3fv_remap_index]
#define _gloffset_VertexAttrib4f driDispatchRemapTable[VertexAttrib4f_remap_index]
#define _gloffset_VertexAttrib4fv driDispatchRemapTable[VertexAttrib4fv_remap_index]
#define _gloffset_VertexAttribPointer driDispatchRemapTable[VertexAttribPointer_remap_index]
#define _gloffset_BlendFuncSeparate driDispatchRemapTable[BlendFuncSeparate_remap_index]
#define _gloffset_BindFramebuffer driDispatchRemapTable[BindFramebuffer_remap_index]
#define _gloffset_BindRenderbuffer driDispatchRemapTable[BindRenderbuffer_remap_index]
#define _gloffset_CheckFramebufferStatus driDispatchRemapTable[CheckFramebufferStatus_remap_index]
#define _gloffset_ClearDepthf driDispatchRemapTable[ClearDepthf_remap_index]
#define _gloffset_DeleteFramebuffers driDispatchRemapTable[DeleteFramebuffers_remap_index]
#define _gloffset_DeleteRenderbuffers driDispatchRemapTable[DeleteRenderbuffers_remap_index]
#define _gloffset_DepthRangef driDispatchRemapTable[DepthRangef_remap_index]
#define _gloffset_FramebufferRenderbuffer driDispatchRemapTable[FramebufferRenderbuffer_remap_index]
#define _gloffset_FramebufferTexture2D driDispatchRemapTable[FramebufferTexture2D_remap_index]
#define _gloffset_GenFramebuffers driDispatchRemapTable[GenFramebuffers_remap_index]
#define _gloffset_GenRenderbuffers driDispatchRemapTable[GenRenderbuffers_remap_index]
#define _gloffset_GenerateMipmap driDispatchRemapTable[GenerateMipmap_remap_index]
#define _gloffset_GetFramebufferAttachmentParameteriv driDispatchRemapTable[GetFramebufferAttachmentParameteriv_remap_index]
#define _gloffset_GetRenderbufferParameteriv driDispatchRemapTable[GetRenderbufferParameteriv_remap_index]
#define _gloffset_GetShaderPrecisionFormat driDispatchRemapTable[GetShaderPrecisionFormat_remap_index]
#define _gloffset_IsFramebuffer driDispatchRemapTable[IsFramebuffer_remap_index]
#define _gloffset_IsRenderbuffer driDispatchRemapTable[IsRenderbuffer_remap_index]
#define _gloffset_ReleaseShaderCompiler driDispatchRemapTable[ReleaseShaderCompiler_remap_index]
#define _gloffset_RenderbufferStorage driDispatchRemapTable[RenderbufferStorage_remap_index]
#define _gloffset_ShaderBinary driDispatchRemapTable[ShaderBinary_remap_index]

#endif /* _GLAPI_USE_REMAP_TABLE */

#define CALL_NewList(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLenum)), _gloffset_NewList, parameters)
#define GET_NewList(disp) GET_by_offset(disp, _gloffset_NewList)
#define SET_NewList(disp, fn) SET_by_offset(disp, _gloffset_NewList, fn)
#define CALL_EndList(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_EndList, parameters)
#define GET_EndList(disp) GET_by_offset(disp, _gloffset_EndList)
#define SET_EndList(disp, fn) SET_by_offset(disp, _gloffset_EndList, fn)
#define CALL_CallList(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_CallList, parameters)
#define GET_CallList(disp) GET_by_offset(disp, _gloffset_CallList)
#define SET_CallList(disp, fn) SET_by_offset(disp, _gloffset_CallList, fn)
#define CALL_CallLists(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLenum, const GLvoid *)), _gloffset_CallLists, parameters)
#define GET_CallLists(disp) GET_by_offset(disp, _gloffset_CallLists)
#define SET_CallLists(disp, fn) SET_by_offset(disp, _gloffset_CallLists, fn)
#define CALL_DeleteLists(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLsizei)), _gloffset_DeleteLists, parameters)
#define GET_DeleteLists(disp) GET_by_offset(disp, _gloffset_DeleteLists)
#define SET_DeleteLists(disp, fn) SET_by_offset(disp, _gloffset_DeleteLists, fn)
#define CALL_GenLists(disp, parameters) CALL_by_offset(disp, (GLuint (GLAPIENTRYP)(GLsizei)), _gloffset_GenLists, parameters)
#define GET_GenLists(disp) GET_by_offset(disp, _gloffset_GenLists)
#define SET_GenLists(disp, fn) SET_by_offset(disp, _gloffset_GenLists, fn)
#define CALL_ListBase(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_ListBase, parameters)
#define GET_ListBase(disp) GET_by_offset(disp, _gloffset_ListBase)
#define SET_ListBase(disp, fn) SET_by_offset(disp, _gloffset_ListBase, fn)
#define CALL_Begin(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_Begin, parameters)
#define GET_Begin(disp) GET_by_offset(disp, _gloffset_Begin)
#define SET_Begin(disp, fn) SET_by_offset(disp, _gloffset_Begin, fn)
#define CALL_Bitmap(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLsizei, GLfloat, GLfloat, GLfloat, GLfloat, const GLubyte *)), _gloffset_Bitmap, parameters)
#define GET_Bitmap(disp) GET_by_offset(disp, _gloffset_Bitmap)
#define SET_Bitmap(disp, fn) SET_by_offset(disp, _gloffset_Bitmap, fn)
#define CALL_Color3b(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLbyte, GLbyte, GLbyte)), _gloffset_Color3b, parameters)
#define GET_Color3b(disp) GET_by_offset(disp, _gloffset_Color3b)
#define SET_Color3b(disp, fn) SET_by_offset(disp, _gloffset_Color3b, fn)
#define CALL_Color3bv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLbyte *)), _gloffset_Color3bv, parameters)
#define GET_Color3bv(disp) GET_by_offset(disp, _gloffset_Color3bv)
#define SET_Color3bv(disp, fn) SET_by_offset(disp, _gloffset_Color3bv, fn)
#define CALL_Color3d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble)), _gloffset_Color3d, parameters)
#define GET_Color3d(disp) GET_by_offset(disp, _gloffset_Color3d)
#define SET_Color3d(disp, fn) SET_by_offset(disp, _gloffset_Color3d, fn)
#define CALL_Color3dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_Color3dv, parameters)
#define GET_Color3dv(disp) GET_by_offset(disp, _gloffset_Color3dv)
#define SET_Color3dv(disp, fn) SET_by_offset(disp, _gloffset_Color3dv, fn)
#define CALL_Color3f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat)), _gloffset_Color3f, parameters)
#define GET_Color3f(disp) GET_by_offset(disp, _gloffset_Color3f)
#define SET_Color3f(disp, fn) SET_by_offset(disp, _gloffset_Color3f, fn)
#define CALL_Color3fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_Color3fv, parameters)
#define GET_Color3fv(disp) GET_by_offset(disp, _gloffset_Color3fv)
#define SET_Color3fv(disp, fn) SET_by_offset(disp, _gloffset_Color3fv, fn)
#define CALL_Color3i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint)), _gloffset_Color3i, parameters)
#define GET_Color3i(disp) GET_by_offset(disp, _gloffset_Color3i)
#define SET_Color3i(disp, fn) SET_by_offset(disp, _gloffset_Color3i, fn)
#define CALL_Color3iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_Color3iv, parameters)
#define GET_Color3iv(disp) GET_by_offset(disp, _gloffset_Color3iv)
#define SET_Color3iv(disp, fn) SET_by_offset(disp, _gloffset_Color3iv, fn)
#define CALL_Color3s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort)), _gloffset_Color3s, parameters)
#define GET_Color3s(disp) GET_by_offset(disp, _gloffset_Color3s)
#define SET_Color3s(disp, fn) SET_by_offset(disp, _gloffset_Color3s, fn)
#define CALL_Color3sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_Color3sv, parameters)
#define GET_Color3sv(disp) GET_by_offset(disp, _gloffset_Color3sv)
#define SET_Color3sv(disp, fn) SET_by_offset(disp, _gloffset_Color3sv, fn)
#define CALL_Color3ub(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLubyte, GLubyte, GLubyte)), _gloffset_Color3ub, parameters)
#define GET_Color3ub(disp) GET_by_offset(disp, _gloffset_Color3ub)
#define SET_Color3ub(disp, fn) SET_by_offset(disp, _gloffset_Color3ub, fn)
#define CALL_Color3ubv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLubyte *)), _gloffset_Color3ubv, parameters)
#define GET_Color3ubv(disp) GET_by_offset(disp, _gloffset_Color3ubv)
#define SET_Color3ubv(disp, fn) SET_by_offset(disp, _gloffset_Color3ubv, fn)
#define CALL_Color3ui(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLuint, GLuint)), _gloffset_Color3ui, parameters)
#define GET_Color3ui(disp) GET_by_offset(disp, _gloffset_Color3ui)
#define SET_Color3ui(disp, fn) SET_by_offset(disp, _gloffset_Color3ui, fn)
#define CALL_Color3uiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLuint *)), _gloffset_Color3uiv, parameters)
#define GET_Color3uiv(disp) GET_by_offset(disp, _gloffset_Color3uiv)
#define SET_Color3uiv(disp, fn) SET_by_offset(disp, _gloffset_Color3uiv, fn)
#define CALL_Color3us(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLushort, GLushort, GLushort)), _gloffset_Color3us, parameters)
#define GET_Color3us(disp) GET_by_offset(disp, _gloffset_Color3us)
#define SET_Color3us(disp, fn) SET_by_offset(disp, _gloffset_Color3us, fn)
#define CALL_Color3usv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLushort *)), _gloffset_Color3usv, parameters)
#define GET_Color3usv(disp) GET_by_offset(disp, _gloffset_Color3usv)
#define SET_Color3usv(disp, fn) SET_by_offset(disp, _gloffset_Color3usv, fn)
#define CALL_Color4b(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLbyte, GLbyte, GLbyte, GLbyte)), _gloffset_Color4b, parameters)
#define GET_Color4b(disp) GET_by_offset(disp, _gloffset_Color4b)
#define SET_Color4b(disp, fn) SET_by_offset(disp, _gloffset_Color4b, fn)
#define CALL_Color4bv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLbyte *)), _gloffset_Color4bv, parameters)
#define GET_Color4bv(disp) GET_by_offset(disp, _gloffset_Color4bv)
#define SET_Color4bv(disp, fn) SET_by_offset(disp, _gloffset_Color4bv, fn)
#define CALL_Color4d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble, GLdouble)), _gloffset_Color4d, parameters)
#define GET_Color4d(disp) GET_by_offset(disp, _gloffset_Color4d)
#define SET_Color4d(disp, fn) SET_by_offset(disp, _gloffset_Color4d, fn)
#define CALL_Color4dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_Color4dv, parameters)
#define GET_Color4dv(disp) GET_by_offset(disp, _gloffset_Color4dv)
#define SET_Color4dv(disp, fn) SET_by_offset(disp, _gloffset_Color4dv, fn)
#define CALL_Color4f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat)), _gloffset_Color4f, parameters)
#define GET_Color4f(disp) GET_by_offset(disp, _gloffset_Color4f)
#define SET_Color4f(disp, fn) SET_by_offset(disp, _gloffset_Color4f, fn)
#define CALL_Color4fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_Color4fv, parameters)
#define GET_Color4fv(disp) GET_by_offset(disp, _gloffset_Color4fv)
#define SET_Color4fv(disp, fn) SET_by_offset(disp, _gloffset_Color4fv, fn)
#define CALL_Color4i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint, GLint)), _gloffset_Color4i, parameters)
#define GET_Color4i(disp) GET_by_offset(disp, _gloffset_Color4i)
#define SET_Color4i(disp, fn) SET_by_offset(disp, _gloffset_Color4i, fn)
#define CALL_Color4iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_Color4iv, parameters)
#define GET_Color4iv(disp) GET_by_offset(disp, _gloffset_Color4iv)
#define SET_Color4iv(disp, fn) SET_by_offset(disp, _gloffset_Color4iv, fn)
#define CALL_Color4s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort, GLshort)), _gloffset_Color4s, parameters)
#define GET_Color4s(disp) GET_by_offset(disp, _gloffset_Color4s)
#define SET_Color4s(disp, fn) SET_by_offset(disp, _gloffset_Color4s, fn)
#define CALL_Color4sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_Color4sv, parameters)
#define GET_Color4sv(disp) GET_by_offset(disp, _gloffset_Color4sv)
#define SET_Color4sv(disp, fn) SET_by_offset(disp, _gloffset_Color4sv, fn)
#define CALL_Color4ub(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLubyte, GLubyte, GLubyte, GLubyte)), _gloffset_Color4ub, parameters)
#define GET_Color4ub(disp) GET_by_offset(disp, _gloffset_Color4ub)
#define SET_Color4ub(disp, fn) SET_by_offset(disp, _gloffset_Color4ub, fn)
#define CALL_Color4ubv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLubyte *)), _gloffset_Color4ubv, parameters)
#define GET_Color4ubv(disp) GET_by_offset(disp, _gloffset_Color4ubv)
#define SET_Color4ubv(disp, fn) SET_by_offset(disp, _gloffset_Color4ubv, fn)
#define CALL_Color4ui(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLuint, GLuint, GLuint)), _gloffset_Color4ui, parameters)
#define GET_Color4ui(disp) GET_by_offset(disp, _gloffset_Color4ui)
#define SET_Color4ui(disp, fn) SET_by_offset(disp, _gloffset_Color4ui, fn)
#define CALL_Color4uiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLuint *)), _gloffset_Color4uiv, parameters)
#define GET_Color4uiv(disp) GET_by_offset(disp, _gloffset_Color4uiv)
#define SET_Color4uiv(disp, fn) SET_by_offset(disp, _gloffset_Color4uiv, fn)
#define CALL_Color4us(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLushort, GLushort, GLushort, GLushort)), _gloffset_Color4us, parameters)
#define GET_Color4us(disp) GET_by_offset(disp, _gloffset_Color4us)
#define SET_Color4us(disp, fn) SET_by_offset(disp, _gloffset_Color4us, fn)
#define CALL_Color4usv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLushort *)), _gloffset_Color4usv, parameters)
#define GET_Color4usv(disp) GET_by_offset(disp, _gloffset_Color4usv)
#define SET_Color4usv(disp, fn) SET_by_offset(disp, _gloffset_Color4usv, fn)
#define CALL_EdgeFlag(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLboolean)), _gloffset_EdgeFlag, parameters)
#define GET_EdgeFlag(disp) GET_by_offset(disp, _gloffset_EdgeFlag)
#define SET_EdgeFlag(disp, fn) SET_by_offset(disp, _gloffset_EdgeFlag, fn)
#define CALL_EdgeFlagv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLboolean *)), _gloffset_EdgeFlagv, parameters)
#define GET_EdgeFlagv(disp) GET_by_offset(disp, _gloffset_EdgeFlagv)
#define SET_EdgeFlagv(disp, fn) SET_by_offset(disp, _gloffset_EdgeFlagv, fn)
#define CALL_End(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_End, parameters)
#define GET_End(disp) GET_by_offset(disp, _gloffset_End)
#define SET_End(disp, fn) SET_by_offset(disp, _gloffset_End, fn)
#define CALL_Indexd(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble)), _gloffset_Indexd, parameters)
#define GET_Indexd(disp) GET_by_offset(disp, _gloffset_Indexd)
#define SET_Indexd(disp, fn) SET_by_offset(disp, _gloffset_Indexd, fn)
#define CALL_Indexdv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_Indexdv, parameters)
#define GET_Indexdv(disp) GET_by_offset(disp, _gloffset_Indexdv)
#define SET_Indexdv(disp, fn) SET_by_offset(disp, _gloffset_Indexdv, fn)
#define CALL_Indexf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat)), _gloffset_Indexf, parameters)
#define GET_Indexf(disp) GET_by_offset(disp, _gloffset_Indexf)
#define SET_Indexf(disp, fn) SET_by_offset(disp, _gloffset_Indexf, fn)
#define CALL_Indexfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_Indexfv, parameters)
#define GET_Indexfv(disp) GET_by_offset(disp, _gloffset_Indexfv)
#define SET_Indexfv(disp, fn) SET_by_offset(disp, _gloffset_Indexfv, fn)
#define CALL_Indexi(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint)), _gloffset_Indexi, parameters)
#define GET_Indexi(disp) GET_by_offset(disp, _gloffset_Indexi)
#define SET_Indexi(disp, fn) SET_by_offset(disp, _gloffset_Indexi, fn)
#define CALL_Indexiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_Indexiv, parameters)
#define GET_Indexiv(disp) GET_by_offset(disp, _gloffset_Indexiv)
#define SET_Indexiv(disp, fn) SET_by_offset(disp, _gloffset_Indexiv, fn)
#define CALL_Indexs(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort)), _gloffset_Indexs, parameters)
#define GET_Indexs(disp) GET_by_offset(disp, _gloffset_Indexs)
#define SET_Indexs(disp, fn) SET_by_offset(disp, _gloffset_Indexs, fn)
#define CALL_Indexsv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_Indexsv, parameters)
#define GET_Indexsv(disp) GET_by_offset(disp, _gloffset_Indexsv)
#define SET_Indexsv(disp, fn) SET_by_offset(disp, _gloffset_Indexsv, fn)
#define CALL_Normal3b(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLbyte, GLbyte, GLbyte)), _gloffset_Normal3b, parameters)
#define GET_Normal3b(disp) GET_by_offset(disp, _gloffset_Normal3b)
#define SET_Normal3b(disp, fn) SET_by_offset(disp, _gloffset_Normal3b, fn)
#define CALL_Normal3bv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLbyte *)), _gloffset_Normal3bv, parameters)
#define GET_Normal3bv(disp) GET_by_offset(disp, _gloffset_Normal3bv)
#define SET_Normal3bv(disp, fn) SET_by_offset(disp, _gloffset_Normal3bv, fn)
#define CALL_Normal3d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble)), _gloffset_Normal3d, parameters)
#define GET_Normal3d(disp) GET_by_offset(disp, _gloffset_Normal3d)
#define SET_Normal3d(disp, fn) SET_by_offset(disp, _gloffset_Normal3d, fn)
#define CALL_Normal3dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_Normal3dv, parameters)
#define GET_Normal3dv(disp) GET_by_offset(disp, _gloffset_Normal3dv)
#define SET_Normal3dv(disp, fn) SET_by_offset(disp, _gloffset_Normal3dv, fn)
#define CALL_Normal3f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat)), _gloffset_Normal3f, parameters)
#define GET_Normal3f(disp) GET_by_offset(disp, _gloffset_Normal3f)
#define SET_Normal3f(disp, fn) SET_by_offset(disp, _gloffset_Normal3f, fn)
#define CALL_Normal3fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_Normal3fv, parameters)
#define GET_Normal3fv(disp) GET_by_offset(disp, _gloffset_Normal3fv)
#define SET_Normal3fv(disp, fn) SET_by_offset(disp, _gloffset_Normal3fv, fn)
#define CALL_Normal3i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint)), _gloffset_Normal3i, parameters)
#define GET_Normal3i(disp) GET_by_offset(disp, _gloffset_Normal3i)
#define SET_Normal3i(disp, fn) SET_by_offset(disp, _gloffset_Normal3i, fn)
#define CALL_Normal3iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_Normal3iv, parameters)
#define GET_Normal3iv(disp) GET_by_offset(disp, _gloffset_Normal3iv)
#define SET_Normal3iv(disp, fn) SET_by_offset(disp, _gloffset_Normal3iv, fn)
#define CALL_Normal3s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort)), _gloffset_Normal3s, parameters)
#define GET_Normal3s(disp) GET_by_offset(disp, _gloffset_Normal3s)
#define SET_Normal3s(disp, fn) SET_by_offset(disp, _gloffset_Normal3s, fn)
#define CALL_Normal3sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_Normal3sv, parameters)
#define GET_Normal3sv(disp) GET_by_offset(disp, _gloffset_Normal3sv)
#define SET_Normal3sv(disp, fn) SET_by_offset(disp, _gloffset_Normal3sv, fn)
#define CALL_RasterPos2d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble)), _gloffset_RasterPos2d, parameters)
#define GET_RasterPos2d(disp) GET_by_offset(disp, _gloffset_RasterPos2d)
#define SET_RasterPos2d(disp, fn) SET_by_offset(disp, _gloffset_RasterPos2d, fn)
#define CALL_RasterPos2dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_RasterPos2dv, parameters)
#define GET_RasterPos2dv(disp) GET_by_offset(disp, _gloffset_RasterPos2dv)
#define SET_RasterPos2dv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos2dv, fn)
#define CALL_RasterPos2f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat)), _gloffset_RasterPos2f, parameters)
#define GET_RasterPos2f(disp) GET_by_offset(disp, _gloffset_RasterPos2f)
#define SET_RasterPos2f(disp, fn) SET_by_offset(disp, _gloffset_RasterPos2f, fn)
#define CALL_RasterPos2fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_RasterPos2fv, parameters)
#define GET_RasterPos2fv(disp) GET_by_offset(disp, _gloffset_RasterPos2fv)
#define SET_RasterPos2fv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos2fv, fn)
#define CALL_RasterPos2i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint)), _gloffset_RasterPos2i, parameters)
#define GET_RasterPos2i(disp) GET_by_offset(disp, _gloffset_RasterPos2i)
#define SET_RasterPos2i(disp, fn) SET_by_offset(disp, _gloffset_RasterPos2i, fn)
#define CALL_RasterPos2iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_RasterPos2iv, parameters)
#define GET_RasterPos2iv(disp) GET_by_offset(disp, _gloffset_RasterPos2iv)
#define SET_RasterPos2iv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos2iv, fn)
#define CALL_RasterPos2s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort)), _gloffset_RasterPos2s, parameters)
#define GET_RasterPos2s(disp) GET_by_offset(disp, _gloffset_RasterPos2s)
#define SET_RasterPos2s(disp, fn) SET_by_offset(disp, _gloffset_RasterPos2s, fn)
#define CALL_RasterPos2sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_RasterPos2sv, parameters)
#define GET_RasterPos2sv(disp) GET_by_offset(disp, _gloffset_RasterPos2sv)
#define SET_RasterPos2sv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos2sv, fn)
#define CALL_RasterPos3d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble)), _gloffset_RasterPos3d, parameters)
#define GET_RasterPos3d(disp) GET_by_offset(disp, _gloffset_RasterPos3d)
#define SET_RasterPos3d(disp, fn) SET_by_offset(disp, _gloffset_RasterPos3d, fn)
#define CALL_RasterPos3dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_RasterPos3dv, parameters)
#define GET_RasterPos3dv(disp) GET_by_offset(disp, _gloffset_RasterPos3dv)
#define SET_RasterPos3dv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos3dv, fn)
#define CALL_RasterPos3f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat)), _gloffset_RasterPos3f, parameters)
#define GET_RasterPos3f(disp) GET_by_offset(disp, _gloffset_RasterPos3f)
#define SET_RasterPos3f(disp, fn) SET_by_offset(disp, _gloffset_RasterPos3f, fn)
#define CALL_RasterPos3fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_RasterPos3fv, parameters)
#define GET_RasterPos3fv(disp) GET_by_offset(disp, _gloffset_RasterPos3fv)
#define SET_RasterPos3fv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos3fv, fn)
#define CALL_RasterPos3i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint)), _gloffset_RasterPos3i, parameters)
#define GET_RasterPos3i(disp) GET_by_offset(disp, _gloffset_RasterPos3i)
#define SET_RasterPos3i(disp, fn) SET_by_offset(disp, _gloffset_RasterPos3i, fn)
#define CALL_RasterPos3iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_RasterPos3iv, parameters)
#define GET_RasterPos3iv(disp) GET_by_offset(disp, _gloffset_RasterPos3iv)
#define SET_RasterPos3iv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos3iv, fn)
#define CALL_RasterPos3s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort)), _gloffset_RasterPos3s, parameters)
#define GET_RasterPos3s(disp) GET_by_offset(disp, _gloffset_RasterPos3s)
#define SET_RasterPos3s(disp, fn) SET_by_offset(disp, _gloffset_RasterPos3s, fn)
#define CALL_RasterPos3sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_RasterPos3sv, parameters)
#define GET_RasterPos3sv(disp) GET_by_offset(disp, _gloffset_RasterPos3sv)
#define SET_RasterPos3sv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos3sv, fn)
#define CALL_RasterPos4d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble, GLdouble)), _gloffset_RasterPos4d, parameters)
#define GET_RasterPos4d(disp) GET_by_offset(disp, _gloffset_RasterPos4d)
#define SET_RasterPos4d(disp, fn) SET_by_offset(disp, _gloffset_RasterPos4d, fn)
#define CALL_RasterPos4dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_RasterPos4dv, parameters)
#define GET_RasterPos4dv(disp) GET_by_offset(disp, _gloffset_RasterPos4dv)
#define SET_RasterPos4dv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos4dv, fn)
#define CALL_RasterPos4f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat)), _gloffset_RasterPos4f, parameters)
#define GET_RasterPos4f(disp) GET_by_offset(disp, _gloffset_RasterPos4f)
#define SET_RasterPos4f(disp, fn) SET_by_offset(disp, _gloffset_RasterPos4f, fn)
#define CALL_RasterPos4fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_RasterPos4fv, parameters)
#define GET_RasterPos4fv(disp) GET_by_offset(disp, _gloffset_RasterPos4fv)
#define SET_RasterPos4fv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos4fv, fn)
#define CALL_RasterPos4i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint, GLint)), _gloffset_RasterPos4i, parameters)
#define GET_RasterPos4i(disp) GET_by_offset(disp, _gloffset_RasterPos4i)
#define SET_RasterPos4i(disp, fn) SET_by_offset(disp, _gloffset_RasterPos4i, fn)
#define CALL_RasterPos4iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_RasterPos4iv, parameters)
#define GET_RasterPos4iv(disp) GET_by_offset(disp, _gloffset_RasterPos4iv)
#define SET_RasterPos4iv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos4iv, fn)
#define CALL_RasterPos4s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort, GLshort)), _gloffset_RasterPos4s, parameters)
#define GET_RasterPos4s(disp) GET_by_offset(disp, _gloffset_RasterPos4s)
#define SET_RasterPos4s(disp, fn) SET_by_offset(disp, _gloffset_RasterPos4s, fn)
#define CALL_RasterPos4sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_RasterPos4sv, parameters)
#define GET_RasterPos4sv(disp) GET_by_offset(disp, _gloffset_RasterPos4sv)
#define SET_RasterPos4sv(disp, fn) SET_by_offset(disp, _gloffset_RasterPos4sv, fn)
#define CALL_Rectd(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble, GLdouble)), _gloffset_Rectd, parameters)
#define GET_Rectd(disp) GET_by_offset(disp, _gloffset_Rectd)
#define SET_Rectd(disp, fn) SET_by_offset(disp, _gloffset_Rectd, fn)
#define CALL_Rectdv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *, const GLdouble *)), _gloffset_Rectdv, parameters)
#define GET_Rectdv(disp) GET_by_offset(disp, _gloffset_Rectdv)
#define SET_Rectdv(disp, fn) SET_by_offset(disp, _gloffset_Rectdv, fn)
#define CALL_Rectf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat)), _gloffset_Rectf, parameters)
#define GET_Rectf(disp) GET_by_offset(disp, _gloffset_Rectf)
#define SET_Rectf(disp, fn) SET_by_offset(disp, _gloffset_Rectf, fn)
#define CALL_Rectfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *, const GLfloat *)), _gloffset_Rectfv, parameters)
#define GET_Rectfv(disp) GET_by_offset(disp, _gloffset_Rectfv)
#define SET_Rectfv(disp, fn) SET_by_offset(disp, _gloffset_Rectfv, fn)
#define CALL_Recti(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint, GLint)), _gloffset_Recti, parameters)
#define GET_Recti(disp) GET_by_offset(disp, _gloffset_Recti)
#define SET_Recti(disp, fn) SET_by_offset(disp, _gloffset_Recti, fn)
#define CALL_Rectiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *, const GLint *)), _gloffset_Rectiv, parameters)
#define GET_Rectiv(disp) GET_by_offset(disp, _gloffset_Rectiv)
#define SET_Rectiv(disp, fn) SET_by_offset(disp, _gloffset_Rectiv, fn)
#define CALL_Rects(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort, GLshort)), _gloffset_Rects, parameters)
#define GET_Rects(disp) GET_by_offset(disp, _gloffset_Rects)
#define SET_Rects(disp, fn) SET_by_offset(disp, _gloffset_Rects, fn)
#define CALL_Rectsv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *, const GLshort *)), _gloffset_Rectsv, parameters)
#define GET_Rectsv(disp) GET_by_offset(disp, _gloffset_Rectsv)
#define SET_Rectsv(disp, fn) SET_by_offset(disp, _gloffset_Rectsv, fn)
#define CALL_TexCoord1d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble)), _gloffset_TexCoord1d, parameters)
#define GET_TexCoord1d(disp) GET_by_offset(disp, _gloffset_TexCoord1d)
#define SET_TexCoord1d(disp, fn) SET_by_offset(disp, _gloffset_TexCoord1d, fn)
#define CALL_TexCoord1dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_TexCoord1dv, parameters)
#define GET_TexCoord1dv(disp) GET_by_offset(disp, _gloffset_TexCoord1dv)
#define SET_TexCoord1dv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord1dv, fn)
#define CALL_TexCoord1f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat)), _gloffset_TexCoord1f, parameters)
#define GET_TexCoord1f(disp) GET_by_offset(disp, _gloffset_TexCoord1f)
#define SET_TexCoord1f(disp, fn) SET_by_offset(disp, _gloffset_TexCoord1f, fn)
#define CALL_TexCoord1fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_TexCoord1fv, parameters)
#define GET_TexCoord1fv(disp) GET_by_offset(disp, _gloffset_TexCoord1fv)
#define SET_TexCoord1fv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord1fv, fn)
#define CALL_TexCoord1i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint)), _gloffset_TexCoord1i, parameters)
#define GET_TexCoord1i(disp) GET_by_offset(disp, _gloffset_TexCoord1i)
#define SET_TexCoord1i(disp, fn) SET_by_offset(disp, _gloffset_TexCoord1i, fn)
#define CALL_TexCoord1iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_TexCoord1iv, parameters)
#define GET_TexCoord1iv(disp) GET_by_offset(disp, _gloffset_TexCoord1iv)
#define SET_TexCoord1iv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord1iv, fn)
#define CALL_TexCoord1s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort)), _gloffset_TexCoord1s, parameters)
#define GET_TexCoord1s(disp) GET_by_offset(disp, _gloffset_TexCoord1s)
#define SET_TexCoord1s(disp, fn) SET_by_offset(disp, _gloffset_TexCoord1s, fn)
#define CALL_TexCoord1sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_TexCoord1sv, parameters)
#define GET_TexCoord1sv(disp) GET_by_offset(disp, _gloffset_TexCoord1sv)
#define SET_TexCoord1sv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord1sv, fn)
#define CALL_TexCoord2d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble)), _gloffset_TexCoord2d, parameters)
#define GET_TexCoord2d(disp) GET_by_offset(disp, _gloffset_TexCoord2d)
#define SET_TexCoord2d(disp, fn) SET_by_offset(disp, _gloffset_TexCoord2d, fn)
#define CALL_TexCoord2dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_TexCoord2dv, parameters)
#define GET_TexCoord2dv(disp) GET_by_offset(disp, _gloffset_TexCoord2dv)
#define SET_TexCoord2dv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord2dv, fn)
#define CALL_TexCoord2f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat)), _gloffset_TexCoord2f, parameters)
#define GET_TexCoord2f(disp) GET_by_offset(disp, _gloffset_TexCoord2f)
#define SET_TexCoord2f(disp, fn) SET_by_offset(disp, _gloffset_TexCoord2f, fn)
#define CALL_TexCoord2fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_TexCoord2fv, parameters)
#define GET_TexCoord2fv(disp) GET_by_offset(disp, _gloffset_TexCoord2fv)
#define SET_TexCoord2fv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord2fv, fn)
#define CALL_TexCoord2i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint)), _gloffset_TexCoord2i, parameters)
#define GET_TexCoord2i(disp) GET_by_offset(disp, _gloffset_TexCoord2i)
#define SET_TexCoord2i(disp, fn) SET_by_offset(disp, _gloffset_TexCoord2i, fn)
#define CALL_TexCoord2iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_TexCoord2iv, parameters)
#define GET_TexCoord2iv(disp) GET_by_offset(disp, _gloffset_TexCoord2iv)
#define SET_TexCoord2iv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord2iv, fn)
#define CALL_TexCoord2s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort)), _gloffset_TexCoord2s, parameters)
#define GET_TexCoord2s(disp) GET_by_offset(disp, _gloffset_TexCoord2s)
#define SET_TexCoord2s(disp, fn) SET_by_offset(disp, _gloffset_TexCoord2s, fn)
#define CALL_TexCoord2sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_TexCoord2sv, parameters)
#define GET_TexCoord2sv(disp) GET_by_offset(disp, _gloffset_TexCoord2sv)
#define SET_TexCoord2sv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord2sv, fn)
#define CALL_TexCoord3d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble)), _gloffset_TexCoord3d, parameters)
#define GET_TexCoord3d(disp) GET_by_offset(disp, _gloffset_TexCoord3d)
#define SET_TexCoord3d(disp, fn) SET_by_offset(disp, _gloffset_TexCoord3d, fn)
#define CALL_TexCoord3dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_TexCoord3dv, parameters)
#define GET_TexCoord3dv(disp) GET_by_offset(disp, _gloffset_TexCoord3dv)
#define SET_TexCoord3dv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord3dv, fn)
#define CALL_TexCoord3f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat)), _gloffset_TexCoord3f, parameters)
#define GET_TexCoord3f(disp) GET_by_offset(disp, _gloffset_TexCoord3f)
#define SET_TexCoord3f(disp, fn) SET_by_offset(disp, _gloffset_TexCoord3f, fn)
#define CALL_TexCoord3fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_TexCoord3fv, parameters)
#define GET_TexCoord3fv(disp) GET_by_offset(disp, _gloffset_TexCoord3fv)
#define SET_TexCoord3fv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord3fv, fn)
#define CALL_TexCoord3i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint)), _gloffset_TexCoord3i, parameters)
#define GET_TexCoord3i(disp) GET_by_offset(disp, _gloffset_TexCoord3i)
#define SET_TexCoord3i(disp, fn) SET_by_offset(disp, _gloffset_TexCoord3i, fn)
#define CALL_TexCoord3iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_TexCoord3iv, parameters)
#define GET_TexCoord3iv(disp) GET_by_offset(disp, _gloffset_TexCoord3iv)
#define SET_TexCoord3iv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord3iv, fn)
#define CALL_TexCoord3s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort)), _gloffset_TexCoord3s, parameters)
#define GET_TexCoord3s(disp) GET_by_offset(disp, _gloffset_TexCoord3s)
#define SET_TexCoord3s(disp, fn) SET_by_offset(disp, _gloffset_TexCoord3s, fn)
#define CALL_TexCoord3sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_TexCoord3sv, parameters)
#define GET_TexCoord3sv(disp) GET_by_offset(disp, _gloffset_TexCoord3sv)
#define SET_TexCoord3sv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord3sv, fn)
#define CALL_TexCoord4d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble, GLdouble)), _gloffset_TexCoord4d, parameters)
#define GET_TexCoord4d(disp) GET_by_offset(disp, _gloffset_TexCoord4d)
#define SET_TexCoord4d(disp, fn) SET_by_offset(disp, _gloffset_TexCoord4d, fn)
#define CALL_TexCoord4dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_TexCoord4dv, parameters)
#define GET_TexCoord4dv(disp) GET_by_offset(disp, _gloffset_TexCoord4dv)
#define SET_TexCoord4dv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord4dv, fn)
#define CALL_TexCoord4f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat)), _gloffset_TexCoord4f, parameters)
#define GET_TexCoord4f(disp) GET_by_offset(disp, _gloffset_TexCoord4f)
#define SET_TexCoord4f(disp, fn) SET_by_offset(disp, _gloffset_TexCoord4f, fn)
#define CALL_TexCoord4fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_TexCoord4fv, parameters)
#define GET_TexCoord4fv(disp) GET_by_offset(disp, _gloffset_TexCoord4fv)
#define SET_TexCoord4fv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord4fv, fn)
#define CALL_TexCoord4i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint, GLint)), _gloffset_TexCoord4i, parameters)
#define GET_TexCoord4i(disp) GET_by_offset(disp, _gloffset_TexCoord4i)
#define SET_TexCoord4i(disp, fn) SET_by_offset(disp, _gloffset_TexCoord4i, fn)
#define CALL_TexCoord4iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_TexCoord4iv, parameters)
#define GET_TexCoord4iv(disp) GET_by_offset(disp, _gloffset_TexCoord4iv)
#define SET_TexCoord4iv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord4iv, fn)
#define CALL_TexCoord4s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort, GLshort)), _gloffset_TexCoord4s, parameters)
#define GET_TexCoord4s(disp) GET_by_offset(disp, _gloffset_TexCoord4s)
#define SET_TexCoord4s(disp, fn) SET_by_offset(disp, _gloffset_TexCoord4s, fn)
#define CALL_TexCoord4sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_TexCoord4sv, parameters)
#define GET_TexCoord4sv(disp) GET_by_offset(disp, _gloffset_TexCoord4sv)
#define SET_TexCoord4sv(disp, fn) SET_by_offset(disp, _gloffset_TexCoord4sv, fn)
#define CALL_Vertex2d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble)), _gloffset_Vertex2d, parameters)
#define GET_Vertex2d(disp) GET_by_offset(disp, _gloffset_Vertex2d)
#define SET_Vertex2d(disp, fn) SET_by_offset(disp, _gloffset_Vertex2d, fn)
#define CALL_Vertex2dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_Vertex2dv, parameters)
#define GET_Vertex2dv(disp) GET_by_offset(disp, _gloffset_Vertex2dv)
#define SET_Vertex2dv(disp, fn) SET_by_offset(disp, _gloffset_Vertex2dv, fn)
#define CALL_Vertex2f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat)), _gloffset_Vertex2f, parameters)
#define GET_Vertex2f(disp) GET_by_offset(disp, _gloffset_Vertex2f)
#define SET_Vertex2f(disp, fn) SET_by_offset(disp, _gloffset_Vertex2f, fn)
#define CALL_Vertex2fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_Vertex2fv, parameters)
#define GET_Vertex2fv(disp) GET_by_offset(disp, _gloffset_Vertex2fv)
#define SET_Vertex2fv(disp, fn) SET_by_offset(disp, _gloffset_Vertex2fv, fn)
#define CALL_Vertex2i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint)), _gloffset_Vertex2i, parameters)
#define GET_Vertex2i(disp) GET_by_offset(disp, _gloffset_Vertex2i)
#define SET_Vertex2i(disp, fn) SET_by_offset(disp, _gloffset_Vertex2i, fn)
#define CALL_Vertex2iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_Vertex2iv, parameters)
#define GET_Vertex2iv(disp) GET_by_offset(disp, _gloffset_Vertex2iv)
#define SET_Vertex2iv(disp, fn) SET_by_offset(disp, _gloffset_Vertex2iv, fn)
#define CALL_Vertex2s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort)), _gloffset_Vertex2s, parameters)
#define GET_Vertex2s(disp) GET_by_offset(disp, _gloffset_Vertex2s)
#define SET_Vertex2s(disp, fn) SET_by_offset(disp, _gloffset_Vertex2s, fn)
#define CALL_Vertex2sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_Vertex2sv, parameters)
#define GET_Vertex2sv(disp) GET_by_offset(disp, _gloffset_Vertex2sv)
#define SET_Vertex2sv(disp, fn) SET_by_offset(disp, _gloffset_Vertex2sv, fn)
#define CALL_Vertex3d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble)), _gloffset_Vertex3d, parameters)
#define GET_Vertex3d(disp) GET_by_offset(disp, _gloffset_Vertex3d)
#define SET_Vertex3d(disp, fn) SET_by_offset(disp, _gloffset_Vertex3d, fn)
#define CALL_Vertex3dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_Vertex3dv, parameters)
#define GET_Vertex3dv(disp) GET_by_offset(disp, _gloffset_Vertex3dv)
#define SET_Vertex3dv(disp, fn) SET_by_offset(disp, _gloffset_Vertex3dv, fn)
#define CALL_Vertex3f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat)), _gloffset_Vertex3f, parameters)
#define GET_Vertex3f(disp) GET_by_offset(disp, _gloffset_Vertex3f)
#define SET_Vertex3f(disp, fn) SET_by_offset(disp, _gloffset_Vertex3f, fn)
#define CALL_Vertex3fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_Vertex3fv, parameters)
#define GET_Vertex3fv(disp) GET_by_offset(disp, _gloffset_Vertex3fv)
#define SET_Vertex3fv(disp, fn) SET_by_offset(disp, _gloffset_Vertex3fv, fn)
#define CALL_Vertex3i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint)), _gloffset_Vertex3i, parameters)
#define GET_Vertex3i(disp) GET_by_offset(disp, _gloffset_Vertex3i)
#define SET_Vertex3i(disp, fn) SET_by_offset(disp, _gloffset_Vertex3i, fn)
#define CALL_Vertex3iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_Vertex3iv, parameters)
#define GET_Vertex3iv(disp) GET_by_offset(disp, _gloffset_Vertex3iv)
#define SET_Vertex3iv(disp, fn) SET_by_offset(disp, _gloffset_Vertex3iv, fn)
#define CALL_Vertex3s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort)), _gloffset_Vertex3s, parameters)
#define GET_Vertex3s(disp) GET_by_offset(disp, _gloffset_Vertex3s)
#define SET_Vertex3s(disp, fn) SET_by_offset(disp, _gloffset_Vertex3s, fn)
#define CALL_Vertex3sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_Vertex3sv, parameters)
#define GET_Vertex3sv(disp) GET_by_offset(disp, _gloffset_Vertex3sv)
#define SET_Vertex3sv(disp, fn) SET_by_offset(disp, _gloffset_Vertex3sv, fn)
#define CALL_Vertex4d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble, GLdouble)), _gloffset_Vertex4d, parameters)
#define GET_Vertex4d(disp) GET_by_offset(disp, _gloffset_Vertex4d)
#define SET_Vertex4d(disp, fn) SET_by_offset(disp, _gloffset_Vertex4d, fn)
#define CALL_Vertex4dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_Vertex4dv, parameters)
#define GET_Vertex4dv(disp) GET_by_offset(disp, _gloffset_Vertex4dv)
#define SET_Vertex4dv(disp, fn) SET_by_offset(disp, _gloffset_Vertex4dv, fn)
#define CALL_Vertex4f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat)), _gloffset_Vertex4f, parameters)
#define GET_Vertex4f(disp) GET_by_offset(disp, _gloffset_Vertex4f)
#define SET_Vertex4f(disp, fn) SET_by_offset(disp, _gloffset_Vertex4f, fn)
#define CALL_Vertex4fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_Vertex4fv, parameters)
#define GET_Vertex4fv(disp) GET_by_offset(disp, _gloffset_Vertex4fv)
#define SET_Vertex4fv(disp, fn) SET_by_offset(disp, _gloffset_Vertex4fv, fn)
#define CALL_Vertex4i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint, GLint)), _gloffset_Vertex4i, parameters)
#define GET_Vertex4i(disp) GET_by_offset(disp, _gloffset_Vertex4i)
#define SET_Vertex4i(disp, fn) SET_by_offset(disp, _gloffset_Vertex4i, fn)
#define CALL_Vertex4iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLint *)), _gloffset_Vertex4iv, parameters)
#define GET_Vertex4iv(disp) GET_by_offset(disp, _gloffset_Vertex4iv)
#define SET_Vertex4iv(disp, fn) SET_by_offset(disp, _gloffset_Vertex4iv, fn)
#define CALL_Vertex4s(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLshort, GLshort, GLshort, GLshort)), _gloffset_Vertex4s, parameters)
#define GET_Vertex4s(disp) GET_by_offset(disp, _gloffset_Vertex4s)
#define SET_Vertex4s(disp, fn) SET_by_offset(disp, _gloffset_Vertex4s, fn)
#define CALL_Vertex4sv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLshort *)), _gloffset_Vertex4sv, parameters)
#define GET_Vertex4sv(disp) GET_by_offset(disp, _gloffset_Vertex4sv)
#define SET_Vertex4sv(disp, fn) SET_by_offset(disp, _gloffset_Vertex4sv, fn)
#define CALL_ClipPlane(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLdouble *)), _gloffset_ClipPlane, parameters)
#define GET_ClipPlane(disp) GET_by_offset(disp, _gloffset_ClipPlane)
#define SET_ClipPlane(disp, fn) SET_by_offset(disp, _gloffset_ClipPlane, fn)
#define CALL_ColorMaterial(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum)), _gloffset_ColorMaterial, parameters)
#define GET_ColorMaterial(disp) GET_by_offset(disp, _gloffset_ColorMaterial)
#define SET_ColorMaterial(disp, fn) SET_by_offset(disp, _gloffset_ColorMaterial, fn)
#define CALL_CullFace(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_CullFace, parameters)
#define GET_CullFace(disp) GET_by_offset(disp, _gloffset_CullFace)
#define SET_CullFace(disp, fn) SET_by_offset(disp, _gloffset_CullFace, fn)
#define CALL_Fogf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat)), _gloffset_Fogf, parameters)
#define GET_Fogf(disp) GET_by_offset(disp, _gloffset_Fogf)
#define SET_Fogf(disp, fn) SET_by_offset(disp, _gloffset_Fogf, fn)
#define CALL_Fogfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfloat *)), _gloffset_Fogfv, parameters)
#define GET_Fogfv(disp) GET_by_offset(disp, _gloffset_Fogfv)
#define SET_Fogfv(disp, fn) SET_by_offset(disp, _gloffset_Fogfv, fn)
#define CALL_Fogi(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint)), _gloffset_Fogi, parameters)
#define GET_Fogi(disp) GET_by_offset(disp, _gloffset_Fogi)
#define SET_Fogi(disp, fn) SET_by_offset(disp, _gloffset_Fogi, fn)
#define CALL_Fogiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLint *)), _gloffset_Fogiv, parameters)
#define GET_Fogiv(disp) GET_by_offset(disp, _gloffset_Fogiv)
#define SET_Fogiv(disp, fn) SET_by_offset(disp, _gloffset_Fogiv, fn)
#define CALL_FrontFace(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_FrontFace, parameters)
#define GET_FrontFace(disp) GET_by_offset(disp, _gloffset_FrontFace)
#define SET_FrontFace(disp, fn) SET_by_offset(disp, _gloffset_FrontFace, fn)
#define CALL_Hint(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum)), _gloffset_Hint, parameters)
#define GET_Hint(disp) GET_by_offset(disp, _gloffset_Hint)
#define SET_Hint(disp, fn) SET_by_offset(disp, _gloffset_Hint, fn)
#define CALL_Lightf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), _gloffset_Lightf, parameters)
#define GET_Lightf(disp) GET_by_offset(disp, _gloffset_Lightf)
#define SET_Lightf(disp, fn) SET_by_offset(disp, _gloffset_Lightf, fn)
#define CALL_Lightfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), _gloffset_Lightfv, parameters)
#define GET_Lightfv(disp) GET_by_offset(disp, _gloffset_Lightfv)
#define SET_Lightfv(disp, fn) SET_by_offset(disp, _gloffset_Lightfv, fn)
#define CALL_Lighti(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint)), _gloffset_Lighti, parameters)
#define GET_Lighti(disp) GET_by_offset(disp, _gloffset_Lighti)
#define SET_Lighti(disp, fn) SET_by_offset(disp, _gloffset_Lighti, fn)
#define CALL_Lightiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLint *)), _gloffset_Lightiv, parameters)
#define GET_Lightiv(disp) GET_by_offset(disp, _gloffset_Lightiv)
#define SET_Lightiv(disp, fn) SET_by_offset(disp, _gloffset_Lightiv, fn)
#define CALL_LightModelf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat)), _gloffset_LightModelf, parameters)
#define GET_LightModelf(disp) GET_by_offset(disp, _gloffset_LightModelf)
#define SET_LightModelf(disp, fn) SET_by_offset(disp, _gloffset_LightModelf, fn)
#define CALL_LightModelfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfloat *)), _gloffset_LightModelfv, parameters)
#define GET_LightModelfv(disp) GET_by_offset(disp, _gloffset_LightModelfv)
#define SET_LightModelfv(disp, fn) SET_by_offset(disp, _gloffset_LightModelfv, fn)
#define CALL_LightModeli(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint)), _gloffset_LightModeli, parameters)
#define GET_LightModeli(disp) GET_by_offset(disp, _gloffset_LightModeli)
#define SET_LightModeli(disp, fn) SET_by_offset(disp, _gloffset_LightModeli, fn)
#define CALL_LightModeliv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLint *)), _gloffset_LightModeliv, parameters)
#define GET_LightModeliv(disp) GET_by_offset(disp, _gloffset_LightModeliv)
#define SET_LightModeliv(disp, fn) SET_by_offset(disp, _gloffset_LightModeliv, fn)
#define CALL_LineStipple(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLushort)), _gloffset_LineStipple, parameters)
#define GET_LineStipple(disp) GET_by_offset(disp, _gloffset_LineStipple)
#define SET_LineStipple(disp, fn) SET_by_offset(disp, _gloffset_LineStipple, fn)
#define CALL_LineWidth(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat)), _gloffset_LineWidth, parameters)
#define GET_LineWidth(disp) GET_by_offset(disp, _gloffset_LineWidth)
#define SET_LineWidth(disp, fn) SET_by_offset(disp, _gloffset_LineWidth, fn)
#define CALL_Materialf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), _gloffset_Materialf, parameters)
#define GET_Materialf(disp) GET_by_offset(disp, _gloffset_Materialf)
#define SET_Materialf(disp, fn) SET_by_offset(disp, _gloffset_Materialf, fn)
#define CALL_Materialfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), _gloffset_Materialfv, parameters)
#define GET_Materialfv(disp) GET_by_offset(disp, _gloffset_Materialfv)
#define SET_Materialfv(disp, fn) SET_by_offset(disp, _gloffset_Materialfv, fn)
#define CALL_Materiali(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint)), _gloffset_Materiali, parameters)
#define GET_Materiali(disp) GET_by_offset(disp, _gloffset_Materiali)
#define SET_Materiali(disp, fn) SET_by_offset(disp, _gloffset_Materiali, fn)
#define CALL_Materialiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLint *)), _gloffset_Materialiv, parameters)
#define GET_Materialiv(disp) GET_by_offset(disp, _gloffset_Materialiv)
#define SET_Materialiv(disp, fn) SET_by_offset(disp, _gloffset_Materialiv, fn)
#define CALL_PointSize(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat)), _gloffset_PointSize, parameters)
#define GET_PointSize(disp) GET_by_offset(disp, _gloffset_PointSize)
#define SET_PointSize(disp, fn) SET_by_offset(disp, _gloffset_PointSize, fn)
#define CALL_PolygonMode(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum)), _gloffset_PolygonMode, parameters)
#define GET_PolygonMode(disp) GET_by_offset(disp, _gloffset_PolygonMode)
#define SET_PolygonMode(disp, fn) SET_by_offset(disp, _gloffset_PolygonMode, fn)
#define CALL_PolygonStipple(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLubyte *)), _gloffset_PolygonStipple, parameters)
#define GET_PolygonStipple(disp) GET_by_offset(disp, _gloffset_PolygonStipple)
#define SET_PolygonStipple(disp, fn) SET_by_offset(disp, _gloffset_PolygonStipple, fn)
#define CALL_Scissor(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLsizei, GLsizei)), _gloffset_Scissor, parameters)
#define GET_Scissor(disp) GET_by_offset(disp, _gloffset_Scissor)
#define SET_Scissor(disp, fn) SET_by_offset(disp, _gloffset_Scissor, fn)
#define CALL_ShadeModel(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_ShadeModel, parameters)
#define GET_ShadeModel(disp) GET_by_offset(disp, _gloffset_ShadeModel)
#define SET_ShadeModel(disp, fn) SET_by_offset(disp, _gloffset_ShadeModel, fn)
#define CALL_TexParameterf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), _gloffset_TexParameterf, parameters)
#define GET_TexParameterf(disp) GET_by_offset(disp, _gloffset_TexParameterf)
#define SET_TexParameterf(disp, fn) SET_by_offset(disp, _gloffset_TexParameterf, fn)
#define CALL_TexParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), _gloffset_TexParameterfv, parameters)
#define GET_TexParameterfv(disp) GET_by_offset(disp, _gloffset_TexParameterfv)
#define SET_TexParameterfv(disp, fn) SET_by_offset(disp, _gloffset_TexParameterfv, fn)
#define CALL_TexParameteri(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint)), _gloffset_TexParameteri, parameters)
#define GET_TexParameteri(disp) GET_by_offset(disp, _gloffset_TexParameteri)
#define SET_TexParameteri(disp, fn) SET_by_offset(disp, _gloffset_TexParameteri, fn)
#define CALL_TexParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLint *)), _gloffset_TexParameteriv, parameters)
#define GET_TexParameteriv(disp) GET_by_offset(disp, _gloffset_TexParameteriv)
#define SET_TexParameteriv(disp, fn) SET_by_offset(disp, _gloffset_TexParameteriv, fn)
#define CALL_TexImage1D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLsizei, GLint, GLenum, GLenum, const GLvoid *)), _gloffset_TexImage1D, parameters)
#define GET_TexImage1D(disp) GET_by_offset(disp, _gloffset_TexImage1D)
#define SET_TexImage1D(disp, fn) SET_by_offset(disp, _gloffset_TexImage1D, fn)
#define CALL_TexImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid *)), _gloffset_TexImage2D, parameters)
#define GET_TexImage2D(disp) GET_by_offset(disp, _gloffset_TexImage2D)
#define SET_TexImage2D(disp, fn) SET_by_offset(disp, _gloffset_TexImage2D, fn)
#define CALL_TexEnvf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), _gloffset_TexEnvf, parameters)
#define GET_TexEnvf(disp) GET_by_offset(disp, _gloffset_TexEnvf)
#define SET_TexEnvf(disp, fn) SET_by_offset(disp, _gloffset_TexEnvf, fn)
#define CALL_TexEnvfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), _gloffset_TexEnvfv, parameters)
#define GET_TexEnvfv(disp) GET_by_offset(disp, _gloffset_TexEnvfv)
#define SET_TexEnvfv(disp, fn) SET_by_offset(disp, _gloffset_TexEnvfv, fn)
#define CALL_TexEnvi(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint)), _gloffset_TexEnvi, parameters)
#define GET_TexEnvi(disp) GET_by_offset(disp, _gloffset_TexEnvi)
#define SET_TexEnvi(disp, fn) SET_by_offset(disp, _gloffset_TexEnvi, fn)
#define CALL_TexEnviv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLint *)), _gloffset_TexEnviv, parameters)
#define GET_TexEnviv(disp) GET_by_offset(disp, _gloffset_TexEnviv)
#define SET_TexEnviv(disp, fn) SET_by_offset(disp, _gloffset_TexEnviv, fn)
#define CALL_TexGend(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLdouble)), _gloffset_TexGend, parameters)
#define GET_TexGend(disp) GET_by_offset(disp, _gloffset_TexGend)
#define SET_TexGend(disp, fn) SET_by_offset(disp, _gloffset_TexGend, fn)
#define CALL_TexGendv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLdouble *)), _gloffset_TexGendv, parameters)
#define GET_TexGendv(disp) GET_by_offset(disp, _gloffset_TexGendv)
#define SET_TexGendv(disp, fn) SET_by_offset(disp, _gloffset_TexGendv, fn)
#define CALL_TexGenf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), _gloffset_TexGenf, parameters)
#define GET_TexGenf(disp) GET_by_offset(disp, _gloffset_TexGenf)
#define SET_TexGenf(disp, fn) SET_by_offset(disp, _gloffset_TexGenf, fn)
#define CALL_TexGenfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), _gloffset_TexGenfv, parameters)
#define GET_TexGenfv(disp) GET_by_offset(disp, _gloffset_TexGenfv)
#define SET_TexGenfv(disp, fn) SET_by_offset(disp, _gloffset_TexGenfv, fn)
#define CALL_TexGeni(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint)), _gloffset_TexGeni, parameters)
#define GET_TexGeni(disp) GET_by_offset(disp, _gloffset_TexGeni)
#define SET_TexGeni(disp, fn) SET_by_offset(disp, _gloffset_TexGeni, fn)
#define CALL_TexGeniv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLint *)), _gloffset_TexGeniv, parameters)
#define GET_TexGeniv(disp) GET_by_offset(disp, _gloffset_TexGeniv)
#define SET_TexGeniv(disp, fn) SET_by_offset(disp, _gloffset_TexGeniv, fn)
#define CALL_FeedbackBuffer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLenum, GLfloat *)), _gloffset_FeedbackBuffer, parameters)
#define GET_FeedbackBuffer(disp) GET_by_offset(disp, _gloffset_FeedbackBuffer)
#define SET_FeedbackBuffer(disp, fn) SET_by_offset(disp, _gloffset_FeedbackBuffer, fn)
#define CALL_SelectBuffer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), _gloffset_SelectBuffer, parameters)
#define GET_SelectBuffer(disp) GET_by_offset(disp, _gloffset_SelectBuffer)
#define SET_SelectBuffer(disp, fn) SET_by_offset(disp, _gloffset_SelectBuffer, fn)
#define CALL_RenderMode(disp, parameters) CALL_by_offset(disp, (GLint (GLAPIENTRYP)(GLenum)), _gloffset_RenderMode, parameters)
#define GET_RenderMode(disp) GET_by_offset(disp, _gloffset_RenderMode)
#define SET_RenderMode(disp, fn) SET_by_offset(disp, _gloffset_RenderMode, fn)
#define CALL_InitNames(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_InitNames, parameters)
#define GET_InitNames(disp) GET_by_offset(disp, _gloffset_InitNames)
#define SET_InitNames(disp, fn) SET_by_offset(disp, _gloffset_InitNames, fn)
#define CALL_LoadName(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_LoadName, parameters)
#define GET_LoadName(disp) GET_by_offset(disp, _gloffset_LoadName)
#define SET_LoadName(disp, fn) SET_by_offset(disp, _gloffset_LoadName, fn)
#define CALL_PassThrough(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat)), _gloffset_PassThrough, parameters)
#define GET_PassThrough(disp) GET_by_offset(disp, _gloffset_PassThrough)
#define SET_PassThrough(disp, fn) SET_by_offset(disp, _gloffset_PassThrough, fn)
#define CALL_PopName(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_PopName, parameters)
#define GET_PopName(disp) GET_by_offset(disp, _gloffset_PopName)
#define SET_PopName(disp, fn) SET_by_offset(disp, _gloffset_PopName, fn)
#define CALL_PushName(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_PushName, parameters)
#define GET_PushName(disp) GET_by_offset(disp, _gloffset_PushName)
#define SET_PushName(disp, fn) SET_by_offset(disp, _gloffset_PushName, fn)
#define CALL_DrawBuffer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_DrawBuffer, parameters)
#define GET_DrawBuffer(disp) GET_by_offset(disp, _gloffset_DrawBuffer)
#define SET_DrawBuffer(disp, fn) SET_by_offset(disp, _gloffset_DrawBuffer, fn)
#define CALL_Clear(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLbitfield)), _gloffset_Clear, parameters)
#define GET_Clear(disp) GET_by_offset(disp, _gloffset_Clear)
#define SET_Clear(disp, fn) SET_by_offset(disp, _gloffset_Clear, fn)
#define CALL_ClearAccum(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat)), _gloffset_ClearAccum, parameters)
#define GET_ClearAccum(disp) GET_by_offset(disp, _gloffset_ClearAccum)
#define SET_ClearAccum(disp, fn) SET_by_offset(disp, _gloffset_ClearAccum, fn)
#define CALL_ClearIndex(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat)), _gloffset_ClearIndex, parameters)
#define GET_ClearIndex(disp) GET_by_offset(disp, _gloffset_ClearIndex)
#define SET_ClearIndex(disp, fn) SET_by_offset(disp, _gloffset_ClearIndex, fn)
#define CALL_ClearColor(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampf, GLclampf, GLclampf, GLclampf)), _gloffset_ClearColor, parameters)
#define GET_ClearColor(disp) GET_by_offset(disp, _gloffset_ClearColor)
#define SET_ClearColor(disp, fn) SET_by_offset(disp, _gloffset_ClearColor, fn)
#define CALL_ClearStencil(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint)), _gloffset_ClearStencil, parameters)
#define GET_ClearStencil(disp) GET_by_offset(disp, _gloffset_ClearStencil)
#define SET_ClearStencil(disp, fn) SET_by_offset(disp, _gloffset_ClearStencil, fn)
#define CALL_ClearDepth(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampd)), _gloffset_ClearDepth, parameters)
#define GET_ClearDepth(disp) GET_by_offset(disp, _gloffset_ClearDepth)
#define SET_ClearDepth(disp, fn) SET_by_offset(disp, _gloffset_ClearDepth, fn)
#define CALL_StencilMask(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_StencilMask, parameters)
#define GET_StencilMask(disp) GET_by_offset(disp, _gloffset_StencilMask)
#define SET_StencilMask(disp, fn) SET_by_offset(disp, _gloffset_StencilMask, fn)
#define CALL_ColorMask(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLboolean, GLboolean, GLboolean, GLboolean)), _gloffset_ColorMask, parameters)
#define GET_ColorMask(disp) GET_by_offset(disp, _gloffset_ColorMask)
#define SET_ColorMask(disp, fn) SET_by_offset(disp, _gloffset_ColorMask, fn)
#define CALL_DepthMask(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLboolean)), _gloffset_DepthMask, parameters)
#define GET_DepthMask(disp) GET_by_offset(disp, _gloffset_DepthMask)
#define SET_DepthMask(disp, fn) SET_by_offset(disp, _gloffset_DepthMask, fn)
#define CALL_IndexMask(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_IndexMask, parameters)
#define GET_IndexMask(disp) GET_by_offset(disp, _gloffset_IndexMask)
#define SET_IndexMask(disp, fn) SET_by_offset(disp, _gloffset_IndexMask, fn)
#define CALL_Accum(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat)), _gloffset_Accum, parameters)
#define GET_Accum(disp) GET_by_offset(disp, _gloffset_Accum)
#define SET_Accum(disp, fn) SET_by_offset(disp, _gloffset_Accum, fn)
#define CALL_Disable(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_Disable, parameters)
#define GET_Disable(disp) GET_by_offset(disp, _gloffset_Disable)
#define SET_Disable(disp, fn) SET_by_offset(disp, _gloffset_Disable, fn)
#define CALL_Enable(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_Enable, parameters)
#define GET_Enable(disp) GET_by_offset(disp, _gloffset_Enable)
#define SET_Enable(disp, fn) SET_by_offset(disp, _gloffset_Enable, fn)
#define CALL_Finish(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_Finish, parameters)
#define GET_Finish(disp) GET_by_offset(disp, _gloffset_Finish)
#define SET_Finish(disp, fn) SET_by_offset(disp, _gloffset_Finish, fn)
#define CALL_Flush(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_Flush, parameters)
#define GET_Flush(disp) GET_by_offset(disp, _gloffset_Flush)
#define SET_Flush(disp, fn) SET_by_offset(disp, _gloffset_Flush, fn)
#define CALL_PopAttrib(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_PopAttrib, parameters)
#define GET_PopAttrib(disp) GET_by_offset(disp, _gloffset_PopAttrib)
#define SET_PopAttrib(disp, fn) SET_by_offset(disp, _gloffset_PopAttrib, fn)
#define CALL_PushAttrib(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLbitfield)), _gloffset_PushAttrib, parameters)
#define GET_PushAttrib(disp) GET_by_offset(disp, _gloffset_PushAttrib)
#define SET_PushAttrib(disp, fn) SET_by_offset(disp, _gloffset_PushAttrib, fn)
#define CALL_Map1d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLdouble, GLdouble, GLint, GLint, const GLdouble *)), _gloffset_Map1d, parameters)
#define GET_Map1d(disp) GET_by_offset(disp, _gloffset_Map1d)
#define SET_Map1d(disp, fn) SET_by_offset(disp, _gloffset_Map1d, fn)
#define CALL_Map1f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat, GLfloat, GLint, GLint, const GLfloat *)), _gloffset_Map1f, parameters)
#define GET_Map1f(disp) GET_by_offset(disp, _gloffset_Map1f)
#define SET_Map1f(disp, fn) SET_by_offset(disp, _gloffset_Map1f, fn)
#define CALL_Map2d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLdouble, GLdouble, GLint, GLint, GLdouble, GLdouble, GLint, GLint, const GLdouble *)), _gloffset_Map2d, parameters)
#define GET_Map2d(disp) GET_by_offset(disp, _gloffset_Map2d)
#define SET_Map2d(disp, fn) SET_by_offset(disp, _gloffset_Map2d, fn)
#define CALL_Map2f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat, GLfloat, GLint, GLint, GLfloat, GLfloat, GLint, GLint, const GLfloat *)), _gloffset_Map2f, parameters)
#define GET_Map2f(disp) GET_by_offset(disp, _gloffset_Map2f)
#define SET_Map2f(disp, fn) SET_by_offset(disp, _gloffset_Map2f, fn)
#define CALL_MapGrid1d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLdouble, GLdouble)), _gloffset_MapGrid1d, parameters)
#define GET_MapGrid1d(disp) GET_by_offset(disp, _gloffset_MapGrid1d)
#define SET_MapGrid1d(disp, fn) SET_by_offset(disp, _gloffset_MapGrid1d, fn)
#define CALL_MapGrid1f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLfloat, GLfloat)), _gloffset_MapGrid1f, parameters)
#define GET_MapGrid1f(disp) GET_by_offset(disp, _gloffset_MapGrid1f)
#define SET_MapGrid1f(disp, fn) SET_by_offset(disp, _gloffset_MapGrid1f, fn)
#define CALL_MapGrid2d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLdouble, GLdouble, GLint, GLdouble, GLdouble)), _gloffset_MapGrid2d, parameters)
#define GET_MapGrid2d(disp) GET_by_offset(disp, _gloffset_MapGrid2d)
#define SET_MapGrid2d(disp, fn) SET_by_offset(disp, _gloffset_MapGrid2d, fn)
#define CALL_MapGrid2f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLfloat, GLfloat, GLint, GLfloat, GLfloat)), _gloffset_MapGrid2f, parameters)
#define GET_MapGrid2f(disp) GET_by_offset(disp, _gloffset_MapGrid2f)
#define SET_MapGrid2f(disp, fn) SET_by_offset(disp, _gloffset_MapGrid2f, fn)
#define CALL_EvalCoord1d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble)), _gloffset_EvalCoord1d, parameters)
#define GET_EvalCoord1d(disp) GET_by_offset(disp, _gloffset_EvalCoord1d)
#define SET_EvalCoord1d(disp, fn) SET_by_offset(disp, _gloffset_EvalCoord1d, fn)
#define CALL_EvalCoord1dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_EvalCoord1dv, parameters)
#define GET_EvalCoord1dv(disp) GET_by_offset(disp, _gloffset_EvalCoord1dv)
#define SET_EvalCoord1dv(disp, fn) SET_by_offset(disp, _gloffset_EvalCoord1dv, fn)
#define CALL_EvalCoord1f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat)), _gloffset_EvalCoord1f, parameters)
#define GET_EvalCoord1f(disp) GET_by_offset(disp, _gloffset_EvalCoord1f)
#define SET_EvalCoord1f(disp, fn) SET_by_offset(disp, _gloffset_EvalCoord1f, fn)
#define CALL_EvalCoord1fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_EvalCoord1fv, parameters)
#define GET_EvalCoord1fv(disp) GET_by_offset(disp, _gloffset_EvalCoord1fv)
#define SET_EvalCoord1fv(disp, fn) SET_by_offset(disp, _gloffset_EvalCoord1fv, fn)
#define CALL_EvalCoord2d(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble)), _gloffset_EvalCoord2d, parameters)
#define GET_EvalCoord2d(disp) GET_by_offset(disp, _gloffset_EvalCoord2d)
#define SET_EvalCoord2d(disp, fn) SET_by_offset(disp, _gloffset_EvalCoord2d, fn)
#define CALL_EvalCoord2dv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_EvalCoord2dv, parameters)
#define GET_EvalCoord2dv(disp) GET_by_offset(disp, _gloffset_EvalCoord2dv)
#define SET_EvalCoord2dv(disp, fn) SET_by_offset(disp, _gloffset_EvalCoord2dv, fn)
#define CALL_EvalCoord2f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat)), _gloffset_EvalCoord2f, parameters)
#define GET_EvalCoord2f(disp) GET_by_offset(disp, _gloffset_EvalCoord2f)
#define SET_EvalCoord2f(disp, fn) SET_by_offset(disp, _gloffset_EvalCoord2f, fn)
#define CALL_EvalCoord2fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_EvalCoord2fv, parameters)
#define GET_EvalCoord2fv(disp) GET_by_offset(disp, _gloffset_EvalCoord2fv)
#define SET_EvalCoord2fv(disp, fn) SET_by_offset(disp, _gloffset_EvalCoord2fv, fn)
#define CALL_EvalMesh1(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint)), _gloffset_EvalMesh1, parameters)
#define GET_EvalMesh1(disp) GET_by_offset(disp, _gloffset_EvalMesh1)
#define SET_EvalMesh1(disp, fn) SET_by_offset(disp, _gloffset_EvalMesh1, fn)
#define CALL_EvalPoint1(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint)), _gloffset_EvalPoint1, parameters)
#define GET_EvalPoint1(disp) GET_by_offset(disp, _gloffset_EvalPoint1)
#define SET_EvalPoint1(disp, fn) SET_by_offset(disp, _gloffset_EvalPoint1, fn)
#define CALL_EvalMesh2(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLint)), _gloffset_EvalMesh2, parameters)
#define GET_EvalMesh2(disp) GET_by_offset(disp, _gloffset_EvalMesh2)
#define SET_EvalMesh2(disp, fn) SET_by_offset(disp, _gloffset_EvalMesh2, fn)
#define CALL_EvalPoint2(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint)), _gloffset_EvalPoint2, parameters)
#define GET_EvalPoint2(disp) GET_by_offset(disp, _gloffset_EvalPoint2)
#define SET_EvalPoint2(disp, fn) SET_by_offset(disp, _gloffset_EvalPoint2, fn)
#define CALL_AlphaFunc(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLclampf)), _gloffset_AlphaFunc, parameters)
#define GET_AlphaFunc(disp) GET_by_offset(disp, _gloffset_AlphaFunc)
#define SET_AlphaFunc(disp, fn) SET_by_offset(disp, _gloffset_AlphaFunc, fn)
#define CALL_BlendFunc(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum)), _gloffset_BlendFunc, parameters)
#define GET_BlendFunc(disp) GET_by_offset(disp, _gloffset_BlendFunc)
#define SET_BlendFunc(disp, fn) SET_by_offset(disp, _gloffset_BlendFunc, fn)
#define CALL_LogicOp(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_LogicOp, parameters)
#define GET_LogicOp(disp) GET_by_offset(disp, _gloffset_LogicOp)
#define SET_LogicOp(disp, fn) SET_by_offset(disp, _gloffset_LogicOp, fn)
#define CALL_StencilFunc(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLuint)), _gloffset_StencilFunc, parameters)
#define GET_StencilFunc(disp) GET_by_offset(disp, _gloffset_StencilFunc)
#define SET_StencilFunc(disp, fn) SET_by_offset(disp, _gloffset_StencilFunc, fn)
#define CALL_StencilOp(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum)), _gloffset_StencilOp, parameters)
#define GET_StencilOp(disp) GET_by_offset(disp, _gloffset_StencilOp)
#define SET_StencilOp(disp, fn) SET_by_offset(disp, _gloffset_StencilOp, fn)
#define CALL_DepthFunc(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_DepthFunc, parameters)
#define GET_DepthFunc(disp) GET_by_offset(disp, _gloffset_DepthFunc)
#define SET_DepthFunc(disp, fn) SET_by_offset(disp, _gloffset_DepthFunc, fn)
#define CALL_PixelZoom(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat)), _gloffset_PixelZoom, parameters)
#define GET_PixelZoom(disp) GET_by_offset(disp, _gloffset_PixelZoom)
#define SET_PixelZoom(disp, fn) SET_by_offset(disp, _gloffset_PixelZoom, fn)
#define CALL_PixelTransferf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat)), _gloffset_PixelTransferf, parameters)
#define GET_PixelTransferf(disp) GET_by_offset(disp, _gloffset_PixelTransferf)
#define SET_PixelTransferf(disp, fn) SET_by_offset(disp, _gloffset_PixelTransferf, fn)
#define CALL_PixelTransferi(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint)), _gloffset_PixelTransferi, parameters)
#define GET_PixelTransferi(disp) GET_by_offset(disp, _gloffset_PixelTransferi)
#define SET_PixelTransferi(disp, fn) SET_by_offset(disp, _gloffset_PixelTransferi, fn)
#define CALL_PixelStoref(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat)), _gloffset_PixelStoref, parameters)
#define GET_PixelStoref(disp) GET_by_offset(disp, _gloffset_PixelStoref)
#define SET_PixelStoref(disp, fn) SET_by_offset(disp, _gloffset_PixelStoref, fn)
#define CALL_PixelStorei(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint)), _gloffset_PixelStorei, parameters)
#define GET_PixelStorei(disp) GET_by_offset(disp, _gloffset_PixelStorei)
#define SET_PixelStorei(disp, fn) SET_by_offset(disp, _gloffset_PixelStorei, fn)
#define CALL_PixelMapfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, const GLfloat *)), _gloffset_PixelMapfv, parameters)
#define GET_PixelMapfv(disp) GET_by_offset(disp, _gloffset_PixelMapfv)
#define SET_PixelMapfv(disp, fn) SET_by_offset(disp, _gloffset_PixelMapfv, fn)
#define CALL_PixelMapuiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, const GLuint *)), _gloffset_PixelMapuiv, parameters)
#define GET_PixelMapuiv(disp) GET_by_offset(disp, _gloffset_PixelMapuiv)
#define SET_PixelMapuiv(disp, fn) SET_by_offset(disp, _gloffset_PixelMapuiv, fn)
#define CALL_PixelMapusv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, const GLushort *)), _gloffset_PixelMapusv, parameters)
#define GET_PixelMapusv(disp) GET_by_offset(disp, _gloffset_PixelMapusv)
#define SET_PixelMapusv(disp, fn) SET_by_offset(disp, _gloffset_PixelMapusv, fn)
#define CALL_ReadBuffer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_ReadBuffer, parameters)
#define GET_ReadBuffer(disp) GET_by_offset(disp, _gloffset_ReadBuffer)
#define SET_ReadBuffer(disp, fn) SET_by_offset(disp, _gloffset_ReadBuffer, fn)
#define CALL_CopyPixels(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLsizei, GLsizei, GLenum)), _gloffset_CopyPixels, parameters)
#define GET_CopyPixels(disp) GET_by_offset(disp, _gloffset_CopyPixels)
#define SET_CopyPixels(disp, fn) SET_by_offset(disp, _gloffset_CopyPixels, fn)
#define CALL_ReadPixels(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, GLvoid *)), _gloffset_ReadPixels, parameters)
#define GET_ReadPixels(disp) GET_by_offset(disp, _gloffset_ReadPixels)
#define SET_ReadPixels(disp, fn) SET_by_offset(disp, _gloffset_ReadPixels, fn)
#define CALL_DrawPixels(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLsizei, GLenum, GLenum, const GLvoid *)), _gloffset_DrawPixels, parameters)
#define GET_DrawPixels(disp) GET_by_offset(disp, _gloffset_DrawPixels)
#define SET_DrawPixels(disp, fn) SET_by_offset(disp, _gloffset_DrawPixels, fn)
#define CALL_GetBooleanv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLboolean *)), _gloffset_GetBooleanv, parameters)
#define GET_GetBooleanv(disp) GET_by_offset(disp, _gloffset_GetBooleanv)
#define SET_GetBooleanv(disp, fn) SET_by_offset(disp, _gloffset_GetBooleanv, fn)
#define CALL_GetClipPlane(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLdouble *)), _gloffset_GetClipPlane, parameters)
#define GET_GetClipPlane(disp) GET_by_offset(disp, _gloffset_GetClipPlane)
#define SET_GetClipPlane(disp, fn) SET_by_offset(disp, _gloffset_GetClipPlane, fn)
#define CALL_GetDoublev(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLdouble *)), _gloffset_GetDoublev, parameters)
#define GET_GetDoublev(disp) GET_by_offset(disp, _gloffset_GetDoublev)
#define SET_GetDoublev(disp, fn) SET_by_offset(disp, _gloffset_GetDoublev, fn)
#define CALL_GetError(disp, parameters) CALL_by_offset(disp, (GLenum (GLAPIENTRYP)(void)), _gloffset_GetError, parameters)
#define GET_GetError(disp) GET_by_offset(disp, _gloffset_GetError)
#define SET_GetError(disp, fn) SET_by_offset(disp, _gloffset_GetError, fn)
#define CALL_GetFloatv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat *)), _gloffset_GetFloatv, parameters)
#define GET_GetFloatv(disp) GET_by_offset(disp, _gloffset_GetFloatv)
#define SET_GetFloatv(disp, fn) SET_by_offset(disp, _gloffset_GetFloatv, fn)
#define CALL_GetIntegerv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint *)), _gloffset_GetIntegerv, parameters)
#define GET_GetIntegerv(disp) GET_by_offset(disp, _gloffset_GetIntegerv)
#define SET_GetIntegerv(disp, fn) SET_by_offset(disp, _gloffset_GetIntegerv, fn)
#define CALL_GetLightfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), _gloffset_GetLightfv, parameters)
#define GET_GetLightfv(disp) GET_by_offset(disp, _gloffset_GetLightfv)
#define SET_GetLightfv(disp, fn) SET_by_offset(disp, _gloffset_GetLightfv, fn)
#define CALL_GetLightiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetLightiv, parameters)
#define GET_GetLightiv(disp) GET_by_offset(disp, _gloffset_GetLightiv)
#define SET_GetLightiv(disp, fn) SET_by_offset(disp, _gloffset_GetLightiv, fn)
#define CALL_GetMapdv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLdouble *)), _gloffset_GetMapdv, parameters)
#define GET_GetMapdv(disp) GET_by_offset(disp, _gloffset_GetMapdv)
#define SET_GetMapdv(disp, fn) SET_by_offset(disp, _gloffset_GetMapdv, fn)
#define CALL_GetMapfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), _gloffset_GetMapfv, parameters)
#define GET_GetMapfv(disp) GET_by_offset(disp, _gloffset_GetMapfv)
#define SET_GetMapfv(disp, fn) SET_by_offset(disp, _gloffset_GetMapfv, fn)
#define CALL_GetMapiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetMapiv, parameters)
#define GET_GetMapiv(disp) GET_by_offset(disp, _gloffset_GetMapiv)
#define SET_GetMapiv(disp, fn) SET_by_offset(disp, _gloffset_GetMapiv, fn)
#define CALL_GetMaterialfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), _gloffset_GetMaterialfv, parameters)
#define GET_GetMaterialfv(disp) GET_by_offset(disp, _gloffset_GetMaterialfv)
#define SET_GetMaterialfv(disp, fn) SET_by_offset(disp, _gloffset_GetMaterialfv, fn)
#define CALL_GetMaterialiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetMaterialiv, parameters)
#define GET_GetMaterialiv(disp) GET_by_offset(disp, _gloffset_GetMaterialiv)
#define SET_GetMaterialiv(disp, fn) SET_by_offset(disp, _gloffset_GetMaterialiv, fn)
#define CALL_GetPixelMapfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat *)), _gloffset_GetPixelMapfv, parameters)
#define GET_GetPixelMapfv(disp) GET_by_offset(disp, _gloffset_GetPixelMapfv)
#define SET_GetPixelMapfv(disp, fn) SET_by_offset(disp, _gloffset_GetPixelMapfv, fn)
#define CALL_GetPixelMapuiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint *)), _gloffset_GetPixelMapuiv, parameters)
#define GET_GetPixelMapuiv(disp) GET_by_offset(disp, _gloffset_GetPixelMapuiv)
#define SET_GetPixelMapuiv(disp, fn) SET_by_offset(disp, _gloffset_GetPixelMapuiv, fn)
#define CALL_GetPixelMapusv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLushort *)), _gloffset_GetPixelMapusv, parameters)
#define GET_GetPixelMapusv(disp) GET_by_offset(disp, _gloffset_GetPixelMapusv)
#define SET_GetPixelMapusv(disp, fn) SET_by_offset(disp, _gloffset_GetPixelMapusv, fn)
#define CALL_GetPolygonStipple(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLubyte *)), _gloffset_GetPolygonStipple, parameters)
#define GET_GetPolygonStipple(disp) GET_by_offset(disp, _gloffset_GetPolygonStipple)
#define SET_GetPolygonStipple(disp, fn) SET_by_offset(disp, _gloffset_GetPolygonStipple, fn)
#define CALL_GetString(disp, parameters) CALL_by_offset(disp, (const GLubyte * (GLAPIENTRYP)(GLenum)), _gloffset_GetString, parameters)
#define GET_GetString(disp) GET_by_offset(disp, _gloffset_GetString)
#define SET_GetString(disp, fn) SET_by_offset(disp, _gloffset_GetString, fn)
#define CALL_GetTexEnvfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), _gloffset_GetTexEnvfv, parameters)
#define GET_GetTexEnvfv(disp) GET_by_offset(disp, _gloffset_GetTexEnvfv)
#define SET_GetTexEnvfv(disp, fn) SET_by_offset(disp, _gloffset_GetTexEnvfv, fn)
#define CALL_GetTexEnviv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetTexEnviv, parameters)
#define GET_GetTexEnviv(disp) GET_by_offset(disp, _gloffset_GetTexEnviv)
#define SET_GetTexEnviv(disp, fn) SET_by_offset(disp, _gloffset_GetTexEnviv, fn)
#define CALL_GetTexGendv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLdouble *)), _gloffset_GetTexGendv, parameters)
#define GET_GetTexGendv(disp) GET_by_offset(disp, _gloffset_GetTexGendv)
#define SET_GetTexGendv(disp, fn) SET_by_offset(disp, _gloffset_GetTexGendv, fn)
#define CALL_GetTexGenfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), _gloffset_GetTexGenfv, parameters)
#define GET_GetTexGenfv(disp) GET_by_offset(disp, _gloffset_GetTexGenfv)
#define SET_GetTexGenfv(disp, fn) SET_by_offset(disp, _gloffset_GetTexGenfv, fn)
#define CALL_GetTexGeniv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetTexGeniv, parameters)
#define GET_GetTexGeniv(disp) GET_by_offset(disp, _gloffset_GetTexGeniv)
#define SET_GetTexGeniv(disp, fn) SET_by_offset(disp, _gloffset_GetTexGeniv, fn)
#define CALL_GetTexImage(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLenum, GLenum, GLvoid *)), _gloffset_GetTexImage, parameters)
#define GET_GetTexImage(disp) GET_by_offset(disp, _gloffset_GetTexImage)
#define SET_GetTexImage(disp, fn) SET_by_offset(disp, _gloffset_GetTexImage, fn)
#define CALL_GetTexParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), _gloffset_GetTexParameterfv, parameters)
#define GET_GetTexParameterfv(disp) GET_by_offset(disp, _gloffset_GetTexParameterfv)
#define SET_GetTexParameterfv(disp, fn) SET_by_offset(disp, _gloffset_GetTexParameterfv, fn)
#define CALL_GetTexParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetTexParameteriv, parameters)
#define GET_GetTexParameteriv(disp) GET_by_offset(disp, _gloffset_GetTexParameteriv)
#define SET_GetTexParameteriv(disp, fn) SET_by_offset(disp, _gloffset_GetTexParameteriv, fn)
#define CALL_GetTexLevelParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLenum, GLfloat *)), _gloffset_GetTexLevelParameterfv, parameters)
#define GET_GetTexLevelParameterfv(disp) GET_by_offset(disp, _gloffset_GetTexLevelParameterfv)
#define SET_GetTexLevelParameterfv(disp, fn) SET_by_offset(disp, _gloffset_GetTexLevelParameterfv, fn)
#define CALL_GetTexLevelParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLenum, GLint *)), _gloffset_GetTexLevelParameteriv, parameters)
#define GET_GetTexLevelParameteriv(disp) GET_by_offset(disp, _gloffset_GetTexLevelParameteriv)
#define SET_GetTexLevelParameteriv(disp, fn) SET_by_offset(disp, _gloffset_GetTexLevelParameteriv, fn)
#define CALL_IsEnabled(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLenum)), _gloffset_IsEnabled, parameters)
#define GET_IsEnabled(disp) GET_by_offset(disp, _gloffset_IsEnabled)
#define SET_IsEnabled(disp, fn) SET_by_offset(disp, _gloffset_IsEnabled, fn)
#define CALL_IsList(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), _gloffset_IsList, parameters)
#define GET_IsList(disp) GET_by_offset(disp, _gloffset_IsList)
#define SET_IsList(disp, fn) SET_by_offset(disp, _gloffset_IsList, fn)
#define CALL_DepthRange(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampd, GLclampd)), _gloffset_DepthRange, parameters)
#define GET_DepthRange(disp) GET_by_offset(disp, _gloffset_DepthRange)
#define SET_DepthRange(disp, fn) SET_by_offset(disp, _gloffset_DepthRange, fn)
#define CALL_Frustum(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble)), _gloffset_Frustum, parameters)
#define GET_Frustum(disp) GET_by_offset(disp, _gloffset_Frustum)
#define SET_Frustum(disp, fn) SET_by_offset(disp, _gloffset_Frustum, fn)
#define CALL_LoadIdentity(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_LoadIdentity, parameters)
#define GET_LoadIdentity(disp) GET_by_offset(disp, _gloffset_LoadIdentity)
#define SET_LoadIdentity(disp, fn) SET_by_offset(disp, _gloffset_LoadIdentity, fn)
#define CALL_LoadMatrixf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_LoadMatrixf, parameters)
#define GET_LoadMatrixf(disp) GET_by_offset(disp, _gloffset_LoadMatrixf)
#define SET_LoadMatrixf(disp, fn) SET_by_offset(disp, _gloffset_LoadMatrixf, fn)
#define CALL_LoadMatrixd(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_LoadMatrixd, parameters)
#define GET_LoadMatrixd(disp) GET_by_offset(disp, _gloffset_LoadMatrixd)
#define SET_LoadMatrixd(disp, fn) SET_by_offset(disp, _gloffset_LoadMatrixd, fn)
#define CALL_MatrixMode(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_MatrixMode, parameters)
#define GET_MatrixMode(disp) GET_by_offset(disp, _gloffset_MatrixMode)
#define SET_MatrixMode(disp, fn) SET_by_offset(disp, _gloffset_MatrixMode, fn)
#define CALL_MultMatrixf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLfloat *)), _gloffset_MultMatrixf, parameters)
#define GET_MultMatrixf(disp) GET_by_offset(disp, _gloffset_MultMatrixf)
#define SET_MultMatrixf(disp, fn) SET_by_offset(disp, _gloffset_MultMatrixf, fn)
#define CALL_MultMatrixd(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLdouble *)), _gloffset_MultMatrixd, parameters)
#define GET_MultMatrixd(disp) GET_by_offset(disp, _gloffset_MultMatrixd)
#define SET_MultMatrixd(disp, fn) SET_by_offset(disp, _gloffset_MultMatrixd, fn)
#define CALL_Ortho(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble, GLdouble, GLdouble, GLdouble)), _gloffset_Ortho, parameters)
#define GET_Ortho(disp) GET_by_offset(disp, _gloffset_Ortho)
#define SET_Ortho(disp, fn) SET_by_offset(disp, _gloffset_Ortho, fn)
#define CALL_PopMatrix(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_PopMatrix, parameters)
#define GET_PopMatrix(disp) GET_by_offset(disp, _gloffset_PopMatrix)
#define SET_PopMatrix(disp, fn) SET_by_offset(disp, _gloffset_PopMatrix, fn)
#define CALL_PushMatrix(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_PushMatrix, parameters)
#define GET_PushMatrix(disp) GET_by_offset(disp, _gloffset_PushMatrix)
#define SET_PushMatrix(disp, fn) SET_by_offset(disp, _gloffset_PushMatrix, fn)
#define CALL_Rotated(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble, GLdouble)), _gloffset_Rotated, parameters)
#define GET_Rotated(disp) GET_by_offset(disp, _gloffset_Rotated)
#define SET_Rotated(disp, fn) SET_by_offset(disp, _gloffset_Rotated, fn)
#define CALL_Rotatef(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat, GLfloat)), _gloffset_Rotatef, parameters)
#define GET_Rotatef(disp) GET_by_offset(disp, _gloffset_Rotatef)
#define SET_Rotatef(disp, fn) SET_by_offset(disp, _gloffset_Rotatef, fn)
#define CALL_Scaled(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble)), _gloffset_Scaled, parameters)
#define GET_Scaled(disp) GET_by_offset(disp, _gloffset_Scaled)
#define SET_Scaled(disp, fn) SET_by_offset(disp, _gloffset_Scaled, fn)
#define CALL_Scalef(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat)), _gloffset_Scalef, parameters)
#define GET_Scalef(disp) GET_by_offset(disp, _gloffset_Scalef)
#define SET_Scalef(disp, fn) SET_by_offset(disp, _gloffset_Scalef, fn)
#define CALL_Translated(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLdouble, GLdouble, GLdouble)), _gloffset_Translated, parameters)
#define GET_Translated(disp) GET_by_offset(disp, _gloffset_Translated)
#define SET_Translated(disp, fn) SET_by_offset(disp, _gloffset_Translated, fn)
#define CALL_Translatef(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat, GLfloat)), _gloffset_Translatef, parameters)
#define GET_Translatef(disp) GET_by_offset(disp, _gloffset_Translatef)
#define SET_Translatef(disp, fn) SET_by_offset(disp, _gloffset_Translatef, fn)
#define CALL_Viewport(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLsizei, GLsizei)), _gloffset_Viewport, parameters)
#define GET_Viewport(disp) GET_by_offset(disp, _gloffset_Viewport)
#define SET_Viewport(disp, fn) SET_by_offset(disp, _gloffset_Viewport, fn)
#define CALL_ArrayElement(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint)), _gloffset_ArrayElement, parameters)
#define GET_ArrayElement(disp) GET_by_offset(disp, _gloffset_ArrayElement)
#define SET_ArrayElement(disp, fn) SET_by_offset(disp, _gloffset_ArrayElement, fn)
#define CALL_BindTexture(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint)), _gloffset_BindTexture, parameters)
#define GET_BindTexture(disp) GET_by_offset(disp, _gloffset_BindTexture)
#define SET_BindTexture(disp, fn) SET_by_offset(disp, _gloffset_BindTexture, fn)
#define CALL_ColorPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLenum, GLsizei, const GLvoid *)), _gloffset_ColorPointer, parameters)
#define GET_ColorPointer(disp) GET_by_offset(disp, _gloffset_ColorPointer)
#define SET_ColorPointer(disp, fn) SET_by_offset(disp, _gloffset_ColorPointer, fn)
#define CALL_DisableClientState(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_DisableClientState, parameters)
#define GET_DisableClientState(disp) GET_by_offset(disp, _gloffset_DisableClientState)
#define SET_DisableClientState(disp, fn) SET_by_offset(disp, _gloffset_DisableClientState, fn)
#define CALL_DrawArrays(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLsizei)), _gloffset_DrawArrays, parameters)
#define GET_DrawArrays(disp) GET_by_offset(disp, _gloffset_DrawArrays)
#define SET_DrawArrays(disp, fn) SET_by_offset(disp, _gloffset_DrawArrays, fn)
#define CALL_DrawElements(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, GLenum, const GLvoid *)), _gloffset_DrawElements, parameters)
#define GET_DrawElements(disp) GET_by_offset(disp, _gloffset_DrawElements)
#define SET_DrawElements(disp, fn) SET_by_offset(disp, _gloffset_DrawElements, fn)
#define CALL_EdgeFlagPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLvoid *)), _gloffset_EdgeFlagPointer, parameters)
#define GET_EdgeFlagPointer(disp) GET_by_offset(disp, _gloffset_EdgeFlagPointer)
#define SET_EdgeFlagPointer(disp, fn) SET_by_offset(disp, _gloffset_EdgeFlagPointer, fn)
#define CALL_EnableClientState(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_EnableClientState, parameters)
#define GET_EnableClientState(disp) GET_by_offset(disp, _gloffset_EnableClientState)
#define SET_EnableClientState(disp, fn) SET_by_offset(disp, _gloffset_EnableClientState, fn)
#define CALL_IndexPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, const GLvoid *)), _gloffset_IndexPointer, parameters)
#define GET_IndexPointer(disp) GET_by_offset(disp, _gloffset_IndexPointer)
#define SET_IndexPointer(disp, fn) SET_by_offset(disp, _gloffset_IndexPointer, fn)
#define CALL_Indexub(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLubyte)), _gloffset_Indexub, parameters)
#define GET_Indexub(disp) GET_by_offset(disp, _gloffset_Indexub)
#define SET_Indexub(disp, fn) SET_by_offset(disp, _gloffset_Indexub, fn)
#define CALL_Indexubv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(const GLubyte *)), _gloffset_Indexubv, parameters)
#define GET_Indexubv(disp) GET_by_offset(disp, _gloffset_Indexubv)
#define SET_Indexubv(disp, fn) SET_by_offset(disp, _gloffset_Indexubv, fn)
#define CALL_InterleavedArrays(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, const GLvoid *)), _gloffset_InterleavedArrays, parameters)
#define GET_InterleavedArrays(disp) GET_by_offset(disp, _gloffset_InterleavedArrays)
#define SET_InterleavedArrays(disp, fn) SET_by_offset(disp, _gloffset_InterleavedArrays, fn)
#define CALL_NormalPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, const GLvoid *)), _gloffset_NormalPointer, parameters)
#define GET_NormalPointer(disp) GET_by_offset(disp, _gloffset_NormalPointer)
#define SET_NormalPointer(disp, fn) SET_by_offset(disp, _gloffset_NormalPointer, fn)
#define CALL_PolygonOffset(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLfloat, GLfloat)), _gloffset_PolygonOffset, parameters)
#define GET_PolygonOffset(disp) GET_by_offset(disp, _gloffset_PolygonOffset)
#define SET_PolygonOffset(disp, fn) SET_by_offset(disp, _gloffset_PolygonOffset, fn)
#define CALL_TexCoordPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLenum, GLsizei, const GLvoid *)), _gloffset_TexCoordPointer, parameters)
#define GET_TexCoordPointer(disp) GET_by_offset(disp, _gloffset_TexCoordPointer)
#define SET_TexCoordPointer(disp, fn) SET_by_offset(disp, _gloffset_TexCoordPointer, fn)
#define CALL_VertexPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLenum, GLsizei, const GLvoid *)), _gloffset_VertexPointer, parameters)
#define GET_VertexPointer(disp) GET_by_offset(disp, _gloffset_VertexPointer)
#define SET_VertexPointer(disp, fn) SET_by_offset(disp, _gloffset_VertexPointer, fn)
#define CALL_AreTexturesResident(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLsizei, const GLuint *, GLboolean *)), _gloffset_AreTexturesResident, parameters)
#define GET_AreTexturesResident(disp) GET_by_offset(disp, _gloffset_AreTexturesResident)
#define SET_AreTexturesResident(disp, fn) SET_by_offset(disp, _gloffset_AreTexturesResident, fn)
#define CALL_CopyTexImage1D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint)), _gloffset_CopyTexImage1D, parameters)
#define GET_CopyTexImage1D(disp) GET_by_offset(disp, _gloffset_CopyTexImage1D)
#define SET_CopyTexImage1D(disp, fn) SET_by_offset(disp, _gloffset_CopyTexImage1D, fn)
#define CALL_CopyTexImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint)), _gloffset_CopyTexImage2D, parameters)
#define GET_CopyTexImage2D(disp) GET_by_offset(disp, _gloffset_CopyTexImage2D)
#define SET_CopyTexImage2D(disp, fn) SET_by_offset(disp, _gloffset_CopyTexImage2D, fn)
#define CALL_CopyTexSubImage1D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLint, GLsizei)), _gloffset_CopyTexSubImage1D, parameters)
#define GET_CopyTexSubImage1D(disp) GET_by_offset(disp, _gloffset_CopyTexSubImage1D)
#define SET_CopyTexSubImage1D(disp, fn) SET_by_offset(disp, _gloffset_CopyTexSubImage1D, fn)
#define CALL_CopyTexSubImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)), _gloffset_CopyTexSubImage2D, parameters)
#define GET_CopyTexSubImage2D(disp) GET_by_offset(disp, _gloffset_CopyTexSubImage2D)
#define SET_CopyTexSubImage2D(disp, fn) SET_by_offset(disp, _gloffset_CopyTexSubImage2D, fn)
#define CALL_DeleteTextures(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *)), _gloffset_DeleteTextures, parameters)
#define GET_DeleteTextures(disp) GET_by_offset(disp, _gloffset_DeleteTextures)
#define SET_DeleteTextures(disp, fn) SET_by_offset(disp, _gloffset_DeleteTextures, fn)
#define CALL_GenTextures(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), _gloffset_GenTextures, parameters)
#define GET_GenTextures(disp) GET_by_offset(disp, _gloffset_GenTextures)
#define SET_GenTextures(disp, fn) SET_by_offset(disp, _gloffset_GenTextures, fn)
#define CALL_GetPointerv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLvoid **)), _gloffset_GetPointerv, parameters)
#define GET_GetPointerv(disp) GET_by_offset(disp, _gloffset_GetPointerv)
#define SET_GetPointerv(disp, fn) SET_by_offset(disp, _gloffset_GetPointerv, fn)
#define CALL_IsTexture(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), _gloffset_IsTexture, parameters)
#define GET_IsTexture(disp) GET_by_offset(disp, _gloffset_IsTexture)
#define SET_IsTexture(disp, fn) SET_by_offset(disp, _gloffset_IsTexture, fn)
#define CALL_PrioritizeTextures(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *, const GLclampf *)), _gloffset_PrioritizeTextures, parameters)
#define GET_PrioritizeTextures(disp) GET_by_offset(disp, _gloffset_PrioritizeTextures)
#define SET_PrioritizeTextures(disp, fn) SET_by_offset(disp, _gloffset_PrioritizeTextures, fn)
#define CALL_TexSubImage1D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const GLvoid *)), _gloffset_TexSubImage1D, parameters)
#define GET_TexSubImage1D(disp) GET_by_offset(disp, _gloffset_TexSubImage1D)
#define SET_TexSubImage1D(disp, fn) SET_by_offset(disp, _gloffset_TexSubImage1D, fn)
#define CALL_TexSubImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *)), _gloffset_TexSubImage2D, parameters)
#define GET_TexSubImage2D(disp) GET_by_offset(disp, _gloffset_TexSubImage2D)
#define SET_TexSubImage2D(disp, fn) SET_by_offset(disp, _gloffset_TexSubImage2D, fn)
#define CALL_PopClientAttrib(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_PopClientAttrib, parameters)
#define GET_PopClientAttrib(disp) GET_by_offset(disp, _gloffset_PopClientAttrib)
#define SET_PopClientAttrib(disp, fn) SET_by_offset(disp, _gloffset_PopClientAttrib, fn)
#define CALL_PushClientAttrib(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLbitfield)), _gloffset_PushClientAttrib, parameters)
#define GET_PushClientAttrib(disp) GET_by_offset(disp, _gloffset_PushClientAttrib)
#define SET_PushClientAttrib(disp, fn) SET_by_offset(disp, _gloffset_PushClientAttrib, fn)
#define CALL_BlendColor(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampf, GLclampf, GLclampf, GLclampf)), _gloffset_BlendColor, parameters)
#define GET_BlendColor(disp) GET_by_offset(disp, _gloffset_BlendColor)
#define SET_BlendColor(disp, fn) SET_by_offset(disp, _gloffset_BlendColor, fn)
#define CALL_BlendEquation(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_BlendEquation, parameters)
#define GET_BlendEquation(disp) GET_by_offset(disp, _gloffset_BlendEquation)
#define SET_BlendEquation(disp, fn) SET_by_offset(disp, _gloffset_BlendEquation, fn)
#define CALL_DrawRangeElements(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint, GLuint, GLsizei, GLenum, const GLvoid *)), _gloffset_DrawRangeElements, parameters)
#define GET_DrawRangeElements(disp) GET_by_offset(disp, _gloffset_DrawRangeElements)
#define SET_DrawRangeElements(disp, fn) SET_by_offset(disp, _gloffset_DrawRangeElements, fn)
#define CALL_ColorTable(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLsizei, GLenum, GLenum, const GLvoid *)), _gloffset_ColorTable, parameters)
#define GET_ColorTable(disp) GET_by_offset(disp, _gloffset_ColorTable)
#define SET_ColorTable(disp, fn) SET_by_offset(disp, _gloffset_ColorTable, fn)
#define CALL_ColorTableParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), _gloffset_ColorTableParameterfv, parameters)
#define GET_ColorTableParameterfv(disp) GET_by_offset(disp, _gloffset_ColorTableParameterfv)
#define SET_ColorTableParameterfv(disp, fn) SET_by_offset(disp, _gloffset_ColorTableParameterfv, fn)
#define CALL_ColorTableParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLint *)), _gloffset_ColorTableParameteriv, parameters)
#define GET_ColorTableParameteriv(disp) GET_by_offset(disp, _gloffset_ColorTableParameteriv)
#define SET_ColorTableParameteriv(disp, fn) SET_by_offset(disp, _gloffset_ColorTableParameteriv, fn)
#define CALL_CopyColorTable(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint, GLint, GLsizei)), _gloffset_CopyColorTable, parameters)
#define GET_CopyColorTable(disp) GET_by_offset(disp, _gloffset_CopyColorTable)
#define SET_CopyColorTable(disp, fn) SET_by_offset(disp, _gloffset_CopyColorTable, fn)
#define CALL_GetColorTable(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLvoid *)), _gloffset_GetColorTable, parameters)
#define GET_GetColorTable(disp) GET_by_offset(disp, _gloffset_GetColorTable)
#define SET_GetColorTable(disp, fn) SET_by_offset(disp, _gloffset_GetColorTable, fn)
#define CALL_GetColorTableParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), _gloffset_GetColorTableParameterfv, parameters)
#define GET_GetColorTableParameterfv(disp) GET_by_offset(disp, _gloffset_GetColorTableParameterfv)
#define SET_GetColorTableParameterfv(disp, fn) SET_by_offset(disp, _gloffset_GetColorTableParameterfv, fn)
#define CALL_GetColorTableParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetColorTableParameteriv, parameters)
#define GET_GetColorTableParameteriv(disp) GET_by_offset(disp, _gloffset_GetColorTableParameteriv)
#define SET_GetColorTableParameteriv(disp, fn) SET_by_offset(disp, _gloffset_GetColorTableParameteriv, fn)
#define CALL_ColorSubTable(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *)), _gloffset_ColorSubTable, parameters)
#define GET_ColorSubTable(disp) GET_by_offset(disp, _gloffset_ColorSubTable)
#define SET_ColorSubTable(disp, fn) SET_by_offset(disp, _gloffset_ColorSubTable, fn)
#define CALL_CopyColorSubTable(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, GLint, GLint, GLsizei)), _gloffset_CopyColorSubTable, parameters)
#define GET_CopyColorSubTable(disp) GET_by_offset(disp, _gloffset_CopyColorSubTable)
#define SET_CopyColorSubTable(disp, fn) SET_by_offset(disp, _gloffset_CopyColorSubTable, fn)
#define CALL_ConvolutionFilter1D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLsizei, GLenum, GLenum, const GLvoid *)), _gloffset_ConvolutionFilter1D, parameters)
#define GET_ConvolutionFilter1D(disp) GET_by_offset(disp, _gloffset_ConvolutionFilter1D)
#define SET_ConvolutionFilter1D(disp, fn) SET_by_offset(disp, _gloffset_ConvolutionFilter1D, fn)
#define CALL_ConvolutionFilter2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *)), _gloffset_ConvolutionFilter2D, parameters)
#define GET_ConvolutionFilter2D(disp) GET_by_offset(disp, _gloffset_ConvolutionFilter2D)
#define SET_ConvolutionFilter2D(disp, fn) SET_by_offset(disp, _gloffset_ConvolutionFilter2D, fn)
#define CALL_ConvolutionParameterf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat)), _gloffset_ConvolutionParameterf, parameters)
#define GET_ConvolutionParameterf(disp) GET_by_offset(disp, _gloffset_ConvolutionParameterf)
#define SET_ConvolutionParameterf(disp, fn) SET_by_offset(disp, _gloffset_ConvolutionParameterf, fn)
#define CALL_ConvolutionParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLfloat *)), _gloffset_ConvolutionParameterfv, parameters)
#define GET_ConvolutionParameterfv(disp) GET_by_offset(disp, _gloffset_ConvolutionParameterfv)
#define SET_ConvolutionParameterfv(disp, fn) SET_by_offset(disp, _gloffset_ConvolutionParameterfv, fn)
#define CALL_ConvolutionParameteri(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint)), _gloffset_ConvolutionParameteri, parameters)
#define GET_ConvolutionParameteri(disp) GET_by_offset(disp, _gloffset_ConvolutionParameteri)
#define SET_ConvolutionParameteri(disp, fn) SET_by_offset(disp, _gloffset_ConvolutionParameteri, fn)
#define CALL_ConvolutionParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, const GLint *)), _gloffset_ConvolutionParameteriv, parameters)
#define GET_ConvolutionParameteriv(disp) GET_by_offset(disp, _gloffset_ConvolutionParameteriv)
#define SET_ConvolutionParameteriv(disp, fn) SET_by_offset(disp, _gloffset_ConvolutionParameteriv, fn)
#define CALL_CopyConvolutionFilter1D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint, GLint, GLsizei)), _gloffset_CopyConvolutionFilter1D, parameters)
#define GET_CopyConvolutionFilter1D(disp) GET_by_offset(disp, _gloffset_CopyConvolutionFilter1D)
#define SET_CopyConvolutionFilter1D(disp, fn) SET_by_offset(disp, _gloffset_CopyConvolutionFilter1D, fn)
#define CALL_CopyConvolutionFilter2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint, GLint, GLsizei, GLsizei)), _gloffset_CopyConvolutionFilter2D, parameters)
#define GET_CopyConvolutionFilter2D(disp) GET_by_offset(disp, _gloffset_CopyConvolutionFilter2D)
#define SET_CopyConvolutionFilter2D(disp, fn) SET_by_offset(disp, _gloffset_CopyConvolutionFilter2D, fn)
#define CALL_GetConvolutionFilter(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLvoid *)), _gloffset_GetConvolutionFilter, parameters)
#define GET_GetConvolutionFilter(disp) GET_by_offset(disp, _gloffset_GetConvolutionFilter)
#define SET_GetConvolutionFilter(disp, fn) SET_by_offset(disp, _gloffset_GetConvolutionFilter, fn)
#define CALL_GetConvolutionParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), _gloffset_GetConvolutionParameterfv, parameters)
#define GET_GetConvolutionParameterfv(disp) GET_by_offset(disp, _gloffset_GetConvolutionParameterfv)
#define SET_GetConvolutionParameterfv(disp, fn) SET_by_offset(disp, _gloffset_GetConvolutionParameterfv, fn)
#define CALL_GetConvolutionParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetConvolutionParameteriv, parameters)
#define GET_GetConvolutionParameteriv(disp) GET_by_offset(disp, _gloffset_GetConvolutionParameteriv)
#define SET_GetConvolutionParameteriv(disp, fn) SET_by_offset(disp, _gloffset_GetConvolutionParameteriv, fn)
#define CALL_GetSeparableFilter(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLvoid *, GLvoid *, GLvoid *)), _gloffset_GetSeparableFilter, parameters)
#define GET_GetSeparableFilter(disp) GET_by_offset(disp, _gloffset_GetSeparableFilter)
#define SET_GetSeparableFilter(disp, fn) SET_by_offset(disp, _gloffset_GetSeparableFilter, fn)
#define CALL_SeparableFilter2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *, const GLvoid *)), _gloffset_SeparableFilter2D, parameters)
#define GET_SeparableFilter2D(disp) GET_by_offset(disp, _gloffset_SeparableFilter2D)
#define SET_SeparableFilter2D(disp, fn) SET_by_offset(disp, _gloffset_SeparableFilter2D, fn)
#define CALL_GetHistogram(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLboolean, GLenum, GLenum, GLvoid *)), _gloffset_GetHistogram, parameters)
#define GET_GetHistogram(disp) GET_by_offset(disp, _gloffset_GetHistogram)
#define SET_GetHistogram(disp, fn) SET_by_offset(disp, _gloffset_GetHistogram, fn)
#define CALL_GetHistogramParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), _gloffset_GetHistogramParameterfv, parameters)
#define GET_GetHistogramParameterfv(disp) GET_by_offset(disp, _gloffset_GetHistogramParameterfv)
#define SET_GetHistogramParameterfv(disp, fn) SET_by_offset(disp, _gloffset_GetHistogramParameterfv, fn)
#define CALL_GetHistogramParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetHistogramParameteriv, parameters)
#define GET_GetHistogramParameteriv(disp) GET_by_offset(disp, _gloffset_GetHistogramParameteriv)
#define SET_GetHistogramParameteriv(disp, fn) SET_by_offset(disp, _gloffset_GetHistogramParameteriv, fn)
#define CALL_GetMinmax(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLboolean, GLenum, GLenum, GLvoid *)), _gloffset_GetMinmax, parameters)
#define GET_GetMinmax(disp) GET_by_offset(disp, _gloffset_GetMinmax)
#define SET_GetMinmax(disp, fn) SET_by_offset(disp, _gloffset_GetMinmax, fn)
#define CALL_GetMinmaxParameterfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLfloat *)), _gloffset_GetMinmaxParameterfv, parameters)
#define GET_GetMinmaxParameterfv(disp) GET_by_offset(disp, _gloffset_GetMinmaxParameterfv)
#define SET_GetMinmaxParameterfv(disp, fn) SET_by_offset(disp, _gloffset_GetMinmaxParameterfv, fn)
#define CALL_GetMinmaxParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetMinmaxParameteriv, parameters)
#define GET_GetMinmaxParameteriv(disp) GET_by_offset(disp, _gloffset_GetMinmaxParameteriv)
#define SET_GetMinmaxParameteriv(disp, fn) SET_by_offset(disp, _gloffset_GetMinmaxParameteriv, fn)
#define CALL_Histogram(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizei, GLenum, GLboolean)), _gloffset_Histogram, parameters)
#define GET_Histogram(disp) GET_by_offset(disp, _gloffset_Histogram)
#define SET_Histogram(disp, fn) SET_by_offset(disp, _gloffset_Histogram, fn)
#define CALL_Minmax(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLboolean)), _gloffset_Minmax, parameters)
#define GET_Minmax(disp) GET_by_offset(disp, _gloffset_Minmax)
#define SET_Minmax(disp, fn) SET_by_offset(disp, _gloffset_Minmax, fn)
#define CALL_ResetHistogram(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_ResetHistogram, parameters)
#define GET_ResetHistogram(disp) GET_by_offset(disp, _gloffset_ResetHistogram)
#define SET_ResetHistogram(disp, fn) SET_by_offset(disp, _gloffset_ResetHistogram, fn)
#define CALL_ResetMinmax(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_ResetMinmax, parameters)
#define GET_ResetMinmax(disp) GET_by_offset(disp, _gloffset_ResetMinmax)
#define SET_ResetMinmax(disp, fn) SET_by_offset(disp, _gloffset_ResetMinmax, fn)
#define CALL_TexImage3DOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid *)), _gloffset_TexImage3DOES, parameters)
#define GET_TexImage3DOES(disp) GET_by_offset(disp, _gloffset_TexImage3DOES)
#define SET_TexImage3DOES(disp, fn) SET_by_offset(disp, _gloffset_TexImage3DOES, fn)
#define CALL_TexSubImage3DOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid *)), _gloffset_TexSubImage3DOES, parameters)
#define GET_TexSubImage3DOES(disp) GET_by_offset(disp, _gloffset_TexSubImage3DOES)
#define SET_TexSubImage3DOES(disp, fn) SET_by_offset(disp, _gloffset_TexSubImage3DOES, fn)
#define CALL_CopyTexSubImage3DOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei)), _gloffset_CopyTexSubImage3DOES, parameters)
#define GET_CopyTexSubImage3DOES(disp) GET_by_offset(disp, _gloffset_CopyTexSubImage3DOES)
#define SET_CopyTexSubImage3DOES(disp, fn) SET_by_offset(disp, _gloffset_CopyTexSubImage3DOES, fn)
#define CALL_ActiveTexture(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_ActiveTexture, parameters)
#define GET_ActiveTexture(disp) GET_by_offset(disp, _gloffset_ActiveTexture)
#define SET_ActiveTexture(disp, fn) SET_by_offset(disp, _gloffset_ActiveTexture, fn)
#define CALL_ClientActiveTextureARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_ClientActiveTextureARB, parameters)
#define GET_ClientActiveTextureARB(disp) GET_by_offset(disp, _gloffset_ClientActiveTextureARB)
#define SET_ClientActiveTextureARB(disp, fn) SET_by_offset(disp, _gloffset_ClientActiveTextureARB, fn)
#define CALL_MultiTexCoord1dARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLdouble)), _gloffset_MultiTexCoord1dARB, parameters)
#define GET_MultiTexCoord1dARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord1dARB)
#define SET_MultiTexCoord1dARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord1dARB, fn)
#define CALL_MultiTexCoord1dvARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLdouble *)), _gloffset_MultiTexCoord1dvARB, parameters)
#define GET_MultiTexCoord1dvARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord1dvARB)
#define SET_MultiTexCoord1dvARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord1dvARB, fn)
#define CALL_MultiTexCoord1fARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat)), _gloffset_MultiTexCoord1fARB, parameters)
#define GET_MultiTexCoord1fARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord1fARB)
#define SET_MultiTexCoord1fARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord1fARB, fn)
#define CALL_MultiTexCoord1fvARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfloat *)), _gloffset_MultiTexCoord1fvARB, parameters)
#define GET_MultiTexCoord1fvARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord1fvARB)
#define SET_MultiTexCoord1fvARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord1fvARB, fn)
#define CALL_MultiTexCoord1iARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint)), _gloffset_MultiTexCoord1iARB, parameters)
#define GET_MultiTexCoord1iARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord1iARB)
#define SET_MultiTexCoord1iARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord1iARB, fn)
#define CALL_MultiTexCoord1ivARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLint *)), _gloffset_MultiTexCoord1ivARB, parameters)
#define GET_MultiTexCoord1ivARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord1ivARB)
#define SET_MultiTexCoord1ivARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord1ivARB, fn)
#define CALL_MultiTexCoord1sARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLshort)), _gloffset_MultiTexCoord1sARB, parameters)
#define GET_MultiTexCoord1sARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord1sARB)
#define SET_MultiTexCoord1sARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord1sARB, fn)
#define CALL_MultiTexCoord1svARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLshort *)), _gloffset_MultiTexCoord1svARB, parameters)
#define GET_MultiTexCoord1svARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord1svARB)
#define SET_MultiTexCoord1svARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord1svARB, fn)
#define CALL_MultiTexCoord2dARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLdouble, GLdouble)), _gloffset_MultiTexCoord2dARB, parameters)
#define GET_MultiTexCoord2dARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord2dARB)
#define SET_MultiTexCoord2dARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord2dARB, fn)
#define CALL_MultiTexCoord2dvARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLdouble *)), _gloffset_MultiTexCoord2dvARB, parameters)
#define GET_MultiTexCoord2dvARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord2dvARB)
#define SET_MultiTexCoord2dvARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord2dvARB, fn)
#define CALL_MultiTexCoord2fARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat, GLfloat)), _gloffset_MultiTexCoord2fARB, parameters)
#define GET_MultiTexCoord2fARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord2fARB)
#define SET_MultiTexCoord2fARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord2fARB, fn)
#define CALL_MultiTexCoord2fvARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfloat *)), _gloffset_MultiTexCoord2fvARB, parameters)
#define GET_MultiTexCoord2fvARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord2fvARB)
#define SET_MultiTexCoord2fvARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord2fvARB, fn)
#define CALL_MultiTexCoord2iARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint)), _gloffset_MultiTexCoord2iARB, parameters)
#define GET_MultiTexCoord2iARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord2iARB)
#define SET_MultiTexCoord2iARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord2iARB, fn)
#define CALL_MultiTexCoord2ivARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLint *)), _gloffset_MultiTexCoord2ivARB, parameters)
#define GET_MultiTexCoord2ivARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord2ivARB)
#define SET_MultiTexCoord2ivARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord2ivARB, fn)
#define CALL_MultiTexCoord2sARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLshort, GLshort)), _gloffset_MultiTexCoord2sARB, parameters)
#define GET_MultiTexCoord2sARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord2sARB)
#define SET_MultiTexCoord2sARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord2sARB, fn)
#define CALL_MultiTexCoord2svARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLshort *)), _gloffset_MultiTexCoord2svARB, parameters)
#define GET_MultiTexCoord2svARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord2svARB)
#define SET_MultiTexCoord2svARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord2svARB, fn)
#define CALL_MultiTexCoord3dARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLdouble, GLdouble, GLdouble)), _gloffset_MultiTexCoord3dARB, parameters)
#define GET_MultiTexCoord3dARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord3dARB)
#define SET_MultiTexCoord3dARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord3dARB, fn)
#define CALL_MultiTexCoord3dvARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLdouble *)), _gloffset_MultiTexCoord3dvARB, parameters)
#define GET_MultiTexCoord3dvARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord3dvARB)
#define SET_MultiTexCoord3dvARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord3dvARB, fn)
#define CALL_MultiTexCoord3fARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat, GLfloat, GLfloat)), _gloffset_MultiTexCoord3fARB, parameters)
#define GET_MultiTexCoord3fARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord3fARB)
#define SET_MultiTexCoord3fARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord3fARB, fn)
#define CALL_MultiTexCoord3fvARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfloat *)), _gloffset_MultiTexCoord3fvARB, parameters)
#define GET_MultiTexCoord3fvARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord3fvARB)
#define SET_MultiTexCoord3fvARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord3fvARB, fn)
#define CALL_MultiTexCoord3iARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint)), _gloffset_MultiTexCoord3iARB, parameters)
#define GET_MultiTexCoord3iARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord3iARB)
#define SET_MultiTexCoord3iARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord3iARB, fn)
#define CALL_MultiTexCoord3ivARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLint *)), _gloffset_MultiTexCoord3ivARB, parameters)
#define GET_MultiTexCoord3ivARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord3ivARB)
#define SET_MultiTexCoord3ivARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord3ivARB, fn)
#define CALL_MultiTexCoord3sARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLshort, GLshort, GLshort)), _gloffset_MultiTexCoord3sARB, parameters)
#define GET_MultiTexCoord3sARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord3sARB)
#define SET_MultiTexCoord3sARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord3sARB, fn)
#define CALL_MultiTexCoord3svARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLshort *)), _gloffset_MultiTexCoord3svARB, parameters)
#define GET_MultiTexCoord3svARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord3svARB)
#define SET_MultiTexCoord3svARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord3svARB, fn)
#define CALL_MultiTexCoord4dARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLdouble, GLdouble, GLdouble, GLdouble)), _gloffset_MultiTexCoord4dARB, parameters)
#define GET_MultiTexCoord4dARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord4dARB)
#define SET_MultiTexCoord4dARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord4dARB, fn)
#define CALL_MultiTexCoord4dvARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLdouble *)), _gloffset_MultiTexCoord4dvARB, parameters)
#define GET_MultiTexCoord4dvARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord4dvARB)
#define SET_MultiTexCoord4dvARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord4dvARB, fn)
#define CALL_MultiTexCoord4fARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLfloat, GLfloat, GLfloat, GLfloat)), _gloffset_MultiTexCoord4fARB, parameters)
#define GET_MultiTexCoord4fARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord4fARB)
#define SET_MultiTexCoord4fARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord4fARB, fn)
#define CALL_MultiTexCoord4fvARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLfloat *)), _gloffset_MultiTexCoord4fvARB, parameters)
#define GET_MultiTexCoord4fvARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord4fvARB)
#define SET_MultiTexCoord4fvARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord4fvARB, fn)
#define CALL_MultiTexCoord4iARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLint)), _gloffset_MultiTexCoord4iARB, parameters)
#define GET_MultiTexCoord4iARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord4iARB)
#define SET_MultiTexCoord4iARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord4iARB, fn)
#define CALL_MultiTexCoord4ivARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLint *)), _gloffset_MultiTexCoord4ivARB, parameters)
#define GET_MultiTexCoord4ivARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord4ivARB)
#define SET_MultiTexCoord4ivARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord4ivARB, fn)
#define CALL_MultiTexCoord4sARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLshort, GLshort, GLshort, GLshort)), _gloffset_MultiTexCoord4sARB, parameters)
#define GET_MultiTexCoord4sARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord4sARB)
#define SET_MultiTexCoord4sARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord4sARB, fn)
#define CALL_MultiTexCoord4svARB(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLshort *)), _gloffset_MultiTexCoord4svARB, parameters)
#define GET_MultiTexCoord4svARB(disp) GET_by_offset(disp, _gloffset_MultiTexCoord4svARB)
#define SET_MultiTexCoord4svARB(disp, fn) SET_by_offset(disp, _gloffset_MultiTexCoord4svARB, fn)
#define CALL_GetBufferPointervOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLvoid **)), _gloffset_GetBufferPointervOES, parameters)
#define GET_GetBufferPointervOES(disp) GET_by_offset(disp, _gloffset_GetBufferPointervOES)
#define SET_GetBufferPointervOES(disp, fn) SET_by_offset(disp, _gloffset_GetBufferPointervOES, fn)
#define CALL_MapBufferOES(disp, parameters) CALL_by_offset(disp, (GLvoid * (GLAPIENTRYP)(GLenum, GLenum)), _gloffset_MapBufferOES, parameters)
#define GET_MapBufferOES(disp) GET_by_offset(disp, _gloffset_MapBufferOES)
#define SET_MapBufferOES(disp, fn) SET_by_offset(disp, _gloffset_MapBufferOES, fn)
#define CALL_UnmapBufferOES(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLenum)), _gloffset_UnmapBufferOES, parameters)
#define GET_UnmapBufferOES(disp) GET_by_offset(disp, _gloffset_UnmapBufferOES)
#define SET_UnmapBufferOES(disp, fn) SET_by_offset(disp, _gloffset_UnmapBufferOES, fn)
#define CALL_CompressedTexImage3DOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const GLvoid *)), _gloffset_CompressedTexImage3DOES, parameters)
#define GET_CompressedTexImage3DOES(disp) GET_by_offset(disp, _gloffset_CompressedTexImage3DOES)
#define SET_CompressedTexImage3DOES(disp, fn) SET_by_offset(disp, _gloffset_CompressedTexImage3DOES, fn)
#define CALL_CompressedTexSubImage3DOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid *)), _gloffset_CompressedTexSubImage3DOES, parameters)
#define GET_CompressedTexSubImage3DOES(disp) GET_by_offset(disp, _gloffset_CompressedTexSubImage3DOES)
#define SET_CompressedTexSubImage3DOES(disp, fn) SET_by_offset(disp, _gloffset_CompressedTexSubImage3DOES, fn)
#define CALL_FramebufferTexture3DOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLuint, GLint, GLint)), _gloffset_FramebufferTexture3DOES, parameters)
#define GET_FramebufferTexture3DOES(disp) GET_by_offset(disp, _gloffset_FramebufferTexture3DOES)
#define SET_FramebufferTexture3DOES(disp, fn) SET_by_offset(disp, _gloffset_FramebufferTexture3DOES, fn)
#define CALL_GetProgramBinaryOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLsizei, GLsizei *, GLenum *, GLvoid *)), _gloffset_GetProgramBinaryOES, parameters)
#define GET_GetProgramBinaryOES(disp) GET_by_offset(disp, _gloffset_GetProgramBinaryOES)
#define SET_GetProgramBinaryOES(disp, fn) SET_by_offset(disp, _gloffset_GetProgramBinaryOES, fn)
#define CALL_ProgramBinaryOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLenum, const GLvoid *, GLint)), _gloffset_ProgramBinaryOES, parameters)
#define GET_ProgramBinaryOES(disp) GET_by_offset(disp, _gloffset_ProgramBinaryOES)
#define SET_ProgramBinaryOES(disp, fn) SET_by_offset(disp, _gloffset_ProgramBinaryOES, fn)
#define CALL_MultiDrawArraysEXT(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLint *, const GLsizei *, GLsizei)), _gloffset_MultiDrawArraysEXT, parameters)
#define GET_MultiDrawArraysEXT(disp) GET_by_offset(disp, _gloffset_MultiDrawArraysEXT)
#define SET_MultiDrawArraysEXT(disp, fn) SET_by_offset(disp, _gloffset_MultiDrawArraysEXT, fn)
#define CALL_MultiDrawElementsEXT(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, const GLsizei *, GLenum, const GLvoid **, GLsizei)), _gloffset_MultiDrawElementsEXT, parameters)
#define GET_MultiDrawElementsEXT(disp) GET_by_offset(disp, _gloffset_MultiDrawElementsEXT)
#define SET_MultiDrawElementsEXT(disp, fn) SET_by_offset(disp, _gloffset_MultiDrawElementsEXT, fn)
#define CALL_BindVertexArrayAPPLE(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_BindVertexArrayAPPLE, parameters)
#define GET_BindVertexArrayAPPLE(disp) GET_by_offset(disp, _gloffset_BindVertexArrayAPPLE)
#define SET_BindVertexArrayAPPLE(disp, fn) SET_by_offset(disp, _gloffset_BindVertexArrayAPPLE, fn)
#define CALL_DeleteVertexArraysAPPLE(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *)), _gloffset_DeleteVertexArraysAPPLE, parameters)
#define GET_DeleteVertexArraysAPPLE(disp) GET_by_offset(disp, _gloffset_DeleteVertexArraysAPPLE)
#define SET_DeleteVertexArraysAPPLE(disp, fn) SET_by_offset(disp, _gloffset_DeleteVertexArraysAPPLE, fn)
#define CALL_GenVertexArraysAPPLE(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), _gloffset_GenVertexArraysAPPLE, parameters)
#define GET_GenVertexArraysAPPLE(disp) GET_by_offset(disp, _gloffset_GenVertexArraysAPPLE)
#define SET_GenVertexArraysAPPLE(disp, fn) SET_by_offset(disp, _gloffset_GenVertexArraysAPPLE, fn)
#define CALL_IsVertexArrayAPPLE(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), _gloffset_IsVertexArrayAPPLE, parameters)
#define GET_IsVertexArrayAPPLE(disp) GET_by_offset(disp, _gloffset_IsVertexArrayAPPLE)
#define SET_IsVertexArrayAPPLE(disp, fn) SET_by_offset(disp, _gloffset_IsVertexArrayAPPLE, fn)
#define CALL_EGLImageTargetRenderbufferStorageOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLvoid *)), _gloffset_EGLImageTargetRenderbufferStorageOES, parameters)
#define GET_EGLImageTargetRenderbufferStorageOES(disp) GET_by_offset(disp, _gloffset_EGLImageTargetRenderbufferStorageOES)
#define SET_EGLImageTargetRenderbufferStorageOES(disp, fn) SET_by_offset(disp, _gloffset_EGLImageTargetRenderbufferStorageOES, fn)
#define CALL_EGLImageTargetTexture2DOES(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLvoid *)), _gloffset_EGLImageTargetTexture2DOES, parameters)
#define GET_EGLImageTargetTexture2DOES(disp) GET_by_offset(disp, _gloffset_EGLImageTargetTexture2DOES)
#define SET_EGLImageTargetTexture2DOES(disp, fn) SET_by_offset(disp, _gloffset_EGLImageTargetTexture2DOES, fn)
#define CALL_CompressedTexImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const GLvoid *)), _gloffset_CompressedTexImage2D, parameters)
#define GET_CompressedTexImage2D(disp) GET_by_offset(disp, _gloffset_CompressedTexImage2D)
#define SET_CompressedTexImage2D(disp, fn) SET_by_offset(disp, _gloffset_CompressedTexImage2D, fn)
#define CALL_CompressedTexSubImage2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid *)), _gloffset_CompressedTexSubImage2D, parameters)
#define GET_CompressedTexSubImage2D(disp) GET_by_offset(disp, _gloffset_CompressedTexSubImage2D)
#define SET_CompressedTexSubImage2D(disp, fn) SET_by_offset(disp, _gloffset_CompressedTexSubImage2D, fn)
#define CALL_SampleCoverage(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampf, GLboolean)), _gloffset_SampleCoverage, parameters)
#define GET_SampleCoverage(disp) GET_by_offset(disp, _gloffset_SampleCoverage)
#define SET_SampleCoverage(disp, fn) SET_by_offset(disp, _gloffset_SampleCoverage, fn)
#define CALL_BindBuffer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint)), _gloffset_BindBuffer, parameters)
#define GET_BindBuffer(disp) GET_by_offset(disp, _gloffset_BindBuffer)
#define SET_BindBuffer(disp, fn) SET_by_offset(disp, _gloffset_BindBuffer, fn)
#define CALL_BufferData(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLsizeiptr, const GLvoid *, GLenum)), _gloffset_BufferData, parameters)
#define GET_BufferData(disp) GET_by_offset(disp, _gloffset_BufferData)
#define SET_BufferData(disp, fn) SET_by_offset(disp, _gloffset_BufferData, fn)
#define CALL_BufferSubData(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLintptr, GLsizeiptr, const GLvoid *)), _gloffset_BufferSubData, parameters)
#define GET_BufferSubData(disp) GET_by_offset(disp, _gloffset_BufferSubData)
#define SET_BufferSubData(disp, fn) SET_by_offset(disp, _gloffset_BufferSubData, fn)
#define CALL_DeleteBuffers(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *)), _gloffset_DeleteBuffers, parameters)
#define GET_DeleteBuffers(disp) GET_by_offset(disp, _gloffset_DeleteBuffers)
#define SET_DeleteBuffers(disp, fn) SET_by_offset(disp, _gloffset_DeleteBuffers, fn)
#define CALL_GenBuffers(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), _gloffset_GenBuffers, parameters)
#define GET_GenBuffers(disp) GET_by_offset(disp, _gloffset_GenBuffers)
#define SET_GenBuffers(disp, fn) SET_by_offset(disp, _gloffset_GenBuffers, fn)
#define CALL_GetBufferParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetBufferParameteriv, parameters)
#define GET_GetBufferParameteriv(disp) GET_by_offset(disp, _gloffset_GetBufferParameteriv)
#define SET_GetBufferParameteriv(disp, fn) SET_by_offset(disp, _gloffset_GetBufferParameteriv, fn)
#define CALL_IsBuffer(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), _gloffset_IsBuffer, parameters)
#define GET_IsBuffer(disp) GET_by_offset(disp, _gloffset_IsBuffer)
#define SET_IsBuffer(disp, fn) SET_by_offset(disp, _gloffset_IsBuffer, fn)
#define CALL_AttachShader(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLuint)), _gloffset_AttachShader, parameters)
#define GET_AttachShader(disp) GET_by_offset(disp, _gloffset_AttachShader)
#define SET_AttachShader(disp, fn) SET_by_offset(disp, _gloffset_AttachShader, fn)
#define CALL_BindAttribLocation(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLuint, const GLchar *)), _gloffset_BindAttribLocation, parameters)
#define GET_BindAttribLocation(disp) GET_by_offset(disp, _gloffset_BindAttribLocation)
#define SET_BindAttribLocation(disp, fn) SET_by_offset(disp, _gloffset_BindAttribLocation, fn)
#define CALL_BlendEquationSeparate(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum)), _gloffset_BlendEquationSeparate, parameters)
#define GET_BlendEquationSeparate(disp) GET_by_offset(disp, _gloffset_BlendEquationSeparate)
#define SET_BlendEquationSeparate(disp, fn) SET_by_offset(disp, _gloffset_BlendEquationSeparate, fn)
#define CALL_CompileShader(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_CompileShader, parameters)
#define GET_CompileShader(disp) GET_by_offset(disp, _gloffset_CompileShader)
#define SET_CompileShader(disp, fn) SET_by_offset(disp, _gloffset_CompileShader, fn)
#define CALL_CreateProgram(disp, parameters) CALL_by_offset(disp, (GLuint (GLAPIENTRYP)(void)), _gloffset_CreateProgram, parameters)
#define GET_CreateProgram(disp) GET_by_offset(disp, _gloffset_CreateProgram)
#define SET_CreateProgram(disp, fn) SET_by_offset(disp, _gloffset_CreateProgram, fn)
#define CALL_CreateShader(disp, parameters) CALL_by_offset(disp, (GLuint (GLAPIENTRYP)(GLenum)), _gloffset_CreateShader, parameters)
#define GET_CreateShader(disp) GET_by_offset(disp, _gloffset_CreateShader)
#define SET_CreateShader(disp, fn) SET_by_offset(disp, _gloffset_CreateShader, fn)
#define CALL_DeleteProgram(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_DeleteProgram, parameters)
#define GET_DeleteProgram(disp) GET_by_offset(disp, _gloffset_DeleteProgram)
#define SET_DeleteProgram(disp, fn) SET_by_offset(disp, _gloffset_DeleteProgram, fn)
#define CALL_DeleteShader(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_DeleteShader, parameters)
#define GET_DeleteShader(disp) GET_by_offset(disp, _gloffset_DeleteShader)
#define SET_DeleteShader(disp, fn) SET_by_offset(disp, _gloffset_DeleteShader, fn)
#define CALL_DetachShader(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLuint)), _gloffset_DetachShader, parameters)
#define GET_DetachShader(disp) GET_by_offset(disp, _gloffset_DetachShader)
#define SET_DetachShader(disp, fn) SET_by_offset(disp, _gloffset_DetachShader, fn)
#define CALL_DisableVertexAttribArray(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_DisableVertexAttribArray, parameters)
#define GET_DisableVertexAttribArray(disp) GET_by_offset(disp, _gloffset_DisableVertexAttribArray)
#define SET_DisableVertexAttribArray(disp, fn) SET_by_offset(disp, _gloffset_DisableVertexAttribArray, fn)
#define CALL_EnableVertexAttribArray(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_EnableVertexAttribArray, parameters)
#define GET_EnableVertexAttribArray(disp) GET_by_offset(disp, _gloffset_EnableVertexAttribArray)
#define SET_EnableVertexAttribArray(disp, fn) SET_by_offset(disp, _gloffset_EnableVertexAttribArray, fn)
#define CALL_GetActiveAttrib(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLuint, GLsizei , GLsizei *, GLint *, GLenum *, GLchar *)), _gloffset_GetActiveAttrib, parameters)
#define GET_GetActiveAttrib(disp) GET_by_offset(disp, _gloffset_GetActiveAttrib)
#define SET_GetActiveAttrib(disp, fn) SET_by_offset(disp, _gloffset_GetActiveAttrib, fn)
#define CALL_GetActiveUniform(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLuint, GLsizei, GLsizei *, GLint *, GLenum *, GLchar *)), _gloffset_GetActiveUniform, parameters)
#define GET_GetActiveUniform(disp) GET_by_offset(disp, _gloffset_GetActiveUniform)
#define SET_GetActiveUniform(disp, fn) SET_by_offset(disp, _gloffset_GetActiveUniform, fn)
#define CALL_GetAttachedShaders(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLsizei, GLsizei *, GLuint *)), _gloffset_GetAttachedShaders, parameters)
#define GET_GetAttachedShaders(disp) GET_by_offset(disp, _gloffset_GetAttachedShaders)
#define SET_GetAttachedShaders(disp, fn) SET_by_offset(disp, _gloffset_GetAttachedShaders, fn)
#define CALL_GetAttribLocation(disp, parameters) CALL_by_offset(disp, (GLint (GLAPIENTRYP)(GLuint, const GLchar *)), _gloffset_GetAttribLocation, parameters)
#define GET_GetAttribLocation(disp) GET_by_offset(disp, _gloffset_GetAttribLocation)
#define SET_GetAttribLocation(disp, fn) SET_by_offset(disp, _gloffset_GetAttribLocation, fn)
#define CALL_GetProgramInfoLog(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLsizei, GLsizei *, GLchar *)), _gloffset_GetProgramInfoLog, parameters)
#define GET_GetProgramInfoLog(disp) GET_by_offset(disp, _gloffset_GetProgramInfoLog)
#define SET_GetProgramInfoLog(disp, fn) SET_by_offset(disp, _gloffset_GetProgramInfoLog, fn)
#define CALL_GetProgramiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLenum, GLint *)), _gloffset_GetProgramiv, parameters)
#define GET_GetProgramiv(disp) GET_by_offset(disp, _gloffset_GetProgramiv)
#define SET_GetProgramiv(disp, fn) SET_by_offset(disp, _gloffset_GetProgramiv, fn)
#define CALL_GetShaderInfoLog(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLsizei, GLsizei *, GLchar *)), _gloffset_GetShaderInfoLog, parameters)
#define GET_GetShaderInfoLog(disp) GET_by_offset(disp, _gloffset_GetShaderInfoLog)
#define SET_GetShaderInfoLog(disp, fn) SET_by_offset(disp, _gloffset_GetShaderInfoLog, fn)
#define CALL_GetShaderSource(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLsizei, GLsizei *, GLchar *)), _gloffset_GetShaderSource, parameters)
#define GET_GetShaderSource(disp) GET_by_offset(disp, _gloffset_GetShaderSource)
#define SET_GetShaderSource(disp, fn) SET_by_offset(disp, _gloffset_GetShaderSource, fn)
#define CALL_GetShaderiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLenum, GLint *)), _gloffset_GetShaderiv, parameters)
#define GET_GetShaderiv(disp) GET_by_offset(disp, _gloffset_GetShaderiv)
#define SET_GetShaderiv(disp, fn) SET_by_offset(disp, _gloffset_GetShaderiv, fn)
#define CALL_GetUniformLocation(disp, parameters) CALL_by_offset(disp, (GLint (GLAPIENTRYP)(GLuint, const GLchar *)), _gloffset_GetUniformLocation, parameters)
#define GET_GetUniformLocation(disp) GET_by_offset(disp, _gloffset_GetUniformLocation)
#define SET_GetUniformLocation(disp, fn) SET_by_offset(disp, _gloffset_GetUniformLocation, fn)
#define CALL_GetUniformfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLint, GLfloat *)), _gloffset_GetUniformfv, parameters)
#define GET_GetUniformfv(disp) GET_by_offset(disp, _gloffset_GetUniformfv)
#define SET_GetUniformfv(disp, fn) SET_by_offset(disp, _gloffset_GetUniformfv, fn)
#define CALL_GetUniformiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLint, GLint *)), _gloffset_GetUniformiv, parameters)
#define GET_GetUniformiv(disp) GET_by_offset(disp, _gloffset_GetUniformiv)
#define SET_GetUniformiv(disp, fn) SET_by_offset(disp, _gloffset_GetUniformiv, fn)
#define CALL_GetVertexAttribPointerv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLenum, GLvoid **)), _gloffset_GetVertexAttribPointerv, parameters)
#define GET_GetVertexAttribPointerv(disp) GET_by_offset(disp, _gloffset_GetVertexAttribPointerv)
#define SET_GetVertexAttribPointerv(disp, fn) SET_by_offset(disp, _gloffset_GetVertexAttribPointerv, fn)
#define CALL_GetVertexAttribfv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLenum, GLfloat *)), _gloffset_GetVertexAttribfv, parameters)
#define GET_GetVertexAttribfv(disp) GET_by_offset(disp, _gloffset_GetVertexAttribfv)
#define SET_GetVertexAttribfv(disp, fn) SET_by_offset(disp, _gloffset_GetVertexAttribfv, fn)
#define CALL_GetVertexAttribiv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLenum, GLint *)), _gloffset_GetVertexAttribiv, parameters)
#define GET_GetVertexAttribiv(disp) GET_by_offset(disp, _gloffset_GetVertexAttribiv)
#define SET_GetVertexAttribiv(disp, fn) SET_by_offset(disp, _gloffset_GetVertexAttribiv, fn)
#define CALL_IsProgram(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), _gloffset_IsProgram, parameters)
#define GET_IsProgram(disp) GET_by_offset(disp, _gloffset_IsProgram)
#define SET_IsProgram(disp, fn) SET_by_offset(disp, _gloffset_IsProgram, fn)
#define CALL_IsShader(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), _gloffset_IsShader, parameters)
#define GET_IsShader(disp) GET_by_offset(disp, _gloffset_IsShader)
#define SET_IsShader(disp, fn) SET_by_offset(disp, _gloffset_IsShader, fn)
#define CALL_LinkProgram(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_LinkProgram, parameters)
#define GET_LinkProgram(disp) GET_by_offset(disp, _gloffset_LinkProgram)
#define SET_LinkProgram(disp, fn) SET_by_offset(disp, _gloffset_LinkProgram, fn)
#define CALL_ShaderSource(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLsizei, const GLchar **, const GLint *)), _gloffset_ShaderSource, parameters)
#define GET_ShaderSource(disp) GET_by_offset(disp, _gloffset_ShaderSource)
#define SET_ShaderSource(disp, fn) SET_by_offset(disp, _gloffset_ShaderSource, fn)
#define CALL_StencilFuncSeparate(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint, GLuint)), _gloffset_StencilFuncSeparate, parameters)
#define GET_StencilFuncSeparate(disp) GET_by_offset(disp, _gloffset_StencilFuncSeparate)
#define SET_StencilFuncSeparate(disp, fn) SET_by_offset(disp, _gloffset_StencilFuncSeparate, fn)
#define CALL_StencilMaskSeparate(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint)), _gloffset_StencilMaskSeparate, parameters)
#define GET_StencilMaskSeparate(disp) GET_by_offset(disp, _gloffset_StencilMaskSeparate)
#define SET_StencilMaskSeparate(disp, fn) SET_by_offset(disp, _gloffset_StencilMaskSeparate, fn)
#define CALL_StencilOpSeparate(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLenum)), _gloffset_StencilOpSeparate, parameters)
#define GET_StencilOpSeparate(disp) GET_by_offset(disp, _gloffset_StencilOpSeparate)
#define SET_StencilOpSeparate(disp, fn) SET_by_offset(disp, _gloffset_StencilOpSeparate, fn)
#define CALL_Uniform1f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLfloat)), _gloffset_Uniform1f, parameters)
#define GET_Uniform1f(disp) GET_by_offset(disp, _gloffset_Uniform1f)
#define SET_Uniform1f(disp, fn) SET_by_offset(disp, _gloffset_Uniform1f, fn)
#define CALL_Uniform1fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, const GLfloat *)), _gloffset_Uniform1fv, parameters)
#define GET_Uniform1fv(disp) GET_by_offset(disp, _gloffset_Uniform1fv)
#define SET_Uniform1fv(disp, fn) SET_by_offset(disp, _gloffset_Uniform1fv, fn)
#define CALL_Uniform1i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint)), _gloffset_Uniform1i, parameters)
#define GET_Uniform1i(disp) GET_by_offset(disp, _gloffset_Uniform1i)
#define SET_Uniform1i(disp, fn) SET_by_offset(disp, _gloffset_Uniform1i, fn)
#define CALL_Uniform1iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, const GLint *)), _gloffset_Uniform1iv, parameters)
#define GET_Uniform1iv(disp) GET_by_offset(disp, _gloffset_Uniform1iv)
#define SET_Uniform1iv(disp, fn) SET_by_offset(disp, _gloffset_Uniform1iv, fn)
#define CALL_Uniform2f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLfloat, GLfloat)), _gloffset_Uniform2f, parameters)
#define GET_Uniform2f(disp) GET_by_offset(disp, _gloffset_Uniform2f)
#define SET_Uniform2f(disp, fn) SET_by_offset(disp, _gloffset_Uniform2f, fn)
#define CALL_Uniform2fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, const GLfloat *)), _gloffset_Uniform2fv, parameters)
#define GET_Uniform2fv(disp) GET_by_offset(disp, _gloffset_Uniform2fv)
#define SET_Uniform2fv(disp, fn) SET_by_offset(disp, _gloffset_Uniform2fv, fn)
#define CALL_Uniform2i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint)), _gloffset_Uniform2i, parameters)
#define GET_Uniform2i(disp) GET_by_offset(disp, _gloffset_Uniform2i)
#define SET_Uniform2i(disp, fn) SET_by_offset(disp, _gloffset_Uniform2i, fn)
#define CALL_Uniform2iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, const GLint *)), _gloffset_Uniform2iv, parameters)
#define GET_Uniform2iv(disp) GET_by_offset(disp, _gloffset_Uniform2iv)
#define SET_Uniform2iv(disp, fn) SET_by_offset(disp, _gloffset_Uniform2iv, fn)
#define CALL_Uniform3f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLfloat, GLfloat, GLfloat)), _gloffset_Uniform3f, parameters)
#define GET_Uniform3f(disp) GET_by_offset(disp, _gloffset_Uniform3f)
#define SET_Uniform3f(disp, fn) SET_by_offset(disp, _gloffset_Uniform3f, fn)
#define CALL_Uniform3fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, const GLfloat *)), _gloffset_Uniform3fv, parameters)
#define GET_Uniform3fv(disp) GET_by_offset(disp, _gloffset_Uniform3fv)
#define SET_Uniform3fv(disp, fn) SET_by_offset(disp, _gloffset_Uniform3fv, fn)
#define CALL_Uniform3i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint, GLint)), _gloffset_Uniform3i, parameters)
#define GET_Uniform3i(disp) GET_by_offset(disp, _gloffset_Uniform3i)
#define SET_Uniform3i(disp, fn) SET_by_offset(disp, _gloffset_Uniform3i, fn)
#define CALL_Uniform3iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, const GLint *)), _gloffset_Uniform3iv, parameters)
#define GET_Uniform3iv(disp) GET_by_offset(disp, _gloffset_Uniform3iv)
#define SET_Uniform3iv(disp, fn) SET_by_offset(disp, _gloffset_Uniform3iv, fn)
#define CALL_Uniform4f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLfloat, GLfloat, GLfloat, GLfloat)), _gloffset_Uniform4f, parameters)
#define GET_Uniform4f(disp) GET_by_offset(disp, _gloffset_Uniform4f)
#define SET_Uniform4f(disp, fn) SET_by_offset(disp, _gloffset_Uniform4f, fn)
#define CALL_Uniform4fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, const GLfloat *)), _gloffset_Uniform4fv, parameters)
#define GET_Uniform4fv(disp) GET_by_offset(disp, _gloffset_Uniform4fv)
#define SET_Uniform4fv(disp, fn) SET_by_offset(disp, _gloffset_Uniform4fv, fn)
#define CALL_Uniform4i(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLint, GLint, GLint, GLint)), _gloffset_Uniform4i, parameters)
#define GET_Uniform4i(disp) GET_by_offset(disp, _gloffset_Uniform4i)
#define SET_Uniform4i(disp, fn) SET_by_offset(disp, _gloffset_Uniform4i, fn)
#define CALL_Uniform4iv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, const GLint *)), _gloffset_Uniform4iv, parameters)
#define GET_Uniform4iv(disp) GET_by_offset(disp, _gloffset_Uniform4iv)
#define SET_Uniform4iv(disp, fn) SET_by_offset(disp, _gloffset_Uniform4iv, fn)
#define CALL_UniformMatrix2fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, GLboolean, const GLfloat *)), _gloffset_UniformMatrix2fv, parameters)
#define GET_UniformMatrix2fv(disp) GET_by_offset(disp, _gloffset_UniformMatrix2fv)
#define SET_UniformMatrix2fv(disp, fn) SET_by_offset(disp, _gloffset_UniformMatrix2fv, fn)
#define CALL_UniformMatrix3fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, GLboolean, const GLfloat *)), _gloffset_UniformMatrix3fv, parameters)
#define GET_UniformMatrix3fv(disp) GET_by_offset(disp, _gloffset_UniformMatrix3fv)
#define SET_UniformMatrix3fv(disp, fn) SET_by_offset(disp, _gloffset_UniformMatrix3fv, fn)
#define CALL_UniformMatrix4fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLint, GLsizei, GLboolean, const GLfloat *)), _gloffset_UniformMatrix4fv, parameters)
#define GET_UniformMatrix4fv(disp) GET_by_offset(disp, _gloffset_UniformMatrix4fv)
#define SET_UniformMatrix4fv(disp, fn) SET_by_offset(disp, _gloffset_UniformMatrix4fv, fn)
#define CALL_UseProgram(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_UseProgram, parameters)
#define GET_UseProgram(disp) GET_by_offset(disp, _gloffset_UseProgram)
#define SET_UseProgram(disp, fn) SET_by_offset(disp, _gloffset_UseProgram, fn)
#define CALL_ValidateProgram(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint)), _gloffset_ValidateProgram, parameters)
#define GET_ValidateProgram(disp) GET_by_offset(disp, _gloffset_ValidateProgram)
#define SET_ValidateProgram(disp, fn) SET_by_offset(disp, _gloffset_ValidateProgram, fn)
#define CALL_VertexAttrib1f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLfloat)), _gloffset_VertexAttrib1f, parameters)
#define GET_VertexAttrib1f(disp) GET_by_offset(disp, _gloffset_VertexAttrib1f)
#define SET_VertexAttrib1f(disp, fn) SET_by_offset(disp, _gloffset_VertexAttrib1f, fn)
#define CALL_VertexAttrib1fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, const GLfloat *)), _gloffset_VertexAttrib1fv, parameters)
#define GET_VertexAttrib1fv(disp) GET_by_offset(disp, _gloffset_VertexAttrib1fv)
#define SET_VertexAttrib1fv(disp, fn) SET_by_offset(disp, _gloffset_VertexAttrib1fv, fn)
#define CALL_VertexAttrib2f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLfloat, GLfloat)), _gloffset_VertexAttrib2f, parameters)
#define GET_VertexAttrib2f(disp) GET_by_offset(disp, _gloffset_VertexAttrib2f)
#define SET_VertexAttrib2f(disp, fn) SET_by_offset(disp, _gloffset_VertexAttrib2f, fn)
#define CALL_VertexAttrib2fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, const GLfloat *)), _gloffset_VertexAttrib2fv, parameters)
#define GET_VertexAttrib2fv(disp) GET_by_offset(disp, _gloffset_VertexAttrib2fv)
#define SET_VertexAttrib2fv(disp, fn) SET_by_offset(disp, _gloffset_VertexAttrib2fv, fn)
#define CALL_VertexAttrib3f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLfloat, GLfloat, GLfloat)), _gloffset_VertexAttrib3f, parameters)
#define GET_VertexAttrib3f(disp) GET_by_offset(disp, _gloffset_VertexAttrib3f)
#define SET_VertexAttrib3f(disp, fn) SET_by_offset(disp, _gloffset_VertexAttrib3f, fn)
#define CALL_VertexAttrib3fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, const GLfloat *)), _gloffset_VertexAttrib3fv, parameters)
#define GET_VertexAttrib3fv(disp) GET_by_offset(disp, _gloffset_VertexAttrib3fv)
#define SET_VertexAttrib3fv(disp, fn) SET_by_offset(disp, _gloffset_VertexAttrib3fv, fn)
#define CALL_VertexAttrib4f(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat)), _gloffset_VertexAttrib4f, parameters)
#define GET_VertexAttrib4f(disp) GET_by_offset(disp, _gloffset_VertexAttrib4f)
#define SET_VertexAttrib4f(disp, fn) SET_by_offset(disp, _gloffset_VertexAttrib4f, fn)
#define CALL_VertexAttrib4fv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, const GLfloat *)), _gloffset_VertexAttrib4fv, parameters)
#define GET_VertexAttrib4fv(disp) GET_by_offset(disp, _gloffset_VertexAttrib4fv)
#define SET_VertexAttrib4fv(disp, fn) SET_by_offset(disp, _gloffset_VertexAttrib4fv, fn)
#define CALL_VertexAttribPointer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid *)), _gloffset_VertexAttribPointer, parameters)
#define GET_VertexAttribPointer(disp) GET_by_offset(disp, _gloffset_VertexAttribPointer)
#define SET_VertexAttribPointer(disp, fn) SET_by_offset(disp, _gloffset_VertexAttribPointer, fn)
#define CALL_BlendFuncSeparate(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLenum)), _gloffset_BlendFuncSeparate, parameters)
#define GET_BlendFuncSeparate(disp) GET_by_offset(disp, _gloffset_BlendFuncSeparate)
#define SET_BlendFuncSeparate(disp, fn) SET_by_offset(disp, _gloffset_BlendFuncSeparate, fn)
#define CALL_BindFramebuffer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint)), _gloffset_BindFramebuffer, parameters)
#define GET_BindFramebuffer(disp) GET_by_offset(disp, _gloffset_BindFramebuffer)
#define SET_BindFramebuffer(disp, fn) SET_by_offset(disp, _gloffset_BindFramebuffer, fn)
#define CALL_BindRenderbuffer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLuint)), _gloffset_BindRenderbuffer, parameters)
#define GET_BindRenderbuffer(disp) GET_by_offset(disp, _gloffset_BindRenderbuffer)
#define SET_BindRenderbuffer(disp, fn) SET_by_offset(disp, _gloffset_BindRenderbuffer, fn)
#define CALL_CheckFramebufferStatus(disp, parameters) CALL_by_offset(disp, (GLenum (GLAPIENTRYP)(GLenum)), _gloffset_CheckFramebufferStatus, parameters)
#define GET_CheckFramebufferStatus(disp) GET_by_offset(disp, _gloffset_CheckFramebufferStatus)
#define SET_CheckFramebufferStatus(disp, fn) SET_by_offset(disp, _gloffset_CheckFramebufferStatus, fn)
#define CALL_ClearDepthf(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampf)), _gloffset_ClearDepthf, parameters)
#define GET_ClearDepthf(disp) GET_by_offset(disp, _gloffset_ClearDepthf)
#define SET_ClearDepthf(disp, fn) SET_by_offset(disp, _gloffset_ClearDepthf, fn)
#define CALL_DeleteFramebuffers(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *)), _gloffset_DeleteFramebuffers, parameters)
#define GET_DeleteFramebuffers(disp) GET_by_offset(disp, _gloffset_DeleteFramebuffers)
#define SET_DeleteFramebuffers(disp, fn) SET_by_offset(disp, _gloffset_DeleteFramebuffers, fn)
#define CALL_DeleteRenderbuffers(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *)), _gloffset_DeleteRenderbuffers, parameters)
#define GET_DeleteRenderbuffers(disp) GET_by_offset(disp, _gloffset_DeleteRenderbuffers)
#define SET_DeleteRenderbuffers(disp, fn) SET_by_offset(disp, _gloffset_DeleteRenderbuffers, fn)
#define CALL_DepthRangef(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLclampf, GLclampf)), _gloffset_DepthRangef, parameters)
#define GET_DepthRangef(disp) GET_by_offset(disp, _gloffset_DepthRangef)
#define SET_DepthRangef(disp, fn) SET_by_offset(disp, _gloffset_DepthRangef, fn)
#define CALL_FramebufferRenderbuffer(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLuint)), _gloffset_FramebufferRenderbuffer, parameters)
#define GET_FramebufferRenderbuffer(disp) GET_by_offset(disp, _gloffset_FramebufferRenderbuffer)
#define SET_FramebufferRenderbuffer(disp, fn) SET_by_offset(disp, _gloffset_FramebufferRenderbuffer, fn)
#define CALL_FramebufferTexture2D(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLuint, GLint)), _gloffset_FramebufferTexture2D, parameters)
#define GET_FramebufferTexture2D(disp) GET_by_offset(disp, _gloffset_FramebufferTexture2D)
#define SET_FramebufferTexture2D(disp, fn) SET_by_offset(disp, _gloffset_FramebufferTexture2D, fn)
#define CALL_GenFramebuffers(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), _gloffset_GenFramebuffers, parameters)
#define GET_GenFramebuffers(disp) GET_by_offset(disp, _gloffset_GenFramebuffers)
#define SET_GenFramebuffers(disp, fn) SET_by_offset(disp, _gloffset_GenFramebuffers, fn)
#define CALL_GenRenderbuffers(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, GLuint *)), _gloffset_GenRenderbuffers, parameters)
#define GET_GenRenderbuffers(disp) GET_by_offset(disp, _gloffset_GenRenderbuffers)
#define SET_GenRenderbuffers(disp, fn) SET_by_offset(disp, _gloffset_GenRenderbuffers, fn)
#define CALL_GenerateMipmap(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum)), _gloffset_GenerateMipmap, parameters)
#define GET_GenerateMipmap(disp) GET_by_offset(disp, _gloffset_GenerateMipmap)
#define SET_GenerateMipmap(disp, fn) SET_by_offset(disp, _gloffset_GenerateMipmap, fn)
#define CALL_GetFramebufferAttachmentParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLenum, GLint *)), _gloffset_GetFramebufferAttachmentParameteriv, parameters)
#define GET_GetFramebufferAttachmentParameteriv(disp) GET_by_offset(disp, _gloffset_GetFramebufferAttachmentParameteriv)
#define SET_GetFramebufferAttachmentParameteriv(disp, fn) SET_by_offset(disp, _gloffset_GetFramebufferAttachmentParameteriv, fn)
#define CALL_GetRenderbufferParameteriv(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *)), _gloffset_GetRenderbufferParameteriv, parameters)
#define GET_GetRenderbufferParameteriv(disp) GET_by_offset(disp, _gloffset_GetRenderbufferParameteriv)
#define SET_GetRenderbufferParameteriv(disp, fn) SET_by_offset(disp, _gloffset_GetRenderbufferParameteriv, fn)
#define CALL_GetShaderPrecisionFormat(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLint *, GLint *)), _gloffset_GetShaderPrecisionFormat, parameters)
#define GET_GetShaderPrecisionFormat(disp) GET_by_offset(disp, _gloffset_GetShaderPrecisionFormat)
#define SET_GetShaderPrecisionFormat(disp, fn) SET_by_offset(disp, _gloffset_GetShaderPrecisionFormat, fn)
#define CALL_IsFramebuffer(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), _gloffset_IsFramebuffer, parameters)
#define GET_IsFramebuffer(disp) GET_by_offset(disp, _gloffset_IsFramebuffer)
#define SET_IsFramebuffer(disp, fn) SET_by_offset(disp, _gloffset_IsFramebuffer, fn)
#define CALL_IsRenderbuffer(disp, parameters) CALL_by_offset(disp, (GLboolean (GLAPIENTRYP)(GLuint)), _gloffset_IsRenderbuffer, parameters)
#define GET_IsRenderbuffer(disp) GET_by_offset(disp, _gloffset_IsRenderbuffer)
#define SET_IsRenderbuffer(disp, fn) SET_by_offset(disp, _gloffset_IsRenderbuffer, fn)
#define CALL_ReleaseShaderCompiler(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(void)), _gloffset_ReleaseShaderCompiler, parameters)
#define GET_ReleaseShaderCompiler(disp) GET_by_offset(disp, _gloffset_ReleaseShaderCompiler)
#define SET_ReleaseShaderCompiler(disp, fn) SET_by_offset(disp, _gloffset_ReleaseShaderCompiler, fn)
#define CALL_RenderbufferStorage(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLenum, GLenum, GLsizei, GLsizei)), _gloffset_RenderbufferStorage, parameters)
#define GET_RenderbufferStorage(disp) GET_by_offset(disp, _gloffset_RenderbufferStorage)
#define SET_RenderbufferStorage(disp, fn) SET_by_offset(disp, _gloffset_RenderbufferStorage, fn)
#define CALL_ShaderBinary(disp, parameters) CALL_by_offset(disp, (void (GLAPIENTRYP)(GLsizei, const GLuint *, GLenum, const GLvoid *, GLsizei)), _gloffset_ShaderBinary, parameters)
#define GET_ShaderBinary(disp) GET_by_offset(disp, _gloffset_ShaderBinary)
#define SET_ShaderBinary(disp, fn) SET_by_offset(disp, _gloffset_ShaderBinary, fn)

/* define aliases for compatibility */
#define CALL_TexImage3D(disp, parameters) CALL_TexImage3DOES(disp, parameters)
#define GET_TexImage3D(disp) GET_TexImage3DOES(disp)
#define SET_TexImage3D(disp, fn) SET_TexImage3DOES(disp, fn)
#define CALL_TexSubImage3D(disp, parameters) CALL_TexSubImage3DOES(disp, parameters)
#define GET_TexSubImage3D(disp) GET_TexSubImage3DOES(disp)
#define SET_TexSubImage3D(disp, fn) SET_TexSubImage3DOES(disp, fn)
#define CALL_CopyTexSubImage3D(disp, parameters) CALL_CopyTexSubImage3DOES(disp, parameters)
#define GET_CopyTexSubImage3D(disp) GET_CopyTexSubImage3DOES(disp)
#define SET_CopyTexSubImage3D(disp, fn) SET_CopyTexSubImage3DOES(disp, fn)
#define CALL_ActiveTextureARB(disp, parameters) CALL_ActiveTexture(disp, parameters)
#define GET_ActiveTextureARB(disp) GET_ActiveTexture(disp)
#define SET_ActiveTextureARB(disp, fn) SET_ActiveTexture(disp, fn)

#if defined(_GLAPI_USE_REMAP_TABLE)
#define TexImage3D_remap_index TexImage3DOES_remap_index
#define TexSubImage3D_remap_index TexSubImage3DOES_remap_index
#define CopyTexSubImage3D_remap_index CopyTexSubImage3DOES_remap_index
#define ActiveTextureARB_remap_index ActiveTexture_remap_index
#endif /* defined(_GLAPI_USE_REMAP_TABLE) */


#endif /* !defined( _GLAPI_DISPATCH_H_ ) */
