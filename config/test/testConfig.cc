// -*- C++ -*-
// $Id: testConfig.cc,v 1.1.2.4 2004/11/29 18:41:24 pfeiffer Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a small program for testing min(), max(), sqr(), abs()
// function templates.
//

#include <cmath>
#include <iostream>
#include <assert.h>
#include "CLHEP/config/TemplateFunctions.h"
#include "CLHEP/config/CLHEP.h"

int main() {
  int          ia=-3;
  const int    ib=4;
  float        fa=-3.;
  const float  fb=4.;
  double       da=-3.;
  const double db=4.;
  double       mpi = M_PI;

  // test M_PI and HepStd
  HepStd::cout << "pi mass is " << mpi << HepStd::endl;

  // Test min()

  assert(min(3,4)   ==  3);
  assert(min(ia,ib) == -3);
  assert(min(3.,4.) ==  3.);
  assert(min(fa,fb) == -3.);
  assert(min(da,db) == -3.);

  // Test max()

  assert(max(3,4)   == 4);
  assert(max(ia,ib) == 4);
  assert(max(3.,4.) == 4.);
  assert(max(fa,fb) == 4.);
  assert(max(da,db) == 4.);

  // Test sqr()

  assert(sqr(3)  == 9);
  assert(sqr(ia) == 9);
  assert(sqr(ib) == 16);
  assert(sqr(3.) == 9.);
  assert(sqr(fa) == 9.);
  assert(sqr(fb) == 16.);
  assert(sqr(da) == 9.);
  assert(sqr(db) == 16.);

  // Test abs()

  assert(abs(3)  == 3); 
  assert(abs(ia) == 3);
  assert(abs(ib) == 4);
  assert(abs(3.) == 3.);
  assert(abs(fa) == 3.);
  assert(abs(fb) == 4.);
  assert(abs(da) == 3.);
  assert(abs(db) == 4.);

  return 0;
}