// -*- C++ -*-
// $Id: Plane3D.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// History:
// 22.09.96 E.Chernyaev - initial version
// 19.10.96 J.Allison - added == and <<.

#ifndef HEP_PLANE3D_H
#define HEP_PLANE3D_H

#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Geometry/Normal3D.h"
#include <iostream>

/**
 * Geometrical 3D Plane.
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepPlane3D {
 protected:
  double aa, bb, cc, dd;
 
 public:
  /**
   * Constructor from four numbers.
   * The numbers are the coefficients of the equation of the plane:
   * @code
   *   a*x+b*y+c*z+d=0
   * @endcode
   */
  HepPlane3D(double a=0, double b=0, double c=0, double d=0)
    : aa(a), bb(b), cc(c), dd(d) {}

  /// Constructor from normal and point.
  HepPlane3D(const HepNormal3D &n, const HepPoint3D &p)
    : aa(n.x()), bb(n.y()), cc(n.z()), dd(-n*p) {}

  /// Constructor from three points.
  HepPlane3D(const HepPoint3D &p1, const HepPoint3D &p2, const HepPoint3D &p3)
  {
    HepNormal3D n = (p2-p1).cross(p3-p1);
    aa = n.x(); bb = n.y(); cc = n.z(); dd = -n*p1;
  }

  /// Copy constructor.
  HepPlane3D(const HepPlane3D &plane)
    : aa(plane.aa), bb(plane.bb), cc(plane.cc), dd(plane.dd) {}

  /// Destructor.
  ~HepPlane3D() {};

  /// Assignment.
  HepPlane3D& operator=(const HepPlane3D &plane) {
   aa = plane.aa; bb = plane.bb; cc = plane.cc; dd = plane.dd; return *this;
  }

  /// Test for equality.
  bool operator == (const HepPlane3D& p) const {
    return aa == p.aa && bb == p.bb && cc == p.cc && dd == p.dd;
  }

  /// Test for inequality.
  bool operator != (const HepPlane3D& p) const {
    return aa != p.aa || bb != p.bb || cc != p.cc || dd != p.dd;
  }

  /// Normalization.
  HepPlane3D& normalize() {
    double ll = sqrt(aa*aa + bb*bb + cc*cc);
    if (ll > 0.0) { aa /= ll; bb /= ll; cc /= ll, dd /= ll; }
    return *this;
  }

  /// Returns coefficient a from the plane defining equation.
  double a() const { return aa; }
  /// Returns coefficient b from the plane defining equation.
  double b() const { return bb; }
  /// Returns coefficient c from the plane defining equation.
  double c() const { return cc; }
  /// Returns free member d from the plane defining equation.
  double d() const { return dd; }

  /// Returns normal.
  HepNormal3D normal() const { return HepNormal3D(aa,bb,cc); }

  /// Returns distance from the point.
  double distance(const HepPoint3D &p) const {
    return aa*p.x() + bb*p.y() + cc*p.z() + dd;
  }

  /// Returns projection of the point to the plane.
  HepPoint3D point(const HepPoint3D &p) const {
    double k = distance(p)/(aa*aa+bb*bb+cc*cc);
    return HepPoint3D(p.x()-aa*k, p.y()-bb*k, p.z()-cc*k);
  }

  /// Returns projection of the origin to the plane.
  HepPoint3D point() const {
    double k = -dd/(aa*aa+bb*bb+cc*cc);
    return HepPoint3D(aa*k, bb*k, cc*k);
  }

  /// Transformation by HepTransform3D.
  HepPlane3D& transform(const HepTransform3D &m) {
    HepNormal3D n(aa,bb,cc);
    n.transform(m);
    dd = -n*point().transform(m); aa = n.x(); bb = n.y(); cc = n.z();
    return *this;
  }
};

/**
 * Output to the stream.
 * @relates HepPlane3D
 */
std::ostream & operator << (std::ostream &, const HepPlane3D &);

#endif /* HEP_PLANE3D_H */
