// $Id: testVectorDists.cc,v 1.2 2003/08/13 20:00:13 garren Exp $
// -*- C++ -*-
// ----------------------------------------------------------------------

// ----------------------------------------------------------------------
//
// testVectorDists -- tests of the correctness of vector random distributions 
//
// Currently tested:
//	RandMultiGauss
// 
// ----------------------------------------------------------------------

#include "CLHEP/RandomObjects/defs.h"
#include "CLHEP/Random/Randomize.h"
#include "CLHEP/RandomObjects/RandMultiGauss.h"
#include "CLHEP/Matrix/SymMatrix.h"
#include "CLHEP/Matrix/Matrix.h"
#include "CLHEP/Matrix/Vector.h"
#include <iostream>

using namespace std;
using namespace CLHEP;

static const int MultiGaussBAD    = 1 << 0;


static HepMatrix modifiedOutput(const HepMatrix& D) {
  HepMatrix DD (D);
  int n = DD.num_row();
  int m = DD.num_col();
  int i;
  int j;
  for ( i = 1; i <= n; ++i ) {
   for ( j = 1; j <= m; ++j ) {
    if ( DD(i,j)*DD(i,j) < 1.0e-24 * DD(i,i) * DD(j,j) ) DD (i,j) = 0;
   }
  }
  return DD;
}


// --------------
// RandMultiGauss
// --------------

int testRandMultiGauss( ) {

  cout << "\n--------------------------------------------\n";
  cout << "Test of RandMultiGauss distribution \n\n";

  long seed;
  cout << "Please enter an integer seed:        ";
  cin >> seed;

  int nvectors;
  cout << "How many vectors should we generate: ";
  cin >> nvectors;
  double rootn = sqrt((double)nvectors);

  int nMu;
  int nS;
  cout << "Enter the dimensions of mu, then S (normally the same):  ";
  cin >> nMu >> nS;
  if ( nMu != nS ) {
    cout << "Usually mu and S will be of equal dimensions.\n";
    cout << "You may be testing the behavior when that is not the case.\n";
    cout << "Please verify by re-entering the correct dimensions: ";
    cin >> nMu >> nS;
  }
  int dim = (nMu >= nS) ? nMu : nS;

  HepVector    mu(nMu);
  HepSymMatrix S(nS);

  cout << "Enter mu, one component at a time: \n";
  int imu;
  double muElement;
  for (imu = 1; imu <= nMu; imu++) {
    cout << imu << ": ";
    cin >> muElement;
    mu(imu) = muElement;
  }

  cout << "Enter S, one white-space-separated row at a time. \n";
  cout << "The length needed for each row is given in {braces}.\n";
  cout << 
	"The diagonal elements of S will be the first numbers on each line:\n";
  int row, col;
  double sij;
  for (row = 1; row <= nS; row++) {
    cout << row << " {" << nS - row + 1 << " numbers}: ";
    for (col = row; col <= nS; col++) {
      cin >> sij;
      S(row, col) = sij;
    }
  }

  cout << "mu is: \n";
  cout << mu;
  cout << endl;

  cout << "S is: \n";
  cout << S << endl;

  HepSymMatrix tempS ( S ); // Since diagonalize does not take a const s
                            // we have to copy S.
  HepMatrix U = diagonalize ( &tempS );
  HepSymMatrix D = S.similarityT(U);
  cout << "D = Diagonalized S is " << modifiedOutput(D) << endl;
  bool pd = true;
  for ( int npd = 1; npd <= dim; npd++) {
    if ( D(npd,npd) < 0 ) {
	pd = false;
    }
  }
  if (!pd) {
    cout << "S is not positive definite.\n" <<
            "The negative elements of D will have been raised to zero.\n" <<
	    "The second moment matrix at the end will not match S.\n";
  }

  cout << "\nInstantiating distribution utilizing TripleRand engine...\n";
  TripleRand eng (seed);
  RandMultiGauss dist (eng, mu, S);
 
  HepVector x(dim);

  cout << "\n Sample  fire(): \n";

  x = dist.fire();
  cout << x;

  int ntrials;
  cout << "Normal operation will try a single group of " << nvectors 
	<< " random vectors.\n" 
	<< "Enter 1 for a single trial with " << nvectors 
	<< " random vectors.\n" 
	<< "Alternatively some number of groups of " << nvectors 
	<< " vectors can be produced to accumulate deviation statistics.\n"
	<< "Enter " << 5000/(dim*(dim+1))+1 
	<< " or some other number of trials to do this: ";
  cin >> ntrials;
  if (ntrials < 1) return 0;

  cout << "\n Testing fire() ... \n";

// I'm going to accumulate correlation matrix by equation (28.9) RPP
// and compare to the specified matrix S.  That is, E(x-<x>)(y-<y>) should
// be Sxy.
//
// For off-diagonal terms, Sxy = <xy> - <x><y>.
//
// For diagonal terms, Sxx = <x^2> - <x>^2.

  HepSymMatrix Sumxy(nS);
  HepSymMatrix Dprime(dim); 
  HepSymMatrix VarD(dim);
  HepSymMatrix Delta(dim);

  int ipr = nvectors / 10;  if (ipr < 1) ipr = 1;
  int in1 = 0;
  int in2 = 0;
  int in3 = 0;
  int nentries = 0;
  float binno;
  int nbin;
  int bins[30];
  int ix, iy;
//  double root2 = sqrt(2.0);
  double sumDelta = 0.0;
  double sumDelta2 = 0.0;
  int nunder = 0;
  int nover = 0;
  double worstDeviation=0;

  int k;
  for(k=0; k<30; ++k) {
    bins[k] = 0;
  }
  for(k=0; k<ntrials; ++k ) {
    HepVector sumx(dim,0);
    HepMatrix sumxy(dim,dim,0);
    for ( int ifire = 1; ifire <= nvectors; ifire++) {
      x = dist.fire();
      for (ix = 1; ix <= dim; ix++) {
        sumx(ix) += x(ix);
        for (iy = 1; iy <= dim; iy++) {
          sumxy(ix,iy) += x(ix)*x(iy);
        }
      }
      if ( (ifire % ipr) == 0 && k == 0 ) {
        cout << ifire << ", ";
      }
    }
    if( k == 0 )  
	cout << "Statistics for the first (or only) trial of " << nvectors
		<< " vectors:\n\n";

    sumx = sumx / nvectors;
    if( k == 0 ) cout << "\nAverage (should match mu): \n" << sumx << endl;
    for (ix = 1; ix <= dim; ix++) {
      for (iy = 1; iy <= dim; iy++) {
        sumxy(ix,iy) = sumxy(ix,iy) / nvectors - sumx(ix)*sumx(iy);
      }
    }
    if (pd) {
      if( k == 0 )  cout << "Second Moments (should match S)\n" << sumxy << endl;
    } else {
      if( k == 0 )  cout << "Second Moments \n" << sumxy << endl;
    }

// Now transform sumxy with the same matrix that diagonalized S.  Call the
// result Dprime. There is a bit of fooling around here because sumxy is a
// general matrix and similarityT() acts on a symmetric matrix.

    Sumxy.assign(sumxy);
    Dprime = Sumxy.similarityT(U);

    if( k == 0 )  cout << "\nDprime = Second moment matrix transformed by the same matrix that diagonalized S\n" << Dprime << endl;

    for( ix=1; ix<=dim; ++ix ) {
      for( iy=ix; iy<=dim; ++iy ) {
        if( ix == iy ) {
          VarD(ix,iy) = 2.0*Dprime(ix,iy)*Dprime(ix,iy)/rootn;
        } else {
          VarD(ix,iy) =     Dprime(ix,ix)*Dprime(iy,iy)/rootn;
        }
      }
    }
    if( k == 0 )  cout << "\nThe expected variance for Dprime elements is \n" 
				<< VarD << endl;

    for( ix=1; ix<=dim; ++ix ) {
      for( iy=ix; iy<=dim; ++iy ) {
        Delta(ix,iy) = sqrt(rootn)*(D(ix,iy)-Dprime(ix,iy))/sqrt(VarD(ix,iy));
	if (k==0) {
	  if (abs(Delta(ix,iy)) > abs(worstDeviation)) {
	    worstDeviation = Delta(ix,iy);
	  }
	}
      }
    }

    if( k == 0 ) {
      cout 
	<< "\nDifferences between each element and its normative value,\n"
	<< "scaled by the expected deviation (sqrt(variance)) are: \n" 
	<< Delta << endl;
    }

    if( k == 0 ) {
      cout << 
	"About 5% of the above values should have absolute value more than 2.\n"
      << "Deviations of more than 4 sigma would probably indicate a problem.\n";
    }

// Do a little counting

    for( ix=1; ix<=dim; ++ix ) {
      for( iy=ix; iy<=dim; ++iy ) {
        if( Delta(ix,iy) >= -1.0 && Delta(ix,iy) <= 1.0 ) in1++;
        if( Delta(ix,iy) >= -2.0 && Delta(ix,iy) <= 2.0 ) in2++;
        if( Delta(ix,iy) >= -3.0 && Delta(ix,iy) <= 3.0 ) in3++;
        sumDelta += Delta(ix,iy);
        sumDelta2 += Delta(ix,iy)*Delta(ix,iy);
        binno = 5.0*(Delta(ix,iy)+3.0);
        if( binno <  0.0 ) ++nunder;
        if( binno > 30.0 ) ++nover;
        if( binno >= 0.0 && binno < 30.0 ) {
          nbin = (int)binno;
          ++nentries;
          ++bins[nbin];
        }
      }
    }
  }

  if (ntrials == 1) {
    cout << "The worst deviation of any element of D in this trial was "
	<< worstDeviation << "\n";
    if (abs(worstDeviation) > 4) {
      cout << "\nREJECT this distribution: \n" 
	   << "This value indicates a PROBLEM!!!!\n\n";
      return MultiGaussBAD;
    } else {
      return 0;
    }
  } 

  float ndf = ntrials*dim*(dim+1)/2.0;
  cout << "\nOut of a total of " << ndf << " entries" << endl;
  cout << "There are " << in1 << " within 1 sigma or " 
       << 100.0*(float)in1/ndf << "%" << endl;
  cout << "There are " << in2 << " within 2 sigma or "
       << 100.0*(float)in2/ndf << "%" << endl;
  cout << "There are " << in3 << " within 3 sigma or "
       << 100.0*(float)in3/ndf << "%" << endl;
  double aveDelta = sumDelta/(double)ndf;
  double rmsDelta = sumDelta2/(double)ndf - aveDelta*aveDelta;
  cout << "\nFor dim = " << dim << " Average(Delta) = " << aveDelta << "    RMS(Delta) = " << rmsDelta << endl;
  cout << "\nPoor man's histogram of deviations in 30 bins from -3.0 to 3.0" << endl;
  cout << "This should be a standard unit Gaussian.\n" << endl;
  for(k=0; k<30; ++k ) {
    cout << setw(3) << k+1 << "   " << setw(4) << bins[k] << endl;
  }
  cout << "\nTotal number of entries in this histogram is " << nentries << endl;
  cout << "\twith " << nunder << " underflow(s) and " << nover << " overflow(s)" << endl;

  int status;

  cout << "The mean squared delta should be between .85 and 1.15; it is "
       << rmsDelta << "\n";

  if( abs(rmsDelta-1.0) <= 0.15 ) {
    status = false;
  } else {
    cout << "REJECT this distribution based on improper spread of delta!\n";
    status = MultiGaussBAD;
  }
  if (abs(worstDeviation)>4) {
    cout << "REJECT this distribution:  Bad correlation in first trial!\n";
    status = MultiGaussBAD;
  }

  return status;

} // testRandMultiGauss() 

int main() {

  int mask = 0;
  
  mask |= testRandMultiGauss();

  return mask;

}


