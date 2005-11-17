// ----------------------------------------------------------------------
//
// QQChannel.hh
// Author: Lynn Garren
// 
// ----------------------------------------------------------------------
#ifndef QQCHANNEL_HH
#define QQCHANNEL_HH

#include <string>
#include <vector>
#include <sstream>

#include "CLHEP/HepPDT/defs.h"
#include "CLHEP/HepPDT/QQStructs.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
struct QQhelicity {
  // normally HELICITY has 3 values, but the documentation allows for more
  double           prob;
  std::vector<int> hel;
};

/**
 * @author
 * @ingroup heppdt
 */
struct QQAngularHelicity {
  int     hel;
  double  a0;
  double  a1;
  double  a2;
  double  a3;
  double  a4;
  double  a5;
  double  a6;
};

/**
 * @author
 * @ingroup heppdt
 */
struct QQmatrix {
  double  a;
  double  b;
  double  c;
};

/**
 * @author
 * @ingroup heppdt
 */
class QQChannel  {

public:

  typedef std::vector<std::string>       SringVect;
  typedef std::vector<QQhelicity>        HelVect;
  typedef std::vector<QQAngularHelicity> AngHelVect;

  // -- constructors
  QQChannel();
  ~QQChannel();

  // ---  copying:
  //
  void  swap ( QQChannel & rhs );
  QQChannel( const QQChannel & orig );
  QQChannel & operator = ( const QQChannel & rhs );

  // --- mutators
  //
  void addDaughter( std::string nm )           { itsDaughters.push_back( nm ); }
  void addHelicity( QQhelicity hel )           { itsHelicity.push_back( hel ); }
  void addAngHelicity( QQAngularHelicity hel ) { itsAngularHelicity.push_back( hel ); }
  void setMatrixCode( std::string & m )        { itsMatrixCode = m; }
  void setBranchingFraction( double bf )       { itsBranchingFraction = bf; }
  void setSinPhi( double s )                   { itsSinPhi = s; }
  void setMatrix( QQmatrix m )                 { itsMatrix = m; }
  void setCPTag( )                             { itsCPTag = true; }
  void clear();
  void addHelicity( std::istringstream & thisline );
  void addAngHelicity( std::istringstream & thisline );
  void parse( std::istringstream & thisline );

  // --- accessors
  //
  bool              cpt( )               const { return itsCPTag; }
  std::string       matrixCode( )        const { return itsMatrixCode; }
  double            branchingFraction( ) const { return itsBranchingFraction; }
  double            sinPhi( )            const { return itsSinPhi; }
  std::string       daughter( int i )    const { return itsDaughters[i]; }
  QQhelicity        helicity( int i )    const { return itsHelicity[i]; }
  QQAngularHelicity angHelicity( int i ) const { return itsAngularHelicity[i]; }
  int               sizeDtr()            const { return itsDaughters.size(); }
  int               sizeHel()            const { return itsHelicity.size(); }
  int               sizeAngHel()         const { return itsAngularHelicity.size(); }
  
  void write( std::ostream & os ) const;	// intended for diagnostic use


private:

  std::string itsMatrixCode;
  double      itsBranchingFraction;
  double      itsSinPhi;
  QQmatrix    itsMatrix;
  SringVect   itsDaughters;
  HelVect     itsHelicity;
  AngHelVect  itsAngularHelicity;
  bool        itsCPTag;

};  // QQChannel

inline void swap( QQChannel & first, QQChannel & second ) {
  first.swap( second );
}

}  // namespace HepPDT

#endif // QQCHANNEL_HH
