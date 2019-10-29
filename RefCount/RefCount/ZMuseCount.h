#ifndef ZMUSECOUNT_H
#define ZMUSECOUNT_H


// ----------------------------------------------------------------------
//
//  ZMuseCount.h - utility class for use in reference-counting
//
//
//  History:
//    19-Sep-1997  WEB  Design stolen, and code adapted, from pp 70-73 of
//      Koenig & Moo: "Ruminations on C++" (1996)
//
// ----------------------------------------------------------------------


class ZMuseCount  {

public:

  // --------------------------
  // Constructors & destructor:
  // --------------------------

  ZMuseCount();
    // Constructor
  ZMuseCount( const ZMuseCount & u );
    // Copy constructor
  ~ZMuseCount();
    // Destructor


  // -----------------------------------
  // Functions useful to a handle class:
  // -----------------------------------

  bool only();
    // Is there exactly one copy of the referent?

  bool makeonly();
    // Enables the handle (to a ClassType) to refer to a unique (copy of)
    // the referent via the following usage:
    //   if ( u.makeonly() )            /* ZMuseCount u;     */
    //      p = new ClassType( *p );    /* ClassType * p;  */
    // This is useful in implementing copy-on-write semantics
    // (i.e., non-shared or value semantics), and would appear just before
    // updating (any part of) *p in such a context.

  bool reattach( const ZMuseCount & u );
    // Simplifies a handle's implementation of assignment via the following
    // usage:
    //   if ( u.reattach(h.u) )       /* Handle<ClassType> h; */
    //     delete p;                  /* p and u as above     */
    //   p = h.p;


private:

  int * p;
    // *p is the reference counter itself

  ZMuseCount & operator=( const ZMuseCount & );
    // Forbidden operation on a ZMuseCount object

};  // ZMuseCount


//#include "CLHEP/RefCount/ZMuseCount.icc"


#endif  // ZMUSECOUNT_H
