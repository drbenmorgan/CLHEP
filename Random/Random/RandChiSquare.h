// $Id: RandChiSquare.h,v 1.2 2003/07/17 19:20:02 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                         --- RandChiSquare ---
//                          class header file
// -----------------------------------------------------------------------

// Class defining methods for shooting Chi^2 distributed random values,
// given a number of degrees of freedom a (default=1.0).
// Default values are used for operator()().

// Valid values of a satisfy a > 1. When invalid values are presented,
// the code silently returns -1.0.

// =======================================================================
// John Marraffino - Created: 12th May 1998  Based on the C-Rand package
//                   by Ernst Stadlober and Franz Niederl of the Technical
//                   University of Graz, Austria.
// Gabriele Cosmo  - Removed useless methods and data: 5th Jan 1999
// =======================================================================

#ifndef RandChiSquare_h
#define RandChiSquare_h 1

#include "CLHEP/Random/Random.h"

namespace CLHEP {

/**
 * @author
 * @ingroup random
 */
class RandChiSquare : public HepRandom {

public:

  inline RandChiSquare ( HepRandomEngine& anEngine, double a=1 );
  inline RandChiSquare ( HepRandomEngine* anEngine, double a=1 );
  // These constructors should be used to instantiate a RandChiSquare
  // distribution object defining a local engine for it.
  // The static generator will be skipped using the non-static methods
  // defined below.
  // If the engine is passed by pointer the corresponding engine object
  // will be deleted by the RandChiSquare destructor.
  // If the engine is passed by reference the corresponding engine object
  // will not be deleted by the RandChiSquare destructor.

  virtual ~RandChiSquare();
  // Destructor

  // Static methods to shoot random values using the static generator

  static inline double shoot();

  static double shoot( double a );

  static void shootArray ( const int size, double* vect,
                            double a=1.0 );

  //  Static methods to shoot random values using a given engine
  //  by-passing the static generator.

  static inline double shoot( HepRandomEngine* anEngine );

  static double shoot( HepRandomEngine* anEngine, 
                                  double a );

  static void shootArray ( HepRandomEngine* anEngine, const int size,
                            double* vect, double a=1.0 );

  //  Methods using the localEngine to shoot random values, by-passing
  //  the static generator.

  inline double fire();

  double fire( double a );
  
  void fireArray ( const int size, double* vect);
  void fireArray ( const int size, double* vect,
                   double a );
  inline double operator()();
  inline double operator()( double a );

private:

  // Private copy constructor. Defining it here disallows use.
  RandChiSquare(const RandChiSquare& d);

  static double genChiSquare( HepRandomEngine *anEngine, double a );

  HepRandomEngine* localEngine;
  bool deleteEngine;
  const double defaultA;

};

}  // namespace CLHEP

#include "CLHEP/Random/RandChiSquare.icc"

#endif
