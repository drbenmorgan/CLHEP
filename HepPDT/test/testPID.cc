// $Id: testPID.cc,v 1.3 2003/08/06 19:41:08 garren Exp $
// ----------------------------------------------------------------------
// TestPID.cc
//
// test ParticleID
//
// ----------------------------------------------------------------------

#include <iostream>
#include <iomanip>

#include "HepPDT/defs.h"
#include "CLHEP/HepPDT/ParticleID.hh"

using std::cout;
using std::cerr;
using std::endl;
using std::setw;

int main()
{
    int id[15] = { 5, 25, 15, 213, -3214, 10213, 9050225, -200543, 129050225,
                   2000025, 3101, 3301, 1004002003, -1012006001, 555 };
    int it;
    int nr, nx;
    int chg, sid, extra;
    int js, ls;
    for( it=0; it < 15; it++ ) {
        HepPDT::ParticleID pid( id[it] );
	nx = pid.digit(HepPDT::n);
	nr = pid.digit(HepPDT::nr);
	extra = pid.extraBits();
        cout << endl;
	cout << setw(18) << id[it] << ": " << nx << " " << nr 
	             << " " << pid.digit(HepPDT::nl)
                     << " " << pid.digit(HepPDT::nq1) << " " 
	             << pid.digit(HepPDT::nq2) << " " << pid.digit(HepPDT::nq3)
                     << " " <<  pid.digit(HepPDT::nj)
    	             << " extra bits " << extra << endl;
	js = pid.jSpin();
        HepPDT::Quarks cqks = pid.quarks( );
	ls = pid.lSpin();
	sid = pid.fundamentalID();
	chg = pid.threeCharge();
        if( !pid.isValid() ) {
	   cout << "**** Invalid PID: " << pid.pid() << " ****" << endl;
	} else if( pid.isHadron() ) {
	    if( pid.isMeson() ) {
	       cout << "meson   " << setw(10) << id[it] << ": " << nx
                         << " " << nr << " "  << ls << " " 
	                 << cqks.nq1 << " " << cqks.nq2 << " " << cqks.nq3
                         << " " << js << " " << sid << " " << chg
		         << " extra bits " << extra << endl;
            } else if( pid.isBaryon() ) {
	       cout << "baryon  " << setw(10) << id[it] << ": " << nx
                         << " " << nr << " "  << ls << " " 
	                 << cqks.nq1 << " " << cqks.nq2 << " " << cqks.nq3 
                         << " " << js << " " << sid << " " << chg
		         << " extra bits " << extra << endl;
            } else {
	        cout << "**** undefined hadron: " << pid.pid() 
                          << " ****" << endl;
	    }
	} else if( pid.isLepton() ) {
	   cout << "lepton  " << setw(10) << id[it] << ": " << nx 
                     << " " << nr << " "  << ls << " " 
	             << cqks.nq1 << " " << cqks.nq2 << " " << cqks.nq3
                     << " " << js << " " << sid << " " << chg
		     << " extra bits " << extra << endl;
	} else if( pid.isDiQuark() ) {
	   cout << "diquark " << setw(10) << id[it] << ": " << nx 
                     << " " << nr << " "  << ls << " " 
	             << cqks.nq1 << " " << cqks.nq2 << " " << cqks.nq3 
                     << " " << js << " " << sid << " " << chg
		     << " extra bits " << extra << endl;
	} else if( pid.isNucleus() ) {
	   cout << "ion    " << setw(11) << id[it] 
                     << ": " << pid.digit(HepPDT::n10)
                     << " " << setw(3) << pid.A() 
                     << " " << setw(3) << pid.Z() 
                     << " " << js << " " << sid << " " << chg
		     << " extra bits " << extra << endl;
	} else {
	   cout << "unknown " << setw(10) << id[it] << ": " << nx 
                     << " " << nr << " "  << ls << " " 
	             << cqks.nq1 << " " << cqks.nq2 << " " << cqks.nq3 
                     << " " << js << " " << sid << " " << chg
		     << " extra bits " << extra << endl;
	}
        if( pid.isValid() ) {
	    js = pid.jSpin();
	    chg = pid.threeCharge();
	    cout << "total spin: " << js << " " << HepPDT::spinitod(js) ;
	    cout << " orbital angular momentum: " <<  pid.lSpin() ;
	    cout << " spin: " <<  pid.sSpin() ; 
	    cout << " charge: " << chg << " " << double(chg)/3.0 << endl;
            HepPDT::Quarks qlist = pid.quarks( );
	    cout <<  "quarks: " << qlist.nq1 << " " << qlist.nq2 << " " << qlist.nq3 << endl;
        }
    }
}
