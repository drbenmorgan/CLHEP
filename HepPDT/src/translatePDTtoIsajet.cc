// $Id: translatePDTtoIsajet.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// translatePDTtoIsajet.cc
//
// translate an ID number from the standard numbering scheme to Isajet
//
// ----------------------------------------------------------------------

#include <iostream>

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int translatePDTtoIsajet( const int id )
{
// ... itabi(I) converts miscellaneous ISAJET particle ID's to a standard scheme
    static int itabi[100]={2,1,3,4,5,6,7,8,0,0,
                12,11,14,13,16,15,0,0,0,0,
                9,10,90,80,81,0,0,0,0,0,
                0,0,0,0,83,84,86,0,92,0,
                0,0,0,0,0,0,0,0,0,0,
                82,88,87,89,85,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0};
    static int noant[11]={-21,-22,-23,-25,-32,-33,-35,-36,-51,-55,-56};
    int i;

    int istran=0;
    ParticleID pid(id);
    int ida=pid.abspid();
    int j1=ida%10;
    int i1=(ida/10)%10;
    int i2=(ida/100)%10;
    int i3=(ida/1000)%10;
    int i4=(ida/10000)%10;
    int ksusy = (ida/1000000)%10;
    int kqn=pid.extraBits();

    if(ida == 0){
        std::cout << " ISTRAN: particle ID is zero" << std::endl;
    } else if(kqn > 0 ) {
    // ... ion
        std::cout << " ISTRAN 2: ion is not allowed" << std::endl;
    } else if(ksusy == 1 || ksusy == 2) {
    // ...SUSY 
	if(ida == 1000001) { istran = 22; }
	if(ida == 1000002) { istran = 21; }
	if(ida == 1000003) { istran = 23; }
	if(ida == 1000004) { istran = 24; }
	if(ida == 1000005) { istran = 25; }
	if(ida == 1000006) { istran = 26; }
	if(ida == 1000011) { istran = 32; }
	if(ida == 1000012) { istran = 31; }
	if(ida == 1000013) { istran = 34; }
	if(ida == 1000014) { istran = 33; }
	if(ida == 1000015) { istran = 36; }
	if(ida == 1000016) { istran = 35; }
	if(ida == 2000001) { istran = 42; }
	if(ida == 2000002) { istran = 41; }
	if(ida == 2000003) { istran = 43; }
	if(ida == 2000004) { istran = 44; }
	if(ida == 2000005) { istran = 45; }
	if(ida == 2000006) { istran = 46; }
	if(ida == 2000011) { istran = 52; }
	if(ida == 2000012) { istran = 51; }
	if(ida == 2000013) { istran = 54; }
	if(ida == 2000014) { istran = 53; }
	if(ida == 2000015) { istran = 56; }
	if(ida == 2000016) { istran = 55; }
	if(ida == 1000021) { istran = 29; }
	if(ida == 1000022) { istran = 30; }
	if(ida == 1000023) { istran = 40; }
	if(ida == 1000025) { istran = 50; }
	if(ida == 1000035) { istran = 60; }
	if(ida == 1000024) { istran = 39; }
	if(ida == 1000037) { istran = 49; }
	if(ida == 1000039) { istran = 91; }
        if(id < 0){
	  istran = -istran;
          // ...check for illegal antiparticles
	  int irt = pid.fundamentalID();
	  for( i=0; i<11; ++i ){
            if(irt == noant[i]) { istran=0; }
          }
        }
    } else if(ksusy > 2 ) {
    // no translation for these
    } else if(ida <= 100){
    // ...elementary particles
        istran=itabi[ida];
        if(id < 0){
	  istran = -istran;
          // ...check for illegal antiparticles
	  for( i=0; i<11; ++i ){
            if(id == noant[i]) { istran=0; }
          }
        }
    } else if(id == 130){
    // ...K short and K long
        istran=-20;
    } else if(id == 310){
        istran=20;
    } else if(i1 != 0 && i2 != 0 && i3 == 0) {
    // ...mesons
          //   u and d have opposite definitions - sometimes
          if(i2 <= 2 && i1 <= 2){
              //     don't change
          } else if(i2 <= 2) {
              i2=itabi[i2];
	  } else if(i1 <= 2) {
              i1=itabi[i1];
          }
          istran=i1*100 + i2*10 + (j1-1)/2 + i4*10000;
          if( id < 0 ) { istran = -istran; }
          // ...         charmed and top mesons have wrong sign
          if(i2 == 4 && i1 != 4) { istran = -istran; }
          if(i2 == 6 && i1 != 6 && i1 != 4) { istran = -istran; }
          // ...    
	  if(ida == 10221) { istran=0; }
	  if(id == 225) { istran = 112; }
	  if(id == 9010221) { istran = 10110; }
	  if(id == 20113) { istran = 10111; }
	  if(id == 20213) { istran = 10121; }
	  if(id == -20213) { istran = -10121; }
	  if(id == 100313) { istran = 30231; }
	  if(id == 100323) { istran = 30131; }
	  if(id == -100313) { istran = -30231; }
	  if(id == -100323) { istran = -30131; }
	  if(id == 100443) { istran = 10441; }
	  if(id == 10441) { istran = 20440; }
	  if(id == 445) { istran = 20442; }
          // ...check for illegal antiparticles
          if(i2 == i1 && id < 0) { istran=0; }
    } else if(i1 == 0){
    // ...diquarks
          // ...         u and d have opposite definitions
          if(i3 <= 2) i3=itabi[i3];
          if(i2 <= 2) i2=itabi[i2];
          if(i3 < i2){
            istran=i3*1000 + i2*100 + (j1-1)/2;
          } else {
            istran=i2*1000 + i3*100 + (j1-1)/2;
          }
          if( id < 0 ) { istran = -istran; }
          // ...         charmed and top mesons have wrong sign
          if(i2 == 4 && i3 != 4) { istran=-istran; }
          if(i2 == 6 && i3 != 6 && i3 != 4) { istran=-istran; }
    } else if( i1 != 0 && i3 != 0 && i2 != 0 && ( j1 == 2 || j1 == 4)) {
    // ...spin 1/2 or spin 3/2 baryons
          // ...         u and d have opposite definitions
          if(i3 <= 2) { i3=itabi[i3]; }
          if(i2 <= 2) { i2=itabi[i2]; }
          if(i1 <= 2) { i1=itabi[i1]; }
          if(i3 <= 2){
            istran=i3*1000 + i2*100 + i1*10 + (j1-2)/2;
          } else if(i1 <= 2 && i2 <= 2){
            istran=i2*1000 + i1*100 + i3*10 + (j1-2)/2;
          } else {
            istran=i1*1000 + i2*100 + i3*10 + (j1-2)/2;
          }
          if( id < 0 ) { istran = -istran; }
	  // isajet has only spin 
	  if( i4 > 0 ) { istran=0; }
    }

    return istran;
}

}	// HepPDT
