// $Id: MTwistEngine.cc,v 1.3 2003/07/25 20:59:21 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                        --- MTwistEngine ---
//                      class implementation file
// -----------------------------------------------------------------------
// A "fast, compact, huge-period generator" based on M. Matsumoto and 
// T. Nishimura, "Mersenne Twister: A 623-dimensionally equidistributed 
// uniform pseudorandom number generator", to appear in ACM Trans. on
// Modeling and Computer Simulation.  It is a twisted GFSR generator
// with a Mersenne-prime period of 2^19937-1, uniform on open interval (0,1)
// =======================================================================
// Ken Smith      - Started initial draft:                    14th Jul 1998
//                - Optimized to get pow() out of flat() method
//                - Added conversion operators:                6th Aug 1998
// J. Marraffino  - Added some explicit casts to deal with
//                  machines where sizeof(int) != sizeof(long)  22 Aug 1998
// M. Fischler    - Modified constructors such that no two
//		    seeds will match sequences, no single/double
//		    seeds will match, explicit seeds give 
//		    determined results, and default will not 
//		    match any of the above or other defaults.
//                - Modified use of the various exponents of 2
//                  to avoid per-instance space overhead and
//                  correct the rounding procedure              16 Sep 1998
// J. Marfaffino  - Remove dependence on hepString class        13 May 1999
// =======================================================================

#include "Random/defs.h"
#include "CLHEP/Random/Random.h"
#include "CLHEP/Random/MTwistEngine.h"
#include <string.h>
#include <cmath>	// for ldexp()
#include <stdlib.h>	// for abs(int)

using namespace std;

namespace CLHEP {

static const int MarkerLen = 64; // Enough room to hold a begin or end marker. 

double MTwistEngine::twoToMinus_32;
double MTwistEngine::twoToMinus_53;
double MTwistEngine::nearlyTwoToMinus_54;

void MTwistEngine::powersOfTwo() {
  twoToMinus_32 = ldexp (1.0, -32);
  twoToMinus_53 = ldexp (1.0, -53);
  nearlyTwoToMinus_54 = ldexp (1.0, -54) - ldexp (1.0, -100);
}

int MTwistEngine::numEngines = 0;
int MTwistEngine::maxIndex = 215;

MTwistEngine::MTwistEngine() 
{
  powersOfTwo();
  int cycle = abs(int(numEngines/maxIndex));
  int curIndex = abs(int(numEngines%maxIndex));
  long mask = ((cycle & 0x007fffff) << 8);
  long seedlist[2];
  HepRandom::getTheTableSeeds( seedlist, curIndex );
  seedlist[0] = (seedlist[0])^mask;
  seedlist[1] = 0;
  setSeeds( seedlist, numEngines );
  count624=0;
  ++numEngines;
  for( int i=0; i < 2000; ++i ) flat();      // Warm up just a bit
}

MTwistEngine::MTwistEngine(long seed)  
{
  powersOfTwo();
  long seedlist[2]={seed,17587};
  setSeeds( seedlist, 0 );
  count624=0;
  for( int i=0; i < 2000; ++i ) flat();      // Warm up just a bit
}

MTwistEngine::MTwistEngine(int rowIndex, int colIndex)  
{
  powersOfTwo();
  int cycle = abs(int(rowIndex/maxIndex));
  int row = abs(int(rowIndex%maxIndex));
  int col = abs(int(colIndex%2));
  long mask = (( cycle & 0x000007ff ) << 20 );
  long seedlist[2];
  HepRandom::getTheTableSeeds( seedlist, row );
  seedlist[0] = (seedlist[col])^mask;
  seedlist[1] = 690691;
  setSeeds(seedlist, 4444772);
  count624=0;
  for( int i=0; i < 2000; ++i ) flat();      // Warm up just a bit
}

MTwistEngine::MTwistEngine( std::istream& is )  
{
  is >> *this;
}

MTwistEngine::~MTwistEngine() {}

MTwistEngine::MTwistEngine( const MTwistEngine & p )  
{
  *this = p;
}

MTwistEngine & MTwistEngine::operator=( const MTwistEngine & p ) {
  if( this != &p ) {
     for( int i=0; i < 624; ++i )  mt[i] = p.mt[i];
     count624 = p.count624;
  }
  return *this;
}

double MTwistEngine::flat() {
  unsigned int y;

  if( count624 >= N ) {
    register int i;

    for( i=0; i < NminusM; ++i ) {
      y = (mt[i] & 0x80000000) | (mt[i+1] & 0x7fffffff);
      mt[i] = mt[i+M]       ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );
    }

    for(    ; i < N-1    ; ++i ) {
      y = (mt[i] & 0x80000000) | (mt[i+1] & 0x7fffffff);
      mt[i] = mt[i-NminusM] ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );
    }

    y = (mt[i] & 0x80000000) | (mt[0] & 0x7fffffff);
    mt[i] = mt[M-1] ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );

    count624 = 0;
  }

  y = mt[count624];
  y ^= ( y >> 11);
  y ^= ((y << 7 ) & 0x9d2c5680);
  y ^= ((y << 15) & 0xefc60000);
  y ^= ( y >> 18);

  return                      y * twoToMinus_32  +    // Scale to range 
         (mt[count624++] >> 11) * twoToMinus_53  +    // fill remaining bits
                	    nearlyTwoToMinus_54;      // make sure non-zero
}

void MTwistEngine::flatArray( const int size, double *vect ) {
  for( int i=0; i < size; ++i) vect[i] = flat();
}

void MTwistEngine::setSeed(long seed, int k) {
  theSeed = seed ? seed : 4357;
  mt[0] = (unsigned int)theSeed;
  int i;
  for( i=1; i < 624; ++i ) {
    mt[i] = (69069 * mt[i-1]) & 0xffffffff;
  }
  for( i=1; i < 624; ++i ) {
    mt[i] ^= k;			// MF 9/16/98: distinguish starting points
  }
}

void MTwistEngine::setSeeds(const long *seeds, int k) {
  setSeed( (*seeds ? *seeds : 43571346), k );
  int i;
  for( i=1; i < 624; ++i ) {
    mt[i] = ( seeds[1] + mt[i] ) & 0xffffffff; // MF 9/16/98 
  }
  theSeeds = seeds;
}

void MTwistEngine::saveStatus( const char filename[] ) const
{
   std::ofstream outFile( filename, std::ios::out ) ;
   if (!outFile.bad()) {
     outFile << theSeed << std::endl;
     for (int i=0; i<624; ++i) outFile <<std::setprecision(20) << mt[i] << " ";
     outFile << std::endl;
     outFile << count624 << std::endl;
   }
}

void MTwistEngine::restoreStatus( const char filename[] )
{
   std::ifstream inFile( filename, std::ios::in);

   if (!inFile.bad() && !inFile.eof()) {
     inFile >> theSeed;
     for (int i=0; i<624; ++i) inFile >> mt[i];
     inFile >> count624;
   }
}

void MTwistEngine::showStatus() const
{
   std::cout << std::endl;
   std::cout << "--------- MTwist engine status ---------" << std::endl;
   std::cout << std::setprecision(20);
   std::cout << " Initial seed      = " << theSeed << std::endl;
   std::cout << " Current index     = " << count624 << std::endl;
   std::cout << " Array status mt[] = " << std::endl;
   for (int i=0; i<624; i+=5) {
     std::cout << mt[i]   << " " << mt[i+1] << " " << mt[i+2] << " " 
	       << mt[i+3] << " " << mt[i+4] << std::endl;
   }
   std::cout << "----------------------------------------" << std::endl;
}

MTwistEngine::operator float() {
  unsigned int y;

  if( count624 >= N ) {
    register int i;

    for( i=0; i < NminusM; ++i ) {
      y = (mt[i] & 0x80000000) | (mt[i+1] & 0x7fffffff);
      mt[i] = mt[i+M]       ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );
    }

    for(    ; i < N-1    ; ++i ) {
      y = (mt[i] & 0x80000000) | (mt[i+1] & 0x7fffffff);
      mt[i] = mt[i-NminusM] ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );
    }

    y = (mt[i] & 0x80000000) | (mt[0] & 0x7fffffff);
    mt[i] = mt[M-1] ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );

    count624 = 0;
  }

  y = mt[count624++];
  y ^= ( y >> 11);
  y ^= ((y << 7 ) & 0x9d2c5680);
  y ^= ((y << 15) & 0xefc60000);
  y ^= ( y >> 18);

  return (float)(y * twoToMinus_32);
}

MTwistEngine::operator unsigned int() {
  unsigned int y;

  if( count624 >= N ) {
    register int i;

    for( i=0; i < NminusM; ++i ) {
      y = (mt[i] & 0x80000000) | (mt[i+1] & 0x7fffffff);
      mt[i] = mt[i+M]       ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );
    }

    for(    ; i < N-1    ; ++i ) {
      y = (mt[i] & 0x80000000) | (mt[i+1] & 0x7fffffff);
      mt[i] = mt[i-NminusM] ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );
    }

    y = (mt[i] & 0x80000000) | (mt[0] & 0x7fffffff);
    mt[i] = mt[M-1] ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );

    count624 = 0;
  }

  y = mt[count624++];
  y ^= ( y >> 11);
  y ^= ((y << 7 ) & 0x9d2c5680);
  y ^= ((y << 15) & 0xefc60000);
  y ^= ( y >> 18);

  return y;
}

std::ostream & operator << ( std::ostream& os, const MTwistEngine& e )
{
   char beginMarker[] = "MTwistEngine-begin";
   char endMarker[]   = "MTwistEngine-end";

   os << " " << beginMarker << " ";
   os << e.theSeed << " ";
   for (int i=0; i<624; ++i) {
     os << std::setprecision(20) << e.mt[i] << " ";
   }
   os << e.count624 << " ";
   os << endMarker << " ";
   return os;
}

std::istream & operator >> ( std::istream& is, MTwistEngine& e )
{
  char beginMarker [MarkerLen];
  char endMarker   [MarkerLen];

  is >> std::ws;
  is.width(MarkerLen);  // causes the next read to the char* to be <=
			// that many bytes, INCLUDING A TERMINATION \0 
			// (Stroustrup, section 21.3.2)
  is >> beginMarker;
  if (strcmp(beginMarker,"MTwistEngine-begin")) {
     is.clear(std::ios::badbit | is.rdstate());
     std::cerr << "\nInput stream mispositioned or"
	       << "\nMTwistEngine state description missing or"
	       << "\nwrong engine type found." << std::endl;
     return is;
   }
  is >> e.theSeed;
  for (int i=0; i<624; ++i)  is >> e.mt[i];
  is >> e.count624;
  is >> std::ws;
  is.width(MarkerLen);  
  is >> endMarker;
  if (strcmp(endMarker,"MTwistEngine-end")) {
     is.clear(std::ios::badbit | is.rdstate());
     std::cerr << "\nMTwistEngine state description incomplete."
	       << "\nInput stream is probably mispositioned now." << std::endl;
     return is;
   }
   return is;
}

}  // namespace CLHEP
