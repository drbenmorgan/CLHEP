// $Id: WriteHepMC.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// WriteHepMC.h
// Author: Lynn Garren
//
// write to an ostream in ascii format
// ----------------------------------------------------------------------
#ifndef WRITEHEPMC_H
#define WRITEHEPMC_H

#include <iostream>
#include <string>

#include "CLHEP/HepMC/GenEvent.h"

namespace HepMC  {

std::ostream & writeComment( std::ostream & os, std::string const comment );
std::ostream & writeLegend( std::ostream & os );
std::ostream & flushOutput( std::ostream & os );
std::ostream & writeGenEvent( std::ostream & os, GenEvent const * evt );
std::ostream & operator << ( std::ostream & os, GenEvent const * evt );

  namespace Detail {

     std::ostream & writeVertex( std::ostream & os, GenVertex const * );
     std::ostream & writeParticle( std::ostream & os, GenParticle const * p );
     std::ostream & output( std::ostream & os, const double& d );

  }	// Detail

}	// HepMC

#endif // WRITEHEPMC_H

