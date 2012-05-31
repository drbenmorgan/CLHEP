// -*- C++ -*-
// $Id: testSubscripts.cc,v 1.2 2003/08/13 20:00:14 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a small program for testing of subscriping in the Vector module.
//

#include <assert.h>
#include "CLHEP/Units/GlobalSystemOfUnits.h"	// to see shadowing problems
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/LorentzRotation.h"

using namespace CLHEP;

typedef Hep3Vector       Vec3;
typedef HepLorentzVector Vec4;

class Rot3 : public HepRotation {
public:  
  void setMatrix(double xx1, double xy1, double xz1,
                 double yx1, double yy1, double yz1,
                 double zx1, double zy1, double zz1) {
    rxx = xx1; rxy = xy1; rxz = xz1;
    ryx = yx1; ryy = yy1; ryz = yz1;
    rzx = zx1; rzy = zy1; rzz = zz1;
  }
};

class Rot4 : public HepLorentzRotation {
public:  
  void setMatrix(double xx1, double xy1, double xz1, double xt1,
                 double yx1, double yy1, double yz1, double yt1,
                 double zx1, double zy1, double zz1, double zt1,
                 double tx1, double ty1, double tz1, double tt1) {
    mxx = xx1; mxy = xy1; mxz = xz1; mxt = xt1;
    myx = yx1; myy = yy1; myz = yz1; myt = yt1;
    mzx = zx1; mzy = zy1; mzz = zz1; mzt = zt1;
    mtx = tx1; mty = ty1; mtz = tz1; mtt = tt1;
  }
};

int main() {

  // Test ThreeVector subscripting

  Vec3  V3;
  const Vec3 ConstV3(1.,2.,3.);

  V3[0] = ConstV3[0];
  V3[1] = ConstV3[1];
  V3[2] = ConstV3[2];
  assert(V3 == ConstV3);

  V3(0) = ConstV3(2);
  V3(1) = ConstV3(1);
  V3(2) = ConstV3(0);
  assert(V3 == Hep3Vector(3.,2.,1.));

  // Test LorentzVector subscripting

  Vec4  V4;
  const Vec4 ConstV4(1.,2.,3.,4); 

  V4[0] = ConstV4[0];
  V4[1] = ConstV4[1];
  V4[2] = ConstV4[2];
  V4[3] = ConstV4[3];
  assert(V4 == ConstV4);

  V4(0) = ConstV4(3);
  V4(1) = ConstV4(2);
  V4(2) = ConstV4(1);
  V4(3) = ConstV4(0);
  assert(V4 == HepLorentzVector(4.,3.,2.,1.));

  // Test Rotation subscripting

  int  i, j, k;
  Rot3 R3;

  R3.setMatrix(1.,2.,3.,4.,5.,6.,7.,8.,9.);

  k = 1;
  for(i=0; i<3; i++) {
    for(j=0; j<3; j++) {
      assert(R3(i,j)  == double(k));
      assert(R3[i][j] == double(k));
      k++;
    }
  }

  // Test LorentzRotation subscripting

  Rot4 R4;
  R4.setMatrix(1.,2.,3.,4.,5.,6.,7.,8.,9.,10.,11.,12.,13.,14.,15.,16.);

  k = 1;
  for(i=0; i<4; i++) {
    for(j=0; j<4; j++) {
      assert(R4(i,j)  == double(k));
      assert(R4[i][j] == double(k));
      k++;
    }
  }

  return 0;
}
