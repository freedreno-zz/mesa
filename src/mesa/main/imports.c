/**
 * \file imports.c
 * Standard C library function wrappers.
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
 * \todo Functions still needed:
 * - scanf
 * - qsort
 * - rand and RAND_MAX
 */

/*
 * Mesa 3-D graphics library
 *
 * Copyright (C) 1999-2007  Brian Paul   All Rights Reserved.
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
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdarg.h>
#include "c99_math.h"
#include "util/rounding.h" /* for _mesa_roundeven */
#include "imports.h"
#include "context.h"
#include "mtypes.h"
#include "version.h"

#ifdef _GNU_SOURCE
#include <locale.h>
#ifdef __APPLE__
#include <xlocale.h>
#endif
#endif


#ifdef _WIN32
#define vsnprintf _vsnprintf
#elif defined(__IBMC__) || defined(__IBMCPP__)
extern int vsnprintf(char *str, size_t count, const char *fmt, va_list arg);
#endif

/**********************************************************************/
/** \name Memory */
/*@{*/

/**
 * Allocate aligned memory.
 *
 * \param bytes number of bytes to allocate.
 * \param alignment alignment (must be greater than zero).
 * 
 * Allocates extra memory to accommodate rounding up the address for
 * alignment and to record the real malloc address.
 *
 * \sa _mesa_align_free().
 */
void *
_mesa_align_malloc(size_t bytes, unsigned long alignment)
{
#if defined(HAVE_POSIX_MEMALIGN)
   void *mem;
   int err = posix_memalign(& mem, alignment, bytes);
   if (err)
      return NULL;
   return mem;
#elif defined(_WIN32) && defined(_MSC_VER)
   return _aligned_malloc(bytes, alignment);
#else
   uintptr_t ptr, buf;

   assert( alignment > 0 );

   ptr = (uintptr_t)malloc(bytes + alignment + sizeof(void *));
   if (!ptr)
      return NULL;

   buf = (ptr + alignment + sizeof(void *)) & ~(uintptr_t)(alignment - 1);
   *(uintptr_t *)(buf - sizeof(void *)) = ptr;

#ifdef DEBUG
   /* mark the non-aligned area */
   while ( ptr < buf - sizeof(void *) ) {
      *(unsigned long *)ptr = 0xcdcdcdcd;
      ptr += sizeof(unsigned long);
   }
#endif

   return (void *) buf;
#endif /* defined(HAVE_POSIX_MEMALIGN) */
}

/**
 * Same as _mesa_align_malloc(), but using calloc(1, ) instead of
 * malloc()
 */
void *
_mesa_align_calloc(size_t bytes, unsigned long alignment)
{
#if defined(HAVE_POSIX_MEMALIGN)
   void *mem;
   
   mem = _mesa_align_malloc(bytes, alignment);
   if (mem != NULL) {
      (void) memset(mem, 0, bytes);
   }

   return mem;
#elif defined(_WIN32) && defined(_MSC_VER)
   void *mem;

   mem = _aligned_malloc(bytes, alignment);
   if (mem != NULL) {
      (void) memset(mem, 0, bytes);
   }

   return mem;
#else
   uintptr_t ptr, buf;

   assert( alignment > 0 );

   ptr = (uintptr_t)calloc(1, bytes + alignment + sizeof(void *));
   if (!ptr)
      return NULL;

   buf = (ptr + alignment + sizeof(void *)) & ~(uintptr_t)(alignment - 1);
   *(uintptr_t *)(buf - sizeof(void *)) = ptr;

#ifdef DEBUG
   /* mark the non-aligned area */
   while ( ptr < buf - sizeof(void *) ) {
      *(unsigned long *)ptr = 0xcdcdcdcd;
      ptr += sizeof(unsigned long);
   }
#endif

   return (void *)buf;
#endif /* defined(HAVE_POSIX_MEMALIGN) */
}

/**
 * Free memory which was allocated with either _mesa_align_malloc()
 * or _mesa_align_calloc().
 * \param ptr pointer to the memory to be freed.
 * The actual address to free is stored in the word immediately before the
 * address the client sees.
 * Note that it is legal to pass NULL pointer to this function and will be
 * handled accordingly.
 */
void
_mesa_align_free(void *ptr)
{
#if defined(HAVE_POSIX_MEMALIGN)
   free(ptr);
#elif defined(_WIN32) && defined(_MSC_VER)
   _aligned_free(ptr);
#else
   if (ptr) {
      void **cubbyHole = (void **) ((char *) ptr - sizeof(void *));
      void *realAddr = *cubbyHole;
      free(realAddr);
   }
#endif /* defined(HAVE_POSIX_MEMALIGN) */
}

/**
 * Reallocate memory, with alignment.
 */
void *
_mesa_align_realloc(void *oldBuffer, size_t oldSize, size_t newSize,
                    unsigned long alignment)
{
#if defined(_WIN32) && defined(_MSC_VER)
   (void) oldSize;
   return _aligned_realloc(oldBuffer, newSize, alignment);
#else
   const size_t copySize = (oldSize < newSize) ? oldSize : newSize;
   void *newBuf = _mesa_align_malloc(newSize, alignment);
   if (newBuf && oldBuffer && copySize > 0) {
      memcpy(newBuf, oldBuffer, copySize);
   }

   _mesa_align_free(oldBuffer);
   return newBuf;
#endif
}

/*@}*/


/**********************************************************************/
/** \name Math */
/*@{*/


#ifndef HAVE___BUILTIN_FFS
/**
 * Find the first bit set in a word.
 */
int
ffs(int i)
{
   register int bit = 0;
   if (i != 0) {
      if ((i & 0xffff) == 0) {
         bit += 16;
         i >>= 16;
      }
      if ((i & 0xff) == 0) {
         bit += 8;
         i >>= 8;
      }
      if ((i & 0xf) == 0) {
         bit += 4;
         i >>= 4;
      }
      while ((i & 1) == 0) {
         bit++;
         i >>= 1;
      }
      bit++;
   }
   return bit;
}
#endif

#ifndef HAVE___BUILTIN_FFSLL
/**
 * Find position of first bit set in given value.
 * XXX Warning: this function can only be used on 64-bit systems!
 * \return  position of least-significant bit set, starting at 1, return zero
 *          if no bits set.
 */
int
ffsll(long long int val)
{
   int bit;

   assert(sizeof(val) == 8);

   bit = ffs((int) val);
   if (bit != 0)
      return bit;

   bit = ffs((int) (val >> 32));
   if (bit != 0)
      return 32 + bit;

   return 0;
}
#endif


#ifndef HAVE___BUILTIN_POPCOUNT
/**
 * Return number of bits set in given GLuint.
 */
unsigned int
_mesa_bitcount(unsigned int n)
{
   unsigned int bits;
   for (bits = 0; n > 0; n = n >> 1) {
      bits += (n & 1);
   }
   return bits;
}
#endif

#ifndef HAVE___BUILTIN_POPCOUNTLL
/**
 * Return number of bits set in given 64-bit uint.
 */
unsigned int
_mesa_bitcount_64(uint64_t n)
{
   unsigned int bits;
   for (bits = 0; n > 0; n = n >> 1) {
      bits += (n & 1);
   }
   return bits;
}
#endif

/*@}*/


/**********************************************************************/
/** \name String */
/*@{*/


/** Compute simple checksum/hash for a string */
unsigned int
_mesa_str_checksum(const char *str)
{
   /* This could probably be much better */
   unsigned int sum, i;
   const char *c;
   sum = i = 1;
   for (c = str; *c; c++, i++)
      sum += *c * (i % 100);
   return sum + i;
}


/*@}*/


/** Needed due to #ifdef's, above. */
int
_mesa_vsnprintf(char *str, size_t size, const char *fmt, va_list args)
{
   return vsnprintf( str, size, fmt, args);
}

/** Wrapper around vsnprintf() */
int
_mesa_snprintf( char *str, size_t size, const char *fmt, ... )
{
   int r;
   va_list args;
   va_start( args, fmt );  
   r = vsnprintf( str, size, fmt, args );
   va_end( args );
   return r;
}


