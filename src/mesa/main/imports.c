/**
 * \file imports.c
 * \brief Standard C library function wrappers.
 * 
 * Imports are services which the device driver or window system or
 * operating system provides to the core renderer.  The core renderer (Mesa)
 * will call these functions in order to do memory allocation, simple I/O,
 * etc.
 *
 * Some drivers will want to override/replace this file with something
 * specialized, but that'll be rare.
 *
 * Eventually, I want to move roll the glheader.h file into this.
 *
 * The OpenGL SI's __GLimports structure allows per-context specification of
 * replacements for the standard C lib functions.  In practice that's probably
 * never needed; compile-time replacements are far more likely.
 *
 * The _mesa_*() functions defined here don't in general take a context
 * parameter.  I guess we can change that someday, if need be.
 * So for now, the __GLimports stuff really isn't used.
 */

/*
 * Mesa 3-D graphics library
 * Version:  5.0
 *
 * Copyright (C) 1999-2002  Brian Paul   All Rights Reserved.
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

/* $Id: imports.c,v 1.25.4.2 2003/03/20 12:56:57 jrfonseca Exp $ */


#include "glheader.h"
#include "mtypes.h"
#include "context.h"
#include "imports.h"


#define MAXSTRING 4000  /* for vsnprintf() */

#ifdef WIN32
#define vsnprintf _vsnprintf
#endif


/**********************************************************************/
/** \name Wrappers for standard C library functions
 *
 * Functions still needed:
 * - scanf
 * - qsort
 * - bsearch
 * - rand and RAND_MAX
 *
 * \note When compiled into a XFree86 module these functions wrap around
 * XFree86 own wrappers.
 */
/**********************************************************************/
/*@{*/

/** \brief Wrapper around either malloc() or xf86malloc() */
void *
_mesa_malloc(size_t bytes)
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86malloc(bytes);
#else
   return malloc(bytes);
#endif
}

/** \brief Wrapper around either calloc() or xf86calloc() */
void *
_mesa_calloc(size_t bytes)
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86calloc(1, bytes);
#else
   return calloc(1, bytes);
#endif
}

/** \brief Wrapper around either free() or xf86free() */
void
_mesa_free(void *ptr)
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   xf86free(ptr);
#else
   free(ptr);
#endif
}

/**
 * \brief Allocate aligned memory.
 *
 * \param bytes number of bytes to allocate.
 * \param alignment alignment (must be greater than zero).
 * 
 * Allocates extra memory to accomodate rounding up the address for
 * alignment and to record the real malloc address.
 *
 * \sa _mesa_align_free().
 */
void *
_mesa_align_malloc(size_t bytes, unsigned long alignment)
{
   unsigned long ptr, buf;

   ASSERT( alignment > 0 );

   ptr = (unsigned long) _mesa_malloc(bytes + alignment + sizeof(void *));
   if (!ptr)
      return NULL;

   buf = (ptr + alignment + sizeof(void *)) & ~(unsigned long)(alignment - 1);
   *(unsigned long *)(buf - sizeof(void *)) = ptr;

#ifdef DEBUG
   /* mark the non-aligned area */
   while ( ptr < buf - sizeof(void *) ) {
      *(unsigned long *)ptr = 0xcdcdcdcd;
      ptr += sizeof(unsigned long);
   }
#endif

   return (void *) buf;
}

/** \brief Same as _mesa_align_malloc(), but using _mesa_calloc() instead of
 * _mesa_malloc() */
void *
_mesa_align_calloc(size_t bytes, unsigned long alignment)
{
   unsigned long ptr, buf;

   ASSERT( alignment > 0 );

   ptr = (unsigned long) _mesa_calloc(bytes + alignment + sizeof(void *));
   if (!ptr)
      return NULL;

   buf = (ptr + alignment + sizeof(void *)) & ~(unsigned long)(alignment - 1);
   *(unsigned long *)(buf - sizeof(void *)) = ptr;

#ifdef DEBUG
   /* mark the non-aligned area */
   while ( ptr < buf - sizeof(void *) ) {
      *(unsigned long *)ptr = 0xcdcdcdcd;
      ptr += sizeof(unsigned long);
   }
#endif

   return (void *)buf;
}

/**
 * \brief Free memory allocated with _mesa_align_malloc() or _mesa_align_calloc().
 *
 * \param ptr pointer to the memory to be freed.
 * 
 * The actual address to free is stored in the word immediately before the
 * address the client sees.
 */
void
_mesa_align_free(void *ptr)
{
#if 0
   _mesa_free( (void *)(*(unsigned long *)((unsigned long)ptr - sizeof(void *))) );
#else
   void **cubbyHole = (void **) ((char *) ptr - sizeof(void *));
   void *realAddr = *cubbyHole;
   _mesa_free(realAddr);
#endif
}

/** \brief Wrapper around either memcpy() or xf86memcpy() */
void *
_mesa_memcpy(void *dest, const void *src, size_t n)
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86memcpy(dest, src, n);
#elif defined(SUNOS4)
   return memcpy((char *) dest, (char *) src, (int) n);
#else
   return memcpy(dest, src, n);
#endif
}

/** \brief Wrapper around either memset() or xf86memset() */
void
_mesa_memset( void *dst, int val, size_t n )
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   xf86memset( dst, val, n );
#elif defined(SUNOS4)
   memset( (char *) dst, (int) val, (int) n );
#else
   memset(dst, val, n);
#endif
}

/** \brief Fill memory with a constant 16bit word.
 *
 * \param dst destination pointer.
 * \param val value.
 * \param n number of words.
 */
void
_mesa_memset16( unsigned short *dst, unsigned short val, size_t n )
{
   while (n-- > 0)
      *dst++ = val;
}

/** \brief Wrapper around either memcpy() or xf86memcpy() or bzero() */
void
_mesa_bzero( void *dst, size_t n )
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   xf86memset( dst, 0, n );
#elif defined(__FreeBSD__)
   bzero( dst, n );
#else
   memset( dst, 0, n );
#endif
}

/** \brief Wrapper around either sin() or xf86sin() */
double
_mesa_sin(double a)
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86sin(a);
#else
   return sin(a);
#endif
}

/** \brief Wrapper around either cos() or xf86cos() */
double
_mesa_cos(double a)
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86cos(a);
#else
   return cos(a);
#endif
}

/** \brief Wrapper around either sqrt() or xf86sqrt() */
double
_mesa_sqrt(double x)
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86sqrt(x);
#else
   return sqrt(x);
#endif
}

/** \brief Wrapper around either pow() or xf86pow() */
double
_mesa_pow(double x, double y)
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86pow(x, y);
#else
   return pow(x, y);
#endif
}

/** \brief Wrapper around either () or xf86() */
char *
_mesa_getenv( const char *var )
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86getenv(var);
#else
   return getenv(var);
#endif
}

/** \brief Wrapper around either strstr() or xf86strstr() */
char *
_mesa_strstr( const char *haystack, const char *needle )
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86strstr(haystack, needle);
#else
   return strstr(haystack, needle);
#endif
}

/** \brief Wrapper around either strncat() or xf86strncat() */
char *
_mesa_strncat( char *dest, const char *src, size_t n )
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86strncat(dest, src, n);
#else
   return strncat(dest, src, n);
#endif
}

/** \brief Wrapper around either strcpy() or xf86strcpy() */
char *
_mesa_strcpy( char *dest, const char *src )
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86strcpy(dest, src);
#else
   return strcpy(dest, src);
#endif
}

/** \brief Wrapper around either strncpy() or xf86strncpy() */
char *
_mesa_strncpy( char *dest, const char *src, size_t n )
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86strncpy(dest, src, n);
#else
   return strncpy(dest, src, n);
#endif
}

/** \brief Wrapper around either strlen() or xf86strlen() */
size_t
_mesa_strlen( const char *s )
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86strlen(s);
#else
   return strlen(s);
#endif
}

/** \brief Wrapper around either strcmp() or xf86strcmp() */
int
_mesa_strcmp( const char *s1, const char *s2 )
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86strcmp(s1, s2);
#else
   return strcmp(s1, s2);
#endif
}

/** \brief Wrapper around either strncmp() or xf86strncmp() */
int
_mesa_strncmp( const char *s1, const char *s2, size_t n )
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86strncmp(s1, s2, n);
#else
   return strncmp(s1, s2, n);
#endif
}

/** \brief Wrapper around either atoi() or xf86atoi() */
int
_mesa_atoi(const char *s)
{
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86atoi(s);
#else
   return atoi(s);
#endif
}

/** \brief Wrapper around either vsprintf() or xf86vsprintf() */
int
_mesa_sprintf( char *str, const char *fmt, ... )
{
   int r;
   va_list args;
   va_start( args, fmt );  
   va_end( args );
#if defined(XFree86LOADER) && defined(IN_MODULE)
   r = xf86vsprintf( str, fmt, args );
#else
   r = vsprintf( str, fmt, args );
#endif
   return r;
}

/** \brief Wrapper around either printf() or xf86printf(), using vsprintf() for
 * the formatting. */
void
_mesa_printf( const char *fmtString, ... )
{
   char s[MAXSTRING];
   va_list args;
   va_start( args, fmtString );  
   vsnprintf(s, MAXSTRING, fmtString, args);
   va_end( args );
#if defined(XFree86LOADER) && defined(IN_MODULE)
   xf86printf("%s", s);
#else
   printf("%s", s);
#endif
}

/**
 * \brief Display a warning.
 *
 * \param ctx GL context.
 * \param fmtString printf() alike format string.
 * 
 * If debugging is enabled (either at compile-time via the DEBUG macro, or
 * run-time via the MESA_DEBUG environment variable), prints the warning to
 * stderr, either via fprintf() or xf86printf().
 */
void
_mesa_warning( GLcontext *ctx, const char *fmtString, ... )
{
   GLboolean debug;
   char str[MAXSTRING];
   va_list args;
   (void) ctx;
   va_start( args, fmtString );  
   (void) vsnprintf( str, MAXSTRING, fmtString, args );
   va_end( args );
#ifdef DEBUG
   debug = GL_TRUE; /* always print warning */
#else
   debug = _mesa_getenv("MESA_DEBUG") ? GL_TRUE : GL_FALSE;
#endif
   if (debug) {
#if defined(XFree86LOADER) && defined(IN_MODULE)
      xf86fprintf(stderr, "Mesa warning: %s\n", str);
#else
      fprintf(stderr, "Mesa warning: %s\n", str);
#endif
   }
}

/**
 * \brief This function is called when the Mesa user has stumbled into a code
 * path which may not be implemented fully or correctly.
 *
 * \param ctx GL context.
 * \param s problem description string.
 *
 * Prints the message to stderr, either via fprintf() or xf86fprintf().
 */
void
_mesa_problem( const GLcontext *ctx, const char *s )
{
   (void) ctx;
#if defined(XFree86LOADER) && defined(IN_MODULE)
   xf86fprintf(stderr, "Mesa implementation error: %s\n", s);
   xf86fprintf(stderr, "Please report to the DRI project at dri.sourceforge.net\n");
#else
   fprintf(stderr, "Mesa implementation error: %s\n", s);
   fprintf(stderr, "Please report to the Mesa bug database at www.mesa3d.org\n" );
#endif
}

/**
 * \brief Display an error message.
 *
 * If in debug mode, print error message.
 * Also, record the error code by calling _mesa_record_error().
 * 
 * \param ctx the GL context.
 * \param error the error value.
 * \param fmtString printf() style format string, followed by optional args
 *         
 * If debugging is enabled (either at compile-time via the DEBUG macro, or
 * run-time via the MESA_DEBUG environment variable), interperts the error code and 
 * prints the error message via _mesa_debug().
 */
void
_mesa_error( GLcontext *ctx, GLenum error, const char *fmtString, ... )
{
   const char *debugEnv;
   GLboolean debug;

   debugEnv = _mesa_getenv("MESA_DEBUG");

#ifdef DEBUG
   if (debugEnv && _mesa_strstr(debugEnv, "silent"))
      debug = GL_FALSE;
   else
      debug = GL_TRUE;
#else
   if (debugEnv)
      debug = GL_TRUE;
   else
      debug = GL_FALSE;
#endif

   if (debug) {
      va_list args;
      char where[MAXSTRING];
      const char *errstr;

      va_start( args, fmtString );  
      vsnprintf( where, MAXSTRING, fmtString, args );
      va_end( args );

      switch (error) {
	 case GL_NO_ERROR:
	    errstr = "GL_NO_ERROR";
	    break;
	 case GL_INVALID_VALUE:
	    errstr = "GL_INVALID_VALUE";
	    break;
	 case GL_INVALID_ENUM:
	    errstr = "GL_INVALID_ENUM";
	    break;
	 case GL_INVALID_OPERATION:
	    errstr = "GL_INVALID_OPERATION";
	    break;
	 case GL_STACK_OVERFLOW:
	    errstr = "GL_STACK_OVERFLOW";
	    break;
	 case GL_STACK_UNDERFLOW:
	    errstr = "GL_STACK_UNDERFLOW";
	    break;
	 case GL_OUT_OF_MEMORY:
	    errstr = "GL_OUT_OF_MEMORY";
	    break;
         case GL_TABLE_TOO_LARGE:
            errstr = "GL_TABLE_TOO_LARGE";
            break;
	 default:
	    errstr = "unknown";
	    break;
      }
      _mesa_debug(ctx, "Mesa user error: %s in %s\n", errstr, where);
   }

   _mesa_record_error(ctx, error);
}  

/**
 * \brief Report debug information.
 * 
 * \param ctx GL context.
 * \param fmtString printf() alike format string.
 * 
 * Prints the message to stderr, either via fprintf() or xf86printf().
 */
void
_mesa_debug( const GLcontext *ctx, const char *fmtString, ... )
{
   char s[MAXSTRING];
   va_list args;
   va_start(args, fmtString);
   vsnprintf(s, MAXSTRING, fmtString, args);
   va_end(args);
#if defined(XFree86LOADER) && defined(IN_MODULE)
   xf86fprintf(stderr, "Mesa: %s", s);
#else
   fprintf(stderr, "Mesa: %s", s);
#endif
}

/*@{*/


/**********************************************************************/
/** \name Default Imports Wrapper                                     */
/**********************************************************************/
/*@{*/

/** \brief Wrapper around _mesa_malloc() */
static void *
default_malloc(__GLcontext *gc, size_t size)
{
   (void) gc;
   return _mesa_malloc(size);
}

/** \brief Wrapper around _mesa_malloc() */
static void *
default_calloc(__GLcontext *gc, size_t numElem, size_t elemSize)
{
   (void) gc;
   return _mesa_calloc(numElem * elemSize);
}

/** \brief Wrapper around either realloc() or xf86realloc() */
static void *
default_realloc(__GLcontext *gc, void *oldAddr, size_t newSize)
{
   (void) gc;
#if defined(XFree86LOADER) && defined(IN_MODULE)
   return xf86realloc(oldAddr, newSize);
#else
   return realloc(oldAddr, newSize);
#endif
}

/** \brief Wrapper around _mesa_free() */
static void
default_free(__GLcontext *gc, void *addr)
{
   (void) gc;
   _mesa_free(addr);
}

/** \brief Wrapper around _mesa_getenv() */
static char * CAPI
default_getenv( __GLcontext *gc, const char *var )
{
   (void) gc;
   return _mesa_getenv(var);
}

/** \brief Wrapper around _mesa_warning() */
static void
default_warning(__GLcontext *gc, char *str)
{
   _mesa_warning(gc, str);
}

/** \brief Wrapper around _mesa_problem() */
static void
default_fatal(__GLcontext *gc, char *str)
{
   _mesa_problem(gc, str);
   abort();
}

/** \brief Wrapper around atoi() */
static int CAPI
default_atoi(__GLcontext *gc, const char *str)
{
   (void) gc;
   return atoi(str);
}

/** \brief Wrapper around vsprintf() */
static int CAPI
default_sprintf(__GLcontext *gc, char *str, const char *fmt, ...)
{
   int r;
   va_list args;
   va_start( args, fmt );  
   r = vsprintf( str, fmt, args );
   va_end( args );
   return r;
}

/** \brief Wrapper around fopen() */
static void * CAPI
default_fopen(__GLcontext *gc, const char *path, const char *mode)
{
   return fopen(path, mode);
}

/** \brief Wrapper around fclose() */
static int CAPI
default_fclose(__GLcontext *gc, void *stream)
{
   return fclose((FILE *) stream);
}

/** \brief Wrapper around vfprintf() */
static int CAPI
default_fprintf(__GLcontext *gc, void *stream, const char *fmt, ...)
{
   int r;
   va_list args;
   va_start( args, fmt );  
   r = vfprintf( (FILE *) stream, fmt, args );
   va_end( args );
   return r;
}

/**
 * \todo this really is driver-specific and can't be here 
 */
static __GLdrawablePrivate *
default_GetDrawablePrivate(__GLcontext *gc)
{
   return NULL;
}

/*@}*/


/**
 * \brief Initialize a __GLimports object to point to the functions in this
 * file.  
 *
 * This is to be called from device drivers.
 * 
 * \param imports the object to initialize.
 * \param driverCtx pointer to device driver-specific data.
 */
void
_mesa_init_default_imports(__GLimports *imports, void *driverCtx)
{
   imports->malloc = default_malloc;
   imports->calloc = default_calloc;
   imports->realloc = default_realloc;
   imports->free = default_free;
   imports->warning = default_warning;
   imports->fatal = default_fatal;
   imports->getenv = default_getenv; /* not used for now */
   imports->atoi = default_atoi;
   imports->sprintf = default_sprintf;
   imports->fopen = default_fopen;
   imports->fclose = default_fclose;
   imports->fprintf = default_fprintf;
   imports->getDrawablePrivate = default_GetDrawablePrivate;
   imports->other = driverCtx;
}
