// $Id: RandGaussQ.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandGaussQ ---
//                      class implementation file
// -----------------------------------------------------------------------

// =======================================================================
// M Fischler	  - Created 24 Jan 2000
// =======================================================================

#include "Random/defs.h"
#include "CLHEP/Random/RandGaussQ.h"
#include <iostream>
#include <cmath>	// for log()

RandGaussQ::~RandGaussQ() {
}

RandGaussQ::RandGaussQ(const RandGaussQ& right) :  RandGauss(right) {
}

double RandGaussQ::operator()() {
  return transformQuick(getTheEngine()->flat()) * defaultStdDev + defaultMean;
}

double RandGaussQ::operator()( double mean, double stdDev ) {
  return transformQuick(getTheEngine()->flat()) * stdDev + mean;
}

void RandGaussQ::shootArray( const int size, double* vect,
                            double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = shoot(mean,stdDev);
   }
}

void RandGaussQ::shootArray( HepRandomEngine* anEngine,
                            const int size, double* vect,
                            double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = shoot(anEngine,mean,stdDev);
   }
}

void RandGaussQ::fireArray( const int size, double* vect)
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = fire( defaultMean, defaultStdDev );
   }
}

void RandGaussQ::fireArray( const int size, double* vect,
                           double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = fire( mean, stdDev );
   }
}


//
// Table of errInts, for use with transform(r) and quickTransform(r)
//

// Since all these are this is static to this compilation unit only, the 
// info is establised a priori and not at each invocation.

// The main data is of course the gaussQTables table; the rest is all 
// bookkeeping to know what the tables mean.

#define Table0size   250
#define Table1size  1000
#define TableSize   (Table0size+Table1size)

#define Table0step  (2.0E-6) 
#define Table1step  (5.0E-4)

#define Table0scale   (1.0/Table1step)

#define Table0offset 0
#define Table1offset (Table0size)

  // Here comes the big (5K bytes) table, kept in a file ---

static const float gaussTables [TableSize] = {
#include "gaussQTables.cdat"
};



double RandGaussQ::transformQuick (double r) {

  double sign = +1.0;	// We always compute a negative number of 
				// sigmas.  For r > 0 we will multiply by
				// sign = -1 to return a positive number.
  if ( r > .5 ) {
    r = 1-r;
    sign = -1.0;
  } 

  register int index;
  double  dx;

  if ( r >= Table1step ) { 
    index = int((Table1size<<1) * r);	// 1 to Table1size
    if (index == Table1size) return 0.0;
    dx = (Table1size<<1) * r - index; 		// fraction of way to next bin
    index += Table1offset-1;	
  } else if ( r > Table0step ) {
    double rr = r * Table0scale;
    index = int(Table0size * rr);		// 1 to Table0size
    dx = Table0size * rr - index; 		// fraction of way to next bin
    index += Table0offset-1;	
  } else {    				// r <= Table0step - not in tables
    return sign*transformSmall(r);	
  }				

  double y0 = gaussTables [index++];
  double y1 = gaussTables [index];
  
  return (float) (sign * ( y1 * dx + y0 * (1.0-dx) ));

} // transformQuick()



double RandGaussQ::transformSmall (double r) {

  // Solve for -v in the asymtotic formula 
  //
  // errInt (-v) =  exp(-v*v/2)         1     1*3    1*3*5
  //		   ------------ * (1 - ---- + ---- - ----- + ... )
  //		   v*sqrt(2*pi)        v**2   v**4   v**6

  // The value of r (=errInt(-v)) supplied is going to less than 2.0E-13,
  // which is such that v < -7.25.  Since the value of r is meaningful only
  // to an absolute error of 1E-16 (double precision accuracy for a number 
  // which on the high side could be of the form 1-epsilon), computing
  // v to more than 3-4 digits of accuracy is suspect; however, to ensure 
  // smoothness with the table generator (which uses quite a few terms) we
  // also use terms up to 1*3*5* ... *13/v**14, and insist on accuracy of
  // solution at the level of 1.0e-7.

  // This routine is called less than one time in a million firings, so
  // speed is of no concern.  As a matter of technique, we terminate the
  // iterations in case they would be infinite, but this should not happen.

  double eps = 1.0e-7;
  double guess = 7.5;
  double v;
  
  for ( int i = 1; i < 50; i++ ) {
    double vn2 = 1.0/(guess*guess);
    double s = -13*11*9*7*5*3 * vn2*vn2*vn2*vn2*vn2*vn2*vn2;
    	      s +=    11*9*7*5*3 * vn2*vn2*vn2*vn2*vn2*vn2;
    	      s +=      -9*7*5*3 * vn2*vn2*vn2*vn2*vn2;
	      s +=         7*5*3 * vn2*vn2*vn2*vn2;
    	      s +=          -5*3 * vn2*vn2*vn2;
	      s += 	       3 * vn2*vn2    - vn2  +    1.0;
    v = sqrt ( 2.0 * log ( s / (r*guess*sqrt(2.0*M_PI)) ) );
    if ( fabs(v-guess) < eps ) break;
    guess = v;
  }
 
  return -v;

} // transformSmall()
