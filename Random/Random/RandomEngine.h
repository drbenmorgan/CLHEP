// $Id: RandomEngine.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                        --- HepRandomEngine ---
//                          class header file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).
//
// Is the abstract class defining the interface for each random engine. It
// implements the getSeed() and getSeeds() methods which return the initial
// seed value and the initial array of seeds respectively. It defines 7
// pure virtual functions: flat(), flatArray(), setSeed(), setSeeds(),
// saveStatus(), restoreStatus() and showStatus(), which are implemented by
// the concrete random engines each one inheriting from this abstract class.
// Many concrete random engines can be defined and added to the structure,
// simply making them inheriting from HepRandomEngine and defining the six
// functions flat(), flatArray(), setSeed(), setSeeds(), saveStatus(),
// restoreStatus() and showStatus() in such a way that flat() and
// flatArray() return double random values ranging between ]0,1[.
// All the random engines have a default seed value already set but they
// can be instantiated with a different seed value set up by the user.

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Minor corrections: 31st October 1996
//                - Added methods for engine status: 19th November 1996
//                - Removed default values to setSeed() and
//                  setSeeds() pure virtual methods: 16th Oct 1997
//                - Moved seeds table to HepRandom: 19th Mar 1998
// Ken Smith      - Added conversion operators:  6th Aug 1998
// Mark Fischler  - Added static twoToMinus_xx constants: 11 Sept 1998
// =======================================================================

#ifndef HepRandomEngine_h
#define HepRandomEngine_h 1

#include <iostream>
#include <fstream>
#include <iomanip>

/**
 * @author <Gabriele.Cosmo@cern.ch>
 * @ingroup random
 */
class HepRandomEngine {

public:

  HepRandomEngine();
  virtual ~HepRandomEngine();
  // Constructor and destructor

  inline bool operator==(const HepRandomEngine& engine);
  inline bool operator!=(const HepRandomEngine& engine);
  // Overloaded operators, ==, !=

  virtual double flat() = 0;
  // Should return a pseudo random number between 0 and 1 
  // (excluding the end points)

  virtual void flatArray(const int size, double* vect) = 0;
  // Fills an array "vect" of specified size with flat random values.

  virtual void setSeed(long seed, int) = 0;
  // Should initialise the status of the algorithm according to seed.

  virtual void setSeeds(const long * seeds, int) = 0;
  // Should initialise the status of the algorithm according to the zero terminated
  // array of seeds. It is allowed to ignore one or many seeds in this array.

  virtual void saveStatus( const char filename[] = "Config.conf") const = 0;
  // Should save on a file specific to the instantiated engine in use
  // the current status.

  virtual void restoreStatus( const char filename[] = "Config.conf" ) = 0;
  // Should read from a file (specific to the instantiated engine in use)
  // and restore the last saved engine configuration.

  virtual void showStatus() const = 0;
  // Should dump the current engine status on the screen.

  long getSeed() const { return theSeed; }
  // Gets the current seed.

  const long* getSeeds() const { return theSeeds; }
  // Gets the current array of seeds.

  void getTableSeeds(long* seeds, int index) const;
  // Gets back seed values stored in the table, given the index.

  virtual operator double();        // Returns same as flat()
  virtual operator float();         // less precise flat, faster if possible
  virtual operator unsigned int();     // 32-bit int flat, faster if possible

  // The above three conversion operators permit one to retrieve a pseudo-
  // random number as either a double-precision float, a single-precision
  // float, or a 32-bit unsigned integer. The usage, presuming an object
  // of the respective engine class "e", is as follows:

  // Recommended:
  //    float x;
  //    x = float( e );

  // Reasonable:
  //    x = e;

  // Works, but bad practice:
  //    x = 1.5 + e;

  // Won't compile:
  //    x = e + 1.5;

protected:

  long theSeed;
  const long* theSeeds;

  const double exponent_bit_32;

};

#include "CLHEP/Random/RandomEngine.icc"

#endif
