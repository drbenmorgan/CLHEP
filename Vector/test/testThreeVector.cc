// -*- C++ -*-
// $Id: testThreeVector.cc,v 1.3 2003/08/08 13:47:09 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a small program for testing the Hep3Vector class
// and the interaction with the HepRotation class.
//

#include "CLHEP/Units/GlobalSystemOfUnits.h"	// to see shadowing problems
#include "CLHEP/Units/GlobalPhysicalConstants.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Vector/Rotation.h"

#include <cmath>
#include <iostream>
#include <stdlib.h>	// for exit

using namespace CLHEP;


#define DEPS 1.0e-14
#define FEPS 1.0e-6

bool approx(double a, double b, double eps) {
  return bool( std::abs(a-b) < eps );
}

bool
test(const Hep3Vector & p, double x, double y, double z,
     double eps) {
  return bool( approx(p.x(), x, eps) && approx(p.y(), y, eps) &&
		     approx(p.z(), z, eps) );
}

bool
test2(const Hep2Vector & p, double x, double y, double eps) {
  return bool( approx(p.x(), x, eps) && approx(p.y(), y, eps) );
}

int main () {

// test constructors:

  Hep3Vector d0; if ( !test(d0, 0.0, 0.0, 0.0, DEPS) ) exit(1);
  Hep3Vector f0; if ( !test(f0, 0.0, 0.0, 0.0, FEPS) ) exit(1);
  Hep3Vector d1(1.0); if ( !test(d1, 1.0, 0.0, 0.0, DEPS) ) exit(1);
  Hep3Vector f1(1.0); if ( !test(f1, 1.0, 0.0, 0.0, FEPS) ) exit(1);
  Hep3Vector d2(1.0, 1.0); if ( !test(d2, 1.0, 1.0, 0.0, DEPS) ) exit(1);
  Hep3Vector f2(1.0, 1.0); if ( !test(f2, 1.0, 1.0, 0.0, FEPS) ) exit(1);
  Hep3Vector d3(1.0, 1.0, 1.0); if ( !test(d3, 1.0, 1.0, 1.0, DEPS) ) exit(1);
  Hep3Vector f3(1.0, 1.0, 1.0); if ( !test(f3, 1.0, 1.0, 1.0, FEPS) ) exit(1);
  Hep3Vector d4(f3); if ( !test(d4, 1.0, 1.0, 1.0, DEPS) ) exit(1);
  Hep3Vector f4(d3); if ( !test(f4, 1.0, 1.0, 1.0, FEPS) ) exit(1);
  
  Hep2Vector t3(d4); if ( !test2(t3, 1.0, 1.0, DEPS) ) exit(1);

// test input/output from a stream

  std::cin >> d0; if ( !test(d0, 1.1, 2.2, 3.3, DEPS) ) exit(1); 
  std::cin >> f0; if ( !test(f0, 3.0, 2.0, 1.0, FEPS) ) exit(1); 
  std::cout << d0 << std::endl;
  std::cout << f0 << std::endl;

// test assignment:

  d4 = d1;  if ( !test(d4, 1.0, 0.0, 0.0, DEPS) ) exit(2);
  f4 = f1;  if ( !test(f4, 1.0, 0.0, 0.0, FEPS) ) exit(2);
  d4 = f1;  if ( !test(d4, 1.0, 0.0, 0.0, FEPS) ) exit(2);
  f4 = d1;  if ( !test(f4, 1.0, 0.0, 0.0, FEPS) ) exit(2);

// test addition:

  d4 = d1 + d2; if ( !test(d4, 2.0, 1.0, 0.0, DEPS) ) exit(3);
  d4 = f1 + d2; if ( !test(d4, 2.0, 1.0, 0.0, FEPS) ) exit(3);
  d4 = d1 + f2; if ( !test(d4, 2.0, 1.0, 0.0, FEPS) ) exit(3);
  d4 = f1 + f2; if ( !test(d4, 2.0, 1.0, 0.0, FEPS) ) exit(3);
  d4 += d3; if ( !test(d4, 3.0, 2.0, 1.0, FEPS) ) exit(3);
  d4 += f3; if ( !test(d4, 4.0, 3.0, 2.0, FEPS) ) exit(3);
  f4 = d1 + d2; if ( !test(f4, 2.0, 1.0, 0.0, FEPS) ) exit(3);
  f4 = f1 + d2; if ( !test(f4, 2.0, 1.0, 0.0, FEPS) ) exit(3);
  f4 = d1 + f2; if ( !test(f4, 2.0, 1.0, 0.0, FEPS) ) exit(3);
  f4 = f1 + f2; if ( !test(f4, 2.0, 1.0, 0.0, FEPS) ) exit(3);
  f4 += d3; if ( !test(f4, 3.0, 2.0, 1.0, FEPS) ) exit(3);
  f4 += f3; if ( !test(f4, 4.0, 3.0, 2.0, FEPS) ) exit(3);

// test subtraction

  d4 -= d3; if ( !test(d4, 3.0, 2.0, 1.0, FEPS) ) exit(4);
  d4 -= f3; if ( !test(d4, 2.0, 1.0, 0.0, FEPS) ) exit(4);
  f4 -= d3; if ( !test(f4, 3.0, 2.0, 1.0, FEPS) ) exit(4);
  f4 -= f3; if ( !test(f4, 2.0, 1.0, 0.0, FEPS) ) exit(4);
  d4 = d1 - d2; if ( !test(d4, 0.0, -1.0, 0.0, DEPS) ) exit(4);
  d4 = f1 - d2; if ( !test(d4, 0.0, -1.0, 0.0, FEPS) ) exit(4);
  d4 = d1 - f2; if ( !test(d4, 0.0, -1.0, 0.0, FEPS) ) exit(4);
  d4 = f1 - f2; if ( !test(d4, 0.0, -1.0, 0.0, FEPS) ) exit(4);
  f4 = d1 - d2; if ( !test(f4, 0.0, -1.0, 0.0, FEPS) ) exit(4);
  f4 = f1 - d2; if ( !test(f4, 0.0, -1.0, 0.0, FEPS) ) exit(4);
  f4 = d1 - f2; if ( !test(f4, 0.0, -1.0, 0.0, FEPS) ) exit(4);
  f4 = f1 - f2; if ( !test(f4, 0.0, -1.0, 0.0, FEPS) ) exit(4);

// test unary minus:

  if ( !test(-d3, -1.0, -1.0, -1.0, DEPS) ) exit(5);
  if ( !test(-f3, -1.0, -1.0, -1.0, FEPS) ) exit(5);
  if ( !test(-d1, -1.0, 0.0, 0.0, DEPS) ) exit(5);
  if ( !test(-f1, -1.0, 0.0, 0.0, FEPS) ) exit(5);

// test scaling:

  if ( !test(d3*2.0, 2.0, 2.0, 2.0, DEPS) ) exit(6);
  if ( !test(2.0*d3, 2.0, 2.0, 2.0, DEPS) ) exit(6);
  if ( !test(d1*2.0, 2.0, 0.0, 0.0, DEPS) ) exit(6);
  if ( !test(2.0*d1, 2.0, 0.0, 0.0, DEPS) ) exit(6);
  if ( !test(f3*2.0f, 2.0, 2.0, 2.0, FEPS) ) exit(6);
  if ( !test(2.0f*f3, 2.0, 2.0, 2.0, FEPS) ) exit(6);
  if ( !test(f1*2.0f, 2.0, 0.0, 0.0, FEPS) ) exit(6);
  if ( !test(2.0f*f1, 2.0, 0.0, 0.0, FEPS) ) exit(6);
  if ( !test(d4*=2.0, 0.0, -2.0, 0.0, FEPS) ) exit(6); 
  if ( !test(f4*=2.0, 0.0, -2.0, 0.0, FEPS) ) exit(6);

// testing scalar and vector product:

  if ( !approx(d4*d1, 0.0, DEPS) ) exit(7);
  if ( !approx(d4*f1, 0.0, FEPS) ) exit(7);
  if ( !approx(f4*d1, 0.0, FEPS) ) exit(7);
  if ( !approx(f4*f1, 0.0, FEPS) ) exit(7);
  if ( !approx(d4.dot(d1), 0.0, DEPS) ) exit(7);
  if ( !approx(d4.dot(f1), 0.0, FEPS) ) exit(7);
  if ( !approx(f4.dot(d1), 0.0, FEPS) ) exit(7);
  if ( !approx(f4.dot(f1), 0.0, FEPS) ) exit(7);
  if ( !approx(d4*d2, -2.0, DEPS) ) exit(7);
  if ( !approx(d4*f2, -2.0, FEPS) ) exit(7);
  if ( !approx(f4*d2, -2.0, FEPS) ) exit(7);
  if ( !approx(f4*f2, -2.0, FEPS) ) exit(7);
  if ( !approx(d4.dot(d2), -2.0, DEPS) ) exit(7);
  if ( !approx(d4.dot(f2), -2.0, FEPS) ) exit(7);
  if ( !approx(f4.dot(d2), -2.0, FEPS) ) exit(7);
  if ( !approx(f4.dot(f2), -2.0, FEPS) ) exit(7);
  d4 = d1.cross(d2); if ( !test(d4, 0.0, 0.0, 1.0, DEPS) ) exit(7);
  d4 = d2.cross(d1); if ( !test(d4, 0.0, 0.0, -1.0, DEPS) ) exit(7);
  f4 = f1.cross(d2); if ( !test(f4, 0.0, 0.0, 1.0, FEPS) ) exit(7);
  f4 = d2.cross(f1); if ( !test(f4, 0.0, 0.0, -1.0, FEPS) ) exit(7);

// testing ptot and pt:

  d4 = d1 + f2 + d3;
  f4 = d1 + f2 + d3;
  if ( !approx(d4.mag2(), 14.0, FEPS) ) exit(8);
  if ( !approx(d4.mag(), std::sqrt(14.0), FEPS) ) exit(8);
  if ( !approx(d4.perp2(), 13.0, FEPS) ) exit(8);
  if ( !approx(d4.perp(), std::sqrt(13.0), FEPS) ) exit(8);
  if ( !approx(f4.mag2(), 14.0, FEPS) ) exit(8);
  if ( !approx(f4.mag(), std::sqrt(14.0), FEPS) ) exit(8);
  if ( !approx(f4.perp2(), 13.0, FEPS) ) exit(8);
  if ( !approx(f4.perp(), std::sqrt(13.0), FEPS) ) exit(8);

// testing angles:

  d4 = d2 - 2.0 * d1;
  f4 = d2 - 2.0f * f1;
  if ( !approx(d1.phi(), 0.0, DEPS) ) exit(9);
  if ( !approx(d1.theta(), CLHEP::halfpi, DEPS) ) exit(9);
  if ( !approx(d1.cosTheta(), 0.0, DEPS) ) exit(9);
  if ( !approx(d2.phi(), CLHEP::halfpi*0.5, DEPS) ) exit(9);
  if ( !approx(d2.theta(), CLHEP::halfpi, DEPS) ) exit(9);
  if ( !approx(d2.cosTheta(), 0.0, DEPS) ) exit(9);
  if ( !approx((-d2).phi(), -3.0*CLHEP::halfpi*0.5, DEPS) ) exit(9);
  if ( !approx(d4.phi(), 3.0*CLHEP::halfpi*0.5, DEPS) ) exit(9);

  if ( !approx(f1.phi(), 0.0, FEPS) ) exit(9);
  if ( !approx(f1.theta(), CLHEP::halfpi, FEPS) ) exit(9);
  if ( !approx(f1.cosTheta(), 0.0, FEPS) ) exit(9);
  if ( !approx(f2.phi(), CLHEP::halfpi*0.5, FEPS) ) exit(9);
  if ( !approx(f2.theta(), CLHEP::halfpi, FEPS) ) exit(9);
  if ( !approx(f2.cosTheta(), 0.0, FEPS) ) exit(9);
  if ( !approx((-f2).phi(), -3.0*CLHEP::halfpi*0.5, FEPS) ) exit(9);
  if ( !approx(f4.phi(), 3.0*CLHEP::halfpi*0.5, FEPS) ) exit(9);

  d4 = d3 - d1; if ( !approx(d4.theta(), CLHEP::halfpi*0.5, DEPS) ) exit(9);
  if ( !approx((-d4).theta(), 3.0*CLHEP::halfpi*0.5, DEPS) ) exit(9);
  if ( !approx((-d4).cosTheta(), -std::sqrt(0.5), DEPS) ) exit(9);
  d4 = d3 - d2; if ( !approx(d4.theta(), 0.0, DEPS) ) exit(9);
  if ( !approx(d4.cosTheta(), 1.0, DEPS) ) exit(9);
  if ( !approx((-d4).theta(), CLHEP::pi, DEPS) ) exit(9);
  if ( !approx((-d4).cosTheta(), -1.0, DEPS) ) exit(9);
  f4 = d3 - d1; if ( !approx(f4.theta(), CLHEP::halfpi*0.5, FEPS) ) exit(9);
  if ( !approx((-f4).theta(), 3.0*CLHEP::halfpi*0.5, FEPS) ) exit(9);
  if ( !approx((-f4).cosTheta(), -std::sqrt(0.5), FEPS) ) exit(9);
  f4 = d3 - d2; if ( !approx(f4.theta(), 0.0, FEPS) ) exit(9);
  if ( !approx(f4.cosTheta(), 1.0, FEPS) ) exit(9);
  if ( !approx((-f4).theta(), CLHEP::pi, FEPS) ) exit(9);
  if ( !approx((-f4).cosTheta(), -1.0, FEPS) ) exit(9);

  d4 = d2 - 2.0*d1; if ( !approx(d4.angle(d2), CLHEP::halfpi, DEPS) ) exit(9);
  f4 = d2 - 2.0*d1; if ( !approx(f4.angle(f2), CLHEP::halfpi, FEPS) ) exit(9);

// testing rotations

  d4 = d1;
  d4.rotateZ(CLHEP::halfpi); if ( !test(d4, 0.0, 1.0, 0.0, DEPS) ) exit(10);
  d4.rotateY(25.3); if ( !test(d4, 0.0, 1.0, 0.0, DEPS) ) exit(10);
  d4.rotateZ(CLHEP::halfpi); if ( !test(d4, -1.0, 0.0, 0.0, DEPS) ) exit(10);
  d4.rotateY(CLHEP::halfpi); if ( !test(d4, 0.0, 0.0, 1.0, DEPS) ) exit(10);
  d4.rotateZ(2.6); if ( !test(d4, 0.0, 0.0, 1.0, DEPS) ) exit(10);
  d4.rotateY(CLHEP::pi*0.25);
  if ( !test(d4, std::sqrt(0.5), 0.0, std::sqrt(0.5), DEPS) ) exit(10);
  f4 = f1;
  f4.rotateZ(CLHEP::halfpi); if ( !test(f4, 0.0, 1.0, 0.0, FEPS) ) exit(10);
  f4.rotateY(25.3); if ( !test(f4, 0.0, 1.0, 0.0, FEPS) ) exit(10);
  f4.rotateZ(CLHEP::halfpi); if ( !test(f4, -1.0, 0.0, 0.0, FEPS) ) exit(10);
  f4.rotateY(CLHEP::halfpi); if ( !test(f4, 0.0, 0.0, 1.0, FEPS) ) exit(10);
  f4.rotateZ(2.6); if ( !test(f4, 0.0, 0.0, 1.0, FEPS) ) exit(10);
  f4.rotateY(CLHEP::pi*0.25);
  if ( !test(f4, std::sqrt(0.5), 0.0, std::sqrt(0.5), FEPS) ) exit(10);

  d4 = d1;
  d4.rotate(d4.angle(d3), d4.cross(d3));
  d4 *= d3.mag();
  if ( !test(d4, 1.0, 1.0, 1.0, DEPS) ) exit(10);
  d4 = d1;
  d4.rotate(0.23, d4.cross(d3));
  if ( !approx(d4.angle(d1), 0.23, DEPS) ) exit(10);
  f4 = d1;
  f4.rotate(f4.angle(d3), f4.cross(d3));
  f4 *= f3.mag();
  if ( !test(f4, 1.0, 1.0, 1.0, FEPS) ) exit(10);
  f4 = f1;
  f4.rotate(0.23, f4.cross(d3));
  if ( !approx(f4.angle(f1), 0.23, FEPS) ) exit(10);
  if ( !approx(f4.angle(d3), f1.angle(d3) - 0.23, FEPS) ) exit(10);

// test rotation maticies:

  d4 = d1;

  HepRotation r0, r1, r2, r3, r4, r5;
  r1.rotateZ(CLHEP::halfpi);
  r2.rotateY(CLHEP::halfpi);
  r4.rotate(d4.angle(d3), d4.cross(d3));
  r5.rotate(0.23, d4.cross(d3));
  d4 = r4.inverse() * d3;
  if ( !test(d4, d3.mag(), 0.0, 0.0, DEPS) ) exit(11);
  d4 = r5 * d3;
  if ( !approx(d1.angle(d4), d1.angle(d3)+0.23, DEPS) ) exit(11);
  f4 = r4.inverse() * f3;
  if ( !test(f4, f3.mag(), 0.0, 0.0, FEPS) ) exit(11);
  f4 = r5 * d3;
  if ( !approx(d1.angle(f4), f1.angle(f3)+0.23, FEPS) ) exit(11);
  r5 = r2 * r1 * r3.inverse() * r0 * r0.inverse();
  d4 = d3;
  d4 *= r3.inverse();
  d4 *= r1;
  d4 *= r2;
  if ( !test(d4, 1.0, 1.0, 1.0, DEPS) ) exit(11);
  r5.invert();
  d4 = r5 * d4;
  if ( !test(d4, 1.0, 1.0, 1.0, DEPS) ) exit(11);
  d1 = d2 = Hep3Vector(1.0, -0.5, 2.1);
  d3 = Hep3Vector(-0.3, 1.1, 1.5);
  d4 = d3.unit();
  d4 *= d3.mag();
  if ( !test(d4, d3.x(), d3.y(), d3.z(), DEPS) ) exit(11);
  r0.rotate(0.10, d1.cross(d3));
  d1 *= r0;
  if ( !approx(d1.angle(d3), d2.angle(d3)-0.1, DEPS) ) exit(12);
  if ( !approx(d1.angle(d2), 0.1, DEPS) ) exit(12);

  return 0;

}
