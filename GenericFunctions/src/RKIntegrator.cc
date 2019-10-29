// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/RKIntegrator.hh"
#include "CLHEP/GenericFunctions/AdaptiveRKStepper.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <climits>
#include <stdexcept>
namespace Genfun {
FUNCTION_OBJECT_IMP(RKIntegrator::RKFunction)

RKIntegrator::RKFunction::RKFunction(RKData *data, unsigned int index)
  :_data(data),
   _index(index)
{
  _data->ref();
}

RKIntegrator::RKFunction::~RKFunction() 
{
  _data->unref();
}

RKIntegrator::RKFunction::RKFunction(const RKIntegrator::RKFunction & right)
  :AbsFunction(right),
   _data(right._data),
   _index(right._index)
{
  _data->ref();
}


double RKIntegrator::RKFunction::operator() (double t) const {
  if (t<0) return 0;
  if (!_data->_locked) _data->lock();

  // Do this first, thereafter, just read the cache
  _data->recache();
  

  // If the cache is empty, make an entry for t=0;
  size_t nvar = _data->_startingValParameter.size();
  if (_data->_fx.empty()) {
    RKData::Data d(nvar);
    d.time=0;
    Argument arg(nvar);
    for (size_t f=0;f<nvar;f++) {
      d.variable[f]=_data->_startingValParameterCache[f];
      arg[f]=d.variable[f];
    }
    _data->_fx.insert(d);
  }

  if (t==0) return (*_data->_fx.begin()).variable[_index];

  RKData::Data dt(nvar);
  dt.time=t;
  std::set<RKData::Data>::iterator l =_data->_fx.lower_bound(dt);

  // We did find an exact value (measure 0), just return it. 
  if (l!=_data->_fx.end() && (*l).time==t) {
    return (*l).variable[_index];
  }

  else {
    std::set<RKData::Data>::iterator u =_data->_fx.upper_bound(dt);
    
    while (u==_data->_fx.end()) {
      u--;
      RKData::Data newData(nvar);;
      _data->_stepper->step(_data,*u, newData, 0);
      _data->_fx.insert(l,newData);
      if (newData.time==t) return newData.variable[_index];
      u = _data->_fx.upper_bound(dt);
    }
    u--;
    _data->_stepper->step(_data,*u, dt, t);
    return dt.variable[_index];
  }
}


RKIntegrator::RKData::RKData():_locked(false) {
}

RKIntegrator::RKData::~RKData() {
  for (size_t i=0;i<_startingValParameter.size();i++) delete _startingValParameter[i];
  for (size_t i=0;i<_controlParameter.size();i++)     delete _controlParameter[i];
  for (size_t i=0;i<_diffEqn.size();  i++)            delete _diffEqn[i];
  delete _stepper;
}

RKIntegrator::RKIntegrator(const RKIntegrator::RKStepper *stepper) :
  _data(new RKData())
{
  if (stepper) _data->_stepper=stepper->clone();
  else _data->_stepper= new AdaptiveRKStepper();
  _data->ref();
}

RKIntegrator::~RKIntegrator() {
  _data->unref();
  for (size_t i=0;i<_fcn.size();i++) delete _fcn[i];
}

Parameter * RKIntegrator::addDiffEquation(const AbsFunction * diffEquation,
					  const std::string &variableName,
					  double defStartingValue,
					  double defValueMin,
					  double defValueMax) {
  Parameter *par = new Parameter(variableName, defStartingValue, defValueMin, defValueMax);
  _data->_startingValParameter.push_back(par);
  _data->_diffEqn.push_back(diffEquation->clone());
  _data->_startingValParameterCache.push_back(defStartingValue);
  _fcn.push_back(new RKFunction(_data,_fcn.size()));
  return par;
}





Parameter * RKIntegrator::createControlParameter (const std::string & variableName,
						  double defStartingValue,
						  double startingValueMin,
						  double startingValueMax) {

  Parameter *par = new Parameter(variableName, defStartingValue, startingValueMin, startingValueMax);
  _data->_controlParameter.push_back(par);
  _data->_controlParameterCache.push_back(defStartingValue);
  return par;

}



const RKIntegrator::RKFunction * RKIntegrator::getFunction(unsigned int i) const {
  return _fcn[i];
}



void RKIntegrator::RKData::lock() {
  if (!_locked) {
    unsigned int size = _diffEqn.size();
    for (size_t i=0;i<size;i++) {
      if (!(_diffEqn[i]->dimensionality()==size)) throw std::runtime_error("Runtime error in RKIntegrator");
    }
    _locked=true;
  }
}



void RKIntegrator::RKData::recache() {

  bool stale=false;
  if (!stale) {
    for (size_t p=0;p<_startingValParameter.size();p++) {
      if (_startingValParameter[p]->getValue()!=_startingValParameterCache[p]) {
	_startingValParameterCache[p]=_startingValParameter[p]->getValue();
	stale=true;
	break;
      }
    }
  }

  if (!stale) {
    for (size_t p=0;p<_controlParameter.size();p++) {
      if (_controlParameter[p]->getValue()!=_controlParameterCache[p]) {
	_controlParameterCache[p]=_controlParameter[p]->getValue();
	stale=true;
	break;
      }
    }
  }
  
  if (stale) {
    _fx.erase(_fx.begin(),_fx.end());
  }
  
}



RKIntegrator::RKStepper::~RKStepper(){}


} // namespace Genfun
