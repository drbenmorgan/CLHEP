// -*- C++ -*-
// $Id: BasicVector3D.h,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// History:
// 12.06.01 Evgeni Chernyaev - CLHEP-1.7: initial version
//

#ifndef BASIC_VECTOR3D_H
#define BASIC_VECTOR3D_H

#include <iostream>
#include "CLHEP/Vector/ThreeVector.h"

/**
 * Base class for HepPoint3D, HepVector3D and HepNormal3D.
 * It only defines common functionality for those classes and
 * should not be used as separate class. For this reason the
 * default constructor is protected.
 *
 * @author <Evgueni.Tcherniaev@cern.ch>
 * @ingroup geometry
 */
class BasicVector3D {
protected:
  CLHEP::Hep3Vector v_;

  // Default constructor. This class should not be instantiated directly.
  inline BasicVector3D() : v_(0,0,0) {}

  // Constructor from CLHEP::Hep3Vector.
  inline explicit BasicVector3D(const CLHEP::Hep3Vector & v) : v_(v) {}

public:
  /// Safe indexing of the coordinates when using with matrices, arrays, etc.
  enum {
    X = 0,                      /**< index for x-component */
    Y = 1,                      /**< index for y-component */
    Z = 2,                      /**< index for z-component */
    NUM_COORDINATES = 3,        /**< number of components  */
    SIZE = NUM_COORDINATES      /**< number of components  */
  };

  /// Destructor.
  ~BasicVector3D() {}

  /// Copy constructor.
  inline BasicVector3D(const BasicVector3D & v) : v_(v.v_) {}

  /// Constructor from three doubles.
  inline BasicVector3D(double x, double y, double z) : v_(x,y,z) {}

  /**
   * Conversion (cast) to Hep3Vector.
   * This operator is needed only for backward compatibility and
   * in principle should not exit.
   */ 
  inline operator CLHEP::Hep3Vector () const { return v_; }

  /// Assignment.
  inline BasicVector3D &
  operator= (const BasicVector3D & v) { v_ = v.v_; return *this; }
  /// Adds another 3-vector.
  inline BasicVector3D &
  operator+=(const BasicVector3D & v) { v_ += v.v_; return *this; }
  /// Subtracts another 3-vector.
  inline BasicVector3D &
  operator-=(const BasicVector3D & v) { v_ -= v.v_; return *this; }
  /// Multiplies by number.
  inline BasicVector3D & operator*=(double a) { v_ *= a; return *this; }
  /// Divides by number.
  inline BasicVector3D & operator/=(double a) { v_ /= a; return *this; }

  /// Gets component by index.
  inline double operator () (int i) const { return v_(i); }
  /// Gets component by index.
  inline double operator [] (int i) const { return v_[i]; }

  /// Sets component by index.
  inline double & operator () (int i) { return v_(i); }
  /// Sets component by index.
  inline double & operator [] (int i) { return v_[i]; }

  /// Returns x-component in cartesian coordinate system.
  inline double x() const { return v_.x(); }
  /// Returns y-component in cartesian coordinate system.
  inline double y() const { return v_.y(); }
  /// Returns z-component in cartesian coordinate system.
  inline double z() const { return v_.z(); }

  /// Set x-component in cartesian coordinate system.
  inline void setX(double a) { v_.setX(a); }
  /// Set y-component in cartesian coordinate system.
  inline void setY(double a) { v_.setY(a); }
  /// Set z-component in cartesian coordinate system.
  inline void setZ(double a) { v_.setZ(a); }
  /// Sets components in cartesian coordinate system.
  inline void set(double x, double y, double z) { v_.set(x,y,z); }

  /// Returns phi-component in spherical (polar) coordinate system.
  inline double phi()      const { return v_.phi(); }
  /// Returns theta-component in spherical (polar) coordinate system.
  inline double theta()    const { return v_.theta(); }
  /// Returns cosine of theta-component in spherical (polar) coordinate system.
  inline double cosTheta() const { return v_.cosTheta(); }
  /// Returns magnitude squared of the 3-vector.
  inline double mag2()     const { return v_.mag2(); }
  /// Returns magnitude of the 3-vector.
  inline double mag()      const { return v_.mag(); }
  /// Returns r-component in spherical (polar) coordinate system.
  inline double r()        const { return v_.r(); }
  /// Returns r-component in spherical (polar) coordinate system.
  inline double getR()     const { return v_.getR(); }
  /// Returns theta-component in spherical (polar) coordinate system.
  inline double getTheta() const { return v_.getTheta(); }
  /// Returns phi-component in spherical (polar) coordinate system.
  inline double getPhi()   const { return v_.getPhi(); }

  /// Sets phi-component in spherical (polar) coordinate system.
  inline void setPhi  (double a) { v_.setPhi(a); }
  /// Sets theta-component in spherical (polar) coordinate system.
  inline void setTheta(double a) { v_.setTheta(a); }
  /// Sets magnitude.
  inline void setMag  (double a) { v_.setMag(a); }
  /// Sets r-component in spherical (polar) coordinate system.
  inline void setR    (double a) { v_.setR(a); }

  /// Gets transverse component squared (rho in cylindrical coordinate system).
  inline double perp2()  const { return v_.perp2(); }
  /// Gets transverse component (rho in cylindrical coordinate system).
  inline double perp()   const { return v_.perp(); }

  /// Gets pseudo-rapidity.
  inline double eta()    const { return v_.eta(); }
  /// Gets pseudo-rapidity.
  inline double getEta() const { return v_.getEta(); }

  /// Sets transverse component keeping phi and z constant.
  inline void setPerp(double a) { v_.setPerp(a); }

  /// Sets pseudo-rapidity, keeping magnitude and phi fixed.
  inline void setEta(double a) { v_.setEta(a); }

  /// Returns transverse component w.r.t. given axis squared.
  inline double perp2(const BasicVector3D & v) const { return v_.perp2(v); }
  /// Returns transverse component w.r.t. given axis.
  inline double perp(const BasicVector3D & v)  const { return v_.perp(v); }

  /// Returns unit 3-vector.
  inline BasicVector3D unit() const { return BasicVector3D(v_.unit()); } 

  /// Returns orthogonal 3-vector.
  inline BasicVector3D orthogonal() const {
    return BasicVector3D(v_.orthogonal());
  }

  /// Returns scalar product with another 3-vector.
  inline double dot(const BasicVector3D & v) const { return v_.dot(v.v_); }

  // Returns cross product with another 3-vector.
  inline BasicVector3D cross(const BasicVector3D & v) const {
    return BasicVector3D(v_.cross(v.v_));
  }

  /// Returns angle w.r.t. another 3-vector.
  inline double angle(const BasicVector3D & v) const {
    return v_.angle(v.v_);
  }

  /// Returns pseudo-rapidity, i.e. -ln(tan(theta/2))
  inline double pseudoRapidity() const { return v_.pseudoRapidity(); }
  
  /// Rotates the 3-vector around x-axis.
  inline BasicVector3D & rotateX(double a) { v_.rotateX(a); return *this; }
  /// Rotates the 3-vector around y-axis.
  inline BasicVector3D & rotateY(double a) { v_.rotateY(a); return *this; }
  /// Rotates the 3-vector around z-axis.
  inline BasicVector3D & rotateZ(double a) { v_.rotateZ(a); return *this; }

  /// Rotates around the axis specified by another 3-vector.
  inline BasicVector3D & rotate(double a, const BasicVector3D & v) {
    v_.rotate(a,v.v_); return *this;
  }
};

/**
 * Output to the stream.
 * @relates BasicVector3D
 */
inline std::ostream &
operator<<(std::ostream & os, const BasicVector3D & v) {
  return (os << (const CLHEP::Hep3Vector &)(v));
}

/**
 * Input from the stream.
 * @relates BasicVector3D
 */
inline std::istream &
operator>>(std::istream & is, BasicVector3D & v) {
  CLHEP::Hep3Vector w(v); is >> w; v.set(w.x(),w.y(),w.z()); return is;
}

/**
 * Unary plus.
 * @relates BasicVector3D
 */
inline BasicVector3D
operator+(const BasicVector3D & v) {
  return v;
}

/**
 * Addition of two 3-vectors.
 * @relates BasicVector3D
 */
inline BasicVector3D
operator+(const BasicVector3D & a, const BasicVector3D & b) {
  return BasicVector3D(a.x()+b.x(),a.y()+b.y(),a.z()+b.z());
}

/**
 * Unary minus.
 * @relates BasicVector3D
 */
inline BasicVector3D
operator-(const BasicVector3D & v) {
  return BasicVector3D(-v.x(),-v.y(),-v.z());
}

/**
 * Subtraction of two 3-vectors.
 * @relates BasicVector3D
 */
inline BasicVector3D
operator-(const BasicVector3D & a, const BasicVector3D & b) {
  return BasicVector3D(a.x()-b.x(),a.y()-b.y(),a.z()-b.z());
}

/**
 * Multiplication 3-vector by scalar.
 * @relates BasicVector3D
 */
inline BasicVector3D
operator*(const BasicVector3D & v, double a) {
  return BasicVector3D(v.x()*a,v.y()*a,v.z()*a);
}

/**
 * Scalar product of two 3-vectors.
 * @relates BasicVector3D
 */
inline double
operator*(const BasicVector3D & a, const BasicVector3D & b) {
  return a.dot(b);
}

/**
 * Multiplication scalar by 3-vector.
 * @relates BasicVector3D
 */
inline BasicVector3D
operator*(double a, const BasicVector3D & v) {
  return BasicVector3D(a*v.x(),a*v.y(),a*v.z());
}

/**
 * Division 3-vector by scalar.
 * @relates BasicVector3D
 */
inline BasicVector3D
operator/(const BasicVector3D & v, double a) {
  CLHEP::Hep3Vector w = CLHEP::Hep3Vector(v)/a;
  return BasicVector3D(w.x(),w.y(),w.z());
}

/**
 * Comparison of two 3-vectors for equality. 
 * @relates BasicVector3D
 */
inline bool
operator==(const BasicVector3D & a, const BasicVector3D & b) {
  return (a.x()==b.x() && a.y()==b.y() && a.z()==b.z());
}

/**
 * Comparison of two 3-vectors for inequality. 
 * @relates BasicVector3D
 */
inline bool
operator!=(const BasicVector3D & a, const BasicVector3D & b) {
  return (a.x()!=b.x() || a.y()!=b.y() || a.z()!=b.z());
}

#endif /* BASIC_VECTOR3D_H */
