// $Id: DefTable.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// DefTable.hh
// Author: Lynn Garren
//
// ----------------------------------------------------------------------
#ifndef DEFTABLE_HH
#define DEFTABLE_HH

#include <string>
#include <map>

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class DefTable  {
  typedef  std::map<std::string,double>            TempDefMap;

public:
  typedef  TempDefMap::const_iterator  const_iterator;
  typedef  TempDefMap::iterator        iterator;

  DefTable( );
  ~DefTable()  { ; }

  // --- mutator
  //
  void addDefinition( std::string const & def, double val ) { tempDefines[def] = val; }

  // --- boolean
  //
  bool hasDefinition( std::string const & def ) const;

  // --- accessors
  //
  int             size()  const { return tempDefines.size(); }
  double          definition( std::string const & def );
  void            writeDefinitions() const;	// intended for diagnostic use

  iterator        begin()       { return tempDefines.begin(); }
  const_iterator  begin() const { return tempDefines.begin(); }

  iterator        end()       { return tempDefines.end(); }
  const_iterator  end() const { return tempDefines.end(); }

private:
  TempDefMap           tempDefines;	// hold EvtGen "Define" info

  // forbidden copy:
  DefTable &  operator = ( DefTable const & );
  DefTable( DefTable const & );

};  // DefTable<>

}  // namespace HepPDT

#endif // DEFTABLE_HH
