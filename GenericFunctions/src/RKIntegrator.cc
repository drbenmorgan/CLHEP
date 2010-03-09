// -*- C++ -*-
// $Id: 
#include "CLHEP/GenericFunctions/RKIntegrator.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include <assert.h>
#include <climits>
#include <cmath>      // for pow()

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
  :_data(right._data),
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


  RKData::Data dt(nvar);
  dt.time=t;
  std::set<RKData::Data>::iterator s=_data->_fx.lower_bound(dt);
  if (dt==(*s)) {
    // Then, there is nothing to do.  Don't touch the
    // list.  Just get the variable:
    return (*s).variable[_index];
  }
  else {

    // Back up:
    assert (s!=_data->_fx.begin());
    s--;

    //std::vector<double> errors;
    rkstep(*s, dt);
    _data->_fx.insert(s,dt);

    return dt.variable[_index];
  }
}


RKIntegrator::RKData::RKData():_locked(false) {
}

RKIntegrator::RKData::~RKData() {
  for (size_t i=0;i<_startingValParameter.size();i++) delete _startingValParameter[i];
  for (size_t i=0;i<_controlParameter.size();i++)     delete _controlParameter[i];
  for (size_t i=0;i<_diffEqn.size();  i++)            delete _diffEqn[i];
}

RKIntegrator::RKIntegrator() :
  _data(new RKData())
{
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
      assert (_diffEqn[i]->dimensionality()==size);
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



void RKIntegrator::RKFunction::rk4(const RKIntegrator::RKData::Data & s, RKIntegrator::RKData::Data & d)  const {

  double h = d.time - s.time;
  double h2 = h/2.0;
  double h6 = h/6.0;
  unsigned int nv = s.variable.size();
  Argument y(nv), yt(nv), dydx(nv), dt(nv), dm(nv);
  for (size_t v=0;v<nv;v++) { y[v]=s.variable[v];}
  
  if (!s.dcalc) {
    for (size_t v=0;v<nv;v++) {dydx[v]=(*_data->_diffEqn[v])(y);}
    for (size_t v=0;v<nv;v++) {s.firstDerivative[v]=dydx[v];}
    s.dcalc=true;
  }
  else {
    for (size_t v=0;v<nv;v++) { dydx[v] = s.firstDerivative[v];}
  }    


  for (size_t v=0;v<nv;v++) { yt[v] = y[v] + h2*dt[v];}                   // First step.
  for (size_t v=0;v<nv;v++) { dt[v] = (*_data->_diffEqn[v])(yt);}         // Second step.
  for (size_t v=0;v<nv;v++) { yt[v] = y[v] + h2*dt[v];}
  for (size_t v=0;v<nv;v++) { dm[v] = (*_data->_diffEqn[v])(yt);}         // Third step
  for (size_t v=0;v<nv;v++) { 
    yt[v] = y[v]+h*dm[v];
    dm[v] += dt[v];
  }
  for (size_t v=0;v<nv;v++) { dt[v] = (*_data->_diffEqn[v])(yt);}         // Fourth step
  for (size_t v=0;v<nv;v++) { d.variable[v]=y[v]+h6*(dydx[v]+dt[v]+2.0*dm[v]);}
  return;

}


void RKIntegrator::RKFunction::rkstep(const RKIntegrator::RKData::Data & s, RKIntegrator::RKData::Data & d)  const {
  //
  // Adaptive stepsize control
  //
  const int nvar = s.variable.size();
  const double eps    = 1.0E-6;
  const double SAFETY = 0.9;
  const double PSHRNK = -0.25;
  const double PGROW  = -0.20;
  const double ERRCON = -1.89E-4;
  const double TINY   = 1.0E-30;
  double hnext;

  
  RKData::Data Tmp0(nvar),Tmp1(nvar);
  Tmp0=s;
  Tmp1=d;
  bool done=false;
  while (1) { // "Same time as"...

    //--------------------------------------//
    // Take one step, from Tmp0 to Tmp1:    //
    //--------------------------------------//

    double h = Tmp1.time - Tmp0.time;
    while (1) {
      std::vector<double> errors;
      
      rkck(Tmp0, Tmp1, errors);
      for (size_t e=0;e<errors.size();e++) {
       	errors[e] = fabs(errors[e]) / (fabs(Tmp0.variable[e]) + fabs(Tmp0.firstDerivative[e]*h) + TINY);
      }
      double emax = (*std::max_element(errors.begin(),errors.end()))/eps;
      if (emax > 1) {
	h = std::max(SAFETY*h*pow(emax,PSHRNK),0.1*h);
	if  (!(((float) Tmp0.time+h - (float) Tmp0.time) > 0) ) {
	  std::cerr << "Warning, RK Integrator step underflow" << std::endl;
	}
	Tmp1.time = Tmp0.time+h;
	continue;
      }
      else {
	
	if (emax > ERRCON) {
	  hnext = SAFETY*h*pow(emax,PGROW);
	}
	else {
	  hnext = 5.0*h;
	}
	if (Tmp1==d) {
	  done=true;
	  break;
	}
	else {
	  Tmp0=Tmp1;
	  Tmp1.time = std::min(Tmp0.time + hnext, d.time);
	  break;
	}
      }
    }

    //--------------------------------------//
    // End of Step.                         //
    //--------------------------------------//

    if (done) break;
  }
  d=Tmp1;
}

void RKIntegrator::RKFunction::rkck(const RKIntegrator::RKData::Data & s, RKIntegrator::RKData::Data & d, std::vector<double> & errors)  const {
  
#ifdef NONAUTONOMOUS_EQUATIONS
  static const double
    a2=0.2,
    a3=0.3,
    a4=0.6,
    a5=1.0, 
    a6=0.875;
#endif
  
  static const double
    b21=0.2,
    b31=3.0/40.0,
    b32=9.0/40.0,
    b41=0.3,
    b42=-0.9,
    b43=1.2,
    b51=-11.0/54.0,
    b52=2.5,
    b53=-70.0/27.0,
    b54=35.0/27.0,
    b61=1631.0/55296.0,
    b62=175.0/512.0,
    b63=575.0/13824.0,
    b64=44275.0/110592.0,
    b65=253.0/4096.0;

  static const double
    c1=37.0/378.0,
    c3=250.0/621.0,
    c4=125.0/594.0,
    c6=512.0/1771.0;
  
  static const double
    dc1=c1-2825.0/27648.0,
    dc3=c3-18575.0/48384.0,
    dc4=c4-13525.0/55296.0,
    dc5=-277.0/14336.0,
    dc6=c6 - 0.25;

  // First step:
  double h = d.time - s.time;
  assert (h>0);
  unsigned int nv = s.variable.size();
  Argument arg(nv), arg0(nv), d1(nv),d2(nv), d3(nv), d4(nv), d5(nv), d6(nv);
  

  for (size_t v=0;v<nv;v++) { arg0[v]=s.variable[v];}
  
  if (!s.dcalc) {
    for (size_t v=0;v<nv;v++) {d1[v]=(*_data->_diffEqn[v])(arg0);}
    for (size_t v=0;v<nv;v++) {s.firstDerivative[v]=d1[v];}
    s.dcalc=true;
  }
  else {
    for (size_t v=0;v<nv;v++) { d1[v] = s.firstDerivative[v];}
  }    
    

  for (size_t v=0;v<nv;v++) { arg[v] = arg0[v] + b21*h*d1[v];} 
  
  for (size_t v=0;v<nv;v++) { d2[v] = (*_data->_diffEqn[v])(arg);}
  for (size_t v=0;v<nv;v++) { arg[v] = arg0[v] + h*(b31*d1[v]+b32*d2[v]);} 
  
  
  for (size_t v=0;v<nv;v++) { d3[v] = (*_data->_diffEqn[v])(arg);}
  for (size_t v=0;v<nv;v++) { arg[v] = arg0[v] + h*(b41*d1[v]+b42*d2[v]+b43*d3[v]);}
  
  for (size_t v=0;v<nv;v++) { d4[v] = (*_data->_diffEqn[v])(arg);}
  for (size_t v=0;v<nv;v++) { arg[v] = arg0[v] + h*(b51*d1[v]+b52*d2[v]+b53*d3[v] + b54*d4[v]);}
  
  for (size_t v=0;v<nv;v++) { d5[v] = (*_data->_diffEqn[v])(arg);}
  for (size_t v=0;v<nv;v++) { arg[v] = arg0[v] + h*(b61*d1[v]+b62*d2[v]+b63*d3[v] + b64*d4[v] + b65*d5[v]);}
  
  for (size_t v=0;v<nv;v++) { d6[v] = (*_data->_diffEqn[v])(arg);}
  
  for (size_t v=0;v<nv;v++) { d.variable[v] = arg0[v] + h*(c1*d1[v]+c3*d3[v]+c4*d4[v]+c6*d6[v]);}
  errors.erase(errors.begin(),errors.end());
  
  for (size_t v=0;v<nv;v++) { errors.push_back(h*(dc1*d1[v]+dc3*d3[v]+dc4*d4[v]+dc5*d5[v]+dc6*d6[v]));}
}



} // namespace Genfun
