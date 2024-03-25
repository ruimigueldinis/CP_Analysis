//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun May 17 08:47:53 2020 by ROOT version 5.34/38
// from TTree CL/CL
// found on file: Rootuples/b2_ttb_A.root_table.CL.root
//////////////////////////////////////////////////////////

#ifndef plotCL2D_h
#define plotCL2D_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class plotCL2D {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         Lumi;
   Float_t         CL_Obs;
   Float_t         CL_Exp;
   Float_t         CL_ExpM1sig;
   Float_t         CL_ExpP1sig;
   Float_t         k;
   Float_t         ktil;
   Float_t         LLR_null_Min;
   Float_t         LLR_null_Median;
   Float_t         LLR_null_Max;
   Float_t         LLRs_Min;
   Float_t         LLRs_Median;
   Float_t         LLRs_Max;

   // List of branches
   TBranch        *b_Lumi;   //!
   TBranch        *b_CL_Obs;   //!
   TBranch        *b_CL_Exp;   //!
   TBranch        *b_CL_ExpM1sig;   //!
   TBranch        *b_CL_ExpP1sig;   //!
   TBranch        *b_k;   //!
   TBranch        *b_ktil;   //!
   TBranch        *b_LLR_null_Min;   //!
   TBranch        *b_LLR_null_Median;   //!
   TBranch        *b_LLR_null_Max;   //!
   TBranch        *b_LLRs_Min;   //!
   TBranch        *b_LLRs_Median;   //!
   TBranch        *b_LLRs_Max;   //!

   plotCL2D(TTree *tree=0);
   virtual ~plotCL2D();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef plotCL2D_cxx
plotCL2D::plotCL2D(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
    // ------------------------------------------------------------------------------
    // ----------------------------------------- (k,k~) plane scan with 2  bins -----
    // ------------------------------------------------------------------------------
    // L=139pb-1, 0-2
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_LowMass_M125_2bins_Asym/b2_ttb_ttH_2bins_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_LowMass_M125_2bins_Asym/b4_ttb_ttH_2bins_A.root_table.CL.root ";
    // L=139pb-1, 1-2
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_LowMass_M125_2bins_Asym/b2_ttb_ttH_2bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_LowMass_M125_2bins_Asym/b4_ttb_ttH_2bins_A.root_table.CL.root ";
    // 
    // L=300pb-1, results for the new paper
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum3fb/H_LowMass_M12/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum3fb/H_LowMass_M20/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum3fb/H_LowMass_M30/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum3fb/H_LowMass_M40/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum3fb/H_LowMass_M12/b4_ttb_ttH_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum3fb/H_LowMass_M20/b4_ttb_ttH_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum3fb/H_LowMass_M30/b4_ttb_ttH_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum3fb/H_LowMass_M40/b4_ttb_ttH_A.root_table.CL.root ";
    // ------------------------------------------------------------------------------
    // ----------------------------------------- (k,k~) plane scan with 20 bins -----
    // ------------------------------------------------------------------------------
    // L=300fb-1
    //string myFname = "Rootuples/H_LowMass_1.5/H12/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass_1.5/H12/b4_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass_1.5/H20/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass_1.5/H20/b4_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass_1.5/H30/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass_1.5/H30/b4_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass_1.5/H40/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass_1.5/H40/b4_ttb_ttH_A.root_table.CL.root";
    // L=3000fb-1
    //string myFname = "Rootuples/H_LowMass/H12/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass/H12/b4_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass/H20/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass/H20/b4_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass/H30/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass/H30/b4_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass/H40/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H_LowMass/H40/b4_ttb_ttH_A.root_table.CL.root";
    // ------------------------------------------------------------------------------
    // older stuff ------------------------------------------------------------------
    //string myFname = "Rootuples/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/b4_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H10tt/b4_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/H125tt/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "Rootuples/case12_Exp_b4_Gunion_fullSM_ttX00.0_1111103.root_table.CL.root";
    //string myFname = "Rootuples/case12_Prob_TMVA_BDTG_ge3b_fullSM_ttX00.0_1111103.root_table.CL.root";
    // ------------------------------------------------------------------------------

    // ----------------------------------------------------------------------------------------------------
    // -------------------------------------------- New Papers: Low Mass Paper 2020 -----------------------
    // ----------------------------------------------------------------------------------------------------
    // L=3000pb-1, results for the new paper 2020
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum30fb/H_LowMass_M12/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum30fb/H_LowMass_M20/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum30fb/H_LowMass_M30/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum30fb/H_LowMass_M40/b2_ttb_ttH_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum30fb/H_LowMass_M12/b4_ttb_ttH_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum30fb/H_LowMass_M20/b4_ttb_ttH_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum30fb/H_LowMass_M30/b4_ttb_ttH_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/lum30fb/H_LowMass_M40/b4_ttb_ttH_A.root_table.CL.root ";
    // ----------------------------------------------------------------------------------------------------
    // -------------------------------------------- New Papers: Higgs Mass Paper 2021 ---------------------
    // ----------------------------------------------------------------------------------------------------
    // L=3000pb-1, results for the new paper 2021
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/Expb2_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/Expb4_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/b2_ttb_ttH_2bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/b4_ttb_ttH_2bins_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/cosExptheta23_3_1t2tb3H*cosExptheta3_4_1t2tb3H4LepN_2bins_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/sinExptheta123_1_1H2t3tb*sinExptheta23_3_1H2t3tb_2bins_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/sinExptheta123_1_1H2t3tb*sinExptheta3_4seq_1t2H3tb4bTbar_2bins_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/sinExptheta123_1_1t2tb3H*sinExptheta3_4seq_1t2tb3H4Wp_2bins_A.root_table.CL.root ";
    // ---best of all CL
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/Best_CL_from_Files_2bins.CL.root ";
    // ---best of all CL
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/ExpDeltaPhi_lab_ttb_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/sinExptheta123_1_1H2t3tb*sinExptheta23_3_1H2t3tb_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/cosExptheta23_3_1t2tb3H*cosExptheta3_4_1t2tb3H4LepN_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/myDeltaPHIpi_ExpPhiLepN_ExpPhiLepP_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/ExpDeltaTheta_ttb_lpln_A.root_table.CL.root";
    // ----------------------------------------------------------------------------------------------------

    // ------------------------------------------------------------------------------
    // Ellis distribution
    // ------------------------------------------------------------------------------
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/Ellis_ExpDelPhiLpLn_cos0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum30fb/Ellis_ExpDelPhiLpLn_noInt_cos0.0_8bins_A.root_table.CL.root";
    // ------------------------------------------------------------------------------
    // DelPhi distribution
    // ------------------------------------------------------------------------------
    //string myFname = "/Users/onofre/CL_Scan/Plots/SpinCorr_DelPhi_1_2/Numofeventsspin0plus0gevNev_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/SpinCorr_DelPhi_0_2/Numofeventsspin0plus0gevNev_A.root_table.CL.root";
    // ------------------------------------------------------------------------------
    // Expb2 and Expb4 distribution L=139fb-1
    // ------------------------------------------------------------------------------
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/Expb2_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/Expb4_ttb_ttH0.0_8bins_A.root_table.CL.root";
    // ------------------------------------------------------------------------------
    // Rodrigo
    // ------------------------------------------------------------------------------
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/sinExptheta123_1_1t2tb3HsinExptheta3_4seq_1t2tb3H4Wp0.0_2bins_A.root_table.CL.root";
    // ------------------------------------------------------------------------------
    // Esteban
    // ------------------------------------------------------------------------------
    //string myFname = "/Users/onofre/CL_Scan/Plots/Esteban/c1tthframespin0_0gevNev_A.root_table.CL.root";
    //
    // ----------------------------------------------------------------------------------------------------
    // -------------------------------------------- New Papers: Higgs Mass Paper 2021 ---------------------
    // ----------------------------------------------------------------------------------------------------
    // L=200pb-1, results for the new paper 2021  **** Asymmetries ****
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/Expb2_ttb_ttH0.0_1bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/Expb4_ttb_ttH0.0_1bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_A.root_table.CL.root ";
    // -- Choice for NULL Asymmetry limits
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Expb2_ttb_ttH0.0_1bins_A.root_table_AsymttH_NULL.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Expb2_ttb_ttH0.0_1bins_A.root_table_AsymFullBack_NULL.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Expb2_ttb_ttH0.0_1bins_A.root_table_AsymFullBack_SMHiggs_NULL.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Expb4_ttb_ttH0.0_1bins_A.root_table_AsymttH_NULL.CL.root";
    // -- Choice for best cases from scans ................................................................
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_12/Expb2_ttb_ttH0.0_1bins_-0.22_A_with_Expb4_ttb_ttH0.0_1bins_0.04_A.CL.root";                                                                             
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_13/Expb2_ttb_ttH0.0_1bins_-0.24_A_with_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_0.18_A.CL.root";                                          
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_14/Expb2_ttb_ttH0.0_1bins_-0.22_A_with_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_0.15_A.CL.root";                                  
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_23/Expb4_ttb_ttH0.0_1bins_-0.46_A_with_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_0.18_A.CL.root";                                          
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_24/Expb4_ttb_ttH0.0_1bins_-0.74_A_with_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_0.15_A.CL.root";                                   
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/ExpBest_34/sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_2bins_0.89_A_with_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_2bins_0.15_A.CL.root";  
    // -- Choice for best cases from scans
    //string myFname = "/Volumes/DISK_T5/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/12_34/Best_CL_from_Files_12_34.CL.root";  
    //string myFname = "/Volumes/DISK_T5/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/13_24/Best_CL_from_Files_13_24.CL.root";  
    //string myFname = "/Volumes/DISK_T5/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Histograms_Scan_100points_CERN/14_23/Best_CL_from_Files_14_23.CL.root";  
    // ....................................................................................................
    // ---best of all CL
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/Best_CL_from_Files.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_Asymmetries_Only/Best_CL_from_Files.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb_AngularDist_Only/Best_CL_from_Files.CL.root ";
    // L=200pb-1, results for the new paper 2021  **** Angular Distributions ****
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/Expb2_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/Expb4_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_8bins_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_8bins_A.root_table.CL.root ";
    // ---Ellis distribution
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/Ellis_ExpDelPhiLpLn_cos0.0_8bins_A.root_table.CL.root"; // 200fb-1
    // L=200pb-1, results for the new paper 2021  **** CPsign Angular Distributions ****
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/CPSign_Expb2_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/CPSign_Expb4_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/CPSign_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_8bins_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum200fb/CPSign_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_8bins_A.root_table.CL.root ";
    // L=3000pb-1, results for the new paper 2021  **** Includes also CPsign Angular Distributions ****
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/Expb2_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/Expb4_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum3000fb/CPSign_Expb2_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum3000fb/CPSign_Expb4_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum3000fb/CPSign_sinExptheta123_1_1H2t3tbsinExptheta23_3_1H2t3tb0.0_8bins_A.root_table.CL.root ";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum3000fb/CPSign_sinExptheta123_1_1H2t3tbsinExptheta3_4seq_1t2H3tb4bTbar0.0_8bins_A.root_table.CL.root ";
    // ---Ellis distribution
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum3000fb/Ellis_ExpDelPhiLpLn_cos0.0_lum30_8bins_A.root_table.CL.root"; // 3000fb-1
    // Dorival
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum3000fb/Dorival_ExpDelPhiLpLnTT_0.0_8bins_A.root_table.CL.root";
    // CP in ttH system distributions
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum3000fb/CPTTH_Expb2_ttb_ttH0.0_8bins_A.root_table.CL.root";
    //string myFname = "/Users/onofre/CL_Scan/Plots/H_125GeV_Paper2021/lum3000fb/CPTTH_Expb4_ttb_ttH0.0_8bins_A.root_table.CL.root";
    // ---------------------------------------------------------------------------------
    // $$$$ Dark Matter $$$$$$$$$$$      C A S E = ( 0 , 2 )      $$$$$$$$$$$$$$$$$$$$$$
    // $$$$ Dark Matter $$$$$$$$$$$      C A S E = ( 1 , 2 )      $$$$$$$$$$$$$$$$$$$$$$
    // ---------------------------------------------------------------------------------
    // 200 fb-1    
    //string myFname = "/Users/onofre/CL_Scan/Plots/Plots_case_02/Expb2_ttb0.0_s1_9bins_A.root_table.CL.root";                   
    //string myFname = "/Users/onofre/CL_Scan/Plots/Plots_case_02/Expb4_ttb0.0_s1_9bins_A.root_table.CL.root";                      
    //string myFname = "/Users/onofre/CL_Scan/Plots/Plots_case_02/absExpSpinCorr_DelPhiLpLn0.0_s1_9bins_A.root_table.CL.root";   
      string myFname = "/Users/onofre/CL_Scan/Plots/Plots_case_02/ExpSpinCorr_Ncosl2:SpinCorr_Ncosl10.0_s1_3bins_A.root_table.CL.root";   
    //string myFname = "/Users/onofre/CL_Scan/Plots/Plots_case_02/ExpSpinCorr_CosDpar0.0_s1_9bins_A.root_table.CL.root";       
    //string myFname = "/Users/onofre/CL_Scan/Plots/Plots_case_02/ExpSpinCorr_CosCosCpar0.0_s1_9bins_A.root_table.CL.root";     
    // ---------------------------------------------------------------------------------

      cout << " -------- Input File Name: " << myFname << endl;
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(myFname.c_str());
      if (!f || !f->IsOpen()) {
          f = new TFile(myFname.c_str());
      }
      f->GetObject("CL",tree);

   }
   Init(tree);
}

plotCL2D::~plotCL2D()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t plotCL2D::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t plotCL2D::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void plotCL2D::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Lumi", &Lumi, &b_Lumi);
   fChain->SetBranchAddress("CL_Obs", &CL_Obs, &b_CL_Obs);
   fChain->SetBranchAddress("CL_Exp", &CL_Exp, &b_CL_Exp);
   fChain->SetBranchAddress("CL_ExpM1sig", &CL_ExpM1sig, &b_CL_ExpM1sig);
   fChain->SetBranchAddress("CL_ExpP1sig", &CL_ExpP1sig, &b_CL_ExpP1sig);
   fChain->SetBranchAddress("k", &k, &b_k);
   fChain->SetBranchAddress("ktil", &ktil, &b_ktil);
   fChain->SetBranchAddress("LLR_null_Min", &LLR_null_Min, &b_LLR_null_Min);
   fChain->SetBranchAddress("LLR_null_Median", &LLR_null_Median, &b_LLR_null_Median);
   fChain->SetBranchAddress("LLR_null_Max", &LLR_null_Max, &b_LLR_null_Max);
   fChain->SetBranchAddress("LLRs_Min", &LLRs_Min, &b_LLRs_Min);
   fChain->SetBranchAddress("LLRs_Median", &LLRs_Median, &b_LLRs_Median);
   fChain->SetBranchAddress("LLRs_Max", &LLRs_Max, &b_LLRs_Max);
   Notify();
}

Bool_t plotCL2D::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void plotCL2D::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t plotCL2D::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef plotCL2D_cxx
