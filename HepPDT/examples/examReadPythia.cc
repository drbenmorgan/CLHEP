// $Id: examReadPythia.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
// examReadPythia.cc
//
// read Pythia table and write it out
//
// ----------------------------------------------------------------------

#include "CLHEP/config/CLHEP.h"
#include "CLHEP/config/fstream.h"

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
}
