#ifndef TRANSLATIONLIST_HH
#define TRANSLATIONLIST_HH
// $Id: TranslationList.hh,v 1.2 2004/04/29 02:47:31 garren Exp $
// ----------------------------------------------------------------------
//
// TranslationList.hh
// Author:  Lynn Garren
//
// list translations for various MonteCarlo input types
// DO NOT mix these functions with the addXXXParticles functions
// These functions will read a table file and write a translation list
//
//
// ----------------------------------------------------------------------


#include <iostream>

namespace HepPDT {


/**
 * @author
 * @ingroup heppdt
 */

// --- free functions
//

bool  listPDGTranslation    ( std::istream &, std::ostream & );
bool  listPythiaTranslation ( std::istream &, std::ostream & );

}  // namespace HepPDT

#endif // TRANSLATIONLIST_HH
