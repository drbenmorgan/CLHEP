// $Id: buildTable.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// buildTable.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include <iostream>
#include <string>

#include "CLHEP/HepPDT/PDGtoQQTable.hh"

namespace HepPDT {
  
typedef std::map<std::string,PARTICLE> ParticleMap;

void PDGtoQQTable::buildTable( QQDecayTable & qd )
{
    // read particle map from QQDecayTable
    ParticleMap pm = qd.particleMap();
    ParticleMap::const_iterator cit;
    ParticleMap::const_iterator endit = pm.end();
    for( cit=pm.begin(); cit != endit; ++cit ) {
        PARTICLE p = cit->second;
	if( p.pdgid != 0 ) {
	    addPDTDefinition( p.pdgid, p.qqid );
	    addQQDefinition( p.qqid, p.pdgid );
	}
    }
    std::cout << "PDGtoQQTable::buildTable: found " << size() 
              << " QQ to PDG particle translations" << std::endl;
}

}  // namespace HepPDT
