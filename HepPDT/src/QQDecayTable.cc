// $Id: QQDecayTable.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// QQDecayTable.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include <algorithm>	// swap()

#include "CLHEP/HepPDT/QQDecayTable.hh"

namespace HepPDT {

QQDecayTable::QQDecayTable(  )
: itsVersion    ( 0 ), 
  itsParticleMap(  ),
  itsQuarkMap   (  ),
  itsDecayMap   (  )
{ version(); }

QQDecayTable::QQDecayTable( std::istream & pdfile )
: itsVersion    ( 0 ), 
  itsParticleMap(  ),
  itsQuarkMap   (  ),
  itsDecayMap   (  )
{ 
    version();
    readQQstream( pdfile );
}

QQDecayTable::~QQDecayTable()
{ ; }

void  QQDecayTable::swap( QQDecayTable & other )
{
    std::swap(itsVersion, other.itsVersion); 
    itsParticleMap.swap( other.itsParticleMap ); 
    itsQuarkMap.swap( other.itsQuarkMap );
    std::swap(itsDecayMap, other.itsDecayMap);
}

QQDecayTable::QQDecayTable( const QQDecayTable & orig )
: itsVersion     ( orig.itsVersion ), 
  itsParticleMap ( orig.itsParticleMap ), 
  itsQuarkMap    ( orig.itsQuarkMap ),
  itsDecayMap    ( orig.itsDecayMap )
{ ; }

QQDecayTable & QQDecayTable::operator=( const QQDecayTable & rhs )
{ 
  QQDecayTable temp( rhs );
  swap( temp );
  return *this;
}

PARTICLE QQDecayTable::particle( const std::string & name )
{
    return itsParticleMap[name];
}

QQBAR    QQDecayTable::qqbar( const std::string & name )
{
    return itsQuarkMap[name];
}

QQDecay  QQDecayTable::decay( const std::string & name )
{
    return itsDecayMap[name];
}

}	// HepPDT
