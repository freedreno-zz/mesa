/* DO NOT EDIT - This file generated automatically by gl_x86-64_asm.py (from Mesa) script */

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

/* If we build with gcc's -fvisibility=hidden flag, we'll need to change
 * the symbol visibility mode to 'default'.
 */

#include "x86/assyntax.h"

#ifdef __GNUC__
#  pragma GCC visibility push(default)
#  define HIDDEN(x) .hidden x
#else
#  define HIDDEN(x)
#endif

# if defined(USE_MGL_NAMESPACE)
#  define GL_PREFIX(n) GLNAME(CONCAT(mgl,n))
#  define _glapi_Dispatch _mglapi_Dispatch
# else
#  define GL_PREFIX(n) GLNAME(CONCAT(gl,n))
# endif

#if defined(PTHREADS) || defined(WIN32) || defined(BEOS_THREADS)
#  define THREADS
#endif

	.text

#ifdef GLX_USE_TLS

	.globl _x86_64_get_get_dispatch; HIDDEN(_x86_64_get_get_dispatch)
_x86_64_get_get_dispatch:
	lea	_x86_64_get_dispatch(%rip), %rax
	ret

	.p2align	4,,15
_x86_64_get_dispatch:
	movq	_glapi_tls_Dispatch@GOTTPOFF(%rip), %rax
	movq	%fs:(%rax), %rax
	ret
	.size	_x86_64_get_dispatch, .-_x86_64_get_dispatch

#elif defined(PTHREADS)

	.extern	_glapi_Dispatch
	.extern	_gl_DispatchTSD
	.extern	pthread_getspecific

	.p2align	4,,15
_x86_64_get_dispatch:
	movq	_gl_DispatchTSD(%rip), %rdi
	jmp	pthread_getspecific@PLT

#elif defined(THREADS)

	.extern	_glapi_get_dispatch

#endif

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_0)
	.type	GL_PREFIX(_dispatch_stub_0), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_0))
GL_PREFIX(_dispatch_stub_0):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	0(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	0(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	0(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_0), .-GL_PREFIX(_dispatch_stub_0)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_1)
	.type	GL_PREFIX(_dispatch_stub_1), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_1))
GL_PREFIX(_dispatch_stub_1):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	8(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	8(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	8(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_1), .-GL_PREFIX(_dispatch_stub_1)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_2)
	.type	GL_PREFIX(_dispatch_stub_2), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_2))
GL_PREFIX(_dispatch_stub_2):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	16(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	16(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	16(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_2), .-GL_PREFIX(_dispatch_stub_2)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_3)
	.type	GL_PREFIX(_dispatch_stub_3), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_3))
GL_PREFIX(_dispatch_stub_3):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	24(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	24(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	24(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_3), .-GL_PREFIX(_dispatch_stub_3)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_4)
	.type	GL_PREFIX(_dispatch_stub_4), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_4))
GL_PREFIX(_dispatch_stub_4):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	32(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	32(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	32(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	32(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_4), .-GL_PREFIX(_dispatch_stub_4)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_5)
	.type	GL_PREFIX(_dispatch_stub_5), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_5))
GL_PREFIX(_dispatch_stub_5):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	40(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	40(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	40(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	40(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_5), .-GL_PREFIX(_dispatch_stub_5)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_6)
	.type	GL_PREFIX(_dispatch_stub_6), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_6))
GL_PREFIX(_dispatch_stub_6):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	48(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	48(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	48(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	48(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_6), .-GL_PREFIX(_dispatch_stub_6)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_7)
	.type	GL_PREFIX(_dispatch_stub_7), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_7))
GL_PREFIX(_dispatch_stub_7):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	56(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	56(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	56(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	56(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_7), .-GL_PREFIX(_dispatch_stub_7)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_8)
	.type	GL_PREFIX(_dispatch_stub_8), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_8))
GL_PREFIX(_dispatch_stub_8):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	64(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$56, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	movq	%xmm1, 24(%rsp)
	movq	%xmm2, 32(%rsp)
	movq	%xmm3, 40(%rsp)
	movq	%rdx, 48(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	48(%rsp), %rdx
	movq	40(%rsp), %xmm3
	movq	32(%rsp), %xmm2
	movq	24(%rsp), %xmm1
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$56, %rsp
	movq	64(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	64(%rax), %r11
	jmp	*%r11
1:
	subq	$56, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	movq	%xmm1, 24(%rsp)
	movq	%xmm2, 32(%rsp)
	movq	%xmm3, 40(%rsp)
	movq	%rdx, 48(%rsp)
	call	_glapi_get_dispatch
	movq	48(%rsp), %rdx
	movq	40(%rsp), %xmm3
	movq	32(%rsp), %xmm2
	movq	24(%rsp), %xmm1
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$56, %rsp
	movq	64(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_8), .-GL_PREFIX(_dispatch_stub_8)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_9)
	.type	GL_PREFIX(_dispatch_stub_9), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_9))
GL_PREFIX(_dispatch_stub_9):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	72(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	72(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	72(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	72(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_9), .-GL_PREFIX(_dispatch_stub_9)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_10)
	.type	GL_PREFIX(_dispatch_stub_10), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_10))
GL_PREFIX(_dispatch_stub_10):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	80(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	80(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	80(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	80(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_10), .-GL_PREFIX(_dispatch_stub_10)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_11)
	.type	GL_PREFIX(_dispatch_stub_11), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_11))
GL_PREFIX(_dispatch_stub_11):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	88(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	88(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	88(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	88(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_11), .-GL_PREFIX(_dispatch_stub_11)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_12)
	.type	GL_PREFIX(_dispatch_stub_12), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_12))
GL_PREFIX(_dispatch_stub_12):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	96(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	96(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	96(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	96(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_12), .-GL_PREFIX(_dispatch_stub_12)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_13)
	.type	GL_PREFIX(_dispatch_stub_13), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_13))
GL_PREFIX(_dispatch_stub_13):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	104(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	104(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	104(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	104(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_13), .-GL_PREFIX(_dispatch_stub_13)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_14)
	.type	GL_PREFIX(_dispatch_stub_14), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_14))
GL_PREFIX(_dispatch_stub_14):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	112(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	112(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	112(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	112(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_14), .-GL_PREFIX(_dispatch_stub_14)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_15)
	.type	GL_PREFIX(_dispatch_stub_15), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_15))
GL_PREFIX(_dispatch_stub_15):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	120(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	120(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	120(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	120(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_15), .-GL_PREFIX(_dispatch_stub_15)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_16)
	.type	GL_PREFIX(_dispatch_stub_16), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_16))
GL_PREFIX(_dispatch_stub_16):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	128(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	128(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	128(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	128(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_16), .-GL_PREFIX(_dispatch_stub_16)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_17)
	.type	GL_PREFIX(_dispatch_stub_17), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_17))
GL_PREFIX(_dispatch_stub_17):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	136(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	136(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	136(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	136(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_17), .-GL_PREFIX(_dispatch_stub_17)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_18)
	.type	GL_PREFIX(_dispatch_stub_18), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_18))
GL_PREFIX(_dispatch_stub_18):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	144(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	144(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	144(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	144(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_18), .-GL_PREFIX(_dispatch_stub_18)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_19)
	.type	GL_PREFIX(_dispatch_stub_19), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_19))
GL_PREFIX(_dispatch_stub_19):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	152(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	152(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	152(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	152(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_19), .-GL_PREFIX(_dispatch_stub_19)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_20)
	.type	GL_PREFIX(_dispatch_stub_20), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_20))
GL_PREFIX(_dispatch_stub_20):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	160(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	160(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	160(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	160(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_20), .-GL_PREFIX(_dispatch_stub_20)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_21)
	.type	GL_PREFIX(_dispatch_stub_21), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_21))
GL_PREFIX(_dispatch_stub_21):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	168(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	168(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	168(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	168(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_21), .-GL_PREFIX(_dispatch_stub_21)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_22)
	.type	GL_PREFIX(_dispatch_stub_22), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_22))
GL_PREFIX(_dispatch_stub_22):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	176(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	176(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	176(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	176(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_22), .-GL_PREFIX(_dispatch_stub_22)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_23)
	.type	GL_PREFIX(_dispatch_stub_23), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_23))
GL_PREFIX(_dispatch_stub_23):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	184(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	184(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	184(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	184(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_23), .-GL_PREFIX(_dispatch_stub_23)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_24)
	.type	GL_PREFIX(_dispatch_stub_24), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_24))
GL_PREFIX(_dispatch_stub_24):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	192(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	192(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	192(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	192(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_24), .-GL_PREFIX(_dispatch_stub_24)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_25)
	.type	GL_PREFIX(_dispatch_stub_25), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_25))
GL_PREFIX(_dispatch_stub_25):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	200(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	200(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	200(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	200(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_25), .-GL_PREFIX(_dispatch_stub_25)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_26)
	.type	GL_PREFIX(_dispatch_stub_26), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_26))
GL_PREFIX(_dispatch_stub_26):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	208(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	208(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	208(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	208(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_26), .-GL_PREFIX(_dispatch_stub_26)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_27)
	.type	GL_PREFIX(_dispatch_stub_27), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_27))
GL_PREFIX(_dispatch_stub_27):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	216(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	216(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	216(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	216(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_27), .-GL_PREFIX(_dispatch_stub_27)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_28)
	.type	GL_PREFIX(_dispatch_stub_28), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_28))
GL_PREFIX(_dispatch_stub_28):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	224(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	224(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	224(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	224(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_28), .-GL_PREFIX(_dispatch_stub_28)

	.p2align	4,,15
	.globl	GL_PREFIX(Color4f)
	.type	GL_PREFIX(Color4f), @function
GL_PREFIX(Color4f):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	232(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	232(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	232(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	232(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Color4f), .-GL_PREFIX(Color4f)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_30)
	.type	GL_PREFIX(_dispatch_stub_30), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_30))
GL_PREFIX(_dispatch_stub_30):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	240(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	240(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	240(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	240(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_30), .-GL_PREFIX(_dispatch_stub_30)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_31)
	.type	GL_PREFIX(_dispatch_stub_31), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_31))
GL_PREFIX(_dispatch_stub_31):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	248(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	248(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	248(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	248(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_31), .-GL_PREFIX(_dispatch_stub_31)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_32)
	.type	GL_PREFIX(_dispatch_stub_32), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_32))
GL_PREFIX(_dispatch_stub_32):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	256(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	256(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	256(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	256(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_32), .-GL_PREFIX(_dispatch_stub_32)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_33)
	.type	GL_PREFIX(_dispatch_stub_33), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_33))
GL_PREFIX(_dispatch_stub_33):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	264(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	264(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	264(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	264(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_33), .-GL_PREFIX(_dispatch_stub_33)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_34)
	.type	GL_PREFIX(_dispatch_stub_34), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_34))
GL_PREFIX(_dispatch_stub_34):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	272(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	272(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	272(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	272(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_34), .-GL_PREFIX(_dispatch_stub_34)

	.p2align	4,,15
	.globl	GL_PREFIX(Color4ub)
	.type	GL_PREFIX(Color4ub), @function
GL_PREFIX(Color4ub):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	280(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	280(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	280(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	280(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Color4ub), .-GL_PREFIX(Color4ub)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_36)
	.type	GL_PREFIX(_dispatch_stub_36), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_36))
GL_PREFIX(_dispatch_stub_36):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	288(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	288(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	288(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	288(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_36), .-GL_PREFIX(_dispatch_stub_36)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_37)
	.type	GL_PREFIX(_dispatch_stub_37), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_37))
GL_PREFIX(_dispatch_stub_37):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	296(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	296(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	296(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	296(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_37), .-GL_PREFIX(_dispatch_stub_37)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_38)
	.type	GL_PREFIX(_dispatch_stub_38), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_38))
GL_PREFIX(_dispatch_stub_38):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	304(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	304(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	304(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	304(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_38), .-GL_PREFIX(_dispatch_stub_38)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_39)
	.type	GL_PREFIX(_dispatch_stub_39), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_39))
GL_PREFIX(_dispatch_stub_39):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	312(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	312(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	312(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	312(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_39), .-GL_PREFIX(_dispatch_stub_39)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_40)
	.type	GL_PREFIX(_dispatch_stub_40), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_40))
GL_PREFIX(_dispatch_stub_40):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	320(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	320(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	320(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	320(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_40), .-GL_PREFIX(_dispatch_stub_40)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_41)
	.type	GL_PREFIX(_dispatch_stub_41), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_41))
GL_PREFIX(_dispatch_stub_41):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	328(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	328(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	328(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	328(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_41), .-GL_PREFIX(_dispatch_stub_41)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_42)
	.type	GL_PREFIX(_dispatch_stub_42), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_42))
GL_PREFIX(_dispatch_stub_42):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	336(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	336(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	336(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	336(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_42), .-GL_PREFIX(_dispatch_stub_42)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_43)
	.type	GL_PREFIX(_dispatch_stub_43), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_43))
GL_PREFIX(_dispatch_stub_43):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	344(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	344(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	344(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	344(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_43), .-GL_PREFIX(_dispatch_stub_43)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_44)
	.type	GL_PREFIX(_dispatch_stub_44), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_44))
GL_PREFIX(_dispatch_stub_44):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	352(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	352(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	352(%rax), %r11
	jmp	*%r11
1:
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_glapi_get_dispatch
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	352(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_44), .-GL_PREFIX(_dispatch_stub_44)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_45)
	.type	GL_PREFIX(_dispatch_stub_45), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_45))
GL_PREFIX(_dispatch_stub_45):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	360(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	360(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	360(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	360(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_45), .-GL_PREFIX(_dispatch_stub_45)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_46)
	.type	GL_PREFIX(_dispatch_stub_46), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_46))
GL_PREFIX(_dispatch_stub_46):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	368(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	368(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	368(%rax), %r11
	jmp	*%r11
1:
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_glapi_get_dispatch
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	368(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_46), .-GL_PREFIX(_dispatch_stub_46)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_47)
	.type	GL_PREFIX(_dispatch_stub_47), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_47))
GL_PREFIX(_dispatch_stub_47):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	376(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	376(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	376(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	376(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_47), .-GL_PREFIX(_dispatch_stub_47)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_48)
	.type	GL_PREFIX(_dispatch_stub_48), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_48))
GL_PREFIX(_dispatch_stub_48):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	384(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	384(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	384(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	384(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_48), .-GL_PREFIX(_dispatch_stub_48)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_49)
	.type	GL_PREFIX(_dispatch_stub_49), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_49))
GL_PREFIX(_dispatch_stub_49):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	392(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	392(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	392(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	392(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_49), .-GL_PREFIX(_dispatch_stub_49)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_50)
	.type	GL_PREFIX(_dispatch_stub_50), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_50))
GL_PREFIX(_dispatch_stub_50):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	400(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	400(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	400(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	400(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_50), .-GL_PREFIX(_dispatch_stub_50)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_51)
	.type	GL_PREFIX(_dispatch_stub_51), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_51))
GL_PREFIX(_dispatch_stub_51):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	408(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	408(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	408(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	408(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_51), .-GL_PREFIX(_dispatch_stub_51)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_52)
	.type	GL_PREFIX(_dispatch_stub_52), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_52))
GL_PREFIX(_dispatch_stub_52):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	416(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	416(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	416(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	416(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_52), .-GL_PREFIX(_dispatch_stub_52)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_53)
	.type	GL_PREFIX(_dispatch_stub_53), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_53))
GL_PREFIX(_dispatch_stub_53):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	424(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	424(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	424(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	424(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_53), .-GL_PREFIX(_dispatch_stub_53)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_54)
	.type	GL_PREFIX(_dispatch_stub_54), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_54))
GL_PREFIX(_dispatch_stub_54):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	432(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	432(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	432(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	432(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_54), .-GL_PREFIX(_dispatch_stub_54)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_55)
	.type	GL_PREFIX(_dispatch_stub_55), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_55))
GL_PREFIX(_dispatch_stub_55):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	440(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	440(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	440(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	440(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_55), .-GL_PREFIX(_dispatch_stub_55)

	.p2align	4,,15
	.globl	GL_PREFIX(Normal3f)
	.type	GL_PREFIX(Normal3f), @function
GL_PREFIX(Normal3f):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	448(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	448(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	448(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	448(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Normal3f), .-GL_PREFIX(Normal3f)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_57)
	.type	GL_PREFIX(_dispatch_stub_57), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_57))
GL_PREFIX(_dispatch_stub_57):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	456(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	456(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	456(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	456(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_57), .-GL_PREFIX(_dispatch_stub_57)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_58)
	.type	GL_PREFIX(_dispatch_stub_58), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_58))
GL_PREFIX(_dispatch_stub_58):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	464(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	464(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	464(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	464(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_58), .-GL_PREFIX(_dispatch_stub_58)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_59)
	.type	GL_PREFIX(_dispatch_stub_59), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_59))
GL_PREFIX(_dispatch_stub_59):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	472(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	472(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	472(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	472(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_59), .-GL_PREFIX(_dispatch_stub_59)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_60)
	.type	GL_PREFIX(_dispatch_stub_60), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_60))
GL_PREFIX(_dispatch_stub_60):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	480(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	480(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	480(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	480(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_60), .-GL_PREFIX(_dispatch_stub_60)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_61)
	.type	GL_PREFIX(_dispatch_stub_61), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_61))
GL_PREFIX(_dispatch_stub_61):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	488(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	488(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	488(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	488(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_61), .-GL_PREFIX(_dispatch_stub_61)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_62)
	.type	GL_PREFIX(_dispatch_stub_62), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_62))
GL_PREFIX(_dispatch_stub_62):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	496(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	496(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	496(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	496(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_62), .-GL_PREFIX(_dispatch_stub_62)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_63)
	.type	GL_PREFIX(_dispatch_stub_63), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_63))
GL_PREFIX(_dispatch_stub_63):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	504(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	504(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	504(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	504(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_63), .-GL_PREFIX(_dispatch_stub_63)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_64)
	.type	GL_PREFIX(_dispatch_stub_64), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_64))
GL_PREFIX(_dispatch_stub_64):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	512(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	512(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	512(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	512(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_64), .-GL_PREFIX(_dispatch_stub_64)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_65)
	.type	GL_PREFIX(_dispatch_stub_65), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_65))
GL_PREFIX(_dispatch_stub_65):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	520(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	520(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	520(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	520(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_65), .-GL_PREFIX(_dispatch_stub_65)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_66)
	.type	GL_PREFIX(_dispatch_stub_66), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_66))
GL_PREFIX(_dispatch_stub_66):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	528(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	528(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	528(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	528(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_66), .-GL_PREFIX(_dispatch_stub_66)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_67)
	.type	GL_PREFIX(_dispatch_stub_67), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_67))
GL_PREFIX(_dispatch_stub_67):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	536(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	536(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	536(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	536(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_67), .-GL_PREFIX(_dispatch_stub_67)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_68)
	.type	GL_PREFIX(_dispatch_stub_68), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_68))
GL_PREFIX(_dispatch_stub_68):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	544(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	544(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	544(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	544(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_68), .-GL_PREFIX(_dispatch_stub_68)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_69)
	.type	GL_PREFIX(_dispatch_stub_69), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_69))
GL_PREFIX(_dispatch_stub_69):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	552(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	552(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	552(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	552(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_69), .-GL_PREFIX(_dispatch_stub_69)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_70)
	.type	GL_PREFIX(_dispatch_stub_70), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_70))
GL_PREFIX(_dispatch_stub_70):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	560(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	560(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	560(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	560(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_70), .-GL_PREFIX(_dispatch_stub_70)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_71)
	.type	GL_PREFIX(_dispatch_stub_71), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_71))
GL_PREFIX(_dispatch_stub_71):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	568(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	568(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	568(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	568(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_71), .-GL_PREFIX(_dispatch_stub_71)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_72)
	.type	GL_PREFIX(_dispatch_stub_72), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_72))
GL_PREFIX(_dispatch_stub_72):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	576(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	576(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	576(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	576(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_72), .-GL_PREFIX(_dispatch_stub_72)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_73)
	.type	GL_PREFIX(_dispatch_stub_73), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_73))
GL_PREFIX(_dispatch_stub_73):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	584(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	584(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	584(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	584(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_73), .-GL_PREFIX(_dispatch_stub_73)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_74)
	.type	GL_PREFIX(_dispatch_stub_74), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_74))
GL_PREFIX(_dispatch_stub_74):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	592(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	592(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	592(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	592(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_74), .-GL_PREFIX(_dispatch_stub_74)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_75)
	.type	GL_PREFIX(_dispatch_stub_75), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_75))
GL_PREFIX(_dispatch_stub_75):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	600(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	600(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	600(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	600(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_75), .-GL_PREFIX(_dispatch_stub_75)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_76)
	.type	GL_PREFIX(_dispatch_stub_76), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_76))
GL_PREFIX(_dispatch_stub_76):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	608(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	608(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	608(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	608(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_76), .-GL_PREFIX(_dispatch_stub_76)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_77)
	.type	GL_PREFIX(_dispatch_stub_77), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_77))
GL_PREFIX(_dispatch_stub_77):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	616(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	616(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	616(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	616(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_77), .-GL_PREFIX(_dispatch_stub_77)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_78)
	.type	GL_PREFIX(_dispatch_stub_78), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_78))
GL_PREFIX(_dispatch_stub_78):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	624(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	624(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	624(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	624(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_78), .-GL_PREFIX(_dispatch_stub_78)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_79)
	.type	GL_PREFIX(_dispatch_stub_79), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_79))
GL_PREFIX(_dispatch_stub_79):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	632(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	632(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	632(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	632(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_79), .-GL_PREFIX(_dispatch_stub_79)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_80)
	.type	GL_PREFIX(_dispatch_stub_80), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_80))
GL_PREFIX(_dispatch_stub_80):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	640(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	640(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	640(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	640(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_80), .-GL_PREFIX(_dispatch_stub_80)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_81)
	.type	GL_PREFIX(_dispatch_stub_81), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_81))
GL_PREFIX(_dispatch_stub_81):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	648(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	648(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	648(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	648(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_81), .-GL_PREFIX(_dispatch_stub_81)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_82)
	.type	GL_PREFIX(_dispatch_stub_82), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_82))
GL_PREFIX(_dispatch_stub_82):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	656(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	656(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	656(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	656(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_82), .-GL_PREFIX(_dispatch_stub_82)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_83)
	.type	GL_PREFIX(_dispatch_stub_83), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_83))
GL_PREFIX(_dispatch_stub_83):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	664(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	664(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	664(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	664(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_83), .-GL_PREFIX(_dispatch_stub_83)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_84)
	.type	GL_PREFIX(_dispatch_stub_84), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_84))
GL_PREFIX(_dispatch_stub_84):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	672(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	672(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	672(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	672(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_84), .-GL_PREFIX(_dispatch_stub_84)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_85)
	.type	GL_PREFIX(_dispatch_stub_85), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_85))
GL_PREFIX(_dispatch_stub_85):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	680(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	680(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	680(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	680(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_85), .-GL_PREFIX(_dispatch_stub_85)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_86)
	.type	GL_PREFIX(_dispatch_stub_86), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_86))
GL_PREFIX(_dispatch_stub_86):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	688(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	688(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	688(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	688(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_86), .-GL_PREFIX(_dispatch_stub_86)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_87)
	.type	GL_PREFIX(_dispatch_stub_87), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_87))
GL_PREFIX(_dispatch_stub_87):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	696(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	696(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	696(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	696(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_87), .-GL_PREFIX(_dispatch_stub_87)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_88)
	.type	GL_PREFIX(_dispatch_stub_88), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_88))
GL_PREFIX(_dispatch_stub_88):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	704(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	704(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	704(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	704(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_88), .-GL_PREFIX(_dispatch_stub_88)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_89)
	.type	GL_PREFIX(_dispatch_stub_89), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_89))
GL_PREFIX(_dispatch_stub_89):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	712(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	712(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	712(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	712(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_89), .-GL_PREFIX(_dispatch_stub_89)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_90)
	.type	GL_PREFIX(_dispatch_stub_90), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_90))
GL_PREFIX(_dispatch_stub_90):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	720(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	720(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	720(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	720(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_90), .-GL_PREFIX(_dispatch_stub_90)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_91)
	.type	GL_PREFIX(_dispatch_stub_91), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_91))
GL_PREFIX(_dispatch_stub_91):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	728(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	728(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	728(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	728(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_91), .-GL_PREFIX(_dispatch_stub_91)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_92)
	.type	GL_PREFIX(_dispatch_stub_92), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_92))
GL_PREFIX(_dispatch_stub_92):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	736(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	736(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	736(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	736(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_92), .-GL_PREFIX(_dispatch_stub_92)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_93)
	.type	GL_PREFIX(_dispatch_stub_93), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_93))
GL_PREFIX(_dispatch_stub_93):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	744(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	744(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	744(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	744(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_93), .-GL_PREFIX(_dispatch_stub_93)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_94)
	.type	GL_PREFIX(_dispatch_stub_94), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_94))
GL_PREFIX(_dispatch_stub_94):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	752(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	752(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	752(%rax), %r11
	jmp	*%r11
1:
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_glapi_get_dispatch
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	752(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_94), .-GL_PREFIX(_dispatch_stub_94)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_95)
	.type	GL_PREFIX(_dispatch_stub_95), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_95))
GL_PREFIX(_dispatch_stub_95):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	760(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	760(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	760(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	760(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_95), .-GL_PREFIX(_dispatch_stub_95)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_96)
	.type	GL_PREFIX(_dispatch_stub_96), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_96))
GL_PREFIX(_dispatch_stub_96):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	768(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	768(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	768(%rax), %r11
	jmp	*%r11
1:
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_glapi_get_dispatch
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	768(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_96), .-GL_PREFIX(_dispatch_stub_96)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_97)
	.type	GL_PREFIX(_dispatch_stub_97), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_97))
GL_PREFIX(_dispatch_stub_97):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	776(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	776(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	776(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	776(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_97), .-GL_PREFIX(_dispatch_stub_97)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_98)
	.type	GL_PREFIX(_dispatch_stub_98), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_98))
GL_PREFIX(_dispatch_stub_98):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	784(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	784(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	784(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	784(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_98), .-GL_PREFIX(_dispatch_stub_98)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_99)
	.type	GL_PREFIX(_dispatch_stub_99), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_99))
GL_PREFIX(_dispatch_stub_99):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	792(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	792(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	792(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	792(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_99), .-GL_PREFIX(_dispatch_stub_99)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_100)
	.type	GL_PREFIX(_dispatch_stub_100), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_100))
GL_PREFIX(_dispatch_stub_100):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	800(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	800(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	800(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	800(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_100), .-GL_PREFIX(_dispatch_stub_100)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_101)
	.type	GL_PREFIX(_dispatch_stub_101), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_101))
GL_PREFIX(_dispatch_stub_101):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	808(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	808(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	808(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	808(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_101), .-GL_PREFIX(_dispatch_stub_101)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_102)
	.type	GL_PREFIX(_dispatch_stub_102), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_102))
GL_PREFIX(_dispatch_stub_102):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	816(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	816(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	816(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	816(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_102), .-GL_PREFIX(_dispatch_stub_102)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_103)
	.type	GL_PREFIX(_dispatch_stub_103), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_103))
GL_PREFIX(_dispatch_stub_103):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	824(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	824(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	824(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	824(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_103), .-GL_PREFIX(_dispatch_stub_103)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_104)
	.type	GL_PREFIX(_dispatch_stub_104), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_104))
GL_PREFIX(_dispatch_stub_104):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	832(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	832(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	832(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	832(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_104), .-GL_PREFIX(_dispatch_stub_104)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_105)
	.type	GL_PREFIX(_dispatch_stub_105), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_105))
GL_PREFIX(_dispatch_stub_105):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	840(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	840(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	840(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	840(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_105), .-GL_PREFIX(_dispatch_stub_105)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_106)
	.type	GL_PREFIX(_dispatch_stub_106), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_106))
GL_PREFIX(_dispatch_stub_106):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	848(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	848(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	848(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	848(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_106), .-GL_PREFIX(_dispatch_stub_106)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_107)
	.type	GL_PREFIX(_dispatch_stub_107), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_107))
GL_PREFIX(_dispatch_stub_107):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	856(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	856(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	856(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	856(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_107), .-GL_PREFIX(_dispatch_stub_107)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_108)
	.type	GL_PREFIX(_dispatch_stub_108), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_108))
GL_PREFIX(_dispatch_stub_108):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	864(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	864(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	864(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	864(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_108), .-GL_PREFIX(_dispatch_stub_108)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_109)
	.type	GL_PREFIX(_dispatch_stub_109), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_109))
GL_PREFIX(_dispatch_stub_109):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	872(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	872(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	872(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	872(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_109), .-GL_PREFIX(_dispatch_stub_109)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_110)
	.type	GL_PREFIX(_dispatch_stub_110), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_110))
GL_PREFIX(_dispatch_stub_110):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	880(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	880(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	880(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	880(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_110), .-GL_PREFIX(_dispatch_stub_110)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_111)
	.type	GL_PREFIX(_dispatch_stub_111), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_111))
GL_PREFIX(_dispatch_stub_111):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	888(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	888(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	888(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	888(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_111), .-GL_PREFIX(_dispatch_stub_111)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_112)
	.type	GL_PREFIX(_dispatch_stub_112), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_112))
GL_PREFIX(_dispatch_stub_112):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	896(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	896(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	896(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	896(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_112), .-GL_PREFIX(_dispatch_stub_112)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_113)
	.type	GL_PREFIX(_dispatch_stub_113), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_113))
GL_PREFIX(_dispatch_stub_113):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	904(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	904(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	904(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	904(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_113), .-GL_PREFIX(_dispatch_stub_113)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_114)
	.type	GL_PREFIX(_dispatch_stub_114), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_114))
GL_PREFIX(_dispatch_stub_114):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	912(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	912(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	912(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	912(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_114), .-GL_PREFIX(_dispatch_stub_114)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_115)
	.type	GL_PREFIX(_dispatch_stub_115), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_115))
GL_PREFIX(_dispatch_stub_115):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	920(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	920(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	920(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	920(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_115), .-GL_PREFIX(_dispatch_stub_115)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_116)
	.type	GL_PREFIX(_dispatch_stub_116), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_116))
GL_PREFIX(_dispatch_stub_116):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	928(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	928(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	928(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	928(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_116), .-GL_PREFIX(_dispatch_stub_116)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_117)
	.type	GL_PREFIX(_dispatch_stub_117), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_117))
GL_PREFIX(_dispatch_stub_117):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	936(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	936(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	936(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	936(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_117), .-GL_PREFIX(_dispatch_stub_117)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_118)
	.type	GL_PREFIX(_dispatch_stub_118), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_118))
GL_PREFIX(_dispatch_stub_118):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	944(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	944(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	944(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	944(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_118), .-GL_PREFIX(_dispatch_stub_118)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_119)
	.type	GL_PREFIX(_dispatch_stub_119), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_119))
GL_PREFIX(_dispatch_stub_119):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	952(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	952(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	952(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	952(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_119), .-GL_PREFIX(_dispatch_stub_119)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_120)
	.type	GL_PREFIX(_dispatch_stub_120), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_120))
GL_PREFIX(_dispatch_stub_120):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	960(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	960(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	960(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	960(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_120), .-GL_PREFIX(_dispatch_stub_120)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_121)
	.type	GL_PREFIX(_dispatch_stub_121), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_121))
GL_PREFIX(_dispatch_stub_121):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	968(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	968(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	968(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	968(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_121), .-GL_PREFIX(_dispatch_stub_121)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_122)
	.type	GL_PREFIX(_dispatch_stub_122), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_122))
GL_PREFIX(_dispatch_stub_122):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	976(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	976(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	976(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	976(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_122), .-GL_PREFIX(_dispatch_stub_122)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_123)
	.type	GL_PREFIX(_dispatch_stub_123), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_123))
GL_PREFIX(_dispatch_stub_123):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	984(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	984(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	984(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	984(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_123), .-GL_PREFIX(_dispatch_stub_123)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_124)
	.type	GL_PREFIX(_dispatch_stub_124), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_124))
GL_PREFIX(_dispatch_stub_124):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	992(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	992(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	992(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	992(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_124), .-GL_PREFIX(_dispatch_stub_124)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_125)
	.type	GL_PREFIX(_dispatch_stub_125), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_125))
GL_PREFIX(_dispatch_stub_125):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1000(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1000(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1000(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1000(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_125), .-GL_PREFIX(_dispatch_stub_125)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_126)
	.type	GL_PREFIX(_dispatch_stub_126), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_126))
GL_PREFIX(_dispatch_stub_126):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1008(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1008(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1008(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1008(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_126), .-GL_PREFIX(_dispatch_stub_126)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_127)
	.type	GL_PREFIX(_dispatch_stub_127), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_127))
GL_PREFIX(_dispatch_stub_127):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1016(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1016(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1016(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1016(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_127), .-GL_PREFIX(_dispatch_stub_127)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_128)
	.type	GL_PREFIX(_dispatch_stub_128), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_128))
GL_PREFIX(_dispatch_stub_128):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1024(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1024(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1024(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1024(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_128), .-GL_PREFIX(_dispatch_stub_128)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_129)
	.type	GL_PREFIX(_dispatch_stub_129), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_129))
GL_PREFIX(_dispatch_stub_129):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1032(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1032(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1032(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1032(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_129), .-GL_PREFIX(_dispatch_stub_129)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_130)
	.type	GL_PREFIX(_dispatch_stub_130), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_130))
GL_PREFIX(_dispatch_stub_130):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1040(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1040(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1040(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1040(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_130), .-GL_PREFIX(_dispatch_stub_130)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_131)
	.type	GL_PREFIX(_dispatch_stub_131), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_131))
GL_PREFIX(_dispatch_stub_131):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1048(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1048(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1048(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1048(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_131), .-GL_PREFIX(_dispatch_stub_131)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_132)
	.type	GL_PREFIX(_dispatch_stub_132), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_132))
GL_PREFIX(_dispatch_stub_132):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1056(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1056(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1056(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1056(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_132), .-GL_PREFIX(_dispatch_stub_132)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_133)
	.type	GL_PREFIX(_dispatch_stub_133), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_133))
GL_PREFIX(_dispatch_stub_133):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1064(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1064(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1064(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1064(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_133), .-GL_PREFIX(_dispatch_stub_133)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_134)
	.type	GL_PREFIX(_dispatch_stub_134), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_134))
GL_PREFIX(_dispatch_stub_134):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1072(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1072(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1072(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1072(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_134), .-GL_PREFIX(_dispatch_stub_134)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_135)
	.type	GL_PREFIX(_dispatch_stub_135), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_135))
GL_PREFIX(_dispatch_stub_135):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1080(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1080(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1080(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1080(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_135), .-GL_PREFIX(_dispatch_stub_135)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_136)
	.type	GL_PREFIX(_dispatch_stub_136), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_136))
GL_PREFIX(_dispatch_stub_136):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1088(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1088(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1088(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1088(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_136), .-GL_PREFIX(_dispatch_stub_136)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_137)
	.type	GL_PREFIX(_dispatch_stub_137), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_137))
GL_PREFIX(_dispatch_stub_137):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1096(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1096(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1096(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1096(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_137), .-GL_PREFIX(_dispatch_stub_137)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_138)
	.type	GL_PREFIX(_dispatch_stub_138), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_138))
GL_PREFIX(_dispatch_stub_138):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1104(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1104(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1104(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1104(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_138), .-GL_PREFIX(_dispatch_stub_138)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_139)
	.type	GL_PREFIX(_dispatch_stub_139), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_139))
GL_PREFIX(_dispatch_stub_139):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1112(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1112(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1112(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1112(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_139), .-GL_PREFIX(_dispatch_stub_139)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_140)
	.type	GL_PREFIX(_dispatch_stub_140), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_140))
GL_PREFIX(_dispatch_stub_140):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1120(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1120(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1120(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1120(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_140), .-GL_PREFIX(_dispatch_stub_140)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_141)
	.type	GL_PREFIX(_dispatch_stub_141), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_141))
GL_PREFIX(_dispatch_stub_141):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1128(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1128(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1128(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1128(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_141), .-GL_PREFIX(_dispatch_stub_141)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_142)
	.type	GL_PREFIX(_dispatch_stub_142), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_142))
GL_PREFIX(_dispatch_stub_142):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1136(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	1136(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1136(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	1136(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_142), .-GL_PREFIX(_dispatch_stub_142)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_143)
	.type	GL_PREFIX(_dispatch_stub_143), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_143))
GL_PREFIX(_dispatch_stub_143):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1144(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1144(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1144(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1144(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_143), .-GL_PREFIX(_dispatch_stub_143)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_144)
	.type	GL_PREFIX(_dispatch_stub_144), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_144))
GL_PREFIX(_dispatch_stub_144):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1152(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	1152(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1152(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	1152(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_144), .-GL_PREFIX(_dispatch_stub_144)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_145)
	.type	GL_PREFIX(_dispatch_stub_145), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_145))
GL_PREFIX(_dispatch_stub_145):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1160(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1160(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1160(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1160(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_145), .-GL_PREFIX(_dispatch_stub_145)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_146)
	.type	GL_PREFIX(_dispatch_stub_146), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_146))
GL_PREFIX(_dispatch_stub_146):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1168(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1168(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1168(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1168(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_146), .-GL_PREFIX(_dispatch_stub_146)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_147)
	.type	GL_PREFIX(_dispatch_stub_147), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_147))
GL_PREFIX(_dispatch_stub_147):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1176(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1176(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1176(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1176(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_147), .-GL_PREFIX(_dispatch_stub_147)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_148)
	.type	GL_PREFIX(_dispatch_stub_148), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_148))
GL_PREFIX(_dispatch_stub_148):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1184(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1184(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1184(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1184(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_148), .-GL_PREFIX(_dispatch_stub_148)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_149)
	.type	GL_PREFIX(_dispatch_stub_149), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_149))
GL_PREFIX(_dispatch_stub_149):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1192(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1192(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1192(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1192(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_149), .-GL_PREFIX(_dispatch_stub_149)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_150)
	.type	GL_PREFIX(_dispatch_stub_150), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_150))
GL_PREFIX(_dispatch_stub_150):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1200(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1200(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1200(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1200(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_150), .-GL_PREFIX(_dispatch_stub_150)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_151)
	.type	GL_PREFIX(_dispatch_stub_151), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_151))
GL_PREFIX(_dispatch_stub_151):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1208(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1208(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1208(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1208(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_151), .-GL_PREFIX(_dispatch_stub_151)

	.p2align	4,,15
	.globl	GL_PREFIX(CullFace)
	.type	GL_PREFIX(CullFace), @function
GL_PREFIX(CullFace):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1216(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1216(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1216(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1216(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(CullFace), .-GL_PREFIX(CullFace)

	.p2align	4,,15
	.globl	GL_PREFIX(Fogf)
	.type	GL_PREFIX(Fogf), @function
GL_PREFIX(Fogf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1224(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1224(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1224(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1224(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Fogf), .-GL_PREFIX(Fogf)

	.p2align	4,,15
	.globl	GL_PREFIX(Fogfv)
	.type	GL_PREFIX(Fogfv), @function
GL_PREFIX(Fogfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1232(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1232(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1232(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1232(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Fogfv), .-GL_PREFIX(Fogfv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_155)
	.type	GL_PREFIX(_dispatch_stub_155), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_155))
GL_PREFIX(_dispatch_stub_155):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1240(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1240(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1240(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1240(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_155), .-GL_PREFIX(_dispatch_stub_155)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_156)
	.type	GL_PREFIX(_dispatch_stub_156), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_156))
GL_PREFIX(_dispatch_stub_156):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1248(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1248(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1248(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1248(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_156), .-GL_PREFIX(_dispatch_stub_156)

	.p2align	4,,15
	.globl	GL_PREFIX(FrontFace)
	.type	GL_PREFIX(FrontFace), @function
GL_PREFIX(FrontFace):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1256(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1256(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1256(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1256(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(FrontFace), .-GL_PREFIX(FrontFace)

	.p2align	4,,15
	.globl	GL_PREFIX(Hint)
	.type	GL_PREFIX(Hint), @function
GL_PREFIX(Hint):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1264(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1264(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1264(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1264(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Hint), .-GL_PREFIX(Hint)

	.p2align	4,,15
	.globl	GL_PREFIX(Lightf)
	.type	GL_PREFIX(Lightf), @function
GL_PREFIX(Lightf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1272(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1272(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1272(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1272(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Lightf), .-GL_PREFIX(Lightf)

	.p2align	4,,15
	.globl	GL_PREFIX(Lightfv)
	.type	GL_PREFIX(Lightfv), @function
GL_PREFIX(Lightfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1280(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1280(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1280(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1280(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Lightfv), .-GL_PREFIX(Lightfv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_161)
	.type	GL_PREFIX(_dispatch_stub_161), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_161))
GL_PREFIX(_dispatch_stub_161):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1288(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1288(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1288(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1288(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_161), .-GL_PREFIX(_dispatch_stub_161)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_162)
	.type	GL_PREFIX(_dispatch_stub_162), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_162))
GL_PREFIX(_dispatch_stub_162):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1296(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1296(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1296(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1296(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_162), .-GL_PREFIX(_dispatch_stub_162)

	.p2align	4,,15
	.globl	GL_PREFIX(LightModelf)
	.type	GL_PREFIX(LightModelf), @function
GL_PREFIX(LightModelf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1304(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1304(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1304(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1304(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(LightModelf), .-GL_PREFIX(LightModelf)

	.p2align	4,,15
	.globl	GL_PREFIX(LightModelfv)
	.type	GL_PREFIX(LightModelfv), @function
GL_PREFIX(LightModelfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1312(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1312(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1312(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1312(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(LightModelfv), .-GL_PREFIX(LightModelfv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_165)
	.type	GL_PREFIX(_dispatch_stub_165), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_165))
GL_PREFIX(_dispatch_stub_165):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1320(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1320(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1320(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1320(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_165), .-GL_PREFIX(_dispatch_stub_165)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_166)
	.type	GL_PREFIX(_dispatch_stub_166), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_166))
GL_PREFIX(_dispatch_stub_166):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1328(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1328(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1328(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1328(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_166), .-GL_PREFIX(_dispatch_stub_166)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_167)
	.type	GL_PREFIX(_dispatch_stub_167), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_167))
GL_PREFIX(_dispatch_stub_167):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1336(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1336(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1336(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1336(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_167), .-GL_PREFIX(_dispatch_stub_167)

	.p2align	4,,15
	.globl	GL_PREFIX(LineWidth)
	.type	GL_PREFIX(LineWidth), @function
GL_PREFIX(LineWidth):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1344(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1344(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1344(%rax), %r11
	jmp	*%r11
1:
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_glapi_get_dispatch
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1344(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(LineWidth), .-GL_PREFIX(LineWidth)

	.p2align	4,,15
	.globl	GL_PREFIX(Materialf)
	.type	GL_PREFIX(Materialf), @function
GL_PREFIX(Materialf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1352(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1352(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1352(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1352(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Materialf), .-GL_PREFIX(Materialf)

	.p2align	4,,15
	.globl	GL_PREFIX(Materialfv)
	.type	GL_PREFIX(Materialfv), @function
GL_PREFIX(Materialfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1360(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1360(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1360(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1360(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Materialfv), .-GL_PREFIX(Materialfv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_171)
	.type	GL_PREFIX(_dispatch_stub_171), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_171))
GL_PREFIX(_dispatch_stub_171):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1368(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1368(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1368(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1368(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_171), .-GL_PREFIX(_dispatch_stub_171)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_172)
	.type	GL_PREFIX(_dispatch_stub_172), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_172))
GL_PREFIX(_dispatch_stub_172):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1376(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1376(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1376(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1376(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_172), .-GL_PREFIX(_dispatch_stub_172)

	.p2align	4,,15
	.globl	GL_PREFIX(PointSize)
	.type	GL_PREFIX(PointSize), @function
GL_PREFIX(PointSize):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1384(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1384(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1384(%rax), %r11
	jmp	*%r11
1:
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_glapi_get_dispatch
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1384(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PointSize), .-GL_PREFIX(PointSize)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_174)
	.type	GL_PREFIX(_dispatch_stub_174), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_174))
GL_PREFIX(_dispatch_stub_174):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1392(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1392(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1392(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1392(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_174), .-GL_PREFIX(_dispatch_stub_174)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_175)
	.type	GL_PREFIX(_dispatch_stub_175), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_175))
GL_PREFIX(_dispatch_stub_175):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1400(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1400(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1400(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1400(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_175), .-GL_PREFIX(_dispatch_stub_175)

	.p2align	4,,15
	.globl	GL_PREFIX(Scissor)
	.type	GL_PREFIX(Scissor), @function
GL_PREFIX(Scissor):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1408(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1408(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1408(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1408(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Scissor), .-GL_PREFIX(Scissor)

	.p2align	4,,15
	.globl	GL_PREFIX(ShadeModel)
	.type	GL_PREFIX(ShadeModel), @function
GL_PREFIX(ShadeModel):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1416(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1416(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1416(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1416(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ShadeModel), .-GL_PREFIX(ShadeModel)

	.p2align	4,,15
	.globl	GL_PREFIX(TexParameterf)
	.type	GL_PREFIX(TexParameterf), @function
GL_PREFIX(TexParameterf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1424(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1424(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1424(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1424(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexParameterf), .-GL_PREFIX(TexParameterf)

	.p2align	4,,15
	.globl	GL_PREFIX(TexParameterfv)
	.type	GL_PREFIX(TexParameterfv), @function
GL_PREFIX(TexParameterfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1432(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1432(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1432(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1432(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexParameterfv), .-GL_PREFIX(TexParameterfv)

	.p2align	4,,15
	.globl	GL_PREFIX(TexParameteri)
	.type	GL_PREFIX(TexParameteri), @function
GL_PREFIX(TexParameteri):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1440(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1440(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1440(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1440(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexParameteri), .-GL_PREFIX(TexParameteri)

	.p2align	4,,15
	.globl	GL_PREFIX(TexParameteriv)
	.type	GL_PREFIX(TexParameteriv), @function
GL_PREFIX(TexParameteriv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1448(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1448(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1448(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1448(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexParameteriv), .-GL_PREFIX(TexParameteriv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_182)
	.type	GL_PREFIX(_dispatch_stub_182), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_182))
GL_PREFIX(_dispatch_stub_182):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1456(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1456(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1456(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1456(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_182), .-GL_PREFIX(_dispatch_stub_182)

	.p2align	4,,15
	.globl	GL_PREFIX(TexImage2D)
	.type	GL_PREFIX(TexImage2D), @function
GL_PREFIX(TexImage2D):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1464(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1464(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1464(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1464(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexImage2D), .-GL_PREFIX(TexImage2D)

	.p2align	4,,15
	.globl	GL_PREFIX(TexEnvf)
	.type	GL_PREFIX(TexEnvf), @function
GL_PREFIX(TexEnvf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1472(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1472(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1472(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1472(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexEnvf), .-GL_PREFIX(TexEnvf)

	.p2align	4,,15
	.globl	GL_PREFIX(TexEnvfv)
	.type	GL_PREFIX(TexEnvfv), @function
GL_PREFIX(TexEnvfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1480(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1480(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1480(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1480(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexEnvfv), .-GL_PREFIX(TexEnvfv)

	.p2align	4,,15
	.globl	GL_PREFIX(TexEnvi)
	.type	GL_PREFIX(TexEnvi), @function
GL_PREFIX(TexEnvi):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1488(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1488(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1488(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1488(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexEnvi), .-GL_PREFIX(TexEnvi)

	.p2align	4,,15
	.globl	GL_PREFIX(TexEnviv)
	.type	GL_PREFIX(TexEnviv), @function
GL_PREFIX(TexEnviv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1496(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1496(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1496(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1496(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexEnviv), .-GL_PREFIX(TexEnviv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_188)
	.type	GL_PREFIX(_dispatch_stub_188), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_188))
GL_PREFIX(_dispatch_stub_188):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1504(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1504(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1504(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1504(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_188), .-GL_PREFIX(_dispatch_stub_188)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_189)
	.type	GL_PREFIX(_dispatch_stub_189), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_189))
GL_PREFIX(_dispatch_stub_189):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1512(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1512(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1512(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1512(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_189), .-GL_PREFIX(_dispatch_stub_189)

	.p2align	4,,15
	.globl	GL_PREFIX(TexGenfOES)
	.type	GL_PREFIX(TexGenfOES), @function
GL_PREFIX(TexGenfOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1520(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1520(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1520(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1520(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexGenfOES), .-GL_PREFIX(TexGenfOES)

	.p2align	4,,15
	.globl	GL_PREFIX(TexGenfvOES)
	.type	GL_PREFIX(TexGenfvOES), @function
GL_PREFIX(TexGenfvOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1528(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1528(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1528(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1528(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexGenfvOES), .-GL_PREFIX(TexGenfvOES)

	.p2align	4,,15
	.globl	GL_PREFIX(TexGeniOES)
	.type	GL_PREFIX(TexGeniOES), @function
GL_PREFIX(TexGeniOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1536(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1536(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1536(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1536(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexGeniOES), .-GL_PREFIX(TexGeniOES)

	.p2align	4,,15
	.globl	GL_PREFIX(TexGenivOES)
	.type	GL_PREFIX(TexGenivOES), @function
GL_PREFIX(TexGenivOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1544(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1544(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1544(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1544(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexGenivOES), .-GL_PREFIX(TexGenivOES)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_194)
	.type	GL_PREFIX(_dispatch_stub_194), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_194))
GL_PREFIX(_dispatch_stub_194):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1552(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1552(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1552(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1552(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_194), .-GL_PREFIX(_dispatch_stub_194)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_195)
	.type	GL_PREFIX(_dispatch_stub_195), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_195))
GL_PREFIX(_dispatch_stub_195):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1560(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1560(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1560(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1560(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_195), .-GL_PREFIX(_dispatch_stub_195)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_196)
	.type	GL_PREFIX(_dispatch_stub_196), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_196))
GL_PREFIX(_dispatch_stub_196):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1568(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1568(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1568(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1568(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_196), .-GL_PREFIX(_dispatch_stub_196)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_197)
	.type	GL_PREFIX(_dispatch_stub_197), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_197))
GL_PREFIX(_dispatch_stub_197):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1576(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	1576(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1576(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	1576(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_197), .-GL_PREFIX(_dispatch_stub_197)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_198)
	.type	GL_PREFIX(_dispatch_stub_198), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_198))
GL_PREFIX(_dispatch_stub_198):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1584(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1584(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1584(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1584(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_198), .-GL_PREFIX(_dispatch_stub_198)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_199)
	.type	GL_PREFIX(_dispatch_stub_199), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_199))
GL_PREFIX(_dispatch_stub_199):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1592(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1592(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1592(%rax), %r11
	jmp	*%r11
1:
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_glapi_get_dispatch
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1592(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_199), .-GL_PREFIX(_dispatch_stub_199)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_200)
	.type	GL_PREFIX(_dispatch_stub_200), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_200))
GL_PREFIX(_dispatch_stub_200):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1600(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	1600(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1600(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	1600(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_200), .-GL_PREFIX(_dispatch_stub_200)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_201)
	.type	GL_PREFIX(_dispatch_stub_201), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_201))
GL_PREFIX(_dispatch_stub_201):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1608(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1608(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1608(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1608(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_201), .-GL_PREFIX(_dispatch_stub_201)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_202)
	.type	GL_PREFIX(_dispatch_stub_202), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_202))
GL_PREFIX(_dispatch_stub_202):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1616(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1616(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1616(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1616(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_202), .-GL_PREFIX(_dispatch_stub_202)

	.p2align	4,,15
	.globl	GL_PREFIX(Clear)
	.type	GL_PREFIX(Clear), @function
GL_PREFIX(Clear):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1624(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1624(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1624(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1624(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Clear), .-GL_PREFIX(Clear)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_204)
	.type	GL_PREFIX(_dispatch_stub_204), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_204))
GL_PREFIX(_dispatch_stub_204):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1632(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	1632(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1632(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	1632(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_204), .-GL_PREFIX(_dispatch_stub_204)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_205)
	.type	GL_PREFIX(_dispatch_stub_205), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_205))
GL_PREFIX(_dispatch_stub_205):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1640(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1640(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1640(%rax), %r11
	jmp	*%r11
1:
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_glapi_get_dispatch
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1640(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_205), .-GL_PREFIX(_dispatch_stub_205)

	.p2align	4,,15
	.globl	GL_PREFIX(ClearColor)
	.type	GL_PREFIX(ClearColor), @function
GL_PREFIX(ClearColor):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1648(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1648(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1648(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1648(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ClearColor), .-GL_PREFIX(ClearColor)

	.p2align	4,,15
	.globl	GL_PREFIX(ClearStencil)
	.type	GL_PREFIX(ClearStencil), @function
GL_PREFIX(ClearStencil):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1656(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1656(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1656(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1656(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ClearStencil), .-GL_PREFIX(ClearStencil)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_208)
	.type	GL_PREFIX(_dispatch_stub_208), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_208))
GL_PREFIX(_dispatch_stub_208):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1664(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1664(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1664(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1664(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_208), .-GL_PREFIX(_dispatch_stub_208)

	.p2align	4,,15
	.globl	GL_PREFIX(StencilMask)
	.type	GL_PREFIX(StencilMask), @function
GL_PREFIX(StencilMask):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1672(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1672(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1672(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1672(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(StencilMask), .-GL_PREFIX(StencilMask)

	.p2align	4,,15
	.globl	GL_PREFIX(ColorMask)
	.type	GL_PREFIX(ColorMask), @function
GL_PREFIX(ColorMask):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1680(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1680(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1680(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1680(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ColorMask), .-GL_PREFIX(ColorMask)

	.p2align	4,,15
	.globl	GL_PREFIX(DepthMask)
	.type	GL_PREFIX(DepthMask), @function
GL_PREFIX(DepthMask):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1688(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1688(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1688(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1688(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DepthMask), .-GL_PREFIX(DepthMask)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_212)
	.type	GL_PREFIX(_dispatch_stub_212), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_212))
GL_PREFIX(_dispatch_stub_212):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1696(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1696(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1696(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1696(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_212), .-GL_PREFIX(_dispatch_stub_212)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_213)
	.type	GL_PREFIX(_dispatch_stub_213), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_213))
GL_PREFIX(_dispatch_stub_213):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1704(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1704(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1704(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1704(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_213), .-GL_PREFIX(_dispatch_stub_213)

	.p2align	4,,15
	.globl	GL_PREFIX(Disable)
	.type	GL_PREFIX(Disable), @function
GL_PREFIX(Disable):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1712(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1712(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1712(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1712(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Disable), .-GL_PREFIX(Disable)

	.p2align	4,,15
	.globl	GL_PREFIX(Enable)
	.type	GL_PREFIX(Enable), @function
GL_PREFIX(Enable):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1720(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1720(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1720(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1720(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Enable), .-GL_PREFIX(Enable)

	.p2align	4,,15
	.globl	GL_PREFIX(Finish)
	.type	GL_PREFIX(Finish), @function
GL_PREFIX(Finish):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1728(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	1728(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1728(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	1728(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Finish), .-GL_PREFIX(Finish)

	.p2align	4,,15
	.globl	GL_PREFIX(Flush)
	.type	GL_PREFIX(Flush), @function
GL_PREFIX(Flush):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1736(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	1736(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1736(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	1736(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Flush), .-GL_PREFIX(Flush)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_218)
	.type	GL_PREFIX(_dispatch_stub_218), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_218))
GL_PREFIX(_dispatch_stub_218):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1744(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	1744(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1744(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	1744(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_218), .-GL_PREFIX(_dispatch_stub_218)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_219)
	.type	GL_PREFIX(_dispatch_stub_219), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_219))
GL_PREFIX(_dispatch_stub_219):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1752(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1752(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1752(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1752(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_219), .-GL_PREFIX(_dispatch_stub_219)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_220)
	.type	GL_PREFIX(_dispatch_stub_220), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_220))
GL_PREFIX(_dispatch_stub_220):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1760(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$56, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%rdx, 32(%rsp)
	movq	%rcx, 40(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	40(%rsp), %rcx
	movq	32(%rsp), %rdx
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$56, %rsp
	movq	1760(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1760(%rax), %r11
	jmp	*%r11
1:
	subq	$56, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%rdx, 32(%rsp)
	movq	%rcx, 40(%rsp)
	call	_glapi_get_dispatch
	movq	40(%rsp), %rcx
	movq	32(%rsp), %rdx
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$56, %rsp
	movq	1760(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_220), .-GL_PREFIX(_dispatch_stub_220)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_221)
	.type	GL_PREFIX(_dispatch_stub_221), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_221))
GL_PREFIX(_dispatch_stub_221):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1768(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$56, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%rdx, 32(%rsp)
	movq	%rcx, 40(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	40(%rsp), %rcx
	movq	32(%rsp), %rdx
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$56, %rsp
	movq	1768(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1768(%rax), %r11
	jmp	*%r11
1:
	subq	$56, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%rdx, 32(%rsp)
	movq	%rcx, 40(%rsp)
	call	_glapi_get_dispatch
	movq	40(%rsp), %rcx
	movq	32(%rsp), %rdx
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$56, %rsp
	movq	1768(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_221), .-GL_PREFIX(_dispatch_stub_221)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_222)
	.type	GL_PREFIX(_dispatch_stub_222), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_222))
GL_PREFIX(_dispatch_stub_222):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1776(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$88, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%rdx, 32(%rsp)
	movq	%xmm2, 40(%rsp)
	movq	%xmm3, 48(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%r8, 64(%rsp)
	movq	%r9, 72(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	72(%rsp), %r9
	movq	64(%rsp), %r8
	movq	56(%rsp), %rcx
	movq	48(%rsp), %xmm3
	movq	40(%rsp), %xmm2
	movq	32(%rsp), %rdx
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$88, %rsp
	movq	1776(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1776(%rax), %r11
	jmp	*%r11
1:
	subq	$88, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%rdx, 32(%rsp)
	movq	%xmm2, 40(%rsp)
	movq	%xmm3, 48(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%r8, 64(%rsp)
	movq	%r9, 72(%rsp)
	call	_glapi_get_dispatch
	movq	72(%rsp), %r9
	movq	64(%rsp), %r8
	movq	56(%rsp), %rcx
	movq	48(%rsp), %xmm3
	movq	40(%rsp), %xmm2
	movq	32(%rsp), %rdx
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$88, %rsp
	movq	1776(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_222), .-GL_PREFIX(_dispatch_stub_222)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_223)
	.type	GL_PREFIX(_dispatch_stub_223), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_223))
GL_PREFIX(_dispatch_stub_223):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1784(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$88, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%rdx, 32(%rsp)
	movq	%xmm2, 40(%rsp)
	movq	%xmm3, 48(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%r8, 64(%rsp)
	movq	%r9, 72(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	72(%rsp), %r9
	movq	64(%rsp), %r8
	movq	56(%rsp), %rcx
	movq	48(%rsp), %xmm3
	movq	40(%rsp), %xmm2
	movq	32(%rsp), %rdx
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$88, %rsp
	movq	1784(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1784(%rax), %r11
	jmp	*%r11
1:
	subq	$88, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%rdx, 32(%rsp)
	movq	%xmm2, 40(%rsp)
	movq	%xmm3, 48(%rsp)
	movq	%rcx, 56(%rsp)
	movq	%r8, 64(%rsp)
	movq	%r9, 72(%rsp)
	call	_glapi_get_dispatch
	movq	72(%rsp), %r9
	movq	64(%rsp), %r8
	movq	56(%rsp), %rcx
	movq	48(%rsp), %xmm3
	movq	40(%rsp), %xmm2
	movq	32(%rsp), %rdx
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$88, %rsp
	movq	1784(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_223), .-GL_PREFIX(_dispatch_stub_223)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_224)
	.type	GL_PREFIX(_dispatch_stub_224), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_224))
GL_PREFIX(_dispatch_stub_224):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1792(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1792(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1792(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1792(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_224), .-GL_PREFIX(_dispatch_stub_224)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_225)
	.type	GL_PREFIX(_dispatch_stub_225), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_225))
GL_PREFIX(_dispatch_stub_225):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1800(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1800(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1800(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1800(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_225), .-GL_PREFIX(_dispatch_stub_225)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_226)
	.type	GL_PREFIX(_dispatch_stub_226), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_226))
GL_PREFIX(_dispatch_stub_226):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1808(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$56, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%xmm2, 32(%rsp)
	movq	%xmm3, 40(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	40(%rsp), %xmm3
	movq	32(%rsp), %xmm2
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$56, %rsp
	movq	1808(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1808(%rax), %r11
	jmp	*%r11
1:
	subq	$56, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%xmm2, 32(%rsp)
	movq	%xmm3, 40(%rsp)
	call	_glapi_get_dispatch
	movq	40(%rsp), %xmm3
	movq	32(%rsp), %xmm2
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$56, %rsp
	movq	1808(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_226), .-GL_PREFIX(_dispatch_stub_226)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_227)
	.type	GL_PREFIX(_dispatch_stub_227), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_227))
GL_PREFIX(_dispatch_stub_227):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1816(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$56, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%xmm2, 32(%rsp)
	movq	%xmm3, 40(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	40(%rsp), %xmm3
	movq	32(%rsp), %xmm2
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$56, %rsp
	movq	1816(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1816(%rax), %r11
	jmp	*%r11
1:
	subq	$56, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%rsi, 24(%rsp)
	movq	%xmm2, 32(%rsp)
	movq	%xmm3, 40(%rsp)
	call	_glapi_get_dispatch
	movq	40(%rsp), %xmm3
	movq	32(%rsp), %xmm2
	movq	24(%rsp), %rsi
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$56, %rsp
	movq	1816(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_227), .-GL_PREFIX(_dispatch_stub_227)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_228)
	.type	GL_PREFIX(_dispatch_stub_228), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_228))
GL_PREFIX(_dispatch_stub_228):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1824(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1824(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1824(%rax), %r11
	jmp	*%r11
1:
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_glapi_get_dispatch
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1824(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_228), .-GL_PREFIX(_dispatch_stub_228)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_229)
	.type	GL_PREFIX(_dispatch_stub_229), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_229))
GL_PREFIX(_dispatch_stub_229):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1832(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1832(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1832(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1832(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_229), .-GL_PREFIX(_dispatch_stub_229)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_230)
	.type	GL_PREFIX(_dispatch_stub_230), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_230))
GL_PREFIX(_dispatch_stub_230):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1840(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1840(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1840(%rax), %r11
	jmp	*%r11
1:
	subq	$8, %rsp
	movq	%xmm0, (%rsp)
	call	_glapi_get_dispatch
	movq	(%rsp), %xmm0
	addq	$8, %rsp
	movq	1840(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_230), .-GL_PREFIX(_dispatch_stub_230)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_231)
	.type	GL_PREFIX(_dispatch_stub_231), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_231))
GL_PREFIX(_dispatch_stub_231):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1848(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1848(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1848(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1848(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_231), .-GL_PREFIX(_dispatch_stub_231)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_232)
	.type	GL_PREFIX(_dispatch_stub_232), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_232))
GL_PREFIX(_dispatch_stub_232):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1856(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1856(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1856(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1856(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_232), .-GL_PREFIX(_dispatch_stub_232)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_233)
	.type	GL_PREFIX(_dispatch_stub_233), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_233))
GL_PREFIX(_dispatch_stub_233):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1864(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1864(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1864(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1864(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_233), .-GL_PREFIX(_dispatch_stub_233)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_234)
	.type	GL_PREFIX(_dispatch_stub_234), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_234))
GL_PREFIX(_dispatch_stub_234):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1872(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1872(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1872(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1872(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_234), .-GL_PREFIX(_dispatch_stub_234)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_235)
	.type	GL_PREFIX(_dispatch_stub_235), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_235))
GL_PREFIX(_dispatch_stub_235):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1880(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1880(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1880(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1880(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_235), .-GL_PREFIX(_dispatch_stub_235)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_236)
	.type	GL_PREFIX(_dispatch_stub_236), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_236))
GL_PREFIX(_dispatch_stub_236):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1888(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1888(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1888(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1888(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_236), .-GL_PREFIX(_dispatch_stub_236)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_237)
	.type	GL_PREFIX(_dispatch_stub_237), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_237))
GL_PREFIX(_dispatch_stub_237):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1896(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1896(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1896(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1896(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_237), .-GL_PREFIX(_dispatch_stub_237)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_238)
	.type	GL_PREFIX(_dispatch_stub_238), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_238))
GL_PREFIX(_dispatch_stub_238):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1904(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1904(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1904(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1904(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_238), .-GL_PREFIX(_dispatch_stub_238)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_239)
	.type	GL_PREFIX(_dispatch_stub_239), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_239))
GL_PREFIX(_dispatch_stub_239):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1912(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1912(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1912(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1912(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_239), .-GL_PREFIX(_dispatch_stub_239)

	.p2align	4,,15
	.globl	GL_PREFIX(AlphaFunc)
	.type	GL_PREFIX(AlphaFunc), @function
GL_PREFIX(AlphaFunc):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1920(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1920(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1920(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1920(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(AlphaFunc), .-GL_PREFIX(AlphaFunc)

	.p2align	4,,15
	.globl	GL_PREFIX(BlendFunc)
	.type	GL_PREFIX(BlendFunc), @function
GL_PREFIX(BlendFunc):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1928(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1928(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1928(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1928(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(BlendFunc), .-GL_PREFIX(BlendFunc)

	.p2align	4,,15
	.globl	GL_PREFIX(LogicOp)
	.type	GL_PREFIX(LogicOp), @function
GL_PREFIX(LogicOp):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1936(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1936(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1936(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1936(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(LogicOp), .-GL_PREFIX(LogicOp)

	.p2align	4,,15
	.globl	GL_PREFIX(StencilFunc)
	.type	GL_PREFIX(StencilFunc), @function
GL_PREFIX(StencilFunc):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1944(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1944(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1944(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1944(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(StencilFunc), .-GL_PREFIX(StencilFunc)

	.p2align	4,,15
	.globl	GL_PREFIX(StencilOp)
	.type	GL_PREFIX(StencilOp), @function
GL_PREFIX(StencilOp):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1952(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1952(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1952(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	1952(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(StencilOp), .-GL_PREFIX(StencilOp)

	.p2align	4,,15
	.globl	GL_PREFIX(DepthFunc)
	.type	GL_PREFIX(DepthFunc), @function
GL_PREFIX(DepthFunc):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1960(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	1960(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1960(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	1960(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DepthFunc), .-GL_PREFIX(DepthFunc)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_246)
	.type	GL_PREFIX(_dispatch_stub_246), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_246))
GL_PREFIX(_dispatch_stub_246):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1968(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1968(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1968(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	1968(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_246), .-GL_PREFIX(_dispatch_stub_246)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_247)
	.type	GL_PREFIX(_dispatch_stub_247), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_247))
GL_PREFIX(_dispatch_stub_247):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1976(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1976(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1976(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1976(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_247), .-GL_PREFIX(_dispatch_stub_247)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_248)
	.type	GL_PREFIX(_dispatch_stub_248), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_248))
GL_PREFIX(_dispatch_stub_248):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1984(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1984(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1984(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	1984(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_248), .-GL_PREFIX(_dispatch_stub_248)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_249)
	.type	GL_PREFIX(_dispatch_stub_249), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_249))
GL_PREFIX(_dispatch_stub_249):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	1992(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1992(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	1992(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	1992(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_249), .-GL_PREFIX(_dispatch_stub_249)

	.p2align	4,,15
	.globl	GL_PREFIX(PixelStorei)
	.type	GL_PREFIX(PixelStorei), @function
GL_PREFIX(PixelStorei):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2000(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2000(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2000(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2000(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PixelStorei), .-GL_PREFIX(PixelStorei)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_251)
	.type	GL_PREFIX(_dispatch_stub_251), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_251))
GL_PREFIX(_dispatch_stub_251):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2008(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2008(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2008(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2008(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_251), .-GL_PREFIX(_dispatch_stub_251)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_252)
	.type	GL_PREFIX(_dispatch_stub_252), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_252))
GL_PREFIX(_dispatch_stub_252):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2016(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2016(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2016(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2016(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_252), .-GL_PREFIX(_dispatch_stub_252)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_253)
	.type	GL_PREFIX(_dispatch_stub_253), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_253))
GL_PREFIX(_dispatch_stub_253):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2024(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2024(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2024(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2024(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_253), .-GL_PREFIX(_dispatch_stub_253)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_254)
	.type	GL_PREFIX(_dispatch_stub_254), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_254))
GL_PREFIX(_dispatch_stub_254):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2032(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2032(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2032(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2032(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_254), .-GL_PREFIX(_dispatch_stub_254)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_255)
	.type	GL_PREFIX(_dispatch_stub_255), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_255))
GL_PREFIX(_dispatch_stub_255):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2040(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2040(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2040(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2040(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_255), .-GL_PREFIX(_dispatch_stub_255)

	.p2align	4,,15
	.globl	GL_PREFIX(ReadPixels)
	.type	GL_PREFIX(ReadPixels), @function
GL_PREFIX(ReadPixels):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2048(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2048(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2048(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2048(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ReadPixels), .-GL_PREFIX(ReadPixels)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_257)
	.type	GL_PREFIX(_dispatch_stub_257), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_257))
GL_PREFIX(_dispatch_stub_257):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2056(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2056(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2056(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2056(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_257), .-GL_PREFIX(_dispatch_stub_257)

	.p2align	4,,15
	.globl	GL_PREFIX(GetBooleanv)
	.type	GL_PREFIX(GetBooleanv), @function
GL_PREFIX(GetBooleanv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2064(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2064(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2064(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2064(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetBooleanv), .-GL_PREFIX(GetBooleanv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_259)
	.type	GL_PREFIX(_dispatch_stub_259), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_259))
GL_PREFIX(_dispatch_stub_259):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2072(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2072(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2072(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2072(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_259), .-GL_PREFIX(_dispatch_stub_259)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_260)
	.type	GL_PREFIX(_dispatch_stub_260), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_260))
GL_PREFIX(_dispatch_stub_260):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2080(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2080(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2080(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2080(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_260), .-GL_PREFIX(_dispatch_stub_260)

	.p2align	4,,15
	.globl	GL_PREFIX(GetError)
	.type	GL_PREFIX(GetError), @function
GL_PREFIX(GetError):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2088(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	2088(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2088(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	2088(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetError), .-GL_PREFIX(GetError)

	.p2align	4,,15
	.globl	GL_PREFIX(GetFloatv)
	.type	GL_PREFIX(GetFloatv), @function
GL_PREFIX(GetFloatv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2096(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2096(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2096(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2096(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetFloatv), .-GL_PREFIX(GetFloatv)

	.p2align	4,,15
	.globl	GL_PREFIX(GetIntegerv)
	.type	GL_PREFIX(GetIntegerv), @function
GL_PREFIX(GetIntegerv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2104(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2104(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2104(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2104(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetIntegerv), .-GL_PREFIX(GetIntegerv)

	.p2align	4,,15
	.globl	GL_PREFIX(GetLightfv)
	.type	GL_PREFIX(GetLightfv), @function
GL_PREFIX(GetLightfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2112(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2112(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2112(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2112(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetLightfv), .-GL_PREFIX(GetLightfv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_265)
	.type	GL_PREFIX(_dispatch_stub_265), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_265))
GL_PREFIX(_dispatch_stub_265):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2120(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2120(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2120(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2120(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_265), .-GL_PREFIX(_dispatch_stub_265)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_266)
	.type	GL_PREFIX(_dispatch_stub_266), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_266))
GL_PREFIX(_dispatch_stub_266):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2128(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2128(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2128(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2128(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_266), .-GL_PREFIX(_dispatch_stub_266)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_267)
	.type	GL_PREFIX(_dispatch_stub_267), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_267))
GL_PREFIX(_dispatch_stub_267):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2136(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2136(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2136(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2136(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_267), .-GL_PREFIX(_dispatch_stub_267)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_268)
	.type	GL_PREFIX(_dispatch_stub_268), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_268))
GL_PREFIX(_dispatch_stub_268):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2144(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2144(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2144(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2144(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_268), .-GL_PREFIX(_dispatch_stub_268)

	.p2align	4,,15
	.globl	GL_PREFIX(GetMaterialfv)
	.type	GL_PREFIX(GetMaterialfv), @function
GL_PREFIX(GetMaterialfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2152(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2152(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2152(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2152(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetMaterialfv), .-GL_PREFIX(GetMaterialfv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_270)
	.type	GL_PREFIX(_dispatch_stub_270), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_270))
GL_PREFIX(_dispatch_stub_270):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2160(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2160(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2160(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2160(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_270), .-GL_PREFIX(_dispatch_stub_270)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_271)
	.type	GL_PREFIX(_dispatch_stub_271), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_271))
GL_PREFIX(_dispatch_stub_271):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2168(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2168(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2168(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2168(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_271), .-GL_PREFIX(_dispatch_stub_271)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_272)
	.type	GL_PREFIX(_dispatch_stub_272), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_272))
GL_PREFIX(_dispatch_stub_272):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2176(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2176(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2176(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2176(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_272), .-GL_PREFIX(_dispatch_stub_272)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_273)
	.type	GL_PREFIX(_dispatch_stub_273), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_273))
GL_PREFIX(_dispatch_stub_273):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2184(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2184(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2184(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2184(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_273), .-GL_PREFIX(_dispatch_stub_273)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_274)
	.type	GL_PREFIX(_dispatch_stub_274), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_274))
GL_PREFIX(_dispatch_stub_274):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2192(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2192(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2192(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2192(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_274), .-GL_PREFIX(_dispatch_stub_274)

	.p2align	4,,15
	.globl	GL_PREFIX(GetString)
	.type	GL_PREFIX(GetString), @function
GL_PREFIX(GetString):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2200(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2200(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2200(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2200(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetString), .-GL_PREFIX(GetString)

	.p2align	4,,15
	.globl	GL_PREFIX(GetTexEnvfv)
	.type	GL_PREFIX(GetTexEnvfv), @function
GL_PREFIX(GetTexEnvfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2208(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2208(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2208(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2208(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetTexEnvfv), .-GL_PREFIX(GetTexEnvfv)

	.p2align	4,,15
	.globl	GL_PREFIX(GetTexEnviv)
	.type	GL_PREFIX(GetTexEnviv), @function
GL_PREFIX(GetTexEnviv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2216(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2216(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2216(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2216(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetTexEnviv), .-GL_PREFIX(GetTexEnviv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_278)
	.type	GL_PREFIX(_dispatch_stub_278), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_278))
GL_PREFIX(_dispatch_stub_278):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2224(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2224(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2224(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2224(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_278), .-GL_PREFIX(_dispatch_stub_278)

	.p2align	4,,15
	.globl	GL_PREFIX(GetTexGenfvOES)
	.type	GL_PREFIX(GetTexGenfvOES), @function
GL_PREFIX(GetTexGenfvOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2232(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2232(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2232(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2232(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetTexGenfvOES), .-GL_PREFIX(GetTexGenfvOES)

	.p2align	4,,15
	.globl	GL_PREFIX(GetTexGenivOES)
	.type	GL_PREFIX(GetTexGenivOES), @function
GL_PREFIX(GetTexGenivOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2240(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2240(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2240(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2240(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetTexGenivOES), .-GL_PREFIX(GetTexGenivOES)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_281)
	.type	GL_PREFIX(_dispatch_stub_281), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_281))
GL_PREFIX(_dispatch_stub_281):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2248(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2248(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2248(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2248(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_281), .-GL_PREFIX(_dispatch_stub_281)

	.p2align	4,,15
	.globl	GL_PREFIX(GetTexParameterfv)
	.type	GL_PREFIX(GetTexParameterfv), @function
GL_PREFIX(GetTexParameterfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2256(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2256(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2256(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2256(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetTexParameterfv), .-GL_PREFIX(GetTexParameterfv)

	.p2align	4,,15
	.globl	GL_PREFIX(GetTexParameteriv)
	.type	GL_PREFIX(GetTexParameteriv), @function
GL_PREFIX(GetTexParameteriv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2264(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2264(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2264(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2264(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetTexParameteriv), .-GL_PREFIX(GetTexParameteriv)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_284)
	.type	GL_PREFIX(_dispatch_stub_284), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_284))
GL_PREFIX(_dispatch_stub_284):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2272(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2272(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2272(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2272(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_284), .-GL_PREFIX(_dispatch_stub_284)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_285)
	.type	GL_PREFIX(_dispatch_stub_285), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_285))
GL_PREFIX(_dispatch_stub_285):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2280(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2280(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2280(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2280(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_285), .-GL_PREFIX(_dispatch_stub_285)

	.p2align	4,,15
	.globl	GL_PREFIX(IsEnabled)
	.type	GL_PREFIX(IsEnabled), @function
GL_PREFIX(IsEnabled):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2288(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2288(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2288(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2288(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(IsEnabled), .-GL_PREFIX(IsEnabled)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_287)
	.type	GL_PREFIX(_dispatch_stub_287), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_287))
GL_PREFIX(_dispatch_stub_287):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2296(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2296(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2296(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2296(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_287), .-GL_PREFIX(_dispatch_stub_287)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_288)
	.type	GL_PREFIX(_dispatch_stub_288), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_288))
GL_PREFIX(_dispatch_stub_288):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2304(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2304(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2304(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2304(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_288), .-GL_PREFIX(_dispatch_stub_288)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_289)
	.type	GL_PREFIX(_dispatch_stub_289), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_289))
GL_PREFIX(_dispatch_stub_289):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2312(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$56, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%xmm4, 32(%rsp)
	movq	%xmm5, 40(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	40(%rsp), %xmm5
	movq	32(%rsp), %xmm4
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$56, %rsp
	movq	2312(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2312(%rax), %r11
	jmp	*%r11
1:
	subq	$56, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%xmm4, 32(%rsp)
	movq	%xmm5, 40(%rsp)
	call	_glapi_get_dispatch
	movq	40(%rsp), %xmm5
	movq	32(%rsp), %xmm4
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$56, %rsp
	movq	2312(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_289), .-GL_PREFIX(_dispatch_stub_289)

	.p2align	4,,15
	.globl	GL_PREFIX(LoadIdentity)
	.type	GL_PREFIX(LoadIdentity), @function
GL_PREFIX(LoadIdentity):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2320(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	2320(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2320(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	2320(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(LoadIdentity), .-GL_PREFIX(LoadIdentity)

	.p2align	4,,15
	.globl	GL_PREFIX(LoadMatrixf)
	.type	GL_PREFIX(LoadMatrixf), @function
GL_PREFIX(LoadMatrixf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2328(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2328(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2328(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2328(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(LoadMatrixf), .-GL_PREFIX(LoadMatrixf)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_292)
	.type	GL_PREFIX(_dispatch_stub_292), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_292))
GL_PREFIX(_dispatch_stub_292):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2336(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2336(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2336(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2336(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_292), .-GL_PREFIX(_dispatch_stub_292)

	.p2align	4,,15
	.globl	GL_PREFIX(MatrixMode)
	.type	GL_PREFIX(MatrixMode), @function
GL_PREFIX(MatrixMode):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2344(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2344(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2344(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2344(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(MatrixMode), .-GL_PREFIX(MatrixMode)

	.p2align	4,,15
	.globl	GL_PREFIX(MultMatrixf)
	.type	GL_PREFIX(MultMatrixf), @function
GL_PREFIX(MultMatrixf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2352(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2352(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2352(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2352(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(MultMatrixf), .-GL_PREFIX(MultMatrixf)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_295)
	.type	GL_PREFIX(_dispatch_stub_295), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_295))
GL_PREFIX(_dispatch_stub_295):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2360(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2360(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2360(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2360(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_295), .-GL_PREFIX(_dispatch_stub_295)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_296)
	.type	GL_PREFIX(_dispatch_stub_296), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_296))
GL_PREFIX(_dispatch_stub_296):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2368(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$56, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%xmm4, 32(%rsp)
	movq	%xmm5, 40(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	40(%rsp), %xmm5
	movq	32(%rsp), %xmm4
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$56, %rsp
	movq	2368(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2368(%rax), %r11
	jmp	*%r11
1:
	subq	$56, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%xmm4, 32(%rsp)
	movq	%xmm5, 40(%rsp)
	call	_glapi_get_dispatch
	movq	40(%rsp), %xmm5
	movq	32(%rsp), %xmm4
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$56, %rsp
	movq	2368(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_296), .-GL_PREFIX(_dispatch_stub_296)

	.p2align	4,,15
	.globl	GL_PREFIX(PopMatrix)
	.type	GL_PREFIX(PopMatrix), @function
GL_PREFIX(PopMatrix):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2376(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	2376(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2376(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	2376(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PopMatrix), .-GL_PREFIX(PopMatrix)

	.p2align	4,,15
	.globl	GL_PREFIX(PushMatrix)
	.type	GL_PREFIX(PushMatrix), @function
GL_PREFIX(PushMatrix):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2384(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	2384(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2384(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	2384(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PushMatrix), .-GL_PREFIX(PushMatrix)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_299)
	.type	GL_PREFIX(_dispatch_stub_299), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_299))
GL_PREFIX(_dispatch_stub_299):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2392(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	2392(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2392(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	2392(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_299), .-GL_PREFIX(_dispatch_stub_299)

	.p2align	4,,15
	.globl	GL_PREFIX(Rotatef)
	.type	GL_PREFIX(Rotatef), @function
GL_PREFIX(Rotatef):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2400(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	2400(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2400(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	2400(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Rotatef), .-GL_PREFIX(Rotatef)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_301)
	.type	GL_PREFIX(_dispatch_stub_301), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_301))
GL_PREFIX(_dispatch_stub_301):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2408(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	2408(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2408(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	2408(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_301), .-GL_PREFIX(_dispatch_stub_301)

	.p2align	4,,15
	.globl	GL_PREFIX(Scalef)
	.type	GL_PREFIX(Scalef), @function
GL_PREFIX(Scalef):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2416(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	2416(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2416(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	2416(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Scalef), .-GL_PREFIX(Scalef)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_303)
	.type	GL_PREFIX(_dispatch_stub_303), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_303))
GL_PREFIX(_dispatch_stub_303):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2424(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	2424(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2424(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	2424(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_303), .-GL_PREFIX(_dispatch_stub_303)

	.p2align	4,,15
	.globl	GL_PREFIX(Translatef)
	.type	GL_PREFIX(Translatef), @function
GL_PREFIX(Translatef):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2432(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	2432(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2432(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	2432(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Translatef), .-GL_PREFIX(Translatef)

	.p2align	4,,15
	.globl	GL_PREFIX(Viewport)
	.type	GL_PREFIX(Viewport), @function
GL_PREFIX(Viewport):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2440(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2440(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2440(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2440(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Viewport), .-GL_PREFIX(Viewport)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_306)
	.type	GL_PREFIX(_dispatch_stub_306), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_306))
GL_PREFIX(_dispatch_stub_306):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2448(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2448(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2448(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2448(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_306), .-GL_PREFIX(_dispatch_stub_306)

	.p2align	4,,15
	.globl	GL_PREFIX(BindTexture)
	.type	GL_PREFIX(BindTexture), @function
GL_PREFIX(BindTexture):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2456(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2456(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2456(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2456(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(BindTexture), .-GL_PREFIX(BindTexture)

	.p2align	4,,15
	.globl	GL_PREFIX(ColorPointer)
	.type	GL_PREFIX(ColorPointer), @function
GL_PREFIX(ColorPointer):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2464(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2464(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2464(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2464(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ColorPointer), .-GL_PREFIX(ColorPointer)

	.p2align	4,,15
	.globl	GL_PREFIX(DisableClientState)
	.type	GL_PREFIX(DisableClientState), @function
GL_PREFIX(DisableClientState):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2472(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2472(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2472(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2472(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DisableClientState), .-GL_PREFIX(DisableClientState)

	.p2align	4,,15
	.globl	GL_PREFIX(DrawArrays)
	.type	GL_PREFIX(DrawArrays), @function
GL_PREFIX(DrawArrays):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2480(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2480(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2480(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2480(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DrawArrays), .-GL_PREFIX(DrawArrays)

	.p2align	4,,15
	.globl	GL_PREFIX(DrawElements)
	.type	GL_PREFIX(DrawElements), @function
GL_PREFIX(DrawElements):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2488(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2488(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2488(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2488(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DrawElements), .-GL_PREFIX(DrawElements)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_312)
	.type	GL_PREFIX(_dispatch_stub_312), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_312))
GL_PREFIX(_dispatch_stub_312):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2496(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2496(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2496(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2496(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_312), .-GL_PREFIX(_dispatch_stub_312)

	.p2align	4,,15
	.globl	GL_PREFIX(EnableClientState)
	.type	GL_PREFIX(EnableClientState), @function
GL_PREFIX(EnableClientState):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2504(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2504(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2504(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2504(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(EnableClientState), .-GL_PREFIX(EnableClientState)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_314)
	.type	GL_PREFIX(_dispatch_stub_314), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_314))
GL_PREFIX(_dispatch_stub_314):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2512(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2512(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2512(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2512(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_314), .-GL_PREFIX(_dispatch_stub_314)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_315)
	.type	GL_PREFIX(_dispatch_stub_315), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_315))
GL_PREFIX(_dispatch_stub_315):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2520(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2520(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2520(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2520(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_315), .-GL_PREFIX(_dispatch_stub_315)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_316)
	.type	GL_PREFIX(_dispatch_stub_316), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_316))
GL_PREFIX(_dispatch_stub_316):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2528(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2528(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2528(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2528(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_316), .-GL_PREFIX(_dispatch_stub_316)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_317)
	.type	GL_PREFIX(_dispatch_stub_317), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_317))
GL_PREFIX(_dispatch_stub_317):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2536(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2536(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2536(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2536(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_317), .-GL_PREFIX(_dispatch_stub_317)

	.p2align	4,,15
	.globl	GL_PREFIX(NormalPointer)
	.type	GL_PREFIX(NormalPointer), @function
GL_PREFIX(NormalPointer):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2544(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2544(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2544(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2544(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(NormalPointer), .-GL_PREFIX(NormalPointer)

	.p2align	4,,15
	.globl	GL_PREFIX(PolygonOffset)
	.type	GL_PREFIX(PolygonOffset), @function
GL_PREFIX(PolygonOffset):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2552(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	2552(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2552(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$24, %rsp
	movq	2552(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PolygonOffset), .-GL_PREFIX(PolygonOffset)

	.p2align	4,,15
	.globl	GL_PREFIX(TexCoordPointer)
	.type	GL_PREFIX(TexCoordPointer), @function
GL_PREFIX(TexCoordPointer):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2560(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2560(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2560(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2560(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexCoordPointer), .-GL_PREFIX(TexCoordPointer)

	.p2align	4,,15
	.globl	GL_PREFIX(VertexPointer)
	.type	GL_PREFIX(VertexPointer), @function
GL_PREFIX(VertexPointer):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2568(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2568(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2568(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2568(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(VertexPointer), .-GL_PREFIX(VertexPointer)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_322)
	.type	GL_PREFIX(_dispatch_stub_322), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_322))
GL_PREFIX(_dispatch_stub_322):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2576(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2576(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2576(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2576(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_322), .-GL_PREFIX(_dispatch_stub_322)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_323)
	.type	GL_PREFIX(_dispatch_stub_323), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_323))
GL_PREFIX(_dispatch_stub_323):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2584(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2584(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2584(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2584(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_323), .-GL_PREFIX(_dispatch_stub_323)

	.p2align	4,,15
	.globl	GL_PREFIX(CopyTexImage2D)
	.type	GL_PREFIX(CopyTexImage2D), @function
GL_PREFIX(CopyTexImage2D):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2592(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2592(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2592(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2592(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(CopyTexImage2D), .-GL_PREFIX(CopyTexImage2D)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_325)
	.type	GL_PREFIX(_dispatch_stub_325), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_325))
GL_PREFIX(_dispatch_stub_325):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2600(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2600(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2600(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2600(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_325), .-GL_PREFIX(_dispatch_stub_325)

	.p2align	4,,15
	.globl	GL_PREFIX(CopyTexSubImage2D)
	.type	GL_PREFIX(CopyTexSubImage2D), @function
GL_PREFIX(CopyTexSubImage2D):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2608(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2608(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2608(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2608(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(CopyTexSubImage2D), .-GL_PREFIX(CopyTexSubImage2D)

	.p2align	4,,15
	.globl	GL_PREFIX(DeleteTextures)
	.type	GL_PREFIX(DeleteTextures), @function
GL_PREFIX(DeleteTextures):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2616(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2616(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2616(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2616(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DeleteTextures), .-GL_PREFIX(DeleteTextures)

	.p2align	4,,15
	.globl	GL_PREFIX(GenTextures)
	.type	GL_PREFIX(GenTextures), @function
GL_PREFIX(GenTextures):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2624(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2624(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2624(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2624(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GenTextures), .-GL_PREFIX(GenTextures)

	.p2align	4,,15
	.globl	GL_PREFIX(GetPointerv)
	.type	GL_PREFIX(GetPointerv), @function
GL_PREFIX(GetPointerv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2632(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2632(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2632(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	2632(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetPointerv), .-GL_PREFIX(GetPointerv)

	.p2align	4,,15
	.globl	GL_PREFIX(IsTexture)
	.type	GL_PREFIX(IsTexture), @function
GL_PREFIX(IsTexture):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2640(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2640(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2640(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2640(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(IsTexture), .-GL_PREFIX(IsTexture)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_331)
	.type	GL_PREFIX(_dispatch_stub_331), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_331))
GL_PREFIX(_dispatch_stub_331):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2648(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2648(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2648(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2648(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_331), .-GL_PREFIX(_dispatch_stub_331)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_332)
	.type	GL_PREFIX(_dispatch_stub_332), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_332))
GL_PREFIX(_dispatch_stub_332):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2656(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2656(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2656(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2656(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_332), .-GL_PREFIX(_dispatch_stub_332)

	.p2align	4,,15
	.globl	GL_PREFIX(TexSubImage2D)
	.type	GL_PREFIX(TexSubImage2D), @function
GL_PREFIX(TexSubImage2D):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2664(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2664(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2664(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2664(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexSubImage2D), .-GL_PREFIX(TexSubImage2D)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_334)
	.type	GL_PREFIX(_dispatch_stub_334), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_334))
GL_PREFIX(_dispatch_stub_334):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2672(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	movq	2672(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2672(%rax), %r11
	jmp	*%r11
1:
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	movq	2672(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_334), .-GL_PREFIX(_dispatch_stub_334)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_335)
	.type	GL_PREFIX(_dispatch_stub_335), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_335))
GL_PREFIX(_dispatch_stub_335):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2680(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2680(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2680(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2680(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_335), .-GL_PREFIX(_dispatch_stub_335)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_336)
	.type	GL_PREFIX(_dispatch_stub_336), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_336))
GL_PREFIX(_dispatch_stub_336):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2688(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2688(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2688(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2688(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_336), .-GL_PREFIX(_dispatch_stub_336)

	.p2align	4,,15
	.globl	GL_PREFIX(BlendEquationOES)
	.type	GL_PREFIX(BlendEquationOES), @function
GL_PREFIX(BlendEquationOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2696(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2696(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2696(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2696(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(BlendEquationOES), .-GL_PREFIX(BlendEquationOES)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_338)
	.type	GL_PREFIX(_dispatch_stub_338), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_338))
GL_PREFIX(_dispatch_stub_338):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2704(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2704(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2704(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2704(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_338), .-GL_PREFIX(_dispatch_stub_338)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_339)
	.type	GL_PREFIX(_dispatch_stub_339), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_339))
GL_PREFIX(_dispatch_stub_339):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2712(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2712(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2712(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2712(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_339), .-GL_PREFIX(_dispatch_stub_339)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_340)
	.type	GL_PREFIX(_dispatch_stub_340), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_340))
GL_PREFIX(_dispatch_stub_340):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2720(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2720(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2720(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2720(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_340), .-GL_PREFIX(_dispatch_stub_340)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_341)
	.type	GL_PREFIX(_dispatch_stub_341), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_341))
GL_PREFIX(_dispatch_stub_341):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2728(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2728(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2728(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2728(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_341), .-GL_PREFIX(_dispatch_stub_341)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_342)
	.type	GL_PREFIX(_dispatch_stub_342), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_342))
GL_PREFIX(_dispatch_stub_342):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2736(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2736(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2736(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2736(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_342), .-GL_PREFIX(_dispatch_stub_342)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_343)
	.type	GL_PREFIX(_dispatch_stub_343), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_343))
GL_PREFIX(_dispatch_stub_343):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2744(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2744(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2744(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2744(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_343), .-GL_PREFIX(_dispatch_stub_343)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_344)
	.type	GL_PREFIX(_dispatch_stub_344), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_344))
GL_PREFIX(_dispatch_stub_344):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2752(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2752(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2752(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2752(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_344), .-GL_PREFIX(_dispatch_stub_344)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_345)
	.type	GL_PREFIX(_dispatch_stub_345), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_345))
GL_PREFIX(_dispatch_stub_345):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2760(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2760(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2760(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2760(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_345), .-GL_PREFIX(_dispatch_stub_345)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_346)
	.type	GL_PREFIX(_dispatch_stub_346), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_346))
GL_PREFIX(_dispatch_stub_346):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2768(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2768(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2768(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2768(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_346), .-GL_PREFIX(_dispatch_stub_346)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_347)
	.type	GL_PREFIX(_dispatch_stub_347), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_347))
GL_PREFIX(_dispatch_stub_347):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2776(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2776(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2776(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2776(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_347), .-GL_PREFIX(_dispatch_stub_347)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_348)
	.type	GL_PREFIX(_dispatch_stub_348), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_348))
GL_PREFIX(_dispatch_stub_348):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2784(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2784(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2784(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2784(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_348), .-GL_PREFIX(_dispatch_stub_348)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_349)
	.type	GL_PREFIX(_dispatch_stub_349), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_349))
GL_PREFIX(_dispatch_stub_349):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2792(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2792(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2792(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2792(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_349), .-GL_PREFIX(_dispatch_stub_349)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_350)
	.type	GL_PREFIX(_dispatch_stub_350), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_350))
GL_PREFIX(_dispatch_stub_350):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2800(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	2800(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2800(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%rsi, 8(%rsp)
	movq	%xmm0, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm0
	movq	8(%rsp), %rsi
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	2800(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_350), .-GL_PREFIX(_dispatch_stub_350)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_351)
	.type	GL_PREFIX(_dispatch_stub_351), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_351))
GL_PREFIX(_dispatch_stub_351):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2808(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2808(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2808(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2808(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_351), .-GL_PREFIX(_dispatch_stub_351)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_352)
	.type	GL_PREFIX(_dispatch_stub_352), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_352))
GL_PREFIX(_dispatch_stub_352):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2816(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2816(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2816(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2816(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_352), .-GL_PREFIX(_dispatch_stub_352)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_353)
	.type	GL_PREFIX(_dispatch_stub_353), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_353))
GL_PREFIX(_dispatch_stub_353):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2824(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2824(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2824(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2824(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_353), .-GL_PREFIX(_dispatch_stub_353)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_354)
	.type	GL_PREFIX(_dispatch_stub_354), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_354))
GL_PREFIX(_dispatch_stub_354):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2832(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2832(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2832(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2832(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_354), .-GL_PREFIX(_dispatch_stub_354)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_355)
	.type	GL_PREFIX(_dispatch_stub_355), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_355))
GL_PREFIX(_dispatch_stub_355):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2840(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2840(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2840(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2840(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_355), .-GL_PREFIX(_dispatch_stub_355)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_356)
	.type	GL_PREFIX(_dispatch_stub_356), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_356))
GL_PREFIX(_dispatch_stub_356):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2848(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2848(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2848(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2848(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_356), .-GL_PREFIX(_dispatch_stub_356)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_357)
	.type	GL_PREFIX(_dispatch_stub_357), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_357))
GL_PREFIX(_dispatch_stub_357):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2856(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2856(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2856(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2856(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_357), .-GL_PREFIX(_dispatch_stub_357)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_358)
	.type	GL_PREFIX(_dispatch_stub_358), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_358))
GL_PREFIX(_dispatch_stub_358):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2864(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2864(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2864(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2864(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_358), .-GL_PREFIX(_dispatch_stub_358)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_359)
	.type	GL_PREFIX(_dispatch_stub_359), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_359))
GL_PREFIX(_dispatch_stub_359):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2872(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2872(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2872(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2872(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_359), .-GL_PREFIX(_dispatch_stub_359)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_360)
	.type	GL_PREFIX(_dispatch_stub_360), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_360))
GL_PREFIX(_dispatch_stub_360):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2880(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2880(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2880(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2880(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_360), .-GL_PREFIX(_dispatch_stub_360)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_361)
	.type	GL_PREFIX(_dispatch_stub_361), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_361))
GL_PREFIX(_dispatch_stub_361):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2888(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2888(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2888(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2888(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_361), .-GL_PREFIX(_dispatch_stub_361)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_362)
	.type	GL_PREFIX(_dispatch_stub_362), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_362))
GL_PREFIX(_dispatch_stub_362):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2896(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2896(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2896(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2896(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_362), .-GL_PREFIX(_dispatch_stub_362)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_363)
	.type	GL_PREFIX(_dispatch_stub_363), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_363))
GL_PREFIX(_dispatch_stub_363):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2904(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2904(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2904(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2904(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_363), .-GL_PREFIX(_dispatch_stub_363)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_364)
	.type	GL_PREFIX(_dispatch_stub_364), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_364))
GL_PREFIX(_dispatch_stub_364):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2912(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2912(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2912(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2912(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_364), .-GL_PREFIX(_dispatch_stub_364)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_365)
	.type	GL_PREFIX(_dispatch_stub_365), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_365))
GL_PREFIX(_dispatch_stub_365):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2920(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2920(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2920(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2920(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_365), .-GL_PREFIX(_dispatch_stub_365)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_366)
	.type	GL_PREFIX(_dispatch_stub_366), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_366))
GL_PREFIX(_dispatch_stub_366):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2928(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2928(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2928(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2928(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_366), .-GL_PREFIX(_dispatch_stub_366)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_367)
	.type	GL_PREFIX(_dispatch_stub_367), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_367))
GL_PREFIX(_dispatch_stub_367):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2936(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2936(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2936(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2936(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_367), .-GL_PREFIX(_dispatch_stub_367)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_368)
	.type	GL_PREFIX(_dispatch_stub_368), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_368))
GL_PREFIX(_dispatch_stub_368):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2944(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2944(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2944(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2944(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_368), .-GL_PREFIX(_dispatch_stub_368)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_369)
	.type	GL_PREFIX(_dispatch_stub_369), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_369))
GL_PREFIX(_dispatch_stub_369):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2952(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2952(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2952(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2952(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_369), .-GL_PREFIX(_dispatch_stub_369)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_370)
	.type	GL_PREFIX(_dispatch_stub_370), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_370))
GL_PREFIX(_dispatch_stub_370):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2960(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2960(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2960(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2960(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_370), .-GL_PREFIX(_dispatch_stub_370)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_371)
	.type	GL_PREFIX(_dispatch_stub_371), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_371))
GL_PREFIX(_dispatch_stub_371):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2968(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2968(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2968(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2968(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_371), .-GL_PREFIX(_dispatch_stub_371)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_372)
	.type	GL_PREFIX(_dispatch_stub_372), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_372))
GL_PREFIX(_dispatch_stub_372):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2976(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2976(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2976(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2976(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_372), .-GL_PREFIX(_dispatch_stub_372)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_373)
	.type	GL_PREFIX(_dispatch_stub_373), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_373))
GL_PREFIX(_dispatch_stub_373):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2984(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2984(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2984(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	2984(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_373), .-GL_PREFIX(_dispatch_stub_373)

	.p2align	4,,15
	.globl	GL_PREFIX(ActiveTexture)
	.type	GL_PREFIX(ActiveTexture), @function
GL_PREFIX(ActiveTexture):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	2992(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	2992(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	2992(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	2992(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ActiveTexture), .-GL_PREFIX(ActiveTexture)

	.p2align	4,,15
	.globl	GL_PREFIX(ClientActiveTexture)
	.type	GL_PREFIX(ClientActiveTexture), @function
GL_PREFIX(ClientActiveTexture):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3000(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3000(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3000(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3000(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ClientActiveTexture), .-GL_PREFIX(ClientActiveTexture)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_376)
	.type	GL_PREFIX(_dispatch_stub_376), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_376))
GL_PREFIX(_dispatch_stub_376):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3008(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	3008(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3008(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	3008(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_376), .-GL_PREFIX(_dispatch_stub_376)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_377)
	.type	GL_PREFIX(_dispatch_stub_377), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_377))
GL_PREFIX(_dispatch_stub_377):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3016(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3016(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3016(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3016(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_377), .-GL_PREFIX(_dispatch_stub_377)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_378)
	.type	GL_PREFIX(_dispatch_stub_378), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_378))
GL_PREFIX(_dispatch_stub_378):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3024(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	3024(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3024(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	3024(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_378), .-GL_PREFIX(_dispatch_stub_378)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_379)
	.type	GL_PREFIX(_dispatch_stub_379), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_379))
GL_PREFIX(_dispatch_stub_379):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3032(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3032(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3032(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3032(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_379), .-GL_PREFIX(_dispatch_stub_379)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_380)
	.type	GL_PREFIX(_dispatch_stub_380), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_380))
GL_PREFIX(_dispatch_stub_380):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3040(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3040(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3040(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3040(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_380), .-GL_PREFIX(_dispatch_stub_380)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_381)
	.type	GL_PREFIX(_dispatch_stub_381), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_381))
GL_PREFIX(_dispatch_stub_381):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3048(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3048(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3048(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3048(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_381), .-GL_PREFIX(_dispatch_stub_381)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_382)
	.type	GL_PREFIX(_dispatch_stub_382), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_382))
GL_PREFIX(_dispatch_stub_382):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3056(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3056(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3056(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3056(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_382), .-GL_PREFIX(_dispatch_stub_382)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_383)
	.type	GL_PREFIX(_dispatch_stub_383), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_383))
GL_PREFIX(_dispatch_stub_383):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3064(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3064(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3064(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3064(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_383), .-GL_PREFIX(_dispatch_stub_383)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_384)
	.type	GL_PREFIX(_dispatch_stub_384), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_384))
GL_PREFIX(_dispatch_stub_384):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3072(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	3072(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3072(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	3072(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_384), .-GL_PREFIX(_dispatch_stub_384)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_385)
	.type	GL_PREFIX(_dispatch_stub_385), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_385))
GL_PREFIX(_dispatch_stub_385):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3080(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3080(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3080(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3080(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_385), .-GL_PREFIX(_dispatch_stub_385)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_386)
	.type	GL_PREFIX(_dispatch_stub_386), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_386))
GL_PREFIX(_dispatch_stub_386):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3088(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	3088(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3088(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	call	_glapi_get_dispatch
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	3088(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_386), .-GL_PREFIX(_dispatch_stub_386)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_387)
	.type	GL_PREFIX(_dispatch_stub_387), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_387))
GL_PREFIX(_dispatch_stub_387):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3096(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3096(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3096(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3096(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_387), .-GL_PREFIX(_dispatch_stub_387)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_388)
	.type	GL_PREFIX(_dispatch_stub_388), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_388))
GL_PREFIX(_dispatch_stub_388):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3104(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3104(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3104(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3104(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_388), .-GL_PREFIX(_dispatch_stub_388)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_389)
	.type	GL_PREFIX(_dispatch_stub_389), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_389))
GL_PREFIX(_dispatch_stub_389):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3112(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3112(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3112(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3112(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_389), .-GL_PREFIX(_dispatch_stub_389)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_390)
	.type	GL_PREFIX(_dispatch_stub_390), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_390))
GL_PREFIX(_dispatch_stub_390):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3120(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3120(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3120(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3120(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_390), .-GL_PREFIX(_dispatch_stub_390)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_391)
	.type	GL_PREFIX(_dispatch_stub_391), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_391))
GL_PREFIX(_dispatch_stub_391):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3128(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3128(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3128(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3128(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_391), .-GL_PREFIX(_dispatch_stub_391)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_392)
	.type	GL_PREFIX(_dispatch_stub_392), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_392))
GL_PREFIX(_dispatch_stub_392):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3136(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%xmm2, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm2
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$40, %rsp
	movq	3136(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3136(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%xmm2, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm2
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$40, %rsp
	movq	3136(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_392), .-GL_PREFIX(_dispatch_stub_392)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_393)
	.type	GL_PREFIX(_dispatch_stub_393), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_393))
GL_PREFIX(_dispatch_stub_393):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3144(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3144(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3144(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3144(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_393), .-GL_PREFIX(_dispatch_stub_393)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_394)
	.type	GL_PREFIX(_dispatch_stub_394), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_394))
GL_PREFIX(_dispatch_stub_394):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3152(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%xmm2, 24(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	24(%rsp), %xmm2
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$40, %rsp
	movq	3152(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3152(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%xmm2, 24(%rsp)
	call	_glapi_get_dispatch
	movq	24(%rsp), %xmm2
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$40, %rsp
	movq	3152(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_394), .-GL_PREFIX(_dispatch_stub_394)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_395)
	.type	GL_PREFIX(_dispatch_stub_395), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_395))
GL_PREFIX(_dispatch_stub_395):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3160(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3160(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3160(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3160(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_395), .-GL_PREFIX(_dispatch_stub_395)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_396)
	.type	GL_PREFIX(_dispatch_stub_396), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_396))
GL_PREFIX(_dispatch_stub_396):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3168(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3168(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3168(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3168(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_396), .-GL_PREFIX(_dispatch_stub_396)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_397)
	.type	GL_PREFIX(_dispatch_stub_397), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_397))
GL_PREFIX(_dispatch_stub_397):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3176(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3176(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3176(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3176(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_397), .-GL_PREFIX(_dispatch_stub_397)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_398)
	.type	GL_PREFIX(_dispatch_stub_398), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_398))
GL_PREFIX(_dispatch_stub_398):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3184(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3184(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3184(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3184(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_398), .-GL_PREFIX(_dispatch_stub_398)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_399)
	.type	GL_PREFIX(_dispatch_stub_399), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_399))
GL_PREFIX(_dispatch_stub_399):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3192(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3192(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3192(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3192(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_399), .-GL_PREFIX(_dispatch_stub_399)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_400)
	.type	GL_PREFIX(_dispatch_stub_400), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_400))
GL_PREFIX(_dispatch_stub_400):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3200(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%xmm2, 24(%rsp)
	movq	%xmm3, 32(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	32(%rsp), %xmm3
	movq	24(%rsp), %xmm2
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$40, %rsp
	movq	3200(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3200(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%xmm2, 24(%rsp)
	movq	%xmm3, 32(%rsp)
	call	_glapi_get_dispatch
	movq	32(%rsp), %xmm3
	movq	24(%rsp), %xmm2
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$40, %rsp
	movq	3200(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_400), .-GL_PREFIX(_dispatch_stub_400)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_401)
	.type	GL_PREFIX(_dispatch_stub_401), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_401))
GL_PREFIX(_dispatch_stub_401):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3208(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3208(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3208(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3208(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_401), .-GL_PREFIX(_dispatch_stub_401)

	.p2align	4,,15
	.globl	GL_PREFIX(MultiTexCoord4f)
	.type	GL_PREFIX(MultiTexCoord4f), @function
GL_PREFIX(MultiTexCoord4f):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3216(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%xmm2, 24(%rsp)
	movq	%xmm3, 32(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	32(%rsp), %xmm3
	movq	24(%rsp), %xmm2
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$40, %rsp
	movq	3216(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3216(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	movq	%xmm1, 16(%rsp)
	movq	%xmm2, 24(%rsp)
	movq	%xmm3, 32(%rsp)
	call	_glapi_get_dispatch
	movq	32(%rsp), %xmm3
	movq	24(%rsp), %xmm2
	movq	16(%rsp), %xmm1
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$40, %rsp
	movq	3216(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(MultiTexCoord4f), .-GL_PREFIX(MultiTexCoord4f)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_403)
	.type	GL_PREFIX(_dispatch_stub_403), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_403))
GL_PREFIX(_dispatch_stub_403):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3224(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3224(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3224(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3224(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_403), .-GL_PREFIX(_dispatch_stub_403)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_404)
	.type	GL_PREFIX(_dispatch_stub_404), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_404))
GL_PREFIX(_dispatch_stub_404):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3232(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3232(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3232(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3232(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_404), .-GL_PREFIX(_dispatch_stub_404)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_405)
	.type	GL_PREFIX(_dispatch_stub_405), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_405))
GL_PREFIX(_dispatch_stub_405):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3240(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3240(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3240(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3240(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_405), .-GL_PREFIX(_dispatch_stub_405)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_406)
	.type	GL_PREFIX(_dispatch_stub_406), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_406))
GL_PREFIX(_dispatch_stub_406):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3248(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3248(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3248(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3248(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_406), .-GL_PREFIX(_dispatch_stub_406)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_407)
	.type	GL_PREFIX(_dispatch_stub_407), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_407))
GL_PREFIX(_dispatch_stub_407):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3256(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3256(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3256(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3256(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_407), .-GL_PREFIX(_dispatch_stub_407)

	.p2align	4,,15
	.globl	GL_PREFIX(BlendEquationSeparateOES)
	.type	GL_PREFIX(BlendEquationSeparateOES), @function
GL_PREFIX(BlendEquationSeparateOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3264(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3264(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3264(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3264(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(BlendEquationSeparateOES), .-GL_PREFIX(BlendEquationSeparateOES)

	.p2align	4,,15
	.globl	GL_PREFIX(BlendFuncSeparateOES)
	.type	GL_PREFIX(BlendFuncSeparateOES), @function
GL_PREFIX(BlendFuncSeparateOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3272(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3272(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3272(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3272(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(BlendFuncSeparateOES), .-GL_PREFIX(BlendFuncSeparateOES)

	.p2align	4,,15
	.globl	GL_PREFIX(DrawTexfOES)
	.type	GL_PREFIX(DrawTexfOES), @function
GL_PREFIX(DrawTexfOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3280(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%xmm4, 32(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	32(%rsp), %xmm4
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	3280(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3280(%rax), %r11
	jmp	*%r11
1:
	subq	$40, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%xmm4, 32(%rsp)
	call	_glapi_get_dispatch
	movq	32(%rsp), %xmm4
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$40, %rsp
	movq	3280(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DrawTexfOES), .-GL_PREFIX(DrawTexfOES)

	.p2align	4,,15
	.globl	GL_PREFIX(DrawTexfvOES)
	.type	GL_PREFIX(DrawTexfvOES), @function
GL_PREFIX(DrawTexfvOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3288(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3288(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3288(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3288(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DrawTexfvOES), .-GL_PREFIX(DrawTexfvOES)

	.p2align	4,,15
	.globl	GL_PREFIX(DrawTexiOES)
	.type	GL_PREFIX(DrawTexiOES), @function
GL_PREFIX(DrawTexiOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3296(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3296(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3296(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3296(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DrawTexiOES), .-GL_PREFIX(DrawTexiOES)

	.p2align	4,,15
	.globl	GL_PREFIX(DrawTexivOES)
	.type	GL_PREFIX(DrawTexivOES), @function
GL_PREFIX(DrawTexivOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3304(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3304(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3304(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3304(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DrawTexivOES), .-GL_PREFIX(DrawTexivOES)

	.p2align	4,,15
	.globl	GL_PREFIX(DrawTexsOES)
	.type	GL_PREFIX(DrawTexsOES), @function
GL_PREFIX(DrawTexsOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3312(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3312(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3312(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3312(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DrawTexsOES), .-GL_PREFIX(DrawTexsOES)

	.p2align	4,,15
	.globl	GL_PREFIX(DrawTexsvOES)
	.type	GL_PREFIX(DrawTexsvOES), @function
GL_PREFIX(DrawTexsvOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3320(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3320(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3320(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3320(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DrawTexsvOES), .-GL_PREFIX(DrawTexsvOES)

	.p2align	4,,15
	.globl	GL_PREFIX(DrawTexxOES)
	.type	GL_PREFIX(DrawTexxOES), @function
GL_PREFIX(DrawTexxOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3328(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3328(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3328(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3328(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DrawTexxOES), .-GL_PREFIX(DrawTexxOES)

	.p2align	4,,15
	.globl	GL_PREFIX(DrawTexxvOES)
	.type	GL_PREFIX(DrawTexxvOES), @function
GL_PREFIX(DrawTexxvOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3336(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3336(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3336(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3336(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DrawTexxvOES), .-GL_PREFIX(DrawTexxvOES)

	.p2align	4,,15
	.globl	GL_PREFIX(BindFramebufferOES)
	.type	GL_PREFIX(BindFramebufferOES), @function
GL_PREFIX(BindFramebufferOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3344(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3344(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3344(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3344(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(BindFramebufferOES), .-GL_PREFIX(BindFramebufferOES)

	.p2align	4,,15
	.globl	GL_PREFIX(BindRenderbufferOES)
	.type	GL_PREFIX(BindRenderbufferOES), @function
GL_PREFIX(BindRenderbufferOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3352(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3352(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3352(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3352(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(BindRenderbufferOES), .-GL_PREFIX(BindRenderbufferOES)

	.p2align	4,,15
	.globl	GL_PREFIX(CheckFramebufferStatusOES)
	.type	GL_PREFIX(CheckFramebufferStatusOES), @function
GL_PREFIX(CheckFramebufferStatusOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3360(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3360(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3360(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3360(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(CheckFramebufferStatusOES), .-GL_PREFIX(CheckFramebufferStatusOES)

	.p2align	4,,15
	.globl	GL_PREFIX(DeleteFramebuffersOES)
	.type	GL_PREFIX(DeleteFramebuffersOES), @function
GL_PREFIX(DeleteFramebuffersOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3368(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3368(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3368(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3368(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DeleteFramebuffersOES), .-GL_PREFIX(DeleteFramebuffersOES)

	.p2align	4,,15
	.globl	GL_PREFIX(DeleteRenderbuffersOES)
	.type	GL_PREFIX(DeleteRenderbuffersOES), @function
GL_PREFIX(DeleteRenderbuffersOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3376(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3376(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3376(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3376(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DeleteRenderbuffersOES), .-GL_PREFIX(DeleteRenderbuffersOES)

	.p2align	4,,15
	.globl	GL_PREFIX(FramebufferRenderbufferOES)
	.type	GL_PREFIX(FramebufferRenderbufferOES), @function
GL_PREFIX(FramebufferRenderbufferOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3384(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3384(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3384(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3384(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(FramebufferRenderbufferOES), .-GL_PREFIX(FramebufferRenderbufferOES)

	.p2align	4,,15
	.globl	GL_PREFIX(FramebufferTexture2DOES)
	.type	GL_PREFIX(FramebufferTexture2DOES), @function
GL_PREFIX(FramebufferTexture2DOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3392(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3392(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3392(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3392(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(FramebufferTexture2DOES), .-GL_PREFIX(FramebufferTexture2DOES)

	.p2align	4,,15
	.globl	GL_PREFIX(GenFramebuffersOES)
	.type	GL_PREFIX(GenFramebuffersOES), @function
GL_PREFIX(GenFramebuffersOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3400(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3400(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3400(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3400(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GenFramebuffersOES), .-GL_PREFIX(GenFramebuffersOES)

	.p2align	4,,15
	.globl	GL_PREFIX(GenRenderbuffersOES)
	.type	GL_PREFIX(GenRenderbuffersOES), @function
GL_PREFIX(GenRenderbuffersOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3408(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3408(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3408(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3408(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GenRenderbuffersOES), .-GL_PREFIX(GenRenderbuffersOES)

	.p2align	4,,15
	.globl	GL_PREFIX(GenerateMipmapOES)
	.type	GL_PREFIX(GenerateMipmapOES), @function
GL_PREFIX(GenerateMipmapOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3416(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3416(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3416(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3416(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GenerateMipmapOES), .-GL_PREFIX(GenerateMipmapOES)

	.p2align	4,,15
	.globl	GL_PREFIX(GetFramebufferAttachmentParameterivOES)
	.type	GL_PREFIX(GetFramebufferAttachmentParameterivOES), @function
GL_PREFIX(GetFramebufferAttachmentParameterivOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3424(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3424(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3424(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3424(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetFramebufferAttachmentParameterivOES), .-GL_PREFIX(GetFramebufferAttachmentParameterivOES)

	.p2align	4,,15
	.globl	GL_PREFIX(GetRenderbufferParameterivOES)
	.type	GL_PREFIX(GetRenderbufferParameterivOES), @function
GL_PREFIX(GetRenderbufferParameterivOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3432(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3432(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3432(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3432(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetRenderbufferParameterivOES), .-GL_PREFIX(GetRenderbufferParameterivOES)

	.p2align	4,,15
	.globl	GL_PREFIX(IsFramebufferOES)
	.type	GL_PREFIX(IsFramebufferOES), @function
GL_PREFIX(IsFramebufferOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3440(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3440(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3440(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3440(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(IsFramebufferOES), .-GL_PREFIX(IsFramebufferOES)

	.p2align	4,,15
	.globl	GL_PREFIX(IsRenderbufferOES)
	.type	GL_PREFIX(IsRenderbufferOES), @function
GL_PREFIX(IsRenderbufferOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3448(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3448(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3448(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3448(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(IsRenderbufferOES), .-GL_PREFIX(IsRenderbufferOES)

	.p2align	4,,15
	.globl	GL_PREFIX(RenderbufferStorageOES)
	.type	GL_PREFIX(RenderbufferStorageOES), @function
GL_PREFIX(RenderbufferStorageOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3456(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3456(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3456(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3456(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(RenderbufferStorageOES), .-GL_PREFIX(RenderbufferStorageOES)

	.p2align	4,,15
	.globl	GL_PREFIX(PointSizePointerOES)
	.type	GL_PREFIX(PointSizePointerOES), @function
GL_PREFIX(PointSizePointerOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3464(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3464(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3464(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3464(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PointSizePointerOES), .-GL_PREFIX(PointSizePointerOES)

	.p2align	4,,15
	.globl	GL_PREFIX(QueryMatrixxOES)
	.type	GL_PREFIX(QueryMatrixxOES), @function
GL_PREFIX(QueryMatrixxOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3472(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3472(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3472(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3472(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(QueryMatrixxOES), .-GL_PREFIX(QueryMatrixxOES)

	.p2align	4,,15
	.globl	GL_PREFIX(GetTexGenxvOES)
	.type	GL_PREFIX(GetTexGenxvOES), @function
GL_PREFIX(GetTexGenxvOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3480(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3480(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3480(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3480(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetTexGenxvOES), .-GL_PREFIX(GetTexGenxvOES)

	.p2align	4,,15
	.globl	GL_PREFIX(TexGenxOES)
	.type	GL_PREFIX(TexGenxOES), @function
GL_PREFIX(TexGenxOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3488(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3488(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3488(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3488(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexGenxOES), .-GL_PREFIX(TexGenxOES)

	.p2align	4,,15
	.globl	GL_PREFIX(TexGenxvOES)
	.type	GL_PREFIX(TexGenxvOES), @function
GL_PREFIX(TexGenxvOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3496(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3496(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3496(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3496(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexGenxvOES), .-GL_PREFIX(TexGenxvOES)

	.p2align	4,,15
	.globl	GL_PREFIX(GetBufferPointervOES)
	.type	GL_PREFIX(GetBufferPointervOES), @function
GL_PREFIX(GetBufferPointervOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3504(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3504(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3504(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3504(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetBufferPointervOES), .-GL_PREFIX(GetBufferPointervOES)

	.p2align	4,,15
	.globl	GL_PREFIX(MapBufferOES)
	.type	GL_PREFIX(MapBufferOES), @function
GL_PREFIX(MapBufferOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3512(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3512(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3512(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3512(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(MapBufferOES), .-GL_PREFIX(MapBufferOES)

	.p2align	4,,15
	.globl	GL_PREFIX(UnmapBufferOES)
	.type	GL_PREFIX(UnmapBufferOES), @function
GL_PREFIX(UnmapBufferOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3520(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3520(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3520(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3520(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(UnmapBufferOES), .-GL_PREFIX(UnmapBufferOES)

	.p2align	4,,15
	.globl	GL_PREFIX(MultiDrawArraysEXT)
	.type	GL_PREFIX(MultiDrawArraysEXT), @function
GL_PREFIX(MultiDrawArraysEXT):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3528(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3528(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3528(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3528(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(MultiDrawArraysEXT), .-GL_PREFIX(MultiDrawArraysEXT)

	.p2align	4,,15
	.globl	GL_PREFIX(MultiDrawElementsEXT)
	.type	GL_PREFIX(MultiDrawElementsEXT), @function
GL_PREFIX(MultiDrawElementsEXT):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3536(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3536(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3536(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3536(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(MultiDrawElementsEXT), .-GL_PREFIX(MultiDrawElementsEXT)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_443)
	.type	GL_PREFIX(_dispatch_stub_443), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_443))
GL_PREFIX(_dispatch_stub_443):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3544(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3544(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3544(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3544(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_443), .-GL_PREFIX(_dispatch_stub_443)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_444)
	.type	GL_PREFIX(_dispatch_stub_444), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_444))
GL_PREFIX(_dispatch_stub_444):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3552(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3552(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3552(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3552(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_444), .-GL_PREFIX(_dispatch_stub_444)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_445)
	.type	GL_PREFIX(_dispatch_stub_445), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_445))
GL_PREFIX(_dispatch_stub_445):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3560(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3560(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3560(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3560(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_445), .-GL_PREFIX(_dispatch_stub_445)

	.p2align	4,,15
	.globl	GL_PREFIX(_dispatch_stub_446)
	.type	GL_PREFIX(_dispatch_stub_446), @function
	HIDDEN(GL_PREFIX(_dispatch_stub_446))
GL_PREFIX(_dispatch_stub_446):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3568(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3568(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3568(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3568(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(_dispatch_stub_446), .-GL_PREFIX(_dispatch_stub_446)

	.p2align	4,,15
	.globl	GL_PREFIX(EGLImageTargetRenderbufferStorageOES)
	.type	GL_PREFIX(EGLImageTargetRenderbufferStorageOES), @function
GL_PREFIX(EGLImageTargetRenderbufferStorageOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3576(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3576(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3576(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3576(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(EGLImageTargetRenderbufferStorageOES), .-GL_PREFIX(EGLImageTargetRenderbufferStorageOES)

	.p2align	4,,15
	.globl	GL_PREFIX(EGLImageTargetTexture2DOES)
	.type	GL_PREFIX(EGLImageTargetTexture2DOES), @function
GL_PREFIX(EGLImageTargetTexture2DOES):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3584(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3584(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3584(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3584(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(EGLImageTargetTexture2DOES), .-GL_PREFIX(EGLImageTargetTexture2DOES)

	.p2align	4,,15
	.globl	GL_PREFIX(CompressedTexImage2D)
	.type	GL_PREFIX(CompressedTexImage2D), @function
GL_PREFIX(CompressedTexImage2D):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3592(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3592(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3592(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3592(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(CompressedTexImage2D), .-GL_PREFIX(CompressedTexImage2D)

	.p2align	4,,15
	.globl	GL_PREFIX(CompressedTexSubImage2D)
	.type	GL_PREFIX(CompressedTexSubImage2D), @function
GL_PREFIX(CompressedTexSubImage2D):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3600(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3600(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3600(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3600(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(CompressedTexSubImage2D), .-GL_PREFIX(CompressedTexSubImage2D)

	.p2align	4,,15
	.globl	GL_PREFIX(SampleCoverage)
	.type	GL_PREFIX(SampleCoverage), @function
GL_PREFIX(SampleCoverage):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3608(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3608(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3608(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3608(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(SampleCoverage), .-GL_PREFIX(SampleCoverage)

	.p2align	4,,15
	.globl	GL_PREFIX(BindBuffer)
	.type	GL_PREFIX(BindBuffer), @function
GL_PREFIX(BindBuffer):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3616(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3616(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3616(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3616(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(BindBuffer), .-GL_PREFIX(BindBuffer)

	.p2align	4,,15
	.globl	GL_PREFIX(BufferData)
	.type	GL_PREFIX(BufferData), @function
GL_PREFIX(BufferData):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3624(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3624(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3624(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3624(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(BufferData), .-GL_PREFIX(BufferData)

	.p2align	4,,15
	.globl	GL_PREFIX(BufferSubData)
	.type	GL_PREFIX(BufferSubData), @function
GL_PREFIX(BufferSubData):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3632(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3632(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3632(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3632(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(BufferSubData), .-GL_PREFIX(BufferSubData)

	.p2align	4,,15
	.globl	GL_PREFIX(DeleteBuffers)
	.type	GL_PREFIX(DeleteBuffers), @function
GL_PREFIX(DeleteBuffers):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3640(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3640(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3640(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3640(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DeleteBuffers), .-GL_PREFIX(DeleteBuffers)

	.p2align	4,,15
	.globl	GL_PREFIX(GenBuffers)
	.type	GL_PREFIX(GenBuffers), @function
GL_PREFIX(GenBuffers):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3648(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3648(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3648(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3648(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GenBuffers), .-GL_PREFIX(GenBuffers)

	.p2align	4,,15
	.globl	GL_PREFIX(GetBufferParameteriv)
	.type	GL_PREFIX(GetBufferParameteriv), @function
GL_PREFIX(GetBufferParameteriv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3656(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3656(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3656(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3656(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetBufferParameteriv), .-GL_PREFIX(GetBufferParameteriv)

	.p2align	4,,15
	.globl	GL_PREFIX(IsBuffer)
	.type	GL_PREFIX(IsBuffer), @function
GL_PREFIX(IsBuffer):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3664(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3664(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3664(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3664(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(IsBuffer), .-GL_PREFIX(IsBuffer)

	.p2align	4,,15
	.globl	GL_PREFIX(PointParameterf)
	.type	GL_PREFIX(PointParameterf), @function
GL_PREFIX(PointParameterf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3672(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	3672(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3672(%rax), %r11
	jmp	*%r11
1:
	subq	$24, %rsp
	movq	%rdi, (%rsp)
	movq	%xmm0, 8(%rsp)
	call	_glapi_get_dispatch
	movq	8(%rsp), %xmm0
	movq	(%rsp), %rdi
	addq	$24, %rsp
	movq	3672(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PointParameterf), .-GL_PREFIX(PointParameterf)

	.p2align	4,,15
	.globl	GL_PREFIX(PointParameterfv)
	.type	GL_PREFIX(PointParameterfv), @function
GL_PREFIX(PointParameterfv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3680(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3680(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3680(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3680(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PointParameterfv), .-GL_PREFIX(PointParameterfv)

	.p2align	4,,15
	.globl	GL_PREFIX(AlphaFuncx)
	.type	GL_PREFIX(AlphaFuncx), @function
GL_PREFIX(AlphaFuncx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3688(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3688(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3688(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3688(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(AlphaFuncx), .-GL_PREFIX(AlphaFuncx)

	.p2align	4,,15
	.globl	GL_PREFIX(ClearColorx)
	.type	GL_PREFIX(ClearColorx), @function
GL_PREFIX(ClearColorx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3696(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3696(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3696(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3696(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ClearColorx), .-GL_PREFIX(ClearColorx)

	.p2align	4,,15
	.globl	GL_PREFIX(ClearDepthf)
	.type	GL_PREFIX(ClearDepthf), @function
GL_PREFIX(ClearDepthf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3704(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3704(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3704(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3704(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ClearDepthf), .-GL_PREFIX(ClearDepthf)

	.p2align	4,,15
	.globl	GL_PREFIX(ClearDepthx)
	.type	GL_PREFIX(ClearDepthx), @function
GL_PREFIX(ClearDepthx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3712(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3712(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3712(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3712(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ClearDepthx), .-GL_PREFIX(ClearDepthx)

	.p2align	4,,15
	.globl	GL_PREFIX(Color4x)
	.type	GL_PREFIX(Color4x), @function
GL_PREFIX(Color4x):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3720(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3720(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3720(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3720(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Color4x), .-GL_PREFIX(Color4x)

	.p2align	4,,15
	.globl	GL_PREFIX(DepthRangef)
	.type	GL_PREFIX(DepthRangef), @function
GL_PREFIX(DepthRangef):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3728(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3728(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3728(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3728(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DepthRangef), .-GL_PREFIX(DepthRangef)

	.p2align	4,,15
	.globl	GL_PREFIX(DepthRangex)
	.type	GL_PREFIX(DepthRangex), @function
GL_PREFIX(DepthRangex):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3736(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3736(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3736(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3736(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(DepthRangex), .-GL_PREFIX(DepthRangex)

	.p2align	4,,15
	.globl	GL_PREFIX(Fogx)
	.type	GL_PREFIX(Fogx), @function
GL_PREFIX(Fogx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3744(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3744(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3744(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3744(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Fogx), .-GL_PREFIX(Fogx)

	.p2align	4,,15
	.globl	GL_PREFIX(Fogxv)
	.type	GL_PREFIX(Fogxv), @function
GL_PREFIX(Fogxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3752(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3752(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3752(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3752(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Fogxv), .-GL_PREFIX(Fogxv)

	.p2align	4,,15
	.globl	GL_PREFIX(Frustumf)
	.type	GL_PREFIX(Frustumf), @function
GL_PREFIX(Frustumf):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3760(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$56, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%xmm4, 32(%rsp)
	movq	%xmm5, 40(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	40(%rsp), %xmm5
	movq	32(%rsp), %xmm4
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$56, %rsp
	movq	3760(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3760(%rax), %r11
	jmp	*%r11
1:
	subq	$56, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%xmm4, 32(%rsp)
	movq	%xmm5, 40(%rsp)
	call	_glapi_get_dispatch
	movq	40(%rsp), %xmm5
	movq	32(%rsp), %xmm4
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$56, %rsp
	movq	3760(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Frustumf), .-GL_PREFIX(Frustumf)

	.p2align	4,,15
	.globl	GL_PREFIX(Frustumx)
	.type	GL_PREFIX(Frustumx), @function
GL_PREFIX(Frustumx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3768(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3768(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3768(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3768(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Frustumx), .-GL_PREFIX(Frustumx)

	.p2align	4,,15
	.globl	GL_PREFIX(LightModelx)
	.type	GL_PREFIX(LightModelx), @function
GL_PREFIX(LightModelx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3776(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3776(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3776(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3776(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(LightModelx), .-GL_PREFIX(LightModelx)

	.p2align	4,,15
	.globl	GL_PREFIX(LightModelxv)
	.type	GL_PREFIX(LightModelxv), @function
GL_PREFIX(LightModelxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3784(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3784(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3784(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3784(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(LightModelxv), .-GL_PREFIX(LightModelxv)

	.p2align	4,,15
	.globl	GL_PREFIX(Lightx)
	.type	GL_PREFIX(Lightx), @function
GL_PREFIX(Lightx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3792(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3792(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3792(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3792(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Lightx), .-GL_PREFIX(Lightx)

	.p2align	4,,15
	.globl	GL_PREFIX(Lightxv)
	.type	GL_PREFIX(Lightxv), @function
GL_PREFIX(Lightxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3800(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3800(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3800(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3800(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Lightxv), .-GL_PREFIX(Lightxv)

	.p2align	4,,15
	.globl	GL_PREFIX(LineWidthx)
	.type	GL_PREFIX(LineWidthx), @function
GL_PREFIX(LineWidthx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3808(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3808(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3808(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3808(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(LineWidthx), .-GL_PREFIX(LineWidthx)

	.p2align	4,,15
	.globl	GL_PREFIX(LoadMatrixx)
	.type	GL_PREFIX(LoadMatrixx), @function
GL_PREFIX(LoadMatrixx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3816(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3816(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3816(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3816(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(LoadMatrixx), .-GL_PREFIX(LoadMatrixx)

	.p2align	4,,15
	.globl	GL_PREFIX(Materialx)
	.type	GL_PREFIX(Materialx), @function
GL_PREFIX(Materialx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3824(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3824(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3824(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3824(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Materialx), .-GL_PREFIX(Materialx)

	.p2align	4,,15
	.globl	GL_PREFIX(Materialxv)
	.type	GL_PREFIX(Materialxv), @function
GL_PREFIX(Materialxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3832(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3832(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3832(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3832(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Materialxv), .-GL_PREFIX(Materialxv)

	.p2align	4,,15
	.globl	GL_PREFIX(MultMatrixx)
	.type	GL_PREFIX(MultMatrixx), @function
GL_PREFIX(MultMatrixx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3840(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3840(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3840(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3840(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(MultMatrixx), .-GL_PREFIX(MultMatrixx)

	.p2align	4,,15
	.globl	GL_PREFIX(MultiTexCoord4x)
	.type	GL_PREFIX(MultiTexCoord4x), @function
GL_PREFIX(MultiTexCoord4x):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3848(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_x86_64_get_dispatch@PLT
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3848(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3848(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	call	_glapi_get_dispatch
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3848(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(MultiTexCoord4x), .-GL_PREFIX(MultiTexCoord4x)

	.p2align	4,,15
	.globl	GL_PREFIX(Normal3x)
	.type	GL_PREFIX(Normal3x), @function
GL_PREFIX(Normal3x):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3856(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3856(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3856(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3856(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Normal3x), .-GL_PREFIX(Normal3x)

	.p2align	4,,15
	.globl	GL_PREFIX(Orthof)
	.type	GL_PREFIX(Orthof), @function
GL_PREFIX(Orthof):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3864(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	subq	$56, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%xmm4, 32(%rsp)
	movq	%xmm5, 40(%rsp)
	call	_x86_64_get_dispatch@PLT
	movq	40(%rsp), %xmm5
	movq	32(%rsp), %xmm4
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$56, %rsp
	movq	3864(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3864(%rax), %r11
	jmp	*%r11
1:
	subq	$56, %rsp
	movq	%xmm0, (%rsp)
	movq	%xmm1, 8(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%xmm4, 32(%rsp)
	movq	%xmm5, 40(%rsp)
	call	_glapi_get_dispatch
	movq	40(%rsp), %xmm5
	movq	32(%rsp), %xmm4
	movq	24(%rsp), %xmm3
	movq	16(%rsp), %xmm2
	movq	8(%rsp), %xmm1
	movq	(%rsp), %xmm0
	addq	$56, %rsp
	movq	3864(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Orthof), .-GL_PREFIX(Orthof)

	.p2align	4,,15
	.globl	GL_PREFIX(Orthox)
	.type	GL_PREFIX(Orthox), @function
GL_PREFIX(Orthox):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3872(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3872(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3872(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3872(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Orthox), .-GL_PREFIX(Orthox)

	.p2align	4,,15
	.globl	GL_PREFIX(PointSizex)
	.type	GL_PREFIX(PointSizex), @function
GL_PREFIX(PointSizex):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3880(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	call	_x86_64_get_dispatch@PLT
	popq	%rdi
	movq	3880(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3880(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	call	_glapi_get_dispatch
	popq	%rdi
	movq	3880(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PointSizex), .-GL_PREFIX(PointSizex)

	.p2align	4,,15
	.globl	GL_PREFIX(PolygonOffsetx)
	.type	GL_PREFIX(PolygonOffsetx), @function
GL_PREFIX(PolygonOffsetx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3888(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3888(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3888(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3888(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PolygonOffsetx), .-GL_PREFIX(PolygonOffsetx)

	.p2align	4,,15
	.globl	GL_PREFIX(Rotatex)
	.type	GL_PREFIX(Rotatex), @function
GL_PREFIX(Rotatex):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3896(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3896(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3896(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3896(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Rotatex), .-GL_PREFIX(Rotatex)

	.p2align	4,,15
	.globl	GL_PREFIX(SampleCoveragex)
	.type	GL_PREFIX(SampleCoveragex), @function
GL_PREFIX(SampleCoveragex):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3904(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3904(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3904(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3904(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(SampleCoveragex), .-GL_PREFIX(SampleCoveragex)

	.p2align	4,,15
	.globl	GL_PREFIX(Scalex)
	.type	GL_PREFIX(Scalex), @function
GL_PREFIX(Scalex):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3912(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3912(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3912(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3912(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Scalex), .-GL_PREFIX(Scalex)

	.p2align	4,,15
	.globl	GL_PREFIX(TexEnvx)
	.type	GL_PREFIX(TexEnvx), @function
GL_PREFIX(TexEnvx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3920(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3920(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3920(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3920(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexEnvx), .-GL_PREFIX(TexEnvx)

	.p2align	4,,15
	.globl	GL_PREFIX(TexEnvxv)
	.type	GL_PREFIX(TexEnvxv), @function
GL_PREFIX(TexEnvxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3928(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3928(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3928(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3928(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexEnvxv), .-GL_PREFIX(TexEnvxv)

	.p2align	4,,15
	.globl	GL_PREFIX(TexParameterx)
	.type	GL_PREFIX(TexParameterx), @function
GL_PREFIX(TexParameterx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3936(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3936(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3936(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3936(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexParameterx), .-GL_PREFIX(TexParameterx)

	.p2align	4,,15
	.globl	GL_PREFIX(Translatex)
	.type	GL_PREFIX(Translatex), @function
GL_PREFIX(Translatex):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3944(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3944(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3944(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3944(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(Translatex), .-GL_PREFIX(Translatex)

	.p2align	4,,15
	.globl	GL_PREFIX(ClipPlanef)
	.type	GL_PREFIX(ClipPlanef), @function
GL_PREFIX(ClipPlanef):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3952(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3952(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3952(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3952(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ClipPlanef), .-GL_PREFIX(ClipPlanef)

	.p2align	4,,15
	.globl	GL_PREFIX(ClipPlanex)
	.type	GL_PREFIX(ClipPlanex), @function
GL_PREFIX(ClipPlanex):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3960(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3960(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3960(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3960(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(ClipPlanex), .-GL_PREFIX(ClipPlanex)

	.p2align	4,,15
	.globl	GL_PREFIX(GetClipPlanef)
	.type	GL_PREFIX(GetClipPlanef), @function
GL_PREFIX(GetClipPlanef):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3968(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3968(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3968(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3968(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetClipPlanef), .-GL_PREFIX(GetClipPlanef)

	.p2align	4,,15
	.globl	GL_PREFIX(GetClipPlanex)
	.type	GL_PREFIX(GetClipPlanex), @function
GL_PREFIX(GetClipPlanex):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3976(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3976(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3976(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3976(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetClipPlanex), .-GL_PREFIX(GetClipPlanex)

	.p2align	4,,15
	.globl	GL_PREFIX(GetFixedv)
	.type	GL_PREFIX(GetFixedv), @function
GL_PREFIX(GetFixedv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3984(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3984(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3984(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	3984(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetFixedv), .-GL_PREFIX(GetFixedv)

	.p2align	4,,15
	.globl	GL_PREFIX(GetLightxv)
	.type	GL_PREFIX(GetLightxv), @function
GL_PREFIX(GetLightxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	3992(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3992(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	3992(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	3992(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetLightxv), .-GL_PREFIX(GetLightxv)

	.p2align	4,,15
	.globl	GL_PREFIX(GetMaterialxv)
	.type	GL_PREFIX(GetMaterialxv), @function
GL_PREFIX(GetMaterialxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	4000(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	4000(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	4000(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	4000(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetMaterialxv), .-GL_PREFIX(GetMaterialxv)

	.p2align	4,,15
	.globl	GL_PREFIX(GetTexEnvxv)
	.type	GL_PREFIX(GetTexEnvxv), @function
GL_PREFIX(GetTexEnvxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	4008(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	4008(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	4008(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	4008(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetTexEnvxv), .-GL_PREFIX(GetTexEnvxv)

	.p2align	4,,15
	.globl	GL_PREFIX(GetTexParameterxv)
	.type	GL_PREFIX(GetTexParameterxv), @function
GL_PREFIX(GetTexParameterxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	4016(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	4016(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	4016(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	4016(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(GetTexParameterxv), .-GL_PREFIX(GetTexParameterxv)

	.p2align	4,,15
	.globl	GL_PREFIX(PointParameterx)
	.type	GL_PREFIX(PointParameterx), @function
GL_PREFIX(PointParameterx):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	4024(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	4024(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	4024(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	4024(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PointParameterx), .-GL_PREFIX(PointParameterx)

	.p2align	4,,15
	.globl	GL_PREFIX(PointParameterxv)
	.type	GL_PREFIX(PointParameterxv), @function
GL_PREFIX(PointParameterxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	4032(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_x86_64_get_dispatch@PLT
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	4032(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	4032(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rbp
	call	_glapi_get_dispatch
	popq	%rbp
	popq	%rsi
	popq	%rdi
	movq	4032(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(PointParameterxv), .-GL_PREFIX(PointParameterxv)

	.p2align	4,,15
	.globl	GL_PREFIX(TexParameterxv)
	.type	GL_PREFIX(TexParameterxv), @function
GL_PREFIX(TexParameterxv):
#if defined(GLX_USE_TLS)
	call	_x86_64_get_dispatch@PLT
	movq	4040(%rax), %r11
	jmp	*%r11
#elif defined(PTHREADS)
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_x86_64_get_dispatch@PLT
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	4040(%rax), %r11
	jmp	*%r11
#else
	movq	_glapi_Dispatch(%rip), %rax
	testq	%rax, %rax
	je	1f
	movq	4040(%rax), %r11
	jmp	*%r11
1:
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	call	_glapi_get_dispatch
	popq	%rdx
	popq	%rsi
	popq	%rdi
	movq	4040(%rax), %r11
	jmp	*%r11
#endif /* defined(GLX_USE_TLS) */
	.size	GL_PREFIX(TexParameterxv), .-GL_PREFIX(TexParameterxv)

	.globl GL_PREFIX(AlphaFuncxOES) ; .set GL_PREFIX(AlphaFuncxOES), GL_PREFIX(AlphaFuncx)
	.globl GL_PREFIX(ClearColorxOES) ; .set GL_PREFIX(ClearColorxOES), GL_PREFIX(ClearColorx)
	.globl GL_PREFIX(ClearDepthfOES) ; .set GL_PREFIX(ClearDepthfOES), GL_PREFIX(ClearDepthf)
	.globl GL_PREFIX(ClearDepthxOES) ; .set GL_PREFIX(ClearDepthxOES), GL_PREFIX(ClearDepthx)
	.globl GL_PREFIX(Color4xOES) ; .set GL_PREFIX(Color4xOES), GL_PREFIX(Color4x)
	.globl GL_PREFIX(DepthRangefOES) ; .set GL_PREFIX(DepthRangefOES), GL_PREFIX(DepthRangef)
	.globl GL_PREFIX(DepthRangexOES) ; .set GL_PREFIX(DepthRangexOES), GL_PREFIX(DepthRangex)
	.globl GL_PREFIX(FogxOES) ; .set GL_PREFIX(FogxOES), GL_PREFIX(Fogx)
	.globl GL_PREFIX(FogxvOES) ; .set GL_PREFIX(FogxvOES), GL_PREFIX(Fogxv)
	.globl GL_PREFIX(FrustumfOES) ; .set GL_PREFIX(FrustumfOES), GL_PREFIX(Frustumf)
	.globl GL_PREFIX(FrustumxOES) ; .set GL_PREFIX(FrustumxOES), GL_PREFIX(Frustumx)
	.globl GL_PREFIX(LightModelxOES) ; .set GL_PREFIX(LightModelxOES), GL_PREFIX(LightModelx)
	.globl GL_PREFIX(LightModelxvOES) ; .set GL_PREFIX(LightModelxvOES), GL_PREFIX(LightModelxv)
	.globl GL_PREFIX(LightxOES) ; .set GL_PREFIX(LightxOES), GL_PREFIX(Lightx)
	.globl GL_PREFIX(LightxvOES) ; .set GL_PREFIX(LightxvOES), GL_PREFIX(Lightxv)
	.globl GL_PREFIX(LineWidthxOES) ; .set GL_PREFIX(LineWidthxOES), GL_PREFIX(LineWidthx)
	.globl GL_PREFIX(LoadMatrixxOES) ; .set GL_PREFIX(LoadMatrixxOES), GL_PREFIX(LoadMatrixx)
	.globl GL_PREFIX(MaterialxOES) ; .set GL_PREFIX(MaterialxOES), GL_PREFIX(Materialx)
	.globl GL_PREFIX(MaterialxvOES) ; .set GL_PREFIX(MaterialxvOES), GL_PREFIX(Materialxv)
	.globl GL_PREFIX(MultMatrixxOES) ; .set GL_PREFIX(MultMatrixxOES), GL_PREFIX(MultMatrixx)
	.globl GL_PREFIX(MultiTexCoord4xOES) ; .set GL_PREFIX(MultiTexCoord4xOES), GL_PREFIX(MultiTexCoord4x)
	.globl GL_PREFIX(Normal3xOES) ; .set GL_PREFIX(Normal3xOES), GL_PREFIX(Normal3x)
	.globl GL_PREFIX(OrthofOES) ; .set GL_PREFIX(OrthofOES), GL_PREFIX(Orthof)
	.globl GL_PREFIX(OrthoxOES) ; .set GL_PREFIX(OrthoxOES), GL_PREFIX(Orthox)
	.globl GL_PREFIX(PointSizexOES) ; .set GL_PREFIX(PointSizexOES), GL_PREFIX(PointSizex)
	.globl GL_PREFIX(PolygonOffsetxOES) ; .set GL_PREFIX(PolygonOffsetxOES), GL_PREFIX(PolygonOffsetx)
	.globl GL_PREFIX(RotatexOES) ; .set GL_PREFIX(RotatexOES), GL_PREFIX(Rotatex)
	.globl GL_PREFIX(SampleCoveragexOES) ; .set GL_PREFIX(SampleCoveragexOES), GL_PREFIX(SampleCoveragex)
	.globl GL_PREFIX(ScalexOES) ; .set GL_PREFIX(ScalexOES), GL_PREFIX(Scalex)
	.globl GL_PREFIX(TexEnvxOES) ; .set GL_PREFIX(TexEnvxOES), GL_PREFIX(TexEnvx)
	.globl GL_PREFIX(TexEnvxvOES) ; .set GL_PREFIX(TexEnvxvOES), GL_PREFIX(TexEnvxv)
	.globl GL_PREFIX(TexParameterxOES) ; .set GL_PREFIX(TexParameterxOES), GL_PREFIX(TexParameterx)
	.globl GL_PREFIX(TranslatexOES) ; .set GL_PREFIX(TranslatexOES), GL_PREFIX(Translatex)
	.globl GL_PREFIX(ClipPlanefOES) ; .set GL_PREFIX(ClipPlanefOES), GL_PREFIX(ClipPlanef)
	.globl GL_PREFIX(ClipPlanexOES) ; .set GL_PREFIX(ClipPlanexOES), GL_PREFIX(ClipPlanex)
	.globl GL_PREFIX(GetClipPlanefOES) ; .set GL_PREFIX(GetClipPlanefOES), GL_PREFIX(GetClipPlanef)
	.globl GL_PREFIX(GetClipPlanexOES) ; .set GL_PREFIX(GetClipPlanexOES), GL_PREFIX(GetClipPlanex)
	.globl GL_PREFIX(GetFixedvOES) ; .set GL_PREFIX(GetFixedvOES), GL_PREFIX(GetFixedv)
	.globl GL_PREFIX(GetLightxvOES) ; .set GL_PREFIX(GetLightxvOES), GL_PREFIX(GetLightxv)
	.globl GL_PREFIX(GetMaterialxvOES) ; .set GL_PREFIX(GetMaterialxvOES), GL_PREFIX(GetMaterialxv)
	.globl GL_PREFIX(GetTexEnvxvOES) ; .set GL_PREFIX(GetTexEnvxvOES), GL_PREFIX(GetTexEnvxv)
	.globl GL_PREFIX(GetTexParameterxvOES) ; .set GL_PREFIX(GetTexParameterxvOES), GL_PREFIX(GetTexParameterxv)
	.globl GL_PREFIX(PointParameterxOES) ; .set GL_PREFIX(PointParameterxOES), GL_PREFIX(PointParameterx)
	.globl GL_PREFIX(PointParameterxvOES) ; .set GL_PREFIX(PointParameterxvOES), GL_PREFIX(PointParameterxv)
	.globl GL_PREFIX(TexParameterxvOES) ; .set GL_PREFIX(TexParameterxvOES), GL_PREFIX(TexParameterxv)

#if defined(GLX_USE_TLS) && defined(__linux__)
	.section ".note.ABI-tag", "a"
	.p2align 2
	.long	1f - 0f   /* name length */
	.long	3f - 2f   /* data length */
	.long	1         /* note length */
0:	.asciz "GNU"      /* vendor name */
1:	.p2align 2
2:	.long	0         /* note data: the ABI tag */
	.long	2,4,20    /* Minimum kernel version w/TLS */
3:	.p2align 2        /* pad out section */
#endif /* GLX_USE_TLS */

#if defined (__ELF__) && defined (__linux__)
	.section .note.GNU-stack,"",%progbits
#endif
