// -*- C++ -*-
// $Id: RandomFunc.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -----------------------------------------------------------------------
//                             HEP RandomFunc
//                      get proper system headers for drand, etc.
// -----------------------------------------------------------------------

#ifndef RANDOMFUNC_H
#define RANDOMFUNC_H

// Those function are available on all unix platform but their
// prototypes are not included in stdlib when strict ANSI flag is set.
// Such behaviour was noticed with "KCC --strict" and "g++ -ansi".
//
// To provide declaration of those functions on Linux g++ should be used
// with -D_GNU_SOURCE. Similar options for non-Linux plaforms are: 
// _HPUX_SOURCE, _IRIX_SOURCE, but we prefer just explicitely declare
// the functions on those platforms.
//
// drand48() extracted from GNU C Library 2.1.3 is used on Windows NT
// and Macintosh (see drand48.src)
  
#if !defined(__GNUC__)
extern "C" {
  extern double	drand48(void);
  extern void	srand48(long);
  extern unsigned short * seed48(unsigned short int [3]);
}
#else
#include <stdlib.h>
#endif

#ifdef WIN32
#include "drand48.src"
#endif  /* WIN32 */

#ifdef __APPLE__ 
#include "drand48.src"
#endif  /* __APPLE__ */

#endif 	// RANDOMFUNC_H
