// $Id: writeTranslations.cc,v 1.2.4.1 2004/04/21 16:14:51 garren Exp $
// ----------------------------------------------------------------------
//
// writeTranslations.cc
// Author: Lynn Garren
//
// ----------------------------------------------------------------------

#include <iomanip>

#include "CLHEP/HepPDT/defs.h"
#if HAVE_SSTREAM
#include <sstream>
#else
#include "CLHEP/HepPDT/StringStream.h"
#endif
#include "CLHEP/HepPDT/PDGtoQQTable.hh"

// Particle names
#include "CLHEP/HepPDT/ParticleName.hh"

using namespace std;

namespace HepPDT {

void PDGtoQQTable::writeTranslations( std::ostream & os ) const
{
  int i, ipdt, iqq;
  for( i=0; i<QQTOPDTARRAYSIZE; ++i ) {
      ipdt = itsQQtoPDTarray[i];
      const_iterator it = itsPDTtoQQmap.find( ipdt );
      if( it != itsPDTtoQQmap.end() ) {
	  iqq = it->second;
      } else {
          iqq = 0;
      }
      os << " index " ;
      os.width(5);
      os << i << "  PDT number " ;
      os.width(12);
      os << ipdt << "  QQ number " ;
      os.width(5);
      os << iqq << "  PDT name: " ;
      os << particleName( ipdt ) << std::endl;
  }
}

}  // namespace HepPDT
