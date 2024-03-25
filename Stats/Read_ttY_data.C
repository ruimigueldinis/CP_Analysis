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

void Read_ttY_data()
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
   //  Define Input Variable
   //--------------------------------------------
   int   iChoice =   1;  
   // --Individual Cases------------
   // --DM Studies: My b2 observable  
   // --Dark Matter Studies---------
   //--------------------------------------------
   //           Define Input Variable 
   //--------------------------------------------
   string Fname;

   // -- (300/3000 fb-1)
      if ( iChoice == 1 ) Fname = "Expb2_Gunion_0.0_s0_9bins_A.rootmode02_table"; 
      if ( iChoice == 2 ) Fname = "Expb2_Gunion_Y_0.0_s0_9bins_A.rootmode02_table"; 
      if ( iChoice == 3 ) Fname = "Expb2_Gunion_KD_0.0_s0_9bins_A.rootmode02_table";

      if ( iChoice == 101 ) Fname = "Expb2_Gunion_0.0_s0_9bins_A.rootmode12_table"; 
      if ( iChoice == 102 ) Fname = "Expb2_Gunion_Y_0.0_s0_9bins_A.rootmode12_table"; 
      if ( iChoice == 103 ) Fname = "Expb2_Gunion_KD_0.0_s0_9bins_A.rootmode12_table";  
      

      if ( iChoice == 4 ) Fname = "Expb2_Gunion_1.0_s0_9bins_A.rootmode02_table"; 
      if ( iChoice == 5 ) Fname = "Expb2_Gunion_Y_1.0_s0_9bins_A.rootmode02_table"; 
      if ( iChoice == 6 ) Fname = "Expb2_Gunion_KD_1.0_s0_9bins_A.rootmode02_table";

      if ( iChoice == 104 ) Fname = "Expb2_Gunion_1.0_s0_9bins_A.rootmode12_table"; 
      if ( iChoice == 105 ) Fname = "Expb2_Gunion_Y_1.0_s0_9bins_A.rootmode12_table"; 
      if ( iChoice == 106 ) Fname = "Expb2_Gunion_KD_1.0_s0_9bins_A.rootmode12_table";


      if ( iChoice == 7 ) Fname = "Expb2_Gunion_10.0_s0_9bins_A.rootmode02_table"; 
      if ( iChoice == 8 ) Fname = "Expb2_Gunion_Y_10.0_s0_9bins_A.rootmode02_table"; 
      if ( iChoice == 9 ) Fname = "Expb2_Gunion_KD_10.0_s0_9bins_A.rootmode02_table";

      if ( iChoice == 107 ) Fname = "Expb2_Gunion_10.0_s0_9bins_A.rootmode12_table"; 
      if ( iChoice == 108 ) Fname = "Expb2_Gunion_Y_10.0_s0_9bins_A.rootmode12_table"; 
      if ( iChoice == 109 ) Fname = "Expb2_Gunion_KD_10.0_s0_9bins_A.rootmode12_table";


      if ( iChoice == 10 ) Fname = "Expb2_Gunion_100.0_s0_9bins_A.rootmode02_table"; 
      if ( iChoice == 11 ) Fname = "Expb2_Gunion_Y_100.0_s0_9bins_A.rootmode02_table"; 
      if ( iChoice == 12 ) Fname = "Expb2_Gunion_KD_100.0_s0_9bins_A.rootmode02_table";

      if ( iChoice == 110 ) Fname = "Expb2_Gunion_100.0_s0_9bins_A.rootmode12_table"; 
      if ( iChoice == 111 ) Fname = "Expb2_Gunion_Y_100.0_s0_9bins_A.rootmode12_table"; 
      if ( iChoice == 112 ) Fname = "Expb2_Gunion_KD_100.0_s0_9bins_A.rootmode12_table";  


      if ( iChoice == 13 ) Fname = "Expb2_Gunion_125.0_s0_9bins_A.rootmode02_table"; 
      if ( iChoice == 14 ) Fname = "Expb2_Gunion_Y_125.0_s0_9bins_A.rootmode02_table"; 
      if ( iChoice == 15 ) Fname = "Expb2_Gunion_KD_125.0_s0_9bins_A.rootmode02_table";

      if ( iChoice == 113 ) Fname = "Expb2_Gunion_125.0_s0_9bins_A.rootmode12_table"; 
      if ( iChoice == 114 ) Fname = "Expb2_Gunion_Y_125.0_s0_9bins_A.rootmode12_table"; 
      if ( iChoice == 115 ) Fname = "Expb2_Gunion_KD_125.0_s0_9bins_A.rootmode12_table";    

   //--------------------------------------------
   //           Define Input File Names 
   //--------------------------------------------
   std::vector<string> inpFile;
   std::vector<string> outFile;
        // -- Choice for Dark Matter Studies
        // Spin 0: Case (0,2) and (1,2)            
            if ( iChoice >= 1 && iChoice <= 115 ) inpFile.push_back("/Users/ruimiguelsilva/Desktop/CL_M12_300fb/Tables/"+Fname+".txt");            
        //  if ( iChoice >= 101 && iChoice <= 115 ) inpFile.push_back("MYDIRECTORY/Tables_case_12/"+Fname+".txt");            
        // ----------------------------------------------------------------------------------------------------
            cout << " " << endl;
            cout << " ###################################################################################....." << endl;
            cout << " ####### Input Variable Name: " << Fname << "  from Input File: " << inpFile[0] << endl;
   //--------------------------------------------
   //           Define Output File Names 
   //--------------------------------------------
        // -- Choice for Dark Matter Studies
          if ( iChoice >= 1 && iChoice <= 115 ) outFile.push_back("/Users/ruimiguelsilva/Desktop/CL_M12_300fb/Stats/"+Fname+".CL");
        //  if ( iChoice >= 101 && iChoice <= 115 ) outFile.push_back("/MYDIRECTORY/Plots/"+Fname+".CL");             
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
}
