// $Id: RandGaussT.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// -*- C++ -*-
//
// -----------------------------------------------------------------------
//                             HEP Random
//                          --- RandGaussT ---
//                      class implementation file
// -----------------------------------------------------------------------

// =======================================================================
// M Fischler	  - Created 04 Feb 2000
// =======================================================================

#include "Random/defs.h"
#include "CLHEP/Random/RandGaussT.h"
#include <iostream>

RandGaussT::~RandGaussT() {
}

RandGaussT::RandGaussT(const RandGaussT& right) :  RandGauss(right) {
}

double RandGaussT::operator()() {
  return HepStat::flatToGaussian(getTheEngine()->flat()) * defaultStdDev 
								+ defaultMean;
}

double RandGaussT::operator()( double mean, double stdDev ) {
  return HepStat::flatToGaussian(getTheEngine()->flat()) * stdDev + mean;
}

void RandGaussT::shootArray( const int size, double* vect,
                            double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = shoot(mean,stdDev);
   }
}

void RandGaussT::shootArray( HepRandomEngine* anEngine,
                            const int size, double* vect,
                            double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = shoot(anEngine,mean,stdDev);
   }
}

void RandGaussT::fireArray( const int size, double* vect)
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = fire( defaultMean, defaultStdDev );
   }
}

void RandGaussT::fireArray( const int size, double* vect,
                           double mean, double stdDev )
{
   int i;

   for (i=0; i<size; ++i) {
     vect[i] = fire( mean, stdDev );
   }
}

