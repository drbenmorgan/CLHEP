// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of methods of the HepRotation class which
// were introduced when ZOOM PhysicsVectors was merged in, and which involve
// Euler Angles representation.
//

#ifdef GNUPRAGMA
#pragma implementation
#endif

#include "Vector/defs.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Vector/EulerAngles.h"

#include <cmath>

namespace CLHEP  {

static inline double safe_acos (double x) {
  if (abs(x) <= 1.0) return acos(x);
  return ( (x>0) ? 0 : M_PI );
}

// ----------  Constructors and Assignment:

// Euler angles

HepRotation & HepRotation::set(double phi, double theta, double psi) {

  register double sinPhi   = sin( phi   ), cosPhi   = cos( phi   );
  register double sinTheta = sin( theta ), cosTheta = cos( theta );
  register double sinPsi   = sin( psi   ), cosPsi   = cos( psi   );

  rxx =   cosPsi * cosPhi - cosTheta * sinPhi * sinPsi;
  rxy =   cosPsi * sinPhi + cosTheta * cosPhi * sinPsi;
  rxz =   sinPsi * sinTheta;

  ryx = - sinPsi * cosPhi - cosTheta * sinPhi * cosPsi;
  ryy = - sinPsi * sinPhi + cosTheta * cosPhi * cosPsi;
  ryz =   cosPsi * sinTheta;

  rzx =   sinTheta * sinPhi;
  rzy = - sinTheta * cosPhi;
  rzz =   cosTheta;

  return  *this;

}  // Rotation::set(phi, theta, psi)

HepRotation::HepRotation( double phi, double theta, double psi ) 
{
  set (phi, theta, psi);
}
HepRotation & HepRotation::set( const HepEulerAngles & e ) {
  return set(e.phi(), e.theta(), e.psi());
}
HepRotation::HepRotation ( const HepEulerAngles & e ) 
{
  set(e.phi(), e.theta(), e.psi());
}


 
double HepRotation::phi  () const {

  double s2 =  1.0 - rzz*rzz;
  if (s2 < 0) {
    ZMthrowC ( ZMxpvImproperRotation (
        "HepRotation::phi() finds | rzz | > 1 "));
    s2 = 0;
  }
  const double sinTheta = sqrt( s2 );

  if (sinTheta != 0) {

    const double cscTheta = 1/sinTheta;
    double cosabsphi =  - rzy * cscTheta;
    if ( fabs(cosabsphi) > 1 ) {	// NaN-proofing
      ZMthrowC ( ZMxpvImproperRotation (
	"HepRotation::phi() finds | cos phi | > 1 "));
      cosabsphi = 1;
    }
    const double absPhi = acos ( cosabsphi );
    if (rzx > 0) {
      return   absPhi;
    } else if (rzx < 0) {
      return  -absPhi;
    } else {
      return  (rzy < 0) ? 0 : M_PI;
    }

  } else {              // sinTheta == 0 so |Rzz| = 1

    const double absPhi = .5 * safe_acos (rxx);
    if (rxy > 0) {
      return   absPhi;
    } else if (rxy < 0) {
      return  -absPhi;
    } else {
      return (rxx > 0) ? 0 : M_PI/2;
    }

  }

} // phi()

double HepRotation::theta() const {

  return  safe_acos( rzz );

} // theta()

double HepRotation::psi  () const {

  const double sinTheta = sqrt( 1.0 - rzz*rzz );

  if (sinTheta != 0) {

    const double cscTheta = 1/sinTheta;
    double cosabspsi =  ryz * cscTheta;
    if ( fabs(cosabspsi) > 1 ) {	// NaN-proofing
      ZMthrowC ( ZMxpvImproperRotation (
	"HepRotation::psi() finds | cos psi | > 1"));
      cosabspsi = 1;
    }
    const double absPsi = acos ( cosabspsi );
    if (rxz > 0) {
      return   absPsi;
    } else if (rxz < 0) {
      return  -absPsi;
    } else {
      return  (ryz > 0) ? 0 : M_PI;
    }

  } else {              // sinTheta == 0 so |Rzz| = 1

    const double absPsi = .5 * safe_acos (rxx);
    if (ryx > 0) {
      return  -absPsi;
    } else if (ryx < 0) {
      return   absPsi;
    } else {
      return (rxx > 0) ? 0 : rzz * M_PI/2;
    }

  }

} // psi()


HepEulerAngles HepRotation::eulerAngles() const {

  double phi, theta, psi;

  theta = safe_acos( rzz );

  double s2 =  1.0 - rzz*rzz;
  if (s2 < 0) {
    ZMthrowC ( ZMxpvImproperRotation (
        "HepRotation::eulerAngles() finds | rzz | > 1 "));
    s2 = 0;
  }
  const double sinTheta = sqrt( s2 );

  if (sinTheta != 0) {

    const double cscTheta = 1/sinTheta;
    double cosabspsi =  ryz * cscTheta;
    if ( fabs(cosabspsi) > 1 ) {	// NaN-proofing
      ZMthrowC ( ZMxpvImproperRotation (
	"HepRotation::eulerAngles() finds | cos psi | > 1"));
      cosabspsi = 1;
    }
    double cosabsphi =  - rzy * cscTheta;
    if ( fabs(cosabsphi) > 1 ) {	// NaN-proofing
      ZMthrowC ( ZMxpvImproperRotation (
	"HepRotation::eulerAngles() finds | cos phi | > 1 "));
      cosabsphi = 1;
    }
    const double absPhi = acos ( cosabsphi );
    const double absPsi = acos ( cosabspsi );

    phi = (rzx > 0) ?  absPhi
        : (rzx < 0) ? -absPhi
        : (rzy < 0) ?       0
        :                    M_PI;

    psi = (rxz > 0) ?  absPsi
        : (rxz < 0) ? -absPsi
        : (ryz > 0) ?       0
        :                    M_PI;

  } else {              // sinTheta == 0 so |Rzz| = 1

    const double absPhi = .5 * safe_acos (rxx);

    phi = (rxy > 0) ?  absPhi
        : (rxy < 0) ? -absPhi
        : (rxx > 0) ?       0
        :                M_PI / 2;

    psi = (rzz > 0) ?  phi
        :               -phi;

  }

  return  HepEulerAngles( phi, theta, psi );

} // eulerAngles()


void HepRotation::setPhi (double phi) {
  set ( phi, theta(), psi() );
}

void HepRotation::setTheta (double theta) {
  set ( phi(), theta, psi() );
}

void HepRotation::setPsi (double psi) {
  set ( phi(), theta(), psi );
}

}  // namespace CLHEP

