// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//

#ifdef GNUPRAGMA
#pragma implementation
#endif

#include <string.h>
#include <cmath>

#include "CLHEP/Matrix/defs.h"
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
  HepMatrix::mIter a=m.begin();            \
  HepMatrix::mIter e=m.begin()+num_size(); \
  for(;a<e; a++) (*a) OPER t;

#define SIMPLE_BOP(OPER)          \
   HepMatrix::mIter a=m.begin();            \
   HepMatrix::mcIter b=m2.m.begin();         \
   HepMatrix::mIter e=m.begin()+num_size(); \
   for(;a<e; a++, b++) (*a) OPER (*b);

#define SIMPLE_TOP(OPER)          \
   HepMatrix::mcIter a=m1.m.begin();            \
   HepMatrix::mcIter b=m2.m.begin();         \
   HepMatrix::mIter t=mret.m.begin();         \
   HepMatrix::mcIter e=m1.m.begin()+m1.nrow; \
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
   : m(p), nrow(p)
{
}

HepDiagMatrix::HepDiagMatrix(int p, int init)
   : m(p), nrow(p)
{   
   switch(init)
   {
   case 0:
      m.assign(nrow,0);
      break;

   case 1:
      {
	 HepMatrix::mIter a=m.begin();
	 HepMatrix::mIter b=m.begin() + p;
	 for( ; a<b; a++) *a = 1.0;
	 break;
      }
   default:
      error("DiagMatrix: initialization must be either 0 or 1.");
   }
}

HepDiagMatrix::HepDiagMatrix(int p, HepRandom &r)
  : m(p), nrow(p)
{
   HepMatrix::mIter a = m.begin();
   HepMatrix::mIter b = m.begin() + num_size();
   for(;a<b;a++) *a = r();
}
//
// Destructor
//
HepDiagMatrix::~HepDiagMatrix() {
}

HepDiagMatrix::HepDiagMatrix(const HepDiagMatrix &m1)
   : HepGenMatrix(m1), m(m1.nrow), nrow(m1.nrow)
{
   m = m1.m;
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
  HepMatrix::mIter a = mret.m.begin();
  HepMatrix::mcIter b = m.begin() + min_row - 1;
  HepMatrix::mIter e = mret.m.begin() + mret.num_row();
  for(;a<e;) *(a++) = *(b++);
  return mret;
}

HepDiagMatrix HepDiagMatrix::sub(int min_row, int max_row)
{
  HepDiagMatrix mret(max_row-min_row+1);
  if(max_row > num_row())
    error("HepDiagMatrix::sub: Index out of range");
  HepMatrix::mIter a = mret.m.begin();
  HepMatrix::mIter b = m.begin() + min_row - 1;
  HepMatrix::mIter e = mret.m.begin() + mret.num_row();
  for(;a<e;) *(a++) = *(b++);
  return mret;
}

void HepDiagMatrix::sub(int row,const HepDiagMatrix &m1)
{
  if(row <1 || row+m1.num_row()-1 > num_row() )
    error("HepDiagMatrix::sub: Index out of range");
  HepMatrix::mcIter a = m1.m.begin();
  HepMatrix::mIter b = m.begin() + row - 1;
  HepMatrix::mcIter e = m1.m.begin() + m1.num_row();
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
   HepMatrix::mcIter a=m.begin();
   HepMatrix::mIter b=m2.m.begin();
   HepMatrix::mcIter e=m.begin()+num_size();
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
    HepMatrix::mcIter mit1=m1.m.begin();
    HepMatrix::mIter mir=mret.m.begin();
    for(int irow=1;irow<=m1.num_row();irow++) {
      HepMatrix::mcIter mcc = m2.m.begin();
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
  HepMatrix::mcIter mit1=m2.m.begin();
  HepMatrix::mIter mir=mret.m.begin();
  HepMatrix::mcIter mrr = m1.m.begin();
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
  HepMatrix::mIter a = mret.m.begin();
  HepMatrix::mcIter b = m1.m.begin();
  HepMatrix::mcIter c = m2.m.begin();
  HepMatrix::mIter e = mret.m.begin() + m1.num_col();
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
  HepGenMatrix::mIter mir=mret.m.begin();
  HepGenMatrix::mcIter mi1 = m1.m.begin(), mi2 = m2.m.begin();
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
  mIter mrr = m.begin();
  HepMatrix::mcIter mr = m2.m.begin();
  for(int r=1;r<=n;r++) {
    *mrr += *(mr++);
    if(r<n) mrr += (n+1);
  }
  return (*this);
}

HepSymMatrix & HepSymMatrix::operator+=(const HepDiagMatrix &m2)
{
  CHK_DIM_2(num_row(),m2.num_row(),num_col(),m2.num_col(),+=);
  HepMatrix::mIter a=m.begin();
  HepMatrix::mcIter b=m2.m.begin();
  for(int i=1;i<=num_row();i++) {
    *a += *(b++);
    if(i<num_row()) a += (i+1);
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
  mIter mrr = m.begin();
  HepMatrix::mcIter mr = m2.m.begin();
  for(int r=1;r<=n;r++) {
    *mrr -= *(mr++);
    if(r<n) mrr += (n+1);
  }
  return (*this);
}

HepSymMatrix & HepSymMatrix::operator-=(const HepDiagMatrix &m2)
{
  CHK_DIM_2(num_row(),m2.num_row(),num_col(),m2.num_col(),+=);
  HepMatrix::mIter a=m.begin();
  HepMatrix::mcIter b=m2.m.begin();
  for(int i=1;i<=num_row();i++) {
    *a -= *(b++);
    if(i<num_row()) a += (i+1);
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
   if(m1.nrow*m1.nrow != size_)
   {
      size_ = m1.nrow * m1.nrow;
      m.resize(size_);
   }
   nrow = m1.nrow;
   ncol = m1.nrow;
   int n = nrow;
   m.assign(size_,0); 
   mIter mrr = m.begin();
   HepMatrix::mcIter mr = m1.m.begin();
   for(int r=1;r<=n;r++) {
      *mrr = *(mr++);
      if(r<n) mrr += (n+1);
   }
   return (*this);
}

HepDiagMatrix & HepDiagMatrix::operator=(const HepDiagMatrix &m1)
{
   if(m1.nrow != nrow)
   {
      nrow = m1.nrow;
      m.resize(nrow);
   }
   m=m1.m;
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
  HepMatrix::mcIter a = m.begin();
  HepMatrix::mIter b = mret.m.begin();
  for(int ir=1;ir<=num_row();ir++) {
    *(b++) = (*f)(*(a++), ir, ir);
  }
  return mret;
}

void HepDiagMatrix::assign (const HepMatrix &m1)
{
   if(m1.num_row()!=nrow)
   {
      nrow = m1.num_row();
      m.resize(nrow);
   }
   HepMatrix::mcIter a = m1.m.begin();
   HepMatrix::mIter b = m.begin();
   for(int r=1;r<=nrow;r++) {
      *(b++) = *a;
      if(r<nrow) a += (nrow+1);
   }
}

void HepDiagMatrix::assign(const HepSymMatrix &m1)
{
   if(m1.num_row()!=nrow)
   {
      nrow = m1.num_row();
      m.resize(nrow);
   }
   HepMatrix::mcIter a = m1.m.begin();
   HepMatrix::mIter b = m.begin();
   for(int r=1;r<=nrow;r++) {
      *(b++) = *a;
      if(r<nrow) a += (r+1);
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
  HepMatrix::mIter mrc = mret.m.begin();
  for(int r=1;r<=mret.num_row();r++) {
    HepMatrix::mcIter mrr = m1.m.begin()+(r-1)*m1.num_col();
    HepMatrix::mcIter mc = m1.m.begin();
    for(int c=1;c<=r;c++) {
      HepMatrix::mcIter mi = m.begin();
      register double tmp = 0;
      HepMatrix::mcIter mr = mrr;
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
  HepMatrix::mcIter mi = m.begin();
  HepMatrix::mcIter mv = m1.m.begin();
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
	HepMatrix::mcIter mi = m.begin();
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
  HepMatrix::mIter mm = m.begin();
  int i;
  for(i=0;i<n;i++) {
    if(*(mm++)==0) return;
  }
  ierr = 0;
  mm = m.begin();
  for(i=0;i<n;i++) {
    *mm = 1.0 / *mm;
    mm++;
  }  
}

double HepDiagMatrix::determinant() const {
   double d = 1.0;
   HepMatrix::mcIter end = m.begin() + nrow;
   for (HepMatrix::mcIter p=m.begin(); p < end; p++)
      d *= *p;
   return d;
}

double HepDiagMatrix::trace() const {
   double d = 0.0;
   HepMatrix::mcIter end = m.begin() + nrow;
   for (HepMatrix::mcIter p=m.begin(); p < end; p++)
      d += *p;
   return d;
}

}  // namespace CLHEP
