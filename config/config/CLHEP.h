// -*- C++ -*-
// $Id: CLHEP.h,v 1.1.2.3 2005/11/17 23:48:25 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This file contains definitions of some usefull utilities and macros.
//
#ifndef _CLHEP_H_
#define _CLHEP_H_

#include <stdlib.h>
#include <limits.h>
#include <math.h>

#include "CLHEP/config/defs.h"

/// as of CLHEP 1.8, these are unnecessary
#define FORTRAN_PPU 1
#define HEP_USE_STD_STL 1
#define HEP_USE_STD 1
#define HEP_HAVE_IOSFWD 1
#define HepSTL std
#define HepStd std

// names have been changed to protect the innocent
// These will be unneccessary after CLHEP 1.9 since gcc 2.95.2
// will no longer be supported
#define HEP_HAVE_SSTREAM
#ifdef HAVE_IOS_BASE
#define HEP_USE_IOS_BASE
#endif

// CLASSDOC OFF
// **** You should probably not touch anything below this line: ****

typedef double HepDouble;
typedef int    HepInt;
typedef float  HepFloat;
typedef bool   HepBoolean;

#ifdef HEP_SHORT_NAMES
typedef HepBoolean Boolean;
#endif

// use the pi mass information in Units/PhysicalConstants.h instead
#ifndef M_PI_2
#define M_PI_2	1.57079632679489661923
#endif

#ifndef M_PI
#define M_PI	3.14159265358979323846
#endif

#ifndef M_2PI
#define M_2PI   6.28318530717958647692
#endif

#ifdef HEP_DEBUG_INLINE
#define HEP_NO_INLINE_IN_DECLARATION
#endif

#ifdef HEP_NO_INLINE_IN_DECLARATION
#define HEP_NO_INLINE_IN_TEMPLATE_DECLARATION
#endif

// Default to generate random matrix
//
#ifndef HEP_USE_RANDOM
#define HEP_USE_RANDOM
#endif

// Default to have assigment from three vector and rotation to matrix
//
#ifndef HEP_USE_VECTOR_MODULE
#define HEP_USE_VECTOR_MODULE
#endif

// GNU g++ compiler can optimize when returning an object.
// However g++ on HP cannot deal with this.
//
#undef HEP_GNU_OPTIMIZED_RETURN


#endif /* _CLHEP_H_ */

