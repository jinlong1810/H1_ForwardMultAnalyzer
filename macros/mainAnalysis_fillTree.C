#include "../header/mainAnalysis.h"
#include "../header/MCweight.h"
#include "TLorentzVector.h"

using namespace std;

double ptcut[3] = {0.15,0.15,0.15};
double cuts_1_value[3]={1.0,2.0,5.0};
double cuts_2_value[3]={40.,50.,60.};
double cuts_3_value[3]={12.,10.,8.};
double cuts_4_value[3]={3.,5.,10.};
//Generate a random number:
TF1* randn = new TF1("randn","1",0,1);

int getPassFlag(vector<int> trackType, vector<double> cuts, int trackQuality){

   //define pass flag
   int pass = 1;

   //define track quality, trackQuality = 0 (tight), = 1 (default), = 2 (loose)
   //pt,dcaPrime,trkTheta,startHits,endHits,vtxNhits,elecTheta,nuclia,p,pe,chi2vtx,chi2Link,zLength,rZero,chi2Trk

   if( trackType[0] == 1 ){
      if( cuts[0]<ptcut[trackQuality] ) pass = 0;
      if( fabs( cuts[1]*TMath::Sin(cuts[2]) ) > cuts_1_value[trackQuality] ) pass = 0;
      if( cuts[3] > cuts_2_value[trackQuality] ) pass = 0;
      if( fabs(cuts[3] - cuts[4]) < cuts_3_value[trackQuality] ) pass = 0;
      if( cuts[5] < 0 ) pass = 0;
      if( fabs(cuts[2] - cuts[6]) < 0.1 ) pass = 0;
      if( randn->GetRandom() > cuts[7] && randn->GetRandom() < 1.0 ) pass = 0; 
   }      
   else if( trackType[1] && trackType[0] == 2 ){
      if( cuts[0]<ptcut[trackQuality] ) pass = 0;
      if( cuts[8] < 0.5 ) pass = 0;
      if( TMath::RadToDeg()*cuts[2] < 10. || TMath::RadToDeg()*cuts[2] > 30. ) pass = 0;
      if( fabs(cuts[1]) > cuts_4_value[trackQuality] ) pass = 0;
      if( cuts[3] > cuts_2_value[trackQuality] ) pass = 0;
      if( cuts[5] < 0 ) pass = 0;
      if( cuts[9]/cuts[8] > 99999.9 ) pass = 0;
      if( cuts[10] > 50. ) pass = 0;
      if( cuts[11] > 50. ) pass = 0;
      if( randn->GetRandom() > cuts[7] && randn->GetRandom() < 1.0 ) pass = 0; 
   }  
   else if( trackType[2] && trackType[0] == 3 ){
      if( cuts[0]<ptcut[trackQuality] ) pass = 0;
      if( cuts[8] < 0.5 ) pass = 0;
      if( TMath::RadToDeg()*cuts[2] < 6. || TMath::RadToDeg()*cuts[2] > 25. ) pass = 0;
      if( cuts[3] > 25.0 ) pass = 0;
      if( fabs(cuts[12]) < 10. ) pass = 0;
      if( cuts[13] > 20. ) pass = 0;
      if( cuts[9]/cuts[8] > 99999.9 ) pass = 0;
      if( cuts[10] > 25. ) pass = 0;
      if( cuts[14] > 10. ) pass = 0;
      if( randn->GetRandom() > cuts[7] && randn->GetRandom() < 1.0 ) pass = 0; 
   }  
   else{
      pass = 0;
   }

   return pass;
}

struct MyEvent {
   // general information
   Int_t run_mini,evno_mini; // run and event number
   Float_t w_mini; // event weight
   // event quality .. not complete yet
   Float_t vertex_mini[3];
   // Monte Carlo information
   Float_t xMC_es_mini,yMC_es_mini,Q2MC_es_mini;

   enum {
      nMCtrack_MAX=400
   };
   // if there is no MC info, nMCtrack is set to zero
   Int_t nMCtrack_mini;
   Float_t pxMC_mini[nMCtrack_MAX];
   Float_t pyMC_mini[nMCtrack_MAX];
   Float_t pzMC_mini[nMCtrack_MAX];
   Float_t etaMC_mini[nMCtrack_MAX];
   Float_t chargeMC_mini[nMCtrack_MAX];

   Float_t ptStarMC_mini[nMCtrack_MAX];
   Float_t etaStarMC_mini[nMCtrack_MAX];
   Float_t phiStarMC_mini[nMCtrack_MAX];

   Int_t imatchMC_mini[nMCtrack_MAX];
   Float_t etaAsymMC_mini;
   Int_t totalMultMC_mini;
   Float_t eGammaPhiMC_mini;
   Float_t sumPtMC_mini;
   Float_t elecPxMC_mini;
   Float_t elecPyMC_mini;
   Float_t elecPzMC_mini;
   Float_t elecEMC_mini;
   Float_t phoPxMC_mini;
   Float_t phoPyMC_mini;
   Float_t phoPzMC_mini;
   Float_t phoEMC_mini;
   Int_t isQEDcMC_mini;

   // reconstructed quantities
   Float_t xREC_es_mini,yREC_es_mini,Q2REC_es_mini;
   enum {
      nRECtrack_MAX=200
   };
   Int_t eventpass_mini;
   Int_t eventpassTight_mini;
   Int_t eventpassLoose_mini;
   Int_t nRECtrack_mini;
   Int_t typeChgREC_mini[nRECtrack_MAX];
   Float_t etaAsymREC_mini;
   Float_t EpzREC_mini;
   Float_t eElectronBeam_mini;

   //hfs and elec kinematics
   Float_t hfsEREC_mini, hfsPtREC_mini, hfsPzREC_mini;
   Float_t elecEREC_mini, elecPtREC_mini, elecPzREC_mini;
   Int_t elecChargeREC_mini;

   Int_t totalMultREC_mini;
   Float_t pxREC_mini[nRECtrack_MAX];
   Float_t pyREC_mini[nRECtrack_MAX];
   Float_t pzREC_mini[nRECtrack_MAX];
   Float_t pREC_mini[nRECtrack_MAX];
   Float_t peREC_mini[nRECtrack_MAX];
   Float_t etaREC_mini[nRECtrack_MAX];
   Float_t phiREC_mini[nRECtrack_MAX];

   Float_t ptStarREC_mini[nRECtrack_MAX];
   Float_t etaStarREC_mini[nRECtrack_MAX];
   Float_t phiStarREC_mini[nRECtrack_MAX];

   Float_t nucliaREC_mini[nRECtrack_MAX];
   Float_t dmatchREC_mini[nRECtrack_MAX];
   Int_t imatchREC_mini[nRECtrack_MAX];
   Int_t passREC_mini[nRECtrack_MAX];
   Int_t passTightREC_mini[nRECtrack_MAX];
   Int_t passLooseREC_mini[nRECtrack_MAX];
};

void mainAnalysis_fillTree(const int start = 0, int end = -1, const bool doGen_ = true, const bool doRapgap_ = true, const bool doReweight_ = false, const bool doComb_=true, const bool doFwd_= false) {

   //dirty hack of the problem of using TFile with TTree here. 
   TH1D* DATA_y = new TH1D("h_y_1","h_y_1",200,0,1);
   TH1D* DATA_vtxZ = new TH1D("h_vtxZ_1","h_vtxZ_1", 100,-50,50);
   if( doRapgap_ ){
      for(int i = 0; i < DATA_vtxZ->GetNbinsX(); i++){
         DATA_vtxZ->SetBinContent(i+1,vtxz_weight_hadCali_rapgap[i]);
      }
      for(int i = 0; i < DATA_y->GetNbinsX(); i++){
         DATA_y->SetBinContent(i+1,y_weight_hadCali_rapgap[i]);
      }
   }
   else{
      for(int i = 0; i < DATA_vtxZ->GetNbinsX(); i++){
         DATA_vtxZ->SetBinContent(i+1,vtxz_weight_hadCali_django[i]);
      }
      for(int i = 0; i < DATA_y->GetNbinsX(); i++){
         DATA_y->SetBinContent(i+1,y_weight_hadCali_django[i]);
      }
   }

   //starting TChain;
   TChain* tree = new TChain("properties");
   int dis_events = 0;

   if( doRapgap_ && doGen_ ){
      tree->Add("../batch/output/mc_9299_hadCaliNewRadPho/*.root");
      tree->Add("../batch/output/mc_9300_hadCaliNewRadPho/*.root");
      tree->Add("../batch/output/mc_9301_hadCaliNewRadPho/*.root");
      tree->Add("../batch/output/mc_9302_hadCaliNewRadPho/*.root");
      tree->Add("../batch/output/mc_9303_hadCaliNewRadPho/*.root");
      tree->Add("../batch/output/mc_9304_hadCaliNewRadPho/*.root");
      tree->Add("../batch/output/mc_9305_hadCaliNewRadPho/*.root");
      tree->Add("../batch/output/mc_9306_hadCaliNewRadPho/*.root");

      //save the number of events that separate inclusive DIS to diffractive DIS
         dis_events = tree->GetEntries();
      tree->Add("../batch/output/mc_9015_hadCaliNewRadPho/*.root");

      //nonradiative MCs
      // tree->Add("../batch/output/mc_5878_NRAD/*.root");
   }
   else if( !doRapgap_ && doGen_){
      tree->Add("../batch/output/mc_8926_hadCaliNewRadPho/*.root");
      tree->Add("../batch/output/mc_8927_hadCaliNewRadPho/*.root");

      // tree->Add("../batch/output/mc_5877_NRAD_django14/*.root");

   }
   else if( !doGen_ ){
      tree->Add("../batch/output/data_highE_06_hadCaliNew/*.root");
      tree->Add("../batch/output/data_highE_07_hadCaliNew/*.root");
   }
   else{ cout << "no files" << endl;}
  


   //start to define new miniTree:
   TTree *outtree =new TTree("miniTree","miniTree");
   MyEvent myEvent;
   TH1D* h_RstartPos[4];
   TH1D* h_RstartNeg[4];
   TH1D* h_dcaPos[4];
   TH1D* h_dcaNeg[4];

   for(int i=0;i<4;i++){
      h_RstartPos[i] = new TH1D(Form("h_RstartPos_%d",i),";R_{start}",200,0,100);
      h_RstartNeg[i] = new TH1D(Form("h_RstartNeg_%d",i),";R_{start}",200,0,100);
      h_dcaPos[i] = new TH1D(Form("h_dcaPos_%d",i),";dca",200,-15,15);
      h_dcaNeg[i] = new TH1D(Form("h_dcaNeg_%d",i),";dca",200,-15,15);
   }
   

   outtree->Branch("w_mini",&myEvent.w_mini,"w_mini/F");
   outtree->Branch("vertex_mini",myEvent.vertex_mini,"vertex_mini[3]/F");
   outtree->Branch("yMC_es_mini",&myEvent.yMC_es_mini,"yMC_es_mini/F");
   outtree->Branch("Q2MC_es_mini",&myEvent.Q2MC_es_mini,"Q2MC_es_mini/F");
   outtree->Branch("eGammaPhiMC_mini",&myEvent.eGammaPhiMC_mini,"eGammaPhiMC_mini/F");
   outtree->Branch("sumPtMC_mini",&myEvent.sumPtMC_mini,"sumPtMC_mini/F");
   outtree->Branch("elecPxMC_mini",&myEvent.elecPxMC_mini,"elecPxMC_mini/F");
   outtree->Branch("elecPyMC_mini",&myEvent.elecPyMC_mini,"elecPyMC_mini/F");
   outtree->Branch("elecPzMC_mini",&myEvent.elecPzMC_mini,"elecPzMC_mini/F");
   outtree->Branch("elecEMC_mini",&myEvent.elecEMC_mini,"elecEMC_mini/F");
   outtree->Branch("phoPxMC_mini",&myEvent.phoPxMC_mini,"phoPxMC_mini/F");
   outtree->Branch("phoPyMC_mini",&myEvent.phoPyMC_mini,"phoPyMC_mini/F");
   outtree->Branch("phoPzMC_mini",&myEvent.phoPzMC_mini,"phoPzMC_mini/F");
   outtree->Branch("phoEMC_mini",&myEvent.phoEMC_mini,"phoEMC_mini/F");
   outtree->Branch("isQEDcMC_mini",&myEvent.isQEDcMC_mini,"isQEDcMC_mini/I");

   outtree->Branch("nMCtrack_mini",&myEvent.nMCtrack_mini,"nMCtrack_mini/I");
   outtree->Branch("pxMC_mini",myEvent.pxMC_mini,"pxMC_mini[nMCtrack_mini]/F");
   outtree->Branch("pyMC_mini",myEvent.pyMC_mini,"pyMC_mini[nMCtrack_mini]/F");
   outtree->Branch("pzMC_mini",myEvent.pzMC_mini,"pzMC_mini[nMCtrack_mini]/F");
   outtree->Branch("etaMC_mini",myEvent.etaMC_mini,"etaMC_mini[nMCtrack_mini]/F");
   outtree->Branch("ptStarMC_mini",myEvent.ptStarMC_mini,"ptStarMC_mini[nMCtrack_mini]/F");
   outtree->Branch("etaStarMC_mini",myEvent.etaStarMC_mini,"etaStarMC_mini[nMCtrack_mini]/F");

   outtree->Branch("totalMultMC_mini",&myEvent.totalMultMC_mini,"totalMultMC_mini/I");

   /*
   comment out for simple scatElec miniTree
   */

   outtree->Branch("hfsEREC_mini",&myEvent.hfsEREC_mini,"hfsEREC_mini/F");
   outtree->Branch("hfsPtREC_mini",&myEvent.hfsPtREC_mini,"hfsPtREC_mini/F");
   outtree->Branch("hfsPzREC_mini",&myEvent.hfsPzREC_mini,"hfsPzREC_mini/F");
   outtree->Branch("elecEREC_mini",&myEvent.elecEREC_mini,"elecEREC_mini/F");
   outtree->Branch("elecPtREC_mini",&myEvent.elecPtREC_mini,"elecPtREC_mini/F");
   outtree->Branch("elecPzREC_mini",&myEvent.elecPzREC_mini,"elecPzREC_mini/F");
   outtree->Branch("elecChargeREC_mini",&myEvent.elecChargeREC_mini,"elecChargeREC_mini/I");

   outtree->Branch("xREC_es_mini",&myEvent.xREC_es_mini,"xREC_es_mini/F");
   outtree->Branch("yREC_es_mini",&myEvent.yREC_es_mini,"yREC_es_mini/F");
   outtree->Branch("Q2REC_es_mini",&myEvent.Q2REC_es_mini,"Q2REC_es_mini/F");
   outtree->Branch("eventpass_mini",&myEvent.eventpass_mini,"eventpass_mini/I");
   outtree->Branch("eventpassTight_mini",&myEvent.eventpassTight_mini,"eventpassTight_mini/I");
   outtree->Branch("eventpassLoose_mini",&myEvent.eventpassLoose_mini,"eventpassLoose_mini/I");
   outtree->Branch("nRECtrack_mini",&myEvent.nRECtrack_mini,"nRECtrack_mini/I");
   outtree->Branch("EpzREC_mini",&myEvent.EpzREC_mini,"EpzREC_mini/F");
   outtree->Branch("totalMultREC_mini",&myEvent.totalMultREC_mini,"totalMultREC_mini/I");
   outtree->Branch("eElectronBeam_mini",&myEvent.eElectronBeam_mini,"eElectronBeam_mini/F");

   outtree->Branch("pxREC_mini",myEvent.pxREC_mini,"pxREC_mini[nRECtrack_mini]/F");
   outtree->Branch("pyREC_mini",myEvent.pyREC_mini,"pyREC_mini[nRECtrack_mini]/F");
   outtree->Branch("pzREC_mini",myEvent.pzREC_mini,"pzREC_mini[nRECtrack_mini]/F");

   outtree->Branch("etaREC_mini",myEvent.etaREC_mini,"etaREC_mini[nRECtrack_mini]/F");
   outtree->Branch("phiREC_mini",myEvent.phiREC_mini,"phiREC_mini[nRECtrack_mini]/F");
   outtree->Branch("ptStarREC_mini",myEvent.ptStarREC_mini,"ptStarREC_mini[nRECtrack_mini]/F");
   outtree->Branch("etaStarREC_mini",myEvent.etaStarREC_mini,"etaStarREC_mini[nRECtrack_mini]/F");
   outtree->Branch("phiStarREC_mini",myEvent.phiStarREC_mini,"phiStarREC_mini[nRECtrack_mini]/F");

   outtree->Branch("nucliaREC_mini",myEvent.nucliaREC_mini,"nucliaREC_mini[nRECtrack_mini]/F");
   outtree->Branch("passREC_mini",myEvent.passREC_mini,"passREC_mini[nRECtrack_mini]/I");
   outtree->Branch("passTightREC_mini",myEvent.passTightREC_mini,"passTightREC_mini[nRECtrack_mini]/I");
   outtree->Branch("passLooseREC_mini",myEvent.passLooseREC_mini,"passLooseREC_mini[nRECtrack_mini]/I");

   double zvtxOffset=0.;

   if(tree) {
      Int_t run, evno;
      Int_t vertexType;
      Float_t w;
      Float_t trigWeightAC;
      Float_t trigWeightRW;
      Float_t elecPxREC,elecPyREC,elecEREC,elecPzREC;
      Float_t hfsEREC,hfsPxREC, hfsPyREC, hfsPzREC;
      Float_t elecXclusREC,elecYclusREC, elecThetaREC,elecEnergyREC,elecEfracREC,elecHfracREC;
      Float_t elecEradREC,elecEcraREC;
      Int_t elecChargeREC;
      Float_t eElectronBeam;
      Int_t isQEDc;
     
      Int_t ibgREC;

      Float_t vertex[3];
      Float_t xREC,yREC,Q2REC;
      Float_t xREC_es,yREC_es,Q2REC_es;
      
      Float_t simvertex[3];
      Float_t elecEradMC;
      Float_t xMC,yMC,Q2MC;
      Float_t xGKI,yGKI,Q2GKI;
      Float_t xMC_es,yMC_es,Q2MC_es;
      Int_t nMCtrack;
      Float_t ptStarMC[400];
      Float_t etaStarMC[400];
      Float_t phiStarMC[400];
      Float_t pxMC[400];
      Float_t pyMC[400];
      Float_t pzMC[400];
      Float_t etaMC[400];
      Float_t chargeMC[400];
      Float_t elecPxMC,elecPyMC,elecPzMC,elecEMC;
      Float_t radPhoPxMC,radPhoPyMC,radPhoPzMC,radPhoEMC;
 
      Int_t nRECtrack;
      Int_t typeChgREC[200];
      Float_t pxREC[200];
      Float_t pyREC[200];
      Float_t pzREC[200];
      Float_t pREC[200];
      Float_t peREC[200];
      Float_t ptStarREC[200];
      Float_t phiStarREC[200];
      Float_t etaStarREC[200];
      Float_t etaREC[200];
      Float_t chi2vtxREC[400];
      Float_t chi2nvREC[400];
      Int_t vtxNdfREC[200];
      Int_t nvNdfREC[200];
      Int_t vtxNHitsREC[200];
      Int_t nvNHitsREC[200];
      Float_t vtxTrackLengthREC[400];
      Float_t nvTrackLengthREC[400];
      Float_t dcaPrimeREC[400];
      Float_t dz0PrimeREC[400];
      Float_t nucliaREC[400];

      Int_t imatchREC[400];
      Float_t dmatchREC[400];
      Int_t imatchMC[400];

      Float_t startHitsRadiusREC[400];
      Float_t endHitsRadiusREC[400];
      Float_t trkThetaREC[400];
      Float_t chi2TrkREC[400];
      Int_t   ndfTrkREC[400];
      Float_t zLengthHitREC[400];
      Float_t chi2LinkREC[400];
      Int_t ndfLinkREC[400];
      Float_t rZeroREC[400];

      tree->SetBranchAddress("run",&run);
      tree->SetBranchAddress("evno",&evno);
      tree->SetBranchAddress("xGKI",&xGKI);

      tree->SetBranchAddress("xGKI",&xGKI);
      tree->SetBranchAddress("yGKI",&yGKI);
      tree->SetBranchAddress("Q2GKI",&Q2GKI);
      tree->SetBranchAddress("simvertex",&simvertex);
      tree->SetBranchAddress("eElectronBeam",&eElectronBeam);
      tree->SetBranchAddress("isQEDc",&isQEDc);

      tree->SetBranchAddress("nMCtrack",&nMCtrack);
      tree->SetBranchAddress("etaStar2MC",etaStarMC);
      tree->SetBranchAddress("ptStar2MC",ptStarMC);
      tree->SetBranchAddress("phiStar2MC",phiStarMC);
      tree->SetBranchAddress("pxMC",&pxMC);
      tree->SetBranchAddress("pyMC",&pyMC);
      tree->SetBranchAddress("pzMC",&pzMC);
      tree->SetBranchAddress("etaMC",&etaMC);
      tree->SetBranchAddress("chargeMC",&chargeMC);
      tree->SetBranchAddress("xMC",&xMC);
      tree->SetBranchAddress("yMC",&yMC);
      tree->SetBranchAddress("Q2MC",&Q2MC);
      tree->SetBranchAddress("xMC_es",&xMC_es);
      tree->SetBranchAddress("yMC_es",&yMC_es);
      tree->SetBranchAddress("Q2MC_es",&Q2MC_es);
      tree->SetBranchAddress("elecEMC",&elecEMC);
      tree->SetBranchAddress("elecEradMC",&elecEradMC);
      tree->SetBranchAddress("imatchMC",&imatchMC);
      tree->SetBranchAddress("elecPxMC",&elecPxMC);
      tree->SetBranchAddress("elecPyMC",&elecPyMC);
      tree->SetBranchAddress("elecPzMC",&elecPzMC);
      tree->SetBranchAddress("elecEMC",&elecEMC);
      tree->SetBranchAddress("radPhoPxMC",&radPhoPxMC);
      tree->SetBranchAddress("radPhoPyMC",&radPhoPyMC);
      tree->SetBranchAddress("radPhoPzMC",&radPhoPzMC);
      tree->SetBranchAddress("radPhoEMC",&radPhoEMC);

      tree->SetBranchAddress("ibg",&ibgREC);
      tree->SetBranchAddress("elecXclusREC",&elecXclusREC);
      tree->SetBranchAddress("elecYclusREC",&elecYclusREC);
      tree->SetBranchAddress("elecThetaREC",&elecThetaREC);
      tree->SetBranchAddress("elecEnergyREC",&elecEnergyREC);
      tree->SetBranchAddress("elecEfracREC",&elecEfracREC);
      tree->SetBranchAddress("elecHfracREC",&elecHfracREC);
      tree->SetBranchAddress("elecChargeREC",&elecChargeREC);
      
      tree->SetBranchAddress("w",&w);
      tree->SetBranchAddress("vertexType",&vertexType);
      tree->SetBranchAddress("vertex",vertex);
      tree->SetBranchAddress("trigWeightAC",&trigWeightAC);
      tree->SetBranchAddress("trigWeightRW",&trigWeightRW);
      tree->SetBranchAddress("xREC",&xREC);
      tree->SetBranchAddress("yREC",&yREC);
      tree->SetBranchAddress("Q2REC",&Q2REC);
      tree->SetBranchAddress("xREC_es",&xREC_es);
      tree->SetBranchAddress("yREC_es",&yREC_es);
      tree->SetBranchAddress("Q2REC_es",&Q2REC_es);
      tree->SetBranchAddress("elecPxREC",&elecPxREC);
      tree->SetBranchAddress("elecPyREC",&elecPyREC);
      tree->SetBranchAddress("elecPzREC",&elecPzREC);
      tree->SetBranchAddress("elecEREC",&elecEREC);
      tree->SetBranchAddress("elecEradREC",&elecEradREC);
      tree->SetBranchAddress("elecEcraREC",&elecEcraREC);

      tree->SetBranchAddress("hfsPxREC",&hfsPxREC);
      tree->SetBranchAddress("hfsPyREC",&hfsPyREC);
      tree->SetBranchAddress("hfsPzREC",&hfsPzREC);
      tree->SetBranchAddress("hfsEREC",&hfsEREC);
      
      tree->SetBranchAddress("nRECtrack",&nRECtrack);
      tree->SetBranchAddress("typeChgREC",typeChgREC);
      tree->SetBranchAddress("pxREC",pxREC);
      tree->SetBranchAddress("pyREC",pyREC);
      tree->SetBranchAddress("pzREC",pzREC);
      tree->SetBranchAddress("pREC",pREC);
      tree->SetBranchAddress("peREC",peREC);
      tree->SetBranchAddress("etaStar2REC",etaStarREC);
      tree->SetBranchAddress("etaREC",etaREC);
      tree->SetBranchAddress("phiStar2REC",phiStarREC);
      tree->SetBranchAddress("ptStar2REC",ptStarREC);
      tree->SetBranchAddress("chi2vtxREC",chi2vtxREC);
      tree->SetBranchAddress("chi2nvREC",chi2nvREC);
      tree->SetBranchAddress("vtxNdfREC",vtxNdfREC);
      tree->SetBranchAddress("nvNdfREC",nvNdfREC);
      tree->SetBranchAddress("vtxNHitsREC",vtxNHitsREC);
      tree->SetBranchAddress("nvNHitsREC",nvNHitsREC);
      tree->SetBranchAddress("vtxTrackLengthREC",vtxTrackLengthREC);
      tree->SetBranchAddress("nvTrackLengthREC",nvTrackLengthREC);
      tree->SetBranchAddress("dcaPrimeREC",dcaPrimeREC);
      tree->SetBranchAddress("dz0PrimeREC",dz0PrimeREC);
      tree->SetBranchAddress("nucliaREC",nucliaREC);
      
      tree->SetBranchAddress("imatchREC",imatchREC);
      tree->SetBranchAddress("dmatchREC",dmatchREC);

      tree->SetBranchAddress("startHitsRadiusREC",startHitsRadiusREC);
      tree->SetBranchAddress("endHitsRadiusREC",endHitsRadiusREC);
      tree->SetBranchAddress("trkThetaREC",trkThetaREC);
      tree->SetBranchAddress("chi2TrkREC",chi2TrkREC);
      tree->SetBranchAddress("ndfTrkREC",ndfTrkREC);
      tree->SetBranchAddress("zLengthHitREC",zLengthHitREC);
      tree->SetBranchAddress("chi2LinkREC",chi2LinkREC);
      tree->SetBranchAddress("ndfLinkREC",ndfLinkREC);
      tree->SetBranchAddress("rZeroREC",rZeroREC);

      cout << "total. number of events = " << tree->GetEntries() << endl;
      if(end == -1 || end >= tree->GetEntries()) {end = tree->GetEntries();}
      cout << "starting events = " << start << endl;
      cout << "ending events = " << end << endl;
      cout << "total events now ~ " << 1.0*(tree->GetEntries()-dis_events)+dis_events << endl;

      int totalEvents = 0;
      for(int i=start;i<end;i++) {
         tree->GetEntry(i);

         //assigning all reweights:
         double evt_weight = 1.;
         if( !doGen_ && !doReweight_ ){
            //this is data weighting for triggers
            evt_weight = w*trigWeightRW;
         }
         else if( doGen_ && doReweight_ ) {
            //reweighting MC to DATA distribution in phase space variables
            double y_weight = DATA_y->GetBinContent( DATA_y->FindBin(yMC_es) );
            if( y_weight == 0. ) y_weight = 1.0;
            double vtxZ_weight = DATA_vtxZ->GetBinContent( DATA_vtxZ->FindBin( simvertex[2]) );
            if( vtxZ_weight == 0. ) vtxZ_weight = 1.0;
            if( doRapgap_ ){//rapgap has diffractive MCs
               if( i < dis_events ){
                  evt_weight = w*y_weight*vtxZ_weight*(136./68.);//data/mc Lumi
               }
               else if( i >= dis_events && i < 1.0*(tree->GetEntries()-dis_events)+dis_events ){
                  evt_weight = w*y_weight*vtxZ_weight*(136./(0.9*219.35));//data/mc Lumi
               }
            }
            else{
               evt_weight = w*y_weight*vtxZ_weight;
            }
         }
         else if( doGen_ && !doReweight_ ) {
            //this is MC without anyreweighting
            if( doRapgap_ ){ //rapgap has diffractive MCs
               if( i < dis_events ){
                  evt_weight = w*(136./68.);//data/mc Lumi
                  // evt_weight = w;
               }
               else if( i >= dis_events && i < 1.0*(tree->GetEntries()-dis_events)+dis_events ){
                  evt_weight = w*(136./(1.0*219.35) );//data/mc Lumi
               }
               else{
                  cout << "overflow in events! " << endl;
               }
            }
            else{
               evt_weight = w;
            }
            
         }
         else{
            cout << "Error in config! " << endl;
         }


         myEvent.run_mini = run;
         myEvent.evno_mini = evno;
         myEvent.w_mini = evt_weight;
         myEvent.eElectronBeam_mini = eElectronBeam;
         myEvent.totalMultREC_mini = -999;

         myEvent.xMC_es_mini = -999.;
         myEvent.yMC_es_mini = -999.;
         myEvent.Q2MC_es_mini = -999.;

         myEvent.nMCtrack_mini = -999;
         myEvent.etaAsymMC_mini = -999.;

         for(int j=0;j<400;j++) {
               myEvent.pxMC_mini[j] = -999.;
               myEvent.pyMC_mini[j] = -999.;
               myEvent.pzMC_mini[j] = -999.;
               myEvent.etaMC_mini[j] = -999.;
               myEvent.chargeMC_mini[j] = -999.;
               myEvent.ptStarMC_mini[j] = -999.;
               myEvent.etaStarMC_mini[j] = -999.;
               myEvent.phiStarMC_mini[j] = -999.;
               myEvent.imatchMC_mini[j] = -999;
         }
         
         if( doGen_ ){
            //generator level event selections:
            myEvent.xMC_es_mini = xMC_es;
            myEvent.yMC_es_mini = yMC_es;
            myEvent.Q2MC_es_mini = Q2MC_es;
            myEvent.nMCtrack_mini = nMCtrack;

            double Ntracks_eta_p_MC=0.;
            double Ntracks_eta_m_MC=0.;
            double etaAsymMC=0.;
            for(int j=0;j<nMCtrack;j++) {
               myEvent.pxMC_mini[j] = pxMC[j];
               myEvent.pyMC_mini[j] = pyMC[j];
               myEvent.pzMC_mini[j] = pzMC[j];
               myEvent.etaMC_mini[j] = etaMC[j];
               myEvent.chargeMC_mini[j] = chargeMC[j];
               myEvent.ptStarMC_mini[j] = ptStarMC[j];
               myEvent.etaStarMC_mini[j] = etaStarMC[j];
               myEvent.phiStarMC_mini[j] = phiStarMC[j];
               myEvent.imatchMC_mini[j] = imatchMC[j];

               if( TMath::Hypot(pxMC[j],pyMC[j]) < 0.15 ) continue;
               if(etaMC[j] > 0.2 && etaMC[j] < 1.6 ) Ntracks_eta_p_MC++;
               if(etaMC[j] < 0.2 && etaMC[j] > -1.2) Ntracks_eta_m_MC++;
            } 
            etaAsymMC = (Ntracks_eta_p_MC - Ntracks_eta_m_MC)/(Ntracks_eta_p_MC + Ntracks_eta_m_MC);
            if( (Ntracks_eta_p_MC + Ntracks_eta_m_MC) == 0. ) etaAsymMC = -999.;
            myEvent.etaAsymMC_mini = etaAsymMC;
            myEvent.totalMultMC_mini = (int) (Ntracks_eta_p_MC+Ntracks_eta_m_MC);

            //gen level QED Compton
            myEvent.isQEDcMC_mini = isQEDc;
            TLorentzVector eMC, gammaMC, sumEgamma;
            eMC.SetPxPyPzE(elecPxMC,elecPyMC,elecPzMC,elecEMC);
            gammaMC.SetPxPyPzE(radPhoPxMC,radPhoPyMC,radPhoPzMC,radPhoEMC);
            sumEgamma = eMC+gammaMC;
            myEvent.sumPtMC_mini = sumEgamma.Pt();
            myEvent.eGammaPhiMC_mini = eMC.DeltaPhi( gammaMC );
            myEvent.elecPxMC_mini = eMC.Px();
            myEvent.elecPyMC_mini = eMC.Py();
            myEvent.elecPzMC_mini = eMC.Pz();
            myEvent.elecEMC_mini = eMC.E();
            myEvent.phoPxMC_mini = gammaMC.Px();
            myEvent.phoPyMC_mini = gammaMC.Py();
            myEvent.phoPzMC_mini = gammaMC.Pz();
            myEvent.phoEMC_mini = gammaMC.E();
            //end QED Compton

          }//end doGen_

         int event_pass = 1;
         int event_pass_tight = 1;
         int event_pass_loose = 1;

         /**RECO level starts here both MC and DATA**/
         if( (doGen_ && trigWeightRW <= 0) || (!doGen_ && trigWeightAC <= 0) ) event_pass = 0; //require trigger fired
         if( vertexType != 1 ) event_pass = 0;

         double Epz = hfsEREC+elecEREC - (hfsPzREC+elecPzREC);
         myEvent.EpzREC_mini = Epz;
         double elecPt = TMath::Hypot(elecPxREC,elecPyREC);
         myEvent.elecPtREC_mini = elecPt;
         myEvent.elecPzREC_mini = elecPzREC;
         myEvent.elecEREC_mini = elecEREC;
         myEvent.elecChargeREC_mini = elecChargeREC;
         double hfsPt = TMath::Hypot(hfsPxREC,hfsPyREC);
         myEvent.hfsPtREC_mini = hfsPt;
         myEvent.hfsPzREC_mini = hfsPzREC;
         myEvent.hfsEREC_mini = hfsEREC;
         //bkg finder bit cuts:
         if( (ibgREC & 1) != 0 ) event_pass = 0;
         if( (ibgREC & 2) != 0 ) event_pass = 0;
         if( (ibgREC & 4) != 0 ) event_pass = 0;
         if( (ibgREC & 8) != 0 ) event_pass = 0;
         if( (ibgREC & 16) != 0 ) event_pass = 0;
         if( (ibgREC & 32) != 0 ) event_pass = 0;
         if( (ibgREC & 64) != 0 ) event_pass = 0;  
         //kinematic cuts are not included   
         //Cut electron spatial 
         if( TMath::Hypot(elecXclusREC,elecYclusREC) > 70. || TMath::Hypot(elecXclusREC,elecYclusREC) < 15. ) event_pass = 0;
         if( elecEREC < 12. ) event_pass = 0;
         //same cuts for all eventpass
         event_pass_tight = event_pass;
         event_pass_loose = event_pass; 
         //E-pz cuts
         if( Epz > 70 || Epz < 35 ) event_pass = 0;
         if( Epz > 80 || Epz < 25 ) event_pass_loose = 0;
         if( Epz > 60 || Epz < 45 ) event_pass_tight = 0;
         //vertex cuts
         if(TMath::Abs(vertex[2]+zvtxOffset)>35.) event_pass = 0;
         if(TMath::Abs(vertex[2]+zvtxOffset)>20.) event_pass_tight = 0;
         if(TMath::Abs(vertex[2]+zvtxOffset)>50.) event_pass_loose = 0;

         //rec level QED Compton
         // we don't do anything at rec level
         //end QED Compton

         //after all event selection cuts:
         myEvent.xREC_es_mini = xREC_es;
         myEvent.yREC_es_mini = yREC_es;
         myEvent.Q2REC_es_mini = Q2REC_es;

         myEvent.vertex_mini[0] = vertex[0];
         myEvent.vertex_mini[1] = vertex[1];
         myEvent.vertex_mini[2] = vertex[2];

         myEvent.eventpass_mini = event_pass;
         myEvent.eventpassTight_mini = event_pass_tight;
         myEvent.eventpassLoose_mini = event_pass_loose;
         myEvent.nRECtrack_mini = nRECtrack;

         double Ntracks_eta_m = 0;
         double Ntracks_eta_p = 0;
         vector<double> cutVar;
         vector<int> trackType;
         //loop over reconstructed tracks:
         for(int j = 0; j<nRECtrack; j++){
            int type=typeChgREC[j];            
            if(type<0) type= -type;
           
            double phi = TMath::ATan(pyREC[j]/pxREC[j]);
            if( pxREC[j] < 0 && pyREC[j] > 0 ) phi = phi+3.14;
            if( pxREC[j] < 0 && pyREC[j] < 0 ) phi = phi-3.14;

            int pass_default = 0;
            int pass_tight = 0;
            int pass_loose = 0; 
            /*
            track quality variables are stored using arrays below
            */
            double ptREC = TMath::Hypot(pxREC[j],pyREC[j]);
            //pay attention if it is pt or ptStar
            cutVar.push_back(ptREC); cutVar.push_back(dcaPrimeREC[j]); cutVar.push_back(trkThetaREC[j]);
            cutVar.push_back(startHitsRadiusREC[j]); cutVar.push_back(endHitsRadiusREC[j]); cutVar.push_back((double)vtxNHitsREC[j]);
            cutVar.push_back(elecThetaREC); cutVar.push_back(nucliaREC[j]); cutVar.push_back(pREC[j]);
            cutVar.push_back(peREC[j]); cutVar.push_back(chi2vtxREC[j]); cutVar.push_back(chi2LinkREC[j]);
            cutVar.push_back(zLengthHitREC[j]); cutVar.push_back(rZeroREC[j]); cutVar.push_back(chi2TrkREC[j]);

            trackType.push_back(type); trackType.push_back((int)doComb_);
            trackType.push_back( (int)doFwd_ );

            pass_tight = getPassFlag(trackType, cutVar, 0);
            pass_default = getPassFlag(trackType, cutVar, 1);
            pass_loose = getPassFlag(trackType, cutVar, 2);

            trackType.clear();
            cutVar.clear();

            if( pass_default ){
               if(etaREC[j] > 0.2 && etaREC[j] < 1.6 ) Ntracks_eta_p++;
               if(etaREC[j] < 0.2 && etaREC[j] > -1.2) Ntracks_eta_m++;
            }

            //filling 1D histogram for Rstart and DCA for + and - tracks
            if( event_pass == 1 ){
               if( pass_default == 1 ){
                  if( typeChgREC[j] > 0 ) h_RstartPos[0]->Fill( startHitsRadiusREC[j], evt_weight );
                  if( typeChgREC[j] < 0 ) h_RstartNeg[0]->Fill( startHitsRadiusREC[j], evt_weight );
                  if( typeChgREC[j] > 0 ) h_dcaPos[0]->Fill( dcaPrimeREC[j], evt_weight );
                  if( typeChgREC[j] < 0 ) h_dcaNeg[0]->Fill( dcaPrimeREC[j], evt_weight );
               }
               if( pass_tight == 1 ){
                  if( typeChgREC[j] > 0 ) h_RstartPos[1]->Fill( startHitsRadiusREC[j], evt_weight );
                  if( typeChgREC[j] < 0 ) h_RstartNeg[1]->Fill( startHitsRadiusREC[j], evt_weight );
                  if( typeChgREC[j] > 0 ) h_dcaPos[1]->Fill( dcaPrimeREC[j], evt_weight );
                  if( typeChgREC[j] < 0 ) h_dcaNeg[1]->Fill( dcaPrimeREC[j], evt_weight );
               }
               if( pass_loose == 1 ){
                  if( typeChgREC[j] > 0 ) h_RstartPos[2]->Fill( startHitsRadiusREC[j], evt_weight );
                  if( typeChgREC[j] < 0 ) h_RstartNeg[2]->Fill( startHitsRadiusREC[j], evt_weight );
                  if( typeChgREC[j] > 0 ) h_dcaPos[2]->Fill( dcaPrimeREC[j], evt_weight );
                  if( typeChgREC[j] < 0 ) h_dcaNeg[2]->Fill( dcaPrimeREC[j], evt_weight );
               }
                  if( typeChgREC[j] > 0 ) h_RstartPos[3]->Fill( startHitsRadiusREC[j], evt_weight );
                  if( typeChgREC[j] < 0 ) h_RstartNeg[3]->Fill( startHitsRadiusREC[j], evt_weight );
                  if( typeChgREC[j] > 0 ) h_dcaPos[3]->Fill( dcaPrimeREC[j], evt_weight );
                  if( typeChgREC[j] < 0 ) h_dcaNeg[3]->Fill( dcaPrimeREC[j], evt_weight );
            }

            //assign values to each branch on track levels:
            myEvent.typeChgREC_mini[j] = typeChgREC[j];

            myEvent.pxREC_mini[j] = pxREC[j];
            myEvent.pyREC_mini[j] = pyREC[j];
            myEvent.pzREC_mini[j] = pzREC[j];

            myEvent.pREC_mini[j] = pREC[j];
            myEvent.peREC_mini[j] = peREC[j];
            myEvent.etaREC_mini[j] = etaREC[j];
            myEvent.phiREC_mini[j] = phi;
            myEvent.etaStarREC_mini[j] = etaStarREC[j];
            myEvent.ptStarREC_mini[j] = ptStarREC[j];
            myEvent.phiStarREC_mini[j] = phiStarREC[j];
            // double eff_error = 0.995;
            // if( type == 2 ) eff_error = 0.9;
            // myEvent.nucliaREC_mini[j] = nucliaREC[j]*eff_error;
            myEvent.nucliaREC_mini[j] = nucliaREC[j];
            myEvent.dmatchREC_mini[j] = dmatchREC[j];
            myEvent.imatchREC_mini[j] = imatchREC[j];       
            myEvent.passREC_mini[j] = pass_default; 
            myEvent.passTightREC_mini[j] = pass_tight;
            myEvent.passLooseREC_mini[j] = pass_loose;      
         }

         double etaAsym = (Ntracks_eta_p - Ntracks_eta_m)/(Ntracks_eta_p + Ntracks_eta_m);
         if( (Ntracks_eta_p + Ntracks_eta_m) == 0 ) etaAsym = -999.;
         myEvent.etaAsymREC_mini = etaAsym;
         myEvent.totalMultREC_mini = (int) (Ntracks_eta_p + Ntracks_eta_m);

         // outtree->Fill();

         totalEvents++;
         if( totalEvents%100000 == 0 )cout << "Events ~ " << totalEvents << endl;

      }
      cout << "Number of events processed ~ " << totalEvents << endl;  
   }


   TString outfile_name;

   if( !doReweight_ ){
      if( doRapgap_ && doGen_ ){
            outfile_name = Form("../new_output/mc_highE_RAPGAP_noReweight_Tree_%d.root",start);
      }
      else if( !doRapgap_ && doGen_ ){
            outfile_name = Form("../new_output/mc_highE_DJANGOH_noReweight_Tree_%d.root",start);
      }
      else{
            outfile_name = Form("../new_output/data_highE_0607_noReweight_Tree_%d.root",start);
      }
   }
   else{
      if( doRapgap_ && doGen_ ){
            outfile_name = "../new_output/mc_highE_RAPGAP_fullReweight_Tree.root";
      }
      else if( !doRapgap_ && doGen_ ){
            outfile_name = "../new_output/mc_highE_DJANGOH_fullReweight_Tree.root";
      }
      else{
            cout << "don't reweight data! " << endl;
            outfile_name = "../new_output/data_highE_0607_noReweight_Tree.root";
      }
   }
   
   TFile outfile( outfile_name, "RECREATE");
   
   outtree->Write();
   for(int i=0;i<4;i++){
      h_RstartPos[i]->Write();
      h_RstartNeg[i]->Write();
      h_dcaPos[i]->Write();
      h_dcaNeg[i]->Write();
   }
   
   
}
