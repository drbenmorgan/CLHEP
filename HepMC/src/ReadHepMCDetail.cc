// $Id: ReadHepMCDetail.cc,v 1.2.2.1 2005/03/03 23:25:58 garren Exp $
// ----------------------------------------------------------------------
//
// ReadHepMCDetail.cc
// Author: Lynn Garren
//
// internal methods needed to read from an ascii file
// don't use implicit namespace, since this seems to confuse old compilers
// ----------------------------------------------------------------------

#include "CLHEP/HepMC/defs.h"
#include <iostream>
#include <string>
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include <vector>
#include <map>

#include "CLHEP/HepMC/ReadHepMC.h"
#include "CLHEP/HepMC/GenEvent.h"
#include "CLHEP/HepMC/GenParticle.h"

std::istream & HepMC::Detail::fillEvent( std::istream & is, 
                                  std::string & evline, 
				  HepMC::GenEvent * evt )
{
    int signalVertex, numVertices;
    HepMC::Detail::parseEventLine( evline, evt,  numVertices, signalVertex );
    //
    // save particles in a map so we can assign decay(end) vertices later
    //
    std::map<HepMC::GenParticle*,int> vertexMap;
    //
    // read in the vertices
    std::string newline;
    int numOrphan, numP, decayVertex;
    int iorph, ip;
    int iv=0;
    while( is && iv < numVertices ) {
        std::getline( is, newline);
	if( newline.find("V ") == 0 ) {
           HepMC::GenVertex * v = new HepMC::GenVertex( );
	   ++iv;
	   HepMC::Detail::parseVertexLine( newline, v, numOrphan, numP );
	   // get orphan particles
	   iorph = 0;
           while( is && iorph < numOrphan ) {
               std::getline( is, newline);
	       if( newline.find("P ") == 0 ) {
	           ++iorph;
		   HepMC::GenParticle * p = new HepMC::GenParticle(CLHEP::HepLorentzVector(0,0,0,0),0);
		   HepMC::Detail::parseParticleLine( newline, p, decayVertex );
		   // just add this to the map
                   if ( decayVertex != 0 ) vertexMap[p] = decayVertex;
	       } else {
		   std::cout << "ReadHepMC:fillEvent logic fails for line " << std::endl;
		   std::cout << newline << std::endl;
	           std::cout << "ReadHepMC:fillEvent stop reading orphan particles" << std::endl;
		   iorph = numOrphan;
	       }
	   }
	   // get the remaining particles
	   ip = 0;
           while( is && ip < numP ) {
               std::getline( is, newline);
	       if( newline.find("P ") == 0 ) {
	           ++ip;
		   HepMC::GenParticle * p = new HepMC::GenParticle(CLHEP::HepLorentzVector(0,0,0,0),0);
		   HepMC::Detail::parseParticleLine( newline, p, decayVertex );
		   // add to the map
                   if ( decayVertex != 0 ) vertexMap[p] = decayVertex;
		   // add to vertex
		   v->add_particle_out( p );
	       } else {
		   std::cout << "ReadHepMC:fillEvent logic fails for line " << std::endl;
		   std::cout << newline << std::endl;
	           std::cout << "ReadHepMC:fillEvent stop reading particles" << std::endl;
		   ip = numP;
	       }
	   }
	   // done - add vertex to event
	   evt->add_vertex( v );
	} else {
	   std::cout << "ReadHepMC:fillEvent logic fails for line " << std::endl;
	   std::cout << newline << std::endl;
	   std::cout << "ReadHepMC:fillEvent stop reading vertices" << std::endl;
	   iv = numVertices;
	}
    }
    // set the signal process vertex
    if ( signalVertex ) {
	evt->set_signal_process_vertex( evt->barcode_to_vertex(signalVertex) );
    }
    //
    // last connect particles to their end vertices
    for ( std::map<HepMC::GenParticle*,int>::iterator pmap = vertexMap.begin(); 
	        pmap != vertexMap.end(); ++pmap ) {
	HepMC::GenVertex* itsDecayVtx = evt->barcode_to_vertex(pmap->second);
	if ( itsDecayVtx ) itsDecayVtx->add_particle_in( pmap->first );
	else {
	    std::cerr << "ReadHepMC:fillEvent ERROR particle points"
		      << " to null end vertex. " << std::endl;
	}
    }
    return is;
}

void  HepMC::Detail::parseEventLine( std::string & evline, 
                             HepMC::GenEvent * evt, 
			     int & numVert, int & signalVertex )
{
    std::string key;
    std::istringstream evstr( evline.c_str() );
    numVert=0;
    signalVertex=0;
    int evnum=0, signalID=0, numRan=0, numW=0;
    double escale=0, qcd=0, qed=0;
    std::vector<unsigned long> ranState;
    evstr >> key 
	  >> evnum
	  >> escale
	  >> qcd
	  >> qed
	  >> signalID
	  >> signalVertex
	  >> numVert
	  >> numRan;
    for( int ir=0; ir < numRan; ++ir ) {
        evstr >> ranState[ir];
    }
    evstr >>  numW;
    HepMC::WeightContainer wgt(numW);
    for( int iw=0; iw < numW; ++iw ) {
        evstr >> wgt[iw];
    }
    evt->set_event_number(evnum);
    evt->set_event_scale(escale);
    evt->set_alphaQCD(qcd);
    evt->set_alphaQED(qed);
    evt->set_signal_process_id(signalID);
    evt->set_random_states(ranState);
    evt->weights() = wgt;
    return;
}

void  HepMC::Detail::parseVertexLine( std::string & evline, 
                               HepMC::GenVertex * v,
			       int & numOrphan, int & numP )
{
    std::string key;
    std::istringstream vstr( evline.c_str() );
    numOrphan=0;
    numP=0;
    int bar=0, id=0, numW=0;
    double vx=0, vy=0, vz=0, vt=0;
    vstr >> key
	 >> bar
	 >> id
	 >> vx
	 >> vy
	 >> vz
	 >> vt
	 >> numOrphan
	 >> numP
	 >> numW;
    HepMC::WeightContainer wgt(numW);
    for( int iw=0; iw < numW; ++iw ) {
        vstr >> wgt[iw];
    }
    // set properties
    v->set_id( id );
    v->set_position( CLHEP::HepLorentzVector( vx, vy, vz, vt ) );
    v->weights() = wgt;
    v->suggest_barcode( bar );
}

void  HepMC::Detail::parseParticleLine( std::string & evline,
                                 HepMC::GenParticle * p,
				 int & dv )
{
    std::string key;
    std::istringstream pstr( evline.c_str() );
    dv=0;
    int bar=0, pid=0, stat=0, fsize=0;
    double px=0, py=0, pz=0, pE=0, theta=0, phi=0, mass=0;
    pstr >> key
	 >> bar
	 >> pid
	 >> px
	 >> py
	 >> pz
	 >> pE
	 >> mass
	 >> stat
	 >> theta
	 >> phi
	 >> dv
	 >> fsize;
    // read flow
    HepMC::Flow flow;
    int indx, code;
    for ( int ifl = 1; ifl <= fsize; ++ifl ) {
	pstr >> indx >> code;
	flow.set_icode( indx,code);
    }
    // set particle properties
    p->set_momentum( CLHEP::HepLorentzVector( px, py, pz, pE ) );
    p->set_pdg_id( pid );
    p->set_status( stat );
    p->setGeneratedMass( mass );
    p->set_flow( flow );
    p->set_polarization( Polarization( theta, phi ) );
    p->suggest_barcode( bar );
}
