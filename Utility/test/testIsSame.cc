// ======================================================================
//
// Test basic functionality of is_same type trait
//
// Author:  W. E. Brown, 2010-03-24, adapted from the boost library's
// type_traits and related functionality whose internal attributions bear
// the following various notices:
//
//   (C) Copyright John Maddock 2000.
//   Distributed under the Boost Software License, Version 1.0.
//   See http://www.boost.org/LICENSE_1_0.txt
//
// ======================================================================


#include "CLHEP/Utility/type_traits.h"

#include <cassert>


using namespace CLHEP;
using CLHEP::is_same;


typedef  int  my_int;


#define claim_same(From,To)         (is_same<From,To>::value)
#define has_same_type(From,To)      assert(claim_same(From,To))
#define has_different_type(From,To) assert(!claim_same(From,To))


int main()
{
  has_same_type(int, int);
  has_same_type(int, my_int);

  has_different_type(int      , void);
  has_different_type(int      , const int);
  has_different_type(int      , int&);
  has_different_type(const int, int&);
  has_different_type(int      , const int&);
  has_different_type(int*     , const int*);
  has_different_type(int*     , int*const);
  has_different_type(int      , int[2]);
  has_different_type(int*     , int[2]);
  has_different_type(int[4]   , int[2]);

  return 0;
}
