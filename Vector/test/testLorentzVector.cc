// -*- C++ -*-
// $Id: testLorentzVector.cc,v 1.2 2003/08/13 20:00:14 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of what might become CLHEP -
// a Class Library for High Energy Physics.
//
// This is a small program for testing the HepLorentzVector class
// and the interaction with the HepLorentzRotation class.
//

#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/LorentzRotation.h"
#include "CLHEP/Vector/Sqr.h"
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <assert.h>

using namespace CLHEP;

#define DEPS 1.0e-14
#define FEPS 1.0e-6

bool approx(double a, double b, double eps) {
  return bool( std::abs(a-b) < eps );
}

bool
test(const HepLorentzVector & p, double x, double y, double z, double e,
     double eps) {
  bool t = bool( approx(p.x(), x, eps) && approx(p.y(), y, eps) &&
			     approx(p.z(), z, eps) && approx(p.t(), e, eps));
  if ( !t ) std::cerr << p << std::endl
		      << x << '\t' << y << '\t' << z << '\t' << e
		      << std::endl; 
  return t;
}

void conversion_test(Hep3Vector & v3, HepLorentzVector & v4) {
  v3 = Hep3Vector(3.,2.,1.);
  assert (v3.x() == v4.x() && v3.y() == v4.y() && v3.z() == v4.z());
}

void conversion_test(const Hep3Vector & v3, const HepLorentzVector & v4) {
  assert (v3.x() == v4.x() && v3.y() == v4.y() && v3.z() == v4.z());
}

bool
test(const HepLorentzVector & p, const HepLorentzVector & q, double eps) {
  bool t = bool( approx(p.x(), q.x(), eps) &&
			     approx(p.y(), q.y(), eps) &&
			     approx(p.z(), q.z(), eps) &&
			     approx(p.t(), q.t(), eps));
  if ( !t ) std::cerr << p << std::endl
			 << q << std::endl; 
  return t;
}

int main () {
  HepLorentzVector v4(1.,2.,3.,4.);
  const HepLorentzVector v4const(1.,2.,3.,4);
  conversion_test(v4,v4);
  conversion_test(v4const, v4const);

  Hep3Vector f3x(1.0), f3y(0.0, 1.0), f3z(0.0, 0.0, 1.0);
  Hep3Vector d30, d3x(1.0), d3y(0.0, 1.0), d3z(0.0, 0.0, 1.0);

// test constructors:

  HepLorentzVector d0;
  if ( !test(d0, 0.0, 0.0, 0.0, 0.0, DEPS) ) exit(1);
  HepLorentzVector d1(d3x, 1.0);
  if ( !test(d1, 1.0, 0.0, 0.0, 1.0, DEPS) ) exit(1);
  HepLorentzVector d2(d3x + d3y, sqrt(2.0));
  if ( !test(d2, 1.0, 1.0, 0.0, sqrt(2.0), DEPS) ) exit(1);
  HepLorentzVector d3(d3z + d2, sqrt(3.0));
  if ( !test(d3, 1.0, 1.0, 1.0, sqrt(3.0), DEPS) ) exit(1);
  HepLorentzVector d4(0.0, 0.0, 0.0, 1.0);
  if ( !test(d4,0.0, 0.0, 0.0, 1.0, DEPS) ) exit(1);
  HepLorentzVector d5(f3x, f3x.mag()); if ( !test(d5, d1, FEPS) ) exit(1);
  HepLorentzVector d6(d3x+f3y, (d3x+f3y).mag());
  if ( !test(d6, d2, FEPS) ) exit(1);
  HepLorentzVector d7(f3x+f3y+f3z, (f3x+f3y+f3z).mag());
  if ( !test(d7, d3, FEPS) ) exit(1);

  HepLorentzVector f0; if ( !test(f0, 0.0, 0.0, 0.0, 0.0, FEPS) ) exit(1);
  HepLorentzVector f1(f3x, 1.0);
  if ( !test(f1, 1.0, 0.0, 0.0, 1.0, FEPS) ) exit(1);
  HepLorentzVector f2(f3x + f3y, sqrt(2.0));
  if ( !test(f2, 1.0, 1.0, 0.0, sqrt(2.0), FEPS) ) exit(1);
  HepLorentzVector f3(f3z + f2, sqrt(3.0));
  if ( !test(f3, 1.0, 1.0, 1.0, sqrt(3.0), FEPS) ) exit(1);
  HepLorentzVector f4(0.0, 0.0, 0.0, 1.0);
  if ( !test(f4,0.0, 0.0, 0.0, 1.0, FEPS) ) exit(1);
  HepLorentzVector f5(d3x, d3x.mag()); if ( !test(f5, f1, FEPS) ) exit(1);
  HepLorentzVector f6(f3x+d3y, (f3x+d3y).mag());
  if ( !test(f6, f2, FEPS) ) exit(1);
  HepLorentzVector f7(d3x+d3y+d3z, (d3x+d3y+d3z).mag());
  if ( !test(f7, f3, FEPS) ) exit(1);

  HepLorentzVector d8(f7); if ( !test(d8, d7, FEPS) ) exit(1);
  HepLorentzVector d9(d7); if ( !test(d9, d7, DEPS) ) exit(1);
  HepLorentzVector f8(f7); if ( !test(f8, d7, FEPS) ) exit(1);
  HepLorentzVector f9(d7); if ( !test(f9, d7, FEPS) ) exit(1);

  HepLorentzVector d10(1.0, 1.0, 1.0, sqrt(3.0));
  if ( !test(d10, d7, FEPS) ) exit(1);
  HepLorentzVector f10(1.0, 1.0, 1.0, sqrt(3.0));
  if ( !test(f10, f7, FEPS) ) exit(1);

  HepLorentzVector d11(d3x+d3y+d3z, 1.0);
  if ( !test(d11, 1.0, 1.0, 1.0, 1.0, DEPS) ) exit(1);
  HepLorentzVector f11(d3x+d3y+d3z, 1.0);
  if ( !test(f11, 1.0, 1.0, 1.0, 1.0, FEPS) ) exit(1);

// test input/output from a stream

  std::cin >> d0; if ( !test(d0, 1.1, 2.2, 3.3, 4.4, DEPS) ) exit(1); 
  std::cin >> f0; if ( !test(f0, 4.0, 3.0, 2.0, 1.0, FEPS) ) exit(1); 
  std::cout << d0 << std::endl;
  std::cout << f0 << std::endl;

// testing assignment

  d6 = d7; if ( !test(d6, d7, DEPS) ) exit(2);
  d6 = f7; if ( !test(d6, d7, FEPS) ) exit(2);
  f6 = d7; if ( !test(f6, f7, FEPS) ) exit(2);
  f6 = f7; if ( !test(f6, f7, FEPS) ) exit(2);

  //testing addition and subtraction:

  d11 = d3 + d7 + f3;
  if ( !test(d11, 3.0, 3.0, 3.0, sqrt(27.0), FEPS) ) exit(4);
  f11 = d3 + d7 + f3;
  if ( !test(f11, 3.0, 3.0, 3.0, sqrt(27.0), FEPS) ) exit(4);
  d11 += d3;
  if ( !test(d11, 4.0, 4.0, 4.0, sqrt(48.0), FEPS) ) exit(4);
  f11 += f3;
  if ( !test(f11, 4.0, 4.0, 4.0, sqrt(48.0), FEPS) ) exit(4);
  d11 = d3 + d7 - f3;
  if ( !test(d11, 1.0, 1.0, 1.0, sqrt(3.0), FEPS) ) exit(4);
  if ( !test(-d11, -1.0, -1.0, -1.0, -sqrt(3.0), FEPS) ) exit(4);
  f11 = d3 + f7 - d3;
  if ( !test(f11, 1.0, 1.0, 1.0, sqrt(3.0), FEPS) ) exit(4);
  if ( !test(-f11, -1.0, -1.0, -1.0, -sqrt(3.0), FEPS) ) exit(4);
  d11 -= d3;
  if ( !test(d11, 0.0, 0.0, 0.0, 0.0, FEPS) ) exit(4);
  f11 -= f3;
  if ( !test(f11, 0.0, 0.0, 0.0, 0.0, FEPS) ) exit(4);

  d11 = HepLorentzVector(1.0, 2.0, 3.0, 4.0);
  d11 *= 2.;
  if ( !test(d11, 2.0, 4.0, 6.0, 8.0, DEPS) ) exit(4);
  d11 = 2.*HepLorentzVector(1.0, 2.0, 3.0, 4.0);
  if ( !test(d11, 2.0, 4.0, 6.0, 8.0, DEPS) ) exit(4);
  d11 = HepLorentzVector(1.0, 2.0, 3.0, 4.0)*2.;
  if ( !test(d11, 2.0, 4.0, 6.0, 8.0, DEPS) ) exit(4);

// testing scalar products:

  if ( !approx(d1 * d2, sqrt(2.0)-1.0, DEPS) ) exit(5);
  if ( !approx(d3.dot(d7), 0.0, FEPS) ) exit(5);
  if ( !approx(d2 * f1, sqrt(2.0)-1.0, FEPS) ) exit(5);
  if ( !approx(f3.dot(d7), 0.0, FEPS) ) exit(5);

// testing components:

  d11 = HepLorentzVector(1.0, 1.0, 1.0, sqrt(7.0));
  if ( !approx(d11.mag2(), 4.0, DEPS) ) exit(6);
  if ( !approx(d11.mag(), 2.0, DEPS) ) exit(6);
  if ( !approx(Hep3Vector(d11).mag2(), 3.0, DEPS) ) exit(6);
  if ( !approx(Hep3Vector(d11).mag(), sqrt(3.0), DEPS) ) exit(6);
  if ( !approx(d11.perp2(), 2.0, DEPS) ) exit(6);
  if ( !approx(d11.perp(), sqrt(2.0), DEPS) ) exit(6);
  f11 = HepLorentzVector(1.0, 1.0, 1.0, sqrt(7.0));
  if ( !approx(f11.mag2(), 4.0, FEPS) ) exit(6);
  if ( !approx(f11.mag(), 2.0, FEPS) ) exit(6);
  if ( !approx(f11.vect().mag2(), 3.0, FEPS) ) exit(6);
  if ( !approx(f11.vect().mag(), sqrt(3.0), FEPS) ) exit(6);
  if ( !approx(f11.perp2(), 2.0, FEPS) ) exit(6);
  if ( !approx(f11.perp(), sqrt(2.0), FEPS) ) exit(6);
  
// testing boosts:

  d5 = d3 = d1 = HepLorentzVector(1.0, 2.0, -1.0, 3.0);
  d6 = d4 = d2 = HepLorentzVector(-1.0, 1.0, 2.0, 4.0);
  double M = (d1 + d2).mag();
  double m1 = d1.mag();
  double m2 = d2.mag();
  double p2 = (sqr(M)-sqr(m1+m2))*(sqr(M)-sqr(m1-m2))/(4.0*sqr(M));
  d30 = -(d1 + d2).boostVector();
  d1.boost(d30);
  double phi = d1.phi();
  double theta = d1.theta();
  d1.rotateZ(-phi);
  d1.rotateY(-theta);
  HepRotation r;
  r.rotateZ(-phi);
  HepLorentzRotation r1(d30), r2(r), r3, r4, r5;
  r3.rotateY(-theta);
  r4 = r3  * r2 * r1;
  d2 *= r4;
  if ( !test(d1, 0.0, 0.0, sqrt(p2), sqrt(p2 + sqr(m1)), DEPS) ) exit(7);
  if ( !test(d2, 0.0, 0.0, -sqrt(p2), sqrt(p2 + sqr(m2)), DEPS) ) exit(7);
  d1.transform(r4.inverse());
  if ( !test(d1, d3, DEPS) ) exit(7);
  r5 *= r3;
  r5 *= r;
  r5 *= r1;
  r5.invert();
  d2 *= r5;
  if ( !test(d2, d4, DEPS) ) exit(7);
  r4 = r1;
  r4.rotateZ(-phi);
  r4.rotateY(-theta);
  d3 *= r4;
  d4 = r4 * d6;
  if ( !test(d3, 0.0, 0.0, sqrt(p2), sqrt(p2 + sqr(m1)), DEPS) ) exit(7);
  if ( !test(d4, 0.0, 0.0, -sqrt(p2), sqrt(p2 + sqr(m2)), DEPS) ) exit(7);
  r5 = r1.inverse();
  r5 *= r.inverse();
  r5 *= r3.inverse();
  d4.transform(r5);
  d3.transform(r5);
  
  if ( !test(d4, d6, DEPS) ) exit(7);
  if ( !test(d3, d5, DEPS) ) exit(7);

  r5 = r1;
  r5.transform(r);
  r5.transform(r3);
  d4.transform(r5);
  d3.transform(r5);
  if ( !test(d3, 0.0, 0.0, sqrt(p2), sqrt(p2 + sqr(m1)), DEPS) ) exit(7);
  if ( !test(d4, 0.0, 0.0, -sqrt(p2), sqrt(p2 + sqr(m2)), DEPS) ) exit(7);

  return 0;
}
