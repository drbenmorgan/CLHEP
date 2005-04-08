// ----------------------------------------------------------------------
//
// readQQchannel.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/QQDecayTable.hh"

namespace HepPDT {

void QQChannel::addHelicity( std::istringstream & thisline )
{
    // normally HELICITY has 3 values, but the documentation allows for more
    QQhelicity hlc;
    int h = 0;
    thisline >> hlc.prob;
    while ( !thisline.eof() ) {
        thisline >> h; 
	hlc.hel.push_back( h );
    }
    itsHelicity.push_back( hlc );
}

void QQChannel::addAngHelicity( std::istringstream & thisline )
{
    QQAngularHelicity hlc;
    thisline >> hlc.hel >> hlc.a0 >> hlc.a1 >> hlc.a2 >> hlc.a3 
             >> hlc.a4 >> hlc.a5 >> hlc.a6 ;
    itsAngularHelicity.push_back( hlc );
}

void QQChannel::parse( std::istringstream & thisline )
{
    std::string dtr = "";
    thisline >> itsMatrixCode >> itsBranchingFraction;
    while ( !thisline.eof() ) {
        thisline >> dtr; 
	itsDaughters.push_back( dtr );
    }
}

}	// HepPDT
