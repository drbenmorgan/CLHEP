// $Id: RandGauss.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandGauss ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Added methods to shoot arrays: 28th July 1997
// J.Marraffino   - Added default arguments as attributes and
//                  operator() with arguments. Introduced method normal()
//                  for computation in fire(): 16th Feb 1998
// Gabriele Cosmo - Relocated static data from HepRandom: 5th Jan 1999
// M Fischler     - Copy constructor should supply right engine to HepRandom:
//		    1/26/00.
// M Fischler     - Workaround for problem of non-reproducing saveEngineStatus
//		    by saving cached gaussian.  March 2000.
// =======================================================================

#include "CLHEP/Random/RandGauss.h"
#include <string.h>
#include <cmath>	// for log()

// Initialisation of static data
bool RandGauss::set_st = false;
double RandGauss::nextGauss_st = 0.0;

RandGauss::~RandGauss() {
  if ( deleteEngine ) delete localEngine;
}

RandGauss::RandGauss(const RandGauss& right)
 : HepRandom(right.getTheEngine()), 
   defaultMean(right.defaultMean), defaultStdDev(right.defaultStdDev)
{;}

double RandGauss::operator()() {
  return fire( defaultMean, defaultStdDev );
}

double RandGauss::operator()( double mean, double stdDev ) {
  return fire( mean, stdDev );
}

double RandGauss::shoot()
{
  // Gaussian random numbers are generated two at the time, so every other
  // time this is called we just return a number generated the time before.

  if ( getFlag() ) {
    setFlag(false);
    return getVal();
  }

  double r;
  double v1,v2,fac,val;
  HepRandomEngine* anEngine = HepRandom::getTheEngine();

  do {
    v1 = 2.0 * anEngine->flat() - 1.0;
    v2 = 2.0 * anEngine->flat() - 1.0;
    r = v1*v1 + v2*v2;
  } while ( r > 1.0 );

  fac = sqrt(-2.0*log(r)/r);
  val = v1*fac;
  setVal(val);
  setFlag(true);
  return v2*fac;
}

void RandGauss::shootArray( const int size, double* vect,
                            double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(mean,stdDev);
}

double RandGauss::shoot( HepRandomEngine* anEngine )
{
  // Gaussian random numbers are generated two at the time, so every other
  // time this is called we just return a number generated the time before.

  if ( getFlag() ) {
    setFlag(false);
    return getVal();
  }

  double r;
  double v1,v2,fac,val;

  do {
    v1 = 2.0 * anEngine->flat() - 1.0;
    v2 = 2.0 * anEngine->flat() - 1.0;
    r = v1*v1 + v2*v2;
  } while ( r > 1.0 );

  fac = sqrt( -2.0*log(r)/r);
  val = v1*fac;
  setVal(val);
  setFlag(true);
  return v2*fac;
}

void RandGauss::shootArray( HepRandomEngine* anEngine,
                            const int size, double* vect,
                            double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(anEngine,mean,stdDev);
}

double RandGauss::normal()
{
  // Gaussian random numbers are generated two at the time, so every other
  // time this is called we just return a number generated the time before.

  if ( set ) {
    set = false;
    return nextGauss;
  }

  double r;
  double v1,v2,fac,val;

  do {
    v1 = 2.0 * localEngine->flat() - 1.0;
    v2 = 2.0 * localEngine->flat() - 1.0;
    r = v1*v1 + v2*v2;
  } while ( r > 1.0 );

  fac = sqrt(-2.0*log(r)/r);
  val = v1*fac;
  nextGauss = val;
  set = true;
  return v2*fac;
}

void RandGauss::fireArray( const int size, double* vect)
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire( defaultMean, defaultStdDev );
}

void RandGauss::fireArray( const int size, double* vect,
                           double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire( mean, stdDev );
}

void RandGauss::saveEngineStatus ( const char filename[] ) {

  // First save the engine status just like the base class would do:
  getTheEngine()->saveStatus( filename );

  // Now append the cached variate, if any:

  std::ofstream outfile ( filename, std::ios::app );

  if ( set_st ) {
    outfile << "RANDGAUSS CACHED_GAUSSIAN: " << std::setprecision(20) 
					<< nextGauss_st << "\n";
  } else {
    outfile << "RANDGAUSS NO_CACHED_GAUSSIAN: 0 \n" ;
  }

} // saveEngineStatus

void RandGauss::restoreEngineStatus( const char filename[] ) {

  // First restore the engine status just like the base class would do:
  getTheEngine()->restoreStatus( filename );

  // Now find the line describing the cached variate:

  std::ifstream infile ( filename, std::ios::in );

  char inputword[] = "NO_KEYWORD    "; // leaves room for 14 characters plus \0
  while (true) {
    infile.width(13);
    infile >> inputword;
    if (strcmp(inputword,"RANDGAUSS")==0) break;
    if (infile.eof()) break;
	// If the file ends without the RANDGAUSS line, that means this
	// was a file produced by an earlier version of RandGauss.  We will
	// replicated the old behavior in that case:  set_st is cleared.
  }

  // Then read and use the caching info:

  if (strcmp(inputword,"RANDGAUSS")==0) {
    char setword[40];	// the longest, staticFirstUnusedBit: has length 21
    infile.width(39);
    infile >> setword;  // setword should be CACHED_GAUSSIAN:
    if (strcmp(setword,"CACHED_GAUSSIAN:") ==0) {
      set_st = true;
      infile >> nextGauss_st;
    } else {
      set_st = false;
    }
  } else {
    set_st = false;
  }

} // restoreEngineStatus

