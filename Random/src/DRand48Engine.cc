// -*- C++ -*-
// $Id: DRand48Engine.cc,v 1.3 2003/07/25 20:59:21 garren Exp $
// -----------------------------------------------------------------------
//                             HEP Random
//                        --- DRand48Engine ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// G.Cosmo        - Created: 5th September 1995
//                - Minor corrections: 31st October 1996
//                - Added methods for engine status: 19th November 1996
//                - Added srand48(), seed48(), drand48() implementations
//                  for Windows/NT: 6th March 1997
//                - Fixed bug in setSeeds(): 15th September 1997
//                - Private copy constructor and operator=: 26th Feb 1998
// J.Marraffino   - Added stream operators and related constructor.
//                  Added automatic seed selection from seed table and
//                  engine counter: 16th Feb 1998
// J.Marraffino   - Remove dependence on hepString class  13 May 1999
// E.Tcherniaev   - More accurate code for drand48() on NT base on
//                  a code extracted from GNU C Library 2.1.3: 8th Nov 2000
// =======================================================================

#include "Random/defs.h"
#include "CLHEP/Random/Random.h"
#include "CLHEP/Random/DRand48Engine.h"
#include "CLHEP/Random/RandomFunc.h"
#include <string.h>

namespace CLHEP {

static const int MarkerLen = 64; // Enough room to hold a begin or end marker. 
// Number of instances with automatic seed selection
int DRand48Engine::numEngines = 0;

// Maximum index into the seed table
int DRand48Engine::maxIndex = 215;

DRand48Engine::DRand48Engine(long seed)
{
   setSeed(seed,0);
   setSeeds(&theSeed,0);
}

DRand48Engine::DRand48Engine()
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
}

DRand48Engine::DRand48Engine(int rowIndex, int colIndex)
{
   long seed;
   long seeds[2];

   int cycle = abs(int(rowIndex/maxIndex));
   int row = abs(int(rowIndex%maxIndex));
   int col = abs(int(colIndex%2));
   long mask = ((cycle & 0x000007ff) << 20);
   HepRandom::getTheTableSeeds( seeds, row );
   seed = (seeds[col])^mask;
   setSeed(seed,0);
   setSeeds(&theSeed,0);
}

DRand48Engine::DRand48Engine(std::istream& is)
{
   is >> *this;
}

DRand48Engine::~DRand48Engine() {}

DRand48Engine::DRand48Engine(const DRand48Engine &p)
{
  // Assignment and copy of DRand48Engine objects may provoke
  // undesired behavior in a single thread environment.
  
  std::cerr << "!!! WARNING !!! - Illegal operation." << std::endl;
  std::cerr << "- Copy constructor and operator= are NOT allowed on "
	    << "DRand48Engine objects -" << std::endl;
  *this = p;
}

DRand48Engine & DRand48Engine::operator = (const DRand48Engine &p)
{
  // Assignment and copy of DRand48Engine objects may provoke
  // undesired behavior in a single thread environment.

  std::cerr << "!!! WARNING !!! - Illegal operation." << std::endl;
  std::cerr << "- Copy constructor and operator= are NOT allowed on "
	    << "DRand48Engine objects -" << std::endl;
  *this = p;
  return *this;
}

void DRand48Engine::setSeed(long seed, int)
{
   srand48( seed );
   theSeed = seed;
}

void DRand48Engine::setSeeds(const long* seeds, int)
{
  setSeed(seeds ? *seeds : 19780503L, 0);
  theSeeds = seeds;
}

void DRand48Engine::saveStatus( const char filename[] ) const
{
   std::ofstream outFile( filename, std::ios::out ) ;

   unsigned short dummy[] = { 0, 0, 0 };
   unsigned short* cseed = seed48(dummy);

   if (!outFile.bad()) {
     outFile << theSeed << std::endl;
     for (int i=0; i<3; ++i) {
       outFile << cseed[i] << std::endl;
       dummy[i] = cseed[i];
     }
     seed48(dummy);
   }
}

void DRand48Engine::restoreStatus( const char filename[] )
{
   std::ifstream inFile( filename, std::ios::in);
   unsigned short cseed[3];

   if (!inFile.bad() && !inFile.eof()) {
     inFile >> theSeed;
     for (int i=0; i<3; ++i)
       inFile >> cseed[i];
     seed48(cseed);
   }
}

void DRand48Engine::showStatus() const
{
   unsigned short dummy[] = { 0, 0, 0 };
   unsigned short* cseed = seed48(dummy);
   std::cout << std::endl;
   std::cout << "-------- DRand48 engine status ---------" << std::endl;
   std::cout << " Initial seed  = " << theSeed << std::endl;
   std::cout << " Current seeds = " << cseed[0] << ", ";
   std::cout                        << cseed[1] << ", ";
   std::cout                        << cseed[2] << std::endl;
   std::cout << "----------------------------------------" << std::endl;
   for (int i=0; i<3; ++i)
     dummy[i] = cseed[i];
   seed48(dummy);
}

double DRand48Engine::flat()
{
   double num = 0.;

   while (num == 0.)
     num = drand48();
   return num;
}

void DRand48Engine::flatArray(const int size, double* vect)
{
   int i;

   for (i=0; i<size; ++i)
     vect[i]=flat();
}

std::ostream & operator<< ( std::ostream& os, const DRand48Engine& e  )
{
   unsigned short dummy[] = { 0, 0, 0 };
   unsigned short* cseed = seed48(dummy);
   char beginMarker[] = "DRand48Engine-begin";
   char endMarker[] = "DRand48Engine-end";

   os << " " << beginMarker << " ";
   os << e.theSeed << " ";
   for (int i=0; i<3; ++i) {
     dummy[i] = cseed[i];
     os << cseed[i] << " ";
   }
   os << endMarker << " ";
   seed48(dummy);
   return os;
}

std::istream & operator >> ( std::istream& is, DRand48Engine& e )
{
  unsigned short cseed[3];
  char beginMarker [MarkerLen];
  char endMarker   [MarkerLen];

  is >> std::ws;
  is.width(MarkerLen);  // causes the next read to the char* to be <=
			// that many bytes, INCLUDING A TERMINATION \0 
			// (Stroustrup, section 21.3.2)
  is >> beginMarker;
  if (strcmp(beginMarker,"DRand48Engine-begin")) {
     is.clear(std::ios::badbit | is.rdstate());
     std::cerr << "\nInput stream mispositioned or"
	       << "\nDRand48Engine state description missing or"
	       << "\nwrong engine type found." << std::endl;
     return is;
  }
  is >> e.theSeed;
  for (int i=0; i<3; ++i) {
    is >> cseed[i];
  }
  is >> std::ws;
  is.width(MarkerLen);
  is >> endMarker;
  if (strcmp(endMarker,"DRand48Engine-end")) {
     is.clear(std::ios::badbit | is.rdstate());
     std::cerr << "\nDRand48Engine state description incomplete."
	       << "\nInput stream is probably mispositioned now." << std::endl;
     return is;
   }
   seed48(cseed);
   return is;
}

}  // namespace CLHEP