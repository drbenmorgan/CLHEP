// $Id: write.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// write.cc
//
// ----------------------------------------------------------------------

#include <iomanip>

#include "HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include "CLHEP/HepPDT/CommonParticleData.hh"

using namespace std;

namespace HepPDT {

void CommonParticleData::write( std::ostream & ostr ) const
{
    Measurement mass = itsResonance->mass();
    Measurement width = itsResonance->totalWidth();
    Measurement ctau = lifetime();
    int il = itsParticleName.length();
    ostr << itsParticleName ;
    // pad the name
    int pad;
    for( pad = 0; pad < 20 - il; ++pad ) {
        ostr << " " ;
    }
    ostr.width(12);
    ostr <<  itsID.pid();
    ostr.width(8);
    ostr.precision(4);
    ostr << itsCharge;
    ostr.width(5);
    ostr.precision(2);
    ostr << " " << itsColorCharge;
    ostr.width(5);
    ostr << itsSpin.totalSpin() ;
    ostr.width(5);
    ostr << itsSpin.spin() ;
    ostr.width(5);
    ostr << itsSpin.orbAngMom() ;
    ostr.width(12);
    ostr.precision(4);
    ostr.setf(std::ios::scientific, std::ios::floatfield);
    ostr << mass.value() << "+/-" << mass.sigma() ;
    ostr.width(12);
    ostr.precision(4);
    ostr << width.value() << "+/-" << width.sigma() ;
    ostr.width(12);
    ostr.precision(4);
    ostr << ctau.value() << "+/-" << ctau.sigma();
    // return to default settings
    ostr.precision(6);
    ostr.setf(std::ios::fmtflags(0), std::ios::floatfield);
    // end the line
    ostr << std::endl;
}

}	// HepPDT
