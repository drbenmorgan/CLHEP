// $Id: RandEngine.h,v 1.2 2003/07/17 19:20:02 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                         --- RandEngine ---
//                          class header file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).
//
// Simple random engine using rand() and srand() functions from C standard
// library to implement the flat() basic distribution and for setting
// seeds.
// Copy constructor and operator= are private for objects of this class.

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Minor corrections: 31st October 1996
//                - Added methods for engine status: 19th November 1996
//                - setSeed(), setSeeds() now have default dummy argument
//                  set to zero: 11th July 1997
//                - Private copy constructor and operator=: 26th Feb 1998
// J.Marraffino   - Added stream operators and related constructor.
//                  Added automatic seed selection from seed table and
//                  engine counter: 15th Feb 1998
// Ken Smith      - Added conversion operators:  6th Aug 1998
//                  replace mx by mantissa_bit_32
// =======================================================================

#ifndef RandEngine_h
#define RandEngine_h 1

#include "CLHEP/Random/RandomEngine.h"

namespace CLHEP {

/**
 * @author <Gabriele.Cosmo@cern.ch>
 * @ingroup random
 */
class RandEngine : public HepRandomEngine {

public:

  RandEngine(std::istream& is);
  RandEngine();
  RandEngine(long seed);
  RandEngine(int rowIndex, int colIndex);
  virtual ~RandEngine();
  // Constructors and destructor

  double flat();
  // It returns a pseudo random number between 0 and 1,
  // according to the standard stdlib random function rand()
  // but excluding the end points.

  void flatArray (const int size, double* vect);
  // Fills the array "vect" of specified size with flat random values.

  void setSeed(long seed, int dum=0);
  // Sets the state of the algorithm according to seed.

  void setSeeds(const long * seeds, int dum=0);
  // Sets the state of the algorithm according to the zero terminated
  // array of seeds. Only the first seed is used.

  void saveStatus( const char filename[] = "Rand.conf" ) const;
  // Saves on file Rand.conf the current engine status.

  void restoreStatus( const char filename[] = "Rand.conf" );
  // Reads from file Rand.conf the last saved engine status
  // and restores it.

  void showStatus() const;
  // Dumps the engine status on the screen.
 
  operator unsigned int(); // 32-bit flat value, quickest of all.

  friend std::ostream& operator<< (std::ostream& os, const RandEngine& e);
  friend std::istream& operator>> (std::istream& is,       RandEngine& e);

private:

  RandEngine(const RandEngine &p);
  RandEngine & operator = (const RandEngine &p);
  // Private copy constructor and assignment operator.

private:

  const double mantissa_bit_32;
  long seq;
  static int numEngines;
  static int maxIndex;

};

}  // namespace CLHEP

#endif
