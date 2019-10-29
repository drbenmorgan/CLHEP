// -*- C++ -*-
// $Id: testMatrix.cc,v 1.3 2003/08/13 20:00:12 garren Exp $
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a small program for testing the classes from the HEP Matrix module.
//

#include "CLHEP/Matrix/defs.h"
#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/DiagMatrix.h"
#include "CLHEP/Matrix/Vector.h"
#include "CLHEP/Random/Random.h"
#include "CLHEP/Random/JamesRandom.h"
#include "CLHEP/Random/RandFlat.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

using namespace CLHEP;

#define PRINTOUT

int matrix_test1(const HepGenMatrix&m) {
  //
  // test of virtual finctions.
  //
  static int dum = 0;
  dum += m.num_col();
  return 0;
}

//
// test function
//
double neg(double f, int, int) {
  return -f;
}

double absf(double f, int, int) {
  return fabs(f);
}

double negv(double f, int) {
  return -f;
}

void matrix_test2(const HepSymMatrix&m, HepSymMatrix &n) {
  n = m.sub(2,5);
}


void matrix_test() {
  //
  // complete test of all functions in Matrix.cc
  //
  cout << "Starting Matrix tests" << endl;
  {
    // Test of HepMatrix()
    HepMatrix a;
  }

  {
    // Test of HepMatrix(p,q)
    HepMatrix a(3,5);
    HepMatrix b(4,5,0);
    cout << "4x5 matrix initialized to zero " << b;
    HepMatrix c(3,3,1);
    cout << "3x3 matrix initialized to identity " << c;
  }

  {
    // Test of HepMatrix(p,q,Random)
    HepRandom r;
    r.setTheSeed(31);
    HepMatrix a(3,3,r);
    cout << "3x3 matrix initialized with Random " << a;
    // Test of HepMatrix(const HepMatrix&);
    HepMatrix b(a);
    cout << "matrix initialized to the previous matrix " << b;
  }

  {
    // Test of sub matrix
    HepRandom r;
    r.setTheSeed(31);
    HepMatrix a(8,5,r);
    HepMatrix b = a.sub(2,6,3,5);
    cout << "8x5 matrix" << a;
    cout << "sub matrix (2-6 x 3-5 of the previous matrix." << b;
    HepMatrix c(2,3,0);
    a.sub(4,3,c);
    cout << "embedding sub matrix at 4,3" << a;
    // Test of dsum
    HepMatrix d(3,2,r);
    cout << "dsum" << dsum(a,d);
  }

  {
    // m += m1;
    HepRandom r;
    r.setTheSeed(31);
    HepMatrix a(5,5,r);
    HepMatrix b(5,5,r);
    cout << "a" << a;
    cout << "b" << b;
    cout << "a += b" << (a+=b);
    HepMatrix c;
    c = a + b;
    cout << "a + b" << c;
  }

  {
    // test of T();
    HepRandom r;
    r.setTheSeed(31);
    HepMatrix a(5,3,r);
    HepMatrix b = a.T();
    cout << "a" << a;
    cout << "a.T" << b;
  }

  cout << "End of Matrix tests" << endl;
  
}

void symmatrix_test() {
  {
    // Test of HepSymMatrix()
    HepSymMatrix a;
  }

  {
    // Test of HepSymMatrix(p)
    HepSymMatrix a(3);
    HepSymMatrix b(4,0);
    cout << "4x4 Symmetric matrix initialuzed to zero " << b;
    HepSymMatrix c(3,1);
    cout << "3x3 Symmetric matrix initialized to identity "<< c;
  }

  {
    // Test of HepSymMatrix(p,Random)
    HepRandom r;
    r.setTheSeed(31);
    HepSymMatrix a(3,r);
    cout << "3x3 symmetric matrix initialized with Random " << a << endl;
    // Test of HepSymMatrix(const HepSymMatrix&);
    HepSymMatrix b(a);
    cout << "symmetric matrix initialized to the previous matrix " << b;
    HepMatrix c(b);
    cout << "matrix initialized to the previous symmetric matrix "
	 << c;
    //
    // Access to elements
    //
    double f = 3.8;
    double g = 22.5;
    cout << c(1,1) << " " << c[0][0] << endl;
    c(1,2) = f;
    c[2][1] = g;
    c(2,3) = f;
    c[1][2] = g;
    cout << c << endl;
    HepMatrix &d = c;
    cout << d(1,1) << " " << d[0][0] << endl;
    
  }

  {
    // Test of sub symmatrix
    HepRandom r;
    r.setTheSeed(31);
    HepSymMatrix a(5,r);
    HepSymMatrix b = a.sub(2,5);
    cout << "5x5 sym matrix" << a;
    cout << "sub sym matrix (2-5 x 2-5 of the previous sub matrix." << b;
    HepSymMatrix c(3,0);
    a.sub(2,c);
    cout << "embedding sub matrix at 2" << a;
  }
  {
    // m = m1 + s;
    HepRandom r;
    r.setTheSeed(31);
    HepMatrix a(5,5,r);
    HepSymMatrix b(5,r);
    cout << "a" << a;
    cout << "b(sym)" << b;
    cout << "a += b" << (a+=b);
    HepMatrix c = a + b;
    cout << "a + b" << c;
  }
  {
    // test of similarity(Matrix)
    HepRandom r;
    r.setTheSeed(31);
    HepMatrix a(5,3,r);
    HepSymMatrix b(3,r);
    HepSymMatrix c = b.similarity(a);
    cout << "a" << a;
    cout << "b" << b;
    cout << "c" << c;
  }
  {
    // test of similarityT(Matrix)
    HepRandom r;
    r.setTheSeed(31);
    HepMatrix a(3,5,r);
    HepSymMatrix b(3,r);
    HepSymMatrix c = b.similarityT(a);
    cout << "a" << a;
    cout << "b" << b;
    cout << "c" << c;
  }
  {
    // test of similarity(SymMatrix)
    HepRandom r;
    r.setTheSeed(31);
    HepSymMatrix a(3,r);
    HepSymMatrix b(3,r);
    HepSymMatrix c = b.similarity(a);
    cout << "a" << a;
    cout << "b" << b;
    cout << "c" << c;
  }
  {
    // test of similarity(Vector)
    HepRandom r;
    r.setTheSeed(31);
    HepVector a(3,r);
    HepSymMatrix b(3,r);
    double c = b.similarity(a);
    HepSymMatrix cc = b.similarity(HepMatrix(a.T()));
    cout << "a" << a;
    cout << "b" << b;
    cout << "c\t" << c << endl;
    cout << "c" << cc;
  }
  cout << "End of SymMatrix tests" << endl;
  
}

void diagmatrix_test() { 
  {
    // Test of HepDiagMatrix()
    HepDiagMatrix a;
  }

  {
    // Test of HepDiagMatrix(p)
    HepDiagMatrix a(3);
    HepDiagMatrix b(4,0);
    cout << "4x4 diagonal matrix initialized to zero " << b;
    HepDiagMatrix c(3,1);
    cout << "3x3 diagonal matrix initialized to identity " << c;
  }

  {
    // Test of HepDiagMatrix(p,Random)
    HepRandom r;
    r.setTheSeed(31);
    HepDiagMatrix a(3,r);
    cout << "3x3 diagonal matrix initialized to Random " << a;
    // Test of HepDiagMatrix(const HepDiagMatrix&);
    HepDiagMatrix b(a);
    cout << "diagonal matrix initialized to the previous matrix " << b;
    HepMatrix c(b);
    cout << "matrix initialized to the previous diagonal matrix "
	 << c;
    HepSymMatrix d(b);
    cout << "Symmetric matrix initialized to the previous diagonal matrix "
	 << d;
  }

  {
    // Test of sub diagmatrix
    HepRandom r;
    r.setTheSeed(31);
    HepDiagMatrix a(8,r);
    HepDiagMatrix b = a.sub(2,5);
    cout << "8x8 diag matrix" << a;
    cout << "sub diag matrix (2-5 x 2-5 of the previous diag matrix." << b;
    HepDiagMatrix c(3,0);
    a.sub(2,c);
    cout << "embedding sub matrix at 2" << a;
  }
  {
    // m = m1 + s;
    HepRandom r;
    r.setTheSeed(31);
    HepMatrix a(5,5,r);
    HepDiagMatrix b(5,r);
    cout << "a" << a;
    cout << "b(diag)" << b;
    cout << "a += b" << (a+=b);
    HepMatrix c = a + b;
    cout << "a + b" << c;
  }

  cout << "End of DiagMatrix tests" << endl;
}

void vector_test() {
  {
    // Test of HepVector()
    HepVector a;
  }

  {
    // Test of HepVector(p)
    HepVector a(3);
    HepVector b(4,0);
    cout << "4 vector initialized to zero "<< b;
    HepVector c(3,1);
    cout << "3 vector initialized to identity " << c;
  }

  {
    // Test of HepVector(p,Random)
    HepRandom r;
    r.setTheSeed(31);
    HepVector a(3,r);
    cout << "3 vector initialized to Random " << a;
    // Test of HepVector(const HepVector&);
    HepVector b(a);
    cout << "Vector initialized to the previous vector " << b;
    HepMatrix c(b);
    cout << "matrix initialized to the previous vector "
	 << c;
    HepVector d(c);
    cout << "Vector initialized to the previous matrix "
	 << d;    
  }

  {
    // Test of sub diagmatrix
    HepRandom r;
    r.setTheSeed(31);
    HepVector a(8,r);
    HepVector b = a.sub(2,5);
    cout << "8 vector" << a;
    cout << "sub vector (2-5 of the previous vector." << b;
    HepVector c(3,0);
    a.sub(2,c);
    cout << "embedding sub vector at 2 " << a;
  }
  {
    // m = m1 + s;
    HepRandom r;
    r.setTheSeed(31);
    HepMatrix a(5,1,r);
    HepVector b(5,r);
    cout << "a" << a;
    cout << "b(vector)" << b;
    cout << "a += b" << (a+=b);
    HepMatrix c = a + b;
    cout << "a + b" << c;
  }

  cout << "End of Vector tests" << endl;
}

int main() {
//
// Test of HepMatrix
//
  cout << std::setiosflags(std::ios::fixed) << std::setw(10);
  matrix_test();
  symmatrix_test();
  diagmatrix_test();
  vector_test();
  
  //
  // Test of default constructor
  //
  HepMatrix m;
  //
  // Test of constructors.
  //
  HepMatrix d(3,3,1);
  HepMatrix e(3,3,0);
  HepMatrix f(5,3);
  HepMatrix g(f);
  matrix_test1(g);
  //
  // Test of constructor with a Random object.
  //
  HepRandom r;
  r.setTheSeed(31);
  HepMatrix a(3,3,r);
#if defined(PRINTOUT)
 cout << a << endl;
#endif
  HepMatrix b(3,5,r);
  matrix_test1(b);
#if defined(PRINTOUT)
 cout << b << endl;
#endif

  HepSymMatrix dds(3,r);
  HepMatrix ddm(dds);
  HepDiagMatrix ddd(3,r);
  HepMatrix ddmd(ddd);
  HepVector ddv(3,r);
  HepMatrix ddmv(ddv);
#if defined(PRINTOUT)
 cout << "nraw=" << b.num_row() << " ncol=" << b.num_col() << endl;
#endif
#if defined(PRINTOUT)
 cout << "b(1,1)=" << b(1,1) << " b(2,1)=" << b(2,1) << endl;
#endif
  b(2,3) = 1.0;

  b /= 3.0;
  b *= 6.0;

  HepSymMatrix sm(3,r);
  HepDiagMatrix dm(3,r);
  HepVector vvm(3,r);

  d += e;  
  d += sm;
  d += dm;
  ddmv += vvm;

  a -= e;
  a -= sm;
  a -= dm;
  ddmv -= vvm;

  d = sm;
  d = dm;
  d = a;
  ddmv = vvm;

  e = d.apply(neg);

  a = d.T();
  
  e = b.sub(1,2,3,2);
  
  b.sub(1,3,e);

  swap(a,d);
  
  m = d * a;
  m = d * sm;
  m = d * dm;
  m = sm * d;
#if defined(PRINTOUT)
 cout << "Dm=" << dm << " d = " << d << endl;
#endif
  m = dm * d;
  m = sm * sm;
  m = dm * dm;

  //
  // SymMatrix
  //
  HepSymMatrix s;
  HepSymMatrix ss(6);
  HepSymMatrix si(6,1);
  HepSymMatrix sz(6,0);
  HepSymMatrix sr(6,r);
  HepSymMatrix sc(sr);
  HepSymMatrix scd(dm);

  matrix_test1(si);
#if defined(PRINTOUT)
 cout << "nraw=" << sr.num_row() << " ncol=" << sr.num_col() << endl;
#endif
#if defined(PRINTOUT)
 cout << "sr(1,1)=" << sr(1,1) << " sr(2,1)=" << sr(2,1) << endl;
#endif

  sr(4,3) = r();
  sr.fast(3,1) = r();
  
  s.assign(d);
#if defined(PRINTOUT)
 cout << "d=" << d << "s=" << s << endl;  
#endif
  ss.assign(sc);

  ss *= 0.5;
  ss /= 0.2;

  HepDiagMatrix ddds(ss.num_row(),r);
  ss += si;
  ss += ddds;
  ss -= sr;
  ss -= ddds;
  ss = ddds;

  s = sr;
  s = ss.T();
  s.apply(neg);
  HepMatrix mm(6,4,r);
  ss = s.similarityT(mm);
  
  HepMatrix mt(8,6,r);
  ss = s.similarity(mt);

  s.assign(d);
  
  s = sr.sub(2,5);

  ss.sub(2,s);
  s = ss.sub(2,7);

  m = s * sr;
  m = s * m;
  m = m * s;
  
  HepVector v(6,r);
  s = vT_times_v(v);
  
  //
  // Test of HepDiagMatrix
  //

  HepDiagMatrix dt;
  HepDiagMatrix dn(6);
  HepDiagMatrix di(6,1);
  HepDiagMatrix dz(6,0);
  HepDiagMatrix dr(6,r);
  HepDiagMatrix dc(dr);

  matrix_test1(dr);
#if defined(PRINTOUT)
 cout << "Nr=" << di.num_row() << " Nc=" << dz.num_col() << endl;
#endif
#if defined(PRINTOUT)
 cout << "dr(1,1)=" << dr(1,1) << endl;
#endif

  dr(4,4) = r();
  dr.fast(2,2) = r();

  dt.assign(m);
  dt.assign(s);
  dt.assign(dc);
  
  dr *= 3.0;
  dr /= 3.0;
  
  dr += dt;
  dr -= di;
  
  dt = dz;
  
  dz = dt.T();
  di = dt.apply(neg);
  
  s = dr.similarityT(mm);  
  s = dr.similarity(mt);
#if defined(PRINTOUT)
 cout << "sim=" << dr.similarity(v);
#endif

  dt = dr.sub(2,5);
  dz.sub(3,dt);

  //
  // Test of HepVector
  //

  HepVector vt;
  HepVector vp(6);
  HepVector vz(6,0);
  HepVector vi(6,1);
  HepVector vr(6,r);
  HepVector vc(vr);
#if defined(PRINTOUT)
 cout << "vz=" << vz << "vi=" << vi << endl;
#endif

  HepVector vm(HepMatrix(6,1,r));
  HepVector vs(HepSymMatrix(1,r));
  HepVector vd(HepDiagMatrix(1,r));
#if defined(PRINTOUT)
 cout << "Nr=" << vr.num_row() << endl;
#endif
#if defined(PRINTOUT)
 cout << "vr(3)=" << vr(3) << endl;
#endif

  vr(2) = r();
  
  vi *= 2.5;
  vi /= 2.5;
  
  vm += HepMatrix(6,1,r);
  vs += HepSymMatrix(1,r);
  vd += HepDiagMatrix(1,r);
  vi += vr;
  
  vm -= HepMatrix(6,1,r);
  vs -= HepSymMatrix(1,r);
  vd -= HepDiagMatrix(1,r);  
  vi -= vc;
  
  vm = HepMatrix(6,1,r);
  vs = HepSymMatrix(1,r);
  vd = HepDiagMatrix(1,r);
  vt = vc;
  
  vt = vc.apply(negv);
  vt = vc.sub(2,5);
  vc.sub(3,vt);
#if defined(PRINTOUT)
 cout << "Normsq=" << vc.normsq() << "Norm=" << vc.norm() << endl;
#endif
  
  m = vc.T();

  swap(vc,vr);
  
  vt = sr * vr;
  vt = dr * vr;
  vt = mt * vr;
  f = vr * m;

  //
  // Test of other operators
  //

  f = 3.5 * m;
  s = 3.5 * ss;
  dt = 3.5 * dr;
  vt = 3.5 * vr;

  f = m * 3.6;
  s = ss * 3.6;
  dt = dr * 3.6;
  vt = vr * 3.6;

  f = m / 3.6;
  s = ss / 3.6;
  dt = dr / 3.6;
  vt = vr / 3.6;

  d = HepMatrix(6,3,r);
  e = HepMatrix(6,3,r);
  m = d + e;
  d = HepMatrix(6,6,r);
  m = d + sr;
  m = d + dr;
  
  m = sr + d;
  m = dr + d;
  
  s = sr + si;
  dt = dr + di;
  
  s = dr + sr;
  s = sr + dr;

  e = HepMatrix(6,1,r);

  v = e + vr;
  
  v = vr + e;

  v = vr + vz;


  d = HepMatrix(6,3,r);
  e = HepMatrix(6,3,r);
  m = d - e;
  d = HepMatrix(6,6,r);
  dr = HepDiagMatrix(6,r);
  m = d - sr;
  m = d - dr;
  
  m = sr - d;
  m = dr - d;
  
  s = sr - si;
  dt = dr - di;
  
  s = dr - sr;
  s = sr - dr;

  e = HepMatrix(6,1,r);

  v = e - vr;
  
  v = vr - e;

  v = vr - vz;
  
  //
  // Test of Matrix inversion
  //

  m = HepMatrix(6,6,r);
//  a = m;
  int inv;
  a = m.inverse(inv);
#if defined(PRINTOUT)
 cout << "Inv=" << inv << endl;
#endif
  if(inv==0) {
#if defined(PRINTOUT)
    HepMatrix am(a * m), ma(m * a);
    cout << "a*m=" << am.apply(absf) << "m*a=" << ma.apply(absf) << endl;
#endif
  }

  v = HepVector(6,r);

  vt = solve(m, v);
#if defined(PRINTOUT)
 cout << "m*vt=" << m*vt << "v=" << v << endl;
#endif
  

  ss = HepSymMatrix(6,r);
//  s = ss;
  s = ss.inverse(inv);
#if defined(PRINTOUT)
 cout << "Inv=" << inv << endl;
#endif
  if(inv==0) {
#if defined(PRINTOUT)
    HepMatrix sss(s*ss), ssss(ss*s);
    cout << sss.apply(absf) << ssss.apply(absf) << endl;
#endif
  }
  
#if defined(PRINTOUT)
 cout << "Before diag:ss=" << ss << endl;
  s = ss;
#endif
  m = diagonalize(&ss);
#if defined(PRINTOUT)
  cout << "m=" << m << endl;
#endif
#if defined(PRINTOUT)
  cout << "ss=" << ss << endl;
  cout << "Sim" << ss.similarity(m) << endl;
  HepSymMatrix diff(ss.similarity(m) - s);
  cout << "Diff" << diff.apply(absf) << endl;
#endif

  m = HepMatrix(6,6,r);
  a = qr_inverse(m);
#if defined(PRINTOUT)
  HepMatrix am(a * m), ma(m * a);
  cout << am.apply(absf) << ma.apply(absf) << endl;
#endif
#if defined(PRINTOUT)
 cout << "Norm 1 =" << norm1(m) << endl;
#endif
#if defined(PRINTOUT)
 cout << "Norm 2 =" << norm(m) << endl;
#endif
#if defined(PRINTOUT)
 cout << "Norm i =" << norm_infinity(m) << endl;
#endif

  m = HepMatrix(8,6,r);
#if defined(PRINTOUT)
 cout << "m=" << m << endl;
#endif
  a = qr_decomp(&m);
#if defined(PRINTOUT)
 cout << "a=" << a  << "m=" << m << endl;
#endif
#if defined(PRINTOUT)
 cout << "a*m=" << a*m << endl;
#endif
  
  m = HepMatrix(8,8,r);
  v = HepVector(8,r);
  vt = qr_solve(m,v);
#if defined(PRINTOUT)
 cout << "v=" << v << " m*vt=" << m*vt << endl;
#endif

  m = HepMatrix(8,8,r);
  a = HepMatrix(8,3,r);
  b = qr_solve(m,a);
#if defined(PRINTOUT)
 cout << "v=" << a << " m*b=" << m*b << endl;
#endif
#if defined(PRINTOUT)
 cout << "Test was successful" << endl;
#endif

  //
  // Some useful things it can do.
  //
  // Spherisity
//  HepUniformRandomAB ab(-1,1);
  HepJamesRandom Myengine;
  RandFlat ab(Myengine);
  HepVector p[10];
  int i;
  for(i=0;i<10;i++) {
    p[i] = HepVector(3,ab);
    p[i] *= 2.0;
    p[i](1) -= 1;
    p[i](2) -= 1;
    p[i](3) -= 1;
  }
  HepSymMatrix sp(3,0);
  for(i=0;i<10;i++) {
    double psq = p[i].normsq();
    sp(1,1) += psq - p[i](1)*p[i](1);
    sp(2,2) += psq - p[i](2)*p[i](2);
    sp(3,3) += psq - p[i](3)*p[i](3);
    sp(2,1) -= p[i](2)*p[i](1);
    sp(3,1) -= p[i](3)*p[i](1);
    sp(3,2) -= p[i](3)*p[i](2);
  }
  HepMatrix spd = diagonalize(&sp);
  cout << "sp=" << sp << " spd=" << spd << endl;
  HepSymMatrix spps(7,r);
  HepSymMatrix sppss(spps);
  cout << "condition = " << condition(spps) << endl;
  HepMatrix sb = diagonalize(&spps);
  HepSymMatrix sppssdiff(sppss - spps.similarity(sb));
  cout << "spps=" << spps << "sppss - sim = " << sppssdiff.apply(absf)
       << endl;
  return 0;
}
