// $Id: RandFlat.cc,v 1.2 2003/07/17 19:20:02 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandFlat ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// Gabriele Cosmo - Created: 17th May 1995
//                - Added methods to shoot arrays: 28th July 1997
//                - Added operator(): 24th Jul 1997
// J.Marraffino   - Added default arguments as attributes and
//                  operator() with arguments: 16th Feb 1998
// M Fischler     - Copy constructor should supply right engine to HepRandom:
//                  1/26/00.
// M Fischler	  - Semi-fix to the saveEngineStatus misbehavior causing
//		    non-reproducing shootBit() 3/1/00.
// =======================================================================

#include "CLHEP/Random/RandFlat.h"
#include <string.h>

namespace CLHEP {

const int RandFlat::MSBBits= 15;
const unsigned long RandFlat::MSB= 1ul<<RandFlat::MSBBits;
unsigned long RandFlat::staticRandomInt= 0;
unsigned long RandFlat::staticFirstUnusedBit= 0;

RandFlat::~RandFlat() {
  if ( deleteEngine ) delete localEngine;
}

RandFlat::RandFlat(const RandFlat& right)
 : HepRandom(right.getTheEngine()),
   defaultWidth(right.defaultWidth), defaultA(right.defaultA),
   defaultB(right.defaultB)
{;}

double RandFlat::operator()() {
  return fire( defaultA, defaultB );
}

double RandFlat::operator()( double w ) {
  return fire( w );
}

double RandFlat::operator()( double a, double b ) {
  return fire( a, b );
}

double RandFlat::shoot() {
  return HepRandom::getTheEngine()->flat();
}

void RandFlat::shootArray(const int size, double* vect) {
  HepRandom::getTheEngine()->flatArray(size,vect);
}

void RandFlat::shootArray( const int size, double* vect,
                           double lx, double dx  )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(lx,dx);
}

void RandFlat::shootArray( HepRandomEngine* anEngine,
                           const int size, double* vect,
                           double lx, double dx  )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(anEngine,lx,dx);
}

void RandFlat::fireArray( const int size, double* vect)
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire( defaultA, defaultB );
}

void RandFlat::fireArray( const int size, double* vect,
                          double lx, double dx  )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire( lx, dx );
}

void RandFlat::saveEngineStatus ( const char filename[] ) {

  // First save the engine status just like the base class would do:
  getTheEngine()->saveStatus( filename );

  // Now append the cached random Int, and first unused bit:

  std::ofstream outfile ( filename, std::ios::app );

  outfile << "RANDFLAT staticRandomInt: " << staticRandomInt 
          << "    staticFirstUnusedBit: " << staticFirstUnusedBit << "\n";

} // saveEngineStatus


void RandFlat::restoreEngineStatus( const char filename[] ) {

  // First restore the engine status just like the base class would do:
  getTheEngine()->restoreStatus( filename );

  // Now find the line describing the cached data:

  std::ifstream infile ( filename, std::ios::in );
  char inputword[] = "NO_KEYWORD    "; // leaves room for 14 characters plus \0
  while (true) {
    infile.width(13);
    infile >> inputword;
    if (strcmp(inputword,"RANDFLAT")==0) break;
    if (infile.eof()) break;
        // If the file ends without the RANDFLAT line, that means this
        // was a file produced by an earlier version of RandFlat.  We will
        // replicate the old behavior in that case:  staticFirstUnusedBit 
	// and staticRandomInt retain their existing values.
  }

  // Then read and use the caching info:

  if (strcmp(inputword,"RANDFLAT")==0) {
    char setword[40];	// the longest, staticFirstUnusedBit: has length 21
    infile.width(39);
    infile >> setword;
    // setword should be staticRandomInt:  
    infile >> staticRandomInt;
    infile.width(39);
    infile >> setword;
    // setword should be staticFirstUnusedBit: 
    infile >> staticFirstUnusedBit;
  }

} // restoreEngineStatus


}  // namespace CLHEP

