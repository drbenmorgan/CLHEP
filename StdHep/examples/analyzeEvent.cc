// ----------------------------------------------------------------------
// analyzeEvent.cc
// ----------------------------------------------------------------------

#include "analyzeEvent.hh"
#include "CLHEP/StdHep/StdEvent.hh"

void analyzeEvent( const StdHep::StdEvent * event )
{
    // look at an event
    // using old methods
    int i, id;
    HepLorentzVector mom, vh;
    HepMC::GenParticle* part;
    HepMC::GenVertex* vtx;
    
    fill1DHist ( 11, (float)event->eventNumber() );
    fill1DHist ( 12, (float)event->numParticles() );
    fill1DHist ( 30, (float)event->numCollisions() );
    // loop over particles without iterators
    for ( i = 0; i < event->numParticles(); ++i ) {
        part = event->particle( i );
        if( part ) {
	    id = part->ParticleID(); 
	    mom = part->Momentum();
	    vh = part->CreationVertex();
	    fill1DHist ( 13, (float)id );
	    fill1DHist ( 14, (float)part->StatusCode() );
	    fill1DHist ( 15, (float)part->Mother() );
	    fill1DHist ( 16, (float)part->SecondMother() );
	    fill1DHist ( 17, (float)part->BeginDaughters() );
	    fill1DHist ( 18, (float)part->EndDaughters() );
	    fill1DHist ( 21, (float)mom.px() );
	    fill1DHist ( 22, (float)mom.py() );
	    fill1DHist ( 23, (float)mom.pz() );
	    fill1DHist ( 24, (float)mom.e() );
	    fill1DHist ( 25, (float)part->generatedMass() );
	    fill1DHist ( 26, (float)vh.x() );
	    fill1DHist ( 27, (float)vh.y() );
	    fill1DHist ( 28, (float)vh.z() );
	    fill1DHist ( 29, (float)vh.t() );
	} else {
            std::cout << "cannot find particle " << i << std::endl;
	}
    }
    // loop over vertices without iterators
    for ( i = 1; i <= event->numVertices(); ++i ) {
        vtx = event->vertex( i );
        if( vtx ) {
	    fill1DHist ( 31, (float)vtx->position().x() );
	    fill1DHist ( 32, (float)vtx->position().y() );
	    fill1DHist ( 33, (float)vtx->position().z() );
	    fill1DHist ( 34, (float)vtx->position().t() );
	} else {
            std::cout << "cannot find vertex " << i << std::endl;
	}
    }
}

void fill1DHist ( int ih, float x )
{
    float y=0., wt=1.;
    hfill_ ( & ih, & x, & y, & wt );
}
