// -*- C++ -*-
// $Id: Transform3D.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// Hep geometrical 3D Transformation class
//
// Author: Evgeni Chernyaev <Evgueni.Tcherniaev@cern.ch>
//
//          ******************************************
//          *                                        *
//          *               Transform                *
//          *               /  / \  \                *
//          *       --------  /   \  --------        *
//          *      /         /     \         \       *
//          *   Rotate Translate  Reflect   Scale    *
//          *    / | \    / | \    / | \    / | \    *
//          *   X  Y  Z  X  Y  Z  X  Y  Z  X  Y  Z   *
//          *                                        *
//          ******************************************
//
// Identity transformation:
//   HepTransform3D::Identity   - global identity transformation;
//   any constructor without parameters, e.g. HepTransform3D();
//   m.setIdentity()            - set "m" to identity;
//
// General transformations:
//   HepTransform3D(m,v)         - transformation given by HepRotation "m"
//                                 and Hep3Vector "v";
//   HepTransform3D(a0,a1,a2, b0,b1,b2) - transformation given by initial
//                                 and transformed positions of three points;
// Rotations:
//   HepRotate3D(m)              - rotation given by HepRotation "m";
//   HepRotate3D(ang,v)          - rotation through the angle "ang" around
//                                 vector "v";
//   HepRotate3D(ang,p1,p2)      - rotation through the angle "ang"
//                                 counterclockwise around the axis given by
//                                 two points p1->p2;
//   HepRotate3D(a1,a2, b1,b2)   - rotation around the origin defined by initial
//                                 and transformed positions of two points;
//   HepRotateX3D(ang)           - rotation around X-axis;
//   HepRotateY3D(ang)           - rotation around Y-axis;
//   HepRotateZ3D(ang)           - rotation around Z-axis;
//
// Translations:
//   HepTranslate3D(v)           - translation given by Hep3Vector "v";
//   HepTranslate3D(dx,dy,dz)    - translation on vector (dx,dy,dz);
//   HepTraslateX3D(dx)          - translation along X-axis;
//   HepTraslateY3D(dy)          - translation along Y-axis;
//   HepTraslateZ3D(dz)          - translation along Z-axis;
//
// Reflections:
//   HepReflect3D(a,b,c,d)       - reflection in the plane a*x+b*y+c*z+d=0;
//   HepReflect3D(normal,p)      - reflection in the plane going through "p"
//                                 and whose normal is equal to "normal";
//   HepReflectX3D(a)            - reflect X in the plane x=a (default a=0);
//   HepReflectY3D(a)            - reflect Y in the plane y=a (default a=0);
//   HepReflectZ3D(a)            - reflect Z in the plane z=a (default a=0);
//
// Scalings:
//   HepScale3D(sx,sy,sz)        - general scaling with factors "sx","sy","sz"
//                                 along X, Y and Z;
//   HepScale3D(s)               - scaling with constant factor "s" along all 
//                                 directions;
//   HepScaleX3D(sx)             - scale X;
//   HepScaleY3D(sy)             - scale Y;
//   HepScaleZ3D(sz)             - scale Z;
//
// Inverse transformation:
//   m.inverse() or             - returns inverse transformation;
//
// Compound transformation:
//   m3 = m2 * m1               - it is relatively slow in comparison with
//                                transformation of a vector. Use parenthesis
//                                to avoid this operation (see remark below);
// Transformation of point:
//   p2 = m * p1
//
// Transformation of vector:
//   v2 = m * v1
//
// Transformation of normal:
//   n2 = m * n1
//
// The following table explains how different transformations affect
// point, vector and normal. "+" means affect, "-" means do not affect,
// "*" meas affect but in different way than "+" 
//
//                     Point  Vector  Normal
//      -------------+-------+-------+-------
//       Rotation    !   +   !   +   !   +
//       Translation !   +   !   -   !   -
//       Reflection  !   +   !   +   !   *
//       Scaling     !   +   !   +   !   *
//      -------------+-------+-------+-------
//
// Example of the usage:
//
//   HepTransform3D m1, m2, m3;
//   HepVector3D    v2, v1(0,0,0);
//
//   m1 = HepRotate3D(angle, HepVector3D(1,1,1));
//   m2 = HepTranslate3D(dx,dy,dz);
//   m3 = m1^-1;
//
//   v2 = m3*(m2*(m1*v1));
//
// History:
// 24.09.96 E.Chernyaev - initial version
//
// 26.02.97 E.Chernyaev
// - added global Identity by request of John Allison 
//   (to avoid problems with compilation on HP) 
// - added getRotation and getTranslation 
//
// 29.01.01 E.Chernyaev - added subscripting
// 11.06.01 E.Chernyaev - added getDecomposition

#ifndef HEP_TRANSFROM3D_H
#define HEP_TRANSFROM3D_H

#include "CLHEP/Vector/ThreeVector.h"
//class CLHEP::Hep3Vector;
//class CLHEP::HepRotation;
class HepPoint3D;
class HepVector3D;
class HepNormal3D;

class HepTranslate3D;
class HepRotate3D;
class HepScale3D;

/**
 * Class for transformation of 3D objects from the Geometry module.
 * It allows different translations, rotations, scalings and reflections.
 * Several specialized classes are derived from it:
 *
 * HepTranslateX3D, HepTranslateY3D, HepTranslateZ3D, HepTranslate3D,<br>
 * HepRotateX3D, HepRotateY3D, HepRotateZ3D, HepRotate3D,            <br>
 * HepScaleX3D, HepScaleY3D, HepScaleZ3D, HepScale3D,                <br>
 * HepReflectX3D, HepReflectY3D, HepReflectZ3D, HepReflect3D.
 *
 * The idea behind these classes is to provide some additional constructors
 * for HepTransform3D, they should not be used as separate classes.
 *
 * Example:
 * @code
 *   HepTransform3D m;
 *   m = HepTranslateX3D(10.*cm);
 * @endcode
 *
 * Remark:
 * For the reason that the @e operator* is left associative, the notation
 * @code
 *   v2 = m3*(m2*(m1*v1));
 * @endcode
 * is much more effective then the notation
 * @code
 *   v2 = m3*m2*m1*v1;
 * @endcode
 * In the first case three operations @e Transform*Vector
 * are executed, in the second case two operations @e Transform*Transform and
 * one @e Transform*Vector are perfomed. @e Transform*Transform is roughly
 * 3 times slower than @e Transform*Vector.
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepTransform3D {
 protected:
  double xx, xy, xz, dx,     // 4x3  Transformation Matrix
         yx, yy, yz, dy,
         zx, zy, zz, dz;

  // Protected constructor
  HepTransform3D(double XX, double XY, double XZ, double DX,
		 double YX, double YY, double YZ, double DY,
		 double ZX, double ZY, double ZZ, double DZ)
    : xx(XX), xy(XY), xz(XZ), dx(DX),
      yx(YX), yy(YY), yz(YZ), dy(DY),
      zx(ZX), zy(ZY), zz(ZZ), dz(DZ) {}

  // Set transformation matrix
  void setTransform(double XX, double XY, double XZ, double DX,
		    double YX, double YY, double YZ, double DY,
		    double ZX, double ZY, double ZZ, double DZ) {
    xx = XX; xy = XY; xz = XZ; dx = DX;
    yx = YX; yy = YY; yz = YZ; dy = DY;
    zx = ZX; zy = ZY; zz = ZZ; dz = DZ;
  }

 public:
  /// Global identity transformation
  static const HepTransform3D Identity;

  // Helper class for implemention of C-style subscripting r[i][j] 
  class HepTransform3D_row {
  public:
    inline HepTransform3D_row(const HepTransform3D &, int);
    inline double operator [] (int) const;
  private:
    const HepTransform3D & rr;
    int ii;
  };

  /// Default constructor - sets the Identity transformation.
  HepTransform3D()
    : xx(1), xy(0), xz(0), dx(0),
      yx(0), yy(1), yz(0), dy(0),
      zx(0), zy(0), zz(1), dz(0) {}
  
  /// Constructor: rotation and then translation.
  inline HepTransform3D(const CLHEP::HepRotation &m, const CLHEP::Hep3Vector &v);

  /// Constructor: transformation of basis (assumed - no reflection).
  HepTransform3D
  (const HepPoint3D &fr0, const HepPoint3D &fr1, const HepPoint3D &fr2,
   const HepPoint3D &to0, const HepPoint3D &to1, const HepPoint3D &to2);

  /// Copy constructor.
  HepTransform3D(const HepTransform3D & m)
    : xx(m.xx), xy(m.xy), xz(m.xz), dx(m.dx),
      yx(m.yx), yy(m.yy), yz(m.yz), dy(m.dy),
      zx(m.zx), zy(m.zy), zz(m.zz), dz(m.dz) {}

  /// Returns object of the helper class for C-style subscripting r[i][j]
  inline const HepTransform3D_row operator [] (int) const; 

  /// Fortran-style subscripting: returns (i,j) element of the matrix.
  double operator () (int, int) const;

  /// Assignment.
  HepTransform3D& operator=(const HepTransform3D &m) {
    setTransform(m.xx, m.xy, m.xz, m.dx,
                 m.yx, m.yy, m.yz, m.dy,
                 m.zx, m.zy, m.zz, m.dz);
    return *this;
  }

  /// Sets the Identity transformation.
  void setIdentity() { 
    xy = xz = dx = yx = yz = dy = zx = zy = dz = 0; xx = yy = zz = 1;
  }

  /// Inverses the transformation.
  HepTransform3D inverse() const;

  /// Transformation by another HepTransform3D.
  inline HepTransform3D operator*(const HepTransform3D &b) const;

  /// Transforms the HepPoint3D.
  inline HepPoint3D operator*(const HepPoint3D &p) const;

  /// Transforms the HepVector3D.
  inline HepVector3D operator*(const HepVector3D &v) const;

  /// Transforms the HepNormal3D.
  inline HepNormal3D operator*(const HepNormal3D &n) const;

  /**
   * Decomposition of general transformation.
   * This function gets decomposition of the transformation
   * in three consequentive specific transformations: Scale,
   * then Rotation, then Translation, i.e.
   * @code
   *   Transformation = Translation * Rotation * Scale
   * @endcode
   *
   * @param scale       output: scaling transformation;
   *                    if there was a reflection, then scale factor for
   *                    z-component scale(2,2) will be negative.
   * @param rotation    output: rotation transformaion.
   * @param translation output: translation transformaion.
   */
  void getDecomposition(HepScale3D & scale,
			HepRotate3D & rotation,
			HepTranslate3D & translation) const;

  /**
   * Returns true if the difference between corresponding
   * matrix elements is less than the tolerance.
   */
  bool isNear(const HepTransform3D & t, double tolerance = 2.2E-14 ) const;

  /**
   * Extracts the rotation matrix.
   * This functions is obsolete - use getDecomposition() instead.
   */
  inline CLHEP::HepRotation getRotation() const;

  /**
   * Extracts the translation vector.
   * This functions is obsolete - use getDecomposition() instead.
   */
  inline CLHEP::Hep3Vector getTranslation() const;

  /// Test for equality.
  bool operator == (const HepTransform3D & transform) const;

  /// Test for inequality.
  bool operator != (const HepTransform3D & transform) const {
    return ! operator==(transform);
  }
};

//   R O T A T I O N S

/**
 * Constructs a rotation transformation.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepRotate3D(30.*deg, HepVector3D(1.,1.,1.));
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepRotate3D : public HepTransform3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepRotate3D() : HepTransform3D() {}

  /// Constructor from HepRotation.
  inline HepRotate3D(const CLHEP::HepRotation &m);

  /**
   * Constructor from angle and axis given by two points.
   * @param a  angle of rotation
   * @param p1 begin point of the axis
   * @param p2 end point of the axis
   */
  HepRotate3D(double a, const HepPoint3D &p1, const HepPoint3D &p2);

  /**
   * Constructor from angle and axis.
   * @param a angle of rotation
   * @param v axis of rotation
   */
  inline HepRotate3D(double a, const HepVector3D &v);

  /**
   * Constructor for rotation given by original and rotated position of
   * two points. It is assumed that there is no reflection.
   * @param fr1 original position of 1st point
   * @param fr2 original position of 2nd point
   * @param to1 rotated position of 1st point
   * @param to2 rotated position of 2nd point
   */
  inline HepRotate3D(const HepPoint3D &fr1, const HepPoint3D &fr2,
		     const HepPoint3D &to1, const HepPoint3D &to2);
};

/**
 * Constructs a rotation around x-axis.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepRotateX3D(30.*deg);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepRotateX3D : public HepRotate3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepRotateX3D() : HepRotate3D() {}
  /// Constructs a rotation around x-axis by angle a.
  HepRotateX3D(double a) {
    double cosa = cos(a), sina = sin(a); 
    setTransform(1,0,0,0,  0,cosa,-sina,0,  0,sina,cosa,0);
  }
};

/**
 * Constructs a rotation around y-axis.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepRotateY3D(30.*deg);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepRotateY3D : public HepRotate3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepRotateY3D() : HepRotate3D() {}
  /// Constructs a rotation around y-axis by angle a.
  HepRotateY3D(double a) {
    double cosa = cos(a), sina = sin(a); 
    setTransform(cosa,0,sina,0,  0,1,0,0,  -sina,0,cosa,0);
  }
};

/**
 * Constructs a rotation around z-axis.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepRotateZ3D(30.*deg);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepRotateZ3D : public HepRotate3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepRotateZ3D() : HepRotate3D() {}
  /// Constructs a rotation around z-axis by angle a.
  HepRotateZ3D(double a) {
    double cosa = cos(a), sina = sin(a); 
    setTransform(cosa,-sina,0,0,  sina,cosa,0,0,  0,0,1,0);
  }
};

//   T R A N S L A T I O N S

/**
 * Constructs a translation transformation.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepTranslate3D(10.,20.,30.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepTranslate3D : public HepTransform3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepTranslate3D() : HepTransform3D() {}
  /// Constructor from Hep3Vector.
  inline HepTranslate3D(const CLHEP::Hep3Vector &v);
  /// Constructor from three numbers.
  HepTranslate3D(double x, double y, double z)
    : HepTransform3D(1,0,0,x, 0,1,0,y, 0,0,1,z) {}
};

/**
 * Constructs a translation along x-axis.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepTranslateX3D(10.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepTranslateX3D : public HepTranslate3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepTranslateX3D() : HepTranslate3D() {}
  /// Constructor from a number.
  HepTranslateX3D(double x) : HepTranslate3D(x, 0, 0) {}
};

/**
 * Constructs a translation along y-axis.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepTranslateY3D(10.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepTranslateY3D : public HepTranslate3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepTranslateY3D() : HepTranslate3D() {}
  /// Constructor from a number.
  HepTranslateY3D(double y) : HepTranslate3D(0, y, 0) {}
};

/**
 * Constructs a translation along z-axis.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepTranslateZ3D(10.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepTranslateZ3D : public HepTranslate3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepTranslateZ3D() : HepTranslate3D() {}
  /// Constructor from a number.
  HepTranslateZ3D(double z) : HepTranslate3D(0, 0, z) {}
};

//   R E F L E C T I O N S

/**
 * Constructs a reflection transformation.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepReflect3D(1.,1.,1.,0.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepReflect3D : public HepTransform3D {
 protected:
  HepReflect3D(double XX, double XY, double XZ, double DX,
               double YX, double YY, double YZ, double DY,
               double ZX, double ZY, double ZZ, double DZ)
    : HepTransform3D(XX,XY,XZ,DX, YX,YY,YZ,DY, ZX,ZY,ZZ,DZ) {}

 public:
  /// Default constructor: sets the Identity transformation.
  HepReflect3D() : HepTransform3D() {}
  /// Constructor from four numbers: sets reflection in a plane a*x+b*y+c*z+d=0
  HepReflect3D(double a, double b, double c, double d);
  inline HepReflect3D(const HepNormal3D &normal, const HepPoint3D &point);
};

/**
 * Constructs reflection in a plane x=const.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepReflectX3D(1.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepReflectX3D : public HepReflect3D {
 public:
  /// Constructor from a number.
  HepReflectX3D(double x=0) : HepReflect3D(-1,0,0,x+x, 0,1,0,0, 0,0,1,0) {}
};
 
/**
 * Constructs reflection in a plane y=const.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepReflectY3D(1.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepReflectY3D : public HepReflect3D {
 public:
  /// Constructor from a number.
  HepReflectY3D(double y=0) : HepReflect3D(1,0,0,0, 0,-1,0,y+y, 0,0,1,0) {}
};
 
/**
 * Constructs reflection in a plane z=const.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepReflectZ3D(1.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepReflectZ3D : public HepReflect3D {
 public:
  /// Constructor from a number.
  HepReflectZ3D(double z=0) : HepReflect3D(1,0,0,0, 0,1,0,0, 0,0,-1,z+z) {}
};
 
//   S C A L I N G S

/**
 * Constructs a scaling transformation.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepScale3D(2.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepScale3D : public HepTransform3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepScale3D() : HepTransform3D() {}
  /// Constructor from three numbers (scale factors in different directions).
  HepScale3D(double x, double y, double z)
    : HepTransform3D(x,0,0,0, 0,y,0,0, 0,0,z,0) {}
  /// Constructor from a number: sets uniform scaling in all directions.
  HepScale3D(double s)
    : HepTransform3D(s,0,0,0, 0,s,0,0, 0,0,s,0) {}
};

/**
 * Constructs a scaling transformation in x-direction.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepScaleX3D(2.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepScaleX3D : public HepScale3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepScaleX3D() : HepScale3D() {}
  /// Constructor from a number (scale factor in x-direction).
  HepScaleX3D(double x) : HepScale3D(x, 1, 1) {}
};

/**
 * Constructs a scaling transformation in y-direction.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepScaleY3D(2.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepScaleY3D : public HepScale3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepScaleY3D() : HepScale3D() {}
  /// Constructor from a number (scale factor in y-direction).
  HepScaleY3D(double y) : HepScale3D(1, y, 1) {}
};

/**
 * Constructs a scaling transformation in z-direction.
 * This class provides additional constructors for HepTransform3D
 * and should not be used as a separate class.
 * 
 * Example of use:
 * @code
 *   HepTransform3D m;
 *   m = HepScaleZ3D(2.);
 * @endcode
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class HepScaleZ3D : public HepScale3D {
 public:
  /// Default constructor: sets the Identity transformation.
  HepScaleZ3D() : HepScale3D() {}
  /// Constructor from a number (scale factor in z-direction).
  HepScaleZ3D(double z) : HepScale3D(1, 1, z) {}
};

//   I N L I N E S   F O R   T R A N S F O R M A T I O N

#include "CLHEP/Vector/ThreeVector.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Geometry/Point3D.h"
#include "CLHEP/Geometry/Vector3D.h"
#include "CLHEP/Geometry/Normal3D.h"

inline
HepTransform3D::HepTransform3D_row::HepTransform3D_row
(const HepTransform3D & r, int i) : rr(r), ii(i) {}

inline
double HepTransform3D::HepTransform3D_row::operator[](int jj) const {
  return rr(ii,jj);
}

inline const HepTransform3D::HepTransform3D_row
HepTransform3D::operator[](int i) const {
  return HepTransform3D_row(*this, i);
}

inline
HepTransform3D::HepTransform3D(const CLHEP::HepRotation &m, const CLHEP::Hep3Vector &v) {
  CLHEP::Hep3Vector w;
  w = m * CLHEP::Hep3Vector(1,0,0); xx = w.x(); yx = w.y(); zx = w.z();
  w = m * CLHEP::Hep3Vector(0,1,0); xy = w.x(); yy = w.y(); zy = w.z();
  w = m * CLHEP::Hep3Vector(0,0,1); xz = w.x(); yz = w.y(); zz = w.z();
  dx = v.x(); dy = v.y(); dz = v.z();
}

inline
HepTransform3D HepTransform3D::operator*(const HepTransform3D &b) const {
  return HepTransform3D
    (xx*b.xx+xy*b.yx+xz*b.zx, xx*b.xy+xy*b.yy+xz*b.zy,
     xx*b.xz+xy*b.yz+xz*b.zz, xx*b.dx+xy*b.dy+xz*b.dz+dx,
     yx*b.xx+yy*b.yx+yz*b.zx, yx*b.xy+yy*b.yy+yz*b.zy,
     yx*b.xz+yy*b.yz+yz*b.zz, yx*b.dx+yy*b.dy+yz*b.dz+dy,
     zx*b.xx+zy*b.yx+zz*b.zx, zx*b.xy+zy*b.yy+zz*b.zy,
     zx*b.xz+zy*b.yz+zz*b.zz, zx*b.dx+zy*b.dy+zz*b.dz+dz);
}

inline
HepPoint3D HepTransform3D::operator*(const HepPoint3D &p) const {
  double x = p.x(), y = p.y(), z = p.z(); 
  return HepPoint3D(x*xx+y*xy+z*xz+dx, x*yx+y*yy+z*yz+dy, x*zx+y*zy+z*zz+dz);
}

inline
HepVector3D HepTransform3D::operator*(const HepVector3D &v) const {
  double x = v.x(), y = v.y(), z = v.z(); 
  return HepPoint3D(x*xx+y*xy+z*xz, x*yx+y*yy+z*yz, x*zx+y*zy+z*zz);
}

inline
HepNormal3D HepTransform3D::operator*(const HepNormal3D &n) const {
  double x = n.x(), y = n.y(), z = n.z(); 
  return HepNormal3D(x*(yy*zz-yz*zy) + y*(yz*zx-yx*zz) + z*(yx*zy-yy*zx),
		     x*(zy*xz-zz*xy) + y*(zz*xx-zx*xz) + z*(zx*xy-zy*xx),
		     x*(xy*yz-xz*yy) + y*(xz*yx-xx*yz) + z*(xx*yy-xy*yx));
}

inline
CLHEP::HepRotation HepTransform3D::getRotation() const {
  CLHEP::HepRotation m;
  return m.rotateAxes(CLHEP::Hep3Vector(xx,yx,zx),
		      CLHEP::Hep3Vector(xy,yy,zy),
                      CLHEP::Hep3Vector(xz,yz,zz));
}

inline
CLHEP::Hep3Vector HepTransform3D::getTranslation() const {
  return CLHEP::Hep3Vector(dx,dy,dz); 
}

//   I N L I N E S   F O R   R O T A T I O N

inline HepRotate3D::HepRotate3D(const CLHEP::HepRotation &m) {
  CLHEP::Hep3Vector w;
  w = m * CLHEP::Hep3Vector(1,0,0); xx = w.x(); yx = w.y(); zx = w.z();
  w = m * CLHEP::Hep3Vector(0,1,0); xy = w.x(); yy = w.y(); zy = w.z();
  w = m * CLHEP::Hep3Vector(0,0,1); xz = w.x(); yz = w.y(); zz = w.z();
  dx = 0; dy = 0; dz = 0;
}

inline HepRotate3D::HepRotate3D(double a, const HepVector3D &v) {
  *this = HepRotate3D(a, HepPoint3D(0,0,0), HepPoint3D(v.x(),v.y(),v.z()));
}

inline HepRotate3D::HepRotate3D(const HepPoint3D &fr1, const HepPoint3D &fr2,
			        const HepPoint3D &to1, const HepPoint3D &to2)
  : HepTransform3D(HepPoint3D(0,0,0),fr1,fr2, HepPoint3D(0,0,0),to1,to2) {}

//   I N L I N E S   F O R   T R A N S L A T I O N

inline HepTranslate3D::HepTranslate3D(const CLHEP::Hep3Vector &v)
  : HepTransform3D(1,0,0,v.x(), 0,1,0,v.y(), 0,0,1,v.z()) {}

//   I N L I N E S   F O R   R E F L E C T I O N

inline HepReflect3D::HepReflect3D(const HepNormal3D &n, const HepPoint3D &p) {
  *this = HepReflect3D(n.x(), n.y(), n.z(), -n*p);
}

#endif /* HEP_TRANSFROM3D_H */
