// $Id: RandGauss.cc,v 1.4.2.1 2004/12/17 20:19:38 fischler Exp $
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
// M Fischler     - Avoiding hang when file not found in restoreEngineStatus 
//                  12/3/04
// M Fischler     - put and get to/from streams 12/8/04
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandGauss.h"
#include <string.h>
#include <cmath>	// for log()

namespace CLHEP {

std::string RandGauss::name() const {return "RandGauss";}
HepRandomEngine & RandGauss::engine() {return *localEngine;}

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
  if (!infile) return;

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
      infile >> nextGauss_st; // because a 0 will have been output
    }
  } else {
    set_st = false;
  }

} // restoreEngineStatus

  // Save and restore to/from streams
  
std::ostream & RandGauss::put ( std::ostream & os ) const {
  os << name() << "\n";
  int prec = os.precision(20);
  os << "Mean: " << defaultMean << " Sigma: " << defaultStdDev << "\n";
  if ( set ) {
    os << "RANDGAUSS CACHED_GAUSSIAN: " << nextGauss << "\n";
  } else {
    os << "RANDGAUSS NO_CACHED_GAUSSIAN: 0 \n" ;
  }
  os.precision(prec);
  return os;
} // put   

std::istream & RandGauss::get ( std::istream & is ) {
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
  std::string c1;
  std::string c2;
  is >> c1 >> defaultMean >> c2 >> defaultStdDev;
  if ( (!is) || (c1 != "Mean:") || (c2 != "Sigma:") ) {
    std::cerr << "i/o problem while expecting to read state of a "
    	      << name() << " distribution\n"
	      << "default mean and/or sigma could not be read\n";
    return is;
  }
  is >> c1 >> c2 >> nextGauss;
  if ( (!is) || (c1 != "RANDGAUSS") ) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "Failure when reading caching state of RandGauss\n";
    return is;
  }
  if (c2 == "CACHED_GAUSSIAN:") {
    set = true;
  } else if (c2 == "NO_CACHED_GAUSSIAN:") {
    set = false;  
  } else {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "Unexpected caching state keyword of RandGauss:" << c2
	      << "\nistream is left in the badbit state\n";
  } 
  return is;
} // get


}  // namespace CLHEP

