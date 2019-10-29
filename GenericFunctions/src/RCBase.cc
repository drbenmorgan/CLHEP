#include "CLHEP/GenericFunctions/RCBase.hh"
namespace Genfun {
RCBase::RCBase()
      : _count(0)
{
}


RCBase::~RCBase()
{
}



void RCBase::ref() const
{
  _count++;
}

void RCBase::unref() const
{
  if (!_count)
    {

    }
  else
    {
      _count--;
      if (!_count)
	delete this;
    }
}

unsigned int RCBase::refCount() const
{
  return _count;
}

} // namespace Genfun
