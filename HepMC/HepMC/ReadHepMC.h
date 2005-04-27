// ----------------------------------------------------------------------
//
// ReadHepMC.h
// Author: Lynn Garren
//
// read from an ascii file
// ----------------------------------------------------------------------
#ifndef READHEPMC_H
#define READHEPMC_H

#include <iostream>
#include <string>
#include <map>

#include "CLHEP/HepMC/GenEvent.h"

namespace HepMC  {

std::string readBlockType    ( std::istream & is );
bool        findBlockType    ( std::istream & is, std::string & type );
GenEvent *  readGenEvent     ( std::istream & is );
GenEvent *  findNextGenEvent ( std::istream & is );
std::string readComment      ( std::istream & is );

  namespace Detail {

     //std::istream & readComment( std::istream & is, std::string & comment );
     std::istream & fillEvent( std::istream & is, 
                               std::string & evline,
                               GenEvent * evt );
     void           parseEventLine( std::string & evline, 
                                    GenEvent * evt,
                                    int & nv, int & sv );
     void           parseVertexLine( std::string & evline, 
                                     GenVertex * v,
                                     int & numOrphan, int & numP );
     void           parseParticleLine( std::string & evline, 
                                       GenParticle * p,
                                       int & dv );

  }	// Detail

}	// HepMC

#endif // READHEPMC_H
