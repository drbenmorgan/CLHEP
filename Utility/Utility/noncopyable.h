#ifndef CLHEP_NONCOPYABLE_H
#define CLHEP_NONCOPYABLE_H

// ======================================================================
//
// noncopyable - classes directly/indirectly inheriting won't be copyable
//
// Author:  W. E. Brown; 2010-03-05
//
// ======================================================================


#include "CLHEP/Utility/defs.h"
#include "CLHEP/Utility/keywords.h"


namespace CLHEP {

class noncopyable
{
protected:
  noncopyable () noexcept { }
  ~noncopyable() noexcept { }

private:
  noncopyable              ( noncopyable const & );  // = delete;
  noncopyable & operator = ( noncopyable const & );  // = delete;
};  // noncopyable

}  // namespace CLHEP

#endif  // CLHEP_NONCOPYABLE_H
//
// ======================================================================
