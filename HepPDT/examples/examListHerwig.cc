// $Id: examListHerwig.cc,v 1.1.4.2 2005/03/15 23:57:31 garren Exp $
// -------------------------------------------------------------------
// 
// List the herwig translation
// This requires access to the herwig library
//
// main program must be in C++
// 
// -------------------------------------------------------------------
 
#include <fstream>
#include <iostream>
 
#include "CLHEP/HepPDT/ParticleName.hh"
#include "CLHEP/HepPDT/ParticleID.hh"

extern "C" {
    void list_herwig_init_ ( int * nevt );
    void list_herwig_end_ ( );
    void get_list_size_ ( int * );
    void get_herwig_name_( int * ihwg, int * id, char *name );
}

int main()
{
    int nevt=20;
    int i, j, iend, isize;
    int hid, id;
    char cname[10];
    std::string hname;
    std::string pn;
    static char outfile[] = "examListHerwig.out";
    std::string title = "HepPDT listing of Herwig translations";

    // initialize herwig 
    list_herwig_init_ ( & nevt );

    // open the output stream
    std::ofstream os( outfile );
    if( !os ) {
        std::cout << "error opening output file"  << std::endl;
        exit(1);
    }

    get_list_size_( & isize );
    os << "      " << title << std::endl;
    os << " number of Herwig particles: " << isize << std::endl;
    
    for( i=1, iend=isize+1; i<iend; ++i ) {
	// get info from herwig
	for( j=0; j<10; ++j) { cname[j] = '\0'; }
	get_herwig_name_( & i, & hid, cname );
	hname = std::string( cname );
	id = HepPDT::translateHerwigtoPDT( hid );
        pn = HepPDT::particleName( id );
 	os << "Herwig: ";
	os.width(7);
	os << i ;
	os.width(12);
	os << hid << " " << hname;
	os << "  HepPDT: " ;
	os.width(12);
	os << id << " " << pn << std::endl;
    }

    list_herwig_end_();
    
    return 0;
}

