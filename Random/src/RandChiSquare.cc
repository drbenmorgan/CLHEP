// $Id: RandChiSquare.cc,v 1.2 2003/07/17 19:20:02 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandChiSquare ---
//                      class implementation file
// -----------------------------------------------------------------------

// =======================================================================
// John Marraffino - Created: 12th May 1998
// =======================================================================

#include "CLHEP/Random/RandChiSquare.h"
#include <cmath>	// for log()

namespace CLHEP {

RandChiSquare::~RandChiSquare() {
  if ( deleteEngine ) delete localEngine;
}

RandChiSquare::RandChiSquare(const RandChiSquare& right)
 : defaultA(right.defaultA)
{;}

double RandChiSquare::shoot( HepRandomEngine *anEngine,  double a ) {
  return genChiSquare( anEngine, a );
}

double RandChiSquare::shoot( double a ) {
  HepRandomEngine *anEngine = HepRandom::getTheEngine();
  return genChiSquare( anEngine, a );
}

double RandChiSquare::fire( double a ) {
  return genChiSquare( localEngine, a );
}

void RandChiSquare::shootArray( const int size, double* vect,
                            double a ) {
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(a);
}

void RandChiSquare::shootArray( HepRandomEngine* anEngine,
                            const int size, double* vect,
                            double a )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(anEngine,a);
}

void RandChiSquare::fireArray( const int size, double* vect) {
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire(defaultA);
}

void RandChiSquare::fireArray( const int size, double* vect,
                           double a ) {
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire(a);
}

double RandChiSquare::genChiSquare( HepRandomEngine *anEngine,
                                       double a ) {
/******************************************************************
 *                                                                *
 *        Chi Distribution - Ratio of Uniforms  with shift        *
 *                                                                *
 ******************************************************************
 *                                                                *
 * FUNCTION :   - chru samples a random number from the Chi       *
 *                distribution with parameter  a > 1.             *
 * REFERENCE :  - J.F. Monahan (1987): An algorithm for           *
 *                generating chi random variables, ACM Trans.     *
 *                Math. Software 13, 168-172.                     *
 * SUBPROGRAM : - anEngine  ... pointer to a (0,1)-Uniform        *
 *                engine                                          *
 *                                                                *
 * Implemented by R. Kremer, 1990                                 *
 ******************************************************************/

 static double a_in = -1.0,b,vm,vp,vd;
 double u,v,z,zz,r;

// Check for invalid input value

 if( a < 1 )  return (-1.0);

 if (a == 1)
  {
   for(;;)
    {
     u = anEngine->flat();
     v = anEngine->flat() * 0.857763884960707;
     z = v / u;
     if (z < 0) continue;
     zz = z * z;
     r = 2.5 - zz;
     if (z < 0.0) r = r + zz * z / (3.0 * z);
     if (u < r * 0.3894003915) return(z*z);
     if (zz > (1.036961043 / u + 1.4)) continue;
     if (2 * log(u) < (- zz * 0.5 )) return(z*z);
     }
   }
 else
  {
   if (a != a_in)
    {
     b = sqrt(a - 1.0);
     vm = - 0.6065306597 * (1.0 - 0.25 / (b * b + 1.0));
     vm = (-b > vm)? -b : vm;
     vp = 0.6065306597 * (0.7071067812 + b) / (0.5 + b);
     vd = vp - vm;
     a_in = a;
     }
   for(;;)
    {
     u = anEngine->flat();
     v = anEngine->flat() * vd + vm;
     z = v / u;
     if (z < -b) continue;
     zz = z * z;
     r = 2.5 - zz;
     if (z < 0.0) r = r + zz * z / (3.0 * (z + b));
     if (u < r * 0.3894003915) return((z + b)*(z + b));
     if (zz > (1.036961043 / u + 1.4)) continue;
     if (2 * log(u) < (log(1.0 + z / b) * b * b - zz * 0.5 - z * b)) return((z + b)*(z + b));
     }
   }
}

}  // namespace CLHEP

