// $Id: RandBreitWigner.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                        --- RandBreitWigner ---
//                           class header file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).
//
// Class defining methods for shooting numbers according to the
// Breit-Wigner distribution algorithms (plain or mean^2).
// Default values are set: mean=1, gamma=.2, cut=1.
// Plain algorithm is used for shootArray() and fireArray().
// Plain algorithm with default values is used for operator()(). 

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Added methods to shoot arrays: 28th July 1997
// J.Marraffino   - Added default arguments as attributes and
//                  operator() with arguments: 16th Feb 1998
// =======================================================================

#ifndef RandBreitWigner_h
#define RandBreitWigner_h 1

#include "CLHEP/Random/RandFlat.h"

/**
 * @author <Gabriele.Cosmo@cern.ch>
 * @ingroup random
 */
class RandBreitWigner : public HepRandom {

public:

  inline RandBreitWigner ( HepRandomEngine& anEngine, double a=1.0,
                                       double b=0.2 );
  inline RandBreitWigner ( HepRandomEngine* anEngine, double a=1.0,
                                       double b=0.2 );
  // These constructors should be used to instantiate a RandBreitWigner
  // distribution object defining a local engine for it.
  // The static generator will be skipped using the non-static methods
  // defined below.
  // If the engine is passed by pointer the corresponding engine object
  // will be deleted by the RandBreitWigner destructor.
  // If the engine is passed by reference the corresponding engine object
  // will not be deleted by the RandBreitWigner destructor.

  virtual ~RandBreitWigner();
  // Destructor

  // Static methods to shoot random values using the static generator

  static  double shoot( double a=1.0, double b=0.2 );

  static  double shoot( double a, double b, double c );

  static  double shootM2( double a=1.0, double b=0.2 );

  static  double shootM2( double a, double b, double c );

  static  void shootArray ( const int size, double* vect);

  static  void shootArray ( const int size, double* vect,
                            double a, double b );

  static  void shootArray ( const int size, double* vect,
                            double a, double b, double c );
                           
  //  Static methods to shoot random values using a given engine
  //  by-passing the static generator.

  static  double shoot( HepRandomEngine* anEngine, double a=1.0,
                           double b=0.2 );
  static  double shoot( HepRandomEngine* anEngine, double a,
                           double b, double c );
  static  double shootM2( HepRandomEngine* anEngine, double a=1.0,
                             double b=0.2 );
  static  double shootM2( HepRandomEngine* anEngine, double a,
                             double b, double c );
  static  void shootArray ( HepRandomEngine* anEngine,
                            const int size, double* vect );
  static  void shootArray ( HepRandomEngine* anEngine,
                            const int size, double* vect,
                            double a, double b );
  static  void shootArray ( HepRandomEngine* anEngine,
                            const int size, double* vect,
                            double a, double b, double c );

  //  Methods using the localEngine to shoot random values, by-passing
  //  the static generator. These methods respect distribution parameters
  //  passed by the user at instantiation unless superseded by actual
  //  arguments in the call.

  double fire();

  double fire( double a, double b );

  double fire( double a, double b, double c );

  double fireM2();

  double fireM2( double a, double b );

  double fireM2( double a, double b, double c );

  void fireArray ( const int size, double* vect);

  void fireArray ( const int size, double* vect,
                   double a, double b );

  void fireArray ( const int size, double* vect,
                   double a, double b, double c );
  double operator()();
  double operator()( double a, double b );
  double operator()( double a, double b, double c );
  
private:

  // Private copy constructor. Defining it here disallows use.
  RandBreitWigner(const RandBreitWigner& d);

  HepRandomEngine* localEngine;
  bool deleteEngine;
  const double defaultA;
  const double defaultB;

};

#include "CLHEP/Random/RandBreitWigner.icc"

#endif
