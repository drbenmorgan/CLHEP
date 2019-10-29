// ----------------------------------------------------------------------
//
//  ZMuseCount.cc - utility class for use in reference-counting
//
//
//  History:
//    19-Sep-1997  WEB  Design stolen, and code adapted, from pp 70-73 of
//      Koenig & Moo: "Ruminations on C++" (1996)
//
// ----------------------------------------------------------------------


#ifndef ZMUSECOUNT_H
  #include "CLHEP/RefCount/ZMuseCount.h"
  #include "CLHEP/RefCount/ZMuseCount.icc"
#endif


bool ZMuseCount::makeonly()  {

  bool result = ( ! only() );

  if ( result )  {
    --*p;
    p = new int(1);
  }

  return result;

}  // makeonly()


bool ZMuseCount::reattach( const ZMuseCount & u )  {

  ++*u.p;

  bool result = ( --*p == 0 );
  if ( result )
    delete p;

  p = u.p;
  return result;

}  // reattach()
