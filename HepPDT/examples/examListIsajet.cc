// $Id: examListIsajet.cc,v 1.1.4.3 2005/03/17 02:05:56 garren Exp $
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
    void flavor_( int *, int *, int *, int *, int *, int * );
    void get_label_( int * id, char *name );
}

int main()
{
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
    
    int i, j;
    int id, aid, fl1, fl2, fl3, js, indx;
    int pid;
    char cname[10];
    char acname[10];
    std::string hname;
    std::string pn;
    for( i=1; i<100005; ++i ) {
	// make sure names are empty
	for( j=0; j<10; ++j) { cname[j] = '\0'; }
	for( j=0; j<10; ++j) { acname[j] = '\0'; }
	// get info from isajet
	id = i;
	aid = 0;
	flavor_(&id, &fl1, &fl2, &fl3, &js, &indx );
	// we need both a valid index and a valid label
	// check the label only if there is a valid translation
	if ( indx > 0 ) {
	   get_label_(&id,cname);
	   aid = -id;
	   get_label_(&aid,acname);
	} else {
	   id = aid = 0;
	}
	
	// print particle
	if( id != 0 ) {
	    pid = HepPDT::translateIsajettoPDT( id );
	    hname = std::string( cname );
	    if ( pid != 0 ) {
        	pn = HepPDT::particleName( pid );
 		os << "Isajet: ";
		os.width(10);
		os << id << " " << hname;
		os << "  HepPDT: " ;
		os.width(12);
		os << pid << " " << pn << std::endl;
	    } else if ( strncmp( cname, "ERR", 3 ) != 0 ) {
 		os << "Isajet: ";
		os.width(10);
		os << id << " with name \"" << hname;
		os << "\" has no HepPDT translation " << std::endl;
	    }
	}
        // print antiparticle
	if( aid != 0 ) {
	    hname = std::string( acname );
	    pid = HepPDT::translateIsajettoPDT( aid );
	    if ( pid != 0 ) {
        	pn = HepPDT::particleName( pid );
 		os << "Isajet: ";
		os.width(10);
		os << aid << " " << hname;
		os << "  HepPDT: " ;
		os.width(12);
		os << pid << " " << pn << std::endl;
	    } else if ( strncmp( acname, "ERR", 3 ) != 0 ) {
 		os << "Isajet: ";
		os.width(10);
		os << aid << " with name \"" << hname;
		os << "\" has no HepPDT translation " << std::endl;
	    }
	}
    }
    
    return 0;
}
