// $Id: examListIsajet.cc,v 1.1 2004/04/14 23:56:27 garren Exp $
// -------------------------------------------------------------------
// 
// List the isajet translation
// This requires access to the isajet library
//
// main program must be in C++
// 
// -------------------------------------------------------------------
 
#include <fstream>
#include <iostream>
 
#include "CLHEP/HepPDT/ParticleName.hh"
#include "CLHEP/HepPDT/ParticleID.hh"

extern "C" {
    void list_isajet_init_ ( );
    void get_isajet_name_( int * i, int * id, int * aid, char *name, char *aname );
}

int main()
{
    int i, j;
    int aid, id, hid;
    char cname[10];
    char acname[10];
    std::string hname;
    std::string pn;
    static char outfile[] = "examListIsajet.out";
    std::string title = "HepPDT listing of Isajet translations";

    // initialize isajet 
    list_isajet_init_ ( );

    // open the output stream
    std::ofstream os( outfile );
    if( !os ) {
        std::cout << "error opening output file"  << std::endl;
        exit(1);
    }

    os << "      " << title << std::endl;
    
    for( i=1; i<100001; ++i ) {
	// get info from isajet
	for( j=0; j<10; ++j) { cname[j] = '\0'; }
	for( j=0; j<10; ++j) { acname[j] = '\0'; }
	get_isajet_name_( & i, & id, &aid, cname, acname );
	// particle
	if( id != 0 ) {
	    hname = std::string( cname );
	    hid = HepPDT::translateIsajettoPDT( id );
            pn = HepPDT::particleName( hid );
 	    os << "Isajet: ";
	    os.width(10);
	    os << id << " " << hname;
	    os << "  HepPDT: " ;
	    os.width(12);
	    os << hid << " " << pn << std::endl;
	}
        // antiparticle
	if( aid != 0 ) {
	    hname = std::string( acname );
	    hid = HepPDT::translateIsajettoPDT( aid );
            pn = HepPDT::particleName( hid );
 	    os << "Isajet: ";
	    os.width(10);
	    os << aid << " " << hname;
	    os << "  HepPDT: " ;
	    os.width(12);
	    os << hid << " " << pn << std::endl;
	}
    }

    
    return 0;
}

