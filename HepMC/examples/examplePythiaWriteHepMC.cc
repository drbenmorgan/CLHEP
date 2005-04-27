//////////////////////////////////////////////////////////////////////////
// Lynn Garren
//
// example of generating events with Pythia
// using PythiaWrapper.h and WriteHepMC.h
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/defs.h"
#include <iostream>
#include <fstream>

#include "CLHEP/HepMC/include/PythiaWrapper.h"
#include "CLHEP/HepMC/WriteHepMC.h"
#include "CLHEP/HepMC/ConvertHEPEVT.h"
#include "CLHEP/HepMC/GenEvent.h"
// best to include ParticleDataTableConfig after GenEvent
#include "CLHEP/HepMC/ParticleDataTableConfig.h"

int main() { 
    //
    //........................................PYTHIA INITIALIZATIONS
    // (Some platforms may require the initialization of pythia PYDATA block 
    //  data as external - if you get pythia initialization errors try 
    //  commenting in/out the below call to initpydata() )
    // initpydata();
    //
    // Select W+gamma process (process number 20) 
    // (here we have to be careful of C/F77 differences: arrays in C 
    //  start at 0, F77 at 1, so we need to subtract 1 from the process #)
    pysubs.msel=0;
    pysubs.msub[20-1] = 1;
    // set random number seed (mandatory!)
    pydatr.mrpy[0]=55122 ;
    // Tell Pythia not to write multiple copies of particles in event record.
    pypars.mstp[128-1] = 2;
    // Example of setting a Pythia parameter: set the top mass 
    pydat2.pmas[1-1][6-1]= 175;  
    //
    // Call pythia initialization
    call_pyinit( "CMS", "p", "p", 14000. );

    //........................................Particle Data Table
    const char infile[] = "pythia.tbl";
    // open input file
    std::ifstream pdfile( infile );
    if( !pdfile ) { 
      std::cerr << "cannot open " << infile << std::endl;
      exit(-1);
    }
    // construct empty PDT
    HepMCConfig::ParticleDataTable dataTable( "Pythia Table" );
    {
        // Construct table builder
        HepMCConfig::TableBuilder  tb(dataTable);
	// read the input - put as many here as you want
        if( !addPythiaParticles( pdfile, tb ) ) 
	      { std::cout << "error reading pythia table file " << std::endl; }
    }	// the tb destructor fills dataTable
    //........................................HepMC INITIALIZATIONS
    //
    // Instantiate the HEPEVT conversion class.
    HepMC::ConvertHEPEVT conv;
    //
    // open the output stream
    std::ofstream os( "examplePythiaWriteHepMC.dat" );
    // write particle data table
    dataTable.writeParticleData( os );
    // write legend
    HepMC::writeLegend( os );
    //
    //........................................EVENT LOOP
    for ( int i = 1; i <= 100; i++ ) {
	if ( i%50==1 ) std::cout << "Processing Event Number " 
				 << i << std::endl;
	call_pyevnt();      // generate one event with Pythia
	// pythia pyhepc routine converts common PYJETS in common HEPEVT
	call_pyhepc( 1 );
	HepMC::GenEvent* evt = conv.getGenEventfromHEPEVT();
	// add some information to the event
	evt->set_event_number(i);
	evt->set_signal_process_id(20);
	// write the event
	os << evt;
	// we also need to delete the created event from memory
	delete evt;
    }
    //........................................TERMINATION
    // write out some information from Pythia to the screen
    call_pystat( 1 );
    // flush the output stream
    HepMC::flushOutput( os );

    return 0;
}
