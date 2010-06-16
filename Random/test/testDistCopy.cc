// -*- C++ -*-
// $Id: testDistCopy.cc,v 1.2 2010/06/16 17:24:53 garren Exp $
// ----------------------------------------------------------------------

// ======================================================================
//
//
// testDistCopy -- test copied random distributions
//
// ======================================================================

// ----------------------------------------------------------------------
// Engines:
#include "CLHEP/Random/DualRand.h"            // CLHEP::DualRand
#include "CLHEP/Random/MTwistEngine.h"        // CLHEP::MTwistEngine

// ----------------------------------------------------------------------
// Distributions:
#include "CLHEP/Random/RandBinomial.h"        // CLHEP::RandBinomial
#include "CLHEP/Random/RandBreitWigner.h"     // CLHEP::RandBreitWigner
#include "CLHEP/Random/RandChiSquare.h"       // CLHEP::RandChiSquare
#include "CLHEP/Random/RandExponential.h"     // CLHEP::RandExponential
#include "CLHEP/Random/RandFlat.h"            // CLHEP::RandFlat
#include "CLHEP/Random/RandGamma.h"           // CLHEP::RandGamma
#include "CLHEP/Random/RandGauss.h"           // CLHEP::RandGauss
#include "CLHEP/Random/RandGaussQ.h"          // CLHEP::RandGaussQ
#include "CLHEP/Random/RandGaussT.h"          // CLHEP::RandGaussT
#include "CLHEP/Random/RandGeneral.h"         // CLHEP::RandGeneral
#include "CLHEP/Random/RandLandau.h"          // CLHEP::RandLandau
#include "CLHEP/Random/RandPoissonQ.h"        // CLHEP::RandPoissonQ
#include "CLHEP/Random/RandPoissonT.h"        // CLHEP::RandPoissonT
#include "CLHEP/Random/RandStudentT.h"        // CLHEP::RandStudentT

// ----------------------------------------------------------------------
// Standard library:
#include <sstream>  // for ostringstream
#include <string>   // for string


using namespace CLHEP;
typedef  unsigned int  uint;


// ----------------------------------------------------------------------
// copy-construction test

template< typename Dist >
bool
  copy_constructor_is_okay( Dist & d1 )
{
  // prime the distribution
  for( uint i = 0u;  i != 17u;  ++i )
    (void) d1.fire();

  // capture its state
  std::ostringstream  os1;
  d1.put( os1 );
  HepRandomEngine *  e1  =  & d1.engine();

  // make a copy and capture the copy's state
  Dist  d2( d1 );
  std::ostringstream  os2;
  d2.put( os2 );
  HepRandomEngine *  e2  =  & d2.engine();

  // do the saved states match and is the underlying engine shared?
  return os1.str() == os2.str()  &&  e1 == e2;
}  // copy_constructor_is_okay<>()


// ----------------------------------------------------------------------
// copy-construction test

template< typename Dist >
bool
  copy_assignment_is_okay( Dist & d1, Dist & d2 )
{
  // prime the distributions
  for( uint i = 0u;  i != 17u;  ++i )
    (void) d1.fire();
  for( uint i = 0u;  i != 19u;  ++i )
    (void) d2.fire();

  // capture d1's state
  std::ostringstream  os1;
  d1.put( os1 );
  HepRandomEngine *  e1  =  & d1.engine();

  // make a copy and capture the copy's state
  d2 = d1;
  std::ostringstream  os2;
  d2.put( os2 );
  HepRandomEngine *  e2  =  & d2.engine();

  // do the saved states match and is the underlying engine shared?
  return os1.str() == os2.str()  &&  e1 == e2;
}  // copy_assignment_is_okay<>()


// ----------------------------------------------------------------------
// Mask bits to form a word identifying dists that failed their test

static  uint const  success              =  0u;
static  uint const  Binomial_failure     =  1u <<  1;
static  uint const  BreitWigner_failure  =  1u <<  2;
static  uint const  ChiSquare_failure    =  1u <<  3;
static  uint const  Exponential_failure  =  1u <<  4;
static  uint const  Flat_failure         =  1u <<  5;
static  uint const  Gamma_failure        =  1u <<  6;
static  uint const  Gauss_failure        =  1u <<  7;
static  uint const  GaussQ_failure       =  1u <<  8;
static  uint const  GaussT_failure       =  1u <<  9;
static  uint const  General_failure      =  1u << 10;
static  uint const  Landau_failure       =  1u << 11;
static  uint const  Poisson_failure      =  1u << 12;
static  uint const  PoissonQ_failure     =  1u << 13;
static  uint const  PoissonT_failure     =  1u << 14;
static  uint const  StudentT_failure     =  1u << 15;


// ----------------------------------------------------------------------
// RandBinomial

uint  testRandBinomial()
{
  MTwistEngine  r1( 97531L );
  RandBinomial  d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return Binomial_failure;

  DualRand      r2( 13579L );
  RandBinomial  d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return Binomial_failure;

  return 0u;
}


// ----------------------------------------------------------------------
// RandBreitWigner

uint  testRandBreitWigner()
{
  MTwistEngine     r1( 97531L );
  RandBreitWigner  d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return BreitWigner_failure;

  DualRand         r2( 13579L );
  RandBreitWigner  d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return BreitWigner_failure;

  return 0u;
}  // testRandBreitWigner


// ----------------------------------------------------------------------
// RandChiSquare

uint  testRandChiSquare()
{
  MTwistEngine   r1( 97531L );
  RandChiSquare  d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return ChiSquare_failure;

  DualRand       r2( 13579L );
  RandChiSquare  d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return ChiSquare_failure;

  return 0u;
}  // testRandChiSquare


// ----------------------------------------------------------------------
// RandExponential

uint  testRandExponential()
{
  MTwistEngine     r1( 97531L );
  RandExponential  d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return Exponential_failure;

  DualRand         r2( 13579L );
  RandExponential  d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return Exponential_failure;

  return 0u;
}  // testRandExponential


// ----------------------------------------------------------------------
// RandFlat

uint  testRandFlat()
{
  MTwistEngine  r1( 97531L );
  RandFlat      d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return Flat_failure;

  DualRand      r2( 13579L );
  RandFlat      d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return Flat_failure;

  return 0u;
}  // testRandFlat


// ----------------------------------------------------------------------
// RandGamma

uint  testRandGamma()
{
  MTwistEngine  r1( 97531L );
  RandGamma     d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return Gamma_failure;

  DualRand      r2( 13579L );
  RandGamma     d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return Gamma_failure;

  return 0u;
}  // testRandGamma


// ----------------------------------------------------------------------
// RandGauss

uint  testRandGauss()
{
  MTwistEngine  r1( 97531L );
  RandGauss     d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return Gauss_failure;

  DualRand      r2( 13579L );
  RandGauss     d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return Gauss_failure;

  return 0u;
}  // testRandGauss


// ----------------------------------------------------------------------
// RandGaussQ

uint  testRandGaussQ()
{
  MTwistEngine  r1( 97531L );
  RandGaussQ    d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return GaussQ_failure;

  DualRand      r2( 13579L );
  RandGaussQ    d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return GaussQ_failure;

  return 0u;
}  // testRandGaussQ


// ----------------------------------------------------------------------
// RandGaussT

uint  testRandGaussT()
{
  MTwistEngine  r1( 97531L );
  RandGaussT    d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return GaussT_failure;

  DualRand      r2( 13579L );
  RandGaussT    d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return GaussT_failure;

  return 0u;
}  // testRandGaussT


// ----------------------------------------------------------------------
// RandGeneral

uint  testRandGeneral()
{
  MTwistEngine  r1( 97531L );
  double        pdf1[] = { 1.5, 2.5, 3.0, 4.25, 5.65 };
  RandGeneral   d1( r1, pdf1, sizeof(pdf1)/sizeof(pdf1[0]) );
  if( ! copy_constructor_is_okay(d1) )  return General_failure;

  DualRand      r2( 13579L );
  double        pdf2[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 0.60 };
  RandGeneral   d2( r2, pdf2, sizeof(pdf2)/sizeof(pdf2[0]) );
  if( ! copy_assignment_is_okay(d1,d2) )  return General_failure;

  return 0u;
}  // testRandGeneral


// ----------------------------------------------------------------------
// RandLandau

uint  testRandLandau()
{
  MTwistEngine  r1( 97531L );
  RandLandau    d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return Landau_failure;

  DualRand      r2( 13579L );
  RandLandau    d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return Landau_failure;

  return 0u;
}  // testRandLandau


// ----------------------------------------------------------------------
// RandPoisson

uint  testRandPoisson()
{
  MTwistEngine  r1( 97531L );
  RandPoisson   d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return Poisson_failure;

  DualRand      r2( 13579L );
  RandPoisson   d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return Poisson_failure;

  return 0u;
}  // testRandPoisson


// ----------------------------------------------------------------------
// RandPoissonQ

uint  testRandPoissonQ()
{
  MTwistEngine  r1( 97531L );
  RandPoissonQ  d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return PoissonQ_failure;

  DualRand      r2( 13579L );
  RandPoissonQ  d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return PoissonQ_failure;

  return 0u;
}  // testRandPoissonQ


// ----------------------------------------------------------------------
// RandPoissonT

uint  testRandPoissonT()
{
  MTwistEngine  r1( 97531L );
  RandPoissonT  d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return PoissonT_failure;

  DualRand      r2( 13579L );
  RandPoissonT  d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return PoissonT_failure;

  return 0u;
}  // testRandPoissonT


// ----------------------------------------------------------------------
// RandStudentT

uint  testRandStudentT()
{
  MTwistEngine  r1( 97531L );
  RandStudentT  d1( r1 );
  if( ! copy_constructor_is_okay(d1) )  return StudentT_failure;

  DualRand      r2( 13579L );
  RandStudentT  d2( r2 );
  if( ! copy_assignment_is_okay(d1,d2) )  return StudentT_failure;

  return 0u;
}  // testRandStudentT


// ----------------------------------------------------------------------
// main

int  main()
{
  uint  mask = 0u
             | testRandBinomial   ()
             | testRandBreitWigner()
             | testRandChiSquare  ()
             | testRandExponential()
             | testRandFlat       ()
             | testRandGamma      ()
             | testRandGauss      ()
             | testRandGaussQ     ()
             | testRandGaussT     ()
             | testRandGeneral    ()
             | testRandLandau     ()
             | testRandPoisson    ()
             | testRandPoissonQ   ()
             | testRandPoissonT   ()
             | testRandStudentT   ()
             ;

  return - int(mask);
}

