//////////////////////////////////////////////////////////////////////////
// Matt.Dobbs@Cern.CH, October 2002
// example of generating events with Herwig using HepMC/HerwigWrapper.h 
// Events are read into the HepMC event record from the FORTRAN HEPEVT 
// common block using the ConvertHerwig strategy.
//////////////////////////////////////////////////////////////////////////
// To Compile: go to the HepMC directory and type:
// gmake examples/example_MyHerwig.exe
//
// In this example the precision and number of entries for the HEPEVT 
// fortran common block are explicitly defined to correspond to those 
// used in the Herwig version of the HEPEVT common block. 
// If you get funny output from HEPEVT in your own code, probably you have
// set these values incorrectly!
//

#include <iostream>
#include "CLHEP/HepMC/defs.h"
#include "CLHEP/HepMC/include/HerwigWrapper.h"
#include "CLHEP/HepMC/ConvertHerwig.h"
#include "CLHEP/HepMC/GenEvent.h"

int main() { 
    //
    //.......................................INITIALIZATIONS

    hwproc.PBEAM1 = 7000.; // energy of beam1
    hwproc.PBEAM2 = 7000.; // energy of beam2
    // 1610 = gg->H--> WW, 1706 = qq-->ttbar, 2510 = ttH -> ttWW
    hwproc.IPROC = 1706; // qq -> ttbar production 
    hwproc.MAXEV = 100; // number of events
    // tell it what the beam particles are:
    for ( unsigned int i = 0; i < 8; ++i ) {
        hwbmch.PART1[i] = (i < 1) ? 'P' : ' ';
        hwbmch.PART2[i] = (i < 1) ? 'P' : ' ';
    }
    hwigin();    // INITIALISE OTHER COMMON BLOCKS
    hwevnt.MAXPR = 1; // number of events to print
    hwuinc(); // compute parameter-dependent constants
    hweini(); // initialise elementary process

    //........................................HepMC INITIALIZATIONS
    //
    // Instantiate an IO strategy for reading from HEPEVT.
    HepMC::ConvertHerwig hepevtio;
    //
    //........................................EVENT LOOP
    for ( int i = 1; i <= hwproc.MAXEV; i++ ) {
	if ( i%50==1 ) std::cout << "Processing Event Number " 
				 << i << std::endl;
	// initialise event
	hwuine();
	// generate hard subprocess
	hwepro();
	// generate parton cascades
	hwbgen();
	// do heavy object decays
	hwdhob();
	// do cluster formation
	hwcfor();
	// do cluster decays
	hwcdec();
	// do unstable particle decays
	hwdhad();
	// do heavy flavour hadron decays
	hwdhvy();
	// add soft underlying event if needed
	hwmevt();
	// finish event
	hwufne();
	HepMC::GenEvent* evt = hepevtio.read_next_event();
	// add some information to the event
	evt->set_event_number(i);
	evt->set_signal_process_id(20);
	if (i<=hwevnt.MAXPR) {
	    std::cout << "\n\n This is the FIXED version of HEPEVT as "
		      << "coded in ConvertHerwig " << std::endl;
	    hepevtio.print_hepevt();
	    evt->print();
	}

	// we also need to delete the created event from memory
	delete evt;
    }
    //........................................TERMINATION
    hwefin();

    return 0;
}
