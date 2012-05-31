// test Bug #90848 in CLHEP::Evaluator
// Author: Tom Roberts

#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <limits>

#include "CLHEP/Evaluator/Evaluator.h"
class MyEvaluator : public HepTool::Evaluator {
public:
	MyEvaluator() : HepTool::Evaluator() { setStdMath(); }
	bool isOK() { return status() == OK; }
	double evaluate(const char *e) {
		double v = HepTool::Evaluator::evaluate(e);
		if(status() != OK) v = std::numeric_limits<double>::quiet_NaN();
		return v;
	}
};

struct Test { 
	const char *expr;
	double value1;		// x=1, y=2, z=3
	double value2;		// x=10, y=-20 z=-30
};

Test tests[] = {
	{ "x",					1.0,		10.0},
	{ "y",					2.0,		-20.0},
	{ "z",					3.0,		-30.0},
	{ "x+y",				3.0,		-10.0},
	{ "-z",					-3.0,		30.0},
	{ "0-z",				-3.0,		30.0},
	{ "0 - -z",				3.0,		-30.0},
	{ "10/-x",				-10.0,		-1.0},
	{ "exp(-y)*exp(y)",			1.0,		1.0},
	{ "exp(-y^2)*exp(y^2)",			1.0,		1.0},
	{ "-5*x",				-5.0,		-50.0},
	{ "5+-x",				4.0,		-5.0},
	{ "5+(-x)",				4.0,		-5.0},
	{ "5*-x",				-5.0,		-50.0},
	{ "5*(-x)",				-5.0,		-50.0},
	{ "-z^2",				-9.0,		-900.0},
	{ "0-z^2",				-9.0,		-900.0},
	{ "exp(-0.2*z^2)*exp(0.2*z^2)",		1.0,		1.0},
	{ "exp(0.2*-z^2)*exp(0.2*z^2)",		1.0,		1.0},
	{ "exp(-z^2*0.2)*exp(0.2*z^2)",		1.0,		1.0},
	{ "exp(0.2*-(z^2))*exp(0.2*z^2)",	1.0,		1.0},
	{ "exp(-(z^2)*0.2)*exp(0.2*z^2)",	1.0,		1.0},
	{ "exp(-0.2*z)*exp(0.2*z)",		1.0,		1.0},
	{ "exp(0.2*-z)*exp(0.2*z)",		1.0,		1.0},
	{ "exp(-z*0.2)*exp(0.2*z)",		1.0,		1.0},
};

int main() {
	MyEvaluator e;

	e.setVariable("x",1.0);
	e.setVariable("y",2.0);
	e.setVariable("z",3.0);
//printf("x=1.0 y=2.0 z=3.0\n");
	int err=0;
	for(unsigned i=0; i<sizeof(tests)/sizeof(Test); ++i) {
		double v=e.evaluate(tests[i].expr);
		if(std::isnan(v) || std::fabs(v-tests[i].value1) > 1E-12 || !e.isOK()) {
			printf("%s = %.6f should be %.6f\n",tests[i].expr,
				e.evaluate(tests[i].expr),tests[i].value1);
			err = 1;
		}
	}

	e.setVariable("x",10.0);
	e.setVariable("y",-20.0);
	e.setVariable("z",-30.0);
//printf("x=10.0 y=-20.0 z=-30.0\n");
	for(unsigned i=0; i<sizeof(tests)/sizeof(Test); ++i) {
		double v=e.evaluate(tests[i].expr);
		if(std::isnan(v) || std::fabs(v-tests[i].value2) > 1E-12 || !e.isOK()) {
			printf("%s = %.6f should be %.6f\n",tests[i].expr,
				e.evaluate(tests[i].expr),tests[i].value2);
			err = 1;
		}
	}

	double v=e.evaluate("unknown(0.0)");
	if(!std::isnan(v) || e.isOK()) {
		printf("%s succeeded\n","unknown(0.0)");
		err=1;
	}

	v = e.evaluate("unknown+0.0");
	if(!std::isnan(v) || e.isOK()) {
		printf("%s succeeded\n","unknown+0.0");
		err=1;
	}

	exit(err);
}
