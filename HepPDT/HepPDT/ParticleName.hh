#ifndef PARTICLENAME_HH
#define PARTICLENAME_HH
// $Id: ParticleName.hh,v 1.2 2004/04/29 02:47:31 garren Exp $
// ----------------------------------------------------------------------
//
// ParticleName.hh
// Author: Lynn Garren and Walter Brown
//
//  Create a map that gives a standard name for each pre-defined 
//  particle ID number.  This map is initialized if and only if 
//  the public functions are called. Because the map is static, 
//  the initialization happens only once.
//
//
// ----------------------------------------------------------------------

#include <string>
#include <map>
#include <iostream>

namespace HepPDT {

// get a known HepPDT Particle name
std::string  particleName( const int );
// list all known names
void  listHepPDTParticleNames( std::ostream & os );
// verify that this number has a valid name
bool validParticleName( const int );
// access the ParticleNameMap for other purposes
typedef  std::map< int, std::string >  ParticleNameMap;
ParticleNameMap const &  getParticleNameMap();

}  // namespace HepPDT

#endif // PARTICLENAME_HH
