// ----------------------------------------------------------------------
//
// ZMexSeverity.cc - define severity codes & ancillary information
//
// Revision History:
//	971006	WEB	Split out from ZMexSeverity.h
//	971113  WEB	Updated to conform to standard coding techniques
//	980615	WEB	Added namespace support
//
// ----------------------------------------------------------------------


#include "CLHEP/Exceptions/ZMexSeverity.h"


namespace zmex  {


const std::string ZMexSeverityName[ ZMexSEVERITYenumLAST ] = {
  "NORMAL",			// ZMexNORMAL
  "INFORMATIONAL",		// ZMexINFO
  "WARNING",			// ZMexWARNING
  "ERROR",			// ZMexERROR
  "SEVERE",			// ZMexSEVERE
  "FATAL",			// ZMexFATAL
  "UNANTICIPATED PROBLEM", 	// ZMexPROBLEM
};


const char ZMexSeverityLetter[ ZMexSEVERITYenumLAST ] = {
  ' ',		// ZMexNORMAL
  'I',		// ZMexINFO
  'W',		// ZMexWARNING
  'E',		// ZMexERROR
  'S',		// ZMexSEVERE
  'F', 		// ZMexFATAL
  '?', 		// ZMexPROBLEM
};


int ZMexSeverityLimit[ ZMexSEVERITYenumLAST ] = {
  // Provide starting values to limit logging by severity
  -1,		// ZMexNORMAL
  -1,		// ZMexINFO
  -1,		// ZMexWARNING
  -1,		// ZMexERROR
  -1,		// ZMexSEVERE
  -1, 		// ZMexFATAL
  -1, 		// ZMexPROBLEM
};


}  // namespace zmex
