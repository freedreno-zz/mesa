/**
 * \file glthread.h
 * \brief Thread support for GL dispatch.
 * 
 * \if subset
 * \brief (No-op.)
 *
 * \endif
 *
 * \author Initial version by John Stone (j.stone@acm.org) (johns@cs.umr.edu)
 * and Christoph Poliwoda (poliwoda@volumegraphics.com)
 * \author Revised by Keith Whitwell
 * \author Adapted for new gl dispatcher by Brian Paul
 *
 * \note
 * If this file is accidentally included by a non-threaded build,
 * it should not cause the build to fail, or otherwise cause problems.
 * In general, it should only be included when needed however.
 */

/*
 * Mesa 3-D graphics library
 * Version:  3.5
 *
 * Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.
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

/* $Id: glthread.h,v 1.11.6.3 2003/03/23 03:51:34 jrfonseca Exp $ */


#ifndef GLTHREAD_H
#define GLTHREAD_H

#undef PTHREADS
#undef XTHREADS

#if defined(PTHREADS) || defined(SOLARIS_THREADS) || defined(WIN32_THREADS) || defined(XTHREADS)
#define THREADS
#endif

#ifdef VMS
#include <GL/vms_x_fix.h>
#endif

/*
 * POSIX threads. This should be your choice in the Unix world
 * whenever possible.  When building with POSIX threads, be sure
 * to enable any compiler flags which will cause the MT-safe
 * libc (if one exists) to be used when linking, as well as any
 * header macros for MT-safe errno, etc.  For Solaris, this is the -mt
 * compiler flag.  On Solaris with gcc, use -D_REENTRANT to enable
 * proper compiling for MT-safe libc etc.
 */
#if defined(PTHREADS)
#include <pthread.h> /* POSIX threads headers */

typedef struct {
   pthread_key_t  key;
   int initMagic;
} _glthread_TSD;

typedef pthread_t _glthread_Thread;

typedef pthread_mutex_t _glthread_Mutex;

#define _glthread_DECLARE_STATIC_MUTEX(name) \
   static _glthread_Mutex name = PTHREAD_MUTEX_INITIALIZER

#define _glthread_INIT_MUTEX(name) \
   pthread_mutex_init(&(name), NULL)

#define _glthread_LOCK_MUTEX(name) \
   (void) pthread_mutex_lock(&(name))

#define _glthread_UNLOCK_MUTEX(name) \
   (void) pthread_mutex_unlock(&(name))

#endif /* PTHREADS */




/*
 * Solaris threads. Use only up to Solaris 2.4.
 * Solaris 2.5 and higher provide POSIX threads.
 * Be sure to compile with -mt on the Solaris compilers, or
 * use -D_REENTRANT if using gcc.
 */
#ifdef SOLARIS_THREADS
#include <thread.h>

typedef struct {
   thread_key_t key;
   mutex_t      keylock;
   int          initMagic;
} _glthread_TSD;

typedef thread_t _glthread_Thread;

typedef mutex_t _glthread_Mutex;

/* XXX need to really implement mutex-related macros */
#define _glthread_DECLARE_STATIC_MUTEX(name)  static _glthread_Mutex name = 0
#define _glthread_INIT_MUTEX(name)  (void) name
#define _glthread_LOCK_MUTEX(name)  (void) name
#define _glthread_UNLOCK_MUTEX(name)  (void) name

#endif /* SOLARIS_THREADS */




/*
 * Windows threads. Should work with Windows NT and 95.
 * IMPORTANT: Link with multithreaded runtime library when THREADS are
 * used!
 */
#ifdef WIN32_THREADS
#include <windows.h>

typedef struct {
   DWORD key;
   int   initMagic;
} _glthread_TSD;

typedef HANDLE _glthread_Thread;

typedef CRITICAL_SECTION _glthread_Mutex;

/* XXX need to really implement mutex-related macros */
#define _glthread_DECLARE_STATIC_MUTEX(name)  static _glthread_Mutex name = 0
#define _glthread_INIT_MUTEX(name)  (void) name
#define _glthread_LOCK_MUTEX(name)  (void) name
#define _glthread_UNLOCK_MUTEX(name)  (void) name

#endif /* WIN32_THREADS */




/*
 * XFree86 has its own thread wrapper, Xthreads.h
 * We wrap it again for GL.
 */
#ifdef XTHREADS
#include "Xthreads.h"

typedef struct {
   xthread_key_t key;
   int initMagic;
} _glthread_TSD;

typedef xthread_t _glthread_Thread;

typedef xmutex_rec _glthread_Mutex;

#ifdef XMUTEX_INITIALIZER
#define _glthread_DECLARE_STATIC_MUTEX(name) \
   static _glthread_Mutex name = XMUTEX_INITIALIZER
#else
#define _glthread_DECLARE_STATIC_MUTEX(name) \
   static _glthread_Mutex name
#endif

#define _glthread_INIT_MUTEX(name) \
   xmutex_init(&(name))

#define _glthread_LOCK_MUTEX(name) \
   (void) xmutex_lock(&(name))

#define _glthread_UNLOCK_MUTEX(name) \
   (void) xmutex_unlock(&(name))

#endif /* XTHREADS */



/*
 * BeOS threads. R5.x required.
 */
#ifdef BEOS_THREADS
#include <kernel/OS.h>
#include <support/TLS.h>

typedef struct {
   int32        key;
   int          initMagic;
} _glthread_TSD;

typedef thread_id _glthread_Thread;

/* Use Benaphore, aka speeder semaphore */
typedef struct {
    int32   lock;
    sem_id  sem;
} benaphore;
typedef benaphore _glthread_Mutex;

#define _glthread_DECLARE_STATIC_MUTEX(name)  static _glthread_Mutex name = { 0,
create_sem(0, #name"_benaphore") }
#define _glthread_INIT_MUTEX(name)    name.sem = create_sem(0, #name"_benaphore"), name.lock = 0
#define _glthread_LOCK_MUTEX(name)    if((atomic_add(&(name.lock), 1)) >= 1) acquire_sem(name.sem)
#define _glthread_UNLOCK_MUTEX(name)  if((atomic_add(&(name.lock), -1)) > 1) release_sem(name.sem)

#endif /* BEOS_THREADS */



#ifndef THREADS

/**
 * \name No thread support
 */
/*@{*/

/** 
 * \brief Thread-specific data area.
 *
 * Dummy type.
 */
typedef GLuint _glthread_TSD;

/** 
 * \brief Thread datatype
 *
 * Dummy type 
 */
typedef GLuint _glthread_Thread;

/** 
 * \brief 
 *
 * Dummy type Mutual exclusion lock
 */
typedef GLuint _glthread_Mutex;

/** 
 * \brief Declare a non-local mutex.
 *
 * No-op.
 */
#define _glthread_DECLARE_STATIC_MUTEX(name)  static _glthread_Mutex name = 0

/** 
 * \brief Initialize a mutex.
 *
 * No-op.
 */
#define _glthread_INIT_MUTEX(name)  (void) name

/** 
 * \brief Lock a mutex.
 *
 * No-op.
 */
#define _glthread_LOCK_MUTEX(name)  (void) name

/** 
 * \brief Unlock a mutex.
 *
 * No-op.
 */
#define _glthread_UNLOCK_MUTEX(name)  (void) name

/*@}*/

#endif /* THREADS */


/**
 * \name Platform independent thread specific data API.
 */
/*@{*/

/** \brief Get integer thread ID */
extern unsigned long
_glthread_GetID(void);

/** \brief Initialize thread-specific data */
extern void
_glthread_InitTSD(_glthread_TSD *);

/** \brief Get thread-specific data */
extern void *
_glthread_GetTSD(_glthread_TSD *);

/** \brief Set thread-specific data */
extern void
_glthread_SetTSD(_glthread_TSD *, void *);

/*@}*/


#endif /* THREADS_H */
