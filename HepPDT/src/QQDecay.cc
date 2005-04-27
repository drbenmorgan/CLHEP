// ----------------------------------------------------------------------
//
// QQDecay.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/defs.h"
#include <sstream>
#include <algorithm>	// swap()

#include "CLHEP/HepPDT/QQDecay.hh"
#include "CLHEP/HepPDT/QQChannel.hh"

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

void QQDecay::write( std::ostream & os ) const
{
    // intended for diagnostic use
    if ( itsStable ) {
        os << "        particle is stable" << std::endl;
    } else {
	for( unsigned int i=0; i<itsChannels.size(); ++i ) {
	    itsChannels[i].write( os );
	}
    }
}

}	// HepPDT
