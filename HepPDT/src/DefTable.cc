// $Id: DefTable.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// DefTable.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include <iostream>

#include "CLHEP/HepPDT/DefTable.hh"

namespace HepPDT {

DefTable::DefTable( )
{ ; }

double DefTable::definition( std::string const & def )
{
    TempDefMap::iterator it = tempDefines.find( def );
    if( it != tempDefines.end() ) {
	return it->second;
    } else {
        // can neither build nor return a proper TempParticleData
	std::cout << "HepPDT::DefTable.definition: There is no entry for " 
                       << def << std::endl;
        return 0.0;
    }
}

bool DefTable::hasDefinition( std::string const & def ) const
{
    TempDefMap::const_iterator it = tempDefines.find( def );
    if( it != tempDefines.end() ) {
	return true;
    } else {
        return false;
    }
}

void DefTable::writeDefinitions(  ) const
{
  const_iterator  endit = end();
  const_iterator cit;
  for( cit=begin(); cit != endit; ++cit ) {
    std::cout << "Definition: " << cit->first << " = " << cit->second << std::endl;
  }
}

}  // namespace HepPDT
