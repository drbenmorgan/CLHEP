#ifndef ZMHANDLETO_H
#define ZMHANDLETO_H


// ----------------------------------------------------------------------
//
// ZMhandleTo.h - generic handle class for objects that need to be
//   reference-counted
//
// History:
//   19-Sep-1997  WEB  Design stolen, and code adapted, from
//     Stroustrup: "The C++ Programming Language, 3rd edition" (1997), p 783
//     Koenig & Moo: "Ruminations on C++" (1996), ch 7
//
// ----------------------------------------------------------------------


#ifndef ZMUSECOUNT_H
#include "CLHEP/RefCount/ZMuseCount.h"
#endif


template< class T >
class ZMhandleTo  {

public:

  ZMhandleTo();
  ZMhandleTo( const ZMhandleTo & h );
  ~ZMhandleTo();

  ZMhandleTo & operator=( const ZMhandleTo & rhs );

protected:
  ZMhandleTo( const T & t );
  ZMhandleTo( const T * t );

  ZMuseCount u_;
  T *        rep_;


};  // ZMhandleTo<>


#include "CLHEP/RefCount/ZMhandleTo.icc"


#endif  // ZMHANDLETO_H
