// $Id: RandBreitWigner.cc,v 1.4 2003/08/13 20:00:12 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                       --- RandBreitWigner ---
//                      class implementation file
// -----------------------------------------------------------------------
// This file is part of Geant4 (simulation toolkit for HEP).

// =======================================================================
// Gabriele Cosmo - Created: 5th September 1995
//                - Added methods to shoot arrays: 28th July 1997
// J.Marraffino   - Added default arguments as attributes and
//                  operator() with arguments: 16th Feb 1998
// =======================================================================

#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandBreitWigner.h"
#include "CLHEP/Units/PhysicalConstants.h"
#include <algorithm>	// for min() and max()
#include <cmath>

using namespace std;

namespace CLHEP {

RandBreitWigner::~RandBreitWigner() {
  if ( deleteEngine ) delete localEngine;
}

RandBreitWigner::RandBreitWigner(const RandBreitWigner& right)
 : defaultA(right.defaultA), defaultB(right.defaultB)
{;}

double RandBreitWigner::operator()() {
   return fire( defaultA, defaultB );
}

double RandBreitWigner::operator()( double a, double b ) {
   return fire( a, b );
}

double RandBreitWigner::operator()( double a, double b, double c ) {
   return fire( a, b, c );
}

double RandBreitWigner::shoot(double mean, double gamma)
{
   double rval, displ;

   rval = 2.0*HepRandom::getTheEngine()->flat()-1.0;
   displ = 0.5*gamma*tan(rval*CLHEP::halfpi);

   return mean + displ;
}

double RandBreitWigner::shoot(double mean, double gamma, double cut)
{
   double val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = atan(2.0*cut/gamma);
   rval = 2.0*HepRandom::getTheEngine()->flat()-1.0;
   displ = 0.5*gamma*tan(rval*val);

   return mean + displ;
}

double RandBreitWigner::shootM2(double mean, double gamma )
{
   double val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = atan(-mean/gamma);
   rval = RandFlat::shoot(val, CLHEP::halfpi);
   displ = gamma*tan(rval);

   return sqrt(mean*mean + mean*displ);
}

double RandBreitWigner::shootM2(double mean, double gamma, double cut )
{
   double rval, displ;
   double lower, upper, tmp;

   if ( gamma == 0.0 ) return mean;
   tmp = max(0.0,(mean-cut));
   lower = atan( (tmp*tmp-mean*mean)/(mean*gamma) );
   upper = atan( ((mean+cut)*(mean+cut)-mean*mean)/(mean*gamma) );
   rval = RandFlat::shoot(lower, upper);
   displ = gamma*tan(rval);

   return sqrt(max(0.0, mean*mean + mean*displ));
}

void RandBreitWigner::shootArray ( const int size, double* vect )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot( 1.0, 0.2 );
}

void RandBreitWigner::shootArray ( const int size, double* vect,
                                   double a, double b )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot( a, b );
}

void RandBreitWigner::shootArray ( const int size, double* vect,
                                   double a, double b,
                                   double c )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot( a, b, c );
}

//----------------

double RandBreitWigner::shoot(HepRandomEngine* anEngine,
                                 double mean, double gamma)
{
   double rval, displ;

   rval = 2.0*anEngine->flat()-1.0;
   displ = 0.5*gamma*tan(rval*CLHEP::halfpi);

   return mean + displ;
}

double RandBreitWigner::shoot(HepRandomEngine* anEngine,
                                 double mean, double gamma, double cut )
{
   double val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = atan(2.0*cut/gamma);
   rval = 2.0*anEngine->flat()-1.0;
   displ = 0.5*gamma*tan(rval*val);

   return mean + displ;
}

double RandBreitWigner::shootM2(HepRandomEngine* anEngine,
                                   double mean, double gamma )
{
   double val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = atan(-mean/gamma);
   rval = RandFlat::shoot(anEngine,val, CLHEP::halfpi);
   displ = gamma*tan(rval);

   return sqrt(mean*mean + mean*displ);
}

double RandBreitWigner::shootM2(HepRandomEngine* anEngine,
                                   double mean, double gamma, double cut )
{
   double rval, displ;
   double lower, upper, tmp;

   if ( gamma == 0.0 ) return mean;
   tmp = max(0.0,(mean-cut));
   lower = atan( (tmp*tmp-mean*mean)/(mean*gamma) );
   upper = atan( ((mean+cut)*(mean+cut)-mean*mean)/(mean*gamma) );
   rval = RandFlat::shoot(anEngine, lower, upper);
   displ = gamma*tan(rval);

   return sqrt( max(0.0, mean*mean+mean*displ) );
}

void RandBreitWigner::shootArray ( HepRandomEngine* anEngine,
                                   const int size, double* vect )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot( anEngine, 1.0, 0.2 );
}

void RandBreitWigner::shootArray ( HepRandomEngine* anEngine,
                                   const int size, double* vect,
                                   double a, double b )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot( anEngine, a, b );
}

void RandBreitWigner::shootArray ( HepRandomEngine* anEngine,
                                   const int size, double* vect,
                                   double a, double b, double c )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot( anEngine, a, b, c );
}

//----------------

double RandBreitWigner::fire()
{
  return fire( defaultA, defaultB );
}

double RandBreitWigner::fire(double mean, double gamma)
{
   double rval, displ;

   rval = 2.0*localEngine->flat()-1.0;
   displ = 0.5*gamma*tan(rval*CLHEP::halfpi);

   return mean + displ;
}

double RandBreitWigner::fire(double mean, double gamma, double cut)
{
   double val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = atan(2.0*cut/gamma);
   rval = 2.0*localEngine->flat()-1.0;
   displ = 0.5*gamma*tan(rval*val);

   return mean + displ;
}

double RandBreitWigner::fireM2()
{
  return fireM2( defaultA, defaultB );
}

double RandBreitWigner::fireM2(double mean, double gamma )
{
   double val, rval, displ;

   if ( gamma == 0.0 ) return mean;
   val = atan(-mean/gamma);
   rval = RandFlat::shoot(localEngine,val, CLHEP::halfpi);
   displ = gamma*tan(rval);

   return sqrt(mean*mean + mean*displ);
}

double RandBreitWigner::fireM2(double mean, double gamma, double cut )
{
   double rval, displ;
   double lower, upper, tmp;

   if ( gamma == 0.0 ) return mean;
   tmp = max(0.0,(mean-cut));
   lower = atan( (tmp*tmp-mean*mean)/(mean*gamma) );
   upper = atan( ((mean+cut)*(mean+cut)-mean*mean)/(mean*gamma) );
   rval = RandFlat::shoot(localEngine,lower, upper);
   displ = gamma*tan(rval);

   return sqrt(max(0.0, mean*mean + mean*displ));
}

void RandBreitWigner::fireArray ( const int size, double* vect)
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire(defaultA, defaultB );
}

void RandBreitWigner::fireArray ( const int size, double* vect,
                                  double a, double b )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire( a, b );
}

void RandBreitWigner::fireArray ( const int size, double* vect,
                                  double a, double b, double c )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire( a, b, c );
}

}  // namespace CLHEP
