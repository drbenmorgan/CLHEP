// ----------------------------------------------------------------------
// testHepPDT.cc
// Author: Lynn Garren
//
// test by reading the PDG table
// get filename and location of PDG table from input stream
//
// Usage:  testHepPDT 
//
// ----------------------------------------------------------------------

#include <fstream>

#include "CLHEP/HepPDT/defs.h"
#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/TableBuilder.hh"
#include "CLHEP/HepPDT/ParticleDataTableT.hh"

using std::cout;
using std::cerr;
using std::endl;

#ifdef __osf__
// kludge so linker can find HepPDT::DMFactory<DefaultConfig>::_inst 
template class HepPDT::DMFactory<DefaultConfig>;
#endif

int main()
{
    char pdgfile[300] = "";
    const char outfile[] = "testHepPDT.out";
    std::cin >> pdgfile;
    // open input file
    std::ifstream pdfile( pdgfile );
    if( !pdfile ) { 
      cerr << "cannot open " << pdgfile << endl;
      exit(-1);
    }
    // construct empty PDT
    DefaultConfig::ParticleDataTable datacol( "PDG Table" );
    {
        // Construct table builder
        HepPDT::TableBuilder  tb(datacol);
	// read the input - put as many here as you want
	if( !HepPDT::addPDGParticles( pdfile, tb ) ) { cout << "error reading PDG file " << endl; }
    }	// the tb destructor fills datacol
    std::ofstream wpdfile( outfile );
    if( !wpdfile ) { 
      cerr << "cannot open " << outfile << endl;
      exit(-1);
    }
    datacol.writeParticleData(wpdfile);
    wpdfile << std::endl;

    // output some pion information
    DefaultConfig::ParticleData * pd;
    pd=datacol.particle(HepPDT::ParticleID(111));
    if(pd) pd->write(wpdfile);
    //  -111 is an illegal particle, no info will be written
    pd=datacol.particle(HepPDT::ParticleID(-111));
    if(pd) pd->write(wpdfile);
    pd=datacol.particle(HepPDT::ParticleID(211));
    if(pd) pd->write(wpdfile);
    // string lookup
    pd=datacol.particle(std::string("pi0"));
    if(pd) pd->write(wpdfile);
    // particle info
    datacol.writeParticleInfo(wpdfile);
    
    return 0;
}
