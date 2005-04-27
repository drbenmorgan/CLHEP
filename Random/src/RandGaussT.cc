// $Id: RandGaussT.cc,v 1.4 2005/04/27 20:12:50 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandGaussT ---
//                      class implementation file
// -----------------------------------------------------------------------

// =======================================================================
// M Fischler	  - Created 04 Feb 2000
// M Fischler     - put and get to/from streams 12/13/04
// M Fischler	  - operator() modified to use localEngine 12/13/04
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandGaussT.h"
#include <iostream>

namespace CLHEP {

std::string RandGaussT::name() const {return "RandGaussT";}
HepRandomEngine & RandGaussT::engine() {return RandGauss::engine();}

RandGaussT::~RandGaussT() {
}

RandGaussT::RandGaussT(const RandGaussT& right) :  RandGauss(right) {
}

double RandGaussT::operator()() {
  return HepStat::flatToGaussian(localEngine->flat()) * defaultStdDev 
								+ defaultMean;
}

double RandGaussT::operator()( double mean, double stdDev ) {
  return HepStat::flatToGaussian(localEngine->flat()) * stdDev + mean;
}

void RandGaussT::shootArray( const int size, double* vect,
                            double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = shoot(mean,stdDev);
   }
}

void RandGaussT::shootArray( HepRandomEngine* anEngine,
                            const int size, double* vect,
                            double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = shoot(anEngine,mean,stdDev);
   }
}

void RandGaussT::fireArray( const int size, double* vect)
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = fire( defaultMean, defaultStdDev );
   }
}

void RandGaussT::fireArray( const int size, double* vect,
                           double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = fire( mean, stdDev );
   }
}

std::ostream & RandGaussT::put ( std::ostream & os ) const {
  int pr=os.precision(20);
  os << " " << name() << "\n";
  RandGauss::put(os);
  os.precision(pr);
  return os;
}

std::istream & RandGaussT::get ( std::istream & is ) {
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
  RandGauss::get(is);
  return is;
}

}  // namespace CLHEP

