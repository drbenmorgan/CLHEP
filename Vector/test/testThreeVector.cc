// -*- C++ -*-
// $Id: testThreeVector.cc,v 1.2 2003/07/16 21:43:57 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a small program for testing the Hep3Vector class
// and the interaction with the HepRotation class.
//

#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/Rotation.h"

#include <cmath>
#include <iostream>
#include <stdlib.h>	// for exit

using namespace std;
using namespace CLHEP;


#define DEPS 1.0e-14
#define FEPS 1.0e-6

bool approx(double a, double b, double eps) {
  return bool( abs(a-b) < eps );
}

bool
test(const Hep3Vector & p, double x, double y, double z,
     double eps) {
  return bool( approx(p.x(), x, eps) && approx(p.y(), y, eps) &&
		     approx(p.z(), z, eps) );
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

// test input/output from a stream

  cin >> d0; if ( !test(d0, 1.1, 2.2, 3.3, DEPS) ) exit(1); 
  cin >> f0; if ( !test(f0, 3.0, 2.0, 1.0, FEPS) ) exit(1); 
  cout << d0 << endl;
  cout << f0 << endl;

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
  if ( !approx(d4.mag(), sqrt(14.0), FEPS) ) exit(8);
  if ( !approx(d4.perp2(), 13.0, FEPS) ) exit(8);
  if ( !approx(d4.perp(), sqrt(13.0), FEPS) ) exit(8);
  if ( !approx(f4.mag2(), 14.0, FEPS) ) exit(8);
  if ( !approx(f4.mag(), sqrt(14.0), FEPS) ) exit(8);
  if ( !approx(f4.perp2(), 13.0, FEPS) ) exit(8);
  if ( !approx(f4.perp(), sqrt(13.0), FEPS) ) exit(8);

// testing angles:

  d4 = d2 - 2.0 * d1;
  f4 = d2 - 2.0f * f1;
  if ( !approx(d1.phi(), 0.0, DEPS) ) exit(9);
  if ( !approx(d1.theta(), M_PI_2, DEPS) ) exit(9);
  if ( !approx(d1.cosTheta(), 0.0, DEPS) ) exit(9);
  if ( !approx(d2.phi(), M_PI_2*0.5, DEPS) ) exit(9);
  if ( !approx(d2.theta(), M_PI_2, DEPS) ) exit(9);
  if ( !approx(d2.cosTheta(), 0.0, DEPS) ) exit(9);
  if ( !approx((-d2).phi(), -3.0*M_PI_2*0.5, DEPS) ) exit(9);
  if ( !approx(d4.phi(), 3.0*M_PI_2*0.5, DEPS) ) exit(9);

  if ( !approx(f1.phi(), 0.0, FEPS) ) exit(9);
  if ( !approx(f1.theta(), M_PI_2, FEPS) ) exit(9);
  if ( !approx(f1.cosTheta(), 0.0, FEPS) ) exit(9);
  if ( !approx(f2.phi(), M_PI_2*0.5, FEPS) ) exit(9);
  if ( !approx(f2.theta(), M_PI_2, FEPS) ) exit(9);
  if ( !approx(f2.cosTheta(), 0.0, FEPS) ) exit(9);
  if ( !approx((-f2).phi(), -3.0*M_PI_2*0.5, FEPS) ) exit(9);
  if ( !approx(f4.phi(), 3.0*M_PI_2*0.5, FEPS) ) exit(9);

  d4 = d3 - d1; if ( !approx(d4.theta(), M_PI_2*0.5, DEPS) ) exit(9);
  if ( !approx((-d4).theta(), 3.0*M_PI_2*0.5, DEPS) ) exit(9);
  if ( !approx((-d4).cosTheta(), -sqrt(0.5), DEPS) ) exit(9);
  d4 = d3 - d2; if ( !approx(d4.theta(), 0.0, DEPS) ) exit(9);
  if ( !approx(d4.cosTheta(), 1.0, DEPS) ) exit(9);
  if ( !approx((-d4).theta(), M_PI, DEPS) ) exit(9);
  if ( !approx((-d4).cosTheta(), -1.0, DEPS) ) exit(9);
  f4 = d3 - d1; if ( !approx(f4.theta(), M_PI_2*0.5, FEPS) ) exit(9);
  if ( !approx((-f4).theta(), 3.0*M_PI_2*0.5, FEPS) ) exit(9);
  if ( !approx((-f4).cosTheta(), -sqrt(0.5), FEPS) ) exit(9);
  f4 = d3 - d2; if ( !approx(f4.theta(), 0.0, FEPS) ) exit(9);
  if ( !approx(f4.cosTheta(), 1.0, FEPS) ) exit(9);
  if ( !approx((-f4).theta(), M_PI, FEPS) ) exit(9);
  if ( !approx((-f4).cosTheta(), -1.0, FEPS) ) exit(9);

  d4 = d2 - 2.0*d1; if ( !approx(d4.angle(d2), M_PI_2, DEPS) ) exit(9);
  f4 = d2 - 2.0*d1; if ( !approx(f4.angle(f2), M_PI_2, FEPS) ) exit(9);

// testing rotations

  d4 = d1;
  d4.rotateZ(M_PI_2); if ( !test(d4, 0.0, 1.0, 0.0, DEPS) ) exit(10);
  d4.rotateY(25.3); if ( !test(d4, 0.0, 1.0, 0.0, DEPS) ) exit(10);
  d4.rotateZ(M_PI_2); if ( !test(d4, -1.0, 0.0, 0.0, DEPS) ) exit(10);
  d4.rotateY(M_PI_2); if ( !test(d4, 0.0, 0.0, 1.0, DEPS) ) exit(10);
  d4.rotateZ(2.6); if ( !test(d4, 0.0, 0.0, 1.0, DEPS) ) exit(10);
  d4.rotateY(M_PI*0.25);
  if ( !test(d4, sqrt(0.5), 0.0, sqrt(0.5), DEPS) ) exit(10);
  f4 = f1;
  f4.rotateZ(M_PI_2); if ( !test(f4, 0.0, 1.0, 0.0, FEPS) ) exit(10);
  f4.rotateY(25.3); if ( !test(f4, 0.0, 1.0, 0.0, FEPS) ) exit(10);
  f4.rotateZ(M_PI_2); if ( !test(f4, -1.0, 0.0, 0.0, FEPS) ) exit(10);
  f4.rotateY(M_PI_2); if ( !test(f4, 0.0, 0.0, 1.0, FEPS) ) exit(10);
  f4.rotateZ(2.6); if ( !test(f4, 0.0, 0.0, 1.0, FEPS) ) exit(10);
  f4.rotateY(M_PI*0.25);
  if ( !test(f4, sqrt(0.5), 0.0, sqrt(0.5), FEPS) ) exit(10);

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
  r1.rotateZ(M_PI_2);
  r2.rotateY(M_PI_2);
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
