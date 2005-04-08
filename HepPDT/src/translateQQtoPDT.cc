// ----------------------------------------------------------------------
//
// translateQQtoPDT.cc
// Author: Lynn Garren
//
// translate a Pythia ID number to the standard numbering scheme
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/PDGtoQQTable.hh"

namespace HepPDT {

int translateQQtoPDT( const int id )
{
    PDGtoQQTable *qqtran = PDGtoQQTable::instance();
    return qqtran->PDTnumber( id );
}

}	// HepPDT
