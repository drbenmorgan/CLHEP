// ----------------------------------------------------------------------
//
// QQChannel.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include <sstream>
#include <algorithm>	// swap()

#include "CLHEP/HepPDT/defs.h"
#include "CLHEP/HepPDT/QQChannel.hh"

namespace HepPDT {

QQChannel::QQChannel(  )
: itsMatrixCode        ( "" ), 
  itsBranchingFraction ( 0 ), 
  itsSinPhi            ( 0 ), 
  itsMatrix            (  ),
  itsDaughters         (  ),
  itsHelicity          (  ),
  itsAngularHelicity   (  ),
  itsCPTag             ( false )
{ ; }

QQChannel::~QQChannel()
{ ; }

void  QQChannel::swap( QQChannel & other )
{
    std::swap(itsMatrixCode, other.itsMatrixCode); 
    std::swap(itsBranchingFraction, other.itsBranchingFraction); 
    std::swap(itsSinPhi, other.itsSinPhi); 
    std::swap(itsMatrix, other.itsMatrix); 
    itsDaughters.swap( other.itsDaughters ); 
    itsAngularHelicity.swap( other.itsAngularHelicity ); 
    itsHelicity.swap( other.itsHelicity ); 
    std::swap(itsCPTag, other.itsCPTag);
}

QQChannel::QQChannel( const QQChannel & orig )
: itsMatrixCode        ( orig.itsMatrixCode ), 
  itsBranchingFraction ( orig.itsBranchingFraction ), 
  itsSinPhi            ( orig.itsSinPhi ), 
  itsMatrix            ( orig.itsMatrix ),
  itsDaughters         ( orig.itsDaughters ),
  itsHelicity          ( orig.itsHelicity ),
  itsAngularHelicity   ( orig.itsAngularHelicity ),
  itsCPTag             ( orig.itsCPTag )
{ ; }

QQChannel & QQChannel::operator=( const QQChannel & rhs )
{ 
  QQChannel temp( rhs );
  swap( temp );
  return *this;
}

void  QQChannel::clear(  )
{
  itsMatrixCode = "";
  itsBranchingFraction = 0;
  itsSinPhi = 0;
  itsMatrix.a = 0;
  itsMatrix.b = 0;
  itsMatrix.c = 0;
  itsDaughters.clear();
  itsAngularHelicity.clear();
  itsHelicity.clear();
  itsCPTag = false;
}

void QQChannel::write( std::ostream & os ) const
{
    // intended for diagnostic use
    // incomplete
    os << "        " << itsBranchingFraction << " " <<  itsMatrixCode << " " 
       << itsSinPhi << " " << itsCPTag ;
    for( unsigned int i=0; i<itsDaughters.size(); ++i ){
        os << " " << itsDaughters[i] ;
    }
    os << std::endl;
}

}	// HepPDT
