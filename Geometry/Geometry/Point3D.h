// -*- C++ -*-
// $Id: Point3D.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// History:
// 09.09.96 E.Chernyaev - initial version
// 12.06.01 E.Chernyaev - CLHEP-1.7: introduction of BasicVector3D to decouple
//                        the functionality from Hep3Vector
//

#ifndef HEP_POINT3D_H
#define HEP_POINT3D_H

#include "CLHEP/Geometry/BasicVector3D.h"

class HepTransform3D;

/**
 * Geometrical 3D Point with components of double type.
 * HepPoint3D, HepVector3D and HepNormal3D have very similar
 * set of member functions. The difference among these classes
 * is how they are transformed by HepTransform3D.
 *
 * @see BasicVector3D
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepPoint3D : public BasicVector3D {       
 public:
  /// Default constructor.
  HepPoint3D() {}

  /// Constructor from three doubles.
  HepPoint3D(double x, double y, double z) : BasicVector3D(x,y,z) {}

  /// Constructor from base class.
  HepPoint3D(const BasicVector3D & v) : BasicVector3D(v) {}

  /**
   * Constructor from Hep3Vector.
   * This constructor is needed only for backward compatibility and
   * in principle should be absent.
   */
  HepPoint3D(const CLHEP::Hep3Vector & v) : BasicVector3D(v) {}

  /// Destructor.
  ~HepPoint3D() {}

  /// Assignment.
  HepPoint3D & operator=(const HepPoint3D & v) {
    set(v.x(),v.y(),v.z()); return *this;
  }

  /// Assignment from BasicVector3D and
  /// classes derived from it: HepVector3D, HepNormal3D.
  HepPoint3D & operator=(const BasicVector3D & v) {
    set(v.x(),v.y(),v.z()); return *this;
  }
 
  /// Returns distance to the origin squared.
  double distance2() const { return mag2(); }

  /// Returns distance to the point squared.
  double distance2(const HepPoint3D & p) const {
    double delx = p.x()-x(), dely = p.y()-y(), delz = p.z()-z();
    return delx*delx + dely*dely + delz*delz;
  }

  /// Returns distance to the origin.
  double distance() const { return sqrt(distance2()); }

  /// Returns distance to the point.
  double distance(const HepPoint3D & p) const { return sqrt(distance2(p)); }

  /// Transformation by HepTransform3D.
  HepPoint3D & transform(const HepTransform3D &m);
};

#include "CLHEP/Geometry/Transform3D.h"

inline HepPoint3D & HepPoint3D::transform(const HepTransform3D & m) {
  return *this = m * (*this);
}

#endif /* HEP_POINT3D_H */
