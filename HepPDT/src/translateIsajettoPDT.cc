// $Id: translateIsajettoPDT.cc,v 1.2 2004/04/14 23:56:28 garren Exp $
// ----------------------------------------------------------------------
//
// translateIsajettoPDT.cc
//
// translate an Isajet ID number to the standard numbering scheme
//
// ----------------------------------------------------------------------

#include <iostream>

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int translateIsajettoPDT( const int id )
{
// ... itabi(I) converts miscellaneous ISAJET particle ID's to a standard scheme
    static int itabi[100]={2,1,3,4,5,6,7,8,21,22,
                12,11,14,13,16,15,0,0,0,310,
                1000002,1000001,1000003,1000004,1000005,1000006,
                0,0,1000021,1000022,
                1000012,1000011,1000014,1000013,1000016,1000015,
                0,0,1000024,1000023,
                2000002,2000001,2000003,2000004,2000005,2000006,
                0,0,1000037,1000025,
                2000012,2000011,2000014,2000013,2000016,2000015,
                0,0,0,1000035,
                0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,24,
                25,51,35,36,55,37,53,52,54,23,
                1000039,39,0,0,0,0,0,0,0,0};
    static int noant[10]={-21,-22,-23,-25,-32,-33,-35,-36,-51,-56};
    int i;

    int istran=0;
    ParticleID pid(id);
    int ida=pid.abspid();
    int js=ida%10;
    int i1=(ida/10)%10;
    int i2=(ida/100)%10;
    int i3=(ida/1000)%10;
    int i4=(ida/10000)%10;

    if(ida == 0) {
        std::cout << " ISTRAN: particle ID is zero" << std::endl;
    } else if(ida <= 100) {
        istran = itabi[ida-1];
	if( id < 0 ) { istran = -itabi[ida-1]; }
        if( id == -20) { istran=130; }
        // ...check for illegal antiparticles
	if( istran < 0 ) {
	    for( i=0; i<10; ++i ) {
	        if( istran == noant[i] ) { istran = 0; }
	    }
        }
    } else if(i1 != 0 && i2 != 0 && i3 == 0) {
    // ...mesons
          //   u and d have opposite definitions - sometimes
          if(i2 <= 2 && i1 <= 2){
              //     don't change
          } else if(i2 <= 2) {
              i2=itabi[i2-1];
	  } else if(i1 <= 2) {
              i1=itabi[i1-1];
          }
          istran=i1*100 + i2*10 + 2*js+1 + i4*10000;
          if( id < 0 ) { istran = -istran; }
          //  charmed and top mesons have wrong sign
          if(i1 == 4 && i2 != 4) { istran = -istran; }
          if(i1 == 6 && i2 != 6 && i2 != 4) { istran = -istran; }
          //  special cases
	  if(id == 112) { istran = 225; }
	  if(id == 10110) { istran = 9010221; }
	  if(id == 10111) { istran = 20113; }
	  if(id == 10121) { istran = 20213; }
	  if(id == -10121) { istran = -20213; }
	  if(id == 30231) { istran = 100313; }
	  if(id == -30231) { istran = -100313; }
	  if(id == 30131) { istran = 100323; }
	  if(id == -30131) { istran = -100323; }
	  if(id == 10441) { istran = 100443; }
	  if(id == 20440) { istran = 10441; }
	  if(id == 20442) { istran = 445; }
          // ...check for illegal antiparticles
          if(i2 == i1 && id < 0) { istran=0; }
    } else if(i2 != 0 && i3 != 0 && i1 == 0) {
    // ...diquarks
          // ...         u and d have opposite definitions
          if(i3 <= 2) i3=itabi[i3-1];
          if(i2 <= 2) i2=itabi[i2-1];
          if(i2 < i3){
            istran=i3*1000 + i2*100 + 1;
          } else if(i2 == i3){
            istran=i2*1000 + i3*100 + 3;
          } else {
            istran=i2*1000 + i3*100 + 1;
          }
          if( id < 0 ) { istran = -istran; }
          // ...         charmed and top quarks have wrong sign
          if(i2 == 4 && i3 != 4) { istran=-istran; }
          if(i2 == 6 && i3 != 6 && i3 != 4) { istran=-istran; }
    } else if( i1 != 0 && i3 != 0 && i2 != 0 ) {
    // ...baryons
          //   u and d have opposite definitions
          if(i3 <= 2) i3=itabi[i3-1];
          if(i2 <= 2) i2=itabi[i2-1];
          if(i1 <= 2) i1=itabi[i1-1];
          if(i1 <= 2){
            istran=i3*1000 + i2*100 + i1*10 + 2*js+2;
          } else if(i3 <= 2 && i2 <= 2){
            istran=i1*1000 + i3*100 + i2*10 + 2*js+2;
          } else {
            istran=i1*1000 + i2*100 + i3*10 + 2*js+2;
          }
          if( id < 0 ) { istran = -istran; }
    }
    return istran;
}

}	// HepPDT
