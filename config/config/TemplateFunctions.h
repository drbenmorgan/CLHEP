#include "CLHEP/config/defs.h"
#ifdef ENABLE_BACKWARDS_COMPATIBILITY
// -*- C++ -*-
// CLASSDOC OFF
// $Id: TemplateFunctions.h,v 1.1.2.2 2004/06/30 15:38:30 garren Exp $
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This file contains template definitions of some usefull functions.
//
// sqr was already replaced by sqrt in CLHEP 1.8 so we do not include it here
//
#ifndef HEP_TEMPLATEFUNCTIONS_H
#define HEP_TEMPLATEFUNCTIONS_H

#include <algorithm>  // for min() and max()
#include <cmath>      // double abs()
#include <stdlib.h>   // int abs()

using namespace std;

// Geant 4.6.2 still has at least one reference to sqr
#ifndef CLHEP_SQR_DEFINED
#define CLHEP_SQR_DEFINED
#ifdef sqr
#undef sqr
#endif
template <class T>
inline T sqr(const T& x) {
  return x*x;
}
#endif

#endif /* HEP_TEMPLATEFUNCTIONS_H */

#endif	// ENABLE_BACKWARDS_COMPATIBILITY
