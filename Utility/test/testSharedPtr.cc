// ======================================================================
//
// Test compilability and basic functionality of Utility/memory.h
//
// Author:  W. E. Brown, 2010-03-19, adapted from the boost library's
// shared_ptr and related functionality whose internal attributions bear
// the following various notices:
//
//   Copyright (c) 2002, 2003 Peter Dimov
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
  typedef shared_ptr<int>::element_type T;
  T t;
  f(t);
}

} // namespace n_element_type

namespace n_constructors
{

class incomplete;

void
  default_constructor()
{
  {
    shared_ptr<int> pi;
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 0);
  }

  {
    shared_ptr<void> pv;
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 0);
  }

  {
    shared_ptr<incomplete> px;
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 0);
  }
}

struct A
{
  int dummy;
};

struct X
{
  static long instances;

  X()
  {
    ++instances;
  }

  ~X()
  {
    --instances;
  }

private:
  X(X const &);
  X & operator= (X const &);
};

long X::instances = 0;

// virtual inheritance stresses the implementation

struct Y
  : public A
  , public virtual X
{
  static long instances;

  Y()
  {
    ++instances;
  }

  ~Y()
  {
    --instances;
  }

private:
  Y(Y const &);
  Y & operator= (Y const &);
};

long Y::instances = 0;

template< class T >
  void
  pc0_test(T * p)
{
  assert(p == 0);
  shared_ptr<T> pt(p);
  assert(pt? false: true);
  assert(!pt);
  assert(pt.get() == 0);
  assert(pt.use_count() == 1);
  assert(pt.unique());
}

void
  pointer_constructor()
{
  pc0_test(static_cast<int*>(0));

  pc0_test(static_cast<int const*>(0));
  pc0_test(static_cast<int volatile*>(0));
  pc0_test(static_cast<int const volatile*>(0));

  {
    shared_ptr<int const> pi(static_cast<int*>(0));
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 1);
    assert(pi.unique());
  }

  {
    shared_ptr<int volatile> pi(static_cast<int*>(0));
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 1);
    assert(pi.unique());
  }

  {
    shared_ptr<void> pv(static_cast<int*>(0));
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  {
    shared_ptr<void const> pv(static_cast<int*>(0));
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  pc0_test(static_cast<X*>(0));
  pc0_test(static_cast<X const*>(0));
  pc0_test(static_cast<X volatile*>(0));
  pc0_test(static_cast<X const volatile*>(0));

  {
    shared_ptr<X const> px(static_cast<X*>(0));
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
  }

  {
    shared_ptr<X> px(static_cast<Y*>(0));
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
  }

  {
    shared_ptr<X const> px(static_cast<Y*>(0));
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
  }

  {
    shared_ptr<void> pv(static_cast<X*>(0));
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  {
    shared_ptr<void const> pv(static_cast<X*>(0));
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  {
    int * p = new int(7);
    shared_ptr<int> pi(p);
    assert(pi? true: false);
    assert(!!pi);
    assert(pi.get() == p);
    assert(pi.use_count() == 1);
    assert(pi.unique());
    assert(*pi == 7);
  }

  {
    int * p = new int(7);
    shared_ptr<int const> pi(p);
    assert(pi? true: false);
    assert(!!pi);
    assert(pi.get() == p);
    assert(pi.use_count() == 1);
    assert(pi.unique());
    assert(*pi == 7);
  }

  {
    int * p = new int(7);
    shared_ptr<void> pv(p);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == p);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  {
    int * p = new int(7);
    shared_ptr<void const> pv(p);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == p);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  assert(X::instances == 0);

  {
    X * p = new X;
    shared_ptr<X> px(p);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == p);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 1);
  }

  assert(X::instances == 0);

  {
    X * p = new X;
    shared_ptr<X const> px(p);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == p);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 1);
  }

  assert(X::instances == 0);

  {
    X * p = new X;
    shared_ptr<void> pv(p);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == p);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(X::instances == 1);
  }

  assert(X::instances == 0);

  {
    X * p = new X;
    shared_ptr<void const> pv(p);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == p);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(X::instances == 1);
  }

  assert(X::instances == 0);
  assert(Y::instances == 0);

  {
    Y * p = new Y;
    shared_ptr<X> px(p);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == p);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 1);
    assert(Y::instances == 1);
  }

  assert(X::instances == 0);
  assert(Y::instances == 0);

  {
    Y * p = new Y;
    shared_ptr<X const> px(p);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == p);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 1);
    assert(Y::instances == 1);
  }

  assert(X::instances == 0);
  assert(Y::instances == 0);
}

int m = 0;

void
  deleter(int * p)
{
  assert(p == 0);
}

void
  deleter2(int * p)
{
  assert(p == &m);
  ++*p;
}

struct deleter3
{
  void operator()(incomplete * p)
  {
    assert(p == 0);
  }
};

incomplete * p0 = 0;

void
  deleter_constructor()
{
  {
    shared_ptr<int> pi(static_cast<int*>(0), deleter);
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 1);
    assert(pi.unique());
  }

  {
    shared_ptr<void> pv(static_cast<int*>(0), &deleter);
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  {
    shared_ptr<void const> pv(static_cast<int*>(0), deleter);
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  {
    shared_ptr<incomplete> px(p0, deleter3());
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
  }

  {
    shared_ptr<void> pv(p0, deleter3());
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  {
    shared_ptr<void const> pv(p0, deleter3());
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  assert(m == 0);

  {
    shared_ptr<int> pi(&m, deleter2);
    assert(pi? true: false);
    assert(!!pi);
    assert(pi.get() == &m);
    assert(pi.use_count() == 1);
    assert(pi.unique());
  }

  assert(m == 1);

  {
    shared_ptr<int const> pi(&m, &deleter2);
    assert(pi? true: false);
    assert(!!pi);
    assert(pi.get() == &m);
    assert(pi.use_count() == 1);
    assert(pi.unique());
  }

  assert(m == 2);

  {
    shared_ptr<void> pv(&m, deleter2);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == &m);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  assert(m == 3);

  {
    shared_ptr<void const> pv(&m, &deleter2);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == &m);
    assert(pv.use_count() == 1);
    assert(pv.unique());
  }

  assert(m == 4);
}

void
  copy_constructor()
{
  {
    shared_ptr<int> pi;

    shared_ptr<int> pi2(pi);
    assert(pi2 == pi);
    assert(pi2? false: true);
    assert(!pi2);
    assert(pi2.get() == 0);
    assert(pi2.use_count() == pi.use_count());

    shared_ptr<void> pi3(pi);
    assert(pi3 == pi);
    assert(pi3? false: true);
    assert(!pi3);
    assert(pi3.get() == 0);
    assert(pi3.use_count() == pi.use_count());

    shared_ptr<void> pi4(pi3);
    assert(pi4 == pi3);
    assert(pi4? false: true);
    assert(!pi4);
    assert(pi4.get() == 0);
    assert(pi4.use_count() == pi3.use_count());
  }

  {
    shared_ptr<void> pv;

    shared_ptr<void> pv2(pv);
    assert(pv2 == pv);
    assert(pv2? false: true);
    assert(!pv2);
    assert(pv2.get() == 0);
    assert(pv2.use_count() == pv.use_count());
  }

  {
    shared_ptr<incomplete> px;

    shared_ptr<incomplete> px2(px);
    assert(px2 == px);
    assert(px2? false: true);
    assert(!px2);
    assert(px2.get() == 0);
    assert(px2.use_count() == px.use_count());

    shared_ptr<void> px3(px);
    assert(px3 == px);
    assert(px3? false: true);
    assert(!px3);
    assert(px3.get() == 0);
    assert(px3.use_count() == px.use_count());
  }

  {
    shared_ptr<int> pi(static_cast<int*>(0));

    shared_ptr<int> pi2(pi);
    assert(pi2 == pi);
    assert(pi2? false: true);
    assert(!pi2);
    assert(pi2.get() == 0);
    assert(pi2.use_count() == 2);
    assert(!pi2.unique());
    assert(pi2.use_count() == pi.use_count());
    assert(!(pi < pi2 || pi2 < pi)); // shared ownership test

    shared_ptr<void> pi3(pi);
    assert(pi3 == pi);
    assert(pi3? false: true);
    assert(!pi3);
    assert(pi3.get() == 0);
    assert(pi3.use_count() == 3);
    assert(!pi3.unique());
    assert(pi3.use_count() == pi.use_count());
    assert(!(pi < pi3 || pi3 < pi)); // shared ownership test

    shared_ptr<void> pi4(pi2);
    assert(pi4 == pi2);
    assert(pi4? false: true);
    assert(!pi4);
    assert(pi4.get() == 0);
    assert(pi4.use_count() == 4);
    assert(!pi4.unique());
    assert(pi4.use_count() == pi2.use_count());
    assert(!(pi2 < pi4 || pi4 < pi2)); // shared ownership test

    assert(pi3.use_count() == pi4.use_count());
    assert(!(pi3 < pi4 || pi4 < pi3)); // shared ownership test
  }

  {
    shared_ptr<X> px(static_cast<X*>(0));

    shared_ptr<X> px2(px);
    assert(px2 == px);
    assert(px2? false: true);
    assert(!px2);
    assert(px2.get() == 0);
    assert(px2.use_count() == 2);
    assert(!px2.unique());
    assert(px2.use_count() == px.use_count());
    assert(!(px < px2 || px2 < px)); // shared ownership test

    shared_ptr<void> px3(px);
    assert(px3 == px);
    assert(px3? false: true);
    assert(!px3);
    assert(px3.get() == 0);
    assert(px3.use_count() == 3);
    assert(!px3.unique());
    assert(px3.use_count() == px.use_count());
    assert(!(px < px3 || px3 < px)); // shared ownership test

    shared_ptr<void> px4(px2);
    assert(px4 == px2);
    assert(px4? false: true);
    assert(!px4);
    assert(px4.get() == 0);
    assert(px4.use_count() == 4);
    assert(!px4.unique());
    assert(px4.use_count() == px2.use_count());
    assert(!(px2 < px4 || px4 < px2)); // shared ownership test

    assert(px3.use_count() == px4.use_count());
    assert(!(px3 < px4 || px4 < px3)); // shared ownership test
  }

  {
    int * p = new int(7);
    shared_ptr<int> pi(p);

    shared_ptr<int> pi2(pi);
    assert(pi2 == pi);
    assert(pi2? true: false);
    assert(!!pi2);
    assert(pi2.get() == p);
    assert(pi2.use_count() == 2);
    assert(!pi2.unique());
    assert(*pi2 == 7);
    assert(pi2.use_count() == pi.use_count());
    assert(!(pi < pi2 || pi2 < pi)); // shared ownership test
  }

  {
    int * p = new int(7);
    shared_ptr<void> pv(p);
    assert(pv.get() == p);

    shared_ptr<void> pv2(pv);
    assert(pv2 == pv);
    assert(pv2? true: false);
    assert(!!pv2);
    assert(pv2.get() == p);
    assert(pv2.use_count() == 2);
    assert(!pv2.unique());
    assert(pv2.use_count() == pv.use_count());
    assert(!(pv < pv2 || pv2 < pv)); // shared ownership test
  }

  assert(X::instances == 0);

  {
    X * p = new X;
    shared_ptr<X> px(p);
    assert(px.get() == p);

    shared_ptr<X> px2(px);
    assert(px2 == px);
    assert(px2? true: false);
    assert(!!px2);
    assert(px2.get() == p);
    assert(px2.use_count() == 2);
    assert(!px2.unique());

    assert(X::instances == 1);

    assert(px2.use_count() == px.use_count());
    assert(!(px < px2 || px2 < px)); // shared ownership test

    shared_ptr<void> px3(px);
    assert(px3 == px);
    assert(px3? true: false);
    assert(!!px3);
    assert(px3.get() == p);
    assert(px3.use_count() == 3);
    assert(!px3.unique());
    assert(px3.use_count() == px.use_count());
    assert(!(px < px3 || px3 < px)); // shared ownership test

    shared_ptr<void> px4(px2);
    assert(px4 == px2);
    assert(px4? true: false);
    assert(!!px4);
    assert(px4.get() == p);
    assert(px4.use_count() == 4);
    assert(!px4.unique());
    assert(px4.use_count() == px2.use_count());
    assert(!(px2 < px4 || px4 < px2)); // shared ownership test

    assert(px3.use_count() == px4.use_count());
    assert(!(px3 < px4 || px4 < px3)); // shared ownership test
  }

  assert(X::instances == 0);
  assert(Y::instances == 0);

  {
    Y * p = new Y;
    shared_ptr<Y> py(p);
    assert(py.get() == p);

    shared_ptr<X> px(py);
    assert(px == py);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == p);
    assert(px.use_count() == 2);
    assert(!px.unique());
    assert(px.use_count() == py.use_count());
    assert(!(px < py || py < px)); // shared ownership test

    assert(X::instances == 1);
    assert(Y::instances == 1);

    shared_ptr<void const> pv(px);
    assert(pv == px);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == px.get());
    assert(pv.use_count() == 3);
    assert(!pv.unique());
    assert(pv.use_count() == px.use_count());
    assert(!(px < pv || pv < px)); // shared ownership test

    shared_ptr<void const> pv2(py);
    assert(pv2 == py);
    assert(pv2? true: false);
    assert(!!pv2);
    assert(pv2.get() == py.get());
    assert(pv2.use_count() == 4);
    assert(!pv2.unique());
    assert(pv2.use_count() == py.use_count());
    assert(!(py < pv2 || pv2 < py)); // shared ownership test

    assert(pv.use_count() == pv2.use_count());
    assert(!(pv < pv2 || pv2 < pv)); // shared ownership test
  }

  assert(X::instances == 0);
  assert(Y::instances == 0);
}

void
  weak_ptr_constructor()
{
  {
    weak_ptr<Y> wp;
    assert(wp.use_count() == 0);

    try
    {
      shared_ptr<Y> p2(wp);
      throw "shared_ptr<Y> p2(wp) failed to throw";
    }
    catch(bad_weak_ptr)
    {
    }

    try
    {
      shared_ptr<X> p3(wp);
      throw "shared_ptr<X> p3(wp) failed to throw";
    }
    catch(bad_weak_ptr)
    {
    }
  }

  {
    shared_ptr<Y> p;
    weak_ptr<Y> wp(p);

    if(wp.use_count() != 0) // 0 allowed but not required
    {
      shared_ptr<Y> p2(wp);
      assert(p2.use_count() == wp.use_count());
      assert(p2.get() == 0);

      shared_ptr<X> p3(wp);
      assert(p3.use_count() == wp.use_count());
      assert(p3.get() == 0);
    }
  }

  {
    shared_ptr<Y> p(new Y);
    weak_ptr<Y> wp(p);

    {
      shared_ptr<Y> p2(wp);
      assert(p2? true: false);
      assert(!!p2);
      assert(p2.get() == p.get());
      assert(p2.use_count() == 2);
      assert(!p2.unique());
      assert(p2.use_count() == wp.use_count());

      assert(p.use_count() == p2.use_count());
      assert(!(p < p2 || p2 < p)); // shared ownership test

      shared_ptr<X> p3(wp);
      assert(p3? true: false);
      assert(!!p3);
      assert(p3.get() == p.get());
      assert(p3.use_count() == 3);
      assert(!p3.unique());
      assert(p3.use_count() == wp.use_count());

      assert(p.use_count() == p3.use_count());
    }

    p.reset();
    assert(wp.use_count() == 0);

    try
    {
      shared_ptr<Y> p2(wp);
      throw "shared_ptr<Y> p2(wp) failed to throw";
    }
    catch(bad_weak_ptr)
    {
    }

    try
    {
      shared_ptr<X> p3(wp);
      throw "shared_ptr<X> p3(wp) failed to throw";
    }
    catch(bad_weak_ptr)
    {
    }
  }
}

void
  auto_ptr_constructor()
{
  {
    std::auto_ptr<int> p;
    shared_ptr<int> pi(p);
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 1);
    assert(pi.unique());
    assert(p.get() == 0);
  }

  {
    std::auto_ptr<int> p;
    shared_ptr<int const> pi(p);
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 1);
    assert(pi.unique());
    assert(p.get() == 0);
  }

  {
    std::auto_ptr<int> p;
    shared_ptr<void> pv(p);
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(p.get() == 0);
  }

  {
    std::auto_ptr<int> p;
    shared_ptr<void const> pv(p);
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(p.get() == 0);
  }

  {
    std::auto_ptr<X> p;
    shared_ptr<X> px(p);
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(p.get() == 0);
  }

  {
    std::auto_ptr<X> p;
    shared_ptr<X const> px(p);
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(p.get() == 0);
  }

  {
    std::auto_ptr<Y> p;
    shared_ptr<X> px(p);
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(p.get() == 0);
  }

  {
    std::auto_ptr<Y> p;
    shared_ptr<X const> px(p);
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(p.get() == 0);
  }

  {
    std::auto_ptr<Y> p;
    shared_ptr<void> pv(p);
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(p.get() == 0);
  }

  {
    std::auto_ptr<Y> p;
    shared_ptr<void const> pv(p);
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(p.get() == 0);
  }

  {
    std::auto_ptr<int> p(new int(7));
    int * q = p.get();
    shared_ptr<int> pi(p);
    assert(pi? true: false);
    assert(!!pi);
    assert(pi.get() == q);
    assert(pi.use_count() == 1);
    assert(pi.unique());
    assert(*pi == 7);

    assert(p.get() == 0);
  }

  {
    std::auto_ptr<int> p(new int(7));
    int * q = p.get();
    shared_ptr<int const> pi(p);
    assert(pi? true: false);
    assert(!!pi);
    assert(pi.get() == q);
    assert(pi.use_count() == 1);
    assert(pi.unique());
    assert(*pi == 7);

    assert(p.get() == 0);
  }

  {
    std::auto_ptr<int> p(new int(7));
    int * q = p.get();
    shared_ptr<void> pv(p);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == q);
    assert(pv.use_count() == 1);
    assert(pv.unique());

    assert(p.get() == 0);
  }

  {
    std::auto_ptr<int> p(new int(7));
    int * q = p.get();
    shared_ptr<void const> pv(p);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == q);
    assert(pv.use_count() == 1);
    assert(pv.unique());

    assert(p.get() == 0);
  }

  assert(X::instances == 0);

  {
    std::auto_ptr<X> p(new X);
    X * q = p.get();
    shared_ptr<X> px(p);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == q);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 1);

    assert(p.get() == 0);
  }

  assert(X::instances == 0);

  {
    std::auto_ptr<X> p(new X);
    X * q = p.get();
    shared_ptr<X const> px(p);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == q);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 1);

    assert(p.get() == 0);
  }

  assert(X::instances == 0);

  {
    std::auto_ptr<X> p(new X);
    X * q = p.get();
    shared_ptr<void> pv(p);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == q);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(X::instances == 1);

    assert(p.get() == 0);
  }

  assert(X::instances == 0);

  {
    std::auto_ptr<X> p(new X);
    X * q = p.get();
    shared_ptr<void const> pv(p);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == q);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(X::instances == 1);

    assert(p.get() == 0);
  }

  assert(X::instances == 0);
  assert(Y::instances == 0);

  {
    std::auto_ptr<Y> p(new Y);
    Y * q = p.get();
    shared_ptr<X> px(p);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == q);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 1);
    assert(Y::instances == 1);

    assert(p.get() == 0);
  }

  assert(X::instances == 0);
  assert(Y::instances == 0);

  {
    std::auto_ptr<Y> p(new Y);
    Y * q = p.get();
    shared_ptr<X const> px(p);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == q);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 1);
    assert(Y::instances == 1);

    assert(p.get() == 0);
  }

  assert(X::instances == 0);
  assert(Y::instances == 0);
}

void
  test()
{
  default_constructor();
  pointer_constructor();
  deleter_constructor();
  copy_constructor();
  weak_ptr_constructor();
  auto_ptr_constructor();
}

} // namespace n_constructors

namespace n_assignment
{

class incomplete;

struct A
{
  int dummy;
};

struct X
{
  static long instances;

  X()
  {
    ++instances;
  }

  ~X()
  {
    --instances;
  }

private:
  X(X const &);
  X & operator= (X const &);
};

long X::instances = 0;

struct Y
  : public A
  , public virtual X
{
  static long instances;

  Y()
  {
    ++instances;
  }

  ~Y()
  {
    --instances;
  }

private:
  Y(Y const &);
  Y & operator= (Y const &);
};

long Y::instances = 0;

void
  copy_assignment()
{
  {
    shared_ptr<incomplete> p1;

    p1 = p1;

    assert(p1 == p1);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);

    shared_ptr<incomplete> p2;

    p1 = p2;

    assert(p1 == p2);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);

    shared_ptr<incomplete> p3(p1);

    p1 = p3;

    assert(p1 == p3);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);
  }

  {
    shared_ptr<void> p1;

    p1 = p1;

    assert(p1 == p1);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);

    shared_ptr<void> p2;

    p1 = p2;

    assert(p1 == p2);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);

    shared_ptr<void> p3(p1);

    p1 = p3;

    assert(p1 == p3);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);

    shared_ptr<void> p4(new int);
    assert(p4.use_count() == 1);

    p1 = p4;

    assert(p1 == p4);
    assert(!(p1 < p4 || p4 < p1));
    assert(p1.use_count() == 2);
    assert(p4.use_count() == 2);

    p1 = p3;

    assert(p1 == p3);
    assert(p4.use_count() == 1);
  }

  {
    shared_ptr<X> p1;

    p1 = p1;

    assert(p1 == p1);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);

    shared_ptr<X> p2;

    p1 = p2;

    assert(p1 == p2);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);

    shared_ptr<X> p3(p1);

    p1 = p3;

    assert(p1 == p3);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);

    assert(X::instances == 0);

    shared_ptr<X> p4(new X);

    assert(X::instances == 1);

    p1 = p4;

    assert(X::instances == 1);

    assert(p1 == p4);
    assert(!(p1 < p4 || p4 < p1));

    assert(p1.use_count() == 2);

    p1 = p2;

    assert(p1 == p2);
    assert(X::instances == 1);

    p4 = p3;

    assert(p4 == p3);
    assert(X::instances == 0);
  }
}

void
  conversion_assignment()
{
  {
    shared_ptr<void> p1;

    shared_ptr<incomplete> p2;

    p1 = p2;

    assert(p1 == p2);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);

    shared_ptr<int> p4(new int);
    assert(p4.use_count() == 1);

    shared_ptr<void> p5(p4);
    assert(p4.use_count() == 2);

    p1 = p4;

    assert(p1 == p4);
    assert(!(p1 < p5 || p5 < p1));
    assert(p1.use_count() == 3);
    assert(p4.use_count() == 3);

    p1 = p2;

    assert(p1 == p2);
    assert(p4.use_count() == 2);
  }

  {
    shared_ptr<X> p1;

    shared_ptr<Y> p2;

    p1 = p2;

    assert(p1 == p2);
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);

    assert(X::instances == 0);
    assert(Y::instances == 0);

    shared_ptr<Y> p4(new Y);

    assert(X::instances == 1);
    assert(Y::instances == 1);
    assert(p4.use_count() == 1);

    shared_ptr<X> p5(p4);
    assert(p4.use_count() == 2);

    p1 = p4;

    assert(X::instances == 1);
    assert(Y::instances == 1);

    assert(p1 == p4);
    assert(!(p1 < p5 || p5 < p1));

    assert(p1.use_count() == 3);
    assert(p4.use_count() == 3);

    p1 = p2;

    assert(p1 == p2);
    assert(X::instances == 1);
    assert(Y::instances == 1);
    assert(p4.use_count() == 2);

    p4 = p2;
    p5 = p2;

    assert(p4 == p2);
    assert(X::instances == 0);
    assert(Y::instances == 0);
  }
}

void
  auto_ptr_assignment()
{
  {
    shared_ptr<int> p1;

    std::auto_ptr<int> p2;

    p1 = p2;
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);
    assert(p1.use_count() == 1);

    int * p = new int;
    std::auto_ptr<int> p3(p);

    p1 = p3;
    assert(p1.get() == p);
    assert(p1.use_count() == 1);

    assert(p3.get() == 0);

    p1 = p2;
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);
    assert(p1.use_count() == 1);
  }

  {
    shared_ptr<void> p1;

    std::auto_ptr<int> p2;

    p1 = p2;
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);
    assert(p1.use_count() == 1);

    int * p = new int;
    std::auto_ptr<int> p3(p);

    p1 = p3;
    assert(p1.get() == p);
    assert(p1.use_count() == 1);

    assert(p3.get() == 0);

    p1 = p2;
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);
    assert(p1.use_count() == 1);
  }


  {
    shared_ptr<X> p1;

    std::auto_ptr<Y> p2;

    p1 = p2;
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);
    assert(p1.use_count() == 1);
    assert(X::instances == 0);
    assert(Y::instances == 0);

    Y * p = new Y;
    std::auto_ptr<Y> p3(p);

    assert(X::instances == 1);
    assert(Y::instances == 1);

    p1 = p3;
    assert(p1.get() == p);
    assert(p1.use_count() == 1);
    assert(X::instances == 1);
    assert(Y::instances == 1);

    assert(p3.get() == 0);

    p1 = p2;
    assert(p1? false: true);
    assert(!p1);
    assert(p1.get() == 0);
    assert(p1.use_count() == 1);
    assert(X::instances == 0);
    assert(Y::instances == 0);
  }
}

void
  test()
{
  copy_assignment();
  conversion_assignment();
  auto_ptr_assignment();
}

} // namespace n_assignment

namespace n_reset
{

class incomplete;

incomplete * p0 = 0;

void
  deleter(incomplete *)
{
}

struct X
{
  static long instances;

  X()
  {
    ++instances;
  }

  ~X()
  {
    --instances;
  }

private:
  X(X const &);
  X & operator= (X const &);
};

long X::instances = 0;

void
  plain_reset()
{
  {
    shared_ptr<int> pi;
    pi.reset();
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 0);
  }

  {
    shared_ptr<int> pi(static_cast<int*>(0));
    pi.reset();
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 0);
  }

  {
    shared_ptr<int> pi(new int);
    pi.reset();
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 0);
  }

  {
    shared_ptr<incomplete> px;
    px.reset();
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 0);
  }

  {
    shared_ptr<incomplete> px(p0, deleter);
    px.reset();
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 0);
  }

  {
    shared_ptr<X> px;
    px.reset();
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 0);
  }

  {
    assert(X::instances == 0);
    shared_ptr<X> px(new X);
    assert(X::instances == 1);
    px.reset();
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 0);
    assert(X::instances == 0);
  }

  {
    shared_ptr<void> pv;
    pv.reset();
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 0);
  }

  {
    assert(X::instances == 0);
    shared_ptr<void> pv(new X);
    assert(X::instances == 1);
    pv.reset();
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 0);
    assert(X::instances == 0);
  }
}

struct A
{
  int dummy;
};

struct Y
  : public A
  , public virtual X
{
  static long instances;

  Y()
  {
    ++instances;
  }

  ~Y()
  {
    --instances;
  }

private:
  Y(Y const &);
  Y & operator= (Y const &);
};

long Y::instances = 0;

void
  pointer_reset()
{
  {
    shared_ptr<int> pi;

    pi.reset(static_cast<int*>(0));
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 1);
    assert(pi.unique());

    int * p = new int;
    pi.reset(p);
    assert(pi? true: false);
    assert(!!pi);
    assert(pi.get() == p);
    assert(pi.use_count() == 1);
    assert(pi.unique());

    pi.reset(static_cast<int*>(0));
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 1);
    assert(pi.unique());
  }

  {
    shared_ptr<X> px;

    px.reset(static_cast<X*>(0));
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 0);

    X * p = new X;
    px.reset(p);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == p);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 1);

    px.reset(static_cast<X*>(0));
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 0);
    assert(Y::instances == 0);

    Y * q = new Y;
    px.reset(q);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == q);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 1);
    assert(Y::instances == 1);

    px.reset(static_cast<Y*>(0));
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());
    assert(X::instances == 0);
    assert(Y::instances == 0);
  }

  {
    shared_ptr<void> pv;

    pv.reset(static_cast<X*>(0));
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(X::instances == 0);

    X * p = new X;
    pv.reset(p);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == p);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(X::instances == 1);

    pv.reset(static_cast<X*>(0));
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(X::instances == 0);
    assert(Y::instances == 0);

    Y * q = new Y;
    pv.reset(q);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == q);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(X::instances == 1);
    assert(Y::instances == 1);

    pv.reset(static_cast<Y*>(0));
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());
    assert(X::instances == 0);
    assert(Y::instances == 0);
  }
}

void
  * deleted = 0;

void
  deleter2(void * p)
{
  deleted = p;
}

void
  deleter_reset()
{
  {
    shared_ptr<int> pi;

    pi.reset(static_cast<int*>(0), deleter2);
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 1);
    assert(pi.unique());

    deleted = &pi;

    int m = 0;
    pi.reset(&m, deleter2);
    assert(deleted == 0);
    assert(pi? true: false);
    assert(!!pi);
    assert(pi.get() == &m);
    assert(pi.use_count() == 1);
    assert(pi.unique());

    pi.reset(static_cast<int*>(0), deleter2);
    assert(deleted == &m);
    assert(pi? false: true);
    assert(!pi);
    assert(pi.get() == 0);
    assert(pi.use_count() == 1);
    assert(pi.unique());

    pi.reset();
    assert(deleted == 0);
  }

  {
    shared_ptr<X> px;

    px.reset(static_cast<X*>(0), deleter2);
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());

    deleted = &px;

    X x;
    px.reset(&x, deleter2);
    assert(deleted == 0);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == &x);
    assert(px.use_count() == 1);
    assert(px.unique());

    px.reset(static_cast<X*>(0), deleter2);
    assert(deleted == &x);
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());

    Y y;
    px.reset(&y, deleter2);
    assert(deleted == 0);
    assert(px? true: false);
    assert(!!px);
    assert(px.get() == &y);
    assert(px.use_count() == 1);
    assert(px.unique());

    px.reset(static_cast<Y*>(0), deleter2);
    assert(deleted == &y);
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());

    px.reset();
    assert(deleted == 0);
  }

  {
    shared_ptr<void> pv;

    pv.reset(static_cast<X*>(0), deleter2);
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());

    deleted = &pv;

    X x;
    pv.reset(&x, deleter2);
    assert(deleted == 0);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == &x);
    assert(pv.use_count() == 1);
    assert(pv.unique());

    pv.reset(static_cast<X*>(0), deleter2);
    assert(deleted == &x);
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());

    Y y;
    pv.reset(&y, deleter2);
    assert(deleted == 0);
    assert(pv? true: false);
    assert(!!pv);
    assert(pv.get() == &y);
    assert(pv.use_count() == 1);
    assert(pv.unique());

    pv.reset(static_cast<Y*>(0), deleter2);
    assert(deleted == &y);
    assert(pv? false: true);
    assert(!pv);
    assert(pv.get() == 0);
    assert(pv.use_count() == 1);
    assert(pv.unique());

    pv.reset();
    assert(deleted == 0);
  }

  {
    shared_ptr<incomplete> px;

    px.reset(p0, deleter2);
    assert(px? false: true);
    assert(!px);
    assert(px.get() == 0);
    assert(px.use_count() == 1);
    assert(px.unique());

    deleted = &px;
    px.reset(p0, deleter2);
    assert(deleted == 0);
  }
}

void
  test()
{
  plain_reset();
  pointer_reset();
  deleter_reset();
}

} // namespace n_reset

namespace n_access
{

struct X
{
};

void
  test()
{
  {
    shared_ptr<X> px;
    assert(px.get() == 0);
    assert(px? false: true);
    assert(!px);

    assert(get_pointer(px) == px.get());
  }

  {
    shared_ptr<X> px(static_cast<X*>(0));
    assert(px.get() == 0);
    assert(px? false: true);
    assert(!px);

    assert(get_pointer(px) == px.get());
  }

  #if 0
  {
    shared_ptr<X> px(static_cast<X*>(0), checked_deleter<X>());
    assert(px.get() == 0);
    assert(px? false: true);
    assert(!px);

    assert(get_pointer(px) == px.get());
  }
  #endif  // 0

  {
    X * p = new X;
    shared_ptr<X> px(p);
    assert(px.get() == p);
    assert(px? true: false);
    assert(!!px);
    assert(&*px == px.get());
    assert(px.operator ->() == px.get());

    assert(get_pointer(px) == px.get());
  }

  #if 0
  {
    X * p = new X;
    shared_ptr<X> px(p, checked_deleter<X>());
    assert(px.get() == p);
    assert(px? true: false);
    assert(!!px);
    assert(&*px == px.get());
    assert(px.operator ->() == px.get());

    assert(get_pointer(px) == px.get());
  }
  #endif  // 0
}

} // namespace n_access

namespace n_use_count
{

struct X
{
};

void
  test()
{
  {
    shared_ptr<X> px(static_cast<X*>(0));
    assert(px.use_count() == 1);
    assert(px.unique());

    shared_ptr<X> px2(px);
    assert(px2.use_count() == 2);
    assert(!px2.unique());
    assert(px.use_count() == 2);
    assert(!px.unique());
  }

  {
    shared_ptr<X> px(new X);
    assert(px.use_count() == 1);
    assert(px.unique());

    shared_ptr<X> px2(px);
    assert(px2.use_count() == 2);
    assert(!px2.unique());
    assert(px.use_count() == 2);
    assert(!px.unique());
  }

  #if 0
  {
    shared_ptr<X> px(new X, checked_deleter<X>());
    assert(px.use_count() == 1);
    assert(px.unique());

    shared_ptr<X> px2(px);
    assert(px2.use_count() == 2);
    assert(!px2.unique());
    assert(px.use_count() == 2);
    assert(!px.unique());
  }
  #endif  // 0
}

} // namespace n_use_count

namespace n_swap
{

struct X
{
};

void
  test()
{
  {
    shared_ptr<X> px;
    shared_ptr<X> px2;

    px.swap(px2);

    assert(px.get() == 0);
    assert(px2.get() == 0);

    using std::swap;
    swap(px, px2);

    assert(px.get() == 0);
    assert(px2.get() == 0);
  }

  {
    X * p = new X;
    shared_ptr<X> px;
    shared_ptr<X> px2(p);
    shared_ptr<X> px3(px2);

    px.swap(px2);

    assert(px.get() == p);
    assert(px.use_count() == 2);
    assert(px2.get() == 0);
    assert(px3.get() == p);
    assert(px3.use_count() == 2);

    using std::swap;
    swap(px, px2);

    assert(px.get() == 0);
    assert(px2.get() == p);
    assert(px2.use_count() == 2);
    assert(px3.get() == p);
    assert(px3.use_count() == 2);
  }

  {
    X * p1 = new X;
    X * p2 = new X;
    shared_ptr<X> px(p1);
    shared_ptr<X> px2(p2);
    shared_ptr<X> px3(px2);

    px.swap(px2);

    assert(px.get() == p2);
    assert(px.use_count() == 2);
    assert(px2.get() == p1);
    assert(px2.use_count() == 1);
    assert(px3.get() == p2);
    assert(px3.use_count() == 2);

    using std::swap;
    swap(px, px2);

    assert(px.get() == p1);
    assert(px.use_count() == 1);
    assert(px2.get() == p2);
    assert(px2.use_count() == 2);
    assert(px3.get() == p2);
    assert(px3.use_count() == 2);
  }
}

} // namespace n_swap

namespace n_comparison
{

struct X
{
  int dummy;
};

struct Y
{
  int dummy2;
};

struct Z
  : public X
  , public virtual Y
{
};

void
  test()
{
  {
    shared_ptr<X> px;
    assert(px == px);
    assert(!(px != px));
    assert(!(px < px));

    shared_ptr<X> px2;

    assert(px.get() == px2.get());
    assert(px == px2);
    assert(!(px != px2));
    assert(!(px < px2 && px2 < px));
  }

  {
    shared_ptr<X> px;
    shared_ptr<X> px2(px);

    assert(px2 == px2);
    assert(!(px2 != px2));
    assert(!(px2 < px2));

    assert(px.get() == px2.get());
    assert(px == px2);
    assert(!(px != px2));
    assert(!(px < px2 && px2 < px));
  }

  {
    shared_ptr<X> px;
    shared_ptr<X> px2(new X);

    assert(px2 == px2);
    assert(!(px2 != px2));
    assert(!(px2 < px2));

    assert(px.get() != px2.get());
    assert(px != px2);
    assert(!(px == px2));
    assert(px < px2 || px2 < px);
    assert(!(px < px2 && px2 < px));
  }

  {
    shared_ptr<X> px(new X);
    shared_ptr<X> px2(new X);

    assert(px.get() != px2.get());
    assert(px != px2);
    assert(!(px == px2));
    assert(px < px2 || px2 < px);
    assert(!(px < px2 && px2 < px));
  }

  {
    shared_ptr<X> px(new X);
    shared_ptr<X> px2(px);

    assert(px2 == px2);
    assert(!(px2 != px2));
    assert(!(px2 < px2));

    assert(px.get() == px2.get());
    assert(px == px2);
    assert(!(px != px2));
    assert(!(px < px2 || px2 < px));
  }

  {
    shared_ptr<X> px(new X);
    shared_ptr<Y> py(new Y);
    shared_ptr<Z> pz(new Z);

    assert(px.get() != pz.get());
    assert(px != pz);
    assert(!(px == pz));

    assert(py.get() != pz.get());
    assert(py != pz);
    assert(!(py == pz));

    assert(px < py || py < px);
    assert(px < pz || pz < px);
    assert(py < pz || pz < py);

    assert(!(px < py && py < px));
    assert(!(px < pz && pz < px));
    assert(!(py < pz && pz < py));

    shared_ptr<void> pvx(px);

    assert(pvx == pvx);
    assert(!(pvx != pvx));
    assert(!(pvx < pvx));

    shared_ptr<void> pvy(py);
    shared_ptr<void> pvz(pz);

    assert(pvx < pvy || pvy < pvx);
    assert(pvx < pvz || pvz < pvx);
    assert(pvy < pvz || pvz < pvy);

    assert(!(pvx < pvy && pvy < pvx));
    assert(!(pvx < pvz && pvz < pvx));
    assert(!(pvy < pvz && pvz < pvy));
  }

  {
    shared_ptr<Z> pz(new Z);
    shared_ptr<X> px(pz);

    assert(px == px);
    assert(!(px != px));
    assert(!(px < px));

    shared_ptr<Y> py(pz);

    assert(px.get() == pz.get());
    assert(px == pz);
    assert(!(px != pz));

    assert(py.get() == pz.get());
    assert(py == pz);
    assert(!(py != pz));

    assert(!(px < py || py < px));
    assert(!(px < pz || pz < px));
    assert(!(py < pz || pz < py));

    shared_ptr<void> pvx(px);
    shared_ptr<void> pvy(py);
    shared_ptr<void> pvz(pz);

    // pvx and pvy aren't equal...
    assert(pvx.get() != pvy.get());
    assert(pvx != pvy);
    assert(!(pvx == pvy));

    // ... but they share ownership ...
    assert(!(pvx < pvy || pvy < pvx));

    // ... with pvz
    assert(!(pvx < pvz || pvz < pvx));
    assert(!(pvy < pvz || pvz < pvy));
  }
}

} // namespace n_comparison

namespace n_static_cast
{

struct X
{
};

struct Y
  : public X
{ };

void
  test()
{
  {
    shared_ptr<void> pv;

    shared_ptr<int> pi = static_pointer_cast<int>(pv);
    assert(pi.get() == 0);

    shared_ptr<X> px = static_pointer_cast<X>(pv);
    assert(px.get() == 0);
  }

  {
    shared_ptr<int> pi(new int);
    shared_ptr<void> pv(pi);

    shared_ptr<int> pi2 = static_pointer_cast<int>(pv);
    assert(pi.get() == pi2.get());
    assert(!(pi < pi2 || pi2 < pi));
    assert(pi.use_count() == 3);
    assert(pv.use_count() == 3);
    assert(pi2.use_count() == 3);
  }

  {
    shared_ptr<X> px(new X);
    shared_ptr<void> pv(px);

    shared_ptr<X> px2 = static_pointer_cast<X>(pv);
    assert(px.get() == px2.get());
    assert(!(px < px2 || px2 < px));
    assert(px.use_count() == 3);
    assert(pv.use_count() == 3);
    assert(px2.use_count() == 3);
  }

  {
    shared_ptr<X> px(new Y);

    shared_ptr<Y> py = static_pointer_cast<Y>(px);
    assert(px.get() == py.get());
    assert(px.use_count() == 2);
    assert(py.use_count() == 2);

    shared_ptr<X> px2(py);
    assert(!(px < px2 || px2 < px));
  }
}

} // namespace n_static_cast

namespace n_const_cast
{

struct X;

void
  test()
{
  {
    shared_ptr<void const volatile> px;

    shared_ptr<void> px2 = const_pointer_cast<void>(px);
    assert(px2.get() == 0);
  }

  {
    shared_ptr<int const volatile> px;

    shared_ptr<int> px2 = const_pointer_cast<int>(px);
    assert(px2.get() == 0);
  }

  {
    shared_ptr<X const volatile> px;

    shared_ptr<X> px2 = const_pointer_cast<X>(px);
    assert(px2.get() == 0);
  }

  {
    shared_ptr<void const volatile> px(new int);

    shared_ptr<void> px2 = const_pointer_cast<void>(px);
    assert(px.get() == px2.get());
    assert(!(px < px2 || px2 < px));
    assert(px.use_count() == 2);
    assert(px2.use_count() == 2);
  }

  {
    shared_ptr<int const volatile> px(new int);

    shared_ptr<int> px2 = const_pointer_cast<int>(px);
    assert(px.get() == px2.get());
    assert(!(px < px2 || px2 < px));
    assert(px.use_count() == 2);
    assert(px2.use_count() == 2);
  }
}

} // namespace n_const_cast

namespace n_dynamic_cast
{

struct V
{
  virtual ~V() {}
};

struct W
  : public V
{ };

void
  test()
{
  {
    shared_ptr<V> pv;
    shared_ptr<W> pw = dynamic_pointer_cast<W>(pv);
    assert(pw.get() == 0);
  }

  {
    shared_ptr<V> pv(static_cast<V*>(0));

    shared_ptr<W> pw = dynamic_pointer_cast<W>(pv);
    assert(pw.get() == 0);

    shared_ptr<V> pv2(pw);
    assert(pv < pv2 || pv2 < pv);
  }

  {
    shared_ptr<V> pv(static_cast<W*>(0));

    shared_ptr<W> pw = dynamic_pointer_cast<W>(pv);
    assert(pw.get() == 0);

    shared_ptr<V> pv2(pw);
    assert(pv < pv2 || pv2 < pv);
  }

  {
    shared_ptr<V> pv(new V);

    shared_ptr<W> pw = dynamic_pointer_cast<W>(pv);
    assert(pw.get() == 0);

    shared_ptr<V> pv2(pw);
    assert(pv < pv2 || pv2 < pv);
  }

  {
    shared_ptr<V> pv(new W);

    shared_ptr<W> pw = dynamic_pointer_cast<W>(pv);
    assert(pw.get() == pv.get());
    assert(pv.use_count() == 2);
    assert(pw.use_count() == 2);

    shared_ptr<V> pv2(pw);
    assert(!(pv < pv2 || pv2 < pv));
  }
}

} // namespace n_dynamic_cast

namespace n_map
{

struct X
{
};

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

  std::map< shared_ptr<void>, long > m;

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
    for(std::map< shared_ptr<void>, long >::iterator i = m.begin(); i != m.end(); ++i)
    {
      assert(i->first.use_count() == i->second + 1);
    }
  }
}

} // namespace n_map

namespace n_transitive
{

struct X
{
  X(): next() {}
  shared_ptr<X> next;
};

void
  test()
{
  shared_ptr<X> p(new X);
  p->next = shared_ptr<X>(new X);
  assert(!p->next->next);
  p = p->next;
  assert(!p->next);
}

} // namespace n_transitive

#if 0
namespace n_report_1
{

class foo
{
public:

  foo(): m_self(this)
  { }

  void suicide()
  { m_self.reset(); }

private:
  shared_ptr<foo> m_self;
};

void
  test()
{
  foo * foo_ptr = new foo;
  foo_ptr->suicide();
}

} // namespace n_report_1
#endif  // 0

// Test case by Per Kristensen
namespace n_report_2
{

class foo
{
public:

  void setWeak(shared_ptr<foo> s)
  {
    w = s;
  }

private:

  weak_ptr<foo> w;
};

class deleter
{
public:

  deleter(): lock(0)
  {
  }

  ~deleter()
  {
    assert(lock == 0);
  }

  void operator() (foo * p)
  {
    ++lock;
    delete p;
    --lock;
  }

private:

  int lock;
};

void
  test()
{
  shared_ptr<foo> s(new foo, deleter());
  s->setWeak(s);
  s.reset();
}

} // namespace n_report_2

namespace n_spt_incomplete
{

class file;

shared_ptr<file> fopen(char const * name, char const * mode);
void
  fread(shared_ptr<file> f, void * data, long size);

int file_instances = 0;

void
  test()
{
  assert(file_instances == 0);

  {
    shared_ptr<file> pf = fopen("name", "mode");
    assert(file_instances == 1);
    fread(pf, 0, 17041);
  }

  assert(file_instances == 0);
}

} // namespace n_spt_incomplete

namespace n_spt_pimpl
{

class file
{
private:
  class impl;
  shared_ptr<impl> pimpl_;

public:

  file(char const * name, char const * mode);

  // compiler generated members are fine and useful

  void read(void * data, long size);

  long total_size() const;
};

int file_instances = 0;

void
  test()
{
  assert(file_instances == 0);

  {
    file f("name", "mode");
    assert(file_instances == 1);
    f.read(0, 152);

    file f2(f);
    assert(file_instances == 1);
    f2.read(0, 894);

    assert(f.total_size() == 152+894);

    {
      file f3("name2", "mode2");
      assert(file_instances == 2);
    }

    assert(file_instances == 1);
  }

  assert(file_instances == 0);
}

} // namespace n_spt_pimpl

namespace n_spt_abstract
{

class X
{
public:

  virtual void f(int) = 0;
  virtual int g() = 0;

protected:

  ~X() {}
};

shared_ptr<X> createX();

int X_instances = 0;

void
  test()
{
  assert(X_instances == 0);

  {
    shared_ptr<X> px = createX();

    assert(X_instances == 1);

    px->f(18);
    px->f(152);

    assert(px->g() == 170);
  }

  assert(X_instances == 0);
}

} // namespace n_spt_abstract

namespace n_spt_preventing_delete
{

int X_instances = 0;

class X
{
private:
  X()
  {
    ++X_instances;
  }

  ~X()
  {
    --X_instances;
  }

  class deleter;
  friend class deleter;

  class deleter
  {
  public:

    void operator()(X * p) { delete p; }
  };

public:

  static shared_ptr<X> create()
  {
    shared_ptr<X> px(new X, X::deleter());
    return px;
  }
};

void
  test()
{
  assert(X_instances == 0);

  {
    shared_ptr<X> px = X::create();
    assert(X_instances == 1);
  }

  assert(X_instances == 0);
}

} // namespace n_spt_preventing_delete

namespace n_spt_array
{

int X_instances = 0;

struct X
{
  X()
  {
    ++X_instances;
  }

  ~X()
  {
    --X_instances;
  }
};

void
  test()
{
  assert(X_instances == 0);

  #if 0
  {
    shared_ptr<X> px(new X[4], checked_array_deleter<X>());
    assert(X_instances == 4);
  }
  #endif  // 0

  assert(X_instances == 0);
}

} // namespace n_spt_array

namespace n_spt_static
{

class X
{
public:

  X()
  {
  }

private:
  void operator delete(void *)
  {
    throw "n_spt_static::X::operator delete() called.";
  }
};

struct null_deleter
{
  void operator()(void const *) const
  {
  }
};

static X x;

void
  test()
{
  shared_ptr<X> px(&x, null_deleter());
}

} // namespace n_spt_static

namespace n_spt_intrusive
{

int X_instances = 0;

struct X
{
  long count;

  X(): count(0)
  {
    ++X_instances;
  }

  ~X()
  {
    --X_instances;
  }
};

void
  intrusive_ptr_add_ref(X * p)
{
  ++p->count;
}

void
  intrusive_ptr_release(X * p)
{
  if(--p->count == 0) delete p;
}

template< class T >
  struct intrusive_deleter
{
  void operator()(T * p)
  {
    if(p != 0) intrusive_ptr_release(p);
  }
};

shared_ptr<X> make_shared_from_intrusive(X * p)
{
  if(p != 0) intrusive_ptr_add_ref(p);
  shared_ptr<X> px(p, intrusive_deleter<X>());
  return px;
}

void
  test()
{
  assert(X_instances == 0);

  {
    X * p = new X;
    assert(X_instances == 1);
    assert(p->count == 0);
    shared_ptr<X> px = make_shared_from_intrusive(p);
    assert(px.get() == p);
    assert(p->count == 1);
    shared_ptr<X> px2(px);
    assert(px2.get() == p);
    assert(p->count == 1);
  }

  assert(X_instances == 0);
}

} // namespace n_spt_intrusive

namespace n_spt_another_sp
{

template< class T >
  class another_ptr
    : private shared_ptr<T>
{
private:
  typedef shared_ptr<T> base_type;

public:

  explicit another_ptr(T * p = 0): base_type(p)
  {
  }

  void reset()
  {
    base_type::reset();
  }

  T * get() const
  {
    return base_type::get();
  }
};

class event_handler
{
public:

  virtual ~event_handler() {}
  virtual void begin() = 0;
  virtual void handle(int event) = 0;
  virtual void end() = 0;
};

int begin_called = 0;
int handle_called = 0;
int end_called = 0;

class event_handler_impl
  : public event_handler
{
public:

  virtual void begin()
  {
    ++begin_called;
  }

  virtual void handle(int event)
  {
    handle_called = event;
  }

  virtual void end()
  {
    ++end_called;
  }
};

another_ptr<event_handler> get_event_handler()
{
  another_ptr<event_handler> p(new event_handler_impl);
  return p;
}

shared_ptr<event_handler> current_handler;

void
  install_event_handler(shared_ptr<event_handler> p)
{
  p->begin();
  current_handler = p;
}

void
  handle_event(int event)
{
  current_handler->handle(event);
}

void
  remove_event_handler()
{
  current_handler->end();
  current_handler.reset();
}

template< class P >
  class smart_pointer_deleter
{
private:
  P p_;

public:

  smart_pointer_deleter(P const & p): p_(p)
  {
  }

  void operator()(void const *)
  {
    p_.reset();
  }
};

void
  test()
{
  another_ptr<event_handler> p = get_event_handler();

  shared_ptr<event_handler> q(p.get(), smart_pointer_deleter< another_ptr<event_handler> >(p));

  p.reset();

  assert(begin_called == 0);

  install_event_handler(q);

  assert(begin_called == 1);

  assert(handle_called == 0);

  handle_event(17041);

  assert(handle_called == 17041);

  assert(end_called == 0);

  remove_event_handler();

  assert(end_called == 1);
}

} // namespace n_spt_another_sp

#if 0
namespace n_spt_shared_from_this
{

class X
{
public:

  virtual void f() = 0;

protected:

  ~X() {}
};

class Y
{
public:

  virtual shared_ptr<X> getX() = 0;

protected:

  ~Y() {}
};

class impl
  : public X, public Y
{
private:
  weak_ptr<impl> weak_this;

  impl(impl const &);
  impl & operator=(impl const &);

  impl() {}

public:

  static shared_ptr<impl> create()
  {
    shared_ptr<impl> pi(new impl);
    pi->weak_this = pi;
    return pi;
  }

  virtual void f() {}

  virtual shared_ptr<X> getX()
  {
    shared_ptr<X> px = weak_this.lock();
    return px;
  }
};

void
  test()
{
  shared_ptr<Y> py = impl::create();
  assert(py.get() != 0);
  assert(py.use_count() == 1);

  shared_ptr<X> px = py->getX();
  assert(px.get() != 0);
  assert(py.use_count() == 2);

  shared_ptr<Y> py2 = dynamic_pointer_cast<Y>(px);
  assert(py.get() == py2.get());
  assert(!(py < py2 || py2 < py));
  assert(py.use_count() == 3);
}

} // namespace n_spt_shared_from_this
#endif  // 0

namespace n_spt_wrap
{

void
  test()
{
}

} // namespace n_spt_wrap

int main()
{
  n_element_type::test();
  n_constructors::test();
  n_assignment::test();
  n_reset::test();
  n_access::test();
  n_use_count::test();
  n_swap::test();
  n_comparison::test();
  n_static_cast::test();
  n_const_cast::test();
  n_dynamic_cast::test();

  n_map::test();

  n_transitive::test();
  #if 0
  n_report_1::test();
  #endif  // 0
  n_report_2::test();

  n_spt_incomplete::test();
  n_spt_pimpl::test();
  n_spt_abstract::test();
  n_spt_preventing_delete::test();
  n_spt_array::test();
  n_spt_static::test();
  n_spt_intrusive::test();
  n_spt_another_sp::test();
  //n_spt_shared_from_this::test();
  n_spt_wrap::test();

  return 0;
}

namespace n_spt_incomplete
{

class file
{
public:

  file(): fread_called(false)
  {
    ++file_instances;
  }

  ~file()
  {
    assert(fread_called);
    --file_instances;
  }

  bool fread_called;
};

shared_ptr<file> fopen(char const *, char const *)
{
  shared_ptr<file> pf(new file);
  return pf;
}

void
  fread(shared_ptr<file> pf, void *, long)
{
  pf->fread_called = true;
}

} // namespace n_spt_incomplete

namespace n_spt_pimpl
{

class file::impl
{
private:
  impl(impl const &);
  impl & operator=(impl const &);

  long total_size_;

public:

  impl(char const *, char const *): total_size_(0)
  {
    ++file_instances;
  }

  ~impl()
  {
    --file_instances;
  }

  void read(void *, long size)
  {
    total_size_ += size;
  }

  long total_size() const
  {
    return total_size_;
  }
};

file::file(char const * name, char const * mode): pimpl_(new impl(name, mode))
{
}

void
  file::read(void * data, long size)
{
  pimpl_->read(data, size);
}

long file::total_size() const
{
  return pimpl_->total_size();
}

} // namespace n_spt_pimpl

namespace n_spt_abstract
{

class X_impl
  : public X
{
private:
  X_impl(X_impl const &);
  X_impl & operator=(X_impl const &);

  int n_;

public:

  X_impl(): n_(0)
  {
    ++X_instances;
  }

  ~X_impl()
  {
    --X_instances;
  }

  virtual void f(int n)
  {
    n_ += n;
  }

  virtual int g()
  {
    return n_;
  }
};

shared_ptr<X> createX()
{
  shared_ptr<X> px(new X_impl);
  return px;
}

} // namespace n_spt_abstract
