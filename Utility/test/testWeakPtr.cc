// ======================================================================
//
// Test compilability and basic functionality of Utility/memory.h
//
// Author:  W. E. Brown, 2010-03-19, adapted from the boost library's
// shared_ptr and related functionality whose internal attributions bear
// the following various notices:
//
//   Copyright (c) 2002-2005 Peter Dimov
//   Distributed under the Boost Software License, Version 1.0.
//   See http://www.boost.org/LICENSE_1_0.txt
//
// ======================================================================


#include "CLHEP/Utility/memory.h"

#include <cassert>
#include <map>
#include <vector>


using namespace CLHEP;
using CLHEP::shared_ptr;
using CLHEP::weak_ptr;


#if defined(_MSC_VER) && (_MSC_VER >= 1310)
#  pragma warning (disable : 4675)  // suppress ADL warning
#endif


namespace n_element_type
{

void
  f(int &)
{ }

void
  test()
{
  typedef weak_ptr<int>::element_type T;
  T t;
  f(t);
}

} // namespace n_element_type

class incomplete;

shared_ptr<incomplete> create_incomplete();

struct X
{
  int dummy;
};

struct Y
{
  int dummy2;
};

struct Z
  : public X, public virtual Y
{ };

namespace n_constructors
{

void
  default_constructor()
{
  {
    weak_ptr<int> wp;
    assert(wp.use_count() == 0);
  }

  {
    weak_ptr<void> wp;
    assert(wp.use_count() == 0);
  }

  {
    weak_ptr<incomplete> wp;
    assert(wp.use_count() == 0);
  }
}

void
  shared_ptr_constructor()
{
  {
    shared_ptr<int> sp;

    weak_ptr<int> wp(sp);
    assert(wp.use_count() == sp.use_count());

    weak_ptr<void> wp2(sp);
    assert(wp2.use_count() == sp.use_count());
  }

  {
    shared_ptr<int> sp(static_cast<int*>(0));

    {
      weak_ptr<int> wp(sp);
      assert(wp.use_count() == sp.use_count());
      assert(wp.use_count() == 1);
      shared_ptr<int> sp2(wp);
      assert(wp.use_count() == 2);
      assert(!(sp < sp2 || sp2 < sp));
    }

    {
      weak_ptr<void> wp(sp);
      assert(wp.use_count() == sp.use_count());
      assert(wp.use_count() == 1);
      shared_ptr<void> sp2(wp);
      assert(wp.use_count() == 2);
      assert(!(sp < sp2 || sp2 < sp));
    }
  }

  {
    shared_ptr<int> sp(new int);

    {
      weak_ptr<int> wp(sp);
      assert(wp.use_count() == sp.use_count());
      assert(wp.use_count() == 1);
      shared_ptr<int> sp2(wp);
      assert(wp.use_count() == 2);
      assert(!(sp < sp2 || sp2 < sp));
    }

    {
      weak_ptr<void> wp(sp);
      assert(wp.use_count() == sp.use_count());
      assert(wp.use_count() == 1);
      shared_ptr<void> sp2(wp);
      assert(wp.use_count() == 2);
      assert(!(sp < sp2 || sp2 < sp));
    }
  }

  {
    shared_ptr<void> sp;

    weak_ptr<void> wp(sp);
    assert(wp.use_count() == sp.use_count());
  }

  {
    shared_ptr<void> sp(static_cast<int*>(0));

    weak_ptr<void> wp(sp);
    assert(wp.use_count() == sp.use_count());
    assert(wp.use_count() == 1);
    shared_ptr<void> sp2(wp);
    assert(wp.use_count() == 2);
    assert(!(sp < sp2 || sp2 < sp));
  }

  {
    shared_ptr<void> sp(new int);

    weak_ptr<void> wp(sp);
    assert(wp.use_count() == sp.use_count());
    assert(wp.use_count() == 1);
    shared_ptr<void> sp2(wp);
    assert(wp.use_count() == 2);
    assert(!(sp < sp2 || sp2 < sp));
  }

  {
    shared_ptr<incomplete> sp;

    weak_ptr<incomplete> wp(sp);
    assert(wp.use_count() == sp.use_count());

    weak_ptr<void> wp2(sp);
    assert(wp2.use_count() == sp.use_count());
  }

  {
    shared_ptr<incomplete> sp = create_incomplete();

    {
      weak_ptr<incomplete> wp(sp);
      assert(wp.use_count() == sp.use_count());
      assert(wp.use_count() == 1);
      shared_ptr<incomplete> sp2(wp);
      assert(wp.use_count() == 2);
      assert(!(sp < sp2 || sp2 < sp));
    }

    {
      weak_ptr<void> wp(sp);
      assert(wp.use_count() == sp.use_count());
      assert(wp.use_count() == 1);
      shared_ptr<void> sp2(wp);
      assert(wp.use_count() == 2);
      assert(!(sp < sp2 || sp2 < sp));
    }
  }

  {
    shared_ptr<void> sp = create_incomplete();

    weak_ptr<void> wp(sp);
    assert(wp.use_count() == sp.use_count());
    assert(wp.use_count() == 1);
    shared_ptr<void> sp2(wp);
    assert(wp.use_count() == 2);
    assert(!(sp < sp2 || sp2 < sp));
  }
}

void
  copy_constructor()
{
  {
    weak_ptr<int> wp;
    weak_ptr<int> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 0);
  }

  {
    weak_ptr<void> wp;
    weak_ptr<void> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 0);
  }

  {
    weak_ptr<incomplete> wp;
    weak_ptr<incomplete> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 0);
  }

  {
    shared_ptr<int> sp(static_cast<int*>(0));
    weak_ptr<int> wp(sp);

    weak_ptr<int> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<int> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }

  {
    shared_ptr<int> sp(new int);
    weak_ptr<int> wp(sp);

    weak_ptr<int> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<int> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }

  {
    shared_ptr<void> sp(static_cast<int*>(0));
    weak_ptr<void> wp(sp);

    weak_ptr<void> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<void> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }

  {
    shared_ptr<void> sp(new int);
    weak_ptr<void> wp(sp);

    weak_ptr<void> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<void> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }

  {
    shared_ptr<incomplete> sp = create_incomplete();
    weak_ptr<incomplete> wp(sp);

    weak_ptr<incomplete> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<incomplete> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }
}

void
  conversion_constructor()
{
  {
    weak_ptr<int> wp;
    weak_ptr<void> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 0);
  }

  {
    weak_ptr<incomplete> wp;
    weak_ptr<void> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 0);
  }

  {
    weak_ptr<Z> wp;

    weak_ptr<X> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 0);

    weak_ptr<Y> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
  }

  {
    shared_ptr<int> sp(static_cast<int*>(0));
    weak_ptr<int> wp(sp);

    weak_ptr<void> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<void> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }

  {
    shared_ptr<int> sp(new int);
    weak_ptr<int> wp(sp);

    weak_ptr<void> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<void> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }

  {
    shared_ptr<incomplete> sp = create_incomplete();
    weak_ptr<incomplete> wp(sp);

    weak_ptr<void> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<void> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }

  {
    shared_ptr<Z> sp(static_cast<Z*>(0));
    weak_ptr<Z> wp(sp);

    weak_ptr<X> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<X> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }

  {
    shared_ptr<Z> sp(static_cast<Z*>(0));
    weak_ptr<Z> wp(sp);

    weak_ptr<Y> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<Y> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }

  {
    shared_ptr<Z> sp(new Z);
    weak_ptr<Z> wp(sp);

    weak_ptr<X> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<X> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }

  {
    shared_ptr<Z> sp(new Z);
    weak_ptr<Z> wp(sp);

    weak_ptr<Y> wp2(wp);
    assert(wp2.use_count() == wp.use_count());
    assert(wp2.use_count() == 1);
    assert(!(wp < wp2 || wp2 < wp));

    sp.reset();
    assert(!(wp < wp2 || wp2 < wp));

    weak_ptr<Y> wp3(wp);
    assert(wp3.use_count() == wp.use_count());
    assert(wp3.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));
  }
}

void
  test()
{
  default_constructor();
  shared_ptr_constructor();
  copy_constructor();
  conversion_constructor();
}

} // namespace n_constructors

namespace n_assignment
{

template< class T >
  void
  copy_assignment(shared_ptr<T> & sp)
{
  assert(sp.unique());

  weak_ptr<T> p1;

  p1 = p1;
  assert(p1.use_count() == 0);

  weak_ptr<T> p2;

  p1 = p2;
  assert(p1.use_count() == 0);

  weak_ptr<T> p3(p1);

  p1 = p3;
  assert(p1.use_count() == 0);

  weak_ptr<T> p4(sp);

  p4 = p4;
  assert(p4.use_count() == 1);

  p1 = p4;
  assert(p1.use_count() == 1);

  p4 = p2;
  assert(p4.use_count() == 0);

  sp.reset();

  p1 = p1;
  assert(p1.use_count() == 0);

  p4 = p1;
  assert(p4.use_count() == 0);
}

void
  conversion_assignment()
{
  {
    weak_ptr<void> p1;

    weak_ptr<incomplete> p2;

    p1 = p2;
    assert(p1.use_count() == 0);

    shared_ptr<incomplete> sp = create_incomplete();
    weak_ptr<incomplete> p3(sp);

    p1 = p3;
    assert(p1.use_count() == 1);

    sp.reset();

    p1 = p3;
    assert(p1.use_count() == 0);

    p1 = p2;
    assert(p1.use_count() == 0);
  }

  {
    weak_ptr<X> p1;

    weak_ptr<Z> p2;

    p1 = p2;
    assert(p1.use_count() == 0);

    shared_ptr<Z> sp(new Z);
    weak_ptr<Z> p3(sp);

    p1 = p3;
    assert(p1.use_count() == 1);

    sp.reset();

    p1 = p3;
    assert(p1.use_count() == 0);

    p1 = p2;
    assert(p1.use_count() == 0);
  }

  {
    weak_ptr<Y> p1;

    weak_ptr<Z> p2;

    p1 = p2;
    assert(p1.use_count() == 0);

    shared_ptr<Z> sp(new Z);
    weak_ptr<Z> p3(sp);

    p1 = p3;
    assert(p1.use_count() == 1);

    sp.reset();

    p1 = p3;
    assert(p1.use_count() == 0);

    p1 = p2;
    assert(p1.use_count() == 0);
  }
}

template< class T, class U >
  void
  shared_ptr_assignment(shared_ptr<U> & sp, T * = 0)
{
  assert(sp.unique());

  weak_ptr<T> p1;
  weak_ptr<T> p2(p1);
  weak_ptr<T> p3(sp);
  weak_ptr<T> p4(p3);

  p1 = sp;
  assert(p1.use_count() == 1);

  p2 = sp;
  assert(p2.use_count() == 1);

  p3 = sp;
  assert(p3.use_count() == 1);

  p4 = sp;
  assert(p4.use_count() == 1);

  sp.reset();

  assert(p1.use_count() == 0);
  assert(p2.use_count() == 0);
  assert(p3.use_count() == 0);
  assert(p4.use_count() == 0);

  p1 = sp;
}

void
  test()
{
  {
    shared_ptr<int> p( new int );
    copy_assignment( p );
  }

  {
    shared_ptr<X> p( new X );
    copy_assignment( p );
  }

  {
    shared_ptr<void> p( new int );
    copy_assignment( p );
  }

  {
    shared_ptr<incomplete> p = create_incomplete();
    copy_assignment( p );
  }

  conversion_assignment();

  {
    shared_ptr<int> p( new int );
    shared_ptr_assignment<int>( p );
  }

  {
    shared_ptr<int> p( new int );
    shared_ptr_assignment<void>( p );
  }

  {
    shared_ptr<X> p( new X );
    shared_ptr_assignment<X>( p );
  }

  {
    shared_ptr<X> p( new X );
    shared_ptr_assignment<void>( p );
  }

  {
    shared_ptr<void> p( new int );
    shared_ptr_assignment<void>( p );
  }

  {
    shared_ptr<incomplete> p = create_incomplete();
    shared_ptr_assignment<incomplete>( p );
  }

  {
    shared_ptr<incomplete> p = create_incomplete();
    shared_ptr_assignment<void>( p );
  }
}

} // namespace n_assignment

namespace n_reset
{

template< class T, class U >
  void
  test2( shared_ptr<U> & sp, T * = 0 )
{
  assert(sp.unique());

  weak_ptr<T> p1;
  weak_ptr<T> p2(p1);
  weak_ptr<T> p3(sp);
  weak_ptr<T> p4(p3);
  weak_ptr<T> p5(sp);
  weak_ptr<T> p6(p5);

  p1.reset();
  assert(p1.use_count() == 0);

  p2.reset();
  assert(p2.use_count() == 0);

  p3.reset();
  assert(p3.use_count() == 0);

  p4.reset();
  assert(p4.use_count() == 0);

  sp.reset();

  p5.reset();
  assert(p5.use_count() == 0);

  p6.reset();
  assert(p6.use_count() == 0);
}

void
  test()
{
  {
    shared_ptr<int> p( new int );
    test2<int>( p );
  }

  {
    shared_ptr<int> p( new int );
    test2<void>( p );
  }

  {
    shared_ptr<X> p( new X );
    test2<X>( p );
  }

  {
    shared_ptr<X> p( new X );
    test2<void>( p );
  }

  {
    shared_ptr<void> p( new int );
    test2<void>( p );
  }

  {
    shared_ptr<incomplete> p = create_incomplete();
    test2<incomplete>( p );
  }

  {
    shared_ptr<incomplete> p = create_incomplete();
    test2<void>( p );
  }
}

} // namespace n_reset

namespace n_use_count
{

void
  test()
{
  {
    weak_ptr<X> wp;
    assert(wp.use_count() == 0);
    assert(wp.expired());

    weak_ptr<X> wp2;
    assert(wp.use_count() == 0);
    assert(wp.expired());

    weak_ptr<X> wp3(wp);
    assert(wp.use_count() == 0);
    assert(wp.expired());
    assert(wp3.use_count() == 0);
    assert(wp3.expired());
  }

  {
    shared_ptr<X> sp(static_cast<X*>(0));

    weak_ptr<X> wp(sp);
    assert(wp.use_count() == 1);
    assert(!wp.expired());

    weak_ptr<X> wp2(sp);
    assert(wp.use_count() == 1);
    assert(!wp.expired());

    weak_ptr<X> wp3(wp);
    assert(wp.use_count() == 1);
    assert(!wp.expired());
    assert(wp3.use_count() == 1);
    assert(!wp3.expired());

    shared_ptr<X> sp2(sp);

    assert(wp.use_count() == 2);
    assert(!wp.expired());
    assert(wp2.use_count() == 2);
    assert(!wp2.expired());
    assert(wp3.use_count() == 2);
    assert(!wp3.expired());

    shared_ptr<void> sp3(sp);

    assert(wp.use_count() == 3);
    assert(!wp.expired());
    assert(wp2.use_count() == 3);
    assert(!wp2.expired());
    assert(wp3.use_count() == 3);
    assert(!wp3.expired());

    sp.reset();

    assert(wp.use_count() == 2);
    assert(!wp.expired());
    assert(wp2.use_count() == 2);
    assert(!wp2.expired());
    assert(wp3.use_count() == 2);
    assert(!wp3.expired());

    sp2.reset();

    assert(wp.use_count() == 1);
    assert(!wp.expired());
    assert(wp2.use_count() == 1);
    assert(!wp2.expired());
    assert(wp3.use_count() == 1);
    assert(!wp3.expired());

    sp3.reset();

    assert(wp.use_count() == 0);
    assert(wp.expired());
    assert(wp2.use_count() == 0);
    assert(wp2.expired());
    assert(wp3.use_count() == 0);
    assert(wp3.expired());
  }
}

} // namespace n_use_count

namespace n_swap
{

void
  test()
{
  {
    weak_ptr<X> wp;
    weak_ptr<X> wp2;

    wp.swap(wp2);

    assert(wp.use_count() == 0);
    assert(wp2.use_count() == 0);

    using std::swap;
    swap(wp, wp2);

    assert(wp.use_count() == 0);
    assert(wp2.use_count() == 0);
  }

  {
    shared_ptr<X> sp(new X);
    weak_ptr<X> wp;
    weak_ptr<X> wp2(sp);
    weak_ptr<X> wp3(sp);

    wp.swap(wp2);

    assert(wp.use_count() == 1);
    assert(wp2.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));

    using std::swap;
    swap(wp, wp2);

    assert(wp.use_count() == 0);
    assert(wp2.use_count() == 1);
    assert(!(wp2 < wp3 || wp3 < wp2));

    sp.reset();

    wp.swap(wp2);

    assert(wp.use_count() == 0);
    assert(wp2.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));

    using std::swap;
    swap(wp, wp2);

    assert(wp.use_count() == 0);
    assert(wp2.use_count() == 0);
    assert(!(wp2 < wp3 || wp3 < wp2));
  }

  {
    shared_ptr<X> sp(new X);
    shared_ptr<X> sp2(new X);
    weak_ptr<X> wp(sp);
    weak_ptr<X> wp2(sp2);
    weak_ptr<X> wp3(sp2);

    wp.swap(wp2);

    assert(wp.use_count() == 1);
    assert(wp2.use_count() == 1);
    assert(!(wp < wp3 || wp3 < wp));

    using std::swap;
    swap(wp, wp2);

    assert(wp.use_count() == 1);
    assert(wp2.use_count() == 1);
    assert(!(wp2 < wp3 || wp3 < wp2));

    sp.reset();

    wp.swap(wp2);

    assert(wp.use_count() == 1);
    assert(wp2.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));

    using std::swap;
    swap(wp, wp2);

    assert(wp.use_count() == 0);
    assert(wp2.use_count() == 1);
    assert(!(wp2 < wp3 || wp3 < wp2));

    sp2.reset();

    wp.swap(wp2);

    assert(wp.use_count() == 0);
    assert(wp2.use_count() == 0);
    assert(!(wp < wp3 || wp3 < wp));

    using std::swap;
    swap(wp, wp2);

    assert(wp.use_count() == 0);
    assert(wp2.use_count() == 0);
    assert(!(wp2 < wp3 || wp3 < wp2));
  }
}

} // namespace n_swap

namespace n_comparison
{

// don't generate warnings about unused variable inside assert
#if defined __GNUC__ 
  #if __GNUC__ > 3 && __GNUC_MINOR__ > 6
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wunused-variable"
  #endif
#endif
#ifdef __clang__
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wunused-variable"
#endif
void
  test()
{
  {
    weak_ptr<X> wp;
    assert(!(wp < wp));

    weak_ptr<X> wp2;
    assert(!(wp < wp2 && wp2 < wp));

    weak_ptr<X> wp3(wp);
    assert(!(wp3 < wp3));
    assert(!(wp < wp3 && wp3 < wp));
  }

  {
    shared_ptr<X> sp(new X);

    weak_ptr<X> wp(sp);
    assert(!(wp < wp));

    weak_ptr<X> wp2;
    assert(wp < wp2 || wp2 < wp);
    assert(!(wp < wp2 && wp2 < wp));

    bool b1 = wp < wp2;
    bool b2 = wp2 < wp;

    {
      weak_ptr<X> wp3(wp);

      assert(!(wp < wp3 || wp3 < wp));
      assert(!(wp < wp3 && wp3 < wp));

      assert(wp2 < wp3 || wp3 < wp2);
      assert(!(wp2 < wp3 && wp3 < wp2));

      weak_ptr<X> wp4(wp2);

      assert(wp4 < wp3 || wp3 < wp4);
      assert(!(wp4 < wp3 && wp3 < wp4));
    }

    sp.reset();

    assert(b1 == (wp < wp2));
    assert(b2 == (wp2 < wp));

    {
      weak_ptr<X> wp3(wp);

      assert(!(wp < wp3 || wp3 < wp));
      assert(!(wp < wp3 && wp3 < wp));

      assert(wp2 < wp3 || wp3 < wp2);
      assert(!(wp2 < wp3 && wp3 < wp2));

      weak_ptr<X> wp4(wp2);

      assert(wp4 < wp3 || wp3 < wp4);
      assert(!(wp4 < wp3 && wp3 < wp4));
    }
  }

  {
    shared_ptr<X> sp(new X);
    shared_ptr<X> sp2(new X);

    weak_ptr<X> wp(sp);
    weak_ptr<X> wp2(sp2);

    assert(wp < wp2 || wp2 < wp);
    assert(!(wp < wp2 && wp2 < wp));

    bool b1 = wp < wp2;
    bool b2 = wp2 < wp;

    {
      weak_ptr<X> wp3(wp);

      assert(!(wp < wp3 || wp3 < wp));
      assert(!(wp < wp3 && wp3 < wp));

      assert(wp2 < wp3 || wp3 < wp2);
      assert(!(wp2 < wp3 && wp3 < wp2));

      weak_ptr<X> wp4(wp2);

      assert(wp4 < wp3 || wp3 < wp4);
      assert(!(wp4 < wp3 && wp3 < wp4));
    }

    sp.reset();

    assert(b1 == (wp < wp2));
    assert(b2 == (wp2 < wp));

    {
      weak_ptr<X> wp3(wp);

      assert(!(wp < wp3 || wp3 < wp));
      assert(!(wp < wp3 && wp3 < wp));

      assert(wp2 < wp3 || wp3 < wp2);
      assert(!(wp2 < wp3 && wp3 < wp2));

      weak_ptr<X> wp4(wp2);

      assert(wp4 < wp3 || wp3 < wp4);
      assert(!(wp4 < wp3 && wp3 < wp4));
    }

    sp2.reset();

    assert(b1 == (wp < wp2));
    assert(b2 == (wp2 < wp));

    {
      weak_ptr<X> wp3(wp);

      assert(!(wp < wp3 || wp3 < wp));
      assert(!(wp < wp3 && wp3 < wp));

      assert(wp2 < wp3 || wp3 < wp2);
      assert(!(wp2 < wp3 && wp3 < wp2));

      weak_ptr<X> wp4(wp2);

      assert(wp4 < wp3 || wp3 < wp4);
      assert(!(wp4 < wp3 && wp3 < wp4));
    }
  }

  {
    shared_ptr<X> sp(new X);
    shared_ptr<X> sp2(sp);

    weak_ptr<X> wp(sp);
    weak_ptr<X> wp2(sp2);

    assert(!(wp < wp2 || wp2 < wp));
    assert(!(wp < wp2 && wp2 < wp));

    bool b1 = wp < wp2;
    bool b2 = wp2 < wp;

    {
      weak_ptr<X> wp3(wp);

      assert(!(wp < wp3 || wp3 < wp));
      assert(!(wp < wp3 && wp3 < wp));

      assert(!(wp2 < wp3 || wp3 < wp2));
      assert(!(wp2 < wp3 && wp3 < wp2));

      weak_ptr<X> wp4(wp2);

      assert(!(wp4 < wp3 || wp3 < wp4));
      assert(!(wp4 < wp3 && wp3 < wp4));
    }

    sp.reset();
    sp2.reset();

    assert(b1 == (wp < wp2));
    assert(b2 == (wp2 < wp));

    {
      weak_ptr<X> wp3(wp);

      assert(!(wp < wp3 || wp3 < wp));
      assert(!(wp < wp3 && wp3 < wp));

      assert(!(wp2 < wp3 || wp3 < wp2));
      assert(!(wp2 < wp3 && wp3 < wp2));

      weak_ptr<X> wp4(wp2);

      assert(!(wp4 < wp3 || wp3 < wp4));
      assert(!(wp4 < wp3 && wp3 < wp4));
    }
  }

  {
    shared_ptr<X> spx(new X);
    shared_ptr<Y> spy(new Y);
    shared_ptr<Z> spz(new Z);

    weak_ptr<X> px(spx);
    weak_ptr<Y> py(spy);
    weak_ptr<Z> pz(spz);

    assert(px < py || py < px);
    assert(px < pz || pz < px);
    assert(py < pz || pz < py);

    assert(!(px < py && py < px));
    assert(!(px < pz && pz < px));
    assert(!(py < pz && pz < py));

    weak_ptr<void> pvx(px);
    assert(!(pvx < pvx));

    weak_ptr<void> pvy(py);
    assert(!(pvy < pvy));

    weak_ptr<void> pvz(pz);
    assert(!(pvz < pvz));

    assert(pvx < pvy || pvy < pvx);
    assert(pvx < pvz || pvz < pvx);
    assert(pvy < pvz || pvz < pvy);

    assert(!(pvx < pvy && pvy < pvx));
    assert(!(pvx < pvz && pvz < pvx));
    assert(!(pvy < pvz && pvz < pvy));

    spx.reset();
    spy.reset();
    spz.reset();

    assert(px < py || py < px);
    assert(px < pz || pz < px);
    assert(py < pz || pz < py);

    assert(!(px < py && py < px));
    assert(!(px < pz && pz < px));
    assert(!(py < pz && pz < py));

    assert(!(pvx < pvx));
    assert(!(pvy < pvy));
    assert(!(pvz < pvz));

    assert(pvx < pvy || pvy < pvx);
    assert(pvx < pvz || pvz < pvx);
    assert(pvy < pvz || pvz < pvy);

    assert(!(pvx < pvy && pvy < pvx));
    assert(!(pvx < pvz && pvz < pvx));
    assert(!(pvy < pvz && pvz < pvy));
  }

  {
    shared_ptr<Z> spz(new Z);
    shared_ptr<X> spx(spz);

    weak_ptr<Z> pz(spz);
    weak_ptr<X> px(spx);
    weak_ptr<Y> py(spz);

    assert(!(px < px));
    assert(!(py < py));

    assert(!(px < py || py < px));
    assert(!(px < pz || pz < px));
    assert(!(py < pz || pz < py));

    weak_ptr<void> pvx(px);
    weak_ptr<void> pvy(py);
    weak_ptr<void> pvz(pz);

    assert(!(pvx < pvy || pvy < pvx));
    assert(!(pvx < pvz || pvz < pvx));
    assert(!(pvy < pvz || pvz < pvy));

    spx.reset();
    spz.reset();

    assert(!(px < px));
    assert(!(py < py));

    assert(!(px < py || py < px));
    assert(!(px < pz || pz < px));
    assert(!(py < pz || pz < py));

    assert(!(pvx < pvy || pvy < pvx));
    assert(!(pvx < pvz || pvz < pvx));
    assert(!(pvy < pvz || pvz < pvy));
  }
}
#if defined __GNUC__ 
  #if __GNUC__ > 3 && __GNUC_MINOR__ > 6
    #pragma GCC diagnostic pop
  #endif
#endif
#ifdef __clang__
  #pragma clang diagnostic pop
#endif

} // namespace n_comparison

namespace n_lock
{

void
  test()
{
}

} // namespace n_lock

namespace n_map
{

void
  test()
{
  std::vector< shared_ptr<int> > vi;

  {
    shared_ptr<int> pi1(new int);
    shared_ptr<int> pi2(new int);
    shared_ptr<int> pi3(new int);

    vi.push_back(pi1);
    vi.push_back(pi1);
    vi.push_back(pi1);
    vi.push_back(pi2);
    vi.push_back(pi1);
    vi.push_back(pi2);
    vi.push_back(pi1);
    vi.push_back(pi3);
    vi.push_back(pi3);
    vi.push_back(pi2);
    vi.push_back(pi1);
  }

  std::vector< shared_ptr<X> > vx;

  {
    shared_ptr<X> px1(new X);
    shared_ptr<X> px2(new X);
    shared_ptr<X> px3(new X);

    vx.push_back(px2);
    vx.push_back(px2);
    vx.push_back(px1);
    vx.push_back(px2);
    vx.push_back(px1);
    vx.push_back(px1);
    vx.push_back(px1);
    vx.push_back(px2);
    vx.push_back(px1);
    vx.push_back(px3);
    vx.push_back(px2);
  }

  std::map< weak_ptr<void>, long > m;

  {
    for(std::vector< shared_ptr<int> >::iterator i = vi.begin(); i != vi.end(); ++i)
    {
      ++m[*i];
    }
  }

  {
    for(std::vector< shared_ptr<X> >::iterator i = vx.begin(); i != vx.end(); ++i)
    {
      ++m[*i];
    }
  }

  {
    for(std::map< weak_ptr<void>, long >::iterator i = m.begin(); i != m.end(); ++i)
    {
      assert(i->first.use_count() == i->second);
    }
  }
}

} // namespace n_map

int main()
{
  n_element_type::test();
  n_constructors::test();
  n_assignment::test();
  n_reset::test();
  n_use_count::test();
  n_swap::test();
  n_comparison::test();
  n_lock::test();

  n_map::test();

  return 0;
}

class incomplete
{ };

shared_ptr<incomplete>
  create_incomplete()
{
  shared_ptr<incomplete> px(new incomplete);
  return px;
}
