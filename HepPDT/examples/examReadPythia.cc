// $Id: examReadPythia.cc,v 1.2.2.1 2005/03/17 02:05:56 garren Exp $
// ----------------------------------------------------------------------
// examReadPythia.cc
//
// read Pythia table and write it out
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/defs.h"
#include <fstream>

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/TableBuilder.hh"
#include "CLHEP/HepPDT/ParticleDataT.hh"
#include "CLHEP/HepPDT/ParticleDataTableT.hh"

#ifdef __osf__
// kludge so linker can find HepPDT::DMFactory<DefaultConfig>::_inst
template class HepPDT::DMFactory<DefaultConfig>;
#endif

int main()
{
    const char infile[] = "data/pythia.tbl";
    const char outfile[] = "examReadPythia.out";
    // open input file
    std::ifstream pdfile( infile );
    if( !pdfile ) { 
      std::cerr << "cannot open " << infile << std::endl;
      exit(-1);
    }
    // construct empty PDT
    DefaultConfig::ParticleDataTable datacol( "Pythia Table" );
    {
        // Construct table builder
        HepPDT::TableBuilder  tb(datacol);
	// read the input - put as many here as you want
        if( !addPythiaParticles( pdfile, tb ) ) 
	      { std::cout << "error reading pythia file " << std::endl; }
    }	// the tb destructor fills datacol
    std::ofstream wpdfile( outfile );
    if( !wpdfile ) { 
      std::cerr << "cannot open " << outfile << std::endl;
      exit(-1);
    }
    DefaultConfig::ParticleData * pd = datacol.particle( HepPDT::ParticleID(111) );
    //pd->write(wpdfile);
    //datacol.particle( HepPDT::ParticleID(213) )->write(wpdfile);
    double mumass = datacol.particle( HepPDT::ParticleID(13) )->mass();
    datacol.writeParticleData(wpdfile);
    
    return 0;
}
