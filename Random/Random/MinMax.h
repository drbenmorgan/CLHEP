// -*- C++ -*-
// CLASSDOC OFF
// $Id: MinMax.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This file contains template definitions of some usefull functions.
//
#ifndef HEP_MINMAX_H
#define HEP_MINMAX_H

#ifndef CLHEP_MAX_MIN_DEFINED
#define CLHEP_MAX_MIN_DEFINED
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

template <class T>
inline const T& max(const T& a, const T& b) {
  // Break this into two lines to avoid an incorrect warning with
  // Cfront-based compilers.
  const T& retval = a < b ? b : a;
  return retval;
}

template <class T>
inline const T& min(const T& a, const T& b) {
  // Break this into two lines to avoid an incorrect warning with
  // Cfront-based compilers.
  const T& retval = b < a ? b : a;
  return retval;
}
#endif

#endif /* HEP_MINMAX_H */
