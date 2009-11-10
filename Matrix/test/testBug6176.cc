#include <iostream>

#include "CLHEP/Matrix/Matrix.h"

typedef CLHEP::HepMatrix AlgebraicMatrix; 

int main(int, char **) {

AlgebraicMatrix mtr(7,7,0); 
for(int i=1;i<8;++i) 
{ 
  for(int j=1;j<8;++j) 
    { 
      if(i<=j) 
	{ 
	  mtr(i,j) = 10*i+j; 
	  mtr(j,i) = 10*j+i; 
	} 
    } 
}

std::cout<<"Initial matrix "<<mtr<<std::endl; 
std::cout<<"Sub (1,4,1,4)"<<mtr.sub(1,4,1,4)<<std::endl; 

}
