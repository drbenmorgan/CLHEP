// $Id: Hurd288Engine.cc,v 1.2 2003/07/17 19:20:02 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                           HEP Random
//                     --- Hurd288Engine ---
//                    class implementation file
// -----------------------------------------------------------------------
// An interconnected shift register based on the paper presented by Hurd in
// IEEE Transactions on Computers c23, 2 Feb 1974.
// =======================================================================
// Ken Smith      - Initial draft started:                    23rd Jul 1998
//                - Added conversion operators:                6th Aug 1998
// J. Marraffino  - Added some explicit casts to deal with
//                  machines where sizeof(int) != sizeof(long)  22 Aug 1998
// M. Fischler    - Modified use of the various exponents of 2
//                  to avoid per-instance space overhead and
//                  correct the rounding procedure              15 Sep 1998
//                - Modified various methods to avoid any
//                  possibility of predicting the next number
//                  based on the last several:  We skip one
//                  32-bit word per cycle.			15 Sep 1998
//                - modify word[0] in two of the constructors
//                  so that no sequence can ever accidentally
//                  be produced by differnt seeds.              15 Sep 1998
// J. Marraffino  - Remove dependence on hepString class        13 May 1999
// M. Fischler    - Put endl at end of a save                   10 Apr 2001
//
// =======================================================================

#include "CLHEP/Random/Random.h"
#include "CLHEP/Random/Hurd288Engine.h"
#include <string.h>
#include <cmath>	// for ldexp()
#include <stdlib.h>	// for abs(int)

using namespace std;

namespace CLHEP {

static const int MarkerLen = 64; // Enough room to hold a begin or end marker. 

double Hurd288Engine::twoToMinus_32;
double Hurd288Engine::twoToMinus_53;
double Hurd288Engine::nearlyTwoToMinus_54;

void Hurd288Engine::powersOfTwo() {
  twoToMinus_32 = ldexp (1.0, -32);
  twoToMinus_53 = ldexp (1.0, -53);
  nearlyTwoToMinus_54 = ldexp (1.0, -54) - ldexp (1.0, -100);
}

// Number of instances with automatic seed selection
int Hurd288Engine::numEngines = 0;

// Maximum index into the seed table
int Hurd288Engine::maxIndex = 215;

static inline unsigned int f288(unsigned int a, unsigned int b, unsigned int c)
{
  return ( ((b<<2) & 0x7ffc) | ((a<<2) & ~0x7ffc) | (a>>30) ) ^ 
         ( (c<<1)|(c>>31) );
}

Hurd288Engine::Hurd288Engine() {
  powersOfTwo();
  int cycle    = abs(int(numEngines/maxIndex));
  int curIndex = abs(int(numEngines%maxIndex));
  long mask = ((cycle & 0x007fffff) << 8);
  long seedlist[2];
  HepRandom::getTheTableSeeds( seedlist, curIndex );
  seedlist[0] ^= mask;
  seedlist[1] = 0;
  setSeeds(seedlist, 0);
  words[0] ^= 0x1324abcd;        // To make unique vs long or two unsigned
  if (words[0]==0) words[0] = 1; // ints in the constructor
  ++numEngines;
  for( int i=0; i < 100; ++i ) flat();       // warm up just a bit
}

Hurd288Engine::Hurd288Engine( std::istream& is )
{
    is >> *this;
}

Hurd288Engine::Hurd288Engine( long seed ) {
  powersOfTwo();
  long seedlist[2]={seed,0};
  setSeeds(seedlist, 0);
  words[0] ^= 0xa5482134;        // To make unique vs default two unsigned
  if (words[0]==0) words[0] = 1; // ints in the constructor
  for( int i=0; i < 100; ++i ) flat();       // warm up just a bit
}

Hurd288Engine::Hurd288Engine( int rowIndex, int colIndex ) {
  powersOfTwo();
  int cycle = abs(int(rowIndex/maxIndex));
  int   row = abs(int(rowIndex%maxIndex));
  int   col = colIndex & 0x1;
  long mask = (( cycle & 0x000007ff ) << 20 );
  long seedlist[2];
  HepRandom::getTheTableSeeds( seedlist, row );
  seedlist[0] = (seedlist[col])^mask;
  seedlist[1]= 0;
  setSeeds(seedlist, 0);
  for( int i=0; i < 100; ++i ) flat();       // warm up just a bit
}

Hurd288Engine::~Hurd288Engine() { }

Hurd288Engine::Hurd288Engine( const Hurd288Engine & p ) 
{
  *this = p;
}

Hurd288Engine & Hurd288Engine::operator=( const Hurd288Engine & p ) {
  if( this != &p ) {
    wordIndex = p.wordIndex;
    for( int i=0; i < 9; ++i ) {
      words[i] = p.words[i];
    }
  }
  return *this;
}

void Hurd288Engine::advance() {

     register unsigned int W0, W1, W2, W3, W4, W5, W6, W7, W8;

     W0 = words[0];
     W1 = words[1];
     W2 = words[2];
     W3 = words[3];
     W4 = words[4];
     W5 = words[5];
     W6 = words[6];
     W7 = words[7];
     W8 = words[8];
     W1 ^= W0; W0 = f288(W2, W3, W0);
     W2 ^= W1; W1 = f288(W3, W4, W1);
     W3 ^= W2; W2 = f288(W4, W5, W2);
     W4 ^= W3; W3 = f288(W5, W6, W3);
     W5 ^= W4; W4 = f288(W6, W7, W4);
     W6 ^= W5; W5 = f288(W7, W8, W5);
     W7 ^= W6; W6 = f288(W8, W0, W6);
     W8 ^= W7; W7 = f288(W0, W1, W7);
     W0 ^= W8; W8 = f288(W1, W2, W8);
     words[0] = W0 & 0xffffffff;
     words[1] = W1 & 0xffffffff;
     words[2] = W2 & 0xffffffff;
     words[3] = W3 & 0xffffffff;
     words[4] = W4 & 0xffffffff;
     words[5] = W5 & 0xffffffff;
     words[6] = W6 & 0xffffffff;
     words[7] = W7 & 0xffffffff;
     words[8] = W8 & 0xffffffff;
     wordIndex = 9;

} // advance()


double Hurd288Engine::flat() {

  if( wordIndex <= 2 ) {	// MF 9/15/98: 
				// skip word 0 and use two words per flat
    advance();
  }

  return   words[--wordIndex] * twoToMinus_32 + // most significant part
     (words[--wordIndex]>>11) * twoToMinus_53 + // fill in rest of bits
                    nearlyTwoToMinus_54;        // make sure non-zero
}

void Hurd288Engine::flatArray( const int size, double* vect ) {
    for (int i = 0; i < size; ++i) {
        vect[i] = flat();
    }
}

void Hurd288Engine::setSeed( long seed, int ) {
  words[0] = (unsigned int)seed;
  for (wordIndex = 1; wordIndex < 9; ++wordIndex) {
    words[wordIndex] = 69607 * words[wordIndex-1] + 54329;
  }
}

void Hurd288Engine::setSeeds( const long* seeds, int ) {
  setSeed( *seeds ? *seeds : 32767, 0 );
  theSeeds = seeds;
}
     
void Hurd288Engine::saveStatus( const char filename[] ) const {
  std::ofstream outFile(filename, std::ios::out);
  if( !outFile.bad() ) {
    outFile << std::setprecision(20) << theSeed << " ";
    outFile << wordIndex << " ";
    for( int i = 0; i < 9; ++i ) {
      outFile << words[i] << " ";
    }
    outFile << std::endl;
  }
}

void Hurd288Engine::restoreStatus( const char filename[] ) {
  std::ifstream inFile(filename, std::ios::in);
  if( !inFile.bad() ) {
    inFile >> theSeed;
    inFile >> wordIndex;
    for( int i = 0; i < 9; ++i ) {
        inFile >> words[i];
    }
  }
}

void Hurd288Engine::showStatus() const {
  std::cout << std::setprecision(20) << std::endl;
  std::cout << "----------- Hurd2 engine status ----------" << std::endl;
  std::cout << "Initial seed  = " << theSeed   << std::endl;
  std::cout << "Current index = " << wordIndex << std::endl;
  std::cout << "Current words = " << std::endl;
  for( int i = 0; i < 9 ; ++i ) {
    std::cout << "    " << words[i] << std::endl;
  }
  std::cout << "-------------------------------------------" << std::endl;
}

Hurd288Engine::operator float() {
  if( wordIndex <= 1 ) {	// MF 9/15/98:  skip word 0
    advance();
  }
  return words[--wordIndex ] * twoToMinus_32;
}

Hurd288Engine::operator unsigned int() {
  if( wordIndex <= 1 ) {	// MF 9/15/98:  skip word 0
    advance();
  }
  return words[--wordIndex];
}

std::ostream& operator<< (std::ostream& os, const Hurd288Engine& e) {
  char beginMarker[] = "Hurd288Engine-begin";
  char endMarker[]   = "Hurd288Engine-end";

  os << " " << beginMarker << " ";

  os << std::setprecision(20)  << e.theSeed  << " ";
  os << e.wordIndex << " ";
  for (int i = 0; i < 9; ++i) {
    os << e.words[i]  << " ";
  }
  os << " " << endMarker   << " ";
  return os;
}

std::istream& operator>> (std::istream& is, Hurd288Engine& e) {
  char beginMarker [MarkerLen];
  char endMarker   [MarkerLen];

  is >> std::ws;
  is.width(MarkerLen);  // causes the next read to the char* to be <=
			// that many bytes, INCLUDING A TERMINATION \0 
			// (Stroustrup, section 21.3.2)
  is >> beginMarker;
  if (strcmp(beginMarker,"Hurd288Engine-begin")) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "\nInput mispositioned or"
	      << "\nHurd288Engine state description missing or"
	      << "\nwrong engine type found." << std::endl;
    return is;
  }
  is >> e.theSeed >> e.wordIndex;
  for (int i = 0; i < 9; ++i) {
    is >> e.words[i];
  }
  is >> std::ws;
  is.width(MarkerLen);  
  is >> endMarker;
  if (strcmp(endMarker,"Hurd288Engine-end")) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "\nHurd288Engine state description incomplete."
	      << "\nInput stream is probably mispositioned now." << std::endl;
    return is;
  }
  return is;
}

}  // namespace CLHEP
