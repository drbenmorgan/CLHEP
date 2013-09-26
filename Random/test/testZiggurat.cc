//////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "CLHEP/Random/RandGauss.h"
#include "CLHEP/Random/RandGaussQ.h"
#include "CLHEP/Random/RandExponential.h"
#include "CLHEP/Random/RandGaussZiggurat.h"
#include "CLHEP/Random/RandExpZiggurat.h"

//_________________________________________________________________________
int main() {

 std::ofstream output("testZiggurat.cout");  

 int ntest=10000000;

 output << "DEBUG: ntest="<<ntest<<std::endl;

 double sum_rnd1=0;
 for(int i=0;i<ntest;++i) {
   double g=CLHEP::RandGauss::shoot();
   sum_rnd1+=g;
 }  
 sum_rnd1/=ntest;
 output << "DEBUG: avg RandGauss="<<sum_rnd1<<std::endl;

 double sum_rnd2=0;
 for(int i=0;i<ntest;++i) {
   double g=CLHEP::RandGaussQ::shoot();
   sum_rnd2+=g;
 }  
 sum_rnd2/=ntest;
 output << "DEBUG: avg RandGaussQ="<<sum_rnd2<<std::endl;

 double sum_zig=0;
 for(int i=0;i<ntest;++i) {
   double g=CLHEP::RandGaussZiggurat::shoot();
    sum_zig+=g;
 }  
 sum_zig/=ntest;
 output << "DEBUG: avg RandGaussZiggurat="<<sum_zig<<std::endl;

 double sum_exp=0;
 for(int i=0;i<ntest;++i) {
   double g=CLHEP::RandExponential::shoot();
   sum_exp+=g;
 }  
 sum_exp/=ntest;
 output << "DEBUG: avg RandExponential="<<sum_exp<<std::endl;

 double sum_expZ=0;
 for(int i=0;i<ntest;++i) {
   double g=CLHEP::RandExpZiggurat::shoot();
   sum_expZ+=g;
 }  
 sum_expZ/=ntest;
 output << "DEBUG: avg RandExpZiggurat="<<sum_expZ<<std::endl;

 return 0;
}


