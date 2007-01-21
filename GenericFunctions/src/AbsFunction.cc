// -*- C++ -*-
// $Id: AbsFunction.cc,v 1.4 2007/01/21 20:20:41 boudreau Exp $
#include "CLHEP/GenericFunctions/AbsFunction.hh"
#include "CLHEP/GenericFunctions/ConstTimesFunction.hh"
#include "CLHEP/GenericFunctions/ConstOverFunction.hh"
#include "CLHEP/GenericFunctions/ConstPlusFunction.hh"
#include "CLHEP/GenericFunctions/ConstMinusFunction.hh"
#include "CLHEP/GenericFunctions/FunctionSum.hh"
#include "CLHEP/GenericFunctions/FunctionDifference.hh"
#include "CLHEP/GenericFunctions/FunctionProduct.hh"
#include "CLHEP/GenericFunctions/FunctionQuotient.hh"
#include "CLHEP/GenericFunctions/FunctionConvolution.hh"
#include "CLHEP/GenericFunctions/FunctionNegation.hh"
#include "CLHEP/GenericFunctions/FunctionDirectProduct.hh"
#include "CLHEP/GenericFunctions/FixedConstant.hh"
#include "CLHEP/GenericFunctions/FloatingConstant.hh"
#include "CLHEP/GenericFunctions/FunctionNumDeriv.hh"
#include "CLHEP/GenericFunctions/Variable.hh"
#include "CLHEP/GenericFunctions/FunctionNoop.hh"
#include "CLHEP/GenericFunctions/ParameterComposition.hh"
#include <assert.h>
namespace Genfun {
AbsFunction::AbsFunction() {
}

AbsFunction::~AbsFunction() {
}

AbsFunction *AbsFunction::clone() const {
  return _clone();
}
  

FunctionComposition AbsFunction::operator () (const AbsFunction &function) const {
  return FunctionComposition(this, &function);
}

ParameterComposition AbsFunction::operator() (const AbsParameter &p) const {
  return ParameterComposition(this, &p);
}

Derivative AbsFunction::partial(unsigned int index) const {
  FunctionNumDeriv fPrime(this,index);
  return Derivative(&fPrime);
}


Derivative AbsFunction::derivative(const Variable &v) const {
  return partial(v.index());
}

Derivative AbsFunction::prime() const {
  assert(dimensionality()==1);
  return partial(0);
}

FunctionSum operator + (const AbsFunction & a, const AbsFunction & b) {
  return FunctionSum(&a,&b);
}

FunctionDifference operator - (const AbsFunction & a, const AbsFunction & b) {
  return FunctionDifference(&a,&b);
}

FunctionProduct operator * (const AbsFunction & a, const AbsFunction & b) {
  return FunctionProduct(&a,&b);
}

FunctionQuotient operator / (const AbsFunction & a, const AbsFunction & b) {
  return FunctionQuotient(&a,&b);
}

FunctionConvolution convolve (const AbsFunction & a, const AbsFunction & b, double x0, double x1) {
  return FunctionConvolution(&a,&b, x0, x1);
}

FunctionNegation operator - (const AbsFunction & a) {
  return FunctionNegation(&a);
}

unsigned int AbsFunction::dimensionality() const {
  return 1;
}

FunctionDirectProduct operator % (const AbsFunction & a, const AbsFunction & b) {
  return FunctionDirectProduct(&a,&b);
}

ConstTimesFunction operator * (const AbsFunction &op2, double c) {
  return ConstTimesFunction(c, &op2);
}

ConstPlusFunction  operator + (const AbsFunction &op2, double c) {
  return ConstPlusFunction(c,&op2);
}

ConstPlusFunction  operator - (const AbsFunction &op2, double c) {
  return ConstPlusFunction(-c, &op2);
}

ConstTimesFunction operator / (const AbsFunction &op2, double c) {
  return ConstTimesFunction(1/c,&op2);
}


ConstTimesFunction           operator * (double c, const AbsFunction &op2) {
  return ConstTimesFunction(c,&op2);
}

ConstPlusFunction               operator + (double c, const AbsFunction &op2) {
  return ConstPlusFunction(c,&op2);
}

ConstMinusFunction        operator - (double c, const AbsFunction &op2) {
  return ConstMinusFunction(c,&op2);
}

ConstOverFunction          operator / (double c, const AbsFunction &op2) {
  return ConstOverFunction(c,&op2);
}


FunctionTimesParameter operator * (const AbsFunction &f, const AbsParameter & p) {
  return FunctionTimesParameter(&p, &f);
}

FunctionPlusParameter operator + (const AbsFunction &f, const AbsParameter & p) {
  return FunctionPlusParameter(&p, &f);
}

FunctionPlusParameter operator - (const AbsFunction &f, const AbsParameter & p) {
  GENPARAMETER MinusP = -p;
  return FunctionPlusParameter(&MinusP, &f);
  
}

FunctionTimesParameter operator / (const AbsFunction &f, const AbsParameter & p) {
  GENPARAMETER oneOverP = 1.0/p;
  return FunctionTimesParameter(&oneOverP, &f);
}

FunctionTimesParameter operator * (const AbsParameter & p, const AbsFunction &f) {
  return FunctionTimesParameter(&p, &f);
}

FunctionPlusParameter operator + (const AbsParameter & p, const AbsFunction &f) {
  return FunctionPlusParameter(&p, &f);
}

FunctionPlusParameter operator - (const AbsParameter & p, const AbsFunction &f) {
  GENFUNCTION MinusF = -f;
  return FunctionPlusParameter(&p, &MinusF);
}

FunctionTimesParameter operator / (const AbsParameter & p, const AbsFunction &f) {
  GENFUNCTION oneOverF = 1.0/f;
  return FunctionTimesParameter(&p, &oneOverF);
}
} // namespace Genfun
