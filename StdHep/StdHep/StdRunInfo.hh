// ----------------------------------------------------------------------
// StdRunInfo.hh
// ----------------------------------------------------------------------

#ifndef STDRUNINFO_HH
#define STDRUNINFO_HH

#include <vector>
#include <string>

#include "CLHEP/StdHep/StdRandom.hh"

namespace StdHep  {

class StdRunInfo  {

public:

  // ---  birth/death:
  //
  StdRunInfo( int Runno=0, int togen=0, int ngen=0, int nwrt=0,
              double com=0., double xsec=0. );
  StdRunInfo( const StdRunInfo & orig );
  StdRunInfo& operator=( const StdRunInfo & );
  ~StdRunInfo() { ; }

  // ---  accessors:
  //
  int      runNumber()        const  {  return itsRunNumber; }
  int      eventsToGenerate() const  {  return itsEventsToGenerate; }
  int      eventsGenerated()  const  {  return itsEventsGenerated; }
  int      eventsWritten()    const  {  return itsEventsWritten; }
  double   CoMEnergy()        const  {  return itsCoMEnergy; }
  double   crossSection()     const  {  return itsCrossSection; }
  std::vector<unsigned long>  seedArray()  const {  return itsSeedList.getStateAsLongs(); }
  std::string                 seedStream() const {  return itsSeedList.getStateAsString(); }
  std::ostream&               seedString(std::ostream& os) const {  return itsSeedList.getStateAsStream(os); }
  std::string runIdentifier() const  {  return itsRunIdentifier; }
  std::string generatorName() const  {  return itsGeneratorName; }
  std::string pdfName()       const  {  return itsPDFName; }

  // ---  mutators:
  //
  void  setRunNumber        ( int runno )    { itsRunNumber = runno; }
  void  setEventsToGenerate ( int togen )    { itsEventsToGenerate = togen; }
  void  setEventsGenerated  ( int ngen )     { itsEventsGenerated = ngen; }
  void  setEventsWritten    ( int nwrt )     { itsEventsWritten = nwrt; }
  void  setCoMEnergy        ( double com )   { itsCoMEnergy = com; }
  void  setCrossSection     ( double xsec )  { itsCrossSection = xsec; }
  void  appendSeed          ( unsigned long sd ) { itsSeedList.appendSeed( sd ); }
  void  appendSeed          ( double sd )    { itsSeedList.appendSeed( sd ); }
  void	clearSeeds          (           )    { itsSeedList.clear(); }
  void	saveSeeds           ( std::istream seed ) { itsSeedList.putState(seed); }
  void	saveSeeds           ( std::string& seed ) { itsSeedList.putState(seed); }
  void	saveSeeds           ( std::vector<unsigned long> seed ) { itsSeedList.putState(seed); }
  void  setRunIdentifier    ( std::string & name );
  void  setGeneratorName    ( std::string & name );
  void  setPdfName          ( std::string & name );
  
private:

  int                 itsRunNumber;
  int                 itsEventsToGenerate;
  int                 itsEventsGenerated;
  int                 itsEventsWritten;
  double              itsCoMEnergy;
  double              itsCrossSection;
  std::string         itsRunIdentifier;
  std::string         itsGeneratorName;
  std::string         itsPDFName;
  StdRandom	      itsSeedList;
  
};	// StdRunInfo

}	// StdHep

#endif // STDRUNINFO_HH
