// -*- C++ -*-
// $Id: Argument.hh,v 1.2 2003/09/06 14:04:13 boudreau Exp $
#ifndef __ARGUMENT_H_
#define __ARGUMENT_H_
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
// Here is an argument

namespace Genfun {

  /**
   * @author
   * @ingroup genfun
   */
  class Argument {

  public:

    // Constructor
    Argument(int ndim=0);

    // Copy Constructor
    Argument( const Argument &);

    // Assignment operator
    const Argument & operator=(const Argument &);

    // Destructor:
    ~Argument();

    // Set/Get Value
    double & operator[] (int I);
    const double & operator[] (int i) const; 

    // Get the dimensions
    unsigned int dimension() const;

  private:

    std::vector<double> *_data;

    friend std::ostream & operator << (std::ostream & o, const Argument & a);

  };

  inline Argument::Argument(const Argument & right):
    _data(new std::vector<double>(*(right._data))){
  }

  inline const Argument & Argument::operator=( const Argument & right) {
    if (this != &right) {
      delete _data;
      _data=NULL;
      _data = new std::vector<double>(*(right._data));
    }
    return *this;
  }

  inline unsigned int Argument::dimension() const {
    return _data->size();
  }

  inline double & Argument::operator[] (int i) {
    return (*_data)[i];
  } 

  inline const double & Argument::operator[] (int i) const {
    return (*_data)[i];
  } 

  inline Argument::Argument(int ndim): _data(new std::vector<double>(ndim)) {
  }

  inline Argument::~Argument() {
    delete _data;
  }


  inline std::ostream & operator << (std::ostream & os, const Argument & a) {
    std::ostream_iterator<double> oi(os,",");
    std::copy (a._data->begin(),a._data->end(),oi);
    return os;
  }
} // namespace Genfun
#endif
