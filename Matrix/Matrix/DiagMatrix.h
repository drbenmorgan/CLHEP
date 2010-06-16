// -*- C++ -*-
// CLASSDOC OFF
// ---------------------------------------------------------------------------
// CLASSDOC ON
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// 
// Copyright Cornell University 1993, 1996, All Rights Reserved.
// 
// This software written by Nobu Katayama and Mike Smyth, Cornell University.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice and author attribution, this list of conditions and the
//    following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright
//    notice and author attribution, this list of conditions and the
//    following disclaimer in the documentation and/or other materials
//    provided with the distribution.
// 3. Neither the name of the University nor the names of its contributors
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// 
// Creation of derivative forms of this software for commercial
// utilization may be subject to restriction; written permission may be
// obtained from Cornell University.
// 
// CORNELL MAKES NO REPRESENTATIONS OR WARRANTIES, EXPRESS OR IMPLIED.  By way
// of example, but not limitation, CORNELL MAKES NO REPRESENTATIONS OR
// WARRANTIES OF MERCANTABILITY OR FITNESS FOR ANY PARTICULAR PURPOSE OR THAT
// THE USE OF THIS SOFTWARE OR DOCUMENTATION WILL NOT INFRINGE ANY PATENTS,
// COPYRIGHTS, TRADEMARKS, OR OTHER RIGHTS.  Cornell University shall not be
// held liable for any liability with respect to any claim by the user or any
// other party arising from use of the program.
//
// 
//
// DiagMatrix is a class for diagonal matrix. This is useful for a covariance
// matrix of measured quantities since they are uncorrelated to each other
// and therefore diagonal. It is obviously smaller and faster to manipulate.
//

#ifndef _DIAGMatrix_H_
#define _DIAGMatrix_H_

#ifdef GNUPRAGMA
#pragma interface
#endif

#include <vector>

#include "CLHEP/Matrix/defs.h"
#include "CLHEP/Matrix/GenMatrix.h"

namespace CLHEP {

class HepRandom;

class HepMatrix;
class HepSymMatrix;
class HepVector;

/**
 * @author
 * @ingroup matrix
 */
class HepDiagMatrix: public HepGenMatrix {
public:
   inline HepDiagMatrix();
   // Default constructor. Gives 0x0 matrix. Another Matrix can be assigned
   // to it.

   explicit HepDiagMatrix(int p);
   HepDiagMatrix(int p, int);
   // Constructor. Gives p x p diagonal matrix.
   // With a second argument, either 0 or 1, the matrix is initialized.
   // 0 means a zero matrix, 1 means the identity matrix.

   HepDiagMatrix(int p, HepRandom &r);

   HepDiagMatrix(const HepDiagMatrix &m1);
   // Copy constructor.

   virtual ~HepDiagMatrix();
   // Destructor.

   inline int num_row() const;
   inline int num_col() const;
   // Returns the number of rows/columns. (Should be equal.)

   double &operator()(int row, int col);
   const double &operator()(int row, int col) const; 
   // Read or write a matrix element. row must be equal to col.
   // ** Note that indexing starts from (1,1). **
   
   double &fast(int row, int col);
   const double &fast(int row, int col) const;
   // fast element access.
   // Must be row>=col;
   // ** Note that indexing starts from (1,1). **

   void assign(const HepMatrix &m2);
   // Assigns m2 to d, assuming m2 is a diagnal matrix.

   void assign(const HepSymMatrix &m2);
   // Assigns m2 to d, assuming m2 is a diagnal matrix.

   void assign(const HepDiagMatrix &m2);
   // Another form of assignment. For consistency.

   HepDiagMatrix & operator*=(double t);
   // Multiply a DiagMatrix by a floating number

   HepDiagMatrix & operator/=(double t); 
   // Divide a DiagMatrix by a floating number

   HepDiagMatrix & operator+=( const HepDiagMatrix &m2);
   HepDiagMatrix & operator-=( const HepDiagMatrix &m2);
   // Add or subtract a DiagMatrix.

   HepDiagMatrix & operator=( const HepDiagMatrix &m2);
   // Assignment operator. To assign SymMatrix to DiagMatrix, use d<<s.

   HepDiagMatrix operator- () const;
   // unary minus, ie. flip the sign of each element.

   HepDiagMatrix T() const;
   // Returns the transpose of a DiagMatrix (which is itself).

   HepDiagMatrix apply(double (*f)(double,
					       int, int)) const;
   // Apply a function to all elements of the matrix.

   HepSymMatrix similarity(const HepMatrix &m1) const;
   // Returns m1*s*m1.T().
   HepSymMatrix similarityT(const HepMatrix &m1) const;
   // Returns m1.T()*s*m1.

   double similarity(const HepVector &) const;
   // Returns v.T()*s*v (This is a scaler).

   HepDiagMatrix sub(int min_row, int max_row) const;
   // Returns a sub matrix of a SymMatrix.
   HepDiagMatrix sub(int min_row, int max_row);
   // SGI CC bug. I have to have both with/without const. I should not need
   // one without const.

   void sub(int row, const HepDiagMatrix &m1);
   // Sub matrix of this SymMatrix is replaced with m1.

   HepDiagMatrix inverse(int&ierr) const;
   // Invert a Matrix. The matrix is not changed
   // Returns 0 when successful, otherwise non-zero.

   void invert(int&ierr);
   // Invert a Matrix.
   // N.B. the contents of the matrix are replaced by the inverse.
   // Returns ierr = 0 when successful, otherwise non-zero. 
   // This method has less overhead then inverse().

   double determinant() const;
   // calculate the determinant of the matrix.

   double trace() const;
   // calculate the trace of the matrix (sum of diagonal elements).

   class HepDiagMatrix_row {
   public:
      inline HepDiagMatrix_row(HepDiagMatrix&,int);
      inline double & operator[](int);
   private:
      HepDiagMatrix& _a;
      int _r;
   };
   class HepDiagMatrix_row_const {
   public:
      inline HepDiagMatrix_row_const(const HepDiagMatrix&,int);
      inline const double & operator[](int) const;
   private:
      const HepDiagMatrix& _a;
      int _r;
   };
   // helper classes to implement m[i][j]

   inline HepDiagMatrix_row operator[] (int);
   inline HepDiagMatrix_row_const operator[] (int) const;
   // Read or write a matrix element.
   // While it may not look like it, you simply do m[i][j] to get an
   // element. 
   // ** Note that the indexing starts from [0][0]. **

protected:
   inline int num_size() const;

private:
   friend class HepDiagMatrix_row;
   friend class HepDiagMatrix_row_const;
   friend class HepMatrix;
   friend class HepSymMatrix;

   friend HepDiagMatrix operator*(const HepDiagMatrix &m1,
				   const HepDiagMatrix &m2);
   friend HepDiagMatrix operator+(const HepDiagMatrix &m1,
				   const HepDiagMatrix &m2);
   friend HepDiagMatrix operator-(const HepDiagMatrix &m1,
				   const HepDiagMatrix &m2);
   friend HepMatrix operator*(const HepDiagMatrix &m1, const HepMatrix &m2);
   friend HepMatrix operator*(const HepMatrix &m1, const HepDiagMatrix &m2);
   friend HepVector operator*(const HepDiagMatrix &m1, const HepVector &m2);

#ifdef DISABLE_ALLOC
   std::vector<double > m;
#else
   std::vector<double,Alloc<double,25> > m;
#endif
   int nrow;
#if defined(__sun) || !defined(__GNUG__)
//
// Sun CC 4.0.1 has this bug.
//
   static double zero;
#else
   static const double zero;
#endif
};

std::ostream& operator<<(std::ostream &s, const HepDiagMatrix &q);
// Write out Matrix, SymMatrix, DiagMatrix and Vector into ostream.

HepMatrix operator*(const HepMatrix &m1, const HepDiagMatrix &m2);
HepMatrix operator*(const HepDiagMatrix &m1, const HepMatrix &m2);
HepDiagMatrix operator*(double t, const HepDiagMatrix &d1);
HepDiagMatrix operator*(const HepDiagMatrix &d1, double t);
// Multiplication operators
// Note that m *= m1 is always faster than m = m * m1

HepDiagMatrix operator/(const HepDiagMatrix &m1, double t);
// d = d1 / t. (d /= t is faster if you can use it.)

HepMatrix operator+(const HepMatrix &m1, const HepDiagMatrix &d2);
HepMatrix operator+(const HepDiagMatrix &d1, const HepMatrix &m2);
HepDiagMatrix operator+(const HepDiagMatrix &m1, const HepDiagMatrix &d2);
HepSymMatrix operator+(const HepSymMatrix &s1, const HepDiagMatrix &d2);
HepSymMatrix operator+(const HepDiagMatrix &d1, const HepSymMatrix &s2);
// Addition operators

HepMatrix operator-(const HepMatrix &m1, const HepDiagMatrix &d2);
HepMatrix operator-(const HepDiagMatrix &d1, const HepMatrix &m2);
HepDiagMatrix operator-(const HepDiagMatrix &d1, const HepDiagMatrix &d2);
HepSymMatrix operator-(const HepSymMatrix &s1, const HepDiagMatrix &d2);
HepSymMatrix operator-(const HepDiagMatrix &d1, const HepSymMatrix &s2);
// Subtraction operators

HepDiagMatrix dsum(const HepDiagMatrix &s1, const HepDiagMatrix &s2);
// Direct sum of two diagonal matricies;

}  // namespace CLHEP

#ifdef ENABLE_BACKWARDS_COMPATIBILITY
//  backwards compatibility will be enabled ONLY in CLHEP 1.9
using namespace CLHEP;
#endif

#ifndef HEP_DEBUG_INLINE
#include "CLHEP/Matrix/DiagMatrix.icc"
#endif

#endif /*!_DIAGMatrix_H*/
