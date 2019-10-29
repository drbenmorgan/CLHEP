#ifndef ZMEXLOGRESULT_H
#define ZMEXLOGRESULT_H


// ----------------------------------------------------------------------
//
// ZMexLogResult.h - define action values returnable by a logger
//
// Revision History:
//	970917	WEB	Split out from ZMexLogger.h, per code review 2
//	980615	WEB	Added namespace support
//
// ----------------------------------------------------------------------


namespace zmex  {


enum ZMexLogResult { ZMexLOGGED, ZMexNOTLOGGED, ZMexLOGVIAPARENT };


}  // namespace zmex


#endif  // ZMEXLOGRESULT_H
