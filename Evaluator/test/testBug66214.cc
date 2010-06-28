// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a test for bug report 66214 in the Evaluator class.
//
#include <iostream>
#include <fstream>
#include <CLHEP/Evaluator/Evaluator.h>

void eval(const char *expr, int& numbad, std::ofstream& os)
{
    static HepTool::Evaluator *ev=0;
    if(ev == 0) ev = new HepTool::Evaluator();

    double v = ev->evaluate(expr);

    os << "CALC> " << expr << ": ";
    if(ev->status() != HepTool::Evaluator::OK) {
	os << ev->error_name() << std::endl;
	++numbad;
    } else {
	os << v << std::endl;
    }
}

int main()
{

    std::ofstream os("testBug66214.cout");  

    int numbad = 0;

    eval(" +1",numbad,os);
    eval(" -1",numbad,os);
    eval("1 + 1",numbad,os);
    eval("1 + -1",numbad,os);
    eval("1 + (-1)",numbad,os);
    eval("1 + +1",numbad,os);
    eval("1 + (+1)",numbad,os);
    eval("1 * -1",numbad,os);
    eval("1 * (-1)",numbad,os);
    eval("-1 * 1",numbad,os);
    eval("10^-1",numbad,os);
    eval("10^(-1)",numbad,os);

    return numbad;
}
