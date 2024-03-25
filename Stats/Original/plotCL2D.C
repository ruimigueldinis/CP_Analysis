#define plotCL2D_cxx
#include "plotCL2D.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "myMergeAll.C"
#include "utils.h"


// #############################################################################
void doPlot2D(TH2D* hCL,                   // hist to be represented
              TH2D* hCLXX,                 // hist to be represented
              string name,                 // name of histogram to represent
              string nameH,                // name of output hist file
              string m,                    // string with mass value
              string var,                  // variable
              int    iPal,                 // palette choice
              string Xtit, string Ytit)    // Titles for X-axis and Y-axis
// #############################################################################
{
         // define output file name string
         string outCLXX ="Plots/"+name+"_CLXX_2D.png";
         string out     ="Plots/"+name+"_2D.png";
         string out3D   ="Plots/"+name+"_3D.png";
         string outHist ="Plots/"+nameH+"_2D.hist";
      
         gStyle->SetOptStat(0);
         gStyle->SetOptTitle(0);
         gStyle->SetPaperSize(20,24);
         gStyle->SetTickLength(0.02,"x");
         gStyle->SetTickLength(0.02,"y");
         //
         // set input for now
         //TH1D *hCL = hCL_Exp->Clone(" ");
         //string Xtit = " #it{k} (Re)";
         //string Ytit = " #it{#tilde{k}} (Im)";
         //
         // =========================================
         // Full CL Ditribution
         // =========================================
         // set X-axis title
         TGaxis::SetMaxDigits(4);
         hCL->GetXaxis()->CenterTitle();
         hCL->GetXaxis()->SetTitleOffset(1.15);
         hCL->GetXaxis()->SetTitleSize(0.050);
         hCL->GetXaxis()->SetLabelSize(0.035);
         hCL->GetXaxis()->SetNdivisions(6);
         // set Y-axis title
         hCL->GetYaxis()->CenterTitle();
         hCL->GetYaxis()->SetTitleOffset(1.10);
         hCL->GetYaxis()->SetTitleSize(0.050);       // this is the size of dN/dx_Y  in the y-caption
         hCL->GetYaxis()->SetLabelSize(0.035);
         hCL->GetYaxis()->SetNdivisions(6);
         //
         // =========================================
         // CL=0.68, 0.95, 0.99 Ditribution
         // =========================================
         // set X-axis title
         TGaxis::SetMaxDigits(4);
         hCLXX->GetXaxis()->CenterTitle();
         hCLXX->GetXaxis()->SetTitleOffset(1.15);
         hCLXX->GetXaxis()->SetTitleSize(0.050);
         hCLXX->GetXaxis()->SetLabelSize(0.035);
         hCLXX->GetXaxis()->SetNdivisions(6);
         // set Y-axis title
         hCLXX->GetYaxis()->CenterTitle();
         hCLXX->GetYaxis()->SetTitleOffset(1.10);
         hCLXX->GetYaxis()->SetTitleSize(0.050);       // this is the size of dN/dx_Y  in the y-caption
         hCLXX->GetYaxis()->SetLabelSize(0.035);
         hCLXX->GetYaxis()->SetNdivisions(6);
         //
         TCanvas *c1 = new TCanvas("c1","c1",1000,700);
         c1->SetRightMargin(0.15);
         c1->SetLeftMargin(0.15);
         c1->SetTopMargin(0.15);
         c1->SetBottomMargin(0.15);
         //
         // Define pallette colour scheme
         const UInt_t Number = 6;
         // default color scheme
         //Double_t Red[Number]     = { 0.00, 0.00, 1.00, 1.00, 1.00  , 1.00};
         //Double_t Green[Number]   = { 0.70, 1.00, 1.00, 0.00, 1.00  , 1.00};
         //Double_t Blue[Number]    = { 0.70, 0.00, 0.00, 0.00, 1.00  , 1.00};
         //Double_t Length[Number]  = { 0.00, 0.25, 0.50, 0.75, 0.999 , 1.00};
         Double_t Red[Number]     = { 0.00, 0.00, 1.00, 1.00, 1.00  , 1.00};
         Double_t Green[Number]   = { 0.60, 0.50, 1.00, 0.00, 1.00  , 1.00};
         Double_t Blue[Number]    = { 0.60, 0.00, 0.00, 0.00, 1.00  , 1.00};
         Double_t Length[Number]  = { 0.00, 0.25, 0.50, 0.75, 0.999 , 1.00};
         // 2nd color scheme
         //Double_t Red1[Number]    = { 0.00, 0.10, 0.90, 0.90, 1.00  , 1.00};
         //Double_t Green1[Number]  = { 0.70, 0.50, 0.50, 0.00, 1.00  , 1.00};
         //Double_t Blue1[Number]   = { 0.70, 1.00, 1.00, 0.00, 1.00  , 1.00};
         //Double_t Length1[Number] = { 0.00, 0.25, 0.50, 0.75, 0.999 , 1.00};
         //    Double_t Red1[Number]    = { 0.00, 0.10, 0.90, 0.90, 1.00  , 1.00};
         //    Double_t Green1[Number]  = { 0.20, 0.20, 0.50, 0.00, 1.00  , 1.00};
         //    Double_t Blue1[Number]   = { 0.20, 1.00, 1.00, 0.00, 1.00  , 1.00};
         //    Double_t Length1[Number] = { 0.00, 0.25, 0.50, 0.75, 0.999 , 1.00};

         Double_t Red1[Number]    = { 0.00, 0.10, 0.90, 0.90, 0.99 , 1.00};
         Double_t Green1[Number]  = { 0.20, 0.20, 0.50, 0.00, 0.99 , 1.00};
         Double_t Blue1[Number]   = { 0.40, 1.00, 1.00, 0.00, 0.99 , 1.00};
         Double_t Length1[Number] = { 0.00, 0.25, 0.50, 0.75, 0.99 , 1.00};

         // create gradient colours with nbb color levels
         const int nbb=30;  // it was 40 previously
         if ( iPal == 0) TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nbb);
         if ( iPal == 1) TColor::CreateGradientColorTable(Number,Length1,Red1,Green1,Blue1,nbb);
         if ( iPal == 2) {gStyle->SetPalette(kOcean); gStyle->SetNumberContours(99);}
         if ( iPal == 3) {gStyle->SetPalette(kCherry); gStyle->SetNumberContours(99);}
         if ( iPal == 4) {gStyle->SetPalette(kDarkBodyRadiator); gStyle->SetNumberContours(99);}
         if ( iPal == 5) {gStyle->SetPalette(kBeach); gStyle->SetNumberContours(99);}
         if ( iPal == 6) {gStyle->SetPalette(kSunset); gStyle->SetNumberContours(99);}
         if ( iPal == 7) {gStyle->SetPalette(kBlueRedYellow); gStyle->SetNumberContours(99);}
         // set contours to histogram
         // Full CL
         hCL->SetContour(nbb);
         hCL->SetMaximum(1.0);
         hCL->SetMinimum(0.5);
         hCL->GetZaxis()->SetLabelColor(kAzure+4);         
         hCL->GetZaxis()->SetLabelSize(0.030);         
         hCL->GetXaxis()->SetTitle( Xtit.c_str() );
         hCL->GetYaxis()->SetTitle( Ytit.c_str() );
         // CL=0.68,0.95,0.99
         hCLXX->SetContour(nbb);
         hCLXX->SetMaximum(1.0);
         hCLXX->SetMinimum(0.5);
         hCLXX->GetZaxis()->SetLabelColor(kSpring+5);         
         hCLXX->GetZaxis()->SetLabelSize(0.030);         
         hCLXX->GetXaxis()->SetTitle( Xtit.c_str() );
         hCLXX->GetYaxis()->SetTitle( Ytit.c_str() );

         // ----------------------------------------------------------
              // draw relevant information
         // ----------------------------------------------------------
           char* m_char = const_cast<char*>(m.c_str());
           char* v_char = const_cast<char*>(var.c_str()); 
         //char* l_char = const_cast<char*>("Lumi= 36.1 fb^{-1}"); 
         //char* l_char = const_cast<char*>("Lumi= 139 fb^{-1}"); 
           char* l_char = const_cast<char*>("Lumi= 200 fb^{-1}"); 
         //char* l_char = const_cast<char*>("Lumi= 3000 fb^{-1}"); 

         //        // ----------------------------------------------------------
         //        // New canvas for 3D distribution
         //        // ----------------------------------------------------------
         //        TCanvas *c = new TCanvas("c","c", 1000,1000);
         //        c->SetRightMargin(0.15);
         //        c->SetLeftMargin(0.15);
         //        c->SetTopMargin(0.15);
         //        c->SetBottomMargin(0.15);
         //        gPad->SetTheta(20); // default is 30
         //        gPad->SetPhi(30);   // default is 30
         //        gPad->Update();
         //        hCL->Draw("surf2 Z");
         //        hCL->Draw("CONT1 SAME");
         //        //
         //        myText(     0.930, 0.85,         1,   "(CL)",                   0.035);
         //        myText(     0.065, 0.91,         1,   "LHC, #sqrt{s} = 13 TeV", 0.035);
         //        myText(     0.065, 0.87,         1,   "MadGraph5_aMC@NLO",      0.030);
         //        if ( iPal == 0) {
         //              myText(     0.065, 0.83,   kCyan+3,         l_char,       0.030);
         //              myText(     0.065, 0.78, kOrange+8,         m_char,       0.030);
         //              myText(     0.450, 0.92,    kRed-4,         v_char,       0.030);
         //        }
         //        if ( iPal == 1) {
         //              myText(     0.065, 0.83,   kCyan-2,         l_char,       0.030);
         //              myText(     0.065, 0.78,  kAzure+4,         m_char,       0.030);
         //              myText(     0.450, 0.92,  kAzure-7,         v_char,       0.030);
         //        }
         //        if ( iPal >= 2) {
         //              myText(     0.065, 0.83,   kCyan-2,         l_char,       0.030);
         //              myText(     0.065, 0.78,  kAzure+4,         m_char,       0.030);
         //              myText(     0.450, 0.92,  kAzure-7,         v_char,       0.030);
         //        }
         //        // print to file
         //        c->Print(out3D.c_str());
         //        // delete canvas
         //        delete c;

         // ---------------------------------------------------------------------
         // Clone histogram to plot contours independently to original histo
         // ---------------------------------------------------------------------
         TH2D *hCL_Clone = (TH2D*)hCL->Clone(" ");
         // start contours on cloned histogram
         const int nContours=3;
         Double_t contours[nContours];
         contours[0] =  0.68;
         contours[1] =  0.90;
         contours[2] =  0.95;
         // define contours for histogram
         hCL_Clone->SetContour(nContours, contours); 
         // draw, update contours and draw again
         hCL_Clone->Draw("CONT Z LIST");
         c1->Update();             // need to force update to get contours
         // ---------------------------------------------------------------------

         // ---------------------------------------------------------------------
         // Plot histograms and contours THIS WORKS !!!!!
         // ---------------------------------------------------------------------
         hCL->Draw("CONT4 Z");
         hCL->DrawCopy("colz");
         hCL->SetContour(3,contours);
         hCL->Draw("cont3 same");
         // ---------------------------------------------------------------------

         // The countours will run over the hCL_Clone histogram         
         TObjArray *conts = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
         TList* contLevel = NULL;
         TGraph* curv     = NULL;
         TGraph* gc       = NULL;

         Int_t nGraphs    = 0;
         Int_t TotalConts = 0;

         if (conts == NULL){
            printf("*** No Contours Were Extracted!\n");
            TotalConts = 0;
            return;
         } else {
            TotalConts = conts->GetSize();
         }

         printf("Total Number of Contours = %d\n", TotalConts);
        
         for(int i = 0; i < TotalConts; i++){       
            contLevel = (TList*)conts->At(i);            
            printf("Contour %d has %d Graphs \n", i, contLevel->GetSize());
            nGraphs += contLevel->GetSize();
            cout << "       Increment Total Number of nGraphs = " << nGraphs << endl;
         }

         Double_t xval0, yval0, zval0;
         TLatex l;
         char val[20];

         for(int i = 0; i < TotalConts; i++){
            contLevel = (TList*)conts->At(i);
            zval0 = contours[i];
            printf("Z-Level Passed in as:  Z = %f\n", zval0); 
            if ( contLevel->GetSize() != 0 ){
                   // Get first graph from list on curves on this level
                   curv = (TGraph*)contLevel->First();
                   // set contour and text color
                   curv->SetLineColor(kCyan+4);
                   l.SetTextColor(kBlack);
                   //
                   for(int j = 0; j < contLevel->GetSize(); j++){
                        // get points close to the origin
                        //double  KtildK = 999.;
                        double  KtildK =  0.0; 
                        int   n_KtildK =    0;
                        for ( int iP = 0; iP < curv->GetN(); iP++ ){
                          curv->GetPoint( iP, xval0, yval0);
                          double dist = sqrt( xval0*xval0 + yval0*yval0 );
                        //if ( dist < KtildK ) { KtildK = dist; n_KtildK = iP; }
                          if ( dist > KtildK ) { KtildK = dist; n_KtildK = iP; }
                        }
                        // get the closest point information
                        curv->GetPoint( n_KtildK, xval0, yval0);
                        nGraphs ++;
                        printf("\tGraph: %d  -- %d Elements\n", nGraphs,curv->GetN());       
                        // Draw clones of the graphs to avoid deletions in case the 1st
                        // pad is redrawn.
                        gc = (TGraph*)curv->Clone();
                        gc->Draw("C");
                        // print value
                        sprintf(val, "%g", zval0);
                        l.SetTextSize(0.017); // 0.025/0.017
                        l.SetTextAlign(11);
                      //l.DrawLatex(xval0,yval0,val);  // draw confidence level number
                        curv = (TGraph*)contLevel->After(curv); // Get Next graph
                   }
            } 
         }
         // Update canvas
         c1->Update();
         // printout relevant information
         myText(     0.930, 0.85,         1,   "(CL)",                   0.040);
         myText(     0.165, 0.95,         1,   "LHC, #sqrt{s} = 13 TeV", 0.045);
         myText(     0.165, 0.91,         1,   "MadGraph5_aMC@NLO",      0.030);
         if ( iPal == 0) {
               myText(     0.165, 0.88,   kCyan+3,         l_char,       0.030);
               myText(     0.500, 0.89, kOrange+8,         m_char,       0.040);
               myText(     0.500, 0.94,    kRed-4,         v_char,       0.040);
         }
         if ( iPal == 1) {
               myText(     0.165, 0.88,   kCyan-2,         l_char,       0.030);
               myText(     0.500, 0.89,  kAzure+4,         m_char,       0.040);
               myText(     0.500, 0.94,  kAzure-7,         v_char,       0.040);
         }
         if ( iPal >= 2) {
               myText(     0.165, 0.88,   kCyan-2,         l_char,       0.030);
               myText(     0.500, 0.89,  kAzure+4,         m_char,       0.040);
               myText(     0.500, 0.94,  kAzure-7,         v_char,       0.040);
         }
         // save canvas to file
         c1->Print(out.c_str());
         // delete canvas
         delete c1;

         // ----------------------------------------------------------
         // New canvas for 2D contour distributions only
         // ----------------------------------------------------------
         // Define pallette colour scheme
         const UInt_t Number2 = 4;
         Double_t Red2[Number2]    = { 1.00, 0.10, 0.90, 1.00};
         Double_t Green2[Number2]  = { 1.00, 0.10, 0.10, 1.00};
         Double_t Blue2[Number2]   = { 1.00, 1.00, 1.00, 1.00};
         Double_t Length2[Number2] = { 0.00, 0.68, 0.95, 1.00};
         TColor::CreateGradientColorTable(Number2,Length2,Red2,Green2,Blue2,4);

         TCanvas *c2 = new TCanvas("c2","c2",1000,700);
         c2->SetRightMargin(0.15);
         c2->SetLeftMargin(0.15);
         c2->SetTopMargin(0.15);
         c2->SetBottomMargin(0.15);
         // draw histograms
         // draw original histogram ---------------------------------------------
         hCLXX->Draw("CONT4 Z");
         // printout useful information
         myText(     0.930, 0.85,         1,   "(CL)",                   0.040);
         myText(     0.165, 0.80,         1,   "LHC, #sqrt{s} = 13 TeV", 0.040);
         myText(     0.165, 0.75,         1,   "MadGraph5_aMC@NLO",      0.030);
         if ( iPal == 0) {
               myText(     0.165, 0.70,   kCyan+3,         l_char,       0.035);
               myText(     0.265, 0.91, kOrange+8,         m_char,       0.045);
               myText(     0.500, 0.92,    kRed-4,         v_char,       0.045);
         }
         if ( iPal == 1) {
               myText(     0.165, 0.70,   kCyan-2,         l_char,       0.035);
               myText(     0.265, 0.91,  kAzure+4,         m_char,       0.045);
               myText(     0.500, 0.92,  kAzure-7,         v_char,       0.045);
         }
         if ( iPal >= 2) {
               myText(     0.165, 0.70,   kCyan-2,         l_char,       0.035);
               myText(     0.265, 0.91,  kAzure+4,         m_char,       0.045);
               myText(     0.500, 0.92,  kAzure-7,         v_char,       0.045);
         }
         //c2->Print(outCLXX.c_str());
         // delete canvas
         //delete c2;

         // output histograms
         TFile *outputFile;
         outputFile = new TFile(outHist.c_str(),"RECREATE");
       //hCLines->Write("hCLines");
         hCL    ->Write();
         hCLXX  ->Write();
         outputFile->Close();
} 

void plotCL2D::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L plotCL2D.C
//      Root > plotCL2D t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   // create some histograms
   // L=139fb-1 ---------------
   //   int   nBins =     33;
   //   double kMin =  -1.70;
   //   double kMax =   1.70;
   //   int  ntBins =     33;
   //   double ktMin = -1.70;
   //   double ktMax =  1.70;
   // -------------------------------
   // create some histograms Paper2021
   // L=139fb-1 ---------------
   //   int   nBins =      80;
   //   double kMin =  -2.025;
   //   double kMax =   2.025;
   //   int  ntBins =      80;
   //   double ktMin = -2.025;
   //   double ktMax =  2.025;
   // -------------------------------
   // Esteban
   // L=139fb-1 ---------------
   //   int   nBins =      67;
   //   double kMin =  -2.000;
   //   double kMax =   2.000;
   //   int  ntBins =      67;
   //   double ktMin = -2.000;
   //   double ktMax =  2.000;
   // -------------------------------
   // L=300fb-1 --------------- paper
   //   int   nBins =      60;
   //   double kMin =  -1.525;
   //   double kMax =   1.525;
   //   int  ntBins =      60;
   //   double ktMin = -1.525;
   //   double ktMax =  1.525;
   // -------------------------------
   // L=3000fb-1 (HLLHC)
   //int    nBins =     40;
   //double  kMin = -1.025;
   //double  kMax =  1.025;
   //int   ntBins =     40;
   //double ktMin = -1.025;
   //double ktMax =  1.025;

   // -----------------------------------------------------
   //    Papers:  Low Mass 2020  and  Higgs Mass 2021
   //             ( Luminosity = 3000 fb-1 )
   // -----------------------------------------------------
   // L=3000fb-1 (HLLHC) ------ Low Mass Paper2020   
   // int    nBins =     134;
   // double  kMin = -1.0125;
   // double  kMax =  1.0125;
   // int   ntBins =     134;
   // double ktMin = -1.0125;
   // double ktMax =  1.0125;
   // -----------------------------------------------------
   // L=200fb-1 (HLLHC)  ------ Higgs Mass 125GeV Paper2021
   // int    nBins =     200;
   // double  kMin =   -2.01;
   // double  kMax =    2.01;
   // int   ntBins =     200;
   // double ktMin =   -2.01;
   // double ktMax =    2.01;
   // -------------------------------
   // L=3000fb-1 (HLLHC) ------ Higgs Mass 125GeV Paper2021
   // int    nBins =      150;
   // double  kMin =   -1.510;
   // double  kMax =    1.510;
   // int   ntBins =      150;
   // double ktMin =   -1.510;
   // double ktMax =    1.510;
   // int    nBins =       60;
   // double  kMin =   -1.525;
   // double  kMax =    1.525;
   // int   ntBins =       60;
   // double ktMin =   -1.525;
   // double ktMax =    1.525;
   // Latest...................
   // int    nBins =       200;
   // double  kMin =   -1.5075;
   // double  kMax =    1.5075;
   // int   ntBins =       134;
   // double ktMin =   -1.0125;
   // double ktMax =    1.0125;
   // L=200fb-1 (HLLHC)  ------ // -- Choice for best cases from scans
   // int    nBins =     101;
   // double  kMin =   -0.02;
   // double  kMax =    2.00;
   // int   ntBins =     201;
   // double ktMin =   -2.02;
   // double ktMax =    2.00;

   // ---------------------------------------------------------------------------------
   // $$$$ Dark Matter $$$$$$$$$$$      C A S E = ( 0 , 2 )      $$$$$$$$$$$$$$$$$$$$$$
   // ---------------------------------------------------------------------------------
   // #######  200 fb-1  #######
      int    nBins =       119;  //     59; //     120;
      double  kMin =   0.00125;  // 0.0025; // -0.3050;
      double  kMax =   0.30125;  // 0.3025; //  0.3050;
      int   ntBins =       199;  //     99; //    201;
      double ktMin =     0.005;  //   0.01; //  -2.02;
      double ktMax =     2.005;  //   2.01; //   2.00;
   // ---------------------------------------------------------------------------------
   // $$$$ Dark Matter $$$$$$$$$$$      C A S E = ( 1 , 2 )      $$$$$$$$$$$$$$$$$$$$$$
   // ---------------------------------------------------------------------------------
   // // #######  200 fb-1  #######
   //   int    nBins =     201;
   //   double  kMin =  0.8990;
   //   double  kMax =  1.1010;
   //   double  kBin = ( kMax - kMin )/( nBins + 1 );
   //   int   ntBins =     400;
   //   double ktMin =   -4.01;
   //   double ktMax =    4.01;
   //   double ktBin = ( ktMax - ktMin )/(ntBins + 1);
   // ---------------------------------------------------------------------------------

  // ---------------------------------------------------------------------------------
   // book histograms
   TH2D* hCL_Obs       = new TH2D("hCL_Obs"	 ,"(k,k~) Obs. excl. CL"                , nBins, kMin, kMax, ntBins, ktMin, ktMax);
   TH2D* hCL_Exp       = new TH2D("hCL_Exp"	 ,"(k,k~) Exp. excl. CL"                , nBins, kMin, kMax, ntBins, ktMin, ktMax);
   TH2D* hCL_Exp_m1sig = new TH2D("hCL_Exp_m1sig","(k,k~) Exp.-1Sig excl. CL"        , nBins, kMin, kMax, ntBins, ktMin, ktMax);
   TH2D* hCL_Exp_p1sig = new TH2D("hCL_Exp_p1sig","(k,k~) Exp.+1Sig excl. CL"        , nBins, kMin, kMax, ntBins, ktMin, ktMax);
   // book histograms
   TH2D* hCL_Exp_XX    = new TH2D("hCL_Exp_XX","(k,k~) Exp. excl. CL(0.68,0.95,0.99)", nBins, kMin, kMax, ntBins, ktMin, ktMax);


   // Define limits of k and k~ at 68%, 95% and 99%
   // 68% CL ------------- for k positive values
   double  k_68_low =  999.0;
   double  k_68_hig = -999.0;
   double kt_68_low =  999.0;
   double kt_68_hig = -999.0; 
   // 95% CL -------------
   double  k_95_low =  999.0;
   double  k_95_hig = -999.0;
   double kt_95_low =  999.0;
   double kt_95_hig = -999.0; 
   // 99% CL -------------
   double  k_99_low =  999.0;
   double  k_99_hig = -999.0;
   double kt_99_low =  999.0;
   double kt_99_hig = -999.0; 
   // 68% CL ------------- for k negative values
   double  k_68_low_n =  999.0;
   double  k_68_hig_n = -999.0;
   // 95% CL -------------
   double  k_95_low_n =  999.0;
   double  k_95_hig_n = -999.0;
   // 99% CL -------------
   double  k_99_low_n =  999.0;
   double  k_99_hig_n = -999.0;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      //fill histograms
      hCL_Obs        ->Fill( k, ktil, CL_Obs );
      hCL_Exp        ->Fill( k, ktil, CL_Exp );
      hCL_Exp_m1sig  ->Fill( k, ktil, CL_ExpM1sig );
      hCL_Exp_p1sig  ->Fill( k, ktil, CL_ExpP1sig );

      // Check limits at 99%, 95 and 68% for k and ktil
      int intCL = int(CL_Exp*1000);
      cout << " CL_Exp = " << CL_Exp << " int(CL_Exp)= " << intCL << endl;
      // 68%
    //if ( intCL >= 678 && intCL <= 682 ){
      if ( intCL <= 685 && intCL >= 675 ){
        // fill histogram
        cout << "                                  --- CL=68% ---" << endl;
        hCL_Exp_XX ->Fill( k, ktil, CL_Exp );
        // k
        if ( k > 0.0 ){
            if ( k <= k_68_low ) k_68_low = k;
            if ( k >= k_68_hig ) k_68_hig = k;
        } else {
            if ( k <= k_68_low_n ) k_68_low_n = k;
            if ( k >= k_68_hig_n ) k_68_hig_n = k;         
        }
        // k~
        if ( ktil <= kt_68_low ) kt_68_low = ktil;
        if ( ktil >= kt_68_hig ) kt_68_hig = ktil;
      }
      // 95%
      if ( intCL <= 955 && intCL >= 945 ){
        // fill histogram
        hCL_Exp_XX ->Fill( k, ktil, CL_Exp );
        // k
        if ( k > 0.0 ){
            if ( k <= k_95_low ) k_95_low = k;
            if ( k >= k_95_hig ) k_95_hig = k;
        } else{
            if ( k <= k_95_low_n ) k_95_low_n = k;
            if ( k >= k_95_hig_n ) k_95_hig_n = k;
        }
        // k~
        if ( ktil <= kt_95_low ) kt_95_low = ktil;
        if ( ktil >= kt_95_hig ) kt_95_hig = ktil;
      }
      // 99%
      if ( intCL <= 995 && intCL >= 985 ){
        // fill histogram
        //hCL_Exp_XX ->Fill( k, ktil, CL_Exp );
        // k
        if ( k > 0.0 ){
            if ( k <= k_99_low ) k_99_low = k;
            if ( k >= k_99_hig ) k_99_hig = k;
        } else{
            if ( k <= k_99_low_n ) k_99_low_n = k;
            if ( k >= k_99_hig_n ) k_99_hig_n = k;
        }
        // k~
        if ( ktil <= kt_99_low ) kt_99_low = ktil;
        if ( ktil >= kt_99_hig ) kt_99_hig = ktil;
      }
   }

   // Printout 68% limits
   cout << " " << endl;
   cout << "-----------------------------------------" << endl;
   cout << "68\% Limits for:   (neg. k)  k =[" << k_68_low_n << "," << k_68_hig_n << "]    (pos. k)  k =[" << k_68_low << "," << k_68_hig << "]   and for k~ =[" << kt_68_low << "," << kt_68_hig << "]" << endl;
   cout << "95\% Limits for:   (neg. k)  k =[" << k_95_low_n << "," << k_95_hig_n << "]    (pos. k)  k =[" << k_95_low << "," << k_95_hig << "]   and for k~ =[" << kt_95_low << "," << kt_95_hig << "]" << endl;
   cout << "99\% Limits for:   (neg. k)  k =[" << k_99_low_n << "," << k_99_hig_n << "]    (pos. k)  k =[" << k_99_low << "," << k_99_hig << "]   and for k~ =[" << kt_99_low << "," << kt_99_hig << "]" << endl;
   cout << "-----------------------------------------" << endl;
   cout << " " << endl; 

   // plot and print histogram
   //string Xtit = " #it{#kappa}";
   //string Ytit = " #it{#tilde{#kappa}}";
   // case (0,2)
      string Xtit = " | #it{g^{ S}_{X_{t}}} |";
      string Ytit = " | #it{g^{ P}_{X_{t}}} |";
   // case (1,2)
   // string Xtit = "| #it{g^{ S}_{X_{t}}} |";
   // string Ytit = " #it{g^{ P}_{X_{t}}}";
   // define Plot, Hist Filenames and Legend
   string myFileName, myLegend;
 //myFileName = "expCL_b2_ttH_2bins";                                                         myLegend = " b_{2}^{t#bar{t}#phi} "; 
 //myFileName = "expCL_b4_ttH_2bins";                                                         myLegend = " b_{4}^{t#bar{t}#phi} "; 
 //myFileName = "expCL_cosExptheta23_3_1t2tb3H*cosExptheta3_4_1t2tb3H4LepN_2bins";            myLegend = "cos(#theta^{#bar{t}#phi}_{#phi})*cos(#theta^{#phi}_{l-})"; 
 //myFileName = "expCL_sinExptheta123_1_1H2t3tb*sinExptheta23_3_1H2t3tb_2bins";               myLegend = "sin(#theta^{t#bar{t}#phi}_{#phi})*sin(#theta^{t#bar{t}}_{#bar{t}})"; 
 //myFileName = "expCL_sinExptheta123_1_1H2t3tb*sinExptheta3_4seq_1t2H3tb4bTbar_2bins";       myLegend = "(seq. boost) sin(#theta^{t#bar{t}#phi}_{#phi})*sin(#theta^{#bar{t}}_{#bar{b}_{#bar{t}}})"; 
 //myFileName = "expCL_sinExptheta123_1_1t2tb3H*sinExptheta3_4seq_1t2tb3H4Wp0.0_2bins";       myLegend = "(seq. boost) sin(#theta^{t#bar{t}#phi}_{t})*sin(#theta^{#phi}_{W^{+}})"; 
 // -- Best of all CL
 //myFileName = "Best_CL_from_Files_2bins";          myLegend = "Best of All Asymmetries CL"; 
 //myFileName = "Best_CL_from_Files";          myLegend = "Best of A#oplus(b_{2},b_{4}) CL"; 
 // -- New distributions 
 //myFileName = "ExpDeltaPhi_lab_ttb";                                                         myLegend = "#Delta#phi(t,#bar{t})/#pi CL"; 
 //myFileName = "sinExptheta123_1_1H2t3tb*sinExptheta23_3_1H2t3tb";                            myLegend = "sin(#theta_{#phi}^{t#bar{t}#phi})*sin(#theta_{#bar{t}}^{t#bar{t}}) CL";
 //myFileName = "cosExptheta23_3_1t2tb3H*cosExptheta3_4_1t2tb3H4LepN";                         myLegend = "cos(#theta_{#phi}^{#bar{t}#phi})*cos(#theta_{l^{-}}^{#phi}) CL";
 //myFileName = "myDeltaPHIpi_ExpPhiLepN_ExpPhiLepP";                                          myLegend = "|#Delta #phi_{l-,l+}|/#pi CL";
 //myFileName = "ExpDeltaTheta_ttb_lpln";                                                      myLegend = "cos[#Delta#theta^{t#bar{t}}(l+,l-)]  CL";
 // Ellis Distribution
 // myFileName = "Ellis_ExpDelPhiLpLn_cos0.0_8bins";                                           myLegend = "#Delta #phi^{t#bar{t}}_{l^{-}l^{+}}/#pi [#theta=45^{#circ} (mix. angle)]";   
 // myFileName = "Ellis_ExpDelPhiLpLn_noInt_cos0.0_8bins";                                     myLegend = "#Delta #phi^{t#bar{t}}_{l^{-}l^{+}}/#pi [(no mix. angle)]";   
 // Delphi Distribution
 // myFileName = "Numofeventsspin0plus0gevNev_1_2";                                            myLegend = "#Delta #phi_{l^{-}l^{+}}/#pi (case 1 2)";   
 // myFileName = "Numofeventsspin0plus0gevNev_0_2";                                            myLegend = "#Delta #phi_{l^{-}l^{+}}/#pi (case 0 2)";   
 // Confirmation b2 and b4
 // myFileName = "expCL_b2_ttH_8bins";                                                         myLegend = " b_{2}^{t#bar{t}#phi} "; 
 // myFileName = "expCL_b4_ttH_8bins";                                                         myLegend = " b_{4}^{t#bar{t}#phi} "; 
 // Esteban --------------------------
 // myFileName = "c1tthframespin0_0gevNev";                                                    myLegend = " b_{2}^{t#bar{t}#phi} "; 
 // ----------------------------------------------------------------------------------------------------
 // -------------------------------------------- New Papers: Higgs Mass Paper 2021 ---------------------
 // ----------------------------------------------------------------------------------------------------
 // L=200pb-1, results for the new paper 2021  **** Asymmetries ****
 //myFileName = "expCL_b2_ttH0.0_1bins";                                                       myLegend = " b_{2}^{t#bar{t}#phi} "; 
 //myFileName = "expCL_b4_ttH0.0_1bins";                                                       myLegend = " b_{4}^{t#bar{t}#phi} "; 
 //myFileName = "expCL_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins";              myLegend = "sin(#theta^{t#bar{t}#phi}_{#phi})*sin(#theta^{t#bar{t}}_{#bar{t}})"; 
 //myFileName = "expCL_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins";      myLegend = "(seq. boost) sin(#theta^{t#bar{t}#phi}_{#phi})*sin(#theta^{#bar{t}}_{#bar{b}_{#bar{t}}})"; 
 // -- Choice for NULL Asymmetry limits
 // myFileName = "expCL_b2_ttH0.0_1bins_AsymttH_NULL";                                         myLegend = " b_{2}^{t#bar{t}H} Asym(ttH)=0.";
 // myFileName = "expCL_b2_ttH0.0_1bins_AsymFullBack_NULL";                                    myLegend = " b_{2}^{t#bar{t}H} Asym(SM, no 0^{+} Higgs)=0.";
 // myFileName = "expCL_b2_ttH0.0_1bins_AsymFullBack_SMHiggs_NULL";                            myLegend = " b_{2}^{t#bar{t}H} Asym(SM, inc. 0^{+} Higgs)=0.";
 // myFileName = "expCL_b4_ttH0.0_1bins_AsymttH_NULL";                                         myLegend = " b_{4}^{t#bar{t}H} Asym(ttH)=0.";
 // -- Choice for best cases from scans.................................................................
 // myFileName = "Expb2_ttb_ttH0.0_1bins_-0.22_A_with_Expb4_ttb_ttH0.0_1bins_0.04_A";                                                                            myLegend = "(Case 12) Asym. Scan [x_{1}=-0.22,x_{2}=0.04]";
 // myFileName = "Expb2_ttb_ttH0.0_1bins_-0.24_A_with_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_0.18_A";                                          myLegend = "(Case 13) Asym. Scan [x_{1}=-0.24,x_{3}=0.18]";
 // myFileName = "Expb2_ttb_ttH0.0_1bins_-0.22_A_with_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_0.15_A";                                  myLegend = "(Case 14) Asym. Scan [x_{1}=-0.22,x_{4}=0.15]";
 // myFileName = "Expb4_ttb_ttH0.0_1bins_-0.46_A_with_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_0.18_A";                                          myLegend = "(Case 23) Asym. Scan [x_{2}=-0.46,x_{3}=0.18]";
 // myFileName = "Expb4_ttb_ttH0.0_1bins_-0.74_A_with_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_0.15_A";                                  myLegend = "(Case 24) Asym. Scan [x_{2}=-0.74,x_{3}=0.15]";
 // myFileName = "sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_0.89_A_with_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_0.15_A"; myLegend = "(Case 34) Asym. Scan [x_{3}=0.89,x_{4}=0.15]";
 // -- Choice for best cases from scans
 // myFileName = "Best_CL_from_Files_12_34";                                                   myLegend = "(Combination) Asym. Scan";
 // myFileName = "Best_CL_from_Files_13_24";                                                   myLegend = "(Combination) Asym. Scan";
 // myFileName = "Best_CL_from_Files_14_23";                                                   myLegend = "(Combination) Asym. Scan";
 // ....................................................................................................
 // -- Best of all CL
 //myFileName = "Best_CL_from_Files_Asymmetries_Only";                                         myLegend = "Best of All Asymmetries CL"; 
 //myFileName = "Best_CL_from_Files_Angular_Only";                                             myLegend = "Best of All Angular Dist. CL"; 
 //myFileName = "Best_CL_from_Files_ALL";                                                      myLegend = "Best of Asym+Diff. CL"; 
 // L=200pb-1, results for the new paper 2021  **** Angular Distributions ****
 //myFileName = "expCL_b2_ttH0.0_8bins";                                                       myLegend = " b_{2}^{t#bar{t}H} "; 
 //myFileName = "expCL_b4_ttH0.0_8bins";                                                       myLegend = " b_{4}^{t#bar{t}H} "; 
 //myFileName = "expCL_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_8bins";              myLegend = "sin(#theta^{t#bar{t}H}_{H})*sin(#theta^{t#bar{t}}_{#bar{t}})"; 
 //myFileName = "expCL_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_8bins";      myLegend = "(seq. boost) sin(#theta^{t#bar{t}H}_{H})*sin(#theta^{#bar{t}}_{#bar{b}_{#bar{t}}})"; 
 // -- Ellis Distribution
 //myFileName = "Ellis_ExpDelPhiLpLn_cos0.0_lum30_8bins";                                      myLegend = "#Delta #phi^{t#bar{t}}_{l^{-}l^{+}}/#pi (with Interf.)";   
 // L=200pb-1, results for the new paper 2021  **** CPsign Angular Distributions ****
 //myFileName = "CPSign_expCL_b2_ttH0.0_8bins";                                                  myLegend = " CP_{sign} #times |b_{2}^{t#bar{t}H}| "; 
 //myFileName = "CPSign_expCL_b4_ttH0.0_8bins";                                                  myLegend = " CP_{sign} #times |b_{4}^{t#bar{t}H}| "; 
 //myFileName = "CPSign_expCL_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_8bins";         myLegend = "CP_{sign} #times [sin(#theta^{t#bar{t}H}_{H})*sin(#theta^{t#bar{t}}_{#bar{t}})]"; 
 //myFileName = "CPSign_expCL_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_8bins"; myLegend = "(seq. boost) CP_{sign} #times [sin(#theta^{t#bar{t}H}_{H})*sin(#theta^{#bar{t}}_{#bar{b}_{#bar{t}}})]"; 
 // L=3000pb-1, results for the new paper 2021  **** CPsign Angular Distributions ****
 //myFileName = "expCL_b2_ttH0.0_8bins";                                                         myLegend = " b_{2}^{t#bar{t}#phi} "; 
 //myFileName = "expCL_b4_ttH0.0_8bins";                                                         myLegend = " b_{4}^{t#bar{t}#phi} "; 
 //myFileName = "CPSign_expCL_b2_ttH0.0_lum30_8bins";                                                  myLegend = " CP_{sign} #times |b_{2}^{t#bar{t}H}| "; 
 //myFileName = "CPSign_expCL_b4_ttH0.0_lum30_8bins";                                                  myLegend = " CP_{sign} #times |b_{4}^{t#bar{t}H}| "; 
 //myFileName = "CPSign_expCL_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_lum30_8bins";         myLegend = "CP_{sign} #times [sin(#theta^{t#bar{t}H}_{H})*sin(#theta^{t#bar{t}}_{#bar{t}})]"; 
 //myFileName = "CPSign_expCL_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_lum30_8bins"; myLegend = "(seq. boost) CP_{sign} #times [sin(#theta^{t#bar{t}H}_{H})*sin(#theta^{#bar{t}}_{#bar{b}_{#bar{t}}})]"; 
 // -- Dorival Distribution
 //myFileName = "Dorival_ExpDelPhiLpLnTT_0.0_lum30_8bins";                                       myLegend = "#Delta #phi^{t#bar{t}}_{l^{-}l^{+}}/#pi (with Interf.)";   
 // CP in ttH system
 //myFileName = "CPTTH_expCL_b2_ttH0.0_lum30_8bins";                                             myLegend = " CP^{t#bar{t}H}_{sign} #times |b_{2}^{t#bar{t}H}| "; 
 //myFileName = "CPTTH_expCL_b4_ttH0.0_lum30_8bins";                                             myLegend = " CP^{t#bar{t}H}_{sign} #times |b_{4}^{t#bar{t}H}| "; 
 //
 // ----------------------------------------------------------------------------------------------------
 // -------------------------------------------- Dark Matter Paper 2022 --------------------------------
 // ----------------------------------------------------------------------------------------------------
 //myFileName = "Expb2_ttb0.0_s1_9bins";                         /* Palette=4*/                   myLegend = "(exp) b_{2}^{LAB}";
 //myFileName = "Expb4_ttb0.0_s1_9bins";                         /* Palette=5*/                   myLegend = "(exp) b_{4}^{LAB}";
 //myFileName = "absExpSpinCorr_DelPhiLpLn0.0_s1_9bins";         /* Palette=6*/                   myLegend = "(exp) |#Delta#phi_{l^{+}l^{-}}| /#pi";
   myFileName = "ExpSpinCorr_Ncosl2_SpinCorr_Ncosl10.0_s1_3bins";/* Palette=7*/                   myLegend = "(exp) 2D[cos(#theta^{N}_{l+}),cos(#theta^{N}_{l-})]";
 //myFileName = "ExpSpinCorr_CosDpar0.0_s1_9bins";               /* Palette=3*/                   myLegend = "(exp) cos(#phi_{l+l-})";
 //myFileName = "ExpSpinCorr_CosCosCpar0.0_s1_9bins";            /* Palette=2*/                   myLegend = "(exp) cos(#theta*_{l+})cos(#theta*_{l-})";
 // plot distribution
   doPlot2D( hCL_Exp, hCL_Exp_XX, myFileName, myFileName, "Dark Matter Mediator m_{X_{t}} = 0.01GeV", myLegend, 4, Xtit, Ytit);
 //doPlot2D( hCL_Exp, hCL_Exp_XX, myFileName, myFileName, "m_{#phi} = 0.0GeV (J^{P}=0^{-})", myLegend, 0, Xtit, Ytit);
}
