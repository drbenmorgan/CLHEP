// $Id: examReadEvtGen.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
// examReadEvtGen.cc
//
// read EvtGen table and write it out
//
// ----------------------------------------------------------------------

#include "CLHEP/config/CLHEP.h"
#include "CLHEP/config/fstream.h"

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/TableBuilder.hh"
#include "CLHEP/HepPDT/ParticleDataTableT.hh"

#ifdef __osf__
// kludge so linker can find HepPDT::DMFactory<DefaultConfig>::_inst
template class HepPDT::DMFactory<DefaultConfig>;
#endif

int main()
{
    const char infile1[] = "data/pdt.table";
    const char infile2[] = "data/DECAY.EvtGen.DEC";
    const char outfile[] = "examReadEvtGen.out";
    // open input files
    std::ifstream pdfile1( infile1 );
    if( !pdfile1 ) { 
      std::cerr << "cannot open " << infile1 << std::endl;
      exit(-1);
    }
    // construct empty PDT
    std::ifstream pdfile2( infile2 );
    if( !pdfile2 ) { 
      std::cerr << "cannot open " << infile2 << std::endl;
      exit(-1);
    }
    DefaultConfig::ParticleDataTable datacol( "EvtGen Table" );
    {
        // Construct table builder
        HepPDT::TableBuilder  tb(datacol);
	// read the input - put as many here as you want
        if( !addEvtGenParticles( pdfile1, tb ) ) { std::cout << "error reading EvtGen pdt file " << std::endl; }
        if( !addEvtGenParticles( pdfile2, tb ) ) { std::cout << "error reading EvtGen decay file " << std::endl; }
    }	// the tb destructor fills datacol
    std::ofstream wfile( outfile );
    if( !wfile ) { 
      std::cerr << "cannot open " << outfile << std::endl;
      exit(-1);
    }
    datacol.writeParticleData(wfile);
}
