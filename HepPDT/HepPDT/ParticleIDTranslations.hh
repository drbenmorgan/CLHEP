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

namespace HepPDT {

// translate between generator ID's and standard numbering scheme
int translateQQtoPDT( const int qqID);
int translateGeanttoPDT( const int geantID);
int translateEvtGentoPDT( const int evtGenID );

int translatePDTtoQQ( const int pid );
int translatePDTtoGeant( const int pid );
int translatePDTtoEvtGen( const int pid );

// Herwig translations
int translateHerwigtoPDT( const int herwigID);
int translatePDTtoHerwig( const int pid );

// Isajet translations
int translateIsajettoPDT( const int isajetID );
int translatePDTtoIsajet( const int pid );

// Pythia translations
int translatePythiatoPDT( const int pythiaID );
int translatePDTtoPythia( const int pid );

// PDG table translations
int translatePDGtabletoPDT( const int pdgID);
int translatePDTtoPDGtable( const int pid );

}  // namespace HepPDT

#endif // PARTICLE_ID_TRANSLATIONS_HH
