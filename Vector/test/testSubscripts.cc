// -*- C++ -*-
// $Id: testSubscripts.cc,v 1.2 2003/08/13 20:00:14 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a small program for testing of subscriping in the Vector module.
//

#include <assert.h>
#include "CLHEP/Vector/defs.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/LorentzVector.h"
#include "CLHEP/Vector/LorentzRotation.h"

using namespace CLHEP;

typedef Hep3Vector       Vec3;
typedef HepLorentzVector Vec4;

class Rot3 : public HepRotation {
public:  
  void setMatrix(double xx, double xy, double xz,
                 double yx, double yy, double yz,
                 double zx, double zy, double zz) {
    rxx = xx; rxy = xy; rxz = xz;
    ryx = yx; ryy = yy; ryz = yz;
    rzx = zx; rzy = zy; rzz = zz;
  }
};

class Rot4 : public HepLorentzRotation {
public:  
  void setMatrix(double xx, double xy, double xz, double xt,
                 double yx, double yy, double yz, double yt,
                 double zx, double zy, double zz, double zt,
                 double tx, double ty, double tz, double tt) {
    mxx = xx; mxy = xy; mxz = xz; mxt = xt;
    myx = yx; myy = yy; myz = yz; myt = yt;
    mzx = zx; mzy = zy; mzz = zz; mzt = zt;
    mtx = tx; mty = ty; mtz = tz; mtt = tt;
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
