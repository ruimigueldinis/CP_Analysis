// The ROOT package allows for small pieces of code to be executed without formally making a "main" program.
// In order for this mechanism to work, the function to be executed must have exactly the same name as the file
// (without the .C extension).
// 
// The code in this file may be executed doing either of the following:
// 1.
// [shell-prompt] root
// root [0]  .x CL.C(123, 40)+
// 2.
// [shell-prompt] root -l CL.C(123,40)+
//
// where the first parameter corresponds to the hypothesised mass to test, and the second is the number of (equidistant) bins
// in which to subdivide the mass range from 110 to 150 GeV (a negative number is taken to imply an unbinned fit).
//
// It is also possible to run the macro code in interpreted rather than compiled mode (by omitting the "+" at the end),
// but for anything beyond the simplest piece of code I recommend not using this feature.

#include "TCanvas.h"
#include "TLine.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TMath.h"
#include "TList.h"
#include "TRandom3.h"
#include "TVirtualFitter.h"
#include <math.h>
#include <Riostream.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Math/Math.h"
#include "Math/Error.h"
#include "Math/ProbFuncMathCore.h"
#include "Math/SpecFuncMathCore.h"
#include <stdio.h>
#include <limits>

using namespace std;

//dilep
//std::vector<int> binGroup = {8,8,8,8};
//std::vector<int> histoGroup = {4};
//semilep
//std::vector<int> binGroup = {20,15};
//std::vector<int> histoGroup = {2};
//all
//std::vector<int> binGroup = {5,8,8,20,15};
//std::vector<int> histoGroup = {3,2};
//dilep single
// _______________for 2 bin distributions_____________
//std::vector<int> binGroup = {2};
//std::vector<int> histoGroup = {1};
// _______________for 8 bin distributions_____________
//std::vector<int> binGroup = {8};
//std::vector<int> histoGroup = {1};
// _______________for 9 bin distributions________________________________22 May 2023___
std::vector<int> binGroup = {9};   // use root6
std::vector<int> histoGroup = {1}; 
// _______________for 9 bin distributions________________________________22 May 2023___
//l+jets b4
//std::vector<int> binGroup = {1};
//std::vector<int> histoGroup = {1};
//l+jets other
//std::vector<int> binGroup = {15};
//std::vector<int> histoGroup = {1};
// -------------------------------------------------------------------
// Define Minimum and Maximum X-Coordinate Values for p.d.f. (asym==2)
// -------------------------------------------------------------------
double X_Low_AsymPDF = -999.;
double X_Hig_AsymPDF = +999.;
// -------------------------------------------------------------------


double Median_Vec(vector<double> scores) {
  // vector size
  size_t size = scores.size();

  if (size == 0) { return 0; 
  } else {
    sort(scores.begin(), scores.end());
    if (size % 2 == 0)  { return (scores[size / 2 - 1] + scores[size / 2]) / 2; }
    else 		{ return scores[size / 2];                              }
  }
}


// function to generate a Poisson-fluctuated set of numbers
std::vector<double> generateToyDistribution(TH1D* histogram) {
  // make sure to instantiate the random number generator only once (otherwise it might generate the same
  // set of random numbers every time)
  static TRandom3 rnd;
  
  std::vector<double> results;
  if (results.size()>0) results.clear();

  int lastbin=0, firsthisto=0;
  std::vector<int> nEvents = {0,0};

  //loop over channels
  for (unsigned int ichannel=0; ichannel<histoGroup.size(); ichannel++) {
      //loop over bins of first distribution in channel to Poisson-generate the value in each one
      //also determine number of events in channel
      for (unsigned int ibin = lastbin+1; ibin < (unsigned) lastbin+1+binGroup[firsthisto]; ibin++) {
          double result = rnd.Poisson(histogram->GetBinContent(ibin));
          results.push_back(result);
	        nEvents[ichannel]+=result;
      }
      //cout << "generated with " << nEvents[ichannel] << " events in channel " << ichannel << endl;
      //update lastbin for next histos      
      lastbin+=binGroup[firsthisto];
      //loop over remaining histograms in channel
      for (int ihisto=firsthisto+1; ihisto<firsthisto+histoGroup[ichannel]; ihisto++) {
	        //create temporary histogram from subrange of input histogram          
	        TH1D* tempHist      = new TH1D("temp","temp",binGroup[ihisto],0,binGroup[ihisto]);
	        for (int ibin = 1; ibin<1+binGroup[ihisto]; ibin++) tempHist->SetBinContent(ibin,histogram->GetBinContent(lastbin+ibin));
	        //clone it and fill the clone with nEvents using pdf from previous histo
          	TH1D* tempHistClone = new TH1D;
          	tempHistClone = (TH1D*) tempHist->Clone("tempClone");
          	tempHistClone->Reset();
	        tempHistClone->FillRandom(tempHist,nEvents[ichannel]);
	        //loop over bins to save results into... well, results!
	        for (int ibin = 1; ibin<1+binGroup[ihisto]; ibin++) results.push_back(tempHistClone->GetBinContent(ibin));
	        delete tempHist;
	        delete tempHistClone;
	        //update lastbin for next histo
          	lastbin+=binGroup[ihisto];
      }
      //update firsthisto for next channel
      firsthisto+=histoGroup[ichannel];
  }

//  for (unsigned int bin = 0; bin < (unsigned) histogram->GetNbinsX(); ++bin) {
//    results.push_back(rnd.Poisson(histogram->GetBinContent(bin+1)));
//  }

  //cout << "returned results with " << results.size() << " elements" << endl;
  return results;
}

// ----------------------------------------------------------------------------------------------------------------------
double logLikelihood(const std::vector<double>& observed, TH1D* predicted, bool extended) {
// ----------------------------------------------------------------------------------------------------------------------
// function to compute the logarithm of the Poisson likelihood for an observed distribution given a certain expectation.
// NOTE: There is no cross-check on the compatibility of the two sets of bins.
// ----------------------------------------------------------------------------------------------------------------------
  double LL = 0;
  // Since we need to deal with both the normal and the extended likelihood, we decouple the
  // normalisation from the shape explicitly

  std::vector<double> mu = {0.,0.};
  int firstbin=0, firsthisto=0;
  for (int unsigned ichannel=0; ichannel<histoGroup.size(); ichannel++){
      unsigned int ntot = 0;
      //loop over bins of first histo in this channel to get predicted and observed number of events in this channel
      for (unsigned int ibin = firstbin+1; ibin < (unsigned) firstbin+1+binGroup[firsthisto]; ibin++){
          mu[ichannel]+=predicted->GetBinContent(ibin);
          ntot += observed[ibin-1];
      }
      //cout << "channel " << ichannel << " has " << mu[ichannel] << " events predicted and " << ntot << " observed in channel " << ichannel << endl;
      //loop over histograms for multinomial probability
      for (unsigned int ihisto = firsthisto; ihisto< (unsigned) firsthisto+histoGroup[ichannel]; ihisto++){
          //loop over bins, updating the log likelihood in each one
          for (unsigned int ibin = firstbin+1; ibin < (unsigned) firstbin+1+binGroup[ihisto]; ibin++){
              int n=observed[ibin-1];
              double p=predicted->GetBinContent(ibin)/mu[ichannel];
              if (p>0.) LL+= double(n)*TMath::Log(p);
          }
          //update firstbin for the next histogram
          firstbin+=binGroup[ihisto];
      }
      //update firsthisto for the next channel
      firsthisto+=histoGroup[ichannel];
      if (extended) LL+=double(ntot)*TMath::Log(mu[ichannel]) - mu[ichannel];
  }

  //double mu = 0;
  //for (unsigned int bin = 0; bin < observed.size(); ++bin) mu += predicted->GetBinContent(bin+1);

  //// First compute the multinomial probability
  //unsigned int ntot = 0;
  //for (unsigned int bin = 0; bin < observed.size(); ++bin) {
  //  // also note that we ignore the factorial terms. This will clearly change the likelihood; however,
  //  // since these terms do not depend on the hypothesis they will cancel in the ratio.
  //  unsigned int n = observed[bin]; double p = predicted->GetBinContent(bin+1)/mu;
  //  ntot += n;
  //  if (p > 0) LL += double(n)*TMath::Log(p);
  //  // std::cout << " mu, n, LL: " << mu << "," << n << "," << LL << std::endl;
  //}
  //// For the extended case, add the contribution from the overall normalisation
  //if (extended)
  //  LL += double(ntot)*TMath::Log(mu) - mu;
  
  return LL;
}
// ----------------------------------------------------------------------------------------------------------------------

// ----------------------------------------------------------------------------------------------------------------------
double logLikelihoodAsymmetries(int selProb, const std::vector<double>& observed, TH1D* predicted, bool extended, TH1D* PDF_k_ktil, bool selFunc, TF1* Func_PDF_k_ktil) {
// ----------------------------------------------------------------------------------------------------------------------
// function to compute the logarithm of the Skellam function (pdf distribution of the difference of two Poisson 
// likelihood distributions) for an observed distribution given a certain expectation.
// NOTE: There is no cross-check on the compatibility of the two sets of bins.
// ----------------------------------------------------------------------------------------------------------------------

  // ......................................................
  // define flag to set the methods  ......................
  // ......................................................
  // selProb      =1  use Asymmetry value directly
  //              =2  use Asymmetry PDF to compute probabilities
  //              =3  use R = log( p2 / p1 )
  //              =4  use P = log( p2 * p1 )
  // ......................................................
  
  // initialize likelihood ................................
  double   LL = 0.0;
  // ......................................................
  // ......................................................


  std::vector<double> mu = {0.,0.};
  int firstbin=0, firsthisto=0;
  for (int unsigned ichannel=0; ichannel<histoGroup.size(); ichannel++){  // ........channels loop....................... 

    // ..........................................................................histograms loop ........
    for (unsigned int ihisto = firsthisto; ihisto< (unsigned) firsthisto+histoGroup[ichannel]; ihisto++){

         // get Observed first (N1) and second (N2) bin values for asymmetry definition N=(N2-N1)
         int    N1  = observed[firstbin];
         int    N2  = observed[firstbin+1];
         // calculate Observed Asymmetry
         double    Z = ( double(N2) - double(N1) ) / ( double(N2) + double(N1) );
         // calculate Observed probabilities p1 and p2
         double    p1 = double(N1) / ( double(N2) + double(N1) );
         double    p2 = double(N2) / ( double(N2) + double(N1) );
         // Ratio
         double                      R =  0.0;
         if ( p1 > 0.0 && p2 > 0.0 ) R = TMath::Log( p2 / p1 );
         // Product
         double                      P =  0.0;
         if ( p1 > 0.0 && p2 > 0.0 ) P = TMath::Log( p2 * p1 );

         // get Expected first (mu1) and second (mu2) bin values and uncertainties
         double  mu1 = predicted->GetBinContent(firstbin+1);
         double sig1 = predicted->GetBinError  (firstbin+1);
         double  mu2 = predicted->GetBinContent(firstbin+2);
         double sig2 = predicted->GetBinError  (firstbin+2);
         // define X and Y variables, means and errors
         double  muX = ( mu2 - mu1 ); 
         double  muY = ( mu2 + mu1 ); 
         double sigX = TMath::Sqrt( sig1*sig1 + sig2*sig2 ); 
         double sigY = TMath::Sqrt( sig1*sig1 + sig2*sig2 ); 

         // --------------------------------------
         // use asymmetry itself
         // --------------------------------------
         if ( selProb == 1 ){
            LL += Z;
         }
         // --------------------------------------
         // use pdf of Z=X/Y, X=N2-N1 and Y=N2+N1
         // --------------------------------------
         if ( selProb == 2 ){
              TAxis *xaxis = PDF_k_ktil->GetXaxis();
              if ( Z > X_Low_AsymPDF && Z < X_Hig_AsymPDF ) {
                double prob; 
                // choose if fit function of p.d.f. is the choice
                if ( !selFunc ) {
                      // === get info from p.d.f. histo
                      int ibin = xaxis->FindBin( Z );
                      prob = PDF_k_ktil->GetBinContent( ibin );
                } else {
                      // === get info from p.d.f. function
                      prob = Func_PDF_k_ktil->Eval( Z );                  
                }
                // update LL value
                if (prob>0.) LL+= TMath::Log(prob);
              }
         }
         // --------------------------------------
         // use Ratio = log( p2/p1 )
         // --------------------------------------
         if ( selProb == 3 ){
            LL += R;
         }
         // --------------------------------------
         // use Product = log ( p2*p1 )
         // --------------------------------------
         if ( selProb == 4 ){
            LL += P;
         }
          //cout << " ------------------- LL = " << LL << endl;
          //update firstbin for the next histogram
          firstbin+=binGroup[ihisto];
    }
    // ..........................................................................histograms loop ........
    //update firsthisto for the next channel
    firsthisto+=histoGroup[ichannel];
  } // ..............................................................................channels loop....................... 
  // output likelihood result
  return LL;
}
// ----------------------------------------------------------------------------------------------------------------------


void CL_2D_8bins( std::string indir, std::string infileH, std::string infileA, double scale = 1, std::string cosa = "", unsigned int ntest = 1000000, int pseudo = 0, int sample = 1, int asym = 0, bool extended = true) {
  /* meaning of the arguments:
     - indir:       directory from which to read the input histograms
     - infile(H/A): root file containing histograms for null/alternative hypothesis
     - scale:       scale factor to be applied to all input histograms (can be used to investigate the sensitivity dependence on integrated luminosity)
     - ntest:       number of toy experiments
     - assumeH:     if true, use the bkg+ttH histogram as a basis for pseudo-data generation (if false, use bkg+ttA)
     - hPseudo:      what is the assumed scenario hypothesis (typically b-only or SM hypothesis). 0=SM, 1=SM+ttH, 2=SM+ttA
     - hSample:      what is the hypothesis to exclude (typically s+b or new physics hypothesis). 0=SM, 1=SM+ttH, 2=SM+ttA
     In the end, statement will be: given hPseudo (null), we can exclude hSample (signal) up to a XX% CL
     - extented:    if true, use an extended likelihood rather than an ordinary one
   */

  // ---------------------------------------------------------------------------------
  // Use PDF Distributions from Fits to Asymmetries PDFs (after run with asym=1)
  // ---------------------------------------------------------------------------------
  bool  usePDF_from_Fit = false;    // =false   Use p.d.f. directly from histograms
                                    // =true    Use p.d.f. fits instead (if true choose in the flag below if course gain or continuous function)
  bool  funPDF_from_Fit = false;    // =true    Use p.d.f. fits instead: use continuous fitting function
                                    // =false   Use p.d.f. fits instead: use course gain histogram
  // ---------------------------------------------------------------------------------
  // Use Angular Distributions (asym=0) or Asymmetries (asym=1)
  // ---------------------------------------------------------------------------------
  std::string    TestStatOutfile = "TestStatHistos/TestStat_"     + infileA + "_pseudo" + std::to_string(pseudo) + "_sample" + std::to_string(sample) + ".root";
  std::string useTestStatOutfile = "TestStatHistos/Use/TestStat_" + infileA + "_pseudo" + std::to_string(pseudo) + "_sample" + std::to_string(sample) + ".root";
  TFile    *MyTestStatOutfile; 
  TFile    *MyuseTestStatOutfile; 

  cout << endl;
  cout << endl;
  cout << " ------------------------------------------------------------------------------- " << endl; 
  cout << " ------------------------------------------------------------------------------- " << endl; 
  MyTestStatOutfile = new TFile( TestStatOutfile.c_str() , "RECREATE" );
  cout << " ......ALL Test Statistics Probability Density Functions and Fits Saved to File: " << TestStatOutfile << endl;
  cout << " ------------------------------------------------------------------------------- " << endl; 
  if ( asym == 0  )  cout << " .............Angular Distributions Used in Limits Evaluation....." << endl;
  if ( asym == 1 || 
       asym == 3 || 
       asym == 4 )    cout << " .............       Asymmetries    Used in Limits Evaluation....." << endl;
  if ( asym == 2  ){  cout << " .............  PDF  Asymmetries    Used in Limits Evaluation....." << endl;
                      MyuseTestStatOutfile = new TFile( useTestStatOutfile.c_str() );
                      cout << " ......USE PDF Test Statistics Probability Density Functions from File: " << useTestStatOutfile << endl;
                   }
  cout << " ------------------------------------------------------------------------------- " << endl; 
  cout << " ------------------------------------------------------------------------------- " << endl; 
  cout << endl;
  cout << endl;

  // ---------------------------------------------------------------------------------
  // create the histograms (and, for the unbinned likelihood case, the unbinned data)
  // ---------------------------------------------------------------------------------
  TH1D* hbkg_orig = 0; TH1D* httH_orig = 0; TH1D* httA_orig = 0; 
  TH1D* hLLR_PDF  = 0; TH1D* hLLR_null_PDF     = 0;
  // -------------------------------------------------------------------
  // Define Function(s) for PDF (asym == 2)
  // -------------------------------------------------------------------
  TF1* func_hLLR_PDF;
  TF1* func_hLLR_null_PDF;
  // -------------------------------------------------------------------
  TFile* fttH = TFile::Open((indir+"/"+infileH).c_str(), "READ");
  TFile* fttA = TFile::Open((indir+"/"+infileA).c_str(), "READ");
  fttH->GetObject("Background"           , hbkg_orig);
  fttH->GetObject("Signal"               , httH_orig);
  fttA->GetObject(("Signal"+cosa).c_str(), httA_orig);
  // check if histograms are present in the input files  
  if (!hbkg_orig || !httH_orig || !httA_orig) {
    std::cerr << "error reading histograms!" << std::endl;
    return;
  }
  // use correct error evaluation
  hbkg_orig->Sumw2();
  httH_orig->Sumw2();
  httA_orig->Sumw2();
  // apply "luminosity" scale factors to the input histograms
  hbkg_orig->Scale(scale);
  httH_orig->Scale(scale*1.0); // assume kt=1 if kt!=1, multiply by kt^2
  httA_orig->Scale(scale*1.0); // assume kt=1 if kt!=1, multiply by kt^2
  // ---------------------------------------------------------------------------------

  // ---------------------------------------------------------------------------------
  // Start 2D Scan:     Xsec(mixed) = k^2 * Xsec(CP-even) + ktil^2 * Xsec(CP-odd)
  // ---------------------------------------------------------------------------------
  // k-parameter    (Re part)
  //double k_low = -1.525;
  //double k_hig =  1.525;
  //double k_stp =  0.05;
  // ---low mass values for 3000fb-1
  //double k_low = -1.0125;
  //double k_hig =  1.0125;
  //double k_stp =  0.0150;
  // ---125GeV mass values for 3000fb-1
  //double k_low = -1.525; // -2.01;
  //double k_hig =  1.525; //  2.01;
  //double k_stp =  0.050; //  0.02;    // ********** Paper2021 OFICIAL= 0.020 **********
  //int    kStep = int( ( k_hig - k_low ) / k_stp );
  //double k_low = -1.5075; // -2.01;
  //double k_hig =  1.5075; //  2.01;
  //double k_stp =  0.0150; //  0.02;    // ********** Paper2021 OFICIAL= 0.020 **********
  //int    kStep = int( ( k_hig - k_low ) / k_stp );
  // ---125GeV mass values for 139fb-1
  //double k_low = -2.01; // -2.025;
  //double k_hig =  2.01; //  2.025;
  //double k_stp =  0.02; //  0.050;    // ********** Paper2021 OFICIAL= 0.020 **********
  //int    kStep = int( ( k_hig - k_low ) / k_stp );
  // ktil-parameter (Im part)
  //double ktil_low = -1.525;
  //double ktil_hig =  1.525;
  //double ktil_stp =  0.05;
  // ---low mass values for 3000fb-1
  //double ktil_low = -1.0125;
  //double ktil_hig =  1.0125;
  //double ktil_stp =  0.0150;
  // ---125GeV mass values for 3000fb-1
  //double ktil_low = -1.525; // -2.01;
  //double ktil_hig =  1.525; //  2.01;
  //double ktil_stp =  0.050; //  0.02; // ********** Paper2021 OFICIAL= 0.020 **********
  //int    ktilStep = int( ( ktil_hig - ktil_low ) / ktil_stp );
  //double ktil_low = -1.0125; // -2.01;
  //double ktil_hig =  1.0125; //  2.01;
  //double ktil_stp =  0.0150; //  0.02; // ********** Paper2021 OFICIAL= 0.020 **********
  //int    ktilStep = int( ( ktil_hig - ktil_low ) / ktil_stp );
  // ---125GeV mass values for 139fb-1
  //double ktil_low = -2.01;   // -2.025;
  //double ktil_hig =  2.01;   //  2.025;
  //double ktil_stp =  0.02;   //  0.050; // ********** Paper2021 OFICIAL= 0.020 **********
  //int    ktilStep = int( ( ktil_hig - ktil_low ) / ktil_stp );
  //
  // ---------------------------------------------------------------------------------
  // Dark Matter Mass Scan
  // ---------------------------------------------------------------------------------
  // $$$$$$$$$$$$$$$$$$$$$$$$$$$$      C A S E = ( 0 , 2 )      $$$$$$$$$$$$$$$$$$$$$$
  // ---------------------------------------------------------------------------------
  // #######  200 fb-1  #######
  // k 
  //  double k_low = -0.00125; // k_low = -0.0025; //  k_low = -0.3025;   default
  //  double k_hig =  0.30125; // k_hig =  0.3025; //  k_hig =  0.3025;   default
  //  double k_stp =  0.00250; // k_stp =  0.0050; //  k_stp =  0.0050;   default 
  //  int    kStep = int( ( k_hig - k_low ) / k_stp );
  // ktilde
  //  double ktil_low = -0.005; // ktil_low = -0.01; // ktil_low = -2.01;  default
  //  double ktil_hig =  2.005; // ktil_hig =  2.01; // ktil_hig =  2.01;  default
  //  double ktil_stp =  0.010; // ktil_stp =  0.02; // ktil_stp =  0.02;  default
  //  int    ktilStep = int( ( ktil_hig - ktil_low ) / ktil_stp );
  // #######  3000 fb-1 #######
  // // k 
  //   double k_low = -0.5075;
  //   double k_hig =  0.5075;
  //   double k_stp =  0.0050; 
  //   int    kStep = int( ( k_hig - k_low ) / k_stp );
  // // ktilde
  //   double ktil_low = -1.0125;
  //   double ktil_hig =  1.0125;
  //   double ktil_stp =  0.0150;
  //   int    ktilStep = int( ( ktil_hig - ktil_low ) / ktil_stp );
  // 
  // ---------------------------------------------------------------------------------
  // $$$$$$$$$$$$$$$$$$$$$$$$$$$$      C A S E = ( 1 , 2 )      $$$$$$$$$$$$$$$$$$$$$$
  // ---------------------------------------------------------------------------------
  // // #######  200 fb-1, 3000 fb-1  #######
  // // k 
     double k_low =  0.8990;    // 0.8990; (default)    
     double k_hig =  1.1010;    // 1.1010; (default)   
     double k_stp =  0.0010;    // 0.0020; (default)    
     int    kStep = int( ( k_hig - k_low ) / k_stp );
  // // ktilde
     double ktil_low = -4.01;   //  -4.02; (default)
     double ktil_hig =  4.01;   //   4.02; (default)
     double ktil_stp =  0.02;   //   0.04; (default)
     int    ktilStep = int( ( ktil_hig - ktil_low ) / ktil_stp );
  // // ---------------------------------------------------------------------------------
  // loop over the different    k, ktil values   -------------------------------------
  // k = Re()
//for (unsigned int iRe=int(kStep/2); iRe<= kStep; iRe++){ // This is the one we should use for k>0  Partial Rartial range coverage
  for (unsigned int iRe=0; iRe<= kStep; iRe++){            // This is the one we should use for FULL k range coverage !!!!!!!!
    // ktil = Im()
    for (unsigned int iIm=0; iIm<= ktilStep; iIm++){

         // (Re, Im) = (k, ktil)
         double k    =    k_low + iRe *    k_stp;
         double ktil = ktil_low + iIm * ktil_stp;
         // 
         double k2    =  k   *  k  ;
         double ktil2 = ktil * ktil;
         cout << endl;
         cout << "#### ---------------------------------------------------------------------------------------------------------------------------------------- ####" << endl;
         cout << "#### -------------------------------------------------------------------------------------------- New Scan Point: k(Re)=" << k << "   k~(Im)=" << ktil << " ------ #### " << endl;
         cout << "#### ---------------------------------------------------------------------------------------------------------------------------------------- ####" << endl;

         // Define names for p.d.f. Histogram (if asym == 2 )
         std::string   TestStat_hLLR          = "hLLR_k"      + std::to_string(k) + "_ktil" + std::to_string(ktil);
         std::string   TestStat_hLLR_null     = "hLLR_null_k" + std::to_string(k) + "_ktil" + std::to_string(ktil);
         // Define names for fit p.d.f Histograms
         std::string   TestStat_hLLR_fit      = "hLLR_k"      + std::to_string(k) + "_ktil" + std::to_string(ktil) + "_fit";
         std::string   TestStat_hLLR_null_fit = "hLLR_null_k" + std::to_string(k) + "_ktil" + std::to_string(ktil) + "_fit";
         if ( asym == 2 ) {
              // Choose Signal Hypothesis p.d.f. probability distibution to be used for the Q test
              if ( usePDF_from_Fit ) {
                    hLLR_PDF      = (TH1D*)MyuseTestStatOutfile->Get(TestStat_hLLR_fit.c_str());
                    hLLR_PDF      ->Scale(1./hLLR_PDF->Integral());
                    // fit the pdf distribution and store the information
                         hLLR_PDF ->Fit("gausn" );
                    func_hLLR_PDF = hLLR_PDF->GetFunction("gausn" );          
              } else {
                    hLLR_PDF      = (TH1D*)MyuseTestStatOutfile->Get(TestStat_hLLR.c_str());
                    hLLR_PDF      ->Scale(1./hLLR_PDF->Integral());
              }
              // Get minimum and maximum limits of p.d.f.
              int nPDFbins  = hLLR_PDF->GetXaxis()->GetNbins();
              X_Low_AsymPDF = hLLR_PDF->GetXaxis()->GetBinLowEdge(    1     );
              X_Hig_AsymPDF = hLLR_PDF->GetXaxis()->GetBinUpEdge ( nPDFbins );
              cout << endl;
              cout << "#### ---------------------- PDF Test Statistics Probability Density Functions " << endl;
              cout << "#### ----- Signal Hypothesis   hLLR_PDF       Mean: " << hLLR_PDF->GetMean() << "    RMS: " << hLLR_PDF->GetRMS() << endl;
              cout << "#### -----                     hLLR_PDF      x-Low: " <<    X_Low_AsymPDF    << "  x-Hig: " <<    X_Hig_AsymPDF   << endl;
              // Choose Null Hypothesis p.d.f. probability distibution to be used for the Q test
              if ( usePDF_from_Fit ) {
                    hLLR_null_PDF = (TH1D*)MyuseTestStatOutfile->Get(TestStat_hLLR_null_fit.c_str());
                    hLLR_null_PDF ->Scale(1./hLLR_null_PDF->Integral());
                    // fit the NULL hypothesis p.d.f. distribution and store the information in func_hLLR_null_PDF
                         hLLR_null_PDF ->Fit("gausn" );
                    func_hLLR_null_PDF = hLLR_null_PDF->GetFunction("gausn" );
              } else {
                    hLLR_null_PDF = (TH1D*)MyuseTestStatOutfile->Get(TestStat_hLLR_null.c_str());
                    hLLR_null_PDF      ->Scale(1./hLLR_null_PDF->Integral());
              }
              nPDFbins = hLLR_null_PDF->GetXaxis()->GetNbins();
              if ( hLLR_null_PDF->GetXaxis()->GetBinLowEdge(    1     ) > X_Low_AsymPDF ) X_Low_AsymPDF = hLLR_null_PDF->GetXaxis()->GetBinLowEdge(     1    );
              if ( hLLR_null_PDF->GetXaxis()->GetBinLowEdge( nPDFbins ) < X_Hig_AsymPDF ) X_Hig_AsymPDF = hLLR_null_PDF->GetXaxis()->GetBinLowEdge( nPDFbins );
              cout << "#### ----- Null   Hypothesis   hLLR_null_PDF  Mean: " << hLLR_null_PDF->GetMean() << "    RMS: " << hLLR_null_PDF->GetRMS() << endl;
              cout << "#### -----                     hLLR_null_PDF x-Low: " <<      X_Low_AsymPDF       << "  x-Hig: " <<       X_Hig_AsymPDF     << endl;
              cout << "#### ---------------------- PDF Test Statistics Probability Density Functions " << endl;
              cout << endl;
         }

         // create copies of original histograms
         TH1D *httH  = (TH1D*) httH_orig->Clone("ttH"); 	httH->Sumw2();
         TH1D *httA  = (TH1D*) httA_orig->Clone("ttA"); 	httA->Sumw2();
         TH1D *hbkg  = (TH1D*) hbkg_orig->Clone("ttH"); 	hbkg->Sumw2();
         
         // create CP mixed distribution
         TH1D *httHmix  = (TH1D*) httH->Clone("ttHmix"); httHmix->Sumw2();
         httHmix->Scale(   k2  );
         httA   ->Scale( ktil2 );
         httA   ->Add(httHmix);
         //smooth to reduce sensitivity to fluctuations
         //hbkg->Smooth(40);
         //httH->Smooth(40);
         //httA->Smooth(40);
         
         // these are the two hypotheses against which we test our (pseudo)data
         httH->Add(hbkg);
         httA->Add(hbkg);
         //httA->Add(httH);
         //rebin
         //hbkg->Rebin(5);
         //httH->Rebin(5);
         //httA->Rebin(5);
         cout << "NOTE:   httH has in this test " << httH->GetNbinsX() << " bins" << endl;
         
         // define our pseudo-dataset
         TH1D* hPseudo;
         TH1D* hSample;
         if (pseudo==0) {
              hPseudo = (TH1D*) hbkg->Clone("hPseudo");
         } else if (pseudo==1) {
              hPseudo = (TH1D*) httH->Clone("hPseudo");
         } else if (pseudo==2) {
              hPseudo = (TH1D*) httA->Clone("hPseudo");
         }
         if (sample==0) {
              hSample = (TH1D*) hbkg->Clone("hSample");
         } else if (sample==1) {
              hSample = (TH1D*) httH->Clone("hSample");
         } else if (sample==2) {
              hSample = (TH1D*) httA->Clone("hSample");
         }
         
         // --------------------------------------------------------------------------------------------------------------------------------------
         // generate the LLR distribution for the assumed hypothesis. Since the number of required toy experiments
         // may need to be very large, and since the output values are not a priori known, we simply store the values in a vector.
         // --------------------------------------------------------------------------------------------------------------------------------------
         std::vector<double> LLRs_null;
         double foundMin = 0, foundMax = 0;
         for (unsigned int t = 0; t < ntest; ++t) {
           if (t%100000==0) cout << "Generating toy number " << t << " of assumed hypothesis." << endl;
           std::vector<double> toy = generateToyDistribution(hPseudo);
           // --------------------------------------------------------- Poisson or Skellam Likelihoods --------------------------
           double LLR; 
           if ( asym == 0 ) LLR =         logLikelihood(toy, hSample, extended) - logLikelihood(toy, hPseudo, extended);
           if ( asym == 1 ) LLR =         logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF);
         //if ( asym == 2 ) LLR = -2. * ( logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_PDF,      funPDF_from_Fit, func_hLLR_PDF  ) 
         //                             - logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_null_PDF, funPDF_from_Fit, func_hLLR_null_PDF) );
           if ( asym == 2 ) LLR = -2. * ( logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF) );
           if ( asym == 3 ) LLR =         logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF);
           if ( asym == 4 ) LLR =         logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF);
           // --------------------------------------------------------- Poisson or Skellam Likelihoods --------------------------
           LLRs_null.push_back(LLR);
           // also keep track of the minimum and maximum values (this is for convenience only)
           if (t == 0) {
             foundMin = foundMax = LLR;
           } else if (LLR < foundMin) {
             foundMin     = LLR;
           } else if (LLR > foundMax) {
             foundMax     = LLR;
           }
         }
	       // AO May 7, 2020 ----- Calculate Min and Max -----------------------------------------------
	       double LLR_null_Min = foundMin;
	       double LLR_null_Max = foundMax;
	       // AO May 7, 2020 ----- Calculate Min and Max -----------------------------------------------
	       // --------------------------------------------------------------------------------------------------------------------------------------

  
         // --------------------------------------------------------------------------------------------------------------------------------------
         // generate the LLR distribution for the requested hypothesis. Since the number of required toy experiments
         // may need to be very large, and since the output values are not a priori known, we simply store the values in a vector.
         // --------------------------------------------------------------------------------------------------------------------------------------
         std::vector<double> LLRs;
         // AO May 7, 2020 ----- Calculate Min and Max -----------------------------------------------
         double LLRs_Min = 0.0;
         double LLRs_Max = 0.0;
         // AO May 7, 2020 ----- Calculate Min and Max -----------------------------------------------
         for (unsigned int t = 0; t < ntest; ++t) {
           if (t%100000==0) cout << "Generating toy number " << t << " of tested hypothesis." << endl;
           std::vector<double> toy = generateToyDistribution(hSample);
           // --------------------------------------------------------- Poisson or Skellam Likelihoods --------------------------
           double LLR;
           if ( asym == 0 ) LLR =         logLikelihood(toy, hSample, extended) - logLikelihood(toy, hPseudo, extended);
           if ( asym == 1 ) LLR =         logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF);
         //if ( asym == 2 ) LLR = -2. * ( logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_PDF,      funPDF_from_Fit, func_hLLR_PDF   ) 
         //                             - logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_null_PDF, funPDF_from_Fit, func_hLLR_null_PDF) );
           if ( asym == 2 ) LLR = -2. * ( logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF) );
           if ( asym == 3 ) LLR =         logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF);
           if ( asym == 4 ) LLR =         logLikelihoodAsymmetries(asym, toy, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF);
           // --------------------------------------------------------- Poisson or Skellam Likelihoods --------------------------
           LLRs.push_back(LLR);
           // also keep track of the minimum and maximum values (this is for convenience only)
           if (LLR < foundMin) {
             foundMin = LLR;
           } else if (LLR > foundMax) {
             foundMax = LLR;
           }
           // AO May 7, 2020 ----- Calculate Min and Max ---------------------------------------------
           if      (    t == 0    ) {  LLRs_Min = LLRs_Max = LLR; }
           else if (LLR < LLRs_Min) {  LLRs_Min = LLR;            }
           else if (LLR > LLRs_Max) {  LLRs_Max = LLR;            }
           // AO May 7, 2020 ----- Calculate Min and Max ---------------------------------------------
         }
         cout << "minimum and maximum LLR values found: (" << foundMin << "," << foundMax << ")" << std::endl;
         double delta = (foundMax-foundMin)*0.05;
         // --------------------------------------------------------------------------------------------------------------------------------------


         // --------------------------------------------------------------------------------------------------------------------------------------
         // create (and fill) a histogram to visualise the distribution of the (logarithm of the) likelihood ratio under the requested hypothesis
         // --------------------------------------------------------------------------------------------------------------------------------------
         int n_hLLR_null;
         int n_hLLR_null_fit;
         if ( asym == 1 ) { n_hLLR_null =  100; n_hLLR_null_fit =  500; }
         else             { n_hLLR_null =  500; n_hLLR_null_fit =  500; }
         TH1D* hLLR_null     = new TH1D("hLLR_null",
                               Form("log(L(sample)/L(pseudo)) sampling distribution under pseudo hypothesis, using an %s LH", extended ? "extended" : "ordinary"),
                               n_hLLR_null, foundMin-delta, foundMax+delta);
                             //n_hLLR_null, foundMin-delta, 15.0);
         TH1D* hLLR_null_fit = new TH1D("hLLR_null_fit",
                               Form("fit log(L(sample)/L(pseudo)) sampling distribution under pseudo hypothesis, using an %s LH", extended ? "extended" : "ordinary"),
                               n_hLLR_null_fit, foundMin-delta, foundMax+delta);
                             //n_hLLR_null_fit, foundMin-delta, 15.0);
         // --------------------------------------------------------------------------------------------------------------------------------------
         // AO May 7, 2020 ----- Calculate Mean and Sigma ----------------------------------------------------------------------------------------
         double LLR_null_Mean     = 0.0;
         double LLR_null_Sig      = 0.0;
         double LLR_null_x2       = 0.0;
         for (unsigned int t = 0; t < LLRs_null.size(); ++t) { hLLR_null->Fill( LLRs_null[t] );   LLR_null_Mean += LLRs_null[t];   LLR_null_x2 += LLRs_null[t]*LLRs_null[t]; }
         LLR_null_Mean *= 1./LLRs_null.size();
         LLR_null_Sig   = sqrt( LLR_null_x2 / LLRs_null.size() - LLR_null_Mean * LLR_null_Mean );
         // calculate median
         double LLR_null_Median = Median_Vec( LLRs_null );
         // calculate probabilities corresponding to:  median-1sigma |  median | median+1sigma
         double n_MedMin1Sigma = 0.;	double Prob_MedMin1Sigma;
         double n_MedPlu1Sigma = 0.;	double Prob_MedPlu1Sigma;
         double n_Median       = 0.;     double Prob_Median;
         double cutMin1sig     = LLR_null_Median - LLR_null_Sig;
         double cutPlu1sig     = LLR_null_Median + LLR_null_Sig;
         for (unsigned int t = 0; t < LLRs_null.size(); ++t) {  
         	    if ( LLRs_null[t] < cutMin1sig       ) n_MedMin1Sigma++;
         	    if ( LLRs_null[t] < LLR_null_Median  )       n_Median++;
         	    if ( LLRs_null[t] < cutPlu1sig       ) n_MedPlu1Sigma++;
         }
         Prob_MedMin1Sigma = n_MedMin1Sigma / double( LLRs_null.size() );	// median - 1 sigma probability
         Prob_Median       = n_Median       / double( LLRs_null.size() );  // median
         Prob_MedPlu1Sigma = n_MedPlu1Sigma / double( LLRs_null.size() );  // median + 1 sigma probability
         cout << " %%%%%%% ----------------------------------------------------------------------------------------------------%%%%%%% " << endl;
         cout << " %%%%%%% Null Hypothesis Test Statistics : Likelihood    Min= " << LLR_null_Min      << " Median= "       << LLR_null_Median  << " Max= "               << LLR_null_Max << endl;    
         cout << " %%%%%%%                                 : Prob(Median-1sig)= " << Prob_MedMin1Sigma << " Prob(Median)= " << Prob_Median      << " Prob(Median+1sig)= " << Prob_MedPlu1Sigma << endl;    
         cout << " %%%%%%% ----------------------------------------------------------------------------------------------------%%%%%%% " << endl;
         // AO May 7, 2020 ----- Calculate Mean and Sigma ----------------------------------------------------------------------------------------
         // --------------------------------------------------------------------------------------------------------------------------------------
         TF1* func_null;
         double func_integral_null;
         if ( asym == 999 ) { hLLR_null ->Fit("landau"); func_null = hLLR_null->GetFunction("landau"); }
         else               { hLLR_null ->Fit("gausn" ); func_null = hLLR_null->GetFunction("gausn" ); }
         func_integral_null = func_null->Integral(foundMin-delta, foundMax+delta);
         for (unsigned int ij = 1; ij < n_hLLR_null_fit+1; ++ij)   {  double xx     = hLLR_null_fit->GetXaxis()->GetBinCenter( ij );  
                                                                      double xxVal  = func_null->Eval( xx );
                                                                      hLLR_null_fit ->Fill( xx, xxVal ); 
                                                                      hLLR_null_fit ->SetBinError( ij, sqrt(xxVal) );
                                                                   }
         hLLR_null     ->SetMaximum( 1.2 * hLLR_null->GetMaximum() );
         hLLR_null_fit ->SetMaximum( 1.2 * hLLR_null->GetMaximum() );
         hLLR_null_fit ->SetLineColor(kSpring+9);
         hLLR_null_fit ->SetLineWidth(3);
         hLLR_null_fit ->SetLineStyle(6);
         TCanvas     *ccNUL = new TCanvas();   hLLR_null->Draw();  func_null->Draw("same"); hLLR_null_fit->Draw("e0 same"); ccNUL->Print("hLLR_null.png");  delete ccNUL;   

         // --------------------------------------------------------------------------------------------------------------------------------------
         // create (and fill) a histogram to visualise the distribution of the (logarithm of the) likelihood ratio under the requested hypothesis
         // --------------------------------------------------------------------------------------------------------------------------------------
         int n_hLLR;
         int n_hLLR_fit;
         if ( asym == 1 ) { n_hLLR =  100; n_hLLR_fit =  500; }
         else             { n_hLLR =  500; n_hLLR_fit =  500; }
         TH1D* hLLR     = new TH1D("hLLR",
                          Form("log(L(sample)/L(pseudo)) sampling distribution under sample hypothesis, using an %s LH", extended ? "extended" : "ordinary"),
                          n_hLLR, foundMin-delta, foundMax+delta);
                        //n_hLLR, foundMin-delta, 15.0);
         TH1D* hLLR_fit = new TH1D("hLLR_fit",
                          Form("fit log(L(sample)/L(pseudo)) sampling distribution under sample hypothesis, using an %s LH", extended ? "extended" : "ordinary"),
                          n_hLLR_fit, foundMin-delta, foundMax+delta);
                        //n_hLLR_fit, foundMin-delta, 15.0);
	       // --------------------------------------------------------------------------------------------------------------------------------------
	       // AO May 7, 2020 ----- Calculate Mean and Sigma ----------------------------------------------------------------------------------------
	       double LLRs_Mean     = 0.0;
	       double LLRs_Sig      = 0.0;
	       double LLRs_x2       = 0.0;
         for (unsigned int t = 0; t < LLRs.size(); ++t) { hLLR->Fill(LLRs[t]);    LLRs_Mean += LLRs[t];   LLRs_x2 += LLRs[t]*LLRs[t]; }
         LLRs_Mean *= 1./LLRs.size();
         LLRs_Sig   = sqrt( LLRs_x2 / LLRs.size() - LLRs_Mean * LLRs_Mean );
	       // calculate median
	       double LLRs_Median = Median_Vec( LLRs );
	       // calculate probabilities corresponding to:  median-1sigma |  median | median+1sigma
         double n_MedMin1Sigma_s = 0.;	double Prob_MedMin1Sigma_s;
         double n_MedPlu1Sigma_s = 0.;	double Prob_MedPlu1Sigma_s;
	       double n_Median_s       = 0.;   double Prob_Median_s;
	       double cutMin1sig_s     = LLRs_Median - LLRs_Sig;
	       double cutPlu1sig_s     = LLRs_Median + LLRs_Sig;
	       for (unsigned int t = 0; t < LLRs.size(); ++t) {  
	       	   if ( LLRs[t] < cutMin1sig_s       ) n_MedMin1Sigma_s++;
	       	   if ( LLRs[t] < LLRs_Median        )       n_Median_s++;
	       	   if ( LLRs[t] < cutPlu1sig_s       ) n_MedPlu1Sigma_s++;
	       }
	       Prob_MedMin1Sigma_s = n_MedMin1Sigma_s / double( LLRs.size() );	// median - 1 sigma probability
	       Prob_Median_s       = n_Median_s       / double( LLRs.size() );  // median
	       Prob_MedPlu1Sigma_s = n_MedPlu1Sigma_s / double( LLRs.size() );  // median + 1 sigma probability
	       cout << " %%%%%%% ----------------------------------------------------------------------------------------------------%%%%%%% " << endl;
	       cout << " %%%%%%% Test Hypothesis Test Statistics : Likelihood    Min= " << LLRs_Min            << " Median= "       << LLRs_Median   << " Max= "               << LLRs_Max << endl;    
	       cout << " %%%%%%%                                 : Prob(Median-1sig)= " << Prob_MedMin1Sigma_s << " Prob(Median)= " << Prob_Median_s << " Prob(Median+1sig)= " << Prob_MedPlu1Sigma_s << endl;    
	       cout << " %%%%%%% ----------------------------------------------------------------------------------------------------%%%%%%% " << endl;
	       // AO May 7, 2020 ----- Calculate Mean and Sigma ----------------------------------------------------------------------------------------
	       // --------------------------------------------------------------------------------------------------------------------------------------
         TF1* func;
         double func_integral;
         if ( asym == 999 ) { hLLR->Fit("landau"); func = hLLR->GetFunction("landau"); }
         else               { hLLR->Fit("gausn" ); func = hLLR->GetFunction("gausn" ); }
         func_integral  = func->Integral(foundMin-delta, foundMax+delta);
         for (unsigned int ij = 1; ij < n_hLLR_fit+1; ++ij)        { double xx      = hLLR_fit->GetXaxis()->GetBinCenter( ij );
                                                                     double xxVal   = func->Eval( xx );
                                                                     hLLR_fit       ->Fill( xx, xxVal ); 
                                                                     hLLR_fit       ->SetBinError( ij, sqrt(xxVal) );
                                                                   }
         hLLR     ->SetMaximum( 1.2 * hLLR->GetMaximum() );
         hLLR_fit ->SetMaximum( 1.2 * hLLR->GetMaximum() );
         hLLR_fit ->SetLineColor(kMagenta+2);
         hLLR_fit ->SetLineWidth(3);
         hLLR_fit ->SetLineStyle(6);
         TCanvas *ccLLR = new TCanvas();   hLLR->Draw();  func->Draw("same"); hLLR_fit->Draw("e0 same"); ccLLR->Print("hLLR.png");  delete ccLLR;   

         // --------------------------------------------------------------------------------------------------------------------------------------
         // AO May 7, 2020 ----- Redefine the Quantile Probabilities as defined above ------------------------------------------------------------
         //Find median and 68% band of the pseudo hypothesis
         double* LLRs_null_array = &LLRs_null[0];
         // double probs[3] = {0.16,0.5,0.84};    				     // OLD stuff previous to 2D scan
         double probs[3] = { Prob_MedMin1Sigma, Prob_Median, Prob_MedPlu1Sigma};   // this is the change performed
         double quantiles[3];
         cout << " %%%%%%% -------------------------------------------------------------------------fed to quantile func-------%%%%%%% " << endl;
         cout << " %%%%%%% Null Hypothesis  Probabilities : Prob(Median-1sig)= " << probs[0] << " Prob(Median)= " << probs[1] << " Prob(Median+1sig)= " << probs[2] << endl;
         cout << " %%%%%%% ----------------------------------------------------------------------------------------------------%%%%%%% " << endl;
         cout << "Computing quantiles for LLR in null hypothesis..." << std::endl;
         TMath::Quantiles(ntest, 3, LLRs_null_array, quantiles, probs, kFALSE);
         cout << "Median: " << quantiles[1] << ", -1sigma: " << quantiles[0] << ", +1sigma: " << quantiles[2] << std::endl;
         // AO May 7, 2020 ----- Redefine the Quantile Probabilities as defined above ------------------------------------------------------------
         // --------------------------------------------------------------------------------------------------------------------------------------

         // ========================================================================================================================================
         // Compute the p-value as fractions of toy experiments leading to a BIGGER LLR than the median and +-1sigma observations in the NULL Hypothesis
         // ========================================================================================================================================
         unsigned int aboveQuantile[3] = {0,0,0};
         for (unsigned int t = 0; t < LLRs.size(); ++t){
            if (LLRs[t] >= quantiles[0]){
              aboveQuantile[0]++;
              if (LLRs[t] >= quantiles[1]){
                aboveQuantile[1]++;
                if (LLRs[t] >= quantiles[2])
                  aboveQuantile[2]++;
              }
            }
         }
         // ========================================================================================================================================
         //                          Define the Quantiles for the EXPECTED p-values
         // ========================================================================================================================================
         double pvalQuantile[3] = { double(aboveQuantile[0]) / double(LLRs.size()), 
                                    double(aboveQuantile[1]) / double(LLRs.size()), 
                                    double(aboveQuantile[2]) / double(LLRs.size()) };
         
         // --------------------------------------------- AO 14 November 2020 -------
         // Make sure we are in the right side of the Likelihood: 
         // if the Null hypothesis has a Median SMALLER than the Signal hypothesis
         // we need to mirror change the elusion and take 1-p as the new pval
         // -------------------------------------------------------------------------
         // NOTE: For asym==2 we should NEVER change once we are using a Chi2 distribution
         // -------------------------------------------------------------------------
         if ( asym != 2 && ( LLRs_Median > LLR_null_Median ) ) {
             cout << "     ------------------------------------- NOTE: We inverted the EXPECTED p-value !!!!!! " << endl;
             pvalQuantile[0] = 1.0 - pvalQuantile[0];
             pvalQuantile[1] = 1.0 - pvalQuantile[1];
             pvalQuantile[2] = 1.0 - pvalQuantile[2];
         }
         // --------------------------------------------- AO 14 November 2020 -------       

         // ========================================================================================================================================
         //                          Define the Quantiles for the EXPECTED Confidence Levels CL = 1 - p-values
         // ========================================================================================================================================
         double CL_Quantile[3] = {  1.0 - pvalQuantile[0], 1.0 - pvalQuantile[1], 1.0 - pvalQuantile[2] };
         cout << " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% " << endl;
         cout << " %% EXPECTED Quantile[0]= " << pvalQuantile[0] << " Quantile[1]= " << pvalQuantile[1] << " Quantile[2]= " << pvalQuantile[2] << endl;  
         cout << " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% " << endl;
         cout << " %% ................................................................. " << endl;
         cout << " %% EXPECTED Confidence Level for Exclusion:" << CL_Quantile[1] << endl;

         // also compute the LLR for the pseudo-data at hand (i.e., our desired hypothesis)
         std::vector<double> pseudo_obs;
         for (unsigned int bin = 0; bin < (unsigned) hPseudo->GetNbinsX(); ++bin) {
            pseudo_obs.push_back(hPseudo->GetBinContent(bin+1));
         }
         // --------------------------------------------------------------------------- Poisson or Skellam Likelihoods --------------------------
         double LLR_obs;
         if ( asym == 0 ) LLR_obs =         logLikelihood(pseudo_obs, hSample, extended) - logLikelihood(pseudo_obs, hPseudo, extended);
         if ( asym == 1 ) LLR_obs =         logLikelihoodAsymmetries(asym, pseudo_obs, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF);
       //if ( asym == 2 ) LLR_obs = -2. * ( logLikelihoodAsymmetries(asym, pseudo_obs, hSample, extended, hLLR_PDF,      funPDF_from_Fit, func_hLLR_PDF     ) 
       //                                 - logLikelihoodAsymmetries(asym, pseudo_obs, hSample, extended, hLLR_null_PDF, funPDF_from_Fit, func_hLLR_null_PDF) );
         if ( asym == 2 ) LLR_obs = -2. * ( logLikelihoodAsymmetries(asym, pseudo_obs, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF) );
         if ( asym == 3 ) LLR_obs =         logLikelihoodAsymmetries(asym, pseudo_obs, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF);
         if ( asym == 4 ) LLR_obs =         logLikelihoodAsymmetries(asym, pseudo_obs, hSample, extended, hLLR_PDF, funPDF_from_Fit, func_hLLR_PDF);
         // --------------------------------------------------------------------------- Poisson or Skellam Likelihoods --------------------------
  

         // ========================================================================================================================================
         //                          Define the Quantiles for the OBSERVED p-values
         // ========================================================================================================================================
         // Finally, compute the confidence simply as the fraction of toy experiments leading to a SMALLER LLR than that observed in the pseudo-data
         // ========================================================================================================================================
         unsigned int tails = 0;
         for (unsigned int t = 0; t < LLRs.size(); ++t) {
            if (LLRs[t] >= LLR_obs) ++ tails;
         }
         double pval    = double(tails)/double(LLRs.size());
         double pvalFit = (func) ? func->Integral(LLR_obs, foundMax + delta)/func_integral : 0;

         // --------------------------------------------- AO 14 November 2020 -------
         // Make sure we are in the right side of the Likelihood: 
         // if the Null hypothesis has a Median SMALLER than the Signal hypothesis
         // we need to mirror change the elusion and take 1-p as the new pval
         // -------------------------------------------------------------------------
         // NOTE: For asym==2 we should NEVER change once we are using a Chi2 distribution
         // -------------------------------------------------------------------------
         if ( asym != 2 && ( LLRs_Median > LLR_obs ) ) {
              cout << "     ------------------------------------- NOTE: We inverted the OBSERVED p-value !!!!!! " << endl;
              pval    = 1.0 - pval;
              pvalFit = 1.0 - pvalFit;
         }
         // --------------------------------------------- AO 14 November 2020 -------

         // ========================================================================================================================================
         //                          Define the Quantiles for the OBSERVED Confidence Levels CL = 1.0 - p-value
         // ========================================================================================================================================
         double CL_val    = 1.0 - pval;
         double CL_valFit = 1.0 - pvalFit;
         cout << " %% OBSERVED Confidence Level for Exclusion:" << CL_val << endl;
         cout << " %% ................................................................. " << endl;
         cout << " %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% " << endl;
         cout << endl;


         // print results
         cout << "LLR observed in pseudo-data closest to the MC prediction = " << LLR_obs
              << ", resulting CL: " << CL_val << " (as evaluated using " << ntest << " toy experiments)" << std::endl;
         if (func) {
           cout << "\talternative CL estimate from a fit of a normal distribution to the expected LLR distribution: " << CL_valFit << std::endl;
         }
         cout << "CL observed in pseudo-data with median (-1sigma, +1sigma) LLR = " << CL_Quantile[1] << " (" << CL_Quantile[0] << "," << CL_Quantile[2] << ")" << std::endl;

         //write into table file
         ofstream table;
         table.open((indir+"/Tables/"+infileA+cosa+"mode"+to_string(pseudo)+to_string(sample)+"_table.txt").c_str(),ios::app);
         //table.open("test.txt",ios::app);
         table << scale << " " << CL_val << " " << CL_Quantile[1] << " " << CL_Quantile[0] << " " << CL_Quantile[2] 
                        << " " << k << " " << ktil 
                        << " " << LLR_null_Min << " " << LLR_null_Median << " " << LLR_null_Max 
                        << " " << LLRs_Min     << " " << LLRs_Median     << " " << LLRs_Max     << std::endl;
         table.close();  

  	     // draw the result
  	     TCanvas* c = new TCanvas("cHvsA", "ln(L(bg+A)/L(bg+H)) sampling distribution and observed values", 900, 400);
  	     hLLR->SetLineWidth(2);
  	     hLLR->Draw();
  	     hLLR_null->SetLineWidth(2);
  	     hLLR_null->SetLineColor(kGreen);
  	     hLLR_null->Draw("same");
  	     TLine* l = new TLine(LLR_obs, 0, LLR_obs, 1.1*hLLR->GetBinContent(hLLR->FindFixBin(LLR_obs)));
  	     TLine* lmed = new TLine(quantiles[1], 0, quantiles[1], 1.1*hLLR_null->GetBinContent(hLLR_null->FindFixBin(quantiles[1])));
  	     TLine* llow = new TLine(quantiles[0], 0, quantiles[0], 1.1*hLLR_null->GetBinContent(hLLR_null->FindFixBin(quantiles[0])));
  	     TLine* lhi  = new TLine(quantiles[2], 0, quantiles[2], 1.1*hLLR_null->GetBinContent(hLLR_null->FindFixBin(quantiles[2])));
  	     l->SetLineWidth(2); lmed->SetLineWidth(2); llow->SetLineWidth(2); lhi->SetLineWidth(2);
  	     l->SetLineStyle(2); lmed->SetLineStyle(2); llow->SetLineStyle(2); lhi->SetLineStyle(2);
  	     l->SetLineColor(kRed); lmed->SetLineColor(kGreen+1); llow->SetLineColor(kGreen+2); lhi->SetLineColor(kGreen+2);
  	     l->Draw(); lmed->Draw(); llow->Draw(); lhi->Draw();
         func_null->SetLineColor(kGreen-2);
  	     func->Draw("same");
  	     func_null->Draw("same");
         // add fitted fucntions with a lot of bins
         hLLR_fit      ->Draw("e0 same");
         hLLR_null_fit ->Draw("e0 same");
         // printout histograms
         std::string  pdfOutfile = "PDFhistos/" + infileA + "_k" + std::to_string(k) + "_ktil" + std::to_string(ktil) + ".pdf";
         if ( k == -2.0 || k == -1.5 || k == -1.0 || k == -0.5 || k == 0.0 || k == 0.5 || k == 1.0 || k == 1.5 || k == 2.0 ){
           if ( ktil == -2.0 || ktil == -1.5 || ktil == -1.0 || ktil == -0.5 || ktil == 0.0 || ktil == 0.5 || ktil == 1.0 || ktil == 1.5 || ktil == 2.0 ){
              c->Print(pdfOutfile.c_str());
           }
         }

         // ----------------------------------------------------------------
         // Output hLLR and hLLR_null in appropriate file (for all options)
         // ----------------------------------------------------------------
         MyTestStatOutfile->cd();
         hLLR          ->Write( TestStat_hLLR.c_str()     );
         hLLR_null     ->Write( TestStat_hLLR_null.c_str());
         // save fitted smooth histograms
         hLLR_fit      ->Write( TestStat_hLLR_fit.c_str()      );
         hLLR_null_fit ->Write( TestStat_hLLR_null_fit.c_str() );
         // ----------------------------------------------------------------

         // delete canvas
         delete c;
         // delete histograms and objects
         delete httH;
         delete httA;
         delete hbkg;
         delete hPseudo;
         delete hSample;
         delete hLLR;
         delete hLLR_null;
    } // end of ktil loop
  } // end of k loop
  // end of loop over the different (Re,Im)=(k,ktil) values --------------------------
  // ---------------------------------------------------------------------------------

}
