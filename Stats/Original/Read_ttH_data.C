#include <TROOT.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TChain.h>
#include <TLine.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TF1.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <list>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <iterator>
#include "TSystemFile.h"
#include "TSystemDirectory.h"

using std::cout;
using namespace std;
using std::endl;
using std::vector;

void Read_ttH_data()
{   
   // tb parton
   Float_t          Lumi             = -999;   
   Float_t          CL_Obs           = -999; 
   Float_t          CL_Exp           = -999; 
   Float_t          CL_ExpM1sig      = -999; 
   Float_t          CL_ExpP1sig      = -999; 
   Float_t          k                = -999; 
   Float_t          ktil             = -999;
   Float_t          LLR_null_Min     = -999; 
   Float_t          LLR_null_Median  = -999; 
   Float_t          LLR_null_Max     = -999; 
   Float_t          LLRs_Min         = -999; 
   Float_t          LLRs_Median      = -999; 
   Float_t          LLRs_Max         = -999; 
 
   //--------------------------------------------
   //  Define Input DM/Higgs Mass and Variable
   //--------------------------------------------
   //string massX0 = "125";
     string massX0 = "0";
     int   iChoice =   805;  // --Individual Cases--------------------
                             // =   1(  2) b2(b4) in LAB
                             // =  11( 12) b2(b4) in ttH
                             // = 101(102) other variables (see below)
                             // =  99 Best of all numbers
                             // = 201      Ellis \Delta\Phi variable  
                             // = 301      \Delta\Phi variable  case: 1,2
                             // = 401 (402) set A[ttH]=0 (A[ttA]=0)
                             // --Scan Cases--------------------------
                             // = 10001 b2          ten thousand files
                             // = 10002 b4          ten thousand files
                             // = 10003 sin*sin     ten thousand files
                             // = 10004 sin*sin_seq ten thousand files
                             // --Best Cases from Scans---------------
                             // observable= 1: b2
                             //             2: b4
                             //             3: sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb
                             //             4: sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar
                             // = 612   (1,2) observables combined
                             // = 613   (1,3)     "           "
                             // = 614   (1,4)     "           "
                             // = 623   (2,3)     "           "
                             // = 624   (2,4)     "           "
                             // = 634   (3,4)     "           "
                             // = 701   (1,2) and (3,4) combination
                             // = 702   (1,3) and (2,4) combination
                             // = 703   (1,4) and (2,3) combination
                             // --Dark Matter Studies-------------------------
                             // = 800   DM Studies: absExpSpinCorr_DelPhiLpLn0   
                             // --Dark Matter Studies-------------------------
   //--------------------------------------------
   //           Define Input Variable 
   //--------------------------------------------
   string Fname;
   // -- LAB Frame --
      if ( iChoice ==   1 ) Fname = "b2_ttb_A.root_table";
      if ( iChoice ==   2 ) Fname = "b4_ttb_A.root_table";
   // -- CM  Frame --
   // ..Asymmetries.. 
      if ( iChoice ==  11 ) Fname = "Expb2_ttb_ttH0.0_1bins_A.root_table";
      if ( iChoice ==  12 ) Fname = "Expb4_ttb_ttH0.0_1bins_A.root_table";
      if ( iChoice ==  13 ) Fname = "sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_A.root_table";
      if ( iChoice ==  14 ) Fname = "sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_A.root_table";
   // ..Angular Dis.. 
      if ( iChoice ==  21 ) Fname = "Expb2_ttb_ttH0.0_8bins_A.root_table";
      if ( iChoice ==  22 ) Fname = "Expb4_ttb_ttH0.0_8bins_A.root_table";
      if ( iChoice ==  23 ) Fname = "sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_8bins_A.root_table";
      if ( iChoice ==  24 ) Fname = "sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_8bins_A.root_table";
   // ..Angular CP Dis.. 
      if ( iChoice == 121 ) Fname = "CPSign_Expb2_ttb_ttH0.0_8bins_A.root_table";
      if ( iChoice == 122 ) Fname = "CPSign_Expb4_ttb_ttH0.0_8bins_A.root_table";
      if ( iChoice == 123 ) Fname = "CPSign_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_8bins_A.root_table";
      if ( iChoice == 124 ) Fname = "CPSign_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_8bins_A.root_table";
   // ..Angular CPttH Dis.. 
      if ( iChoice == 125 ) Fname = "CPTTH_Expb2_ttb_ttH0.0_8bins_A.root_table";
      if ( iChoice == 126 ) Fname = "CPTTH_Expb4_ttb_ttH0.0_8bins_A.root_table";
    //if ( iChoice ==  11 ) Fname = "b2_ttb_ttH_A.root_table";
    //if ( iChoice ==  12 ) Fname = "b4_ttb_ttH_A.root_table";
    //if ( iChoice ==  11 ) Fname = "b2_ttb_ttH_2bins_A.root_table";
    //if ( iChoice ==  12 ) Fname = "b4_ttb_ttH_2bins_A.root_table";
   // -- Other Var --
      if ( iChoice == 101 ) Fname = "Exp_b4_Gunion_fullSM_ttX00.0_1111103.root_table";
      if ( iChoice == 102 ) Fname = "Prob_TMVA_BDTG_ge3b_fullSM_ttX00.0_1111103.root_table";

   // -- Other Var --
      if ( iChoice ==  99 ) Fname = "Best_CL_from_Files";
   // -- Ellis+Dorival Var --
      if ( iChoice == 201 ) Fname = "Ellis_ExpDelPhiLpLn_cos0.0_8bins_A.root_table"; // 
      if ( iChoice == 202 ) Fname = "Ellis_ExpDelPhiLpLn_cos0.0_lum30_8bins_A.root_table";
      if ( iChoice == 203 ) Fname = "Dorival_ExpDelPhiLpLnTT_0.0_8bins_A.root_table";
   // -- Spin 0-1  --
   // if ( iChoice == 301 ) Fname = "Numofeventsspin0plus0gevNev_A.root_table";
      if ( iChoice == 301 ) Fname = "c1tthframespin0_0gevNev_A.root_table";
   // -- Choice for NULL Asymmetry limits
      if ( iChoice == 401 ) Fname = "Expb2_ttb_ttH0.0_1bins_A.root_table";
      if ( iChoice == 402 ) Fname = "Expb4_ttb_ttH0.0_1bins_A.root_table";
   // -- Choice for best cases from scans
      if ( iChoice == 612 ) Fname = "Expb2_ttb_ttH0.0_1bins_-0.22_A_with_Expb4_ttb_ttH0.0_1bins_0.04_A";
      if ( iChoice == 613 ) Fname = "Expb2_ttb_ttH0.0_1bins_-0.24_A_with_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_0.18_A";
      if ( iChoice == 614 ) Fname = "Expb2_ttb_ttH0.0_1bins_-0.22_A_with_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_0.15_A";
      if ( iChoice == 623 ) Fname = "Expb4_ttb_ttH0.0_1bins_-0.46_A_with_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_0.18_A";
      if ( iChoice == 624 ) Fname = "Expb4_ttb_ttH0.0_1bins_-0.74_A_with_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_0.15_A";
      if ( iChoice == 634 ) Fname = "sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_0.89_A_with_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_0.15_A";
      if ( iChoice == 701 || iChoice == 702 || iChoice == 703 ) Fname = "Best_CL_from_Files";
   // -- Choice for Dark Matter studies
      if ( iChoice == 800 ) Fname = "Expb2_ttb0.0_s1_9bins_A.root_table"; 
      if ( iChoice == 801 ) Fname = "Expb4_ttb0.0_s1_9bins_A.root_table"; 
      if ( iChoice == 802 ) Fname = "absExpSpinCorr_DelPhiLpLn0.0_s1_9bins_A.root_table"; 
      if ( iChoice == 803 ) Fname = "ExpSpinCorr_Ncosl2:SpinCorr_Ncosl10.0_s1_3bins_A.root_table"; 
      if ( iChoice == 804 ) Fname = "ExpSpinCorr_CosDpar0.0_s1_9bins_A.root_table"; 
      if ( iChoice == 805 ) Fname = "ExpSpinCorr_CosCosCpar0.0_s1_9bins_A.root_table"; 

   //--------------------------------------------
   //           Define Input File Names 
   //--------------------------------------------
   std::vector<string> inpFile;
   std::vector<string> outFile;
   // ----------------------------------------------------------------------------------------------------
   // Read single files if not 10000 files ---------------------------------------------------------------
   // ----------------------------------------------------------------------------------------------------
   if ( iChoice < 10001 ) {
        // -- Low Mass  -- this is the default !!!!!!!
        //  inpFile.push_back("H_LowMass/H"+massX0+"/Histograms/Tables/"+Fname+".txt");    // input file 
        //
        //  inpFile.push_back("Histograms/Tables/"+Fname+".txt");           // input file 
        //  inpFile.push_back("Histograms_125GeV/Tables/"+Fname+".txt");    // input file 
        //  inpFile.push_back("Histograms/H125tt/Tables/"+Fname+".txt");    // input file 
        // -- Low Mass  --
        //  inpFile.push_back("Histograms/H"+massX0+"tt/Tables/"+Fname+".txt");    // input file 
        // -- New Higgs 2 bins with Asymmetries ----
        //  inpFile.push_back(H_LowMass_2bins/H"+massX0+"_2bins/Histograms/Tables/"+Fname+".txt");                  // input file
        //  inpFile.push_back(H_LowMass_2bins/H"+massX0+"_2bins/Histograms/Tables_Asym_1-2_chi2/"+Fname+".txt");    // input file
        // -- Low Mass Higgs 8 bins Full Distributions ----
        //  inpFile.push_back("H_LowMass/H"+massX0+"/Histograms/Tables/"+Fname+".txt");    // input file
        // -- Best CL
        //  inpFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/"+Fname+".txt");
        // -- Best CL
        //  inpFile.push_back("/Users/onofre/CL_Scan/H_125GeV_Paper2021/H125_8bins/Histograms/Tables/"+Fname+".txt");
        // -- DelPhi
        //  inpFile.push_back("/Users/onofre/CL_Scan/SpinCorr_DelPhi_1_2/Histograms/Tables/"+Fname+".txt");
        //  inpFile.push_back("/Users/onofre/CL_Scan/SpinCorr_DelPhi_0_2/Histograms/Tables/"+Fname+".txt");
        // -- b2 and b4
        //if ( iChoice ==  21 || iChoice ==  22) inpFile.push_back("/Users/onofre/CL_Scan/H_125GeV_Paper2021/H125_8bins/Histograms/Tables/"+Fname+".txt");
          if ( iChoice ==  21 || iChoice ==  22 ) inpFile.push_back("/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_HiggsMass_OFICIAL_H125_old/Tables/"+Fname+".txt");
        // -- Esteban
        //  inpFile.push_back("/Users/onofre/CL_Scan/Esteban_b4/Histograms/Tables/"+Fname+".txt");
        // ----------------------------------------------------------------------------------------------------
        // -- Paper2021 Higgs --- b2,b4,angular variables -----------------------------------------------------
        //  inpFile.push_back("/Users/onofre/CL_Scan/H_125GeV_Paper2021/H125_all/Histograms/Tables/"+Fname+".txt");
        // -- Best CL
        //  inpFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/"+Fname+".txt");
        //  inpFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/"+Fname+".txt");
        //  inpFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_AngularDist_Only/"+Fname+".txt");
        // -- Choice for NULL Asymmetry limits
        //  inpFile.push_back("/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_HiggsMass_OFICIAL_H125/Histograms_Asym_ttH_NULL/Tables/"+Fname+".txt");
        //  inpFile.push_back("/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_HiggsMass_OFICIAL_H125/Histograms_Asym_FullBack_NULL/Tables/"+Fname+".txt");
        //  inpFile.push_back("/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_HiggsMass_OFICIAL_H125/Histograms_Asym_FullBack_SMHiggs_NULL/Tables/"+Fname+".txt");
        // -- Choice for best cases from scans
            if ( iChoice == 612 ) inpFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_12/"+Fname+".txt");
            if ( iChoice == 613 ) inpFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_13/"+Fname+".txt");
            if ( iChoice == 614 ) inpFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_14/"+Fname+".txt");
            if ( iChoice == 623 ) inpFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_23/"+Fname+".txt");
            if ( iChoice == 624 ) inpFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_24/"+Fname+".txt");
            if ( iChoice == 634 ) inpFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_34/"+Fname+".txt");
        // -- Choice for best cases combinations
            if ( iChoice == 701 ) inpFile.push_back("/Volumes/DISK_T5/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/12_34/"+Fname+".txt");
            if ( iChoice == 702 ) inpFile.push_back("/Volumes/DISK_T5/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/13_24/"+Fname+".txt");
            if ( iChoice == 703 ) inpFile.push_back("/Volumes/DISK_T5/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/14_23/"+Fname+".txt");
        // -- Choice for Dark Matter Studies
        //  if ( iChoice >= 800 && iChoice <= 805 ) inpFile.push_back("/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_DM_OFICIAL/Tables/"+Fname+".txt");            
        // Spin 0: Case (0,2) and (1,2)
        //  if ( iChoice >= 800 && iChoice <= 805 ) inpFile.push_back("/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_spin0_DM_OFICIAL/Tables/"+Fname+".txt");            
            if ( iChoice >= 800 && iChoice <= 805 ) inpFile.push_back("/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_spin0_DM_OFICIAL/Tables_case_02/"+Fname+".txt");            
        //  if ( iChoice >= 800 && iChoice <= 805 ) inpFile.push_back("/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_spin0_DM_OFICIAL/Tables_case_12/"+Fname+".txt");            
        // ----------------------------------------------------------------------------------------------------
            cout << " " << endl;
            cout << " ###################################################################################....." << endl;
            cout << " ####### Input Variable Name: " << Fname << "  from Input File: " << inpFile[0] << endl;
        // ----------------------------------------------------------------------------------------------------
        //           Define Output File Names 
        // ----------------------------------------------------------------------------------------------------
        // -- Low Mass  -- this is the default !!!!!!!
        // outFile.push_back("Plots/H_LowMass_M"+massX0+"/"+Fname+".CL");                 // output=input to HepFrame file
        //
        // outFile.push_back("Plots/"+Fname+".CL");                                       // output=input to HepFrame file
        // outFile.push_back("Plots/H125tt/"+Fname+".CL");                                // output=input to HepFrame file
        // outFile.push_back("Plots/H"+massX0+"tt/"+Fname+".CL");                         // output=input to HepFrame file
        // 
        // -- New Higgs 2 bins with Asymmetries
        // outFile.push_back("Plots/H_LowMass_M"+massX0+"_2bins_Asym/"+Fname+".CL");      // output=input to HepFrame file
        // -- Low Mass Higgs 8 bins Full Distributions
        // outFile.push_back("Plots/H_LowMass_M"+massX0+"/"+Fname+".CL");                 // output=input to HepFrame file
        // -- Best CL
        // outFile.push_back(/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/"+Fname+".CL");      // output=input to HepFrame file
        // -- DelPhi
        // outFile.push_back("/Users/onofre/CL_Scan/Plots/SpinCorr_DelPhi_1_2/"+Fname+".CL");             // output=input to HepFrame file
        // outFile.push_back("/Users/onofre/CL_Scan/Plots/SpinCorr_DelPhi_0_2/"+Fname+".CL");             // output=input to HepFrame file
        // -- b2 and b4
        // if ( iChoice ==  21 || iChoice ==  22 ) outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/"+Fname+".CL");              // output=input to HepFrame file
           if ( iChoice ==  21 || iChoice ==  22 ) outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/"+Fname+".CL");              // output=input to HepFrame file
        // -- Esteban
        // outFile.push_back("/Users/onofre/CL_Scan/Plots/Esteban/"+Fname+".CL");                         // output=input to HepFrame file
        // ----------------------------------------------------------------------------------------------------
        // -- Paper2021 Higgs --- b2,b4,angular variables -----------------------------------------------------
        // ----------------------------------------------------------------------------------------------------
        // outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/"+Fname+".CL");                       // output to lum200fb
        // outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum3000fb/"+Fname+".CL");                      // output to lum3000fb
        // outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/"+Fname+".CL");      // output to lum200fb
        // outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_AngularDist_Only/"+Fname+".CL");      // output to lum200fb
        // -- Choice for NULL Asymmetry limits
        // outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/"+Fname+"_AsymttH_NULL.CL");              // output to lum200fb
        // outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/"+Fname+"_AsymFullBack_NULL.CL)";         // output to lum200fb
        // outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/"+Fname+"_AsymFullBack_SMHiggs_NULL.CL");  // output to lum200fb
        // -- Choice for best cases from scans
          if ( iChoice == 612 ) outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_12/"+Fname+".CL");  // output to lum200fb
          if ( iChoice == 613 ) outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_13/"+Fname+".CL");  // output to lum200fb
          if ( iChoice == 614 ) outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_14/"+Fname+".CL");  // output to lum200fb
          if ( iChoice == 623 ) outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_23/"+Fname+".CL");  // output to lum200fb
          if ( iChoice == 624 ) outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_24/"+Fname+".CL");  // output to lum200fb
          if ( iChoice == 634 ) outFile.push_back("/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_34/"+Fname+".CL");  // output to lum200fb
        // -- Choice for best cases combinations
          if ( iChoice == 701 ) outFile.push_back("/Volumes/DISK_T5/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/12_34/"+Fname+"_12_34.CL");  // output to lum200fb
          if ( iChoice == 702 ) outFile.push_back("/Volumes/DISK_T5/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/13_24/"+Fname+"_13_24.CL");  // output to lum200fb
          if ( iChoice == 703 ) outFile.push_back("/Volumes/DISK_T5/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/14_23/"+Fname+"_14_23.CL");  // output to lum200fb
        // -- Choice for Dark Matter Studies
          if ( iChoice >= 800 && iChoice <= 805 ) outFile.push_back("/Users/onofre/CL_Scan/Plots/"+Fname+".CL");            
          cout << " ####### Output   File  Name: " << outFile[0] << endl;
          cout << " ###################################################################################....." << endl;
          cout << " " << endl;
        //--------------------------------------------
        // Recreate Output File ----------------------
        //--------------------------------------------
        TFile *hfile = TFile::Open( (outFile[0]+".root").c_str(),"RECREATE");
        // Define TTree
        TTree *tree = new TTree("CL","CL");
        tree->Branch("Lumi"             ,  &Lumi              ,  "Lumi/F"             );
        tree->Branch("CL_Obs"           ,  &CL_Obs            ,  "CL_Obs/F"           );
        tree->Branch("CL_Exp"           ,  &CL_Exp            ,  "CL_Exp/F"           );
        tree->Branch("CL_ExpM1sig"      ,  &CL_ExpM1sig       ,  "CL_ExpM1sig/F"      );
        tree->Branch("CL_ExpP1sig"      ,  &CL_ExpP1sig       ,  "CL_ExpP1sig/F"      );
        tree->Branch("k"                ,  &k                 ,  "k/F"                );
        tree->Branch("ktil"             ,  &ktil              ,  "ktil/F"             );
        tree->Branch("LLR_null_Min"     ,  &LLR_null_Min      ,  "LLR_null_Min/F"     );
        tree->Branch("LLR_null_Median"  ,  &LLR_null_Median   ,  "LLR_null_Median/F"  );
        tree->Branch("LLR_null_Max"     ,  &LLR_null_Max      ,  "LLR_null_Max/F"     );
        tree->Branch("LLRs_Min"         ,  &LLRs_Min          ,  "LLRs_Min/F"         );
        tree->Branch("LLRs_Median"      ,  &LLRs_Median       ,  "LLRs_Median/F"      );
        tree->Branch("LLRs_Max"         ,  &LLRs_Max          ,  "LLRs_Max/F"         );
        // create some histograms
        TH2D* hCL_Obs       = new TH2D("hCL_Obs"      ,"(k,k~) Obs. Excl. CL"     , 41,-2.05,2.05, 41,-2.05,2.05);
        TH2D* hCL_Exp       = new TH2D("hCL_Exp"      ,"(k,k~) Exp. Excl. CL"     , 41,-2.05,2.05, 41,-2.05,2.05);
        TH2D* hCL_Exp_m1sig = new TH2D("hCL_Exp_m1sig","(k,k~) Exp.-1Sig Excl. CL", 41,-2.05,2.05, 41,-2.05,2.05);
        TH2D* hCL_Exp_p1sig = new TH2D("hCL_Exp_p1sig","(k,k~) Exp.+1Sig Excl. CL", 41,-2.05,2.05, 41,-2.05,2.05);
        //
        // ==============================================================================================================================
        // ==============================================================================================================================
        // Open and read data file 
        // ==============================================================================================================================
          ifstream in0;
          in0.open( inpFile[0].c_str() );
        // ==============================================================================================================================
          ofstream cout(  (outFile[0]+".logfile.dat").c_str() );   //output file (just for cross check)   
        // ==============================================================================================================================
        //
        //Count number of lines
        Int_t nlines =0;
        //
        int i = 0;
        //Loop over the full available information
        while (1) {
           printf("%d\n", i++);
            in0  >> Lumi           
                 >> CL_Obs         
                 >> CL_Exp         
                 >> CL_ExpM1sig    
                 >> CL_ExpP1sig    
                 >> k              
                 >> ktil           
                 >> LLR_null_Min   
                 >> LLR_null_Median
                 >> LLR_null_Max   
                 >> LLRs_Min       
                 >> LLRs_Median    
                 >> LLRs_Max;       
            //
            //Check the end of file found (Avoid duplication of last line)
            if (in0.eof()) break;
            // Print out information
            cout   << " " << Lumi           
                   << " " << CL_Obs         
                   << " " << CL_Exp         
                   << " " << CL_ExpM1sig    
                   << " " << CL_ExpP1sig    
                   << " " << k              
                   << " " << ktil           
                   << " " << LLR_null_Min   
                   << " " << LLR_null_Median
                   << " " << LLR_null_Max   
                   << " " << LLRs_Min       
                   << " " << LLRs_Median    
                   << " " << LLRs_Max
             << endl;
            //update number of lines
            nlines ++;
            //fill histograms
            hCL_Obs        ->Fill( k, ktil, CL_Obs );
            hCL_Exp        ->Fill( k, ktil, CL_Exp );
            hCL_Exp_m1sig  ->Fill( k, ktil, CL_ExpM1sig );
            hCL_Exp_p1sig  ->Fill( k, ktil, CL_ExpP1sig );
            //fill tree
            tree->Fill();
        }
        //write histograms
        hCL_Obs        ->Write();
        hCL_Exp        ->Write();
        hCL_Exp_m1sig  ->Write();
        hCL_Exp_p1sig  ->Write();
        //write tree      
        tree->Write();
        // end
        printf(" found %d points \n",nlines );

   // ----------------------------------------------------------------------------------------------------
   // Read 10000 files -----------------------------------------------------------------------------------
   // ----------------------------------------------------------------------------------------------------
   } else {
        // List all files in directory
        std::string path, path_out;
        if ( iChoice == 10001 ) { //Expb2
                                  //path     = "/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_HiggsMass_OFICIAL_H125/Histograms_Scan/Expb2_ttb_ttH0.0_1bins/Tables";
                                  //path_out = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan/Expb2_ttb_ttH0.0_1bins";
                                    path     = "/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_HiggsMass_OFICIAL_H125/Histograms_Scan_100points_CERN/Expb2_ttb_ttH0.0_1bins/Tables";
                                    path_out = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/Expb2_ttb_ttH0.0_1bins";
                                }
        if ( iChoice == 10002 ) { //Expb4
                                  //path     = "/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_HiggsMass_OFICIAL_H125/Histograms_Scan/Expb2_ttb_ttH0.0_1bins/Tables";
                                  //path_out = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan/Expb2_ttb_ttH0.0_1bins";
                                    path     = "/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_HiggsMass_OFICIAL_H125/Histograms_Scan_100points_CERN/Expb4_ttb_ttH0.0_1bins/Tables";
                                    path_out = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/Expb4_ttb_ttH0.0_1bins";
                                } 
        if ( iChoice == 10003 ) { //sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins
                                    path     = "/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_HiggsMass_OFICIAL_H125/Histograms_Scan_100points_CERN/sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins/Tables";
                                    path_out = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins";
                                } 
        if ( iChoice == 10004 ) { //sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins
                                    path     = "/Users/onofre/madanalysis5/bin/ttH_dilep_REC5/StackPlots/Histograms_StackPlots_HiggsMass_OFICIAL_H125/Histograms_Scan_100points_CERN/sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins/Tables";
                                    path_out = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins";
                                } 

        const char *dirname=path.c_str();
        const char *ext=".txt";

        TSystemDirectory dir(dirname, dirname); 
        TList *files = dir.GetListOfFiles(); 

        int ic=-1;
        if ( files ) { 
              TSystemFile *file; 
              TString fname; 
              TIter next( files ); 
              while ( (file=(TSystemFile*)next()) ) { 
                  fname = file->GetName(); 
                  if (!file->IsDirectory() && fname.EndsWith(ext)) { 
                    ic++;
                    inpFile.push_back( fname.Data() );
                    //cout << fname.Data() << endl;
                    //cout << inpFile[ic] << endl;
                  } 
              } 
        } 
        cout << " ------------------------------------------------------------------------------------------------------- " << endl;
        cout << " Directory with " << int(inpFile.size()) << " Files: " << path << endl;
        cout << " ------------------------------------------------------------------------------------------------------- " << endl;
        for (int ic=0; ic< int(inpFile.size()); ic++) {
            // print out information on file read
            cout << " Input file number "<< ic << " is  " << path+"/"+inpFile[ic] << endl;
            // take away the last ".txt" from the inpFile to define out
            std::string out0;
            std::copy( inpFile[ic].begin(), inpFile[ic].end() - 4, std::back_inserter(out0));
            outFile.push_back( out0 ); 
            cout << "       output file "<< ic << " is  " << path_out+"/"+outFile[ic] << endl;
            //            
            //--------------------------------------------
            // Recreate Output File ----------------------
            //--------------------------------------------
            TFile *hfile = TFile::Open( (path_out+"/"+outFile[ic]+".root").c_str(),"RECREATE");
            // Define TTree
            TTree *tree = new TTree("CL","CL");
            tree->Branch("Lumi"             ,  &Lumi              ,  "Lumi/F"             );
            tree->Branch("CL_Obs"           ,  &CL_Obs            ,  "CL_Obs/F"           );
            tree->Branch("CL_Exp"           ,  &CL_Exp            ,  "CL_Exp/F"           );
            tree->Branch("CL_ExpM1sig"      ,  &CL_ExpM1sig       ,  "CL_ExpM1sig/F"      );
            tree->Branch("CL_ExpP1sig"      ,  &CL_ExpP1sig       ,  "CL_ExpP1sig/F"      );
            tree->Branch("k"                ,  &k                 ,  "k/F"                );
            tree->Branch("ktil"             ,  &ktil              ,  "ktil/F"             );
            tree->Branch("LLR_null_Min"     ,  &LLR_null_Min      ,  "LLR_null_Min/F"     );
            tree->Branch("LLR_null_Median"  ,  &LLR_null_Median   ,  "LLR_null_Median/F"  );
            tree->Branch("LLR_null_Max"     ,  &LLR_null_Max      ,  "LLR_null_Max/F"     );
            tree->Branch("LLRs_Min"         ,  &LLRs_Min          ,  "LLRs_Min/F"         );
            tree->Branch("LLRs_Median"      ,  &LLRs_Median       ,  "LLRs_Median/F"      );
            tree->Branch("LLRs_Max"         ,  &LLRs_Max          ,  "LLRs_Max/F"         );
            // create some histograms
            TH2D* hCL_Obs       = new TH2D("hCL_Obs"      ,"(k,k~) Obs. Excl. CL"     , 41,-2.05,2.05, 41,-2.05,2.05);
            TH2D* hCL_Exp       = new TH2D("hCL_Exp"      ,"(k,k~) Exp. Excl. CL"     , 41,-2.05,2.05, 41,-2.05,2.05);
            TH2D* hCL_Exp_m1sig = new TH2D("hCL_Exp_m1sig","(k,k~) Exp.-1Sig Excl. CL", 41,-2.05,2.05, 41,-2.05,2.05);
            TH2D* hCL_Exp_p1sig = new TH2D("hCL_Exp_p1sig","(k,k~) Exp.+1Sig Excl. CL", 41,-2.05,2.05, 41,-2.05,2.05);
            //
            // ==============================================================================================================================
            // ==============================================================================================================================
            // Open and read data file 
            // ==============================================================================================================================
              ifstream in0;
              in0.open( (path+"/"+inpFile[ic]).c_str() );
            // ==============================================================================================================================
              ofstream cout(  (path_out+"/"+outFile[ic]+".logfile.dat").c_str() );   //output file (just for cross check)   
            // ==============================================================================================================================
            //
            //Count number of lines
            Int_t nlines =0;
            //
            int i = 0;
            //Loop over the full available information
            while (1) {
                //printf("%d\n", i++);
                in0  >> Lumi           
                     >> CL_Obs         
                     >> CL_Exp         
                     >> CL_ExpM1sig    
                     >> CL_ExpP1sig    
                     >> k              
                     >> ktil           
                     >> LLR_null_Min   
                     >> LLR_null_Median
                     >> LLR_null_Max   
                     >> LLRs_Min       
                     >> LLRs_Median    
                     >> LLRs_Max;       
                //
                //Check the end of file found (Avoid duplication of last line)
                if (in0.eof()) break;
                // Print out information
                cout   << " " << Lumi           
                       << " " << CL_Obs         
                       << " " << CL_Exp         
                       << " " << CL_ExpM1sig    
                       << " " << CL_ExpP1sig    
                       << " " << k              
                       << " " << ktil           
                       << " " << LLR_null_Min   
                       << " " << LLR_null_Median
                       << " " << LLR_null_Max   
                       << " " << LLRs_Min       
                       << " " << LLRs_Median    
                       << " " << LLRs_Max
                 << endl;
                //update number of lines
                nlines ++;
                //fill histograms
                hCL_Obs        ->Fill( k, ktil, CL_Obs );
                hCL_Exp        ->Fill( k, ktil, CL_Exp );
                hCL_Exp_m1sig  ->Fill( k, ktil, CL_ExpM1sig );
                hCL_Exp_p1sig  ->Fill( k, ktil, CL_ExpP1sig );
                //fill tree
                tree->Fill();
            }
            //write histograms
            hCL_Obs        ->Write();
            hCL_Exp        ->Write();
            hCL_Exp_m1sig  ->Write();
            hCL_Exp_p1sig  ->Write();
            //write tree      
            tree->Write();
            // end
            printf(" found %d points \n",nlines );        
        }
   }


}
