// $Id: QQDecay.hh,v 1.2 2003/08/13 20:00:11 garren Exp $
// ----------------------------------------------------------------------
//
// QQDecay.hh
// Author: Lynn Garren
//
// This class holds all the information in the QQ decay.dec table
// 
// ----------------------------------------------------------------------
#ifndef QQDECAY_HH
#define QQDECAY_HH

#include <vector>

#include "CLHEP/HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include "CLHEP/HepPDT/QQChannel.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class QQDecay  {

public:

  typedef std::vector<QQChannel>  ChannelList;

  // -- constructors
  QQDecay();
  ~QQDecay();

  // ---  copying:
  //
  void  swap ( QQDecay & rhs );
  QQDecay( const QQDecay & orig );
  QQDecay & operator = ( const QQDecay & rhs );

  // --- mutators
  //
  void addChannel( QQChannel c ) { itsChannels.push_back( c ); }
  void makeStable( ) { itsStable = true; }

  // --- accessors
  //
  bool isStable()  const { return itsStable; };
  QQChannel  channel( int i ) const { return itsChannels[i]; }
  void write( std::ostream & os ) const;	// intended for diagnostic use

  int                          size()  const { return itsChannels.size(); }

private:

  bool itsStable;
  ChannelList itsChannels;

};  // QQDecay

inline void swap( QQDecay & first, QQDecay & second ) {
  first.swap( second );
}

}  // namespace HepPDT

#endif // QQDECAY_HH
