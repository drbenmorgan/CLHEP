// $Id: QQStructs.hh,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// QQStructs.hh
// Author: Lynn Garren
// 
// ----------------------------------------------------------------------
#ifndef QQSTRUCTS_HH
#define QQSTRUCTS_HH

#include <string>

namespace HepPDT {

// qqbar pairs
// They allow you to specify partial decays.
/**
 * @author
 * @ingroup heppdt
 */
struct QQBAR { 
  std::string name;
  int         qqid;
};

// Mixing information
/**
 * @author
 * @ingroup heppdt
 */
struct MIXING { 
  std::string name;
  std::string antiname;
  double      mix;
};

// The particle
// Note that the rules of decay.dec specify that the PARTICLE must be
// defined before the separate lines specifying PDG ID, parity, C parity,
// and/or hidden particle.
/**
 * @author
 * @ingroup heppdt
 */
struct PARTICLE { 
  std::string name;
  int         qqid;
  int         stableid;
  int         pdgid;
  double      mass;
  double      charge;
  double      spin;
  double      lifetime;
  double      width;
  double      minMass;
  double      maxMass;
  int         parity;
  int         cparity;
  bool        hide;
  MIXING      mixing;
};

}  // namespace HepPDT

#endif // QQSTRUCTS_HH
