// $Id: RandEngine.cc,v 1.4.4.1 2004/04/29 00:20:37 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                         --- RandEngine ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Minor corrections: 31st October 1996
//                - Added methods for engine status: 19th November 1996
//                - mx is initialised to RAND_MAX: 2nd April 1997
//                - Fixed bug in setSeeds(): 15th September 1997
//                - Private copy constructor and operator=: 26th Feb 1998
// J.Marraffino   - Added stream operators and related constructor.
//                  Added automatic seed selection from seed table and
//                  engine counter. Removed RAND_MAX and replaced by
//                  pow(0.5,32.). Flat() returns now 32 bits values
//                  obtained by concatenation: 15th Feb 1998
// Ken Smith      - Added conversion operators:  6th Aug 1998
// J. Marraffino  - Remove dependence on hepString class  13 May 1999
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandEngine.h"
#include "CLHEP/Random/Random.h"
#include <string.h>
#include <cmath>	// for pow()
#include <stdlib.h>	// for int()

namespace CLHEP {

static const int MarkerLen = 64; // Enough room to hold a begin or end marker. 

// number of instances with automatic seed selection
int RandEngine::numEngines = 0;

// Maximum index into the seed table
int RandEngine::maxIndex = 215;

RandEngine::RandEngine(long seed) 
: mantissa_bit_32( pow(0.5,32.) )
{
   setSeed(seed,0);
   setSeeds(&theSeed,0);
   seq = 0;
}

RandEngine::RandEngine(int rowIndex, int colIndex)
: mantissa_bit_32( pow(0.5,32.) )
{
   long seeds[2];
   long seed;

   int cycle = abs(int(rowIndex/maxIndex));
   int row = abs(int(rowIndex%maxIndex));
   int col = abs(int(colIndex%2));
   long mask = ((cycle & 0x000007ff) << 20 );
   HepRandom::getTheTableSeeds( seeds, row );
   seed = (seeds[col])^mask;
   setSeed(seed,0);
   setSeeds(&theSeed,0);
   seq = 0;
}

RandEngine::RandEngine()
: mantissa_bit_32( pow(0.5,32.) )
{
   long seeds[2];
   long seed;
   int cycle,curIndex;

   cycle = abs(int(numEngines/maxIndex));
   curIndex = abs(int(numEngines%maxIndex));
   numEngines += 1;
   long mask = ((cycle & 0x007fffff) << 8);
   HepRandom::getTheTableSeeds( seeds, curIndex );
   seed = seeds[0]^mask;
   setSeed(seed,0);
   setSeeds(&theSeed,0);
   seq = 0;
}

RandEngine::RandEngine(std::istream& is)
: mantissa_bit_32( pow(0.5,32.) )
{
   is >> *this;
}

RandEngine::~RandEngine() {}

RandEngine::RandEngine(const RandEngine &p)
: mantissa_bit_32( pow(0.5,32.) )
{
  // Assignment and copy of RandEngine objects may provoke
  // undesired behavior in a single thread environment.
  
  std::cerr << "!!! WARNING !!! - Illegal operation." << std::endl;
  std::cerr << "- Copy constructor and operator= are NOT allowed on "
	    << "RandEngine objects -" << std::endl;
  *this = p;
}

RandEngine & RandEngine::operator = (const RandEngine &p)
{
  // Assignment and copy of RandEngine objects may provoke
  // undesired behavior in a single thread environment.

  std::cerr << "!!! WARNING !!! - Illegal operation." << std::endl;
  std::cerr << "- Copy constructor and operator= are NOT allowed on "
	    << "RandEngine objects -" << std::endl;
  *this = p;
  return *this;
}

void RandEngine::setSeed(long seed, int)
{
   theSeed = seed;
   srand( int(seed) );
   seq = 0;
}

void RandEngine::setSeeds(const long* seeds, int)
{
  setSeed(seeds ? *seeds : 19780503L, 0);
  theSeeds = seeds;
}

void RandEngine::saveStatus( const char filename[] ) const
{
   std::ofstream outFile( filename, std::ios::out ) ;

   if (!outFile.bad()) {
     outFile << theSeed << std::endl;
     outFile << seq << std::endl;
   }
}

void RandEngine::restoreStatus( const char filename[] )
{
   // The only way to restore the status of RandEngine is to
   // keep track of the number of shooted random sequences, reset
   // the engine and re-shoot them again. The Rand algorithm does
   // not provide any way of getting its internal status.

   std::ifstream inFile( filename, std::ios::in);
   long count;

   if (!inFile.bad() && !inFile.eof()) {
     inFile >> theSeed;
     inFile >> count;
     setSeed(theSeed,0);
     for (int i=0; i<count; ++i) flat();
   }
}

void RandEngine::showStatus() const
{
   std::cout << std::endl;
   std::cout << "---------- Rand engine status ----------" << std::endl;
   std::cout << " Initial seed  = " << theSeed << std::endl;
   std::cout << " Shooted sequences = " << seq << std::endl;
   std::cout << "----------------------------------------" << std::endl;
}

double RandEngine::flat()
{
   // rand() is such a horrible generator, it only generates 15 bits.
   // The quick fix here to get it to at LEAST 32 bits is to grab two values,
   // and concatenate them, but that still leaves two bits empty and these
   // we grab from the number of times flat() has been called, i.e. seq. 

   return double( (unsigned int)(        (rand() << 17) |   // bits 31-17
                                      (seq++ & 0x3  << 15) |   // bits 16,15
                                                    rand()     // bits 14-0
                                   ) * mantissa_bit_32
                   );
}

void RandEngine::flatArray(const int size, double* vect)
{
   int i;

   for (i=0; i<size; ++i)
     vect[i]=flat();
}

RandEngine::operator unsigned int() {
  return (unsigned int)( (rand() << 17) | ((seq++&0x3) << 15) | rand() );
}

std::ostream & operator << ( std::ostream& os, const RandEngine& e ) 
{
     char beginMarker[] = "RandEngine-begin";
     char endMarker[]   = "RandEngine-end";

     os << " " << beginMarker << " ";
     os << e.theSeed << " " << e.seq << " ";
     os << endMarker << " ";
     return os;
}

std::istream & operator >> ( std::istream& is, RandEngine& e )
{
   // The only way to restore the status of RandEngine is to
   // keep track of the number of shooted random sequences, reset
   // the engine and re-shoot them again. The Rand algorithm does
   // not provide any way of getting its internal status.

  long count;
  char beginMarker [MarkerLen];
  char endMarker   [MarkerLen];

  is >> std::ws;
  is.width(MarkerLen);  // causes the next read to the char* to be <=
			// that many bytes, INCLUDING A TERMINATION \0 
			// (Stroustrup, section 21.3.2)
  is >> beginMarker;
  if (strcmp(beginMarker,"RandEngine-begin")) {
     is.clear(std::ios::badbit | is.rdstate());
     std::cerr << "\nInput stream mispositioned or"
	       << "\nRandEngine state description missing or"
	       << "\nwrong engine type found." << std::endl;
     return is;
  }
  is >> e.theSeed;
  is >> count;
  is >> std::ws;
  is.width(MarkerLen);  
  is >> endMarker;
  if (strcmp(endMarker,"RandEngine-end")) {
     is.clear(std::ios::badbit | is.rdstate());
     std::cerr << "\nRandEngine state description incomplete."
	       << "\nInput stream is probably mispositioned now." << std::endl;
     return is;
   }

   e.setSeed(e.theSeed,0);
   for (int i=0; i<count; ++i)
      { e.flat(); }	// { dummy = flat(); }
   return is;
}

}  // namespace CLHEP
