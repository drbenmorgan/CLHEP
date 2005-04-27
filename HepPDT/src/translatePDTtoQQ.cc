// ----------------------------------------------------------------------
//
// translatePDTtoQQ.cc
// Author: Lynn Garren
//
// translate a Pythia ID number to the standard numbering scheme
//
// ----------------------------------------------------------------------

#include "CLHEP/HepPDT/PDGtoQQTable.hh"

namespace HepPDT {

int translatePDTtoQQ( const int id )
{
    PDGtoQQTable *qqtran = PDGtoQQTable::instance();
    return qqtran->QQnumber( id );
}

}	// HepPDT
