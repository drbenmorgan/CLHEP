// -*- C++ -*-
// $Id: testTransform3D.cc,v 1.3 2003/10/24 21:39:45 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a test for the HepGeom::Transform3D class.
//
#include <assert.h>
#include "CLHEP/Geometry/Transform3D.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Units/PhysicalConstants.h"

typedef HepGeom::Scale3D           Scale;
typedef HepGeom::Rotate3D          Rotation;
typedef HepGeom::Translate3D       Translation;
typedef HepGeom::Transform3D       Transformation;
typedef HepGeom::Point3D<double>   Point;
typedef HepGeom::Vector3D<double>  Vector;
typedef HepGeom::Normal3D<double>  Normal;

#define DEL 10.e-16

int main() {
  int i,k;  
  double E[4][4] = {
    { 1, 0, 0, 0},
    { 0, 1, 0, 0},
    { 0, 0, 1, 0},
    { 0, 0, 0, 1}
  };

  // Default constructor

  Transformation M;
  for (i=0; i<4; i++) {
    for (k=0; k<4; k++) {
      assert ( M[i][k] == E[i][k] );
    }
  }
 assert ( M == Transformation::Identity );

  // Rotation + Translation

  HepRotation R;
  double angA=CLHEP::pi/3, angB=CLHEP::pi/4, angC=CLHEP::pi/6; 

  R.rotateX(angA); R.rotateY(angB); R.rotateZ(angC);
  const Hep3Vector D(1, 2, 3);
  M = Transformation(R,D);

  for (i=0; i<3; i++) {
    for (k=0; k<3; k++) { assert ( M[i][k] == R[i][k] ); }
  }
  assert ( M(0,3) == D.x() );
  assert ( M(1,3) == D.y() );
  assert ( M(2,3) == D.z() );

  // Transformation of point, vector, normal

  const Point  p0(1,1,1);
  const Vector v0(1,1,1);
  const Normal n0(1,1,1);

  Point p1 = M * p0;
  Point p2 = R*Hep3Vector(1,1,1) + D;
  assert( std::abs(p1.x()-p2.x()) < DEL );
  assert( std::abs(p1.y()-p2.y()) < DEL );
  assert( std::abs(p1.z()-p2.z()) < DEL );

  Vector v1 = M * v0;
  Normal n1 = M * n0;
  assert( std::abs(v1.x()-n1.x()) < DEL );
  assert( std::abs(v1.y()-n1.y()) < DEL );
  assert( std::abs(v1.z()-n1.z()) < DEL );

  // Transformation of basis

  p1 = Point(M[0][0]+D.x(), M[1][0]+D.y(), M[2][0]+D.z());
  p2 = Point(M[0][1]+D.x(), M[1][1]+D.y(), M[2][1]+D.z());
  Transformation T(Point(0,0,0), Point(1,0,0), Point(0,1,0), D, p1, p2);

  for (i=0; i<4; i++) {
    for (k=0; k<4; k++) { assert ( std::abs(M[i][k] - T[i][k]) < DEL ); }
  }

  // Set Identity

  T.setIdentity();
  for (i=0; i<4; i++) {
    for (k=0; k<4; k++) { assert ( T[i][k] == E[i][k] ); }
  }

  // Assignment, fortran-style subscripting 

  T = M;
  assert (T == M);
  for (i=0; i<4; i++) {
    for (k=0; k<4; k++) { assert ( T(i,k) == M[i][k] ); }
  }

  // Inversion

  T = M.inverse();
  assert (T != M);
  T = M * T;
  for (i=0; i<4; i++) {
    for (k=0; k<4; k++) { assert ( std::abs(T[i][k] - E[i][k]) < DEL ); }
  }
 
  T = M.inverse();
  T = T * M;
  for (i=0; i<4; i++) {
    for (k=0; k<4; k++) { assert ( std::abs(T[i][k] - E[i][k]) < DEL ); }
  }

  // Get Rotation

  HepRotation Q;
  Q = M.getRotation();
  for (i=0; i<3; i++) {
    for (k=0; k<3; k++) { assert ( R[i][k] == Q[i][k] ); }
  }

  // Get Translation

  Hep3Vector C;
  C = M.getTranslation();
  assert ( C.x() == D.x() );
  assert ( C.y() == D.y() );
  assert ( C.z() == D.z() );

  // Compound transformation
  // Get Decomposition

  Scale S(-2,3,4);
  M = Transformation(R,D)*S;

  Scale       SS;
  Rotation    RR;
  Translation TT;
  M.getDecomposition(SS,RR,TT);

  S = HepGeom::Scale3D(2,3,-4);
  T = TT*RR*SS;
  for (i=0; i<4; i++) {
    for (k=0; k<4; k++) {
      assert ( std::abs(S[i][k] - SS[i][k]) < DEL );
      assert ( std::abs(M[i][k] - T[i][k])  < DEL );
    }
  }

  // test for isNear()

  assert ( T.isNear(M, DEL) );
  S = HepGeom::Scale3D(2.01,3,-4);
  T = TT*RR*S;
  assert ( !T.isNear(M) );

  // Different conversions

  Hep3Vector www(1,2,3);
  Vector     vvv;
  Point      ppp(3,2,1);
  Normal     nnn;

  vvv = www;
  www = vvv;
  nnn = ppp;

  assert (vvv.x() == nnn.z()); 
  assert (vvv.y() == nnn.y()); 
  assert (vvv.z() == nnn.x()); 

  nnn = Normal(ppp);
  www = Hep3Vector(vvv);

  return 0;
}           
