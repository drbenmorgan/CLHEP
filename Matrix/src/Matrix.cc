// -*- C++ -*-
// $Id: Matrix.cc,v 1.3 2003/07/18 05:31:48 garren Exp $
// ---------------------------------------------------------------------------
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

#ifdef GNUPRAGMA
#pragma implementation
#endif

#include "Matrix/defs.h"
#include <string.h>
#include <float.h>        // for DBL_EPSILON
#include <cmath>
#include <stdlib.h>

#include "CLHEP/Random/Random.h"

#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/DiagMatrix.h"
#include "CLHEP/Matrix/Vector.h"

#ifdef HEP_DEBUG_INLINE
#include "CLHEP/Matrix/Matrix.icc"
#endif

namespace CLHEP {

// Simple operation for all elements

#define SIMPLE_UOP(OPER)          \
   register double *a=m;            \
   register double *e=m+num_size(); \
   for(;a<e; a++) (*a) OPER t;

#define SIMPLE_BOP(OPER)          \
   register double *a=m;            \
   register double *b=m2.m;         \
   register double *e=m+num_size(); \
   for(;a<e; a++, b++) (*a) OPER (*b);

#define SIMPLE_TOP(OPER)          \
   register double *a=m1.m;            \
   register double *b=m2.m;         \
   register double *t=mret.m;         \
   register double *e=m1.m+m1.size; \
   for( ;a<e; a++, b++, t++) (*t) = (*a) OPER (*b);

// Static functions.

#define CHK_DIM_2(r1,r2,c1,c2,fun) \
   if (r1!=r2 || c1!=c2)  { \
     HepGenMatrix::error("Range error in Matrix function " #fun "(1)."); \
   }

#define CHK_DIM_1(c1,r2,fun) \
   if (c1!=r2) { \
     HepGenMatrix::error("Range error in Matrix function " #fun "(2)."); \
   }

// Constructors. (Default constructors are inlined and in .icc file)

HepMatrix::HepMatrix(int p,int q)
   : nrow(p), ncol(q)
{
  size = nrow * ncol;
  m = new_m(size);
}

HepMatrix::HepMatrix(int p,int q,int init)
   : nrow(p), ncol(q)
{
   size = nrow * ncol;
   m = new_m(size);

   memset(m, 0, size * sizeof(double));

   if (size > 0) {
      switch(init)
      {
      case 0:
	 break;

      case 1:
	 {
	    if ( ncol == nrow ) {
	       double *a = m;
	       double *b = m + size;
	       for( ; a<b; a+=(ncol+1)) *a = 1.0;
	    } else {
	       error("Invalid dimension in HepMatrix(int,int,1).");
	    }
	    break;
	 }
      default:
	 error("Matrix: initialization must be either 0 or 1.");
      }
   }
}

HepMatrix::HepMatrix(int p,int q, HepRandom &r)
   : nrow(p), ncol(q)
{
   size = nrow * ncol;
   m = new_m(size);

   double *a = m;
   double *b = m + size;
   for(; a<b; a++) *a = r();
}
//
// Destructor
//
HepMatrix::~HepMatrix() {
  delete_m(size, m);
}

HepMatrix::HepMatrix(const HepMatrix &m1)
   : nrow(m1.nrow), ncol(m1.ncol), size(m1.size)
{
   m = new_m(size);
   memcpy(m, m1.m, size*sizeof(double));
}

HepMatrix::HepMatrix(const HepSymMatrix &m1)
   : nrow(m1.nrow), ncol(m1.nrow)
{
   size = nrow * ncol;
   m = new_m(size);

   int n = ncol;
   double *sjk = m1.m;
   double *m1j = m;
   double *mj = m;
   // j >= k
   for(int j=1;j<=nrow;j++) {
      double *mjk = mj;
      double *mkj = m1j;
      for(int k=1;k<=j;k++) {
	 *(mjk++) = *sjk;
	 if(j!=k) *mkj = *sjk;
	 sjk++;
	 mkj += n;
      }
      mj += n;
      m1j++;
   }
}

HepMatrix::HepMatrix(const HepDiagMatrix &m1)
   : nrow(m1.nrow), ncol(m1.nrow)
{
   size = nrow * ncol;
   m = new_m(size);

   int n = num_row();
   memset(m, 0, size * sizeof(double));
   double *mrr = m;
   double *mr = m1.m;
   for(int r=1;r<=n;r++) {
      *mrr = *(mr++);
      mrr += (n+1);
   }
}

HepMatrix::HepMatrix(const HepVector &m1)
   : nrow(m1.nrow), ncol(1)
{
   size = nrow;
   m = new_m(size);

   memcpy(m, m1.m, size*sizeof(double));
}

//
//
// Sub matrix
//
//

HepMatrix HepMatrix::sub(int min_row, int max_row,
			 int min_col,int max_col) const
#ifdef HEP_GNU_OPTIMIZED_RETURN
return mret(max_row-min_row+1,max_col-min_col+1);
{
#else
{
  HepMatrix mret(max_row-min_row+1,max_col-min_col+1);
#endif
  if(max_row > num_row() || max_col >num_col())
    error("HepMatrix::sub: Index out of range");
  double *a = mret.m;
  int nc = num_col();
  double *b1 = m + (min_row - 1) * nc + min_col - 1;
  
  for(int irow=1; irow<=mret.num_row(); irow++) {
    double *brc = b1;
    for(int icol=1; icol<=mret.num_col(); icol++) {
      *(a++) = *(brc++);
    }
    b1 += nc;
  }
  return mret;
}

void HepMatrix::sub(int row,int col,const HepMatrix &m1)
{
  if(row <1 || row+m1.num_row()-1 > num_row() || 
     col <1 || col+m1.num_col()-1 > num_col()   )
    error("HepMatrix::sub: Index out of range");
  double *a = m1.m;
  int nc = num_col();
  double *b1 = m + (row - 1) * nc + col - 1;
  
  for(int irow=1; irow<=m1.num_row(); irow++) {
    double *brc = b1;
    for(int icol=1; icol<=m1.num_col(); icol++) {
      *(brc++) = *(a++);
    }
    b1 += nc;
  }
}

//
// Direct sum of two matricies
//

HepMatrix dsum(const HepMatrix &m1, const HepMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
  return mret(m1.num_row() + m2.num_row(), m1.num_col() + m2.num_col(),
	      0);
{
#else
{
  HepMatrix mret(m1.num_row() + m2.num_row(), m1.num_col() + m2.num_col(),
		 0);
#endif
  mret.sub(1,1,m1);
  mret.sub(m1.num_row()+1,m1.num_col()+1,m2);
  return mret;
}

/* -----------------------------------------------------------------------
   This section contains support routines for matrix.h. This section contains
   The two argument functions +,-. They call the copy constructor and +=,-=.
   ----------------------------------------------------------------------- */
HepMatrix HepMatrix::operator- () const 
#ifdef HEP_GNU_OPTIMIZED_RETURN
      return m2(nrow, ncol);
{
#else
{
   HepMatrix m2(nrow, ncol);
#endif
   register double *a=m;
   register double *b=m2.m;
   register double *e=m+num_size();
   for(;a<e; a++, b++) (*b) = -(*a);
   return m2;
}

   

HepMatrix operator+(const HepMatrix &m1,const HepMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.nrow, m1.ncol);
{
#else
{
  HepMatrix mret(m1.nrow, m1.ncol);
#endif
  CHK_DIM_2(m1.num_row(),m2.num_row(), m1.num_col(),m2.num_col(),+);
  SIMPLE_TOP(+)
  return mret;
}

//
// operator -
//

HepMatrix operator-(const HepMatrix &m1,const HepMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.num_row(), m1.num_col());
{
#else
{
  HepMatrix mret(m1.num_row(), m1.num_col());
#endif
  CHK_DIM_2(m1.num_row(),m2.num_row(),
			 m1.num_col(),m2.num_col(),-);
  SIMPLE_TOP(-)
  return mret;
}

/* -----------------------------------------------------------------------
   This section contains support routines for matrix.h. This file contains
   The two argument functions *,/. They call copy constructor and then /=,*=.
   ----------------------------------------------------------------------- */

HepMatrix operator/(
const HepMatrix &m1,double t)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepMatrix mret(m1);
#endif
  mret /= t;
  return mret;
}

HepMatrix operator*(const HepMatrix &m1,double t)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepMatrix mret(m1);
#endif
  mret *= t;
  return mret;
}

HepMatrix operator*(double t,const HepMatrix &m1)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepMatrix mret(m1);
#endif
  mret *= t;
  return mret;
}

HepMatrix operator*(const HepMatrix &m1,const HepMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.nrow,m2.ncol,0);
{
#else
{
  // initialize matrix to 0.0
  HepMatrix mret(m1.nrow,m2.ncol,0);
#endif
  CHK_DIM_1(m1.ncol,m2.nrow,*);

  int m1cols = m1.ncol;
  int m2cols = m2.ncol;

  for (int i=0; i<m1.nrow; i++)
  {
     for (int j=0; j<m1cols; j++) 
     {
	register double temp = m1.m[i*m1cols+j];
	register double *pt = mret.m + i*m2cols;
	
	// Loop over k (the column index in matrix m2)
	register double *pb = m2.m + m2cols*j;
	const double *pblast = pb + m2cols;
	while (pb < pblast)
	{
	   (*pt) += temp * (*pb);
	   pb++;
	   pt++;
	}
     }
  }

  return mret;
}

/* -----------------------------------------------------------------------
   This section contains the assignment and inplace operators =,+=,-=,*=,/=.
   ----------------------------------------------------------------------- */

HepMatrix & HepMatrix::operator+=(const HepMatrix &m2)
{
  CHK_DIM_2(num_row(),m2.num_row(),num_col(),m2.num_col(),+=);
  SIMPLE_BOP(+=)
  return (*this);
}

HepMatrix & HepMatrix::operator-=(const HepMatrix &m2)
{
  CHK_DIM_2(num_row(),m2.num_row(),num_col(),m2.num_col(),-=);
  SIMPLE_BOP(-=)
  return (*this);
}

HepMatrix & HepMatrix::operator/=(double t)
{
  SIMPLE_UOP(/=)
  return (*this);
}

HepMatrix & HepMatrix::operator*=(double t)
{
  SIMPLE_UOP(*=)
  return (*this);
}

HepMatrix & HepMatrix::operator=(const HepMatrix &m1)
{
   if(m1.nrow*m1.ncol != size)
   {
      delete_m(size,m);
      size = m1.nrow * m1.ncol;
      m = new_m(size);
   }
   nrow = m1.nrow;
   ncol = m1.ncol;
   memcpy(m,m1.m,size*sizeof(double));
   return (*this);
}

// HepMatrix & HepMatrix::operator=(const HepRotation &m2) 
// is now in Matrix=Rotation.cc

// Print the Matrix.

std::ostream& operator<<(std::ostream &s, const HepMatrix &q)
{
  s << "\n";
/* Fixed format needs 3 extra characters for field, while scientific needs 7 */
  int width;
  if(s.flags() & std::ios::fixed)
    width = s.precision()+3;
  else
    width = s.precision()+7;
  for(int irow = 1; irow<= q.num_row(); irow++)
    {
      for(int icol = 1; icol <= q.num_col(); icol++)
	{
	  s.width(width);
	  s << q(irow,icol) << " ";
	}
      s << std::endl;
    }
  return s;
}

HepMatrix HepMatrix::T() const
#ifdef HEP_GNU_OPTIMIZED_RETURN
return mret(ncol,nrow);
{
#else
{
   HepMatrix mret(ncol,nrow);
#endif
   register double *pl = m + size;
   register double *pme = m;
   register double *pt = mret.m;
   register double *ptl = mret.m + size;
   for (; pme < pl; pme++, pt+=nrow)
   {
      if (pt >= ptl) pt -= (size-1);
      (*pt) = (*pme);
   }
   return mret;
}

HepMatrix HepMatrix::apply(double (*f)(double, int, int)) const
#ifdef HEP_GNU_OPTIMIZED_RETURN
return mret(num_row(),num_col());
{
#else
{
  HepMatrix mret(num_row(),num_col());
#endif
  double *a = m;
  double *b = mret.m;
  for(int ir=1;ir<=num_row();ir++) {
    for(int ic=1;ic<=num_col();ic++) {
      *(b++) = (*f)(*(a++), ir, ic);
    }
  }
  return mret;
}

int HepMatrix::dfinv_matrix(int *ir) {
  if (num_col()!=num_row())
    error("dfinv_matrix: Matrix is not NxN");
  register int n = num_col();
  if (n==1) return 0;

  double s31, s32;
  register double s33, s34;

  double *m11 = m;
  double *m12 = m11 + 1;
  double *m21 = m11 + n;
  double *m22 = m12 + n;
  *m21 = -(*m22) * (*m11) * (*m21);
  *m12 = -(*m12);
  if (n>2) {
    double *mi = m + 2 * n;
    double *mii= m + 2 * n + 2;
    double *mimim = m + n + 1;
    for (int i=3;i<=n;i++) {
      int im2 = i - 2;
      double *mj = m;
      double *mji = mj + i - 1;
      double *mij = mi;
      for (int j=1;j<=im2;j++) { 
	s31 = 0.0;
	s32 = *mji;
	double *mkj = mj + j - 1;
	double *mik = mi + j - 1;
	double *mjkp = mj + j;
	double *mkpi = mj + n + i - 1;
	for (int k=j;k<=im2;k++) {
	  s31 += (*mkj) * (*(mik++));
	  s32 += (*(mjkp++)) * (*mkpi);
	  mkj += n;
	  mkpi += n;
	}
	*mij = -(*mii) * (((*(mij-n)))*( (*(mii-1)))+(s31));
	*mji = -s32;
	mj += n;
	mji += n;
	mij++;
      }
      *(mii-1) = -(*mii) * (*mimim) * (*(mii-1));
      *(mimim+1) = -(*(mimim+1));
      mi += n;
      mimim += (n+1);
      mii += (n+1);
    }
  }
  double *mi = m;
  double *mii = m;
  for (int i=1;i<n;i++) {
    int ni = n - i;
    double *mij = mi;
    int j;
    for (j=1; j<=i;j++) {
      s33 = *mij;
      register double *mikj = mi + n + j - 1;
      register double *miik = mii + 1;
      double *min_end = mi + n;
      for (;miik<min_end;) {
	s33 += (*mikj) * (*(miik++));
	mikj += n;
      }
      *(mij++) = s33;
    }
    for (j=1;j<=ni;j++) {
      s34 = 0.0;
      double *miik = mii + j;
      double *mikij = mii + j * n + j;
      for (int k=j;k<=ni;k++) {
	s34 += *mikij * (*(miik++));
	mikij += n;
      }
      *(mii+j) = s34;
    }
    mi += n;
    mii += (n+1);
  }
  int nxch = ir[n];
  if (nxch==0) return 0;
  for (int mm=1;mm<=nxch;mm++) {
    int k = nxch - mm + 1;
    int ij = ir[k];
    int i = ij >> 12;
    int j = ij%4096;
    double *mki = m + i - 1;
    double *mkj = m + j - 1;
    for (k=1; k<=n;k++) {
      register double ti = *mki;
      *mki = *mkj;
      *mkj = ti;
      mki += n;
      mkj += n;
    }
  }
  return 0;
}

int HepMatrix::dfact_matrix(double &det, int *ir) {
  if (ncol!=nrow)
     error("dfact_matrix: Matrix is not NxN");

  int ifail, jfail;
  register int n = ncol;

  double tf;
  double g1 = 1.0e-19, g2 = 1.0e19;

  double p, q, t;
  double s11, s12;

  double epsilon = 8*DBL_EPSILON;
  // could be set to zero (like it was before)
  // but then the algorithm often doesn't detect
  // that a matrix is singular

  int normal = 0, imposs = -1;
  int jrange = 0, jover = 1, junder = -1;
  ifail = normal;
  jfail = jrange;
  int nxch = 0;
  det = 1.0;
  double *mj = m;
  double *mjj = mj;
  for (int j=1;j<=n;j++) {
    int k = j;
    p = (fabs(*mjj));
    if (j!=n) {
      double *mij = mj + n + j - 1; 
      for (int i=j+1;i<=n;i++) {
	q = (fabs(*(mij)));
	if (q > p) {
	  k = i;
	  p = q;
	}
	mij += n;
      }
      if (k==j) {
	if (p <= epsilon) {
	  det = 0;
	  ifail = imposs;
	  jfail = jrange;
	  return ifail;
	}
	det = -det; // in this case the sign of the determinant
	            // must not change. So I change it twice. 
      }
      double *mjl = mj;
      double *mkl = m + (k-1)*n;
      for (int l=1;l<=n;l++) {
        tf = *mjl;
        *(mjl++) = *mkl;
        *(mkl++) = tf;
      }
      nxch = nxch + 1;  // this makes the determinant change its sign
      ir[nxch] = (((j)<<12)+(k));
    } else {
      if (p <= epsilon) {
	det = 0.0;
	ifail = imposs;
	jfail = jrange;
	return ifail;
      }
    }
    det *= *mjj;
    *mjj = 1.0 / *mjj;
    t = (fabs(det));
    if (t < g1) {
      det = 0.0;
      if (jfail == jrange) jfail = junder;
    } else if (t > g2) {
      det = 1.0;
      if (jfail==jrange) jfail = jover;
    }
    if (j!=n) {
      double *mk = mj + n;
      double *mkjp = mk + j;
      double *mjk = mj + j;
      for (k=j+1;k<=n;k++) {
	s11 = - (*mjk);
	s12 = - (*mkjp);
	if (j!=1) {
	  double *mik = m + k - 1;
	  double *mijp = m + j;
	  double *mki = mk;
	  double *mji = mj;
	  for (int i=1;i<j;i++) {
	    s11 += (*mik) * (*(mji++));
	    s12 += (*mijp) * (*(mki++));
	    mik += n;
	    mijp += n;
	  }
	}
	*(mjk++) = -s11 * (*mjj);
	*(mkjp) = -(((*(mjj+1)))*((*(mkjp-1)))+(s12));
	mk += n;
	mkjp += n;
      }
    }
    mj += n;
    mjj += (n+1);
  }
  if (nxch%2==1) det = -det;
  if (jfail !=jrange) det = 0.0;
  ir[n] = nxch;
  return 0;
}

void HepMatrix::invert(int &ierr) {
  if(ncol != nrow)
     error("HepMatrix::invert: Matrix is not NxN");

  static int max_array = 20;
  static int *ir = new int [max_array+1];

  if (ncol > max_array) {
    delete [] ir;
    max_array = nrow;
    ir = new int [max_array+1];
  }
  double t1, t2, t3;
  double det, temp, s;
  int ifail;
  switch(nrow) {
  case 3:
    double c11,c12,c13,c21,c22,c23,c31,c32,c33;
    ifail = 0;
    c11 = (*(m+4)) * (*(m+8)) - (*(m+5)) * (*(m+7));
    c12 = (*(m+5)) * (*(m+6)) - (*(m+3)) * (*(m+8));
    c13 = (*(m+3)) * (*(m+7)) - (*(m+4)) * (*(m+6));
    c21 = (*(m+7)) * (*(m+2)) - (*(m+8)) * (*(m+1));
    c22 = (*(m+8)) * (*m) - (*(m+6)) * (*(m+2));
    c23 = (*(m+6)) * (*(m+1)) - (*(m+7)) * (*m);
    c31 = (*(m+1)) * (*(m+5)) - (*(m+2)) * (*(m+4));
    c32 = (*(m+2)) * (*(m+3)) - (*m) * (*(m+5));
    c33 = (*m) * (*(m+4)) - (*(m+1)) * (*(m+3));
    t1 = fabs(*m);
    t2 = fabs(*(m+3));
    t3 = fabs(*(m+6));
    if (t1 >= t2) {
      if (t3 >= t1) {
      temp = *(m+6);
      det = c23*c12-c22*c13;
      } else {
	temp = *m;
	det = c22*c33-c23*c32;
      }
    } else if (t3 >= t2) {
      temp = *(m+6);
      det = c23*c12-c22*c13;
    } else {
      temp = *(m+3);
      det = c13*c32-c12*c33;
    }
    if (det==0) {
      ierr = 1;
      return;
    }
    {
      double s = temp/det;
      double *mm = m;
      *(mm++) = s*c11;
      *(mm++) = s*c21;
      *(mm++) = s*c31;
      *(mm++) = s*c12;
      *(mm++) = s*c22;
      *(mm++) = s*c32;
      *(mm++) = s*c13;
      *(mm++) = s*c23;
      *(mm) = s*c33;
    }
    break;
  case 2:
    ifail = 0;
    det = (*m)*(*(m+3)) - (*(m+1))*(*(m+2));
    if (det==0) {
      ierr = 1;
      return;
    }
    s = 1.0/det;
    temp = s*(*(m+3));
    *(m+1) *= -s;
    *(m+2) *= -s;
    *(m+3) = s*(*m);
    *m = temp;
    break;
  case 1:
    ifail = 0;
    if ((*m)==0) {
      ierr = 1;
      return;
    }
    *m = 1.0/(*m);
    break;
  case 4:
    invertHaywood4(ierr);
    return;
  case 5:
    invertHaywood5(ierr);
    return;
  case 6:
    invertHaywood6(ierr);
    return;
  default:
    ifail = dfact_matrix(det, ir);
    if(ifail) {
      ierr = 1;
      return;
    }
    dfinv_matrix(ir);
    break;
  }
  ierr = 0;
  return;
}

double HepMatrix::determinant() const {
  static int max_array = 20;
  static int *ir = new int [max_array+1];
  if(ncol != nrow)
    error("HepMatrix::determinant: Matrix is not NxN");
  if (ncol > max_array) {
    delete [] ir;
    max_array = nrow;
    ir = new int [max_array+1];
  }
  double det;
  HepMatrix mt(*this);
  int i = mt.dfact_matrix(det, ir);
  if(i==0) return det;
  return 0;
}

double HepMatrix::trace() const {
   double t = 0.0;
   double *end = m + size;
   for (double *d = m; d < end; d += (ncol+1) )
      t += *d;
   return t;
}

}  // namespace CLHEP
