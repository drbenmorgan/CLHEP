// $Id: TableBuilder.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// TableBuilder.hh
// Author: Marc Paterno, Walter Brown
//
// ----------------------------------------------------------------------
// User code:
//    ParticleDataTable pdt;
//    {
//       TableBuilder      tb(pdt);
//       addPythiaParticles( istream1, tb );
//       addPythiaParticles( istream2, tb );
//       tb.addParticle( myTempParticleData );
//       // ...
//    }  // triggers tb's destruction, filling pdt!
// ----------------------------------------------------------------------
#ifndef TABLEBUILDER_HH
#define TABLEBUILDER_HH

#include "CLHEP/HepPDT/DefaultConfig.hh"
#include "CLHEP/HepPDT/TableBuilderT.hh"

namespace HepPDT {

typedef  TableBuilderT<DefaultConfig>  TableBuilder;

}  // namespace HepPDT

#endif // TABLEBUILDER_HH
