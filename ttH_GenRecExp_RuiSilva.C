#include <iostream>
#include <cmath>

#include "Rtypes.h"
#include "AtlasStyle.C"
//#include "AtlasLabels.C"
#include "myMergeAll.C"

#include "utils.h"

void doTTree(int id,                            // Type of distribution (see below)
             TFile* ttH_GenRec,                 // Root input file names
             TFile* OutPutFile,                 // Output file to store histograms
             string myLog,                      // Set log scale for plots
             string TreeName,                   // TTree name
             string myCut,                      // Cut applied to distributions
             string name,                       // TTree variable name to be represented
             string Recname,                    // TTree variable name to be represented
             int nb, double xLow, double xHigh, // Define histo bins, x-low and x-high
             string xtitle, string ytitle);

void doTTree2D(int id,                                          // Type of distribution (see below)
               TFile* ttH_GenRec,                               // Root input file names
               TFile* OutPutFile,                               // Output file to store histograms
               string myLog,                                    // Set log scale for plots               
               string TreeName,                                 // TTree name
               string myCut,                                    // Cut applied to distributions
               string nameX,                                    // TTree variable name to be represented
               string nameY,                                    // TTree variable name to be represented
               int nbX, double LowX, double HighX,              // Define histo bins, x-low and x-high
               int nbY, double LowY, double HighY,              // Define histo bins, x-low and x-high
               string xtitle, string ytitle, string dTitle);

void doProb_2D(int id,                                  // Type of distribution (see below)
               TFile* ttH_GenRec,                       // Root input file names
               TFile* OutPutFile,                       // Output file to store histograms
               string myLog,                            // Set log scale for plots               
               string TreeName,                         // TTree name
               string myCut,                            // Cut applied to distributions
               string nameX,                            // TTree variable name to be represented
               string nameRecExp,                       // Define if Rec or Exp is to be used
               int nbX, double LowX, double HighX,      // Define histo bins, x-low and x-high
               int nbY, double LowY, double HighY,      // Define histo bins, x-low and x-high
               string xtitle, string ytitle);




// #############################################################################
void ttH_GenRecExp() {
// #############################################################################

    //
    //_____________________________________________________________
    // ____Define File and Tree to be Read_________________________
    string myTTree  = "WithCuts";         // define TTree to be read
    string myRecExp = "Exp";              // define if rec. with (Rec) or without (Exp) truth match
    string myInput = "input";
    //_____________________________________________________________
    // ____Is it Necessary to Delete Input Files?__________________
    bool cleanInp = true;
    //_____________________________________________________________
    // ____Set Logfile for plots___________________________________
    string myLogFlag;   // Order: LogX, LogY, LogZ (see below)
    //_____________________________________________________________
    // ____Define Selection Criteria_______________________________
      //string mySel = "";
        string mySel = " ExpProbTotal > 0. && ExpProbTTbar > 0.0 && ExpProbHiggs > 0.e-6";
      //string mySel = " ExpProbTotal > 0. && ExpProbTTbar > 0.0 && ExpProbHiggs > 0.004";
    //_____________________________________________________________
    // ____Probability limits______________________________________
    double ProbHiggs_Max = 4.0e-3;
    double ProbTTbar_Max = 1.0e-18;
    double ProbTotal_Max = 2.0e-21;
    //_____________________________________________________________
      
    //_____________________________________________________________
    // ____Input File______________________________________________
    if ( cleanInp ){
        gSystem->Exec("rm Figs/ttH_GenRecExp_Input.root");
        TChain ntuSNLO(myTTree.c_str());
        // define input files
        ntuSNLO.Add(myInput.c_str());
        // define output file copy
        ntuSNLO.Merge("Figs/ttH_GenRecExp_Input.root");        
    }

    //_____________________________________________________________
    // ____Output ttH Histograms___________________________________
    gSystem->Exec("rm Figs/ttH_GenRecExp_Output.root");
    TFile* outFile = new TFile("Figs/ttH_GenRecExp_Output.root", "RECREATE");
    outFile->cd();
    
    //_____________________________________________________________
    // ____Assign__Files___________________________________________
    TFile* ttH_GenRec   = TFile::Open("Figs/ttH_GenRecExp_Input.root");

    //_____________________________________________________________
    // ____Print__Histos from TTree________________________________
    //_____________________________________________________________

    // Initialize variable name string
    string nameVar;
    int nDis;
    string xTit;
    string yTit   = "Events";
    string yTitM  = "#frac{1}{N} #frac{dN}{dM}";
    string yTitPt = "#frac{1}{N} #frac{dN}{dP_{T}}";
    string yTitM2D   = "#frac{d^{2}N}{N(dM)^{2}}";
    string yTitPt2D  = "#frac{d^{2}N}{N(dP_{T})^{2}}";
    string yTitEta2D  = "#frac{d^{2}N}{N(d#eta)^{2}}";
    string yTitProb2D  = "#frac{d^{2}N}{N(dP)^{2}";
    string WwoTruth  = " w ";
    if ( myRecExp == "Exp" )  WwoTruth = " w/o ";

    // ===================================================================
    // ===================================================================
    //                  GENERATOR LEVEL DISTRIBUTIONS
    // ===================================================================
    // ===================================================================

    // -------------------------------------------------------------------
    // loop over distributions
    // -------------------------------------------------------------------
    // define binning for m(t,t~) and m(w+,mw-)
    // w+,w-
    int nbh;
    double hLow;
    double hHig;
    int     nbw =  8;
    double wLow = 76.4;
    double wHig = 84.4;
    // t,t~
    int     nbt =   6 ;
    double tLow = 170.;
    double tHig = 176.;
    // h
    if ( myRecExp == "Gen" ){
        int     nbh = 100;
        double hLow = 124.9;
        double hHig = 125.1;
    } else {
        int     nbh =   50;
        double hLow =   0.;
        double hHig = 400.;
    }
    // ========= 1D distributions =======
    // ----------------------------------
    // Distributions at Gen level
    // ----------------------------------
    myLogFlag = "010";    
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mTopQ",              myRecExp+"mTopQ"                  , nbt,   tLow,    tHig, "m_{t} [GeV]"                , yTitM);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtTopQ",             myRecExp+"PtTopQ"                 , 140,    0.0,   700.0, "P_{T}(t) [GeV]"             , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mTbarQ",             myRecExp+"mTbarQ"                 , nbt,   tLow,    tHig, "m_{#bar{t}} [GeV]"          , yTitM);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtTbarQ",            myRecExp+"PtTbarQ"                , 140,    0.0,   700.0, "P_{T}(#bar{t}) [GeV]"       , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mTTbar",             myRecExp+"mTTbar"                 , 120,  350.0,  1550.0, "m_{t#bar{t}} [GeV]"         , yTitM);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtTTbar",            myRecExp+"PtTTbar"                ,  80,    0.0,   800.0, "P_{T}(t#bar{t}) [GeV]"      , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mHiggs",             myRecExp+"mHiggs"                 , nbh,   hLow,    hHig, "m_{H} [GeV]"                , yTitM);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtHiggs",            myRecExp+"PtHiggs"                , 100,    0.0,  1000.0, "P_{T}(H) [GeV]"             , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mWp",                myRecExp+"mWp"                    , nbw,   wLow,    wHig, "m_{W+} [GeV]"               , yTitM);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtWp",               myRecExp+"PtWp"                   , 140,    0.0,   700.0, "P_{T}(W+) [GeV] "           , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mWn",                myRecExp+"mWn"                    , nbw,   wLow,    wHig, "m_{W-} [GeV] "              , yTitM);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtWn",               myRecExp+"PtWn"                   , 140,    0.0,   700.0, "P_{T}(W-) [GeV] "           , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtNeu",              myRecExp+"PtNeu"                  ,  50,    0.0,   400.0, "P_{T}(#nu_{l}) [GeV] "      , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtNeubar",           myRecExp+"PtNeubar"               ,  50,    0.0,   400.0, "P_{T}(#bar{#nu}_{l}) [GeV]" , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mBestHiggs",         myRecExp+"mBestHiggs"             , nbh,   hLow,    hHig, "best m (H) "              , yTitM);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtBestHiggs",        myRecExp+"PtBestHiggs"            , 140,    0.0,   700.0, "best Pt(H) "              , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtBestHiggsJ1",      myRecExp+"PtBestHiggsJ1"          , 140,    0.0,   700.0, "best Pt(H) Jet1"          , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtBestHiggsJ2",      myRecExp+"PtBestHiggsJ2"          , 140,    0.0,   700.0, "best Pt(H) Jet2"          , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mHiggsClo",          myRecExp+"mHiggsClo"              , nbh,   hLow,    hHig, "Closest m (H) "           , yTitM);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtHiggsClo",         myRecExp+"PtHiggsClo"             , 140,    0.0,   700.0, "Closest Pt(H) "           , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtHcloJ1",           myRecExp+"PtHcloJ1"               , 140,    0.0,   700.0, "Closest Pt(H) Jet1"       , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtHcloJ2",           myRecExp+"PtHcloJ2"               , 140,    0.0,   700.0, "Closest Pt(H) Jet2"       , yTitPt);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_bT_bbarTbar", myRecExp+"DeltaR_bT_bbarTbar"     , 100,    0.0,   10.0, "DeltaR_bT_bbarTbar"      , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_bT_bH",       myRecExp+"DeltaR_bT_bH"           , 100,    0.0,   10.0, "DeltaR_bT_bH"            , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_bT_bbarH",    myRecExp+"DeltaR_bT_bbarH"        , 100,    0.0,   10.0, "DeltaR_bT_bbarH"         , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_bbarTbar_bH", myRecExp+"DeltaR_bbarTbar_bH"     , 100,    0.0,   10.0, "DeltaR_bbarTbar_bH"      , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_bbarTbar_bbarH", myRecExp+"DeltaR_bbarTbar_bbarH"  , 100,    0.0,   10.0, "DeltaR_bbarTbar_bbarH"   , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_bH_bbarH",    myRecExp+"DeltaR_bH_bbarH"        , 100,    0.0,   10.0, "DeltaR_bH_bbarH"         , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_lp_bT",       myRecExp+"DeltaR_lp_bT"           , 100,    0.0,   10.0, "DeltaR_lp_bT"            , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_lp_bbarTbar", myRecExp+"DeltaR_lp_bbarTbar"     , 100,    0.0,   10.0, "DeltaR_lp_bbarTbar"      , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_lp_bH",       myRecExp+"DeltaR_lp_bH"           , 100,    0.0,   10.0, "DeltaR_lp_bH"            , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_lp_bbarH",    myRecExp+"DeltaR_lp_bbarH"        , 100,    0.0,   10.0, "DeltaR_lp_bbarH"         , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_ln_bT",       myRecExp+"DeltaR_ln_bT"           , 100,    0.0,   10.0, "DeltaR_ln_bT"            , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_ln_bbarTbar", myRecExp+"DeltaR_ln_bbarTbar"     , 100,    0.0,   10.0, "DeltaR_ln_bbarTbar"      , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_ln_bH",       myRecExp+"DeltaR_ln_bH"           , 100,    0.0,   10.0, "DeltaR_ln_bH"            , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "DeltaR_ln_bbarH",    myRecExp+"DeltaR_ln_bbarH"        , 100,    0.0,   10.0, "DeltaR_ln_bbarH"         , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "Mass_lp_bT",         myRecExp+"Mass_lp_bT"             , 100,    0.0, 1000.0, "Mass_lp_bT"              , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "Mass_lp_bbarTbar",   myRecExp+"Mass_lp_bbarTbar"       , 100,    0.0, 1000.0, "Mass_lp_bbarTbar"        , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "Mass_lp_bH",         myRecExp+"Mass_lp_bH"             , 100,    0.0, 1000.0, "Mass_lp_bH"              , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "Mass_lp_bbarH",      myRecExp+"Mass_lp_bbarH"          , 100,    0.0, 1000.0, "Mass_lp_bbarH"           , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "Mass_ln_bT",         myRecExp+"Mass_ln_bT"             , 100,    0.0, 1000.0, "Mass_ln_bT"              , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "Mass_ln_bbarTbar",   myRecExp+"Mass_ln_bbarTbar"       , 100,    0.0, 1000.0, "Mass_ln_bbarTbar"        , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "Mass_ln_bH",         myRecExp+"Mass_ln_bH"             , 100,    0.0, 1000.0, "Mass_ln_bH"              , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "Mass_ln_bbarH",      myRecExp+"Mass_ln_bbarH"          , 100,    0.0, 1000.0, "Mass_ln_bbarH"           , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "RecProbTotal", "ExpProbTotal" ,                  100,    0.0, ProbTotal_Max, "ProbTotal" , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "RecProbTTbar", "ExpProbTTbar" ,                  100,    0.0, ProbTTbar_Max, "ProbTTbar" , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "RecProbHiggs", "ExpProbHiggs" ,                  100,    0.0, ProbHiggs_Max, "ProbHiggs" , yTit);
    doTTree( 3, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "RecProbTotal_DeltaPtM", "ExpProbTotal_DeltaPtM", 100,    0.0, 200.   , "ProbTotal_DeltaPtM" , yTit);
    // ========= 2D distributions =======
    // w+,w-
         nbw =  8;
        wLow = 76.4;
        wHig = 84.4;
    // t,t~
         nbt =   6 ;
        tLow = 170.;
        tHig = 176.;
    //
    myLogFlag = "000";
    // mass 
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mWp"   , "mTopQ"  , nbw, wLow, wHig,   nbt, tLow, tHig,  "m(W+)" , "m(t) " , yTitM2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mTopQ" , "mTbarQ" , nbt, tLow, tHig,   nbt, tLow, tHig,  "m(t)"  , "m(t~)" , yTitM2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "mWn"   , "mTbarQ" , nbw, wLow, wHig,   nbt, tLow, tHig,  "m(W-)" , "m(t~)" , yTitM2D);
    // pT distr1b
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtNeu"    , myRecExp+"PtNeu"    , 100,  0.0, 100.,  100,  0.0, 100.,  "(NLO+Shower) P_{T}(#nu_{l}) [GeV]"        , "(rec."+WwoTruth+"truth match) P_{T}(#nu_{l}) [GeV]" ,yTitPt2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtNeubar" , myRecExp+"PtNeubar" , 100,  0.0, 100.,  100,  0.0, 100.,  "(NLO+Shower) P_{T}(#bar{#nu}_{l}) [GeV]"  , "(rec."+WwoTruth+"truth match) P_{T}(#bar{#nu}_{l}) [GeV]" ,yTitPt2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtWp"     , myRecExp+"PtWp"     , 100,  0.0, 400.,  100,  0.0, 400.,  "(NLO+Shower) P_{T}(W+) [GeV]"             , "(rec."+WwoTruth+"truth match) P_{T}(W+) [GeV]" ,yTitPt2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtWn"     , myRecExp+"PtWn"     , 100,  0.0, 400.,  100,  0.0, 400.,  "(NLO+Shower) P_{T}(W-) [GeV]"             , "(rec."+WwoTruth+"truth match) P_{T}(W-) [GeV]" ,yTitPt2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtTopQ"   , myRecExp+"PtTopQ"   , 100,  0.0, 400.,  100,  0.0, 400.,  "(NLO+Shower) P_{T}(t) [GeV]"              , "(rec."+WwoTruth+"truth match) P_{T}(t) [GeV]" ,yTitPt2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtTTbar"  , myRecExp+"PtTTbar"  , 100,  0.0, 400.,  100,  0.0, 400.,  "(NLO+Shower) P_{T}(t#bar{t}) [GeV]"       , "(rec."+WwoTruth+"truth match) P_{T}(t#bar{t}) [GeV]" ,yTitPt2D); 
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtTbarQ"  , myRecExp+"PtTbarQ"  , 100,  0.0, 400.,  100,  0.0, 400.,  "(NLO+Shower) P_{T}(#bar{t}) [GeV]"        , "(rec."+WwoTruth+"truth match) P_{T}(#bar{t}) [GeV]" ,yTitPt2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "PtHiggs"  , myRecExp+"PtHiggs"  , 100,  0.0, 400.,  100,  0.0, 400.,  "(NLO+Shower) P_{T}(h) [GeV]"              , "(rec."+WwoTruth+"truth match) P_{T}(h) [GeV]"  ,yTitPt2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, "EtaHiggs", myRecExp+"EtaHiggs"  , 100, -5.0,  5.0,  100, -5.0,  5.0,  "(NLO+Shower) #\eta(h)"                    , "(rec."+WwoTruth+"truth match) #\eta(h)"  ,yTitEta2D);

    // Probabilities
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, myRecExp+"ProbTTbar", myRecExp+"mTopQ",  100, 0., ProbTTbar_Max,  nbt, tLow, tHig, "ProbTTbar", "m(t) " , yTitProb2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, myRecExp+"ProbTTbar", myRecExp+"mTbarQ", 100, 0., ProbTTbar_Max,  nbt, tLow, tHig, "ProbTTbar", "m(t~)" , yTitProb2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, myRecExp+"ProbTTbar", myRecExp+"mWp",    100, 0., ProbTTbar_Max,  nbw, wLow, wHig, "ProbTTbar", "m(W+)" , yTitProb2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, myRecExp+"ProbTTbar", myRecExp+"mWn",    100, 0., ProbTTbar_Max,  nbw, wLow, wHig, "ProbTTbar", "m(W-)" , yTitProb2D);    
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, myRecExp+"ProbHiggs", myRecExp+"ProbTTbar", 100, 0., ProbHiggs_Max, 100, 0., ProbTTbar_Max, "ProbHiggs" , "ProbTTbar" , yTitProb2D);
    doTTree2D( 13, ttH_GenRec, outFile,  myLogFlag, myTTree, mySel, myRecExp+"ProbHiggs", myRecExp+"ProbTotal", 100, 0., ProbHiggs_Max, 100, 0., ProbTotal_Max, "ProbHiggs" , "ProbTotal" , yTitProb2D);
    doTTree2D( 13, ttH_GenRec, outFile,      "111", myTTree, mySel, myRecExp+"ProbTTbar", myRecExp+"ProbTotal", 100, 0., ProbTTbar_Max, 100, 0., ProbTotal_Max, "ProbTTbar" , "ProbTotal" , yTitProb2D);

    // Chi2 distributions (check values from fits)
    // y-axis: chi2 distribution
       int nbc  = 300 ;
    double cLow =   0.;
    double cHig =  30.;
    //
    myLogFlag = "000";
    doProb_2D( 13, ttH_GenRec, outFile, myLogFlag, myTTree, mySel, "ProbHiggs", myRecExp , 100, 0., ProbHiggs_Max, nbc, cLow, cHig, "ProbHiggs",  "Chi2/ndf"  );
    doProb_2D( 13, ttH_GenRec, outFile, myLogFlag, myTTree, mySel, "ProbTTbar", myRecExp , 100, 0., ProbTTbar_Max, nbc, cLow, cHig, "ProbTTbar",  "Chi2/ndf"  );
    
}

// #############################################################################
void doTTree(int id,                            // Type of distribution (see below)
             TFile* ttH_GenRec,                 // Root input file names
             TFile* OutPutFile,                 // Output file to store histograms
             string myLog,                      // Set log scale for plots
             string TreeName,                   // TTree name
             string myCut,                      // Cut applied to distributions
             string name,                       // TTree variable name to be represented
             string Recname,                    // TTree variable name to be represented
             int nb, double xLow, double xHigh, // Define histo bins, x-low and x-high
             string xtitle, string ytitle)      // Titles for X-axis and Y-axis
// #############################################################################
{
    // --------------------------------
    // define output file name string
    // --------------------------------
    string out="Figs/"+name+Recname+".pdf";
    // --------------------------------
    
    cout.precision(6);
    
    gROOT->Reset();
    gROOT->SetStyle("ATLAS");
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaperSize(20,24);
    
    // create canvas
    // c1 = new TCanvas("cf1","Canvas",50,50,750,550);
    //TCanvas *c1 = new TCanvas( "c1",  "c1", 720, 750);
    TCanvas *c1 = new TCanvas( "c1",  "c1", 750, 500);
    c1->Divide(1,2,0.1,0);
    
    //Go to First Pad
    c1->cd(1);
    gPad->SetPad(0.0,0.30,0.95,0.95);
    gPad->SetRightMargin(0.06);
    gPad->SetTopMargin(0.06);
    // check if log wanted
    if ( myLog == "000" ) {c1->SetLogx(0); c1->SetLogy(0); c1->SetLogz(0);} 
    if ( myLog == "001" ) {c1->SetLogx(0); c1->SetLogy(0); c1->SetLogz(1);} 
    if ( myLog == "010" ) {c1->SetLogx(0); c1->SetLogy(1); c1->SetLogz(0);} 
    if ( myLog == "011" ) {c1->SetLogx(0); c1->SetLogy(1); c1->SetLogz(1);} 
    if ( myLog == "100" ) {c1->SetLogx(1); c1->SetLogy(0); c1->SetLogz(0);} 
    if ( myLog == "101" ) {c1->SetLogx(1); c1->SetLogy(0); c1->SetLogz(1);} 
    if ( myLog == "110" ) {c1->SetLogx(1); c1->SetLogy(1); c1->SetLogz(0);} 
    if ( myLog == "111" ) {c1->SetLogx(1); c1->SetLogy(1); c1->SetLogz(1);}     
    
    //___Get TTree from Files_____________
    TTree* ttH_GenRecTree = (TTree*) ttH_GenRec->Get(TreeName.c_str());

    //___Get TTree from Files_____________
    TH1D *httH_Gen = new TH1D("httH_Gen",    name.c_str(), nb, xLow, xHigh);
    TH1D *httH_Rec = new TH1D("httH_Rec", Recname.c_str(), nb, xLow, xHigh);
    httH_Gen->Sumw2();    httH_Rec->Sumw2();
    
    //___Loop over TTree events___________
    // ttH_Gen
    ttH_GenRecTree->Draw((name+">>httH_Gen").c_str()  ,myCut.c_str());
    // ttH_Rec
    ttH_GenRecTree->Draw((Recname+">>httH_Rec").c_str()  ,myCut.c_str());
    
    //___Get_Event_Numbers________________
    double n_ttH_Gen  = httH_Gen->Integral();
    double n_ttH_Rec  = httH_Rec->Integral();
    
    cout << "===============================" << endl;
    cout << "ttH_Gen      = " << n_ttH_Gen << endl;
    cout << "ttH_Rec(Exp) = " << n_ttH_Rec << endl;
    cout << "===============================" << endl;
    
    // normalize histograms
    if ( httH_Gen->Integral() != 0 ) httH_Gen->Scale(1./httH_Gen->Integral());
    if ( httH_Rec->Integral() != 0 ) httH_Rec->Scale(1./httH_Rec->Integral());

    
    //-------------------------------------------------------
    // Set colors for ttH_Gen and ttH_Rec
    //-------------------------------------------------------
    httH_Gen->SetLineWidth(2); //  ttH NLO line width
    httH_Rec->SetLineWidth(3); //  ttH  LO line width
    if ( id < 10) {
        httH_Gen->SetLineColor(kOrange+1);
        httH_Gen->SetFillColor(kOrange+1);
        httH_Rec->SetLineColor(kBlue);
    } else if ( id < 20 ){
        httH_Gen->SetLineColor(kMagenta-3);
        httH_Gen->SetFillColor(kMagenta-3);
        httH_Rec->SetLineColor(kCyan-3);
    } else if ( id < 30 ){
        httH_Gen->SetLineColor(kYellow-3);
        httH_Gen->SetFillColor(kYellow-3);
        httH_Rec->SetLineColor(kGreen-3);
    } else if ( id < 40 ){
        httH_Gen->SetLineColor(kRed-7);
        httH_Gen->SetFillColor(kRed-7);
        httH_Rec->SetLineColor(kBlue-7);
    } else if ( id < 50 ){
        httH_Gen->SetLineColor(kMagenta-6);
        httH_Gen->SetFillColor(kMagenta-6);
        httH_Rec->SetLineColor(kCyan-6);
    } else if ( id < 60 ){
        httH_Gen->SetLineColor(kYellow-6);
        httH_Gen->SetFillColor(kYellow-6);
        httH_Rec->SetLineColor(kGreen-6);
    } else if ( id < 70 ){
        httH_Gen->SetLineColor(kGreen-8);
        httH_Gen->SetFillColor(kGreen-8);
        httH_Rec->SetLineColor(kCyan+3);
    }

    
    //-------------------------------------------------------
    // Draw ttH_LO and ttH_GenRec
    //-------------------------------------------------------
    // set Y-axis title
    httH_Gen->GetYaxis()->SetTitle(ytitle.c_str());
    httH_Gen->GetYaxis()->SetTitleOffset(0.75);
    httH_Gen->GetYaxis()->SetLabelSize(0.05);
    httH_Gen->GetYaxis()->SetTitleSize(0.06);
    httH_Gen->GetYaxis()->SetNdivisions(6);
    // draw the plot
    httH_Gen->Draw("hist");
    httH_Rec->Draw("same hist");
    //httH_Rec->Draw("same e1");

    //-------------------------------------------------------
    // printout information
    //-------------------------------------------------------
    //myText(     0.135, 0.84, 1, "Preliminary",        0.050);
    myText(     0.135, 0.88, 1, (char*) "LHC, #sqrt{s} = 14 TeV",   0.06);
    myText(     0.135, 0.82, 1, (char*) "MadGraph5_aMC@NLO",        0.06);
    if ( id < 10) {
        myText(      0.50, 0.82,   kOrange+1, (char*) "t#bar{t}Y (NLO+Shower)", 0.06);
        myText(      0.75, 0.82,   kBlack   , (char*) "m_{Y}=0 GeV", 0.06);
        myText(      0.50, 0.75,   kBlue    , (char*) "t#bar{t}Y (Rec.)",     0.06);
    } else if ( id < 20 ){
        myText(      0.50, 0.82, kMagenta-3 , (char*) "t#bar{t}Y (NLO+Shower)",   0.06);
        myText(      0.75, 0.82,   kBlack   , (char*) "m_{Y}=0 GeV", 0.06);
        myText(      0.50, 0.75,    kCyan-3 , (char*) "t#bar{t}Y (Rec.)",  0.06);
    } else if ( id < 30 ){
        myText(      0.50, 0.82, kYellow-3  , (char*) "t#bar{t}Y (NLO+Shower)",    0.06);
        myText(      0.75, 0.82,   kBlack   , (char*) "m_{Y}=0 GeV", 0.06);
        myText(      0.50, 0.75,  kGreen-3  , (char*) "t#bar{t}Y (Rec.)",   0.06);
    } else if ( id < 40 ){
        myText(      0.50, 0.82,   kOrange+1-7, (char*) "t#bar{t}Y (NLO+Shower)",0.06);
        myText(      0.75, 0.82,   kBlack     , (char*) "m_{Y}=0 GeV", 0.06);
        myText(      0.50, 0.75,  kBlue-7     , (char*) "t#bar{t}Y (Rec.)",    0.06);
    } else if ( id < 50 ){
        myText(      0.50, 0.82, kMagenta-6, (char*) "t#bar{t}Y (NLO+Shower)",   0.06);
        myText(      0.75, 0.82,   kBlack  , (char*) "m_{Y}=0 GeV", 0.06);
        myText(      0.50, 0.75,    kCyan-6, (char*) "t#bar{t}Y (Rec.)",  0.06);
    } else if ( id < 60 ){
        myText(      0.50, 0.82, kYellow-6, (char*) "t#bar{t}Y (NLO+Shower)",    0.06);
        myText(      0.75, 0.82,   kBlack , (char*) "m_{Y}=0 GeV", 0.06);
        myText(      0.50, 0.75,  kGreen-6, (char*) "t#bar{t}Y (Rec.)",   0.06);
    } else if ( id < 70 ){
        myText(      0.50, 0.82,  kGreen-8, (char*) "t#bar{t}Y (NLO+Shower)",    0.06);
        myText(      0.75, 0.82,   kBlack , (char*) "m_{Y}=0 GeV", 0.06);
        myText(      0.50, 0.75,  kCyan+3 , (char*) "t#bar{t}Y (Rec.)",   0.06);
    }

    
    // Set minimum and maximum
    httH_Gen->SetMaximum(1.8*httH_Gen->GetMaximum());
    httH_Gen->SetMinimum(0.00001);
    
    // ====== Boost v4 Directly to v3 from LAB =======
    //  0: 1=~t, 2= t, 3=H (Signal=kBlue,    ttH_Gen=kOrange+1)
    // 10: 1= t, 2=~t, 3=H (Signal=kCyan-3,  ttH_Gen=kMagenta-3)
    // 20: 1= H, 2=~t, 3=t (Signal=kGreen-3, ttH_Gen=kYellow-3)
    // ====== Boost v4 STEP by STEP to v3 ============
    // 30: 1=~t, 2= t, 3=H (Signal=kBlue-7,  ttH_Gen=-7)
    // 40: 1= t, 2=~t, 3=H (Signal=kCyan-6,  ttH_Gen=kMagenta-6)
    // 50: 1= H, 2=~t, 3=t (Signal=kGreen-6, ttH_Gen=kYellow-6)
    if (id==0 || id==10 || id==20 || id==30 || id==40 || id==50  )   myText(     0.135 , 0.76, 1, (char*) "dilepton channel (l+l-)",      0.05);
    if (id==1 || id==11 || id==21 || id==31 || id==41 || id==51  )   myText(     0.135 , 0.76, 1, (char*) "dilepton channel (e+e-)",      0.05);
    if (id==2 || id==12 || id==22 || id==32 || id==42 || id==52  )   myText(     0.135 , 0.76, 1, (char*) "dilepton channel (#mu+#mu-)",  0.05);
    if (id==3 || id==13 || id==23 || id==33 || id==43 || id==53  )   myText(     0.135 , 0.76, 1, (char*) "dilepton channel (e+#mu)",     0.05);

    // -- Draw in the 2nd Canvas
    c1->cd(2);
    gPad->SetPad(0.0,0.0,0.95,0.30);
    gPad->SetLogy(0);
    gPad->SetLogx(0);
    gPad->SetRightMargin(0.06);
    gStyle->SetPadBottomMargin(0.3);
    // clone data histogram and divide by MC
    TH1D *ratio = static_cast<TH1D*>(httH_Gen->Clone("ratio"));
    ratio->Divide(httH_Rec);
    ratio->SetMinimum(-1.0);
    ratio->SetMaximum( 2.5);

    // set Y-axis title
    string myYtit = "Gen./Rec.";
    ratio->SetYTitle(myYtit.c_str());
    ratio->GetYaxis()->SetTitleOffset(0.3);
    ratio->GetYaxis()->SetLabelSize(0.06);
    ratio->GetYaxis()->SetTitleSize(0.14);
    ratio->GetYaxis()->SetNdivisions(6);
    // set X-axis title attributes
    ratio->GetXaxis()->SetTitle(xtitle.c_str());
    ratio->GetXaxis()->SetLabelSize(0.06);
    ratio->GetXaxis()->SetTitleSize(0.14);
    ratio->GetXaxis()->SetTitleOffset(0.7);

    // draw the plot
    ratio->Draw("E");
    
    TLine *l1 = new TLine(ratio->GetXaxis()->GetXmin(),1.,ratio->GetXaxis()->GetXmax(),1.);
    l1->Draw("same");
    
    // ----------------------------------------------------------
    // close file
    // ----------------------------------------------------------
    c1->Print(out.c_str());
    
    
    // ----------------------------------------------------------
    // Save histos with different names (extensions _LO and _NLO)
    // ----------------------------------------------------------
    OutPutFile->cd();
    httH_Rec->Write(Recname.c_str());
    httH_Gen->Write(name.c_str());
    
    // delete histograms
    delete httH_Gen;
    delete httH_Rec;
    
    // delete canvas
    delete c1;
    
}


// #############################################################################
void doTTree2D(int id,                                          // Type of distribution (see below)
               TFile* ttH_GenRec,                               // Root input file names
               TFile* OutPutFile,                               // Output file to store histograms
               string myLog,                                    // Set log scale for plots               
               string TreeName,                                 // TTree name
               string myCut,                                    // Cut applied to distributions
               string nameX,                                    // TTree variable name to be represented
               string nameY,                                    // TTree variable name to be represented
               int nbX, double LowX, double HighX,              // Define histo bins, x-low and x-high
               int nbY, double LowY, double HighY,              // Define histo bins, x-low and x-high
               string xtitle, string ytitle, string dTitle)     // Titles for X-axis, Y-axis and density plot
// #############################################################################
{
    // --------------------------------
    // define output file name string
    // --------------------------------
    string name=nameX+"vs"+nameY;
    string out="Figs/"+name+".pdf";
    // --------------------------------
    
    cout.precision(6);
    
    gROOT->Reset();
    gROOT->SetStyle("ATLAS");
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaperSize(20,20);
    
    // create canvas
    TCanvas *c1 = new TCanvas("cf1","Canvas",50,50,550,550);
    
    //Go to First Pad
    c1->cd(1);
    gPad->SetPad(0.0,0.0,1.0,1.0);
    gPad->SetTopMargin(0.10);
    gPad->SetBottomMargin(0.10);
    gPad->SetRightMargin(0.25);
    gPad->SetLeftMargin(0.10);
    gPad->SetLogy(0);

    // check if log wanted
    if ( myLog == "000" ) {c1->SetLogx(0); c1->SetLogy(0); c1->SetLogz(0);} 
    if ( myLog == "001" ) {c1->SetLogx(0); c1->SetLogy(0); c1->SetLogz(1);} 
    if ( myLog == "010" ) {c1->SetLogx(0); c1->SetLogy(1); c1->SetLogz(0);} 
    if ( myLog == "011" ) {c1->SetLogx(0); c1->SetLogy(1); c1->SetLogz(1);} 
    if ( myLog == "100" ) {c1->SetLogx(1); c1->SetLogy(0); c1->SetLogz(0);} 
    if ( myLog == "101" ) {c1->SetLogx(1); c1->SetLogy(0); c1->SetLogz(1);} 
    if ( myLog == "110" ) {c1->SetLogx(1); c1->SetLogy(1); c1->SetLogz(0);} 
    if ( myLog == "111" ) {c1->SetLogx(1); c1->SetLogy(1); c1->SetLogz(1);}  

    //___Get TTree from Files_____________
    TTree* ttH_GenRecTree = (TTree*) ttH_GenRec->Get(TreeName.c_str());
    
    //___Get TTree from Files_____________
    TH2D *httH_Gen = new TH2D("httH_Gen",    name.c_str(), nbX, LowX, HighX, nbY, LowY, HighY);
    
    //___Loop over TTree events___________
    // ttH_Gen
    ttH_GenRecTree->Draw((nameY+":"+nameX+">>httH_Gen").c_str()  ,myCut.c_str());
    
    //___Get_Event_Numbers________________
    double n_ttH_Gen  = httH_Gen->Integral();
    
    cout << "===============================" << endl;
    cout << "ttH_Gen(2D)   = " << n_ttH_Gen << endl;
    cout << "===============================" << endl;
    
    // normalize histograms
    if ( httH_Gen->Integral() != 0 ) httH_Gen->Scale(1./httH_Gen->Integral());
    
    //-------------------------------------------------------
    // Set colors for ttH_Gen and ttH_Rec
    //-------------------------------------------------------

    const Int_t NRGBs = 5;
    const Int_t NCont = 255;
     // Rainbow
    //Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    //Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    //Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    //Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
     // Green-like
    Double_t stops[NRGBs] = {0., 0.0, 1.0, 1.0, 1.0};
    Double_t red[NRGBs]   = {0., 0.0, 0.0, 1.0, 1.0};
    Double_t green[NRGBs] = {0., 1.0, 0.0, 0.0, 1.0};
    Double_t blue[NRGBs]  = {0., .25, .50, .75, 1.0};
    
    
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
    
    
    //-------------------------------------------------------
    // Draw ttH_LO and ttH_GenRec
    //-------------------------------------------------------
    httH_Gen->GetYaxis()->SetTitle(ytitle.c_str());
    httH_Gen->GetYaxis()->SetTitleOffset(1.3);
    httH_Gen->GetYaxis()->SetLabelSize(0.025);
    httH_Gen->GetYaxis()->SetTitleSize(0.035);
    //httH_Gen->GetYaxis()->SetNdivisions(6);
    // set X-axis title attributes
    httH_Gen->GetXaxis()->SetTitle(xtitle.c_str());
    httH_Gen->GetXaxis()->SetLabelSize(0.025);
    httH_Gen->GetXaxis()->SetTitleSize(0.035);
    //httH_Gen->GetYaxis()->SetNdivisions(6);
    // set Z-axis sizes
    httH_Gen->GetZaxis()->SetLabelSize(0.025);    
    // draw the plot
    //httH_Gen->Draw("HIST");
    httH_Gen->Draw("COLZ");
    
    //-------------------------------------------------------
    // printout information
    //-------------------------------------------------------
    //myText(     0.135, 0.89, 1, (char*) "Preliminary",        0.025);
    myText(     0.100, 0.95 , 1, (char*) "LHC, #sqrt{s} = 14 TeV",   0.030);
    myText(     0.100, 0.915, 1, (char*) "MadGraph5_aMC@NLO",        0.030);
    //myText(     0.900, 0.55 , 1, (char*) dTitle.c_str(),             0.030);

    if ( id < 10) {
        myText(      0.67, 0.96,  kOrange+1, (char*) "t#bar{t}Y case events, m_{Y}=0 GeV",   0.030);
    } else if ( id < 20 ){
        myText(      0.67, 0.96, kMagenta-3, (char*) "t#bar{t}Y case events, m_{Y}=0 GeV",   0.030);
    } else if ( id < 30 ){
        myText(      0.67, 0.96,  kYellow-3, (char*) "t#bar{t}Y case events, m_{Y}=0 GeV",   0.030);
    } else if ( id < 40 ){
        myText(      0.67, 0.96,     kRed-7, (char*) "t#bar{t}Y case events, m_{Y}=0 GeV",   0.030);
    } else if ( id < 50 ){
        myText(      0.67, 0.96, kMagenta-6, (char*) "t#bar{t}Y case events, m_{Y}=0 GeV",   0.030);
    } else if ( id < 60 ){
        myText(      0.67, 0.96,  kYellow-6, (char*) "t#bar{t}Y case events, m_{Y}=0 GeV",   0.030);
    } else if ( id < 70 ){
        myText(      0.67, 0.96,   kGreen-8, (char*) "t#bar{t}Y case events, m_{Y}=0 GeV",   0.030);
    }
    
    
    // Set minimum and maximum
    //httH_Gen->SetMaximum(4.0*httH_Gen->GetMaximum());
    httH_Gen->SetMinimum(0.00001);
    
    // ====== Boost v4 Directly to v3 from LAB =======
    //  0: 1=~t, 2= t, 3=H (Signal=kBlue,    ttH_Gen=kOrange+1)
    // 10: 1= t, 2=~t, 3=H (Signal=kCyan-3,  ttH_Gen=kMagenta-3)
    // 20: 1= H, 2=~t, 3=t (Signal=kGreen-3, ttH_Gen=kYellow-3)
    // ====== Boost v4 STEP by STEP to v3 ============
    // 30: 1=~t, 2= t, 3=H (Signal=kBlue-7,  ttH_Gen=-7)
    // 40: 1= t, 2=~t, 3=H (Signal=kCyan-6,  ttH_Gen=kMagenta-6)
    // 50: 1= H, 2=~t, 3=t (Signal=kGreen-6, ttH_Gen=kYellow-6)
    if (id==0 || id==10 || id==20 || id==30 || id==40 || id==50  )   myText(     0.50 , 0.915, 1, (char*) "dilepton channel (l+l-)",      0.030);
    if (id==1 || id==11 || id==21 || id==31 || id==41 || id==51  )   myText(     0.50 , 0.915, 1, (char*) "dilepton channel (e+e-)",      0.030);
    if (id==2 || id==12 || id==22 || id==32 || id==42 || id==52  )   myText(     0.50 , 0.915, 1, (char*) "dilepton channel (#mu+#mu-)",  0.030);
    if (id==3 || id==13 || id==23 || id==33 || id==43 || id==53  )   myText(     0.50 , 0.915, 1, (char*) "dilepton channel (e+#mu)",     0.030);
    
    // ----------------------------------------------------------
    // close file
    // ----------------------------------------------------------
    c1->Print(out.c_str());
    
    // ----------------------------------------------------------
    // Save histos with different names (extensions _LO and _NLO)
    // ----------------------------------------------------------
    OutPutFile->cd();
    httH_Gen->Write((name+"_Gen").c_str());
    
    // delete histograms
    delete httH_Gen;
    
    // delete canvas
    delete c1;
    
}

// #############################################################################
void doProb_2D(int id,                                  // Type of distribution (see below)
               TFile* ttH_GenRec,                       // Root input file names
               TFile* OutPutFile,                       // Output file to store histograms
               string myLog,                            // Set log scale for plots               
               string TreeName,                         // TTree name
               string myCut,                            // Cut applied to distributions
               string nameX,                            // TTree variable name to be represented
               string nameRecExp,                       // Define if Rec or Exp is to be used
               int nbX, double LowX, double HighX,      // Define histo bins, x-low and x-high
               int nbY, double LowY, double HighY,      // Define histo bins, x-low and x-high
               string xtitle, string ytitle)            // Titles for X-axis and Y-axis
// #############################################################################
{
    // --------------------------------
    // define output file name string
    // --------------------------------
    string name="Chi2vs"+nameRecExp+nameX;
    string out="Figs/"+name+".pdf";
    // --------------------------------
    
    cout.precision(6);
    
    gROOT->Reset();
    gROOT->SetStyle("ATLAS");
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    gStyle->SetPaperSize(20,24);
    
    // create canvas
    TCanvas *c1 = new TCanvas("cf1","Canvas",50,50,750,550);
    
    //Go to First Pad
    c1->cd(1);
    gPad->SetPad(0.0,0.30,0.95,0.95);
    gPad->SetRightMargin(0.04);
    // check if log wanted
    if ( myLog == "000" ) {c1->SetLogx(0); c1->SetLogy(0); c1->SetLogz(0);} 
    if ( myLog == "001" ) {c1->SetLogx(0); c1->SetLogy(0); c1->SetLogz(1);} 
    if ( myLog == "010" ) {c1->SetLogx(0); c1->SetLogy(1); c1->SetLogz(0);} 
    if ( myLog == "011" ) {c1->SetLogx(0); c1->SetLogy(1); c1->SetLogz(1);} 
    if ( myLog == "100" ) {c1->SetLogx(1); c1->SetLogy(0); c1->SetLogz(0);} 
    if ( myLog == "101" ) {c1->SetLogx(1); c1->SetLogy(0); c1->SetLogz(1);} 
    if ( myLog == "110" ) {c1->SetLogx(1); c1->SetLogy(1); c1->SetLogz(0);} 
    if ( myLog == "111" ) {c1->SetLogx(1); c1->SetLogy(1); c1->SetLogz(1);}  
    
    //___Get TTree from Files_____________
    TTree* ttH_GenRecTree = (TTree*) ttH_GenRec->Get(TreeName.c_str());
    
    //___Get TTree from Files_____________
    TH2D *httH_Gen = new TH2D("httH_Gen",    name.c_str(), nbX, LowX, HighX, nbY, LowY, HighY);
    
    //___Loop over TTree events___________
    // Create Chi2 value from TTree variables
    string Va, ReVa, sVa;
    string p0,  p1,  p2,  p3,  p4,  p5;
    string p00, p11, p22, p33, p44, p55;
    // t
      Va    = "mTopQ";
    ReVa    = nameRecExp+Va;
     sVa    = "0.890";
      p0    = "("+ReVa+"-"+Va+")/"+sVa;
      p00   = p0+"*"+p0;
    // t
      Va    = "mTbarQ";
    ReVa    = nameRecExp+Va;
     sVa    = "0.902";
      p1    = "("+ReVa+"-"+Va+")/"+sVa;
      p11   = p1+"*"+p1;
    // W+
      Va    = "mWp";
    ReVa    = nameRecExp+Va;
     sVa    = "1.231";
      p2    = "("+ReVa+"-"+Va+")/"+sVa;
      p22   = p2+"*"+p2;
    // W-
      Va    = "mWn";
    ReVa    = nameRecExp+Va;
     sVa    = "1.175";
      p3    = "("+ReVa+"-"+Va+")/"+sVa;
      p33   = p3+"*"+p3;
    // PtNeu
      Va    = "PtNeu";
    ReVa    = nameRecExp+Va;
     sVa    = "14.88";
     p4    = "("+ReVa+"-"+Va+")/"+sVa;
     p44   = p4+"*"+p4;
    // PtNeu
      Va    = "PtNeubar";
    ReVa    = nameRecExp+Va;
     sVa    = "14.88";
     p5    = "("+ReVa+"-"+Va+")/"+sVa;
     p55   = p5+"*"+p5;
    
    // Plot things
    string nameYaxis = "(("+ p00 +"+"+ p11 +"+"+ p22 +"+"+ p33 +"+"+ p44 +"+"+ p55 +")/6.)";
    string nameXaxis = nameRecExp+nameX;
    ttH_GenRecTree->Draw((nameYaxis+":"+nameXaxis+">>httH_Gen").c_str()  ,myCut.c_str());
    
    //___Get_Event_Numbers________________
    double n_ttH_Gen  = httH_Gen->Integral();
    
    cout << "===============================" << endl;
    cout << " Chi2 2D Histo = " << n_ttH_Gen << endl;
    cout << "===============================" << endl;
    
    // normalize histograms
    if ( httH_Gen->Integral() != 0 ) httH_Gen->Scale(1./httH_Gen->Integral());
    
    
    //-------------------------------------------------------
    // Set colors for ttH_Gen and ttH_Rec
    //-------------------------------------------------------
    httH_Gen->SetLineWidth(2); //  ttH NLO line width
    if ( id < 10) {
        httH_Gen->SetLineColor(kOrange+1);
        httH_Gen->SetFillColor(kOrange+1);
    } else if ( id < 20 ){
        httH_Gen->SetLineColor(kMagenta-3);
        httH_Gen->SetFillColor(kMagenta-3);
    } else if ( id < 30 ){
        httH_Gen->SetLineColor(kYellow-3);
        httH_Gen->SetFillColor(kYellow-3);
    } else if ( id < 40 ){
        httH_Gen->SetLineColor(kRed-7);
        httH_Gen->SetFillColor(kRed-7);
    } else if ( id < 50 ){
        httH_Gen->SetLineColor(kMagenta-6);
        httH_Gen->SetFillColor(kMagenta-6);
    } else if ( id < 60 ){
        httH_Gen->SetLineColor(kYellow-6);
        httH_Gen->SetFillColor(kYellow-6);
    } else if ( id < 70 ){
        httH_Gen->SetLineColor(kGreen-8);
        httH_Gen->SetFillColor(kGreen-8);
    }
    
    
    //-------------------------------------------------------
    // Draw ttH_LO and ttH_GenRec
    //-------------------------------------------------------
    httH_Gen->Draw("HIST");
    httH_Gen->GetXaxis()->SetTitle(xtitle.c_str());
    httH_Gen->GetYaxis()->SetTitle(ytitle.c_str());
    
    //-------------------------------------------------------
    // printout information
    //-------------------------------------------------------
    myText(     0.135, 0.84, 1, (char*) "Preliminary",        0.050);
    myText(     0.135, 0.79, 1, (char*) "#sqrt{s} = 14 TeV",  0.035);
    myText(     0.135, 0.74, 1, (char*) "MadGraph5_aMC@NLO",  0.035);
    if ( id < 10) {
        myText(      0.60, 0.82,   kOrange+1, (char*) "Chi2, m_{Y}=0 GeV",   0.035);
    } else if ( id < 20 ){
        myText(      0.60, 0.82, kMagenta-3, (char*) "Chi2, m_{Y}=0 GeV",   0.035);
    } else if ( id < 30 ){
        myText(      0.60, 0.82, kYellow-3, (char*) "Chi2, m_{Y}=0 GeV",   0.035);
    } else if ( id < 40 ){
        myText(      0.60, 0.82,   kRed-7, (char*) "Chi2, m_{Y}=0 GeV",   0.035);
    } else if ( id < 50 ){
        myText(      0.60, 0.82, kMagenta-6, (char*) "Chi2, m_{Y}=0 GeV",   0.035);
    } else if ( id < 60 ){
        myText(      0.60, 0.82, kYellow-6, (char*) "Chi2, m_{Y}=0 GeV",   0.035);
    } else if ( id < 70 ){
        myText(      0.60, 0.82,  kGreen-8, (char*) "Chi2, m_{Y}=0 GeV",   0.035);
    }
    
    
    // Set minimum and maximum
    httH_Gen->SetMaximum(4.0*httH_Gen->GetMaximum());
    httH_Gen->SetMinimum(0.00001);
    
    // ====== Boost v4 Directly to v3 from LAB =======
    //  0: 1=~t, 2= t, 3=H (Signal=kBlue,    ttH_Gen=kOrange+1)
    // 10: 1= t, 2=~t, 3=H (Signal=kCyan-3,  ttH_Gen=kMagenta-3)
    // 20: 1= H, 2=~t, 3=t (Signal=kGreen-3, ttH_Gen=kYellow-3)
    // ====== Boost v4 STEP by STEP to v3 ============
    // 30: 1=~t, 2= t, 3=H (Signal=kBlue-7,  ttH_Gen=-7)
    // 40: 1= t, 2=~t, 3=H (Signal=kCyan-6,  ttH_Gen=kMagenta-6)
    // 50: 1= H, 2=~t, 3=t (Signal=kGreen-6, ttH_Gen=kYellow-6)
    if (id==0 || id==10 || id==20 || id==30 || id==40 || id==50  )   myText(     0.135 , 0.69, 1, (char*) "l+l- channels",     0.035);
    if (id==1 || id==11 || id==21 || id==31 || id==41 || id==51  )   myText(     0.135 , 0.69, 1, (char*) "e+e- channel",      0.035);
    if (id==2 || id==12 || id==22 || id==32 || id==42 || id==52  )   myText(     0.135 , 0.69, 1, (char*) "#mu+#mu- channel",  0.035);
    if (id==3 || id==13 || id==23 || id==33 || id==43 || id==53  )   myText(     0.135 , 0.69, 1, (char*) "e+#mu channel",     0.035);
    
    // ----------------------------------------------------------
    // close file
    // ----------------------------------------------------------
    c1->Print(out.c_str());
    
    // ----------------------------------------------------------
    // Save histos with different names (extensions _LO and _NLO)
    // ----------------------------------------------------------
    OutPutFile->cd();
    httH_Gen->Write((name+"_Gen").c_str());
    
    // delete histograms
    delete httH_Gen;
    
    // delete canvas
    delete c1;
    
}

