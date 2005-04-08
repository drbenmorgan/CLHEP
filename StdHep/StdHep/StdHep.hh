// ----------------------------------------------------------------------
//
// StdHep.hh
// L. Garren
//
//  defines various free functions:
//       e.g., combine two events 
//  printVersion defined here
//
// ----------------------------------------------------------------------
#ifndef STDHEP_HH
#define STDHEP_HH

#include <iostream>

#include "CLHEP/StdHep/StdEvent.hh"

namespace StdHep {

/**
 * @author
 * @ingroup StdHep
 */

void printVersion( std::ostream & os = std::cout );

StdEvent * combineEvents( StdEvent * evt1, StdEvent * evt2, int evnum = 0 );

} // StdHep

#endif // STDHEP_HH
