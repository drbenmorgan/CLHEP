// $Id: PDGtoQQTable.hh,v 1.2 2003/08/13 20:00:11 garren Exp $
// ----------------------------------------------------------------------
//
// PDGtoQQTable.hh
// Author: Lynn Garren
//
// There should never be more than one translation table, therefore
// this class is a singleton.
// ----------------------------------------------------------------------
#ifndef PDGTOQQTABLE_HH
#define PDGTOQQTABLE_HH

#include <assert.h>
#include <vector>
#include <map>

#include "CLHEP/HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include "CLHEP/HepPDT/QQDecayTable.hh"

#define QQTOPDTARRAYSIZE 520

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class PDGtoQQTable  {
  typedef  std::map<int,int>            PDTtoQQMap;

public:
  typedef  PDTtoQQMap::const_iterator  const_iterator;
  typedef  PDTtoQQMap::iterator        iterator;

  // The singleton instance
  static PDGtoQQTable* instance();

  // --- mutators
  //
  void addPDTDefinition( int const & def, int val );
  void addQQDefinition( int const & def, int val );
  void buildTable( QQDecayTable & qd );

  // --- boolean
  //
  bool hasDefinition( int const & def ) const;

  // --- accessors
  //
  int   QQnumber( int const & def ) const;
  int   PDTnumber( int const & def ) const;
  void  writeTranslations( std::ostream & os ) const;	// intended for diagnostic use

  int             size()  const { return itsPDTtoQQmap.size(); }
  iterator        begin()       { return itsPDTtoQQmap.begin(); }
  const_iterator  begin() const { return itsPDTtoQQmap.begin(); }
  iterator        end()         { return itsPDTtoQQmap.end(); }
  const_iterator  end()   const { return itsPDTtoQQmap.end(); }

private:
  PDTtoQQMap        itsPDTtoQQmap;	// map of PDT numbers to QQ numbers
  std::vector<int>  itsQQtoPDTarray; 	// QQ numbers range from -13 to 498

  // Singleton stuff
  PDGtoQQTable(): itsPDTtoQQmap(), itsQQtoPDTarray(QQTOPDTARRAYSIZE,0) { ; }
  ~PDGtoQQTable();

  PDGtoQQTable(const PDGtoQQTable&);            // not implemented
  PDGtoQQTable& operator=(const PDGtoQQTable&); // not implemented

  static PDGtoQQTable* _inst;
  static void destroy_and_clear();

  struct Cleaner;
  friend struct Cleaner;
  struct Cleaner { ~Cleaner() { PDGtoQQTable::destroy_and_clear(); } };

};  // PDGtoQQTable

}  // namespace HepPDT

#endif // PDGTOQQTABLE_HH
