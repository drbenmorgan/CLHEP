// -*- C++ -*-
// $Id: testInversion.cc,v 1.2 2003/08/13 20:00:12 garren Exp $
//
// This file is a part of CLHEP - a Class Library for High Energy Physics.
//
// This is a collection of parts of programs that are useful
// for testing matrix inversion algorithms
// 9/97, Mario Stanke

#include <time.h>
#include <iostream>

#include "CLHEP/Matrix/defs.h"
#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/DiagMatrix.h"

using std::cout;
using std::endl;

using namespace CLHEP;

int main()
{
//int n , i, j, k, ierr1, ierr2;
  int n, j, ierr1, ierr2;  
  time_t zeit1, zeit2;
  
// ****compare the speed of inversion algorithms

  HepSymMatrix A(5,1);

 // for (j=1;j <= 100; j++)
 //   for (k=1; k<=j; k++)
 //     A(j,k)=rand()%9-5;

  A(1,1)=6;
  A(1,2)=.8545;
  A(1,3)=-.684651;
  A(1,4)=.372547;
  A(1,5)=.68151;
  //A(1,6)=.068151;
  A(2,2)=4;
  A(2,3)=.5151;
  A(2,4)=.5151;
  A(2,5)=.651651;
  //A(2,6)=.9651651;
  A(3,3)=5;
  A(3,4)=.3;
  A(3,5)=.363;
  //A(3,6)=.7363;
  A(4,4)=-3;
  A(4,5)=-.23753;
  //A(4,6)=-.23753;
  A(5,5)=-5;
  //A(5,6)=-2;
  //A(6,6)=-3;

  HepSymMatrix B(A);
  HepSymMatrix D(A);
  HepSymMatrix C(5,0);
  HepMatrix M(A);

 cout << "M inverse" << M.inverse(ierr2) << endl;
  
  C = B.inverse(ierr1);
  D.invert(ierr2);

  cout << "B " << B << endl;
  cout << "B inverse" << C << endl;
#ifndef INSTALLATION_CHECK
  cout << "B * inverse" << B * C << endl;
#endif
  cout << "ierr1: " << ierr1 << endl;

  cout << "D * inverse" << D * C << endl;
  cout << "ierr2: " << ierr2 << endl;
  cout << "M inverse" << M.inverse(ierr2) << endl;
#ifndef INSTALLATION_CHECK
  cout << "M * inverse" << M * M.inverse(ierr2)<< endl;
#endif
  cout << "ierr2: " << ierr2 << endl;

#ifndef INSTALLATION_CHECK
  n = 100000;
#else
  n = 10;
#endif
  zeit1 = time(NULL);
  cout << "Executing " << n << " inversions ..." << endl;
  for (j=0; j<n; j++)
    {
      B.invert(ierr1);   
      if (ierr1)
	cout << "B: error in invert" << endl;
    }
  zeit2 = time(NULL);
  cout << "B: duration of inversion: " << zeit2-zeit1 << " secs" << endl;
 
  zeit1 = time(NULL);  
  cout << "Executing " << n << " inversions ..." << endl;
  for (j=0; j<n; j++)
    {
      D.invert(ierr2);
      if (ierr2)
	cout << "D: error in invert" << endl;
    }
  zeit2 = time(NULL);
  cout << D << endl;
  cout << "D: duration of inversion: " << zeit2-zeit1 << " secs" << endl;


/***** check correctness and compare results of inversion algorithms

  double dist1, dist2;
  HepSymMatrix A(5,1), B(5), C(5), I(5,1);
  HepSymMatrix M(5);
  n = 200000;
 
  for (j=1; j <= n ; j++)
    {
      A(1,1)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(1,2)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(1,3)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(1,4)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(1,5)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      //A(1,6)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(2,2)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(2,3)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(2,4)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(2,5)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      //A(2,6)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(3,3)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(3,4)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(3,5)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      //A(3,6)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(4,4)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(4,5)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      //A(4,6)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      A(5,5)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      //A(5,6)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
      //A(6,6)=(((rand()%7-3)))+ (rand()%3-1)*1e-10;
    	
      M=B=C=A;
      	
      B.invert(ierr2);
      M.old_invert(ierr1);
      
      dist2 = norm_infinity(B*C-I);
      dist1 = norm_infinity(M*C-I);

      
      if (ierr1 != ierr2)
	{
	  cout << C << endl;
	  cout << "B " << B << endl;
	  cout << "B*C" << B*C << endl;
	  cout << "M*C" << M*C << endl;
	  cout << "M " << M << endl;
	  cout << "determinant " << C.determinant() << endl;
	  cout << "dist2 " << dist2 << endl;
	  cout << "dist1 " << dist1 << endl;

	  cout << "ierr2 " << ierr2 <<endl;
	  cout << "ierr1 " << ierr1 <<endl;

	  cout << "j " << j << endl;
	}
	
      if (ierr2==0 && dist2 > 1e-4)
	{
	  cout << "bunch failed to invert but did not indicate" << endl;
	  cout << C << endl;
	  cout << "B " << B << endl;
	  cout << "B*C" << B*C << endl;
	  cout << "M*C" << M*C << endl;
	  cout << "determinant " << C.determinant() << endl;
	  cout << "dist2 " << dist2 << endl;
	  cout << "dist1 " << dist1 << endl;

	  cout << "ierr2 " << ierr2 <<endl;
	  cout << "ierr1 " << ierr1 <<endl;

	  cout << "j " << j << endl;
	}
      if (ierr2==1)
	{
	  // bunch thinks it is singular
	  if (norm_infinity(M*C-I) < 1e-6)
	    {
	      cout << "bunch said it is singular but old could invert"
		<< endl;
	      cout << C << endl;
	      cout << "B*C" << B*C << endl;
	      cout << "M*C" << M*C << endl; 
	      cout << "determinant " << C.determinant() << endl;
	 
	      cout << "dist2" << dist2 << endl;
	      cout << "ierr2 " << ierr2 <<endl;
	      cout << "ierr1 " << ierr1 <<endl;

	      cout << "j " << j << endl;
	    }
	}
      
      if (ierr1==0 && dist1 > 1e-4 && ierr2==0)
	{
	  cout << "old failed to invert but did not indicate" << endl;
	  
	  cout << C << endl;
	  cout << "B*C" << B*C << endl;
	  cout << "M*C" << M*C << endl;
	  cout << "determinant " << C.determinant() << endl;
	
	  cout << "ierr2 " << ierr2 <<endl;
	  cout << "ierr1 " << ierr1 <<endl;

	  cout << "dist1 " << dist1 << endl;
	  cout << "j " << j << endl;
	  return 0;
	  
	}
      if (ierr1==1)
	{
	  // old thinks it is singular
	  if (norm_infinity(B*C-I) < 1e-6)
	    {
	      cout << "old said it is singular but bunch could invert"
		<< endl;
	      
	      cout << C << endl;
	      cout << "B*C" << B*C << endl;
	      cout << "M*C" << M*C << endl;
	      cout << "determinant " << C.determinant() << endl;
	
	      cout << "dist1" << dist1 << endl;
	      cout << "dist2" << dist2 << endl;
	      cout << "ierr2 " << ierr2 <<endl;
	      cout << "ierr1 " << ierr1 <<endl;
	      
	      cout << "j " << j << endl;
	      return 0;
	      
	      }
	}
	
    }
*/
  
/*** one tough symmetric matrix from real physical data

  sm(1,1)=5347.51; 
  sm(1,2)=-142756; 
  sm(1,3)= -1.86624e+06;
  sm(1,4)=0.0164743; 
  sm(1,5)=0.0915348; 
  sm(1,6)=0.421851;
  sm(2,2)=3.81277; 
  sm(2,3)=4.98668e+07; 
  sm(2,4)=-0.0697533; 
  sm(2,5)=12.8555; 
  sm(2,6)=-2.01124;
  sm(3,3)=6.52498e+08; 
  sm(3,4)=3.87491; 
  sm(3,5)=365.965; 
  sm(3,6)=93.3686;
  sm(4,4)=7.77672e-05; 
  sm(4,5)=0.0032134; 
  sm(4,6)=0.00194407; 
  sm(5,5)=0.132845;
  sm(5,6)=0.0803294; 
  sm(6,6)=0.0485992;
 
*/

/**** a group of near singular (nonsingular) matrices
  int n=5;
  HepSymMatrix sm(n); // nxn Hilbert Matrix
  for(i=1;i<=n;i++)
    for(k=i;k<=n;k++)
      sm(i,k)=1./(i+k-1);
*/
  return 0;
} // end of main



