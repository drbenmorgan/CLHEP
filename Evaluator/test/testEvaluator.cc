// -*- C++ -*-
// $Id: testEvaluator.cc,v 1.1 2003/07/16 21:47:28 garren Exp $
// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a test for the Evaluator class.
// It can be also used as a scientific caculator.
//

#include "CLHEP/Evaluator/Evaluator.h"
#include <iostream>
#include <string.h>
#include <assert.h>

int main() {
  char exp[240];
  HepTool::Evaluator eval;

  eval.setVariable(" dummy  ", 0.);        // these three lines have been
  assert( eval.findVariable("  dummy ") ); // included just for test
  eval.clear();                            // ===========================

  eval.setStdMath();                 // set standard constants and functions
  eval.setSystemOfUnits();           // set SI units
  std::cout.precision(15);
  for(;;) {
    std::cout << "CALC> ";

    // In principle, next two lines could be replaced with just 
    // std::cin.getline(exp, 240); but that does not work on DEC
    // because of bug in the cxx V6.1-027 compiler.
    std::cin.get(exp, 240);
    std::cin.ignore();
    if ( !std::cin || strcmp(exp,"exit") == 0 || strcmp(exp,"quit") == 0) {
      std::cout << std::endl;
      break;                         // exit
    }
    double value = eval.evaluate(exp);
    switch(eval.status()) {
    case HepTool::Evaluator::OK:
      std::cout << value << std::endl;
      break;
    case HepTool::Evaluator::WARNING_BLANK_STRING:
      continue;
    default:
      std::cout << "------";
      for (int i=0; i<eval.error_position(); i++) std::cout << "-";
      std::cout << "^" << std::endl;
      eval.print_error();
    }
    std::cout << std::endl;
  }
  return 0;
}
