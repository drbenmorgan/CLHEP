// -*- C++ -*-
// CLASSDOC OFF
// $Id: fortran.h,v 1.2 2003/08/13 20:00:14 garren Exp $
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of what might become CLHEP -
// a Class Library for High Energy Physics.
// 
// This file contains definitions of macros for declaring and using
// FORTRAN commonblocks and routines in C++ code. It is assumed that
// the default f77 compiler is used for the supported platforms (currently
// HP9000, apollo, decstation, NeXT (using f2c)). If f2c is used, the f2c.h
// file should be included befor this one. If the FORTRAN_PPU macro is
// defined to 1 before this file is included, an underscore will always be
// post-pended to any fortran name. If it is defined to 0, no underclore will
// be post-pended. If FORTRAN_PPU is not defined, an intelligent guess is
// performed in this file.
//
//.SS Usage:
//
// a fortran subroutine delcared as e.g.
//
// .ft B
//       SUBROUTINE GOGEN (U0,P0,NP,M,U,P)
//
// with
//
// .ft B 
//       REAL U0,P0(4),M(30),U(30),P(4,30)
// .fi
//       INTEGER NP(2)
// 
// should be declared as
//
// .ft B
//  extern "C" {
// .fi
//    extern void
// .fi
//    FORTRAN_ROUTINE(gogen)(float*,float[4],int[2],float[30],float[30][4]);
// .fi
//    }
//
// and called by
//
// .ft B
// FORTRAN_ROUTINE(gogen)(&U0, P0, NP, M, U, P1);
//
// a fortran common block declared as e.g.
//
// .ft B
//       COMMON /LUJETS/ N,K(4000,5),P(4000,5),V(4000,5)
//
// using normal implicit rules should be declared as
//
// .ft B
//  extern "C" {
// .fi
//    BEGIN_FORTRAN_COMMON(lujets)
// .fi
//      int   n;
// .fi
//      int   k[5][4000];
// .fi
//      float p[5][4000];
// .fi
//      float v[5][4000];
// .fi
//    END_FORTRAN_COMMON(lujets)
// .fi
//  }
//
// and accessed by eg.
//
// .ft B
//    FORTRAN_COMMON(lujets).k[2][FORTRAN_COMMON(lujets).n-4] = 2;
//
// Author: Leif Lonnblad
//
// fortran.h,v 1.2 1992/11/30 12:31:26 lonnblad Exp

#ifndef _FORTRAN_H_
#define _FORTRAN_H_

#include "CLHEP/Utilities/defs.h"

#ifdef FORTRAN_PPU
#define ADD_UNDERSCORE(name) name ## _
#else
#define ADD_UNDERSCORE(name) name
#endif

//#if defined(__apollo) && !defined(USING_F2C)
#ifdef __apollo
#ifndef USING_F2C
#define BEGIN_FORTRAN_COMMON(name) struct {

#define END_FORTRAN_COMMON(name) \
} ADD_UNDERSCORE(name) __attribute((__section(ADD_UNDERSCORE(name))));

#define FORTRAN_COMMON(name) ADD_UNDERSCORE(name)

#define FORTRAN_ROUTINE(name) ADD_UNDERSCORE(name)

#define FORTRAN_LOGICAL int
#else

#define BEGIN_FORTRAN_COMMON(name) extern struct {

#define END_FORTRAN_COMMON(name) } ADD_UNDERSCORE(name);

#define FORTRAN_COMMON(name) ADD_UNDERSCORE(name)

#define FORTRAN_ROUTINE(name) ADD_UNDERSCORE(name)

#define FORTRAN_LOGICAL long

#endif
#else

#define BEGIN_FORTRAN_COMMON(name) extern struct {

#define END_FORTRAN_COMMON(name) } ADD_UNDERSCORE(name);

#define FORTRAN_COMMON(name) ADD_UNDERSCORE(name)

#define FORTRAN_ROUTINE(name) ADD_UNDERSCORE(name)

#define FORTRAN_LOGICAL long

#endif

#endif // _FORTRAN_H_
