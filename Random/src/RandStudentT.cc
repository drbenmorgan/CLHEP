// $Id: RandStudentT.cc,v 1.4.4.1 2005/03/18 22:26:48 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandStudentT ---
//                      class implementation file
// -----------------------------------------------------------------------

// =======================================================================
// John Marraffino - Created: 12th May 1998
// G.Cosmo         - Fixed minor bug on inline definition for shoot()
//                   methods : 20th Aug 1998
// M Fischler      - put and get to/from streams 12/13/04
// =======================================================================

#include <float.h>
#include <cmath>	// for log() exp()
#include "CLHEP/Random/defs.h"
#include "CLHEP/Random/RandStudentT.h"

namespace CLHEP {

std::string RandStudentT::name() const {return "RandStudentT";}
HepRandomEngine & RandStudentT::engine() {return *localEngine;}

RandStudentT::~RandStudentT() {
  if ( deleteEngine ) delete localEngine;
}

RandStudentT::RandStudentT(const RandStudentT& right)
 : defaultA(right.defaultA)
{;}

double RandStudentT::operator()() {
  return fire( defaultA );
}

double RandStudentT::operator()( double a ) {
  return fire( a );
}

double RandStudentT::shoot( double a ) {
/******************************************************************
 *                                                                *
 *           Student-t Distribution - Polar Method                *
 *                                                                *
 ******************************************************************
 *                                                                *
 * The polar method of Box/Muller for generating Normal variates  *
 * is adapted to the Student-t distribution. The two generated    *
 * variates are not independent and the expected no. of uniforms  *
 * per variate is 2.5464.                                         *
 *                                                                *
 ******************************************************************
 *                                                                *
 * FUNCTION :   - tpol  samples a random number from the          *
 *                Student-t distribution with parameter a > 0.    *
 * REFERENCE :  - R.W. Bailey (1994): Polar generation of random  *
 *                variates with the t-distribution, Mathematics   *
 *                of Computation 62, 779-781.                     *
 * SUBPROGRAM : -  ... (0,1)-Uniform generator                    *
 *                                                                *
 *                                                                *
 * Implemented by F. Niederl, 1994                                *
 ******************************************************************/

 double u,v,w;

// Check for valid input value

 if( a < 0.0) return (DBL_MAX);

 do
 {
	 u = 2.0 * HepRandom::getTheEngine()->flat() - 1.0;
	 v = 2.0 * HepRandom::getTheEngine()->flat() - 1.0;
 }
 while ((w = u * u + v * v) > 1.0);

 return(u * sqrt( a * ( exp(- 2.0 / a * log(w)) - 1.0) / w));
}

void RandStudentT::shootArray( const int size, double* vect,
                            double a )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(a);
}

void RandStudentT::shootArray( HepRandomEngine* anEngine,
                            const int size, double* vect,
                            double a )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = shoot(anEngine,a);
}

double RandStudentT::fire( double a ) {

 double u,v,w;

 do
 {
	 u = 2.0 * localEngine->flat() - 1.0;
	 v = 2.0 * localEngine->flat() - 1.0;
 }
 while ((w = u * u + v * v) > 1.0);

 return(u * sqrt( a * ( exp(- 2.0 / a * log(w)) - 1.0) / w));
}

void RandStudentT::fireArray( const int size, double* vect)
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire(defaultA);
}

void RandStudentT::fireArray( const int size, double* vect,
                           double a )
{
   int i;

   for (i=0; i<size; ++i)
     vect[i] = fire(a);
}

double RandStudentT::shoot( HepRandomEngine *anEngine, double a ) {

 double u,v,w;

 do
 {
	 u = 2.0 * anEngine->flat() - 1.0;
	 v = 2.0 * anEngine->flat() - 1.0;
 }
 while ((w = u * u + v * v) > 1.0);

 return(u * sqrt( a * ( exp(- 2.0 / a * log(w)) - 1.0) / w));
}

std::ostream & RandStudentT::put ( std::ostream & os ) const {
  int pr=os.precision(20);
  os << " " << name() << "\n";
  os << defaultA << "\n";
  os.precision(pr);
  return os;
}

std::istream & RandStudentT::get ( std::istream & is ) {
  std::string inName;
  is >> inName;
  if (inName != name()) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "Mismatch when expecting to read state of a "
    	      << name() << " distribution\n"
	      << "Name found was " << inName
	      << "\nistream is left in the badbit state\n";
    return is;
  }
  is >> defaultA;
  return is;
}

}  // namespace CLHEP
