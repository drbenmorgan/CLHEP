//////////////////////////////////////////////////////////////////////////
// Matt.Dobbs@Cern.CH, December 1999
// November 2000, updated to use Pythia 6.1
// example of generating events with Pythia
// using PythiaWrapper.h 
// Events are read into the HepMC event record from the FORTRAN HEPEVT 
// common block using the IO_HEPEVT strategy and then a very simple event
// selection is performed.
//////////////////////////////////////////////////////////////////////////
// To Compile: go to the HepMC directory and type:
// gmake examples/example_MyPythiaWithEventSelection.exe
//
// See comments in examples/example_MyPythia.cxx regarding the HEPEVT wrapper.
//

#include "CLHEP/HepMC/defs.h"
#include <iostream>
#include "CLHEP/HepMC/include/PythiaWrapper.h"
#include "CLHEP/HepMC/ConvertHEPEVT.h"
#include "CLHEP/HepMC/GenEvent.h"

class IsGoodEvent {
    // event selection predicate. returns true if the event contains
    // a photon with pT > 25 GeV
public:
    bool operator()( const HepMC::GenEvent* evt ) { 
	for ( HepMC::GenEvent::particle_const_iterator p 
		  = evt->particles_begin(); p != evt->particles_end(); ++p ){
	    if ( (*p)->pdg_id() == 22 && (*p)->momentum().perp() > 25. ) {
		//std::cout << "Event " << evt->event_number()
		//     << " is a good event." << std::endl;
		//(*p)->print();
		return 1;
	    }
	}
	return 0;
    }
};
    
int main() { 
    //
    //........................................HEPEVT
    // Pythia 6.1 uses HEPEVT with 4000 entries and 8-byte floating point
    //  numbers. We need to explicitly pass this information to the 
    //  HEPEVT_Wrapper.
    //
    //HepMC::HEPEVT_Wrapper::set_max_number_entries(4000);
    //HepMC::HEPEVT_Wrapper::set_sizeof_real(8);
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
    //
    //........................................HepMC INITIALIZATIONS
    // Instantiate the HEPEVT conversion class.
    HepMC::ConvertHEPEVT conv;
    // declare an instance of the event selection predicate
    IsGoodEvent is_good_event;
    //........................................EVENT LOOP
    int icount=0;
    int num_good_events=0;
    for ( int i = 1; i <= 100; i++ ) {
	icount++;
	if ( i%50==1 ) std::cout << "Processing Event Number " 
				 << i << std::endl;
	call_pyevnt(); // generate one event with Pythia
	// pythia pyhepc routine convert common PYJETS in common HEPEVT
	call_pyhepc( 1 );
	HepMC::GenEvent* evt = conv.getGenEventfromHEPEVT();
	// do event selection
	if ( is_good_event(evt) ) ++num_good_events;
	// we also need to delete the created event from memory
	delete evt;
    }
    //........................................TERMINATION
    // write out some information from Pythia to the screen
    call_pystat( 1 );    
    //........................................PRINT RESULTS
    std::cout << num_good_events << " out of " << icount 
	      << " processed events passed the cuts. Finished." << std::endl;
    return 0;
}


 