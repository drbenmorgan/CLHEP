// $Id: RandBinomial.h,v 1.2 2003/07/17 19:20:02 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                         --- RandBinomial ---
//                          class header file
// -----------------------------------------------------------------------

// Class defining methods for shooting binomial distributed random values,
// given a sample size n (default=1) and a probability p (default=0.5).
// Default values are used for operator()().
//
// Valid input values satisfy the relation n*min(p,1-p) > 0. When invalid
// values are presented, the code silently returns -1.0.

// =======================================================================
// John Marraffino - Created: 12th May 1998  Based on the C-Rand package
//                   by Ernst Stadlober and Franz Niederl of the Technical
//                   University of Graz, Austria.
// Gabriele Cosmo  - Removed useless methods and data: 5th Jan 1999
// =======================================================================

#ifndef RandBinomial_h
#define RandBinomial_h 1

#include "CLHEP/Random/Random.h"

namespace CLHEP {

/**
 * @author
 * @ingroup random
 */
class RandBinomial : public HepRandom {

public:

  inline RandBinomial ( HepRandomEngine& anEngine, long n=1,
                                                     double p=0.5 );
  inline RandBinomial ( HepRandomEngine* anEngine, long n=1,
                                                     double p=0.5 );
  // These constructors should be used to instantiate a RandBinomial
  // distribution object defining a local engine for it.
  // The static generator will be skipped using the non-static methods
  // defined below.
  // If the engine is passed by pointer the corresponding engine object
  // will be deleted by the RandBinomial destructor.
  // If the engine is passed by reference the corresponding engine object
  // will not be deleted by the RandBinomial destructor.

  virtual ~RandBinomial();
  // Destructor

  // Static methods to shoot random values using the static generator

  static inline double shoot();

  static double shoot( long n, double p );

  static void shootArray ( const int size, double* vect,
                            long n=1, double p=0.5 );

  //  Static methods to shoot random values using a given engine
  //  by-passing the static generator.

  static inline double shoot( HepRandomEngine* anEngine );

  static double shoot( HepRandomEngine* anEngine, 
                                  long n, double p );

  static void shootArray ( HepRandomEngine* anEngine, const int size,
                            double* vect, long n=1,
                            double p=0.5 );

  //  Methods using the localEngine to shoot random values, by-passing
  //  the static generator.

  inline double fire();

  double fire( long n, double p );
  
  void fireArray ( const int size, double* vect);
  void fireArray ( const int size, double* vect,
                   long n, double p );
  inline double operator()();
  inline double operator()( long n, double p );

private:

  // Private copy constructor. Defining it here disallows use.
  RandBinomial(const RandBinomial& d);

  static double genBinomial( HepRandomEngine *anEngine, long n, double p );

  HepRandomEngine* localEngine;
  bool deleteEngine;
  const long defaultN;
  const double defaultP;
 
};

}  // namespace CLHEP

#include "CLHEP/Random/RandBinomial.icc"

#endif