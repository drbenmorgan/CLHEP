//////////////////////////////////////////////////////////////////////////
// Matt.Dobbs@Cern.CH, December 1999
// November 2000, updated to use Pythia 6.1
// March 2002, updated for CLHEP (L. Garren)
// example of generating events with Pythia
// using PythiaWrapper.h 
// Events are read into the HepMC event record from the FORTRAN HEPEVT 
// common block using ConvertHEPEVT and then output to file in
// ascii format using the IO_Ascii strategy.
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/defs.h"
#include <iostream>
#include "CLHEP/HepMC/include/PythiaWrapper.h"
#include "CLHEP/HepMC/ConvertHEPEVT.h"
#include "IO_Ascii.h"
#include "CLHEP/HepMC/GenEvent.h"
    
int main() { 
    //
    //........................................HEPEVT
    // Pythia 6.1 uses HEPEVT with 4000 entries and 8-byte floating point
    //  numbers. 
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

    //........................................HepMC INITIALIZATIONS
    //
    // Instantiate the HEPEVT conversion class.
    HepMC::ConvertHEPEVT conv;
    //
    // Instantial an IO strategy to write the data to file 
    HepMC::IO_Ascii ascii_io("example_MyPythia.dat",HepIOS::out);
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
	// write the event out to the ascii file
	ascii_io << evt;
	// we also need to delete the created event from memory
	delete evt;
    }
    //........................................TERMINATION
    // write out some information from Pythia to the screen
    call_pystat( 1 );    

    return 0;
}


 
