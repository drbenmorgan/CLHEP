// $Id: PDGtoQQTable.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ---------------------------------------------------L-------------------
//
// PDGtoQQTable.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include <iostream>
#include <string>

#include "CLHEP/HepPDT/PDGtoQQTable.hh"
#include "CLHEP/HepPDT/pretend.hh"

namespace HepPDT {

PDGtoQQTable* PDGtoQQTable::instance(  )
{
  static Cleaner sentry;
  pretend_to_use( sentry );
  if ( ! _inst ) _inst = new PDGtoQQTable;
  assert ( _inst != 0 );
  return _inst;
}

void PDGtoQQTable::destroy_and_clear()
{
  if ( _inst )
    {
      delete _inst;
      _inst = 0;
    }
}

PDGtoQQTable* PDGtoQQTable::_inst = 0;

PDGtoQQTable::~PDGtoQQTable()
{
  itsPDTtoQQmap.clear();
  itsQQtoPDTarray.clear(); 
}

void PDGtoQQTable::addPDTDefinition( int const & def, int val ) 
{
    PDTtoQQMap::iterator it = itsPDTtoQQmap.find( def );
    if( it != itsPDTtoQQmap.end() ) {
        // override existing value
	it->second = val;
    } else {
        // new map entry
        itsPDTtoQQmap[def] = val; 
    }
}

void PDGtoQQTable::addQQDefinition( int const & def, int val )  
{
  int i = def+13;
  if( i < QQTOPDTARRAYSIZE ) {
      itsQQtoPDTarray[i] = val;
  } else {
      std::cout << "PDGtoQQTable::addQQDefinition: index " << def 
                << " exceeds array bounds" << std::endl;
  }
}

int PDGtoQQTable::QQnumber( int const & def ) const
{
    PDTtoQQMap::const_iterator cit = itsPDTtoQQmap.find( def );
    if( cit != itsPDTtoQQmap.end() ) {
	return cit->second;
    } else {
        // can neither build nor return a proper map entry
	std::cout << "HepPDT::PDGtoQQTable.QQnumber: There is no entry for " 
                       << def << std::endl;
        return 0;
    }
}

int PDGtoQQTable::PDTnumber( int const & def ) const
{
  int i = def+13;
  if( i < QQTOPDTARRAYSIZE ) {
      return itsQQtoPDTarray[i]; 
  } else {
      std::cout << "PDGtoQQTable::QQnumber: index " << def 
                << " exceeds array bounds" << std::endl;
      return 0; 
  }
}

bool PDGtoQQTable::hasDefinition( int const & def ) const
{
    PDTtoQQMap::const_iterator it = itsPDTtoQQmap.find( def );
    if( it != itsPDTtoQQmap.end() ) {
	return true;
    } else {
        return false;
    }
}

}  // namespace HepPDT
