#ifndef PARTICLE_ID_TRANSLATIONS_HH
#define PARTICLE_ID_TRANSLATIONS_HH
// ----------------------------------------------------------------------
//
// ParticleIDTranslations.hh
// Author: Lynn Garren
//
// ..convert between various numbering implementations
//
// ----------------------------------------------------------------------

#include <map>

namespace HepPDT {

// translate between generator ID's and standard numbering scheme
int translatePythiatoPDT( const int pythiaID );
int translateQQtoPDT( const int qqID);
int translateGeanttoPDT( const int geantID);
int translatePDGtabletoPDT( const int pdgID);
int translateEvtGentoPDT( const int evtGenID );

int translatePDTtoPythia( const int pid );
int translatePDTtoQQ( const int pid );
int translatePDTtoGeant( const int pid );
int translatePDTtoPDGtable( const int pid );
int translatePDTtoEvtGen( const int pid );

// Herwig translations
typedef  std::map< int, int >  HerwigPDTMap;
typedef  std::map< int, int >  PDTHerwigMap;
HerwigPDTMap const & getHerwigPDTMap();
PDTHerwigMap const & getPDTHerwigMap();
int translateHerwigtoPDT( const int herwigID);
int translatePDTtoHerwig( const int pid );

// Isajet translations
typedef  std::map< int, int >  IsajetPDTMap;
typedef  std::map< int, int >  PDTIsajetMap;
IsajetPDTMap const & getIsajetPDTMap();
PDTIsajetMap const & getPDTIsajetMap();
int translateIsajettoPDT( const int isajetID );
int translatePDTtoIsajet( const int pid );

}  // namespace HepPDT

#endif // PARTICLE_ID_TRANSLATIONS_HH
