// ----------------------------------------------------------------------
//
// DecayChannelT.hh
// Author:  Lynn Garren
//
// ----------------------------------------------------------------------
#ifndef DECAYCHANNELT_HH
#define DECAYCHANNELT_HH

#include <vector>
#include <string>

#include "CLHEP/HepPDT/Measurement.hh"
#include "CLHEP/HepPDT/NullDecayModelT.hh"
#include "CLHEP/HepPDT/DecayModelBase.hh"
#include "CLHEP/HepPDT/DMFactory.hh"

namespace HepPDT {

/**
 * @author
 * @ingroup heppdt
 */
template< class Config >
class DecayChannelT  {

public:
  // --- useful typedef's
  //
  typedef typename Config::ParticleData PD;	// ParticleDataType
  typedef typename Config::PT           PT;	// ParticleType

  typedef std::vector< PD >    ProductMap;

  // ---  birth/death:
  //
  // defaults 'cause we need vector<DecayChannelT<> >
  inline DecayChannelT( const std::string & name = "unknown", 
                 const Measurement & branchFrac = Measurement(), 
                 const std::vector< PD > & decaylist = ProductMap(), 
                 const std::vector<double> & dmparam = std::vector<double>() )
  : itsDecayName            ( name ),
  itsBranchingFraction    ( branchFrac ),
  itsDecayChannelProducts ( decaylist ),
  itsDecayModelParameters ( dmparam ),
  itsDecayModel ( DMFactory<Config>::instance()->unsafeMakeProduct( name, dmparam ) )
{ ; }

  virtual ~DecayChannelT();

  // ---  copying:
  //
  inline DecayChannelT( const DecayChannelT<Config> & orig );
  inline DecayChannelT & operator = ( const DecayChannelT<Config> & rhs );
  inline void swap( DecayChannelT<Config> & other );

  // ---  accessors:
  //
  std::string                 decayName()         const { return itsDecayName; }
  Measurement                 branchingFraction() const { return itsBranchingFraction; }
  int                         size()              const { return itsDecayChannelProducts.size(); }
  PD                          decayProduct(int i) const { return itsDecayChannelProducts[i]; }
  DecayModelBase<Config> const & decayModel()     const { return *itsDecayModel; }
  
  inline void write( std::ostream & os ) const;

  // ---  mutators:
  //
  void  setBranchingFraction( Measurement const & rate ) { itsBranchingFraction = rate; }
  inline void  appendDecayChannelProduct( PD const & dcp );

  // ---  decay method:
  //
  void decay( const PT & parent, std::vector<PT> & daughters ); 
  
private:

  // ---  class-specific data:
  //
  std::string              itsDecayName;
  Measurement              itsBranchingFraction;
  ProductMap               itsDecayChannelProducts;
  std::vector<double>   itsDecayModelParameters;
  DecayModelBase<Config> * itsDecayModel;

};  // DecayChannelT

template< class Config >
inline
void  swap( DecayChannelT<Config> & first, DecayChannelT<Config> & second )  {
  first.swap( second );
}

}	// HepPDT

#include "CLHEP/HepPDT/DecayChannelT.icc"

#endif // DECAYCHANNELT_HH

