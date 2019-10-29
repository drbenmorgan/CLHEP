#ifndef ZMEXSEVERITY_H
#define ZMEXSEVERITY_H


// ----------------------------------------------------------------------
//
// ZMexSeverity.h - define severity codes & ancillary information
//
// Revision History:
//	970917	WEB	Updated per code review 2
//      971006	WEB	Added ZMexSeverityLimit to support limiting
//			logging by severity
//      971016	WEB	Added explanations of the various severity levels
//      971112  WEB	Updated for conformance to standard and the zoom
//			compatability headers
//	980615	WEB	Added namespace support
//	000217	WEB	Improve C++ standards compliance
//	000503	WEB	Avoid global using
//	031105	LG	Get rid of all ZMutility references
//
// ----------------------------------------------------------------------

#ifndef STRING_INCLUDED
  #define STRING_INCLUDED
  #include <string>
#endif


namespace zmex  {


enum ZMexSeverity {

  ZMexNORMAL,
    // All is well; always safe to ignore; typically not worth logging
    // since it's probably just a temporary placeholder.
  ZMexINFO,
    // In the normal course of events, here is news worth logging;
    // always safe to ignore; often useful for progress reporting and
    // for debugging purposes.
  ZMexWARNING,
    // Something unusual has happened, but we have a quite reasonable
    // action to take; it's generally safe to ignore the warning because
    // you'll probably get just about the result you intended; logging
    // can probably cease after (say) 50 of the same warnings.
  ZMexERROR,
    // We encountered something such that, although we can make it safe
    // to continue running (e.g., by supplying a default value instead of
    // a value we can't for some reason calculate), you probably won't
    // get the result you expected unless you handle this yourself; ought
    // always be logged (but may be sensible, if hundreds of the same
    // error are intentionally ignored, to stop logging each one).
  ZMexSEVERE,
    // The action you intended will almost certainly have a seriously
    // flawed outcome and we doubt that either we or you can make it safe
    // to continue if you ignore this; ought always be logged.
  ZMexFATAL,
    // We can make no representations as to the state of any part of the
    // software, even of software parts not obviously associated with the
    // failed intended action and even if you try to handle the problem;
    // ought always be logged and essentially never be ignored.
  ZMexPROBLEM,
    // The software has reached a logically impossible internal state;
    // must always be logged and never be ignored; if encountered, should
    // always be reported to the software's developers and/or maintainers.
  ZMexSEVERITYenumLAST
    // Not a true severity level; useful to count the number of distinct
    // severity levels and, as such, must always be physically last
    // within this enum's definition.

};  // ZMexSeverity


extern const std::string ZMexSeverityName[ ZMexSEVERITYenumLAST ];

extern const char ZMexSeverityLetter[ ZMexSEVERITYenumLAST ];

extern int ZMexSeverityLimit[ ZMexSEVERITYenumLAST ];


}  // namespace zmex


#endif  // ZMEXSEVERITY_H
