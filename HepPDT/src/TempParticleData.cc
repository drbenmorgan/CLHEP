// $Id: TempParticleData.cc,v 1.1.1.1 2003/07/15 20:15:05 garren Exp $
// ----------------------------------------------------------------------
//
// TempParticleData.cc
//
// ----------------------------------------------------------------------

#include <algorithm>	// swap()

#include "CLHEP/HepPDT/TempParticleData.hh"

namespace HepPDT {

TempParticleData::TempParticleData(  )
: tempID            ( ParticleID(0) ), 
  tempParticleName  ( "" ), 
  tempCharge        ( 0. ),
  tempColorCharge   ( 0. ),
  tempSpin          ( SpinState() ),
  tempMass          ( Measurement(0.,0.) ),
  tempWidth         ( Measurement(0.,0.) ),
  tempLowCutoff     ( 0. ),
  tempHighCutoff    ( 0. ),
  tempQuarks        ( 0 ),
  tempDecayList     ( 0 )
{ ; }


TempParticleData::TempParticleData( int id )
: tempID            ( ParticleID(id) ), 
  tempParticleName  ( "" ), 
  tempCharge        ( 0. ),
  tempColorCharge   ( 0. ),
  tempSpin          ( SpinState() ),
  tempMass          ( Measurement(0.,0.) ),
  tempWidth         ( Measurement(0.,0.) ),
  tempLowCutoff     ( 0. ),
  tempHighCutoff    ( 0. ),
  tempQuarks        ( 0 ),
  tempDecayList     ( 0 )
{
  processPID(); 
}

TempParticleData::TempParticleData( ParticleID pid )
: tempID            ( pid ), 
  tempParticleName  ( "" ), 
  tempCharge        ( 0. ),
  tempColorCharge   ( 0. ),
  tempSpin          ( SpinState() ),
  tempMass          ( Measurement(0.,0.) ),
  tempWidth         ( Measurement(0.,0.) ),
  tempLowCutoff     ( 0. ),
  tempHighCutoff    ( 0. ),
  tempQuarks        ( 0 ),
  tempDecayList     ( 0 )
{
  processPID(); 
}

TempParticleData::TempParticleData( int id, const std::string & name,
                   double charge, SpinState const & spin, 
		    Measurement const & mass, Measurement const & wid )
: tempID            ( ParticleID(id) ), 
  tempParticleName  ( name ), 
  tempCharge        ( charge ),
  tempColorCharge   ( 0. ),
  tempSpin          ( spin ),
  tempMass          ( mass ),
  tempWidth         ( wid ),
  tempLowCutoff     ( 0. ),
  tempHighCutoff    ( 0. ),
  tempQuarks        ( 0 ),
  tempDecayList     ( 0 )
{ ; }

TempParticleData TempParticleData::antiparticle( std::string const & name )
{
    double tchg = tempCharge;
    tempID = ParticleID( -tempID.pid() );
    tempParticleName  = name;
    processPID();
    tempColorCharge   = tempColorCharge;
    tempMass          = tempMass;
    tempWidth         = tempWidth;
    tempLowCutoff     = tempLowCutoff;
    tempHighCutoff    = tempHighCutoff;
    tempDecayList     = tempDecayList;
    // for PID's 81-100, charge may be known but cannot be inferred from the PID
    if( tchg != 0. ) { tempCharge = -tchg; }
    return *this;
}

TempParticleData::TempParticleData( TempParticleData const & orig )
:   tempID ( orig.tempID ),
    tempParticleName ( orig.tempParticleName ),
    tempCharge ( orig.tempCharge ),
    tempColorCharge ( orig.tempColorCharge ),
    tempSpin ( orig.tempSpin ),
    tempMass ( orig.tempMass ),
    tempWidth ( orig.tempWidth ),
    tempLowCutoff ( orig.tempLowCutoff ),
    tempHighCutoff ( orig.tempHighCutoff ),
    tempQuarks ( orig.tempQuarks ),
    tempDecayList ( orig.tempDecayList ) 
{ ; }

TempParticleData & TempParticleData::operator = ( TempParticleData const & rhs )
{
  TempParticleData temp( rhs );
  swap( temp );
  return *this;
}

void TempParticleData::swap( TempParticleData & other )
{
    std::swap( tempID, other.tempID );
    std::swap( tempParticleName, other.tempParticleName );
    std::swap( tempCharge, other.tempCharge );
    std::swap( tempColorCharge, other.tempColorCharge );
    std::swap( tempSpin, other.tempSpin );
    std::swap( tempMass, other.tempMass );
    std::swap( tempWidth, other.tempWidth );
    std::swap( tempLowCutoff, other.tempLowCutoff );
    std::swap( tempHighCutoff, other.tempHighCutoff );
    std::swap( tempQuarks, other.tempQuarks );
    std::swap( tempDecayList, other.tempDecayList ); 
}

bool TempParticleData::processPID()
{
    // extract charge, spin, and quark content from PID
    if( tempID.pid() == 0 ) { return false; }
    tempCharge = double( tempID.threeCharge() )/3.0;
    tempSpin.setTotalSpin( spinitod( tempID.jSpin() ) );
    tempSpin.setSpin( tempID.sSpin() );
    tempSpin.setOrbAngMom( tempID.lSpin() );
    Quarks ql = tempID.quarks();
    if( ql.nq1 != 0 ) { 
        TempConstituent tc;
	tc.tempConstituentPID = ParticleID( ql.nq1 );
	tc.tempMultiplicity = 1;
        tempQuarks.push_back( tc );
    }
    if( ql.nq2 != 0 ) { 
        TempConstituent tc;
	tc.tempConstituentPID = ParticleID( ql.nq2 );
	tc.tempMultiplicity = 1;
        tempQuarks.push_back( tc );
    }
    if( ql.nq3 != 0 ) { 
        TempConstituent tc;
	tc.tempConstituentPID = ParticleID( ql.nq3 );
	tc.tempMultiplicity = 1;
        tempQuarks.push_back( tc );
    }
    return true;
}

TempAliasData::TempAliasData(  )
: tempAlias           ( "" ), 
  tempAliasedParticle ( "" ), 
  tempChargeConj      ( "" ), 
  tempAliasDecayList  ( 0 )
{ ; }


}	// HepPDT
