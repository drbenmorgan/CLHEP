// testBug6181.cc
//
// The bug reported an erroneous result in inverting a 7x7 matrix.
//
// 7x7 represents the break point between the low-n methods and 
// the general-size method.  This test program tests the case triggering
// the bug report, and also inversion for matrices (both symmetric and 
// general) of sizes 1 - 9.

#include <iostream>
#include <math.h>

#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Matrix/SymMatrix.h"

int test_inversion (int N) {

  int i;
  int j;
  CLHEP::HepMatrix M(N,N,0); 
  CLHEP::HepSymMatrix S(N,0); 
  for(i=1;i<=N;++i) { 
    for(j=1;j<=N;++j) { 
      if(i<=j) { 
	S (i,j) = 10*i+j;
	M (i,j) = 10*i+j; 
	M (j,i) = M(i,j) + .1 * (i-j)*(i-j);
      } 
    } 
  }
  CLHEP::HepMatrix MM(N,N,0); 
  CLHEP::HepSymMatrix SS(N,0); 
  MM = M;
  SS = S;
  int ierr = 0;
  MM.invert(ierr);
  if (ierr) {
    std::cout<<"MM.invert failed!!!!  N = " << N << 
    			" ierr =  "<< ierr <<std::endl; 
    return 1+100*N;
  }
  ierr = 0;
  SS.invert(ierr);
  if (ierr) {
    std::cout<<"SS.invert failed!!!!  N = " << N << 
    			" ierr =  "<< ierr <<std::endl; 
    return 2+100*N;
  }
  CLHEP::HepMatrix MI(N,N,0); 
  CLHEP::HepMatrix SI(N,N,0);
  CLHEP::HepMatrix MS(N,N,0);
  CLHEP::HepMatrix MSS(N,N,0); 
  MI = MM*M;
  MS = S;
  MSS = SS;
  SI = MSS*MS;
  for(i=1;i<=N;++i) { 
    for(j=1;j<=N;++j) { 
      if(i!=j) { 
	if (fabs(MI(i,j)) > 1.0e-12) {
    	  std::cout<<"MM.invert incorrect  N = " << N << 
    			" error =  "<< fabs(MI(i,j)) <<std::endl; 
	  return 3+100*N;
	}
	if (fabs(SI(i,j)) > 1.0e-12) {
    	  std::cout<<"SS.invert incorrect  N = " << N << 
    			" error =  "<< fabs(SI(i,j)) <<std::endl; 
	  return 4+100*N;
	}
      } 
      if(i==j) { 
	if (fabs(1-MI(i,j)) > 1.0e-12) {
    	  std::cout<<"MM.invert incorrect  N = " << N << 
    			" error =  "<< fabs(1-MI(i,j)) <<std::endl; 
	  return 3+100*N;
	}
	if (fabs(1-SI(i,j)) > 1.0e-12) {
    	  std::cout<<"SS.invert incorrect  N = " << N << 
    			" error =  "<< fabs(1-SI(i,j)) <<std::endl; 
	  return 4+100*N;
	}
      } 
    } 
  }
  // Finally, the case that actually (for N=7) triggered bug report 6181:
  M = S;
  MM = M;
  MM.invert(ierr);
  if (ierr) {
    std::cout<<"MM.invert for symmetric case failed!!!!  N = " << N << 
    			" ierr =  "<< ierr <<std::endl; 
    return 5+100*N;
  }
  MI = MM*M;
  for(i=1;i<=N;++i) { 
    for(j=1;j<=N;++j) { 
      if(i!=j) { 
	if (fabs(MI(i,j)) > 1.0e-12) {
    	  std::cout<<"MM.invert incorrect  N = " << N << 
    			" error =  "<< fabs(MI(i,j)) <<std::endl; 
	  return 6+100*N;
	}
      } 
      if(i==j) { 
	if (fabs(1-MI(i,j)) > 1.0e-12) {
    	  std::cout<<"MM.invert incorrect  N = " << N << 
    			" error =  "<< fabs(1-MI(i,j)) <<std::endl; 
	  return 7+100*N;
	}
      } 
    } 
  }
  return 0;
}


int main(int, char **) {
  int ret=0;
  for (int i=1; i<10; i++) {
    ret = test_inversion(i);
    if (ret) return ret;
  }
  return ret;
}

