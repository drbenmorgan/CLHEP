// $Id: RandExponential.cc,v 1.4.2.1 2004/12/17 20:19:38 fischler Exp $
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
// M Fischler      - put and get to/from streams 12/15/04
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandExponential.h"

namespace CLHEP {

std::string RandExponential::name() const {return "RandExponential";}
HepRandomEngine & RandExponential::engine() {return *localEngine;}

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

std::ostream & RandExponential::put ( std::ostream & os ) const {
  int pr=os.precision(20);
  os << " " << name() << "\n";
  os << defaultMean << "\n";
  os.precision(pr);
  return os;
}

std::istream & RandExponential::get ( std::istream & is ) {
  std::string inName;
  is >> inName;
  if (inName != name()) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "Mismatch when expecting to read state of a "
    	      << name() << " distribution\n"
	      << "Name found was " << inName
	      << "\nistream is left in the badbit state\n";
    return is;
  }
  is >> defaultMean;
  return is;
}


}  // namespace CLHEP
