// $Id: QQDecay.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// QQDecay.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include <algorithm>	// swap()

#include "CLHEP/HepPDT/QQDecay.hh"

namespace HepPDT {

QQDecay::QQDecay(  )
: itsStable  ( false ), 
  itsChannels(  )
{ ; }

QQDecay::~QQDecay()
{ ; }

void  QQDecay::swap( QQDecay & other )
{
    std::swap(itsStable, other.itsStable); 
    std::swap(itsChannels, other.itsChannels);
}

QQDecay::QQDecay( const QQDecay & orig )
: itsStable     ( orig.itsStable ), 
  itsChannels   ( orig.itsChannels )
{ ; }

QQDecay & QQDecay::operator=( const QQDecay & rhs )
{ 
  QQDecay temp( rhs );
  swap( temp );
  return *this;
}

}	// HepPDT
