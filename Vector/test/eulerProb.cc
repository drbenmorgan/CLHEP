// HepRotatonTest.cc

#include <iostream>
#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Vector/Rotation.h"

using std::cout;
using std::endl;
using namespace CLHEP;


class myRotClass: public HepRotation {
public:
  myRotClass (const HepRotationZ& rot): HepRotation (rot) {;};
  void setXX (const double& v) {rxx = v;};
  void setXY (const double& v) {rxy = v;};
  void setXZ (const double& v) {rxz = v;};
  void setYX (const double& v) {ryx = v;};
  void setYY (const double& v) {ryy = v;};
  void setYZ (const double& v) {ryz = v;};
  void setZX (const double& v) {rzx = v;};
  void setZY (const double& v) {rzy = v;};
  void setZZ (const double& v) {rzz = v;};
};


int main () {
  HepRotationZ az (120*deg); // az.set (120*degree);
  // HepRotation rot (az);
  myRotClass rot(az);

  const double corr = 0.9999999999999999;
  rot.setZZ (corr);
  // Make sure that det(rot)=1, so that its still a valid rotation
  // (in principal I would expect that HepRotation should be robust
  // enough to give reasonable results even without this step since
  // round off errors in floating point operations could also cause
  // such a loss of precision).
  rot.setXX (rot.xx()/sqrt(corr));  rot.setXY (rot.xy()/sqrt(corr));
  rot.setYX (rot.yx()/sqrt(corr));  rot.setYY (rot.yy()/sqrt(corr));

  cout.setf (std::ios::scientific, std::ios::floatfield);
  rot.print (cout); cout << "\n";
  cout.precision (30);
  cout << rot.xx() << "\t" << rot.xy() << "\t" << rot.xz() << "\n"
       << rot.yx() << "\t" << rot.yy() << "\t" << rot.yz() << "\n"
       << rot.zx() << "\t" << rot.zy() << "\t" << rot.zz() << endl;
  cout << "\nEuler angles:"
       << "\nphi = "   << rot.phi()
       << "\ttheta = " << rot.theta()
       << "\tpsi = "   << rot.psi()
       << endl;

  HepRotation newrot (rot.phi(), rot.theta(), rot.psi());
  newrot.print(cout);

  return 0;
}

