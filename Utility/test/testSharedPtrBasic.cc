// ======================================================================
//
// Test compilability and basic functionality of Utility/memory.h
//
// Author:  W. E. Brown, 2010-03-19, adapted from the boost library's
// shared_ptr and related functionality whose internal attributions bear
// the following various notices:
//
//   Copyright (c) 2001, 2002 Peter Dimov and Multi Media Ltd.
//   Distributed under the Boost Software License, Version 1.0.
//   See http://www.boost.org/LICENSE_1_0.txt
//
// ======================================================================


#include "CLHEP/Utility/noncopyable.h"
#include "CLHEP/Utility/memory.h"

#include <cassert>


using namespace CLHEP;
using CLHEP::shared_ptr;


int cnt = 0;

struct X : public noncopyable {
  X() { ++cnt; }
  ~X() { --cnt; }  // virtual destructor deliberately omitted
  virtual int id() const { return 1; }
};  // X

struct Y: public X
{
  Y() { ++cnt; }
  ~Y() { --cnt; }
  virtual int id() const { return 2; }
};  // Y

int * get_object()
{ return &++cnt; }

void release_object(int * p)
{
  assert(p == &cnt);
  --cnt;
}

template< class T >
 void test_is_X(shared_ptr<T> const & p)
{
  assert(p->id() == 1);
  assert((*p).id() == 1);
}

template< class T >
 void test_is_X(weak_ptr<T> const & p)
{
  assert(p.get() != 0);
  assert(p.get()->id() == 1);
}

template< class T >
 void test_is_Y(shared_ptr<T> const & p)
{
  assert(p->id() == 2);
  assert((*p).id() == 2);
}

template< class T >
 void test_is_Y(weak_ptr<T> const & p)
{
  shared_ptr<T> q = p.lock();
  assert(q.get() != 0);
  assert(q->id() == 2);
}

template< class T >
 void test_eq(T const & a, T const & b)
{
  assert(a == b);
  assert(!(a != b));
  assert(!(a < b));
  assert(!(b < a));
}

template< class T >
 void test_ne(T const & a, T const & b)
{
  assert(!(a == b));
  assert(a != b);
  assert(a < b || b < a);
  assert(!(a < b && b < a));
}

template< class T, class U >
 void test_shared(weak_ptr<T> const & a, weak_ptr<U> const & b)
{
  assert(!(a < b));
  assert(!(b < a));
}

template< class T, class U >
 void test_nonshared(weak_ptr<T> const & a, weak_ptr<U> const & b)
{
  assert(a < b || b < a);
  assert(!(a < b && b < a));
}

template< class T, class U >
 void test_eq2(T const & a, U const & b)
{
  assert(a == b);
  assert(!(a != b));
}

template< class T, class U >
 void test_ne2(T const & a, U const & b)
{
  assert(!(a == b));
  assert(a != b);
}

template< class T >
 void test_is_zero(shared_ptr<T> const & p)
{
  assert(!p);
  assert(p.get() == 0);
}

template< class T >
 void test_is_nonzero(shared_ptr<T> const & p)
{
  // p? true: false is used to test p in a boolean context.
  // assert(p) is not guaranteed to test the conversion,
  // as the macro might test !!p instead.
  assert(p? true: false);
  assert(p.get() != 0);
}

int main()
{

  {
    shared_ptr<X> p(new Y);
    shared_ptr<X> p2(new X);

    test_is_nonzero(p);
    test_is_nonzero(p2);
    test_is_Y(p);
    test_is_X(p2);
    test_ne(p, p2);

    {
      shared_ptr<X> q(p);
      test_eq(p, q);
    }

    shared_ptr<Y> p3 = dynamic_pointer_cast<Y>(p);
    shared_ptr<Y> p4 = dynamic_pointer_cast<Y>(p2);

    test_is_nonzero(p3);
    test_is_zero(p4);

    assert(p.use_count() == 2);
    assert(p2.use_count() == 1);
    assert(p3.use_count() == 2);

    test_is_Y(p3);
    test_eq2(p, p3);
    test_ne2(p2, p4);

    shared_ptr<void> p5(p);

    test_is_nonzero(p5);
    test_eq2(p, p5);

    weak_ptr<X> wp1(p2);

    assert(!wp1.expired());
    assert(wp1.use_count() != 0);

    p.reset();
    p2.reset();
    p3.reset();
    p4.reset();

    test_is_zero(p);
    test_is_zero(p2);
    test_is_zero(p3);
    test_is_zero(p4);

    assert(p5.use_count() == 1);

    assert(wp1.expired());
    assert(wp1.use_count() == 0);

    try
    {
      shared_ptr<X> sp1(wp1);
      throw "shared_ptr<X> sp1(wp1) failed to throw";
    }
    catch(bad_weak_ptr const &)
    {
    }

    test_is_zero(wp1.lock());

    weak_ptr<X> wp2 = static_pointer_cast<X>(p5);

    assert(wp2.use_count() == 1);
    test_is_Y(wp2);
    test_nonshared(wp1, wp2);

    // Scoped to not affect the subsequent use_count() tests.
    {
      shared_ptr<X> sp2(wp2);
      test_is_nonzero(wp2.lock());
    }

    weak_ptr<Y> wp3 = dynamic_pointer_cast<Y>(wp2.lock());

    assert(wp3.use_count() == 1);
    test_shared(wp2, wp3);

    weak_ptr<X> wp4(wp3);

    assert(wp4.use_count() == 1);
    test_shared(wp2, wp4);

    wp1 = p2;
    test_is_zero(wp1.lock());

    wp1 = p4;
    wp1 = wp3;
    wp1 = wp2;

    assert(wp1.use_count() == 1);
    test_shared(wp1, wp2);

    weak_ptr<X> wp5;

    bool b1 = wp1 < wp5;
    bool b2 = wp5 < wp1;

    p5.reset();

    assert(wp1.use_count() == 0);
    assert(wp2.use_count() == 0);
    assert(wp3.use_count() == 0);

    // Test operator< stability for std::set< weak_ptr<> >
    // Thanks to Joe Gottman for pointing this out

    assert(b1 == (wp1 < wp5));
    assert(b2 == (wp5 < wp1));

    {
      // note that both get_object and release_object deal with int*
      shared_ptr<void> p6(get_object(), release_object);
    }

  }

  assert(cnt == 0);

  return 0;

}  // main()
