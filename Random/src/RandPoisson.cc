// $Id: RandPoisson.cc,v 1.6 2005/04/27 20:12:50 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                         --- RandPoisson ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Added not static Shoot() method: 17th May 1996
//                - Algorithm now operates on doubles: 31st Oct 1996
//                - Added methods to shoot arrays: 28th July 1997
//                - Added check in case xm=-1: 4th February 1998
// J.Marraffino   - Added default mean as attribute and
//                  operator() with mean: 16th Feb 1998
// Gabriele Cosmo - Relocated static data from HepRandom: 5th Jan 1999
// M Fischler     - put and get to/from streams 12/15/04
// M Fischler	      - put/get to/from streams uses pairs of ulongs when
//			+ storing doubles avoid problems with precision 
//			4/14/05
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandPoisson.h"
#include "CLHEP/Units/PhysicalConstants.h"
#include "CLHEP/Random/DoubConv.hh"
#include <cmath>	// for floor()

namespace CLHEP {

std::string RandPoisson::name() const {return "RandPoisson";}
HepRandomEngine & RandPoisson::engine() {return *localEngine;}

// Initialisation of static data
double RandPoisson::status_st[3] = {0., 0., 0.};
double RandPoisson::oldm_st = -1.0;
const double RandPoisson::meanMax_st = 2.0E9;

RandPoisson::~RandPoisson() {
  if ( deleteEngine ) delete localEngine;
}

RandPoisson::RandPoisson(const RandPoisson& right)
 : meanMax(right.meanMax), defaultMean(right.defaultMean)
{;}

double RandPoisson::operator()() {
  return double(fire( defaultMean ));
}

double RandPoisson::operator()( double mean ) {
  return double(fire( mean ));
}

double gammln(double xx) {

// Returns the value ln(Gamma(xx) for xx > 0.  Full accuracy is obtained for 
// xx > 1. For 0 < xx < 1. the reflection formula (6.1.4) can be used first.
// (Adapted from Numerical Recipes in C)

  static double cof[6] = {76.18009172947146,-86.50532032941677,
                             24.01409824083091, -1.231739572450155,
                             0.1208650973866179e-2, -0.5395239384953e-5};
  int j;
  double x = xx - 1.0;
  double tmp = x + 5.5;
  tmp -= (x + 0.5) * log(tmp);
  double ser = 1.000000000190015;

  for ( j = 0; j <= 5; j++ ) {
    x += 1.0;
    ser += cof[j]/x;
  }
  return -tmp + log(2.5066282746310005*ser);
}

long RandPoisson::shoot(double xm) {

// Returns as a floating-point number an integer value that is a random
// deviation drawn from a Poisson distribution of mean xm, using flat()
// as a source of uniform random numbers.
// (Adapted from Numerical Recipes in C)

  double em, t, y;
  double sq, alxm, g;
  double om = getOldMean();
  HepRandomEngine* anEngine = HepRandom::getTheEngine();

  double* status = getPStatus();
  sq = status[0];
  alxm = status[1];
  g = status[2];

  if( xm == -1 ) return 0;
  if( xm < 12.0 ) {
    if( xm != om ) {
      setOldMean(xm);
      g = exp(-xm);
    }
    em = -1;
    t = 1.0;
    do {
      em += 1.0;
      t *= anEngine->flat();
    } while( t > g );
  }
  else if ( xm < getMaxMean() ) {
    if ( xm != om ) {
      setOldMean(xm);
      sq = sqrt(2.0*xm);
      alxm = log(xm);
      g = xm*alxm - gammln(xm + 1.0);
    }
    do {
      do {
	y = tan(CLHEP::pi*anEngine->flat());
	em = sq*y + xm;
      } while( em < 0.0 );
      em = floor(em);
      t = 0.9*(1.0 + y*y)* exp(em*alxm - gammln(em + 1.0) - g);
    } while( anEngine->flat() > t );
  }
  else {
    if ( xm != om ) {
      setOldMean(xm);
      sq = sqrt(2.0*xm);
      alxm = log(xm);
      g = xm*alxm - gammln(xm + 1.0);
    }
    em = xm;
  }    
  setPStatus(sq,alxm,g);
  return long(em);
}

void RandPoisson::shootArray(const int size, long* vect, double m)
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(m);
}

long RandPoisson::shoot(HepRandomEngine* anEngine, double xm) {

// Returns as a floating-point number an integer value that is a random
// deviation drawn from a Poisson distribution of mean xm, using flat()
// of a given Random Engine as a source of uniform random numbers.
// (Adapted from Numerical Recipes in C)

  double em, t, y;
  double sq, alxm, g;
  double om = getOldMean();

  double* status = getPStatus();
  sq = status[0];
  alxm = status[1];
  g = status[2];

  if( xm == -1 ) return 0;
  if( xm < 12.0 ) {
    if( xm != om ) {
      setOldMean(xm);
      g = exp(-xm);
    }
    em = -1;
    t = 1.0;
    do {
      em += 1.0;
      t *= anEngine->flat();
    } while( t > g );
  }
  else if ( xm < getMaxMean() ) {
    if ( xm != om ) {
      setOldMean(xm);
      sq = sqrt(2.0*xm);
      alxm = log(xm);
      g = xm*alxm - gammln(xm + 1.0);
    }
    do {
      do {
	y = tan(CLHEP::pi*anEngine->flat());
	em = sq*y + xm;
      } while( em < 0.0 );
      em = floor(em);
      t = 0.9*(1.0 + y*y)* exp(em*alxm - gammln(em + 1.0) - g);
    } while( anEngine->flat() > t );
  }
  else {
    if ( xm != om ) {
      setOldMean(xm);
      sq = sqrt(2.0*xm);
      alxm = log(xm);
      g = xm*alxm - gammln(xm + 1.0);
    }
    em = xm;
  }    
  setPStatus(sq,alxm,g);
  return long(em);
}

void RandPoisson::shootArray(HepRandomEngine* anEngine, const int size,
                             long* vect, double m)
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(anEngine,m);
}

long RandPoisson::fire() {
  return long(fire( defaultMean ));
}

long RandPoisson::fire(double xm) {

// Returns as a floating-point number an integer value that is a random
// deviation drawn from a Poisson distribution of mean xm, using flat()
// as a source of uniform random numbers.
// (Adapted from Numerical Recipes in C)

  double em, t, y;
  double sq, alxm, g;

  sq = status[0];
  alxm = status[1];
  g = status[2];

  if( xm == -1 ) return 0;
  if( xm < 12.0 ) {
    if( xm != oldm ) {
      oldm = xm;
      g = exp(-xm);
    }
    em = -1;
    t = 1.0;
    do {
      em += 1.0;
      t *= localEngine->flat();
    } while( t > g );
  }
  else if ( xm < meanMax ) {
    if ( xm != oldm ) {
      oldm = xm;
      sq = sqrt(2.0*xm);
      alxm = log(xm);
      g = xm*alxm - gammln(xm + 1.0);
    }
    do {
      do {
	y = tan(CLHEP::pi*localEngine->flat());
	em = sq*y + xm;
      } while( em < 0.0 );
      em = floor(em);
      t = 0.9*(1.0 + y*y)* exp(em*alxm - gammln(em + 1.0) - g);
    } while( localEngine->flat() > t );
  }
  else {
    if ( xm != oldm ) {
      oldm = xm;
      sq = sqrt(2.0*xm);
      alxm = log(xm);
      g = xm*alxm - gammln(xm + 1.0);
    }
    em = xm;
  }    
  status[0] = sq; status[1] = alxm; status[2] = g;
  return long(em);
}

void RandPoisson::fireArray(const int size, long* vect )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire( defaultMean );
}

void RandPoisson::fireArray(const int size, long* vect, double m)
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire( m );
}

std::ostream & RandPoisson::put ( std::ostream & os ) const {
  int pr=os.precision(20);
  std::vector<unsigned long> t(2);
  os << " " << name() << "\n";
  os << "Uvec" << "\n";
  t = DoubConv::dto2longs(meanMax);
  os << meanMax << " " << t[0] << " " << t[1] << "\n";
  t = DoubConv::dto2longs(defaultMean);
  os << defaultMean << " " << t[0] << " " << t[1] << "\n";
  t = DoubConv::dto2longs(status[0]);
  os << status[0] << " " << t[0] << " " << t[1] << "\n";
  t = DoubConv::dto2longs(status[1]);
  os << status[1] << " " << t[0] << " " << t[1] << "\n";
  t = DoubConv::dto2longs(status[2]);
  os << status[2] << " " << t[0] << " " << t[1] << "\n";
  t = DoubConv::dto2longs(oldm);
  os << oldm << " " << t[0] << " " << t[1] << "\n";
  os.precision(pr);
  return os;
#ifdef REMOVED
  int pr=os.precision(20);
  os << " " << name() << "\n";
  os << meanMax << " " << defaultMean << "\n";
  os << status[0] << " " << status[1] << " " << status[2] << "\n"; 
  os.precision(pr);
  return os;
#endif
}

std::istream & RandPoisson::get ( std::istream & is ) {
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
  if (possibleKeywordInput(is, "Uvec", meanMax)) {
    std::vector<unsigned long> t(2);
    is >> meanMax     >> t[0] >> t[1]; meanMax     = DoubConv::longs2double(t); 
    is >> defaultMean >> t[0] >> t[1]; defaultMean = DoubConv::longs2double(t); 
    is >> status[0]   >> t[0] >> t[1]; status[0]   = DoubConv::longs2double(t); 
    is >> status[1]   >> t[0] >> t[1]; status[1]   = DoubConv::longs2double(t); 
    is >> status[2]   >> t[0] >> t[1]; status[2]   = DoubConv::longs2double(t); 
    is >> oldm        >> t[0] >> t[1]; oldm        = DoubConv::longs2double(t); 
    return is;
  }
  // is >> meanMax encompassed by possibleKeywordInput
  is >> defaultMean >> status[0] >> status[1] >> status[2];
  return is;
}

}  // namespace CLHEP

