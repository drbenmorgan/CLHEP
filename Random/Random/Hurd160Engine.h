// $Id: Hurd160Engine.h,v 1.2 2003/07/17 19:20:02 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                           HEP Random
//                      --- Hurd160Engine ---
//                       class header file
// -----------------------------------------------------------------------
//
// The starting point for the Hurd Random algorithm is the paper in 
// IEEE Transactions on Computers c23, 2 Feb 1974. The algorithm is
// essentially a series of 32 interconnected b-bit registers. The basic
// property is that at each step, bit 1 becomes bit 0, bit 2 the new bit 1,
// bit b the new bit b-1. This is modified so that the new bit b0 is the old
// bit b1 XOR'd with some bit b-d from the previous bit register. The values
// of d can be chosen so as to generate a primitive polynomial, a maximal
// length sequence through all bit patterns except the zero pattern.
//
// This generator, Hurd160 use values based upon Table I of the afore 
// mentioned paper, such that we have 160 total bits, representing 32
// 5-bit registers (actually implemented as an array of 5 32-bit words)
// =======================================================================
//  07-23-98  KLS   Initial draft started
// Ken Smith      - Added conversion operators:  6th Aug 1998
// =======================================================================

#ifndef Hurd160Engine_h
#define Hurd160Engine_h

#include "CLHEP/Random/RandomEngine.h"

namespace CLHEP {

/**
 * @author
 * @ingroup random
 */
class Hurd160Engine: public HepRandomEngine {
 
public:

  Hurd160Engine();
  Hurd160Engine( std::istream &is);
  Hurd160Engine( long seed );
  Hurd160Engine( int rowIndex, int colIndex );
  virtual ~Hurd160Engine();
  // Constructors and destructor.

  Hurd160Engine( const Hurd160Engine &p );
  Hurd160Engine & operator = ( const Hurd160Engine &p );
  // Copy constructor and operator=.

  double flat();
  // Returns a pseudo random number between 0 and 1

  void flatArray( const int size, double* vect );
  // Fills the array "vect" of specified size with flat random values.

  void setSeed( long seed, int );
  // Sets the state of the algorithm according to seed.

  void setSeeds( const long* seeds, int );
  // Sets the state of the algorithm according to the zero-terminated
  // array of seeds. 

  void saveStatus( const char filename[] = "Hurd160Engine.conf" ) const;
  // Saves on named file the current engine status

  void restoreStatus( const char filename[] = "Hurd160Engine.conf" );
  // Reads from named file the last saved engine status
  // and restores it.

  void showStatus() const;
  // Dumps the engine status on the screen

  operator float();      // flat value, without worrying about filling bits
  operator unsigned int();  // 32-bit flat value, quickest of all

  friend std::ostream& operator<< ( std::ostream& os, const Hurd160Engine& e );
  friend std::istream& operator>> ( std::istream& is,       Hurd160Engine& e );

private:
  static int numEngines;
  static int maxIndex;

  static double twoToMinus_32;
  static double twoToMinus_53;
  static double nearlyTwoToMinus_54;
  void powersOfTwo();
  void advance();

  int wordIndex;
  unsigned int words[5];

}; // Hurd160Engine

}  // namespace CLHEP

#endif // Hurd160Engine_h
