// $Id: translatePDTtoPythia.cc,v 1.2 2004/04/14 23:56:28 garren Exp $
// --------------------------
//
// translatePDTtoPythia.cc
//
// --------------------------

#include <iostream>

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int translatePDTtoPythia( const int id )
{

    static int itabj[100] = { 1,2,3,4,5,6,7,8,0,51,
                 11,12,13,14,15,16,17,18,28,29,
                 21,22,23,24,25,0,0,0,0,0,
                 0,32,33,34,35,36,37,0,0,0,
                 40,39,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,
                 81,82,83,84,85,86,87,88,89,90,
                 91,92,93,94,95,96,97,98,99, 0 };
      static int noant[11] = {-10,-21,-22,-23,-25,-32,-33,-35,-36,-81,-83};
    int i;

int   lutran=id;
int   ida=abs(id);
int   j1=ida%10;
int   i1=(ida/10)%10;
int   i2=(ida/100)%10;
int   i3=(ida/1000)%10;
int   ksusy =( ida/1000000)%10;
int   ku =( ida/10000000)%10;
int   kqn=(ida/1000000000)%10;
    ParticleID pid(id);

      if(ida == 0){
        std::cout << "(LUTRAN 1:) particle ID is zero" << std::endl;
        return 0;
//... ions not allowed
      } else if(kqn == 1) {
        std::cout << "(LUTRAN 3:) unallowed ion" << std::endl;
        return 0;
//...SUSY 
      } else if(ksusy == 1 || ksusy == 2) {
        return id;
//...technicolor
      } else if(ksusy == 3) {
	    if(id == 3000111) { return 51; }
	    if(id == 3000211) { return 52; }
	    if(id == -3000211) { return -52; }
	    if(id == 3100111) { return 53; }
	    if(id == 3000221) { return 38; }
	    if(id == 3000113) { return 54; }
	    if(id == 3000213) { return 55; }
	    if(id == -3000213) { return -55; }
	    if(id == 3000223) { return 56; }
        return 0;
//...excited quarks and leptons
      } else if(ksusy == 4) {
        return id;
//...other exotics
      } else if(ksusy == 5) {
        return 0;
//...quarks, Higgs, etc.
      } else if(ida <= 100){
        lutran=itabj[ida-1];
//...check for illegal antiparticles
        if(id < 0){
          if(lutran >= 91 && lutran <= 99) { return 0; }
          for( i=0; i < 11; ++i ) {
            if(lutran == noant[i]) { return 0; }
          }
          lutran = -lutran;
        }
        return lutran;
//...special particles
      } else if(j1 == 0 ) {
          if(id == 110) { return 28; }
          if(id == 990) { return 29; }
          return 0;
      } else if(ksusy == 9 && ku == 9 ) {
	  if(id == 9900041) { return 61; }
	  if(id == 9900042) { return 62; }
	  if(id == 9900024) { return 63; }
	  if(id == 9900012) { return 64; }
	  if(id == 9900014) { return 65; }
	  if(id == 9900016) { return 66; }
	  if(id == -9900041) { return -61; }
	  if(id == -9900042) { return -62; }
	  if(id == -9900024) { return -63; }
	  if(id == -9900012) { return -64; }
	  if(id == -9900014) { return -65; }
	  if(id == -9900016) { return -66; }
	  if(id == 9910113) { return 110; }
 	  if(id == 9910211) { return 210; }
 	  if(id == -9910211) { return -210; }
	  if(id == 9910223) { return 220; }
	  if(id == 9910333) { return 330; }
	  if(id == 9910443) { return 440; }
 	  if(id == 9912112) { return 2110; }
 	  if(id == -9912112) { return -2110; }
 	  if(id == 9912212) { return 2210; }
 	  if(id == -9912212) { return -2210; }
          return 0;
//...baryons
      } else if( pid.isBaryon() ){
        return id;
//...mesons 
      } else if(i1 != 0  && i2 != 0  && i3 == 0){
//...check for illegal antiparticles
        if(i1 == i2 && id < 0) { return 0; }
          if(id == 10111) { return 0; }
          if(id == 10211) { return 0; }
          if(id == 9000111) { return 10111; }
          if(id == 9000211) { return 20211; }
          if(id == -9000211) { return -20211; }
          if(id == 9010221) { return 10221; }
          if(id == 10221) { return 10331; }
          if(id == 9000223) { return 0; }
        return id;
//...diquarks
      } else if(i2 != 0 && i3 != 0 && i1 == 0){
        return id;
      }
//...undefined
        std::cout << "(LUTRAN 5:) particle ID translation is zero" << std::endl;
        return 0;
}

}	// HepPDT
