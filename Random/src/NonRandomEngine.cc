// $Id: NonRandomEngine.cc,v 1.3 2003/07/17 19:20:02 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                           Hep Random
//                        --- NonRandomEngine ---
//                   class implementation file
// -----------------------------------------------------------------------
// M. Fischler    - Created 9/30/99
//=========================================================================

#include "Random/defs.h"
#include "CLHEP/Random/NonRandomEngine.h"
#include <stdlib.h>

namespace CLHEP {

NonRandomEngine::NonRandomEngine() : nextHasBeenSet(false), 
				     sequenceHasBeenSet(false),
				     intervalHasBeenSet(false) { }

NonRandomEngine::~NonRandomEngine() { }


void NonRandomEngine::setNextRandom(double r) {
  nextRandom = r;
  nextHasBeenSet=true;
  return;
}

void NonRandomEngine::setRandomSequence(double* s, int n) {
  nSequence = n;
  sequence = s;
  sequenceHasBeenSet=true;
  nextHasBeenSet=false;
  return;
}

void NonRandomEngine::setRandomInterval(double x) {
  randomInterval = x;
  intervalHasBeenSet=true;
  return;
}

double NonRandomEngine::flat() {

  if (sequenceHasBeenSet) {
    nSequence--;
    if (nSequence<=0) sequenceHasBeenSet = false;
    return *sequence++;
  }

  if ( !nextHasBeenSet ) {
    std::cout 
	<< "Attempt to use NonRandomEngine without setting next random!\n";
    exit(1);
  }

  double a = nextRandom;
  nextHasBeenSet = false;

  if (intervalHasBeenSet) {
    nextRandom += randomInterval;
    if ( nextRandom >= 1 ) nextRandom -= 1.0;
    nextHasBeenSet = true;
  }

  return a;
}


void NonRandomEngine::flatArray(const int size, double* vect) {
  for (int i = 0; i < size; ++i) {
    vect[i] = flat();
  }
}

}  // namespace CLHEP

