// -*- C++ -*-
// $Id:
//------------------RCBase--------------------------------------------------//
//                                                                          //
// Class RCBase                                                             //
// Joe Boudreau                                                             // 
// Base class for reference counting                                        //
//                                                                          //
//--------------------------------------------------------------------------//
#ifndef RCBase_h
#define RCBase_h 1
namespace Genfun {
  /**
   * @author
   * @ingroup genfun
   */
  class RCBase 
  {
    
  public:
    
    RCBase();
    
    
    void ref() const;
    
    void unref() const;
    
    unsigned int refCount() const;
    
    
  protected:
    
    virtual ~RCBase();
    
  private:
    
    RCBase(const RCBase &right);
    
    const RCBase & operator=(const RCBase &right);
    
    mutable unsigned short int _count;
    
    
    
  };
  
  
  
}


#endif


