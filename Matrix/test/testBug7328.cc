// testBug7328.cc
//
// The bug reported a memory leak in inverting symmetric matrices (of size
// greater than 6x6).
//
// This test verifies that the leak is no longer present, and checks for
// correctness.  There is a break in method at N=25, so both sides are examined.
//
// A similar (though unreported) leak was present in the Determinant method;
// since this was also fixed, this test tests for correctness of determinant as
// well.
//

#include <iostream>
//#include <iomanip>
#include <cmath>
#include <stdlib.h>

#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Matrix/SymMatrix.h"

int test_inversion (int N) {

  int i,j;
  CLHEP::HepSymMatrix S(N,0); 
  for(i=1;i<=N;++i) { 
    for(j=1;j<=N;++j) { 
      if(i<=j) { 
	S (i,j) = (10.0*i+j)/10;
      } 
    } 
  }
  CLHEP::HepSymMatrix SS(N,0); 
  SS = S;
  int ierr = 0;
  SS.invert(ierr);
  if (ierr) {
    std::cout<<"SS.invert failed!!!!  N = " << N << 
    			" ierr =  "<< ierr <<std::endl; 
    return 2+100*N;
  }
  CLHEP::HepMatrix SI(N,N,0);
  CLHEP::HepMatrix MS(N,N,0);
  CLHEP::HepMatrix MSS(N,N,0); 
  MS = S;
  MSS = SS;
  SI = MSS*MS;
  for(i=1;i<=N;++i) { 
    for(j=1;j<=N;++j) { 
      if(i!=j) { 
	if (fabs(SI(i,j)) > 1.0e-6) {
    	  std::cout<<"SS.invert incorrect  N = " << N << 
    			" error =  "<< fabs(SI(i,j)) <<std::endl; 
	  return 3+100*N;
	}
      } 
      if(i==j) { 
	if (fabs(1-SI(i,j)) > 1.0e-6) {
    	  std::cout<<"SS.invert incorrect  N = " << N << 
    			" error =  "<< fabs(1-SI(i,j)) <<std::endl; 
	  return 4+100*N;
	}
      } 
    } 
  }
#define DET_ALSO
#ifdef  DET_ALSO
  double detS  =  S.determinant();
//    std::cout<<"Determinant   N = " << N << 
//    	"  =  " << detS <<std::endl;   
  double detSS = SS.determinant();
//    std::cout<<"Determinant Inverse  N = " << N << 
//    	"  =  " << detSS <<std::endl; 
  if (fabs((detS-1.0/detSS)/detS) > 1.0e-6) {
    std::cout<<"Determinant incorrect  N = " << N << 
    			" error =  " << fabs((detS-1.0/detSS)/detS) <<std::endl; 
	  return 5+100*N;
  }  
#endif
  return 0;
}

void heapAddresses ( double * &hNew, 
		     double * &hMalloc, 
		     double * &hNew10000, 
		     double * &hMalloc80000 ) {
  hNew = new double;
  hMalloc =  (double*) malloc(sizeof(double));		    
  hNew10000 = new double[10000];
  hMalloc80000 =  (double*) malloc(10000*sizeof(double));
//  std::cout << std::hex << hNew << " " << hMalloc<< " " 
//            << hNew10000 << " " << hMalloc80000 << std::endl;
  free (hMalloc80000);
  delete[] hNew10000;
  free (hMalloc);
  delete hNew;
}

int checkHeap (	double * &hNew, 
		double * &hMalloc, 
		double * &hNew10000, 
		double * &hMalloc80000,
		double * &xhNew, 
		double * &xhMalloc, 
		double * &xhNew10000, 
  		double * &xhMalloc80000 ) {
  int ret = 0;
  if (hNew != xhNew) {
    std::cout<< "Leak:\n"
    << "xhNew - hNew = " <<  xhNew - hNew << "\n";
    ret |= 1;
  }
  if (hMalloc != xhMalloc) {
    std::cout<< "Leak:\n"
    << "xhMalloc - hMalloc = " <<  xhMalloc - hMalloc << "\n";
    ret |= 2;
  }
  if (hNew10000 != xhNew10000) {
    std::cout<< "Leak:\n"
    << "xhNew10000 - hNew10000 = " <<  xhNew10000 - hNew10000 << "\n";
    ret |= 4;
  }
  if (hMalloc80000 != xhMalloc80000) {
    std::cout<< "Leak:\n"
    << "xhMalloc80000 - hMalloc80000 = " <<  xhMalloc80000 -hMalloc80000 
    << "\n";
    ret |= 8;
  }
  return ret; 
}

int main(int, char **) {
  int ret=0;
  int rhp;
  int i,j;
  for ( i = 1; i <= 50; i++) {
    ret = test_inversion(i);
    if (ret) return ret;
  }
  double *hNew, *hMalloc, *hNew10000, *hMalloc80000;
  double *xhNew, *xhMalloc, *xhNew10000, *xhMalloc80000;
  
  for (int count=0; count < 2; ++count) {

    int n1 = 400;
    int n2 = 25;
    heapAddresses ( hNew, hMalloc, hNew10000, hMalloc80000 );
    for (i=0; i<n1; i++) {
      for (j=1; j <= n2; j++) {
	ret = test_inversion(j);
	if (ret) return ret;
      }
    }
    heapAddresses ( xhNew, xhMalloc, xhNew10000, xhMalloc80000 );
    rhp = 0;
    if(count != 0) rhp =  checkHeap ( hNew,  hMalloc,  hNew10000,  hMalloc80000,
                      xhNew, xhMalloc, xhNew10000, xhMalloc80000 );
    if (rhp) std::cout << "Above Leak is after " << n1*n2 << " test inversions\n";
    ret |= rhp;

    heapAddresses ( hNew, hMalloc, hNew10000, hMalloc80000 );
    for (i=0; i<2; i++) {
      for (j=1; j < 20; j++) {
	rhp = test_inversion(25+2*j);
	if (rhp) return rhp;
      }
    }
    heapAddresses ( xhNew, xhMalloc, xhNew10000, xhMalloc80000 );
    rhp = 0;
    if(count != 0) rhp =  checkHeap ( hNew,  hMalloc,  hNew10000,  hMalloc80000,
                      xhNew, xhMalloc, xhNew10000, xhMalloc80000 );
    if (rhp) std::cout << "Leak after big inversions\n";
    ret |= rhp;
  } 
  return ret;
}

