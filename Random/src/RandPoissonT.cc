// $Id: RandPoissonT.cc,v 1.3 2003/07/25 20:59:21 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                         --- RandPoissonT ---
//                      class implementation file
// -----------------------------------------------------------------------

// =======================================================================
// M. Fischler    - Implemented new, much faster table-driven algorithm
//		    applicable for mu < 100 (Nov 1999), using these as
//		    implementation of RandPoisson.
// M. Fischler	  - Moved the table driven algorithms into RandPoissonT (here)
//		    1/26/00.
// =======================================================================

#include "Random/defs.h"
#include "CLHEP/Random/RandPoissonT.h"
#include "CLHEP/Random/RandPoissonQ.h"

//
// Constructors and destructors:
//

namespace CLHEP {

RandPoissonT::RandPoissonT(HepRandomEngine & anEngine, double m )
: RandPoisson(anEngine, m)
{}

RandPoissonT::RandPoissonT(HepRandomEngine * anEngine, double m )
: RandPoisson(anEngine, m)
{}

RandPoissonT::RandPoissonT(const RandPoissonT& right)
	: RandPoisson(right)
{}

RandPoissonT::~RandPoissonT() {
}

//
// fire, operator(), and shoot methods:
//

long RandPoissonT::shoot(double xm) {
  HepRandomEngine* e = HepRandom::getTheEngine();
  return shoot ( e, xm );
} // shoot()

double RandPoissonT::operator()() {
  return double( fire() );
}

double RandPoissonT::operator()( double mean ) {
  return double( fire( mean ) );
}

long RandPoissonT::fire(double mean) {
  return shoot (getLocalEngine(), mean);
}

long RandPoissonT::fire() {

  if ( defaultMean <= RandPoissonQ::tableBoundary() ) {
    return RandPoissonQ::shoot ( getLocalEngine(), defaultMean );
  } else {
    return RandPoisson::shoot(getLocalEngine(), defaultMean);
  }

} // fire()

long RandPoissonT::shoot(HepRandomEngine* anEngine, double mean) {

  if ( mean <= RandPoissonQ::tableBoundary() ) {
    return RandPoissonQ::shoot ( anEngine, mean );
  } else {
    return RandPoisson::shoot( anEngine, mean );
  }

} // shoot (anEngine, mean)

void RandPoissonT::shootArray(const int size, long* vect, double m) {
   int i;
   for (i=0; i<size; ++i)
     vect[i] = shoot(m);
}

void RandPoissonT::fireArray(const int size, long* vect, double m) {
   int i;
   for (i=0; i<size; ++i) {
     vect[i] = fire( m );
   }
}


}  // namespace CLHEP
