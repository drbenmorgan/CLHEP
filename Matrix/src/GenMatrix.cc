// -*- C++ -*-
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is the implementation of the HepGenMatrix class.
//

#ifdef GNUPRAGMA
#pragma implementation
#endif

#include <string.h>
#include <cmath>
#include <stdlib.h>

#include "CLHEP/Matrix/defs.h"
#include "CLHEP/Matrix/GenMatrix.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/Matrix.h"

#ifdef HEP_DEBUG_INLINE
#include "CLHEP/Matrix/GenMatrix.icc"
#endif

namespace CLHEP {

#ifdef HEP_THIS_FUNCTION_IS_NOT_NEEDED
static void delete_array(double *m)
{
   delete [] m;
}
#endif

double norm_infinity(const HepGenMatrix &m) {
  double max=0,sum;
  for(int r=1;r<=m.num_row();r++) {
    sum=0;
    for(int c=1;c<=m.num_col();c++) {
      sum+=fabs(m(r,c));
    }
    if(sum>max) max=sum;
  }
  return max;
}

double norm1(const HepGenMatrix &m) {
  double max=0,sum;
  for(int c=1;c<=m.num_col();c++) {
    sum=0;
    for(int r=1;r<=m.num_row();r++)
      sum+=fabs(m(r,c));
    if(sum>max) max=sum;
  }
  return max;
}

double norm(const HepGenMatrix &m) {
  HepSymMatrix A(m.num_col(),0);
	
// Calculate m.T*m
  int r;	
  for(r=1;r<=A.num_row();r++)
    for(int c=1;c<=r;c++)
      for(int i=1;i<=m.num_row();i++)
	A.fast(r,c)=m(i,r)*m(i,c);
  diagonalize(&A);
  double max=fabs(A(1,1));
  for(r=2;r<=A.num_row();r++)
    if(max<fabs(A(r,r))) max=fabs(A(r,r));
  return (sqrt(max));
}

void HepGenMatrix::error(const char *s)
{
  std::cerr << s << std::endl;
  std::cerr << "---Exiting to System." << std::endl;
  abort();
}

bool HepGenMatrix::operator== ( const HepGenMatrix& o) const {
  if(o.num_row()!=num_row() || o.num_col()!=num_col()) return false;
  for (int k1=1; k1<=num_row(); k1++)
    for (int k2=1; k2<=num_col(); k2++)
      if(o(k1,k2) != (*this)(k1,k2)) return false;
  return true;
}

// implementation using pre-allocated data array
// -----------------------------------------------------------------

void HepGenMatrix::delete_m(int size, double* m)
{
   if (m)
   {
     if(size > size_max)
       delete [] m;
   }
}

double* HepGenMatrix::new_m(int )
{
  /*-ap: data_array is replaced by the std::vector<double>,
   *     so we simply return 0 here
   * 
   *   if (size == 0) return 0;
   *   else {
   *     if ( size <= size_max ) {
   *       memset(data_array, 0, size * sizeof(double));
   *       return data_array;
   *     } else {
   *       double * nnn = new double[size];
   *       memset(nnn, 0, size * sizeof(double));
   *       return nnn;
   *     }
   *   }
   *-ap end 
   */
  return 0;
}

}  // namespace CLHEP

