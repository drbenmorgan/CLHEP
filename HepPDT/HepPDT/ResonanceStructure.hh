// ----------------------------------------------------------------------
//
// ResonanceStructure.hh
// Author:  Lynn Garren
//
// ResonanceStructure contains the minimum information for a Breit-Wigner
// distribution about a given mass.
// ----------------------------------------------------------------------
#ifndef RESONANCESTRUCTURE_HH
#define RESONANCESTRUCTURE_HH

#include <algorithm>	// swap()

#include "CLHEP/HepPDT/Measurement.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
class ResonanceStructure  {

public:

  // ---  birth/death:
  //
  ResonanceStructure( Measurement mass = Measurement(),
                      Measurement width = Measurement(),
                      double min = 0., double max = 0. );
  virtual ~ResonanceStructure();

  // ---  copying:
  //
  ResonanceStructure( const ResonanceStructure & orig );
  ResonanceStructure& operator= ( const ResonanceStructure & rhs );
  void swap ( ResonanceStructure & other );

  // ---  accessors:
  //
  Measurement   const & mass()         const { return itsMass; }
  Measurement   const & totalWidth()   const { return itsTotalWidth; }
  Measurement   lifetime();
  double        lowerCutoff()          const { return itsLowerCutoff; }
  double        upperCutoff()          const { return itsUpperCutoff; }

  // ---  mutators:
  //
  void  setMass( Measurement const & mass )        {  itsMass = mass; }
  void  setTotalWidth( Measurement const & width ) {  itsTotalWidth = width; }
  void  setTotalWidthFromLifetime( Measurement const & lt );
  void  setLowerCutoff( double cut )               {  itsLowerCutoff = cut; }
  void  setUpperCutoff( double cut )               {  itsUpperCutoff = cut; }

private:

  // ---  class-specific data:
  //
  Measurement   itsMass;
  Measurement   itsTotalWidth;
  double        itsLowerCutoff;
  double        itsUpperCutoff;

};  // ResonanceStructure

inline
void swap( ResonanceStructure & first, ResonanceStructure & second )  {
  first.swap( second );
}

}	// HepPDT

#endif // RESONANCESTRUCTURE_HH
