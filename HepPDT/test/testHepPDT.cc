// $Id: testHepPDT.cc,v 1.3.4.2 2005/03/18 22:26:45 garren Exp $
// ----------------------------------------------------------------------
// testHepPDT.cc
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
    DefaultConfig::ParticleData * pd;
    pd=datacol.particle(HepPDT::ParticleID(111));
    if(pd) pd->write(wpdfile);
    pd=datacol.particle(HepPDT::ParticleID(-111));
    if(pd) pd->write(wpdfile);
    pd=datacol.particle(HepPDT::ParticleID(211));
    if(pd) pd->write(wpdfile);
    pd=datacol.particle(std::string("pi"));
    if(pd) pd->write(wpdfile);
    datacol.writeParticleInfo(wpdfile);

}
