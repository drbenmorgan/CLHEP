// $Id: QQDecayTable.cc,v 1.1.1.1.2.1 2005/02/04 00:24:43 garren Exp $
// ----------------------------------------------------------------------
//
// QQDecayTable.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
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

void QQDecayTable::writeTable( std::ostream & os ) const
{
    // intended for diagnostic use
    os <<  std::endl;
    os << "        QQ Decay Table" << std::endl;
    os << "decay.dec version: " << itsVersion << std::endl;
    QuarkMap::const_iterator qit;
    for( qit=itsQuarkMap.begin(); qit !=itsQuarkMap.end(); ++qit ) {
        std::string nm = qit->first;
        QQBAR q = qit->second;
	os << "  " << nm << " " << q.qqid <<  std::endl;
    }
    ParticleMap::const_iterator cit;
    DecayMap::const_iterator dit;
    for( cit=itsParticleMap.begin(); cit !=itsParticleMap.end(); ++cit ) {
        std::string nm = cit->first;
        PARTICLE p = cit->second;
	os << "  " << nm << " " << p.qqid << " " << p.stableid << " " 
	   << p.pdgid << " " <<  p.mass << " " <<  p.charge << " " 
	   << p.spin << " " << p.lifetime << " " <<  p.width << " " 
	   << p.minMass << " " <<  p.maxMass << " " 
	   << p.parity << " " <<  p.cparity << std::endl;
	dit = itsDecayMap.find( nm );
	if( dit != itsDecayMap.end() ) {
	    QQDecay d = dit->second;
	    d.write( os );
	}
    }
    os <<  std::endl;
}

}	// HepPDT
