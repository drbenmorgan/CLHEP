// $Id: translatePDTtoPDGtable.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// translatePDTtoPDGtable.cc
//
// convert from standard numbering scheme to PDG mass table numbering scheme
//  note that the mass table is not quite identical to the official numbering scheme
//
// ----------------------------------------------------------------------

#include <iostream>

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int translatePDTtoPDGtable( const int id )
{
    static int itabj[100]={
                1,2,3,4,5,6,7,8,0,0,
                11,12,13,14,15,16,17,18,0,0,
                21,22,23,24,25,0,0,0,0,0,
                0,32,33,34,35,36,37,0,39,0,
                41,42,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,
                0,0,0,0,0,0,0,0,0,0,
                81,82,83,84,85,86,87,88,89,90,
                91,92,93,94,95,96,97,98,99,100};
    static int noant[8]={-21,-22,-23,-25,-32,-33,-35,-36};
    int i;

    int pdgtran=id;
    int ida=abs(id);
    int j1=ida%10;
    int i1=(ida/10)%10;
    int i2=(ida/100)%10;
    int i3=(ida/1000)%10;
    int ksusy = (ida/1000000)%10;
    int ku = (ida/10000000)%10;
    int kqn=(ida/1000000000)%10;

    if(ida == 0) {
         std::cout << " PDGTRAN 1: particle ID is zero" << std::endl;
    } else if(kqn > 0 ) {
    //   ions not allowed
        pdgtran=0;
        std::cout << " PDGTRAN 3: unallowed ion" << std::endl;
    } else if(ksusy == 1 || ksusy == 2)  {
    //  SUSY 
    } else if(ksusy == 3)  {
    //  technicolor
	   if(ida == 3100111)  { pdgtran = 0; }
    } else if(ksusy == 4)  {
    //  excited quarks and leptons
    } else if(ida <= 100) {
    //  Higgs, etc.
        pdgtran=itabj[ida];
        if(id < 0) {
	    pdgtran = -pdgtran;
            //  check for illegal antiparticles
	    for( i=0; i < 8; i++ ) {
	        if( pdgtran == noant[i] ) { pdgtran = 0; }
	    }
        }
    } else if(j1 == 0) {
    //  special particles
        //  check for illegal anti KS, KL
        if(id == -130 || id == -310) { pdgtran = 0; }
    } else if(ksusy == 9 && ku == 9 )  {
        pdgtran = 0;
    } else if(i1 != 0 && i3 != 0 && j1 == 2) {
    //  spin 1/2 baryons
	  if(i3 >= 6) { pdgtran = 0; }
    } else if(i1 != 0 && i3 != 0 && j1 == 4) {
    //  spin 3/2 baryons
	  if(i3 >= 6) { pdgtran = 0; }
    } else if(i1 != 0 && i2 != 0 && i3 == 0) {
    //  mesons 
	if(id == 20333) { pdgtran = 30223; }
	if(id == 30223) { pdgtran = 60223; }
 	if(id == 30313) { pdgtran = 40313; }
	if(id == 30323) { pdgtran = 40323; }
 	if(id == -30313) { pdgtran = -40313; }
	if(id == -30323) { pdgtran = -40323; }
        if(ida == 9020553) { pdgtran = 0; }
	if(i2 >= 6) { pdgtran = 0; }
        //  check for illegal antiparticles
        if(i1 == i2 && id < 0) { pdgtran = 0; }
    } else if(i2 != 0 && i3 != 0 && i1 == 0) {
    //  diquarks
	if(i3 >= 6) { pdgtran = 0; }
    } else {
    //  undefined
        pdgtran=0;
    }
    //  check for illegal anti KS, KL
    if(id == -130 || id == -310) { pdgtran = 0; }
    return pdgtran;
}

}	// HepPDT
