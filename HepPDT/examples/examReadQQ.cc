// $Id: examReadQQ.cc,v 1.2 2003/08/26 21:56:39 garren Exp $
// ----------------------------------------------------------------------
// examReadQQ.cc
//
// read QQ table and write it out
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/defs.h"
#include <fstream>

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/QQDecayTable.hh"
#include "CLHEP/HepPDT/PDGtoQQTable.hh"
#include "CLHEP/HepPDT/TableBuilder.hh"
#include "CLHEP/HepPDT/ParticleDataTableT.hh"

#ifdef __osf__
// kludge so linker can find HepPDT::DMFactory<DefaultConfig>::_inst
template class HepPDT::DMFactory<DefaultConfig>;
#endif

int main()
{
    const char infile[] = "data/decay.dec";
    const char outfile[] = "examReadQQ.out";
    // open input file
    std::ifstream pdfile( infile );
    if( !pdfile ) { 
      std::cerr << "cannot open " << infile << std::endl;
      exit(-1);
    }
    // read decay.dec 
    HepPDT::QQDecayTable qdt( pdfile );
    // create the translation table
    HepPDT::PDGtoQQTable::instance()->buildTable( qdt );
    // construct empty PDT
    DefaultConfig::ParticleDataTable datacol( "QQ Table" );
    {
        // Construct table builder
        HepPDT::TableBuilder  tb(datacol);
	// read the input - put as many here as you want
        if( !addQQParticles( qdt, tb ) ) 
	     { std::cout << "error reading QQ table file " << std::endl; }
    }	// the tb destructor fills the PDT
    std::ofstream wpdfile( outfile );
    if( !wpdfile ) { 
      std::cerr << "cannot open " << outfile << std::endl;
      exit(-1);
    }
    // write the tranlations
    HepPDT::PDGtoQQTable::instance()->writeTranslations( wpdfile );
    // write the particle and decay info
    datacol.writeParticleData( wpdfile );
}
