// ----------------------------------------------------------------------
// StdRunInfo.cc
// ----------------------------------------------------------------------

#include <vector>
#include <string>

#include "CLHEP/StdHep/StdRunInfo.hh"

namespace StdHep  {

StdRunInfo::StdRunInfo( int runno, int togen, int ngen, int nwrt, 
                        double com, double xsec )
: itsRunNumber        ( runno ),
  itsEventsToGenerate ( togen ),
  itsEventsGenerated  ( ngen ),
  itsEventsWritten    ( nwrt ),
  itsCoMEnergy        ( com ), 
  itsCrossSection     ( xsec ),
  itsRunIdentifier    ( " " ),
  itsGeneratorName    ( " " ),
  itsPDFName          ( " " ),
  itsSeedList         ( StdRandom() )
{ ; }

StdRunInfo::StdRunInfo( const StdRunInfo & orig )
: itsRunNumber        ( orig.itsRunNumber ),
  itsEventsToGenerate ( orig.itsEventsToGenerate ),
  itsEventsGenerated  ( orig.itsEventsGenerated ),
  itsEventsWritten    ( orig.itsEventsWritten ),
  itsCoMEnergy        ( orig.itsCoMEnergy ), 
  itsCrossSection     ( orig.itsCrossSection ),
  itsRunIdentifier    ( orig.itsRunIdentifier ),
  itsGeneratorName    ( orig.itsGeneratorName ),
  itsPDFName          ( orig.itsPDFName ),
  itsSeedList         ( orig.itsSeedList )
{ ; }

StdRunInfo& StdRunInfo::operator=( const StdRunInfo & rhs )
{ if( this != & rhs )
  {
    itsRunNumber        = rhs.itsRunNumber;
    itsEventsToGenerate = rhs.itsEventsToGenerate;
    itsEventsGenerated  = rhs.itsEventsGenerated;
    itsEventsWritten    = rhs.itsEventsWritten;
    itsCoMEnergy        = rhs.itsCoMEnergy; 
    itsCrossSection     = rhs.itsCrossSection;
    itsRunIdentifier    = rhs.itsRunIdentifier;
    itsGeneratorName    = rhs.itsGeneratorName;
    itsPDFName          = rhs.itsPDFName;
    itsSeedList         = rhs.itsSeedList;
  }
  return *this;
}

void StdRunInfo::setRunIdentifier( std::string & name )
{
   itsRunIdentifier = name;
}

void StdRunInfo::setGeneratorName( std::string & name )
{
   itsGeneratorName = name;
}

void StdRunInfo::setPdfName( std::string & name )
{
   itsPDFName = name;
}

}	// StdHep
