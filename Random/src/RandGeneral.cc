// $Id: RandGeneral.cc,v 1.3 2003/07/25 20:59:21 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandGeneral ---
//                      class implementation file
// -----------------------------------------------------------------------

// =======================================================================
// S.Magni & G.Pieri - Created: 5th September 1995
// G.Cosmo           - Added constructor using default engine from the
//                     static generator. Simplified shoot() and
//                     shootArray() (not needed in principle!): 20th Aug 1998
// M.G.Pia & G.Cosmo - Fixed bug in computation of theIntegralPdf in
//                     two constructors: 5th Jan 1999
// S.Magni & G.Pieri - Added linear interpolation: 24th Mar 1999
// M. Fischler	     - General cleanup: 14th May 1999
//			+ Eliminated constructor code replication by factoring 
//			  common code into prepareTable.
//			+ Eliminated fire/shoot code replication by factoring 
//			  out common code into mapRandom.  
//			+ A couple of methods are moved inline to avoid a 
//			  speed cost for factoring out mapRandom:  fire()
//			  and shoot(anEngine).
//			+ Inserted checks for negative weight and zero total 
//			  weight in the bins.
//			+ Modified the binary search loop to avoid incorrect
//			  behavior when rand is example on a boundary.
//			+ Moved the check of InterpolationType up into 
//			  the constructor.  A type other than 0 or 1
//			  will give the interpolated distribution (instead of
//			  a distribution that always returns 0).
//			+ Modified the computation of the returned value
//			  to use algeraic simplification to improve speed.
//			  Eliminated two of the three divisionns, made
//			  use of the fact that nabove-nbelow is always 1, etc.
//			+ Inserted a check for rand hitting the boundary of a
//			  zero-width bin, to avoid dividing 0/0.  
// M. Fischler	      - Minor correction in assert 31 July 2001
//			+ changed from assert (above = below+1) to ==
//
// =======================================================================

#include "Random/defs.h"
#include "CLHEP/Random/RandGeneral.h"
#include <assert.h>

namespace CLHEP {


//////////////////
// Constructors
//////////////////

RandGeneral::RandGeneral( const double* aProbFunc, 
			  int theProbSize, 
			  int IntType  )
  : deleteEngine(false), 
    nBins(theProbSize), 
    InterpolationType(IntType)
{
  localEngine = HepRandom::getTheEngine();
  prepareTable(aProbFunc);
}

RandGeneral::RandGeneral(HepRandomEngine& anEngine,
                         const double* aProbFunc, 
			 int theProbSize, 
			 int IntType  )
: localEngine(&anEngine), 
  deleteEngine(false), 
  nBins(theProbSize),
  InterpolationType(IntType)
{
  prepareTable(aProbFunc);
}

RandGeneral::RandGeneral(HepRandomEngine* anEngine,
                         const double* aProbFunc, 
			 int theProbSize, 
			 int IntType )
: localEngine(anEngine), 
  deleteEngine(true), 
  nBins(theProbSize),
  InterpolationType(IntType)
{
  prepareTable(aProbFunc);
}

void RandGeneral::prepareTable(const double* aProbFunc) {
//
// Private method called only by constructors.  Prepares theIntegralPdf.
//
  if (nBins < 1) {
    std::cerr << 
	"RandGeneral constructed with no bins - will use flat distribution\n";
    useFlatDistribution();
    return;
  }

  theIntegralPdf = new double[nBins+1];
  theIntegralPdf[0] = 0;
  register int ptn;
  register double weight;

  for ( ptn = 0; ptn<nBins; ++ptn ) {
    weight = aProbFunc[ptn];
    if ( weight < 0 ) {
    // We can't stomach negative bin contents, they invalidate the 
    // search algorithm when the distribution is fired.
      std::cerr << 
	"RandGeneral constructed with negative-weight bin " << ptn <<
	" = " << weight << " \n   -- will substitute 0 weight \n";
      weight = 0;
    }
    // std::cout << ptn << "  " << weight << "  " << theIntegralPdf[ptn] << "\n";
    theIntegralPdf[ptn+1] = theIntegralPdf[ptn] + weight;
  } 

  if ( theIntegralPdf[nBins] <= 0 ) {
    std::cerr << 
      "RandGeneral constructed nothing in bins - will use flat distribution\n";
    delete [] (theIntegralPdf);
    useFlatDistribution();
    return;
  }

  for ( ptn = 0; ptn < nBins+1; ++ptn ) {
    theIntegralPdf[ptn] /= theIntegralPdf[nBins];
    // std::cout << ptn << "  " << theIntegralPdf[ptn] << "\n";
  }

  // And another useful variable is ...
  oneOverNbins = 1.0 / nBins;

  // One last chore:

  if ( (InterpolationType != 0) && (InterpolationType != 1) ) {
    std::cerr << 
      "RandGeneral does not recognize IntType " << InterpolationType 
      << "\n WIll use type 0 (continuous linear interpolation \n";
    InterpolationType = 0;
  }

} // prepareTable()

void RandGeneral::useFlatDistribution() {
//
// Private method called only by prepareTables in case of user error. 
//
    nBins = 1;
    theIntegralPdf = new double[2];
    theIntegralPdf[0] = 0;
    theIntegralPdf[1] = 1;
    oneOverNbins = 1.0;
    return;

} // UseFlatDistribution()

//////////////////
//  Destructor
//////////////////

RandGeneral::~RandGeneral() {
  if ( deleteEngine ) delete localEngine;
  delete [] theIntegralPdf;
}


///////////////////
//  mapRandom(rand)
///////////////////

double RandGeneral::mapRandom(double rand) const {
//
// Private method to take the random (however it is created) and map it
// according to the distribution.
//

  int nbelow = 0;	  // largest k such that I[k] is known to be <= rand
  int nabove = nBins;  // largest k such that I[k] is known to be >  rand
  int middle;
  
  while (nabove > nbelow+1) {
    middle = (nabove + nbelow+1)>>1;
    if (rand >= theIntegralPdf[middle]) {
      nbelow = middle;
    } else {
      nabove = middle;
    }
  } // after this loop, nabove is always nbelow+1 and they straddle rad:
    assert ( nabove == nbelow+1 );
    assert ( theIntegralPdf[nbelow] <= rand );
    assert ( theIntegralPdf[nabove] >= rand );  
		// If a defective engine produces rand=1, that will 
		// still give sensible results so we relax the > rand assertion

  if ( InterpolationType == 1 ) {

    return nbelow * oneOverNbins;

  } else {

    double binMeasure = theIntegralPdf[nabove] - theIntegralPdf[nbelow];
    // binMeasure is always aProbFunc[nbelow], 
    // but we don't have aProbFunc any more so we subtract.

    if ( binMeasure == 0 ) { 
	// rand lies right in a bin of measure 0.  Simply return the center
	// of the range of that bin.  (Any value between k/N and (k+1)/N is 
	// equally good, in this rare case.)
        return (nbelow + .5) * oneOverNbins;
    }

    double binFraction = (rand - theIntegralPdf[nbelow]) / binMeasure;

    return (nbelow + binFraction) * oneOverNbins;
  }

} // mapRandom(rand)


 
void RandGeneral::shootArray( HepRandomEngine* anEngine,
                            const int size, double* vect )
{
   register int i;

   for (i=0; i<size; ++i) {
     vect[i] = shoot(anEngine);
   }
}

void RandGeneral::fireArray( const int size, double* vect )
{
   register int i;

  for (i=0; i<size; ++i) {
     vect[i] = fire();
  }
}

}  // namespace CLHEP
