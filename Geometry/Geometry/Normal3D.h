// -*- C++ -*-
// $Id: Normal3D.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// History:
// 13.09.96 E.Chernyaev - initial version
// 12.06.01 E.Chernyaev - CLHEP-1.7: introduction of BasicVector3D to decouple
//                        the functionality from Hep3Vector
//
 
#ifndef HEP_NORMAL3D_H
#define HEP_NORMAL3D_H

#include "CLHEP/Geometry/BasicVector3D.h"

class HepTransform3D;

/**
 * Geometrical 3D Normal with components of double type.
 * HepPoint3D, HepVector3D and HepNormal3D have very similar
 * set of member functions. The difference among these classes
 * is how they are transformed by HepTransform3D.
 *
 * @see BasicVector3D
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepNormal3D : public BasicVector3D {
 public:
  /// Default constructor.
  HepNormal3D() {}

  /// Constructor from three doubles.
  HepNormal3D(double x, double y, double z) : BasicVector3D(x,y,z) {}

  /// Constructor from base class.
  HepNormal3D(const BasicVector3D & v) : BasicVector3D(v) {}

  /**
   * Constructor from Hep3Vector.
   * This constructor is needed only for backward compatibility and
   * in principle should be absent.
   */
  HepNormal3D(const CLHEP::Hep3Vector & v) : BasicVector3D(v) {}

  /// Destructor.
  ~HepNormal3D() {}

  /// Assignment.
  HepNormal3D & operator=(const HepNormal3D & v) {
    set(v.x(), v.y(), v.z()); return *this;
  }

  /// Assignment from BasicVector3D and
  /// classes derived from it: HepPoint3D, HepVector3D.
  HepNormal3D & operator=(const BasicVector3D & v) {
    set(v.x(), v.y(), v.z()); return *this;
  }

  /// Transformation by HepTransform3D.
  HepNormal3D & transform(const HepTransform3D & m);
};

#include "CLHEP/Geometry/Transform3D.h"

inline HepNormal3D & HepNormal3D::transform(const HepTransform3D & m) {
  return *this = m * (*this);
}

#endif /* HEP_NORMAL3D_H */
