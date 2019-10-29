#ifndef ZMEXACTION_H
#define ZMEXACTION_H


// ----------------------------------------------------------------------
//
// ZMexAction.h - define codes for handler return values
//
// Revision History:
//	970916	WEB	Initial creation, excised from ZMexHandler.h
//	980615	WEB	Added namespace support
//	031105	LG	Get rid of all ZMutility references
//
// ----------------------------------------------------------------------


namespace zmex  {


enum ZMexAction { ZMexThrowIt, ZMexIgnoreIt, ZMexHANDLEVIAPARENT };


}  // namespace zmex


#endif  // ZMEXACTION_H
