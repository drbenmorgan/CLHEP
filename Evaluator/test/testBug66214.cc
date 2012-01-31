// ---------------------------------------------------------------------------
//
// This file is a part of the CLHEP - a Class Library for High Energy Physics.
//
// This is a test for bug report 66214 in the Evaluator class.
//
#include <iostream>
#include <fstream>
#include <CLHEP/Evaluator/Evaluator.h>

double eval( std::string expr, int& numbad, std::ofstream& os)
{
    static HepTool::Evaluator *ev=0;
    if(ev == 0) ev = new HepTool::Evaluator();
    ev->setStdMath();                 // set standard constants and functions
    ev->setSystemOfUnits();           // set SI units

    double v = ev->evaluate(expr.data());

    os << "CALC> " << expr << ": ";
    if(ev->status() != HepTool::Evaluator::OK) {
	os << ev->error_name() << std::endl;
	++numbad;
    } else {
	os << v << std::endl;
    }
    return v;
}

int main()
{

    int numbad = 0;
    double result;
    // many of these expressions fail in releases prior to 2.0.4.7
    std::string exp[43] = {   " +1",     " -1",     "1 + 1",  "1 + -1","1 + (-1)",
                     "1 + +1","1 + (+1)",    "1 * -1","1 * (-1)",  "-1 * 1",
		      "10^-1", "10^(-1)",       "9*4",  "9 * -4","9 * (-4)",
		     "4*---2","4*(---2)","4*(-(--2))","4*(--(-2))","4*(-(-(-2)))",
		      "4*--2", "4*(--2)", "4*(-(-2))",    "-5^2",   "9*4+2",
		     "231/-11","231/-11+10","231/-11/3","(231/-11)+10",
		     "100/5^2","100/+5^2","100/-5^2",   "9*4+30", "9*4+-30",
		     "100/(5^2)","100/(+5^2)","100/(-5^2)",   "100/(-5)^2", "100/((-5)^2)",
		     "-9*4+30","9*-4+30","9*(-4)+30","(9*-4)+30" };
    double res[43] = {     1.,       -1.,          2.,        0.,        0., 
                           2.,        2.,         -1.,       -1.,       -1.,
			  0.1,       0.1,         36.,      -36.,      -36.,
			  -8.,       -8.,         -8.,       -8.,       -8.,
			   8.,        8.,          8.,      -25.,       38.,
		         -21.,      -11.,         -7.,      -11.,
		           4.,        4.,         -4.,       66.,        6., 
		           4.,        4.,         -4.,        4.,        4., 
		          -6.,       -6.,         -6.,       -6. };
    std::string exp2[3] = { "sin(45*deg)", "sin(45*pi/-180)", "232/22" };

    std::ofstream os("testBug66214.cout");  

    for(int i=0; i<43; ++i ) {
        result=eval(exp[i],numbad,os);
	if( result != res[i] ) {
	    ++numbad;
	    os << "ERROR:  expected " << res[i] << " got " << result << std::endl;
	    os << std::endl;
	}
    }

    // inspect these by hand
    // return values: 0.707107, -0.707107, 10.5455
    for(int i=0; i<3; ++i ) {
        eval(exp2[i],numbad,os);
    }

    return numbad;
}
