// $Id: RandExponential.cc,v 1.2 2003/07/17 19:20:02 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                       --- RandExponential ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// Gabriele Cosmo - Created: 17th May 1996
//                - Added methods to shoot arrays: 28th July 1997
// J.Marraffino   - Added default mean as attribute and
//                  operator() with mean: 16th Feb 1998
// =======================================================================

#include "CLHEP/Random/RandExponential.h"

namespace CLHEP {

RandExponential::~RandExponential() {
  if ( deleteEngine ) delete localEngine;
}

RandExponential::RandExponential(const RandExponential& right)
 : defaultMean(right.defaultMean)
{;}

double RandExponential::operator()() {
  return fire( defaultMean );
}

double RandExponential::operator()( double mean ) {
  return fire( mean );
}

double RandExponential::shoot() {
  return -log(HepRandom::getTheEngine()->flat());
}

double RandExponential::shoot(double mean) {
  return -log(HepRandom::getTheEngine()->flat())*mean;
}

void RandExponential::shootArray( const int size, double* vect,
                                  double mean )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(mean);
}

void RandExponential::shootArray(HepRandomEngine* anEngine, const int size,
                                   double* vect, double mean )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(anEngine, mean);
}

void RandExponential::fireArray( const int size, double* vect)
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire( defaultMean );
}

void RandExponential::fireArray( const int size, double* vect,
                                 double mean )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire( mean );
}

}  // namespace CLHEP
