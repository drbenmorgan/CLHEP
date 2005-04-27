// -*- C++ -*-
// $Id: testRandDists.cc,v 1.6 2005/04/27 20:12:50 garren Exp $
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
//
// testRandDists -- tests of the correctness of random distributions 
//
// Usage:
//   testRandDists < testRandDists.dat > testRandDists.log
//
// Currently tested:
//	RandGauss
//	RandGeneral
//
// M. Fischler	    5/17/99	Reconfigured to be suitable for use with
//				an automated validation script - will return 
//				0 if validation is OK, or a mask indicating
//				where problems were found.
// M. Fischler	    5/18/99	Added test for RandGeneral.
// Evgenyi T.	    5/20/99	Vetted for compilation on various CLHEP/CERN
//				platforms.
// M. Fischler	    5/26/99	Extended distribution test to intervals of .5 
//				sigma and to moments up to the sixth.
// M. Fischler	   10/29/99	Added validation for RandPoisson.
// M. Fischler	   11/09/99	Made gammln static to avoid (harmless) 
//				confusion with the gammln in RandPoisson.
// M. Fischler	    2/04/99	Added validation for the Q and T versions of
//				Poisson and Gauss
// M. Fischler     11/04/04     Add kludge to gaussianTest to deal with
//                              different behaviour under optimization on
//                              some compilers (gcc 2.95.2)
//                              This behaviour was only seen with stepwise 
//                              RandGeneral and appears to be solely a 
//                              function of the test program.
// 
// ----------------------------------------------------------------------

#include "CLHEP/Random/Randomize.h"
#include "CLHEP/Random/RandGaussQ.h"
#include "CLHEP/Random/RandGaussT.h"
#include "CLHEP/Random/RandPoissonQ.h"
#include "CLHEP/Random/RandPoissonT.h"
#include "CLHEP/Units/PhysicalConstants.h"
#include "CLHEP/Random/defs.h"
#include <iostream>
#include <iomanip>
#include <cmath>		// double abs()
#include <stdlib.h>		// int abs()

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::abs;
using namespace CLHEP;
//#ifndef _WIN32
//using std::exp;
//#endif

// Tolerance of deviation from expected results
static const double REJECT = 4.0;

// Mask bits to form a word indicating which if any dists were "bad"
static const int GaussBAD    = 1 << 0;
static const int GeneralBAD  = 1 << 1;
static const int PoissonBAD  = 1 << 2;
static const int GaussQBAD   = 1 << 3;
static const int GaussTBAD   = 1 << 4;
static const int PoissonQBAD = 1 << 5;
static const int PoissonTBAD = 1 << 6;


// **********************
//
// SECTION I - General tools for the various tests
//
// **********************

static
double gammln(double x) {
	// Note:  This uses the gammln algorith in Numerical Recipes.
	// In the "old" RandPoisson there is a slightly different algorithm, 
	// which mathematically is identical to this one.  The advantage of
	// the modified method is one fewer division by x (in exchange for
	// doing one subtraction of 1 from x).  The advantage of the method 
	// here comes when .00001 < x < .65:  In this range, the alternate
	// method produces results which have errors 10-100 times those
	// of this method (though still less than 1.0E-10).  If we package
	// either method, we should use the reflection formula (6.1.4) so
	// that the user can never get inaccurate results, even for x very 
	// small.  The test for x < 1 is as costly as a divide, but so be it.

  double y, tmp, ser;
  static double c[6] = {
	 76.18009172947146,
	-86.50532032941677,
	 24.01409824083091,
	 -1.231739572450155,
	  0.001208650973866179,
	 -0.000005395239384953 };
  y = x;
  tmp = x + 5.5;
  tmp -= (x+.5)*log(tmp);
  ser = 1.000000000190015;
  for (int i = 0; i < 6; i++) {
    ser += c[i]/(++y);
  }
  double ans = (-tmp + log (sqrt(CLHEP::twopi)*ser/x));
  return ans;
}

static
double gser(double a, double x) {
  const int ITMAX = 100;
  const double EPS = 1.0E-8;
  double ap = a;
  double sum = 1/a;
  double del = sum;
  for (int n=0; n < ITMAX; n++) {
    ap++;
    del *= x/ap;
    sum += del;
    if (fabs(del) < fabs(sum)*EPS) {
      return sum*exp(-x+a*log(x)-gammln(a));
    }
  }
  cout << "Problem - inaccurate gser " << a << ", " << x << "\n";
  return sum*exp(-x+a*log(x)-gammln(a));
}

static
double gcf(double a, double x) {
  const int ITMAX = 100;
  const double EPS = 1.0E-8;
  const double VERYSMALL = 1.0E-100;
  double b = x+1-a;
  double c = 1/VERYSMALL;
  double d = 1/b;
  double h = d;
  for (int i = 1; i <= ITMAX; i++) {
    double an = -i*(i-a);
    b += 2;
    d = an*d + b;
    if (fabs(d) < VERYSMALL) d = VERYSMALL;
    c = b + an/c;
    if (fabs(c) < VERYSMALL) c = VERYSMALL;
    d = 1/d;
    double del = d*c;
    h *= del;
    if (fabs(del-1.0) < EPS) {
      return exp(-x+a*log(x)-gammln(a))*h;
    }
  }
  cout << "Problem - inaccurate gcf " << a << ", " << x << "\n";
  return exp(-x+a*log(x)-gammln(a))*h;
}

static
double gammp (double a, double x) {
  if (x < a+1) {
    return gser(a,x);
  } else {
    return 1-gcf(a,x);
  }
}


// **********************
//
// SECTION II - Validation of specific distributions
//
// **********************

// ------------
// gaussianTest
// ------------

bool gaussianTest ( HepRandom & dist, double mu, 
		    double sigma, int nNumbers ) {

  bool good = true;
  double worstSigma = 0;

// We will accumulate mean and moments up to the sixth,
// The second moment should be sigma**2, the fourth 3 sigma**4,
// the sixth 15 sigma**6.  The expected variance in these is 
// (for the m-th moment with m even) (2m-1)!! (m-1)!!**2 / n
// (for the m-th moment with m odd)  (2m-1)!!  m!!**2    / n
// We also do a histogram with bins every half sigma.

  double sumx = 0;
  double sumx2 = 0;
  double sumx3 = 0;
  double sumx4 = 0;
  double sumx5 = 0;
  double sumx6 = 0;
  int counts[11];
  int ncounts[11];
  int ciu;
  for (ciu = 0; ciu < 11; ciu++) {
    counts[ciu] = 0;
    ncounts[ciu] = 0;
  }

  double x;
  double u;
  int ipr = nNumbers / 10 + 1;
  for (int ifire = 0; ifire < nNumbers; ifire++) {
    x = dist();		// We avoid fire() because that is not virtual 
			// in HepRandom.
    if( x < mu - 12.0*sigma ) {
        cout << "x  = " << x << "\n";
    }
    if ( (ifire % ipr) == 0 ) {
      cout << ifire << endl;
    }
    sumx  += x;
    sumx2 += x*x;
    sumx3 += x*x*x;
    sumx4 += x*x*x*x;
    sumx5 += x*x*x*x*x;
    sumx6 += x*x*x*x*x*x;
    u = (x - mu) / sigma;
    if ( u >= 0 ) {
      ciu = (int)(2*u);
      if (ciu>10) ciu = 10;
      counts[ciu]++;
    } else {
      ciu = (int)(2*(-u));
      if (ciu>10) ciu = 10;
      ncounts[ciu]++;
    }
  }

  double mean = sumx / nNumbers;
  double u2 = sumx2/nNumbers - mean*mean;
  double u3 = sumx3/nNumbers - 3*sumx2*mean/nNumbers + 2*mean*mean*mean;
  double u4 = sumx4/nNumbers - 4*sumx3*mean/nNumbers 
		+ 6*sumx2*mean*mean/nNumbers - 3*mean*mean*mean*mean;
  double u5 = sumx5/nNumbers - 5*sumx4*mean/nNumbers 
		+ 10*sumx3*mean*mean/nNumbers 
		- 10*sumx2*mean*mean*mean/nNumbers
		+ 4*mean*mean*mean*mean*mean;
  double u6 = sumx6/nNumbers - 6*sumx5*mean/nNumbers 
		+ 15*sumx4*mean*mean/nNumbers 
		- 20*sumx3*mean*mean*mean/nNumbers
		+ 15*sumx2*mean*mean*mean*mean/nNumbers
		- 5*mean*mean*mean*mean*mean*mean;

  cout << "Mean (should be close to " << mu << "): " << mean << endl;
  cout << "Second moment (should be close to " << sigma*sigma << 
			"): " << u2 << endl;
  cout << "Third  moment (should be close to zero): " << u3 << endl;
  cout << "Fourth moment (should be close to " << 3*sigma*sigma*sigma*sigma << 
			"): " << u4 << endl;
  cout << "Fifth moment (should be close to zero): " << u5 << endl;
  cout << "Sixth moment (should be close to " 
	<< 15*sigma*sigma*sigma*sigma*sigma*sigma 
	<< "): " << u6 << endl;

  // For large N, the variance squared in the scaled 2nd, 3rd 4th 5th and
  // 6th moments are roughly 2/N, 6/N, 96/N, 720/N and 10170/N respectively.  
  // Based on this, we can judge how many sigma a result represents:
  
  double del1 = sqrt ( (double) nNumbers ) * abs(mean - mu) / sigma;
  double del2 = sqrt ( nNumbers/2.0 ) * abs(u2 - sigma*sigma) / (sigma*sigma);
  double del3 = sqrt ( nNumbers/6.0 ) * abs(u3) / (sigma*sigma*sigma);
  double sigma4 = sigma*sigma*sigma*sigma;
  double del4 = sqrt ( nNumbers/96.0 ) * abs(u4 - 3 * sigma4) / sigma4;
  double del5 = sqrt ( nNumbers/720.0 ) * abs(u5) / (sigma*sigma4);
  double del6 = sqrt ( nNumbers/10170.0 ) * abs(u6 - 15*sigma4*sigma*sigma) 
				/ (sigma4*sigma*sigma);

  cout << "        These represent " << 
	del1 << ", " << del2 << ", " << del3 << ", \n" 
	<<"                        " << del4 << ", " << del5 << ", " << del6
        <<"\n                         standard deviations from expectations\n";
  if ( del1 > worstSigma ) worstSigma = del1;
  if ( del2 > worstSigma ) worstSigma = del2;
  if ( del3 > worstSigma ) worstSigma = del3;
  if ( del4 > worstSigma ) worstSigma = del4;
  if ( del5 > worstSigma ) worstSigma = del5;
  if ( del6 > worstSigma ) worstSigma = del6;

  if ( del1 > REJECT || del2 > REJECT || del3 > REJECT 
    || del4 > REJECT || del5 > REJECT || del6 > REJECT ) {
      cout << "REJECT hypothesis that this distribution is correct!!\n";
      good = false;
  }

  // The variance of the bin counts is given by a Poisson estimate (sqrt(npq)).

  double table[11] = {  // Table of integrated density in each range:
	.191462, // 0.0 - 0.5 sigma
	.149882, // 0.5 - 1.0 sigma
	.091848, // 1.0 - 1.5 sigma
	.044057, // 1.5 - 2.0 sigma
	.016540, // 2.0 - 2.5 sigma
	.004860, // 2.5 - 3.0 sigma
	.001117, // 3.0 - 3.5 sigma
	.000201, // 3.5 - 4.0 sigma
	2.83E-5, // 4.0 - 4.5 sigma
	3.11E-6, // 4.5 - 5.0 sigma
	3.87E-7  // 5.0 sigma and up
	};

  for (int m = 0; m < 11; m++) {
    double expect = table[m]*nNumbers;
    double sig = sqrt ( table[m] * (1.0-table[m]) * nNumbers );
    cout << "Between " << m/2.0 << " sigma and " 
	<< m/2.0+.5 << " sigma (should be about " << expect << "):\n " 
        << "         "
	<< ncounts[m] << " negative and " << counts[m] << " positive " << "\n";
    double negSigs = abs ( ncounts[m] - expect ) / sig;
    double posSigs = abs (  counts[m] - expect ) / sig;
    cout << "        These represent " << 
	negSigs << " and " << posSigs << " sigma from expectations\n";
    if ( negSigs > REJECT || posSigs > REJECT ) {
      cout << "REJECT hypothesis that this distribution is correct!!\n";
      good = false;
    }
    if ( negSigs > worstSigma ) worstSigma = negSigs;
    if ( posSigs > worstSigma ) worstSigma = posSigs;
  }

  cout << "\n The worst deviation encountered (out of about 25) was "
	<< worstSigma << " sigma \n\n";

  return good;

} // gaussianTest()


// ------------
// poissonTest
// ------------

class poisson {
  double mu_;
  public:
  poisson(double mu) : mu_(mu) {}
  double operator()(int r) { 
    double logAnswer = -mu_ + r*log(mu_) - gammln(r+1);
    return exp(logAnswer);
  }
};

double* createRefDist ( poisson pdist, int N,
				int MINBIN, int MAXBINS, int clumping, 
				int& firstBin, int& lastBin ) {

  // Create the reference distribution -- making sure there are more than
  // 20 points at each value.  The entire tail will be rolled up into one 
  // value (at each end).  We shall end up with some range of bins starting
  // at 0 or more, and ending at MAXBINS-1 or less.

  double * refdist = new double [MAXBINS];

  int c  = 0; // c is the number of the clump, that is, the member number 
	      // of the refdist array.
  int ic = 0; // ic is the number within the clump; mod clumping
  int r  = 0; // r is the value of the variate.

  // Determine the first bin:  at least 20 entries must be at the level
  // of that bin (so that we won't immediately dip belpw 20) but the number
  // to enter is cumulative up to that bin.

  double start = 0;
  double binc;
  while ( c < MAXBINS ) {
    for ( ic=0, binc=0; ic < clumping; ic++, r++ ) {
      binc += pdist(r) * N;
    }
    start += binc;
    if (binc >= MINBIN) break;
    c++;
    if ( c > MAXBINS/3 ) {
      cout << "The number of samples supplied " << N << 
	" is too small to set up a chi^2 to test this distribution.\n";
      exit(-1);
    }
  }
  firstBin = c;
  refdist[firstBin] = start;
  c++;

  // Fill all the other bins until one has less than 20 items.
  double next = 0;
  while ( c < MAXBINS ) {
    for ( ic=0, binc=0; ic < clumping; ic++, r++ ) {
      binc += pdist(r) * N;
    }
    next = binc;
    if (next < MINBIN) break;
    refdist[c] = next;
    c++;
  }

  // Shove all the remaining items into last bin.
  lastBin = c-1;
  next += refdist[lastBin];
  while ( c < MAXBINS ) {
    for ( ic=0, binc=0; ic < clumping; ic++, r++ ) {
      binc += pdist(r) * N;
    }
    next += binc;
    c++;
  } 
  refdist[lastBin] = next;

  return refdist;

} // createRefDist()


bool poissonTest ( RandPoisson & dist, double mu, int N ) {

// Three tests will be done:
//
// A chi-squared test will be used to test the hypothesis that the 
// generated distribution of N numbers matches the proper Poisson distribution.
//
// The same test will be applied to the distribution of numbers "clumping"
// together sqrt(mu) bins.  This will detect small deviations over several 
// touching bins, when mu is not small.
//
// The mean and second moment are checked against their theoretical values.

  bool good = true;

  int clumping = int(sqrt(mu));
  if (clumping <= 1) clumping = 2;
  const int MINBIN  = 20;
  const int MAXBINS = 1000;
  int firstBin;
  int lastBin;
  int firstBin2;
  int lastBin2;

  poisson pdist(mu);

  double* refdist  = createRefDist( pdist, N,
			MINBIN, MAXBINS, 1, firstBin, lastBin);
  double* refdist2 = createRefDist( pdist, N,
			MINBIN, MAXBINS, clumping, firstBin2, lastBin2);

  // Now roll the random dists, treating the tails in the same way as we go.
  
  double sum = 0;
  double moment = 0;

  double* samples  = new double [MAXBINS];
  double* samples2 = new double [MAXBINS];
  int r;
  for (r = 0; r < MAXBINS; r++) {
    samples[r] = 0;
    samples2[r] = 0;
  }

  int r1;
  int r2;
  for (int i = 0; i < N; i++) {
    r = dist.fire();
    sum += r;
    moment += (r - mu)*(r - mu);
    r1 = r;
    if (r1 < firstBin) r1 = firstBin;
    if (r1 > lastBin)  r1 = lastBin;
    samples[r1] += 1;
    r2 = r/clumping;
    if (r2 < firstBin2) r2 = firstBin2;
    if (r2 > lastBin2)  r2 = lastBin2;
    samples2[r2] += 1;
  }

//  #ifdef DIAGNOSTIC
  int k;
  for (k = firstBin; k <= lastBin; k++) {
    cout << k << "  " << samples[k] << "  " << refdist[k] << "     " <<
	(samples[k]-refdist[k])*(samples[k]-refdist[k])/refdist[k] << "\n";
  }
  cout << "----\n";
  for (k = firstBin2; k <= lastBin2; k++) {
    cout << k << "  " << samples2[k] << "  " << refdist2[k] << "\n";
  }
// #endif // DIAGNOSTIC

  // Now find chi^2 for samples[] to apply the first test

  double chi2 = 0;
  for ( r = firstBin; r <= lastBin; r++ ) {
    double delta = (samples[r] - refdist[r]);
    chi2 += delta*delta/refdist[r];
  }
  int degFreedom = (lastBin - firstBin + 1) - 1;
  
  // and finally, p.  Since we only care about it for small values, 
  // and never care about it past the 10% level, we can use the approximations
  // CL(chi^2,n) = 1/sqrt(CLHEP::twopi) * ErrIntC ( y ) with 
  // y = sqrt(2*chi2) - sqrt(2*n-1) 
  // errIntC (y) = exp((-y^2)/2)/(y*sqrt(CLHEP::twopi))

  double pval;
  pval = 1.0 - gammp ( .5*degFreedom , .5*chi2 );

  cout << "Chi^2 is " << chi2 << " on " << degFreedom << " degrees of freedom."
       << "  p = " << pval << "\n";

  delete[] refdist;
  delete[] samples;

  // Repeat the chi^2 and p for the clumped sample, to apply the second test

  chi2 = 0;
  for ( r = firstBin2; r <= lastBin2; r++ ) {
    double delta = (samples2[r] - refdist2[r]);
    chi2 += delta*delta/refdist2[r];
  }
  degFreedom = (lastBin2 - firstBin2 + 1) - 1;
  double pval2;
  pval2 = 1.0 - gammp ( .5*degFreedom , .5*chi2 );

  cout << "Clumps: Chi^2 is " << chi2 << " on " << degFreedom << 
	" degrees of freedom." << "  p = " << pval2 << "\n";

  delete[] refdist2;
  delete[] samples2;

  // Check out the mean and sigma to apply the third test

  double mean = sum / N;
  double sigma = sqrt( moment / (N-1) );

  double deviationMean  = fabs(mean - mu)/(sqrt(mu/N));
  double expectedSigma2Variance = (2*N*mu*mu/(N-1) + mu) / N;
  double deviationSigma = fabs(sigma*sigma-mu)/sqrt(expectedSigma2Variance);

  cout << "Mean  (should be " << mu << ") is " << mean << "\n";
  cout << "Sigma (should be " << sqrt(mu) << ") is " << sigma << "\n";

  cout << "These are " << deviationMean << " and " << deviationSigma <<
	" standard deviations from expected values\n\n";
  
  // If either p-value for the chi-squared tests is less that .0001, or
  // either the mean or sigma are more than 3.5 standard deviations off,
  // then reject the validation.  This would happen by chance one time 
  // in 2000.  Since we will be validating for several values of mu, the
  // net chance of false rejection remains acceptable.

  if ( (pval < .0001) || (pval2 < .0001) ||
       (deviationMean > 3.5) || (deviationSigma > 3.5) ) {
    good = false;
    cout << "REJECT this distributon!!!\n";
  }

  return good;

} // poissonTest()


// **********************
//
// SECTION III - Tests of each distribution class
//
// **********************

// ---------
// RandGauss
// ---------

int testRandGauss() {

  cout << "\n--------------------------------------------\n";
  cout << "Test of RandGauss distribution \n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed;	cout << seed << "\n";
  if (seed == 0) {
    cout << "Moving on to next test...\n";
    return 0; 
  }

  int nNumbers;
  cout << "How many numbers should we generate: ";
  cin >> nNumbers; cout << nNumbers << "\n";

  double mu;
  double sigma;
  cout << "Enter mu: ";
  cin >> mu; cout << mu << "\n";

  cout << "Enter sigma: ";
  cin >> sigma; cout << sigma << "\n";

  cout << "\nInstantiating distribution utilizing TripleRand engine...\n";
  TripleRand eng (seed);
  RandGauss dist (eng, mu, sigma);
 
  cout << "\n Sample  fire(): \n";
  double x;
  
  x = dist.fire();
  cout << x;

  cout << "\n Testing operator() ... \n";

  bool good = gaussianTest ( dist, mu, sigma, nNumbers );

  if (good) { 
    return 0;
  } else {
    return GaussBAD;
  }

} // testRandGauss()



// ---------
// RandGaussT
// ---------

int testRandGaussT() {

  cout << "\n--------------------------------------------\n";
  cout << "Test of RandGaussT distribution \n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed;	cout << seed << "\n";
  if (seed == 0) {
    cout << "Moving on to next test...\n";
    return 0; 
  }

  int nNumbers;
  cout << "How many numbers should we generate: ";
  cin >> nNumbers; cout << nNumbers << "\n";

  double mu;
  double sigma;
  cout << "Enter mu: ";
  cin >> mu; cout << mu << "\n";

  cout << "Enter sigma: ";
  cin >> sigma; cout << sigma << "\n";

  cout << "\nInstantiating distribution utilizing TripleRand engine...\n";
  TripleRand eng (seed);
  RandGaussT dist (eng, mu, sigma);
 
  cout << "\n Sample  fire(): \n";
  double x;
  
  x = dist.fire();
  cout << x;

  cout << "\n Testing operator() ... \n";

  bool good = gaussianTest ( dist, mu, sigma, nNumbers );

  if (good) { 
    return 0;
  } else {
    return GaussTBAD;
  }

} // testRandGaussT()



// ---------
// RandGaussQ
// ---------

int testRandGaussQ() {

  cout << "\n--------------------------------------------\n";
  cout << "Test of RandGaussQ distribution \n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed;	cout << seed << "\n";
  if (seed == 0) {
    cout << "Moving on to next test...\n";
    return 0; 
  }

  int nNumbers;
  cout << "How many numbers should we generate: ";
  cin >> nNumbers; cout << nNumbers << "\n";

  if (nNumbers >= 20000000) {
    cout << "With that many samples RandGaussQ need not pass validation...\n";
  }

  double mu;
  double sigma;
  cout << "Enter mu: ";
  cin >> mu; cout << mu << "\n";

  cout << "Enter sigma: ";
  cin >> sigma; cout << sigma << "\n";

  cout << "\nInstantiating distribution utilizing DualRand engine...\n";
  DualRand eng (seed);
  RandGaussQ dist (eng, mu, sigma);
 
  cout << "\n Sample  fire(): \n";
  double x;
  
  x = dist.fire();
  cout << x;

  cout << "\n Testing operator() ... \n";

  bool good = gaussianTest ( dist, mu, sigma, nNumbers );

  if (good) { 
    return 0;
  } else {
    return GaussQBAD;
  }

} // testRandGaussQ()


// ---------
// RandPoisson
// ---------

int testRandPoisson() {

  cout << "\n--------------------------------------------\n";
  cout << "Test of RandPoisson distribution \n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed; cout << seed << "\n";
  if (seed == 0) {
    cout << "Moving on to next test...\n";
    return 0; 
  }

  cout << "\nInstantiating distribution utilizing TripleRand engine...\n";
  TripleRand eng (seed);

  int nNumbers;
  cout << "How many numbers should we generate for each mu: ";
  cin >> nNumbers; cout << nNumbers << "\n";

  bool good = true;

  while (true) {
   double mu;
   cout << "Enter a value for mu: ";
   cin >> mu; cout << mu << "\n";
   if (mu == 0) break;

   RandPoisson dist (eng, mu);
 
   cout << "\n Sample  fire(): \n";
   double x;
  
   x = dist.fire();
   cout << x;

   cout << "\n Testing operator() ... \n";

   bool this_good = poissonTest ( dist, mu, nNumbers );
   if (!this_good) {
    cout << "\n Poisson distribution for mu = " << mu << " is incorrect!!!\n";
   }
   good &= this_good;
  } // end of the while(true)

  if (good) { 
    return 0;
  } else {
    return PoissonBAD;
  }

} // testRandPoisson()


// ---------
// RandPoissonQ
// ---------

int testRandPoissonQ() {

  cout << "\n--------------------------------------------\n";
  cout << "Test of RandPoissonQ distribution \n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed; cout << seed << "\n";
  if (seed == 0) {
    cout << "Moving on to next test...\n";
    return 0; 
  }

  cout << "\nInstantiating distribution utilizing TripleRand engine...\n";
  TripleRand eng (seed);

  int nNumbers;
  cout << "How many numbers should we generate for each mu: ";
  cin >> nNumbers; cout << nNumbers << "\n";

  bool good = true;

  while (true) {
   double mu;
   cout << "Enter a value for mu: ";
   cin >> mu; cout << mu << "\n";
   if (mu == 0) break;

   RandPoissonQ dist (eng, mu);
 
   cout << "\n Sample  fire(): \n";
   double x;
  
   x = dist.fire();
   cout << x;

   cout << "\n Testing operator() ... \n";

   bool this_good = poissonTest ( dist, mu, nNumbers );
   if (!this_good) {
    cout << "\n Poisson distribution for mu = " << mu << " is incorrect!!!\n";
   }
   good &= this_good;
  } // end of the while(true)

  if (good) { 
    return 0;
  } else {
    return PoissonQBAD;
  }

} // testRandPoissonQ()


// ---------
// RandPoissonT
// ---------

int testRandPoissonT() {

  cout << "\n--------------------------------------------\n";
  cout << "Test of RandPoissonT distribution \n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed; cout << seed << "\n";
  if (seed == 0) {
    cout << "Moving on to next test...\n";
    return 0; 
  }

  cout << "\nInstantiating distribution utilizing TripleRand engine...\n";
  TripleRand eng (seed);

  int nNumbers;
  cout << "How many numbers should we generate for each mu: ";
  cin >> nNumbers; cout << nNumbers << "\n";

  bool good = true;

  while (true) {
   double mu;
   cout << "Enter a value for mu: ";
   cin >> mu; cout << mu << "\n";
   if (mu == 0) break;

   RandPoissonT dist (eng, mu);
 
   cout << "\n Sample  fire(): \n";
   double x;
  
   x = dist.fire();
   cout << x;

   cout << "\n Testing operator() ... \n";

   bool this_good = poissonTest ( dist, mu, nNumbers );
   if (!this_good) {
    cout << "\n Poisson distribution for mu = " << mu << " is incorrect!!!\n";
   }
   good &= this_good;
  } // end of the while(true)

  if (good) { 
    return 0;
  } else {
    return PoissonTBAD;
  }

} // testRandPoissonT()


// -----------
// RandGeneral
// -----------

int testRandGeneral() {

  cout << "\n--------------------------------------------\n";
  cout << "Test of RandGeneral distribution (using a Gaussian shape)\n\n";

  bool good;
  
  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed; cout << seed << "\n";
  if (seed == 0) {
    cout << "Moving on to next test...\n";
    return 0;
  }

  int nNumbers;
  cout << "How many numbers should we generate: ";
  cin >> nNumbers; cout << nNumbers << "\n";

  double mu;
  double sigma;
  mu = .5; 	// Since randGeneral always ranges from 0 to 1
  sigma = .06;	

  cout << "Enter sigma: ";
  cin >> sigma; cout << sigma << "\n";
		// We suggest sigma be .06.  This leaves room for 8 sigma 
		// in the distribution.  If it is much smaller, the number 
		// of bins necessary to expect a good match will increase.
		// If sigma is much larger, the cutoff before 5 sigma can
		// cause the Gaussian hypothesis to be rejected. At .14, for 
		// example, the 4th moment is 7 sigma away from expectation.

  int nBins;
  cout << "Enter nBins for stepwise pdf test: ";
  cin >> nBins;	cout << nBins << "\n";
		// We suggest at least 10000 bins; fewer would risk 
		// false rejection because the step-function curve 
		// does not match an actual Gaussian.  At 10000 bins,
		// a million-hit test does not have the resolving power
		// to tell the boxy pdf from the true Gaussian.  At 5000
		// bins, it does.

  double xBins = nBins;
  double* aProbFunc = new double [nBins];
  double x;
  for ( int iBin = 0; iBin < nBins; iBin++ )  {
    x = iBin / (xBins-1);
    aProbFunc [iBin] = exp ( - (x-mu)*(x-mu) / (2*sigma*sigma) );
  }
  // Note that this pdf is not normalized; RandGeneral does that

  cout << "\nInstantiating distribution utilizing Ranlux64 engine...\n";
  Ranlux64Engine eng (seed, 3);

 { // Open block for testing type 1 - step function pdf

  RandGeneral dist (eng, aProbFunc, nBins, 1);
  delete aProbFunc;

  double* garbage = new double[nBins]; 
				// We wish to verify that deleting the pdf
			    	// after instantiating the engine is fine.
  for ( int gBin = 0; gBin < nBins; gBin++ )  {
    garbage [gBin] = 1;
  }
  
  cout << "\n Sample fire(): \n";
    
  x = dist.fire();
  cout << x;

  cout << "\n Testing operator() ... \n";

  good = gaussianTest ( dist, mu, sigma, nNumbers );

  delete garbage;

 } // Close block for testing type 1 - step function pdf
   // dist goes out of scope but eng is supposed to stick around; 
   // by closing this block we shall verify that!  

  cout << "Enter nBins for linearized pdf test: ";
  cin >> nBins;	cout << nBins << "\n";
		// We suggest at least 1000 bins; fewer would risk 
		// false rejection because the non-smooth curve 
		// does not match an actual Gaussian.  At 1000 bins,
		// a million-hit test does not resolve the non-smoothness;
		// at 300 bins it does.

  xBins = nBins;
  aProbFunc = new double [nBins];
  for ( int jBin = 0; jBin < nBins; jBin++ )  {
    x = jBin / (xBins-1);
    aProbFunc [jBin] = exp ( - (x-mu)*(x-mu) / (2*sigma*sigma) );
  }
  // Note that this pdf is not normalized; RandGeneral does that

  RandGeneral dist (eng, aProbFunc, nBins, 0);

  cout << "\n Sample operator(): \n";
    
  x = dist();
  cout << x;

  cout << "\n Testing operator() ... \n";

  bool good2 = gaussianTest ( dist, mu, sigma, nNumbers );
  good = good && good2;

  if (good) { 
    return 0;
  } else {
    return GeneralBAD;
  }

} // testRandGeneral()




// **********************
//
// SECTION IV - Main
//
// **********************

int main() {

  int mask = 0;
  
  mask |= testRandGauss();
  mask |= testRandGaussQ();
  mask |= testRandGaussT();

  mask |= testRandGeneral();

  mask |= testRandPoisson();
  mask |= testRandPoissonQ();
  mask |= testRandPoissonT();

  return mask > 0 ? -mask : mask;
}

