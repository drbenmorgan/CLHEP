// -*- C++ -*-
// $Id: DiagMatrix.cc,v 1.3 2003/07/18 05:31:48 garren Exp $
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
#include <cmath>

#include "CLHEP/Random/Random.h"

#include "CLHEP/Matrix/DiagMatrix.h"
#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/Vector.h"

#ifdef HEP_DEBUG_INLINE
#include "CLHEP/Matrix/DiagMatrix.icc"
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
   register double *e=m1.m+m1.nrow; \
   for( ;a<e; a++, b++, t++) (*t) = (*a) OPER (*b);

#define CHK_DIM_2(r1,r2,c1,c2,fun) \
   if (r1!=r2 || c1!=c2)  { \
    HepGenMatrix::error("Range error in DiagMatrix function " #fun "(1)."); \
   }

#define CHK_DIM_1(c1,r2,fun) \
   if (c1!=r2) { \
    HepGenMatrix::error("Range error in DiagMatrix function " #fun "(2)."); \
   }

// static constant

#if defined(__sun) || !defined(__GNUG__)
//
// Sun CC 4.0.1 has this bug.
//
double HepDiagMatrix::zero = 0;
#else
const double HepDiagMatrix::zero = 0;
#endif

// Constructors. (Default constructors are inlined and in .icc file)

HepDiagMatrix::HepDiagMatrix(int p)
   : nrow(p)
{
   m = new_m(nrow);
}

HepDiagMatrix::HepDiagMatrix(int p, int init)
   : nrow(p)
{
   m = new_m(nrow);
   
   switch(init)
   {
   case 0:
      memset(m, 0, nrow * sizeof(double));
      break;

   case 1:
      {
	 double *a=m;
	 double *b=m + p;
	 for( ; a<b; a++) *a = 1.0;
	 break;
      }
   default:
      error("DiagMatrix: initialization must be either 0 or 1.");
   }
}

HepDiagMatrix::HepDiagMatrix(int p, HepRandom &r)
  : nrow(p)
{
   m = new_m(nrow);
   double *a = m;
   double *b = m + num_size();
   for(;a<b;a++) *a = r();
}
//
// Destructor
//
HepDiagMatrix::~HepDiagMatrix() {
   delete_m(nrow, m);
}

HepDiagMatrix::HepDiagMatrix(const HepDiagMatrix &m1)
   : nrow(m1.nrow)
{
   m = new_m(nrow);
   memcpy(m, m1.m, nrow*sizeof(double));
}

//
//
// Sub matrix
//
//

HepDiagMatrix HepDiagMatrix::sub(int min_row, int max_row) const
#ifdef HEP_GNU_OPTIMIZED_RETURN
return mret(max_row-min_row+1);
{
#else
{
  HepDiagMatrix mret(max_row-min_row+1);
#endif
  if(max_row > num_row())
    error("HepDiagMatrix::sub: Index out of range");
  double *a = mret.m;
  double *b = m + min_row - 1;
  double *e = mret.m + mret.num_row();
  for(;a<e;) *(a++) = *(b++);
  return mret;
}

#ifdef HEP_CC_NEED_SUB_WITHOUT_CONST
HepDiagMatrix HepDiagMatrix::sub(int min_row, int max_row)
{
  HepDiagMatrix mret(max_row-min_row+1);
  if(max_row > num_row())
    error("HepDiagMatrix::sub: Index out of range");
  double *a = mret.m;
  double *b = m + min_row - 1;
  double *e = mret.m + mret.num_row();
  for(;a<e;) *(a++) = *(b++);
  return mret;
}
#endif

void HepDiagMatrix::sub(int row,const HepDiagMatrix &m1)
{
  if(row <1 || row+m1.num_row()-1 > num_row() )
    error("HepDiagMatrix::sub: Index out of range");
  double *a = m1.m;
  double *b = m + row - 1;
  double *e = m1.m + m1.num_row();
  for(;a<e;) *(b++) = *(a++);
}

//
// Direct sum of two matricies
//

HepDiagMatrix dsum(const HepDiagMatrix &m1,
				     const HepDiagMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
  return mret(m1.num_row() + m2.num_row(), 0);
{
#else
{
  HepDiagMatrix mret(m1.num_row() + m2.num_row(),
				       0);
#endif
  mret.sub(1,m1);
  mret.sub(m1.num_row()+1,m2);
  return mret;
}

HepDiagMatrix HepDiagMatrix::operator- () const 
#ifdef HEP_GNU_OPTIMIZED_RETURN
      return m2(nrow);
{
#else
{
   HepDiagMatrix m2(nrow);
#endif
   register double *a=m;
   register double *b=m2.m;
   register double *e=m+num_size();
   for(;a<e; a++, b++) (*b) = -(*a);
   return m2;
}

   

HepMatrix operator+(const HepMatrix &m1,const HepDiagMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepMatrix mret(m1);
#endif
  CHK_DIM_2(m1.num_row(),m2.num_row(),
			 m1.num_col(),m2.num_col(),+);
  mret += m2;
  return mret;
}

HepMatrix operator+(const HepDiagMatrix &m1,const HepMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m2);
{
#else
{
  HepMatrix mret(m2);
#endif
  CHK_DIM_2(m1.num_row(),m2.num_row(),
			 m1.num_col(),m2.num_col(),+);
  mret += m1;
  return mret;
}

HepDiagMatrix operator+(const HepDiagMatrix &m1,const HepDiagMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.nrow);
{
#else
{
  HepDiagMatrix mret(m1.nrow);
#endif
  CHK_DIM_1(m1.nrow,m2.nrow,+);
  SIMPLE_TOP(+)
  return mret;
}

HepSymMatrix operator+(const HepDiagMatrix &m1,const HepSymMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m2);
{
#else
{
  HepSymMatrix mret(m2);
#endif
  CHK_DIM_1(m1.num_row(),m2.num_row(),+);
  mret += m1;
  return mret;
}

HepSymMatrix operator+(const HepSymMatrix &m2,const HepDiagMatrix &m1)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m2);
{
#else
{
  HepSymMatrix mret(m2);
#endif
  CHK_DIM_1(m1.num_row(),m2.num_row(),+);
  mret += m1;
  return mret;
}

//
// operator -
//

HepMatrix operator-(const HepMatrix &m1,const HepDiagMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepMatrix mret(m1);
#endif
  CHK_DIM_2(m1.num_row(),m2.num_row(),
			 m1.num_col(),m2.num_col(),-);
  mret -= m2;
  return mret;
}
HepMatrix operator-(const HepDiagMatrix &m1,const HepMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepMatrix mret(m1);
#endif
  CHK_DIM_2(m1.num_row(),m2.num_row(),
			 m1.num_col(),m2.num_col(),-);
  mret -= m2;
  return mret;
}

HepDiagMatrix operator-(const HepDiagMatrix &m1,const HepDiagMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.nrow);
{
#else
{
  HepDiagMatrix mret(m1.nrow);
#endif
  CHK_DIM_1(m1.num_row(),m2.num_row(),-);
  SIMPLE_TOP(-)
  return mret;
}
HepSymMatrix operator-(const HepDiagMatrix &m1,const HepSymMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepSymMatrix mret(m1);
#endif
  CHK_DIM_1(m1.num_row(),m2.num_row(),-);
  mret -= m2;
  return mret;
}

HepSymMatrix operator-(const HepSymMatrix &m1,const HepDiagMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepSymMatrix mret(m1);
#endif
  CHK_DIM_1(m1.num_row(),m2.num_row(),-);
  mret -= m2;
  return mret;
}

/* -----------------------------------------------------------------------
   This section contains support routines for matrix.h. This file contains
   The two argument functions *,/. They call copy constructor and then /=,*=.
   Also contains v_times_vT(const HepVector &v).
   ----------------------------------------------------------------------- */

HepDiagMatrix operator/(
const HepDiagMatrix &m1,double t)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepDiagMatrix mret(m1);
#endif
  mret /= t;
  return mret;
}

HepDiagMatrix operator*(const HepDiagMatrix &m1,double t)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepDiagMatrix mret(m1);
#endif
  mret *= t;
  return mret;
}

HepDiagMatrix operator*(double t,const HepDiagMatrix &m1)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1);
{
#else
{
  HepDiagMatrix mret(m1);
#endif
  mret *= t;
  return mret;
}

HepMatrix operator*(const HepMatrix &m1,const HepDiagMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.num_row(),m2.num_col());
{
#else
  {
    HepMatrix mret(m1.num_row(),m2.num_col());
#endif
    CHK_DIM_1(m1.num_col(),m2.num_row(),*);
    double *mit1=m1.m;
    double *mir=mret.m;
    for(int irow=1;irow<=m1.num_row();irow++) {
      double *mcc = m2.m;
      for(int icol=1;icol<=m1.num_col();icol++) {
	*(mir++) = *(mit1++) * (*(mcc++));
      }
    }
    return mret;
  }

HepMatrix operator*(const HepDiagMatrix &m1,const HepMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.num_row(),m2.num_col());
{
#else
{
  HepMatrix mret(m1.num_row(),m2.num_col());
#endif
  CHK_DIM_1(m1.num_col(),m2.num_row(),*);
  double *mit1=m2.m;
  double *mir=mret.m;
  double *mrr = m1.m;
  for(int irow=1;irow<=m2.num_row();irow++) {
    for(int icol=1;icol<=m2.num_col();icol++) {
      *(mir++) = *(mit1++) * (*mrr);
    }
    mrr++;
  }
  return mret;
}

HepDiagMatrix operator*(const HepDiagMatrix &m1,const HepDiagMatrix &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.num_row());
{
#else
{
  HepDiagMatrix mret(m1.num_row());
#endif
  CHK_DIM_1(m1.num_col(),m2.num_row(),*);
  double *a = mret.m;
  double *b = m1.m;
  double *c = m2.m;
  double *e = mret.m + m1.num_col();
  for(;a<e;) *(a++) = *(b++) * (*(c++));
  return mret;
}

HepVector operator*(const HepDiagMatrix &m1,const HepVector &m2)
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.num_row());
{
#else
{
  HepVector mret(m1.num_row());
#endif
  CHK_DIM_1(m1.num_col(),m2.num_row(),*);
  double *mir=mret.m, *mi1 = m1.m, *mi2 = m2.m;
  for(int icol=1;icol<=m1.num_col();icol++) {
    *(mir++) = *(mi1++) * *(mi2++);
  }
  return mret;
}

/* -----------------------------------------------------------------------
   This section contains the assignment and inplace operators =,+=,-=,*=,/=.
   ----------------------------------------------------------------------- */

HepMatrix & HepMatrix::operator+=(const HepDiagMatrix &m2)
{
  CHK_DIM_2(num_row(),m2.num_row(),num_col(),m2.num_col(),+=);
  int n = num_row();
  double *mrr = m;
  double *mr = m2.m;
  for(int r=1;r<=n;r++) {
    *mrr += *(mr++);
    mrr += (n+1);
  }
  return (*this);
}

HepSymMatrix & HepSymMatrix::operator+=(const HepDiagMatrix &m2)
{
  CHK_DIM_2(num_row(),m2.num_row(),num_col(),m2.num_col(),+=);
  register double *a=m;
  register double *b=m2.m;
  for(int i=1;i<=num_row();i++) {
    *a += *(b++);
    a += (i+1);
  }
  return (*this);
}

HepDiagMatrix & HepDiagMatrix::operator+=(const HepDiagMatrix &m2)
{
  CHK_DIM_2(num_row(),m2.num_row(),num_col(),m2.num_col(),+=);
  SIMPLE_BOP(+=)
  return (*this);
}

HepMatrix & HepMatrix::operator-=(const HepDiagMatrix &m2)
{
  CHK_DIM_2(num_row(),m2.num_row(),num_col(),m2.num_col(),-=);
  int n = num_row();
  double *mrr = m;
  double *mr = m2.m;
  for(int r=1;r<=n;r++) {
    *mrr -= *(mr++);
    mrr += (n+1);
  }
  return (*this);
}

HepSymMatrix & HepSymMatrix::operator-=(const HepDiagMatrix &m2)
{
  CHK_DIM_2(num_row(),m2.num_row(),num_col(),m2.num_col(),+=);
  register double *a=m;
  register double *b=m2.m;
  for(int i=1;i<=num_row();i++) {
    *a -= *(b++);
    a += (i+1);
  }
  return (*this);
}

HepDiagMatrix & HepDiagMatrix::operator-=(const HepDiagMatrix &m2)
{
  CHK_DIM_2(num_row(),m2.num_row(),num_col(),m2.num_col(),-=);
  SIMPLE_BOP(-=)
  return (*this);
}

HepDiagMatrix & HepDiagMatrix::operator/=(double t)
{
  SIMPLE_UOP(/=)
  return (*this);
}

HepDiagMatrix & HepDiagMatrix::operator*=(double t)
{
  SIMPLE_UOP(*=)
  return (*this);
}

HepMatrix & HepMatrix::operator=(const HepDiagMatrix &m1)
{
   if(m1.nrow*m1.nrow != size)
   {
      delete_m(size,m);
      size = m1.nrow * m1.nrow;
      m = new_m(size);
   }
   nrow = m1.nrow;
   ncol = m1.nrow;
   int n = nrow;
   memset(m, 0, size * sizeof(double));
   double *mrr = m;
   double *mr = m1.m;
   for(int r=1;r<=n;r++) {
      *mrr = *(mr++);
      mrr += (n+1);
   }
   return (*this);
}

HepDiagMatrix & HepDiagMatrix::operator=(const HepDiagMatrix &m1)
{
   if(m1.nrow != nrow)
   {
      delete_m(nrow,m);
      nrow = m1.nrow;
      m = new_m(nrow);
   }
   memcpy(m,m1.m,nrow*sizeof(double));
   return (*this);
}

// Print the Matrix.

std::ostream& operator<<(std::ostream &s, const HepDiagMatrix &q)
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

HepDiagMatrix HepDiagMatrix::
apply(double (*f)(double, int, int)) const
#ifdef HEP_GNU_OPTIMIZED_RETURN
return mret(num_row());
{
#else
{
  HepDiagMatrix mret(num_row());
#endif
  double *a = m;
  double *b = mret.m;
  for(int ir=1;ir<=num_row();ir++) {
    *(b++) = (*f)(*(a++), ir, ir);
  }
  return mret;
}

void HepDiagMatrix::assign (const HepMatrix &m1)
{
   if(m1.num_row()!=nrow)
   {
      delete_m(nrow, m);
      nrow = m1.num_row();
      m = new_m(nrow);
   }
   double *a = m1.m;
   double *b = m;
   for(int r=1;r<=nrow;r++) {
      *(b++) = *a;
      a += (nrow+1);
   }
}

void HepDiagMatrix::assign(const HepSymMatrix &m1)
{
   if(m1.num_row()!=nrow)
   {
      delete_m(nrow, m);
      nrow = m1.num_row();
      m = new_m(nrow);
   }
   double *a = m1.m;
   double *b = m;
   for(int r=1;r<=nrow;r++) {
      *(b++) = *a;
      a += (r+1);
   }
}

HepSymMatrix HepDiagMatrix::similarity(const HepMatrix &m1) const
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.num_row());
{
#else
{
  HepSymMatrix mret(m1.num_row());
#endif
  CHK_DIM_1(num_row(),m1.num_col(),"similarity");
//  HepMatrix temp = m1*(*this);
// If m1*(*this) has correct dimensions, then so will the m1.T multiplication.
// So there is no need to check dimensions again.
  double *mrc = mret.m;
  for(int r=1;r<=mret.num_row();r++) {
    double *mrr = m1.m+(r-1)*m1.num_col();
    double *mc = m1.m;
    for(int c=1;c<=r;c++) {
      double *mi = m;
      register double tmp = 0;
      double *mr = mrr;
      for(int i=0;i<m1.num_col();i++)
	tmp+=*(mr++) * *(mc++) * *(mi++);
      *(mrc++) = tmp;
    }
  }
  return mret;
}

double HepDiagMatrix::similarity(const HepVector &m1) const
{
  register double mret;
  CHK_DIM_1(num_row(),m1.num_row(),similarity);
  double *mi = m;
  double *mv = m1.m;
  mret = *(mv)* *(mv)* *(mi++);
  mv++;
  for(int i=2;i<=m1.num_row();i++) {
    mret+=*(mv)* *(mv)* *(mi++);
    mv++;
  }
  return mret;
}

HepSymMatrix HepDiagMatrix::similarityT(const HepMatrix &m1) const
#ifdef HEP_GNU_OPTIMIZED_RETURN
     return mret(m1.num_col());
{
#else
{
  HepSymMatrix mret(m1.num_col());
#endif
  CHK_DIM_1(num_col(),m1.num_row(),similarityT);
//  Matrix temp = (*this)*m1;
// If m1*(*this) has correct dimensions, then so will the m1.T multiplication.
// So there is no need to check dimensions again.
  for(int r=1;r<=mret.num_row();r++)
    for(int c=1;c<=r;c++)
      {
	double *mi = m;
	register double tmp = m1(1,r)*m1(1,c)* *(mi++);
	for(int i=2;i<=m1.num_row();i++)
	  tmp+=m1(i,r)*m1(i,c)* *(mi++);
	mret.fast(r,c) = tmp;
      }
  return mret;
}

void HepDiagMatrix::invert(int &ierr) {
  int n = num_row();
  ierr = 1;
  double *mm = m;
  int i;
  for(i=0;i<n;i++) {
    if(*(mm++)==0) return;
  }
  ierr = 0;
  mm = m;
  for(i=0;i<n;i++) {
    *mm = 1.0 / *mm;
    mm++;
  }  
}

double HepDiagMatrix::determinant() const {
   double d = 1.0;
   double *end = m + nrow;
   for (double *p=m; p < end; p++)
      d *= *p;
   return d;
}

double HepDiagMatrix::trace() const {
   double d = 0.0;
   double *end = m + nrow;
   for (double *p=m; p < end; p++)
      d += *p;
   return d;
}

}  // namespace CLHEP
