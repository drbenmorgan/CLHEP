// -*- C++ -*-
// $Id: testRandom.cc,v 1.1 2003/07/17 19:20:29 garren Exp $
// ----------------------------------------------------------------------
#include "CLHEP/Random/Randomize.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cin;
using namespace CLHEP;

HepJamesRandom theJamesEngine;
RandEngine theRandEngine;
DRand48Engine theDRand48Engine;
RanluxEngine theRanluxEngine(19780503,4);
Ranlux64Engine theRanlux64Engine;
RanecuEngine theRanecuEngine;
Hurd160Engine theHurd160Engine;
Hurd288Engine theHurd288Engine;
MTwistEngine theMTwistEngine;
RanshiEngine theRanshiEngine;
DualRand theDualRandEngine;
TripleRand theTripleRandEngine;

void init()
{
   HepRandom r;
   cout << "r=" << r() << endl;

   cout << endl << endl;
   cout << "---------------------------- Random shooting test -----------------------------" << endl;
   cout << "                             --------------------                              " << endl;
   cout << " >>> Random Engines available <<<" << endl << endl;
   cout << "   > HepJamesRandom (default)" << endl;
   cout << "   > Rand" << endl;
   cout << "   > DRand48" << endl;
   cout << "   > Ranlux" << endl;
   cout << "   > Ranlux64" << endl;
   cout << "   > Ranecu" << endl;
   cout << "   > Hurd160" << endl;
   cout << "   > Hurd288" << endl;
   cout << "   > MTwist" << endl;
   cout << "   > Ranshi" << endl;
   cout << "   > DualRand" << endl;
   cout << "   > TripleRand" << endl << endl;
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;

}  // end init()

void layout()
{
   float m=3.0;
   const int size=5;
   double vect[size];

   cout << " Flat ]0,1[          : " << RandFlat::shoot() << endl;
   cout << " Flat ]0,5[          : " << RandFlat::shoot(5) << endl;
   cout << " Flat ]-5,3[         : " << RandFlat::shoot(-5,3) << endl;
   cout << " Exp (m=1)           : " << RandExponential::shoot() << endl;
   cout << " Exp (m=3)           : " << RandExponential::shoot(3) << endl;
   cout << " Gauss (m=1)         : " << RandGauss::shoot() << endl;
   cout << " Gauss (m=3,v=1)     : " << RandGauss::shoot(3,1) << endl;
   cout << " Wigner(1,0.2)       : " << RandBreitWigner::shoot(1,0.2) << endl;
   cout << " Wigner(1,0.2,1)     : " << RandBreitWigner::shoot(1,0.2,1) << endl;
   cout << " Wigner2(1,0.2)      : " << RandBreitWigner::shootM2(1,0.2) << endl;
   cout << " Wigner2(1,0.2,1)    : " << RandBreitWigner::shootM2(1,0.2,1) << endl;
   cout << " IntFlat [0,99[      : " << RandFlat::shootInt(99) << endl;
   cout << " IntFlat [-99,37[    : " << RandFlat::shootInt(-99,37) << endl;
   cout << " Poisson (m=3.0)     : " << RandPoisson::shoot(m) << endl;
   cout << " Binomial(n=1,p=0.5) : " << RandBinomial::shoot() << endl;
   cout << " Binomial(n=-5,p=0.3): " << RandBinomial::shoot(-5,0.3) << endl;
   cout << " ChiSqr (a=1)        : " << RandChiSquare::shoot() << endl;
   cout << " ChiSqr (a=-5)       : " << RandChiSquare::shoot(-5) << endl;
   cout << " Gamma (k=1,l=1)     : " << RandGamma::shoot() << endl;
   cout << " Gamma (k=3,l=0.5)   : " << RandGamma::shoot(3,0.5) << endl;
   cout << " StudT (a=1)         : " << RandStudentT::shoot() << endl;
   cout << " StudT (a=2.5)       : " << RandStudentT::shoot(2.5) << endl;
   cout << endl;
   cout << " Shooting an array of 5 flat numbers ..." << endl << endl;
   RandFlat::shootArray(size,vect);
   for ( int i=0; i<size; ++i )
     cout << " " << vect[i];
   cout << endl << endl;
}   // end layout() 

void dist_layout()
{
   float m=3.0;
   const int size=5;
   double vect[size];

   HepJamesRandom aJamesEngine;
   RandEngine aRandEngine;
   DRand48Engine aDRand48Engine;
   RanluxEngine aRanluxEngine(19780503,4);
   Ranlux64Engine aRanlux64Engine;
   RanecuEngine aRanecuEngine;
   Hurd288Engine aHurd288Engine;
   MTwistEngine aMTwistEngine;
   RanshiEngine aRanshiEngine;
   TripleRand aTripleRandEngine;

   RandFlat aFlatObj(aJamesEngine);
   RandExponential anExponentialObj(aRandEngine);
   RandGauss aGaussObj(aDRand48Engine);
   RandBreitWigner aBreitObj(aRanluxEngine);
   RandPoisson aPoissonObj(aRanecuEngine);
   RandBinomial aBinomialObj(aHurd288Engine);
   RandChiSquare aChiSquareObj(aMTwistEngine);
   RandGamma aGammaObj(aRanshiEngine);
   RandStudentT aStudentTObj(aTripleRandEngine);

   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl << endl;
   cout << "-------------------- Shooting test on distribution objects --------------------" << endl;
   cout << endl;
   cout << " Flat ]0,1[          : " << aFlatObj.fire() << endl;
   cout << " Flat ]0,5[          : " << aFlatObj.fire(5) << endl;
   cout << " Flat ]-5,3[         : " << aFlatObj.fire(-5,3) << endl;
   cout << " Exp (m=1)           : " << anExponentialObj.fire() << endl;
   cout << " Exp (m=3)           : " << anExponentialObj.fire(3) << endl;
   cout << " Gauss (m=1)         : " << aGaussObj.fire() << endl;
   cout << " Gauss (m=3,v=1)     : " << aGaussObj.fire(3,1) << endl;
   cout << " Wigner(1,0.2)       : " << aBreitObj.fire(1,0.2) << endl;
   cout << " Wigner(1,0.2,1)     : " << aBreitObj.fire(1,0.2,1) << endl;
   cout << " Wigner2(1,0.2)      : " << aBreitObj.fireM2(1,0.2) << endl;
   cout << " Wigner2(1,0.2,1)    : " << aBreitObj.fireM2(1,0.2,1) << endl;
   cout << " IntFlat [0,99[      : " << aFlatObj.fireInt(99) << endl;
   cout << " IntFlat [-99,37[    : " << aFlatObj.fireInt(-99,37) << endl;
   cout << " Poisson (m=3.0)     : " << aPoissonObj.fire(m) << endl;
   cout << " Binomial(n=1,p=0.5) : " << aBinomialObj.fire() << endl;
   cout << " Binomial(n=-5,p=0.3): " << aBinomialObj.fire(-5,0.3) << endl;
   cout << " ChiSqr (a=1)        : " << aChiSquareObj.fire() << endl;
   cout << " ChiSqr (a=-5)       : " << aChiSquareObj.fire(-5) << endl;
   cout << " Gamma (k=1,l=1)     : " << aGammaObj.fire() << endl;
   cout << " Gamma (k=3,l=0.5)   : " << aGammaObj.fire(3,0.5) << endl;
   cout << " StudT (a=1)         : " << aStudentTObj.fire() << endl;
   cout << " StudT (a=2.5)       : " << aStudentTObj.fire(2.5) << endl;
   cout << endl;
   cout << " Shooting an array of 5 flat numbers ..." << endl << endl;
   aFlatObj.fireArray(size,vect);
   for ( int i=0; i<size; ++i )
     cout << " " << vect[i];
   cout << endl << endl;
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
}   // end dist_layout() 

void user_layout()
{
   float m=3.0;
   const int size=5;
   double vect[size];
   char sel;
   HepRandomEngine* anEngine;

   cout << endl << endl;
   cout << "-------------------- Shooting test skeeping the generator ---------------------" << endl;
   cout << endl;
   cout << " >>> Select a Random Engine <<<" << endl << endl;
   cout << "   a. HepJamesRandom (default)" << endl;
   cout << "   b. Rand" << endl;
   cout << "   c. DRand48" << endl;
   cout << "   d. Ranlux" << endl;
   cout << "   e. Ranlux64" << endl;
   cout << "   f. Ranecu" << endl;
   cout << "   g. Hurd160" << endl;
   cout << "   h. Hurd288" << endl;
   cout << "   i. MTwist" << endl;
   cout << "   j. Ranshi" << endl;
   cout << "   k. DualRand" << endl;
   cout << "   l. TripleRand" << endl << endl;
   cout << " > ";
   cin >> sel;
   while ((sel!='a')&&(sel!='b')&&(sel!='c')&&(sel!='d')&&(sel!='e')&&
          (sel!='f')&&(sel!='g')&&(sel!='h')&&(sel!='i')&&(sel!='j')&&
          (sel!='k')&&(sel!='l')) {
     cout << endl << " >>> Choice not legal !!  [a..l]<<<" << endl;
     cin >> sel;
   }

   switch (sel) {
     case 'a':
       anEngine = &theJamesEngine;
       break;
     case 'b':
       anEngine = &theRandEngine;
       break;
     case 'c':
       anEngine = &theDRand48Engine;
       break;
     case 'd':
       anEngine = &theRanluxEngine;
       break;
     case 'e':
       anEngine = &theRanlux64Engine;
       break;
     case 'f':
       anEngine = &theRanecuEngine;
       break;
     case 'g':
       anEngine = &theHurd160Engine;
       break;
     case 'h':
       anEngine = &theHurd288Engine;
       break;
     case 'i':
       anEngine = &theMTwistEngine;
       break;
     case 'j':
       anEngine = &theRanshiEngine;
       break;
     case 'k':
       anEngine = &theDualRandEngine;
       break;
     case 'l':
       anEngine = &theTripleRandEngine;
       break;
     default:
       anEngine = &theJamesEngine;
       break;
   }
   cout << endl;
 
   cout << " Flat ]0,1[          : " << RandFlat::shoot(anEngine) << endl;
   cout << " Flat ]0,5[          : " << RandFlat::shoot(anEngine,5) << endl;
   cout << " Flat ]-5,3[         : " << RandFlat::shoot(anEngine,-5,3) << endl;
   cout << " Exp (m=1)           : " << RandExponential::shoot(anEngine) << endl;
   cout << " Exp (m=3)           : " << RandExponential::shoot(anEngine,3) << endl;
   cout << " Gauss (m=1)         : " << RandGauss::shoot(anEngine) << endl;
   cout << " Gauss (m=3,v=1)     : " << RandGauss::shoot(anEngine,3,1) << endl;
   cout << " Wigner(1,0.2)       : " << RandBreitWigner::shoot(anEngine,1,0.2) << endl;
   cout << " Wigner(1,0.2,1)     : " << RandBreitWigner::shoot(anEngine,1,0.2,1) << endl;
   cout << " Wigner2(1,0.2)      : " << RandBreitWigner::shootM2(anEngine,1,0.2) << endl;
   cout << " Wigner2(1,0.2,1)    : " << RandBreitWigner::shootM2(anEngine,1,0.2,1) << endl;
   cout << " IntFlat [0,99[      : " << RandFlat::shootInt(anEngine,99) << endl;
   cout << " IntFlat [-99,37[    : " << RandFlat::shootInt(anEngine,-99,37) << endl;
   cout << " Poisson (m=3.0)     : " << RandPoisson::shoot(anEngine,m) << endl;
   cout << " Binomial(n=1,p=0.5) : " << RandBinomial::shoot(anEngine) << endl;
   cout << " Binomial(n=-5,p=0.3): " << RandBinomial::shoot(anEngine,-5,0.3) << endl;
   cout << " ChiSqr (a=1)        : " << RandChiSquare::shoot(anEngine) << endl;
   cout << " ChiSqr (a=-5)       : " << RandChiSquare::shoot(anEngine,-5) << endl;
   cout << " Gamma (k=1,l=1)     : " << RandGamma::shoot(anEngine) << endl;
   cout << " Gamma (k=3,l=0.5)   : " << RandGamma::shoot(anEngine,3,0.5) << endl;
   cout << " StudT (a=1)         : " << RandStudentT::shoot(anEngine) << endl;
   cout << " StudT (a=2.5)       : " << RandStudentT::shoot(anEngine,2.5) << endl;
   cout << endl;
   cout << " Shooting an array of 5 flat numbers ..." << endl << endl;
   RandFlat::shootArray(anEngine,size,vect);
   for ( int i=0; i<size; ++i )
     cout << " " << vect[i];
   cout << endl << endl;
}   // end layout() 

void start_test()
{
   cout << "-------------------------  Test on HepJamesRandom  ----------------------------" << endl;
   cout << endl;
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "---------------------------  Test on RandEngine  ------------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theRandEngine);
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "-------------------------  Test on DRand48Engine  -----------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theDRand48Engine);
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "---------------------  Test on RanluxEngine (luxury 4) ------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theRanluxEngine);
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "-------------------------  Test on Ranlux64Engine -----------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theRanlux64Engine);
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "--------------------------  Test on RanecuEngine ------------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theRanecuEngine);
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "-------------------------  Test on Hurd160Engine ------------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theHurd160Engine);
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "-------------------------  Test on Hurd288Engine ------------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theHurd288Engine);
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "--------------------------  Test on MTwistEngine ------------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theMTwistEngine);
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "--------------------------  Test on RanshiEngine ------------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theRanshiEngine);
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "-------------------------  Test on DualRandEngine -----------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theDualRandEngine);
   layout();
   cout << "                   -----  Press <ENTER> to continue  -----";
   if ( cin.get() != '\n') exit(0);
   cout << endl;
   cout << "------------------------  Test on TripleRandEngine ----------------------------" << endl;
   cout << endl;
   HepRandom::setTheEngine(&theTripleRandEngine);
   layout();
   dist_layout();
   user_layout();
}  // end start_test()


int main() {

   init();
   start_test();
   
   return 0;
}

