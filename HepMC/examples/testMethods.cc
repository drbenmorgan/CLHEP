//////////////////////////////////////////////////////////////////////////
// 
// testMethods.cc
//
// generate Pythia events and then process them to test various methods
//
//////////////////////////////////////////////////////////////////////////

#include "CLHEP/HepMC/defs.h"
#include <iostream>
#include "CLHEP/HepMC/include/PythiaWrapper.h"
#include "CLHEP/HepMC/ConvertHEPEVT.h"
#include "CLHEP/HepMC/GenEvent.h"

void getDescendants( const HepMC::GenEvent* evt );
  
int main() { 
    //
    //........................................PYTHIA INITIALIZATIONS
    // (Some platforms may require the initialization of pythia PYDATA block 
    //  data as external - if you get pythia initialization errors try 
    //  commenting in/out the below call to initpydata() )
    // initpydata();
    //
    // Select W+gamma process (process number 20) 
    pysubs.msel=0;
    pysubs.msub[20-1] = 1;
    // set random number seed (makes the test reproducible)
    pydatr.mrpy[0]=55122 ;
    // Tell Pythia not to write multiple copies of particles in event record.
    pypars.mstp[128-1] = 2;
    //
    // Call pythia initialization
    call_pyinit( "CMS", "p", "p", 14000. );

    //........................................HepMC INITIALIZATIONS
    //
    HepMC::ConvertHEPEVT conv;
    //
    //........................................EVENT LOOP
    for ( int i = 1; i <= 100; i++ ) {
	call_pyevnt();      // generate one event with Pythia
	// pythia pyhepc routine converts common PYJETS in common HEPEVT
	call_pyhepc( 1 );
	HepMC::GenEvent* evt = conv.getGenEventfromHEPEVT();
	// add some information to the event
	evt->set_event_number(i);
	evt->set_signal_process_id(20);
	// print the first event
        if( i == 1 || i == 100 ) {
	    evt->print();
	    getDescendants( evt );
	}
	// we also need to delete the created event from memory
	delete evt;
    }
    //........................................TERMINATION
    // write out some information from Pythia to the screen
    call_pystat( 1 );    

    return 0;
}

void getDescendants( const HepMC::GenEvent* evt )
{
    //std::cout << "analyzing event " << evt->event_number() << std::endl;
    HepMC::GenEvent::particle_const_iterator wp;
    for ( HepMC::GenEvent::particle_const_iterator p = evt->particles_begin();
	  p != evt->particles_end(); ++p ) {
	if ( abs((*p)->pdg_id()) == 24 ) {
	    wp = p;
	    //std::cout << "event " << evt->event_number() 
	    //          << " has W boson " << (*p)->pdg_id() 
		//      << " at " << (*p)->barcode() << std::endl;
	}
    }
    // hum -- what if no W??
    // look at the last W found
    std::cout << "event " << evt->event_number() 
	      << " has W boson " << (*wp)->pdg_id() 
	      << " at " << (*wp)->barcode() << std::endl;
    std::cout << "W boson has " << (*wp)->numParents() 
              << " parents and " << (*wp)->numChildren() << " children" << std::endl;
    // list parents
    std::vector<HepMC::GenParticle*> par = (*wp)->listParents();
    for( unsigned int ip = 0; ip < par.size(); ++ip ) {
        std::cout << "    parent " << ip << " is " << par[ip]->pdg_id() 
	          << " at " << par[ip]->barcode() << std::endl;
    }
    // list ancestors
    std::vector<HepMC::GenParticle*> an = (*wp)->listParents();
    for( unsigned int ia = 0; ia < an.size(); ++ia ) {
        std::cout << "     ancestor " << ia << " is " << an[ia]->pdg_id() 
	          << " at " << an[ia]->barcode() << std::endl;
    }
    // list children
    std::vector<HepMC::GenParticle*> c = (*wp)->listChildren();
    for( unsigned int ic = 0; ic < c.size(); ++ic ) {
        std::cout << "    child " << ic << " is " << c[ic]->pdg_id() 
	          << " at " << c[ic]->barcode() << std::endl;
    }
    // list descendants
    std::vector<HepMC::GenParticle*> d = (*wp)->listDescendants();
    for( unsigned int id = 0; id < d.size(); ++id ) {
        std::cout << "    descendant " << id << " is " << d[id]->pdg_id() 
	          << " at " << d[id]->barcode() << std::endl;
    }
}

 
