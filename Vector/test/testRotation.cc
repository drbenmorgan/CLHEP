// -*- C++ -*-
// $Id: testRotation.cc,v 1.3 2003/08/13 20:00:14 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a test for HepRotation class.
//
#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Units/PhysicalConstants.h"
#include <assert.h>
#include <cmath>
#include <stdlib.h>

using std::abs;

using namespace CLHEP;

typedef HepRotation Rotation;
typedef Hep3Vector  Vector;

#define DEL 10.e-16

int main() {
  int i,k;  
  double angA=CLHEP::pi/3, angB=CLHEP::pi/4, angC=CLHEP::pi/6; 
  double cosA=cos(angA), sinA=sin(angA);
  double cosB=cos(angB), sinB=sin(angB);
  double cosC=cos(angC), sinC=sin(angC);

  Rotation R;                   // default constructor
  assert ( R.xx() == 1 );
  assert ( R.xy() == 0 );
  assert ( R.xz() == 0 );
  assert ( R.yx() == 0 );
  assert ( R.yy() == 1 );
  assert ( R.yz() == 0 );
  assert ( R.zx() == 0 );
  assert ( R.zy() == 0 );
  assert ( R.zz() == 1 );

  assert( R.isIdentity() );     // isIdentity()

  R = Rotation();               // rotateX() 
  R.rotateX(angA);
  assert ( R.xx() == 1    );
  assert ( R.xy() == 0    );
  assert ( R.xz() == 0    );
  assert ( R.yx() == 0    );
  assert ( R.yy() == cosA );
  assert ( R.yz() ==-sinA );
  assert ( R.zx() == 0    );
  assert ( R.zy() == sinA );
  assert ( R.zz() == cosA );

  R = Rotation();               // rotateY() 
  R.rotateY(angB);
  assert ( R.xx() == cosB );
  assert ( R.xy() == 0    );
  assert ( R.xz() == sinB );
  assert ( R.yx() == 0    );
  assert ( R.yy() == 1    );
  assert ( R.yz() == 0    );
  assert ( R.zx() ==-sinB );
  assert ( R.zy() == 0    );
  assert ( R.zz() == cosB );

  R = Rotation();               // rotateZ() 
  R.rotateZ(angC);
  assert ( R.xx() == cosC );
  assert ( R.xy() ==-sinC );
  assert ( R.xz() == 0    );
  assert ( R.yx() == sinC );
  assert ( R.yy() == cosC );
  assert ( R.yz() == 0    );
  assert ( R.zx() == 0    );
  assert ( R.zy() == 0    );
  assert ( R.zz() == 1    );

  R = Rotation();               // copy constructor
  R.rotateZ(angC);
  R.rotateY(angB);
  R.rotateZ(angA);
  Rotation RR(R);

  assert ( abs(RR.xx() - cosA*cosB*cosC + sinA*sinC) < DEL );
  assert ( abs(RR.xy() + cosA*cosB*sinC + sinA*cosC) < DEL );
  assert ( abs(RR.xz() - cosA*sinB)                  < DEL );
  assert ( abs(RR.yx() - sinA*cosB*cosC - cosA*sinC) < DEL );
  assert ( abs(RR.yy() + sinA*cosB*sinC - cosA*cosC) < DEL );
  assert ( abs(RR.yz() - sinA*sinB)                  < DEL );
  assert ( abs(RR.zx() + sinB*cosC)                  < DEL );
  assert ( abs(RR.zy() - sinB*sinC)                  < DEL );
  assert ( abs(RR.zz() - cosB)                       < DEL );

  RR = Rotation();              // operator=, operator!=, operator==
  assert ( RR != R );
  RR = R;
  assert ( RR == R );

  assert ( R(0,0) == R.xx() );  // operator(i,j), operator[i][j] 
  assert ( R(0,1) == R.xy() );
  assert ( R(0,2) == R.xz() );
  assert ( R(1,0) == R.yx() );
  assert ( R(1,1) == R.yy() );
  assert ( R(1,2) == R.yz() );
  assert ( R(2,0) == R.zx() );
  assert ( R(2,1) == R.zy() );
  assert ( R(2,2) == R.zz() );

  for(i=0; i<3; i++) { 
    for(k=0; k<3; k++) { 
      assert ( RR(i,k) == R[i][k] );
    }
  }

  Rotation A, B ,C;                                // operator*= 
  A.rotateZ(angA);
  B.rotateY(angB);
  C.rotateZ(angC);
  R  = A; R *= B; R *= C;

  Vector V(1,2,3);                                 // operator* (Vector) 
  V = R * V;
  assert ( abs(V.x()-R.xx()-2.*R.xy()-3.*R.xz()) < DEL );
  assert ( abs(V.y()-R.yx()-2.*R.yy()-3.*R.yz()) < DEL );
  assert ( abs(V.z()-R.zx()-2.*R.zy()-3.*R.zz()) < DEL );

  R = A * B * C;                                  // operator*(Matrix)
  assert ( abs(RR.xx() - R.xx()) < DEL );
  assert ( abs(RR.xy() - R.xy()) < DEL );
  assert ( abs(RR.xz() - R.xz()) < DEL );
  assert ( abs(RR.yx() - R.yx()) < DEL );
  assert ( abs(RR.yy() - R.yy()) < DEL );
  assert ( abs(RR.yz() - R.yz()) < DEL );
  assert ( abs(RR.zx() - R.zx()) < DEL );
  assert ( abs(RR.zy() - R.zy()) < DEL );
  assert ( abs(RR.zz() - R.zz()) < DEL );

  R = C;                                           // transform()
  R.transform(B);
  R.transform(A); 
  assert ( abs(RR.xx() - R.xx()) < DEL );
  assert ( abs(RR.xy() - R.xy()) < DEL );
  assert ( abs(RR.xz() - R.xz()) < DEL );
  assert ( abs(RR.yx() - R.yx()) < DEL );
  assert ( abs(RR.yy() - R.yy()) < DEL );
  assert ( abs(RR.yz() - R.yz()) < DEL );
  assert ( abs(RR.zx() - R.zx()) < DEL );
  assert ( abs(RR.zy() - R.zy()) < DEL );
  assert ( abs(RR.zz() - R.zz()) < DEL );

  R = RR.inverse();                                // inverse()
  for(i=0; i<3; i++) { 
    for(k=0; k<3; k++) { 
      assert ( RR(i,k) == R[k][i] );
    }
  }

  R.invert();                                      // invert() 
  assert ( RR == R );

  R = Rotation();                                  // rotateAxes()
  R.rotateAxes( Vector(RR.xx(), RR.yx(), RR.zx()),
		Vector(RR.xy(), RR.yy(), RR.zy()),
		Vector(RR.xz(), RR.yz(), RR.zz()) );
  assert ( RR == R );

  double ang=CLHEP::twopi/9.;                           // rotate()
  R = Rotation();
  R.rotate(ang, V);

  RR = Rotation();
  RR.rotateZ(-(V.phi()));
  RR.rotateY(-(V.theta()));
  RR.rotateZ(ang);
  RR.rotateY(V.theta());
  RR.rotateZ(V.phi());

  assert ( abs(RR.xx() - R.xx()) < DEL );
  assert ( abs(RR.xy() - R.xy()) < DEL );
  assert ( abs(RR.xz() - R.xz()) < DEL );
  assert ( abs(RR.yx() - R.yx()) < DEL );
  assert ( abs(RR.yy() - R.yy()) < DEL );
  assert ( abs(RR.yz() - R.yz()) < DEL );
  assert ( abs(RR.zx() - R.zx()) < DEL );
  assert ( abs(RR.zy() - R.zy()) < DEL );
  assert ( abs(RR.zz() - R.zz()) < DEL );

  Vector Vu = V.unit();                           // getAngleAxis
  R.getAngleAxis(ang, V);
  assert ( abs(ang   - CLHEP::twopi/9.) < DEL );
  assert ( abs(V.x() - Vu.x())     < DEL );
  assert ( abs(V.y() - Vu.y())     < DEL );
  assert ( abs(V.z() - Vu.z())     < DEL );

  assert ( abs(RR.phiX()-atan2(RR.yx(),RR.xx())) < DEL ); // phiX()
  assert ( abs(RR.phiY()-atan2(RR.yy(),RR.xy())) < DEL ); // phiY()
  assert ( abs(RR.phiZ()-atan2(RR.yz(),RR.xz())) < DEL ); // phiZ()

  assert ( abs(RR.thetaX()-acos(RR.zx())) < DEL );        // thetaX()
  assert ( abs(RR.thetaY()-acos(RR.zy())) < DEL );        // thetaY()
  assert ( abs(RR.thetaZ()-acos(RR.zz())) < DEL );        // thetaZ()

  return 0;
}           
