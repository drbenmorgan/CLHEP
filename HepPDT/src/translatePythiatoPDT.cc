// $Id: translatePythiatoPDT.cc,v 1.2 2004/04/14 23:56:28 garren Exp $
// ----------------------------------------------------------------------
//
// translatePythiatoPDT.cc
//
// translate a Pythia ID number to the standard numbering scheme
//
// ----------------------------------------------------------------------

#include <iostream>

#include "CLHEP/HepPDT/ParticleID.hh"

namespace HepPDT {

int translatePythiatoPDT( const int id )
{
     static int itabj[100] = { 1,2,3,4,5,6,7,8,0,0,
              11,12,13,14,15,16,17,18,0,0,
              21,22,23,24,25,0,0,110,990,0,
              0,32,33,34,35,36,37,3000221,42,41,
              0,0,0,0,0,0,0,0,0,0,
              3000111,3000211,3100111,3000113,3000213,3000223,
              0,0,0,0,
              9900041,9900042,9900024,9900012,9900014,9900016,
              0,0,0,0,
              0,0,0,0,0,0,0,0,0,0,
              81,82,83,84,85,86,87,88,89,90,
              91,92,93,94,95,96,97,98,99, 0 };
    static int noant[11] = {-10,-21,-22,-23,-25,-32,-33,-35,-36,-81,-83};
    int i;

    int lutran=id;
    int ida=abs(id);
    int j1=ida%10;
    int i1=(ida/10)%10;
    int i2=(ida/100)%10;
    int i3=(ida/1000)%10;
    int ksusy = (ida/1000000)%10;
    int kqn=(ida/1000000000)%10;

    if(ida == 0) {
	std::cout << "LUTRAN 1: particle ID is zero" << std::endl;
	return 0;
    } else if( kqn > 0 )  {
        // this number is too big
 	std::cout << "LUTRAN 3: illegal number " << id << std::endl;
 	return 0;
    } else if(ksusy == 1 || ksusy == 2)  {
        // SUSY
	return id;
    } else if(ksusy == 3)  {
        // technicolor
	std::cout << "lutran 4: illegal code " << id << std::endl;
	return 0;
    } else if(ksusy == 4)  {
        // excited quarks and leptons
	return id;
    } else if(ksusy == 5)  {
        // other exotics
	std::cout << "lutran 4: illegal code " << id << std::endl;
	return 0;
    } else if(ida <= 100) {
        // quarks, Higgs, etc.
	lutran = itabj[ida-1];
	if( id < 0 ) {
	    if( lutran >= 91 && lutran <= 99 ) { return 0; }
            lutran = -lutran;
	    for( i=0; i < 11; i++ ) {
	        if( lutran == noant[i] ) { return 0; }
	    }
	}
	return lutran;
    } else if( j1 == 0 ) {
        //special particles
        if(id == 110) {
	   return 9910113;
        } else if(id == 210) { 
	   return 9910211;
        } else if(id == -210) { 
	   return -9910211;
        } else if(id == 220) { 
	    return 9910223; 
        } else if(id == 330) { 
	    return 9910333; 
        } else if(id == 440) { 
	    return 9910443; 
        } else if(id == 2110) { 
	    return 9912112; 
        } else if(id == -2110) { 
	    return -9912112; 
        } else if(id == 2210) { 
	    return 9912212;
        } else if(id == -2210) { 
	    return -9912212;
	} else if( id == 130 ) { 
	    return id; 
	} else if( id == 310 ) { 
	    return id; 
	}
	return 0;
    } else if( i1 != 0 && i3 != 0 && ( j1 == 2 || j1 == 4) ) {
        // spin 1/2 and spin 3/2 baryons
	return id;
    } else if(i1 != 0 && i2 != 0 && i3 == 0) {
        // mesons
        if(id == 10111) { 
	    return 9000111; 
        } else if(id == 10211) { 
	    return 9000211; 
        } else if(id == -10211) { 
	    return -9000211; 
        } else if(id == 10221) { 
	    return 9010221; 
        } else if(id == 10331) { 
	    return 10221; 
	}
        // check for illegal antiparticles
        if(i1 == i2 && id < 0) { return 0; }
	return id;
    } else if(i2 != 0 && i3 != 0 && i1 == 0) {
        // diquarks
        if(i2 == i3 && id < 0) { return 0; }
	return id;
    } else {
        // undefined
	return 0;
    }
}

}	// HepPDT
