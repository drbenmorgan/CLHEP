// $Id: translateQQtoPDT.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// translateQQtoPDT.cc
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
