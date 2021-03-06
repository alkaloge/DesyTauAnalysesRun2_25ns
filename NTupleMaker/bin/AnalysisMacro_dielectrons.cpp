#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <sstream>

#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "TTree.h"
#include "TROOT.h"
#include "TLorentzVector.h"
#include "TVector3.h"
#include "TRFIOFile.h"
#include "TH1D.h"
#include "TChain.h"
#include "TGraphAsymmErrors.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include "TRandom.h"

#include "DesyTauAnalyses/NTupleMaker/interface/Config.h"
#include "DesyTauAnalyses/NTupleMaker/interface/AC1B.h"
#include "DesyTauAnalyses/NTupleMaker/interface/json.h"
#include "DesyTauAnalyses/NTupleMaker/interface/PileUp.h"
#include "DesyTauAnalyses/NTupleMaker/interface/Jets.h"
#include "DesyTauAnalyses/NTupleMaker/interface/ScaleFactor.h"

#include "DesyTauAnalyses/NTupleMaker/interface/functions.h"

int main(int argc, char * argv[]) {

  // first argument - config file 
  // second argument - filelist

  using namespace std;

  // **** configuration
  Config cfg(argv[1]);

  const bool isData = cfg.get<bool>("IsData");
  const bool applyGoodRunSelection = cfg.get<bool>("ApplyGoodRunSelection");

  // pile up reweighting
  const bool applyPUreweighting_vertices = cfg.get<bool>("ApplyPUreweighting_vertices");
  const bool applyPUreweighting_official = cfg.get<bool>("ApplyPUreweighting_official");

  const bool applyLeptonSF = cfg.get<bool>("ApplyLeptonSF");

  // kinematic cuts on electron
  const float ptElectronLowCut   = cfg.get<float>("ptElectronLowCut");
  const float ptElectronHighCut  = cfg.get<float>("ptElectronHighCut");
  const float etaElectronCut     = cfg.get<float>("etaElectronCut");
  const float etaElectronHighCut = cfg.get<float>("etaElectronHighCut");
  const float dxyElectronCut     = cfg.get<float>("dxyElectronCut");
  const float dzElectronCut      = cfg.get<float>("dzElectronCut");
  const float dxyElectronLooseCut     = cfg.get<float>("dxyElectronLooseCut");
  const float dzElectronLooseCut      = cfg.get<float>("dzElectronLooseCut");
  const float isoElectronCut     = cfg.get<float>("isoElectronCut");
  const float isoElectronProbeCut = cfg.get<float>("isoElectronProbeCut");
  const unsigned int electronIdType  = cfg.get<unsigned int>("ElectronIdType");

  // topological cuts
  const float dRleptonsCut   = cfg.get<float>("dRleptonsCut");
  const float dPhileptonsCut = cfg.get<float>("dPhileptonsCut");
  const float DRTrigMatch    = cfg.get<float>("DRTrigMatch");
  const bool  oppositeSign   = cfg.get<bool>("OppositeSign");
  const float dielectronMassCut = cfg.get<float>("DielectronMassCut");
  const bool isoDR03         = cfg.get<bool>("IsoDR03");

  // jet related cuts
  const float jetEtaCut      = cfg.get<float>("JetEtaCut");
  const float jetEtaTrkCut   = cfg.get<float>("JetEtaTrkCut");
  const float jetPtHighCut   = cfg.get<float>("JetPtHighCut");
  const float jetPtLowCut    = cfg.get<float>("JetPtLowCut");
  const float dRJetLeptonCut = cfg.get<float>("dRJetLeptonCut");

  //trigger
  const bool applyTrigger = cfg.get<bool>("ApplyTrigger");
  const string electronHLTName = cfg.get<string>("ElectronHLTName");
  const string electronHLTFilterName = cfg.get<string>("ElectronHLTFilterName");
  const string electronEle23FilterName = cfg.get<string>("ElectronEle23FilterName");
  const string electronEle17FilterName = cfg.get<string>("ElectronEle17FilterName");
  const string electronEle12FilterName = cfg.get<string>("ElectronEle12FilterName");
  const string electronSingleEleFilterName = cfg.get<string>("ElectronSingleEleFilterName");

  const float singleEleTriggerPtCut = cfg.get<float>("SingleEleTriggerPtCut");
  const float singleEleTriggerEtaCut = cfg.get<float>("SingleEleTriggerEtaCut");
  const float eleTriggerPtCut = cfg.get<float>("eleTriggerPtCut");
  const float eleTriggerEtaCut = cfg.get<float>("eleTriggerEtaCut");

  TString ElectronHLTName(electronHLTName);
  TString ElectronHLTFilterName(electronHLTFilterName);
  TString ElectronEle23FilterName(electronEle23FilterName);
  TString ElectronEle17FilterName(electronEle17FilterName);
  TString ElectronEle12FilterName(electronEle12FilterName);
  TString ElectronSingleEleFilterName(electronSingleEleFilterName);

  // vertex cuts
  const float ndofVertexCut  = cfg.get<float>("NdofVertexCut");   
  const float zVertexCut     = cfg.get<float>("ZVertexCut");
  const float dVertexCut     = cfg.get<float>("DVertexCut");

  // vertex distributions filenames and histname
  const string vertDataFileName = cfg.get<string>("VertexDataFileName");
  const string vertMcFileName   = cfg.get<string>("VertexMcFileName");
  const string vertHistName     = cfg.get<string>("VertexHistName");

  const string ElectronIdIsoFile = cfg.get<string>("ElectronIdIsoEff");

  const string jsonFile = cfg.get<string>("jsonFile");
  // **** end of configuration
  

  string cmsswBase = (getenv ("CMSSW_BASE"));
  string fullPathToJsonFile = cmsswBase + "/src/DesyTauAnalyses/NTupleMaker/test/json/" + jsonFile;

  // Run-lumi selector
  std::vector<Period> periods;  
  if (isData) { // read the good runs 
    std::fstream inputFileStream(fullPathToJsonFile.c_str(), std::ios::in);
    if (inputFileStream.fail() ) {
      std::cout << "Error: cannot find json file " << fullPathToJsonFile << std::endl;
      std::cout << "please check" << std::endl;
      std::cout << "quitting program" << std::endl;
      exit(-1);
    }
  
    for(std::string s; std::getline(inputFileStream, s); ) {
      periods.push_back(Period());
      std::stringstream ss(s);
      ss >> periods.back();
    }
  }

  // file name and tree name
  std::string rootFileName(argv[2]);
  std::ifstream fileList(argv[2]);
  std::ifstream fileList0(argv[2]);
  std::string ntupleName("makeroottree/AC1B");
  std::string initNtupleName("initroottree/AC1B");

  TString TStrName(rootFileName);
  std::cout <<TStrName <<std::endl; 

  // output fileName with histograms
  TFile * file = new TFile(TStrName+TString(".root"),"recreate");
  file->cd("");

  TH1D * histWeightsH = new TH1D("histWeightsH","",1,-0.5,0.5);
  TH1D * inputEventsH = new TH1D("inputEventsH","",1,-0.5,0.5);
  TH1D * histWeightsSkimmedH = new TH1D("histWeightsSkimmedH","",1,-0.5,0.5);

  TH1D * massSelH = new TH1D("massSelH","",200,0,200);
  TH1D * massSelLargeRangeH = new TH1D("massSelLargeRangeH","",2000,0,2000);
  // Histograms after final selection
  TH1D * ptLeadingEleSelH = new TH1D("ptLeadingEleSelH","",100,0,200);
  TH1D * ptTrailingEleSelH = new TH1D("ptTrailingEleSelH","",100,0,200);
  TH1D * etaLeadingEleSelH = new TH1D("etaLeadingEleSelH","",50,-2.5,2.5);
  TH1D * etaTrailingEleSelH = new TH1D("etaTrailingEleSelH","",50,-2.5,2.5);
  TH1D * metSelH = new TH1D("metSelH","",200,0.,400.);
  TH1D * puppimetSelH = new TH1D("puppiMetSelH","",200,0.,400.);


  TString scales[21] = {"M10","M9","M8","M7","M6","M5","M4","M3","M2","M1","0",
			"P1","P2","P3","P4","P5","P6","P7","P8","P9","P10"};

  TH1D * massSelScaleH[21];
  TH1D * metSelScaleH[21];
  TH1D * puppimetSelScaleH[21];
  for (int iScale=0; iScale<21; ++iScale) {    
    massSelScaleH[iScale] = new TH1D("massSel"+scales[iScale]+"H","",200,0,200);
    metSelScaleH[iScale] = new TH1D("metSel"+scales[iScale]+"H","",200,0,400);
    puppimetSelScaleH[iScale] = new TH1D("puppiMetSel"+scales[iScale]+"H","",200,0,400);
  }


  TH1D * nJets30SelH    = new TH1D("nJets30SelH","",11,-0.5,10.5);
  TH1D * nJets30etaCutSelH = new TH1D("nJets30etaCutSelH","",11,-0.5,10.5);
  TH1D * nJets20SelH    = new TH1D("nJets20SelH","",11,-0.5,10.5);
  TH1D * nJets20etaCutSelH = new TH1D("nJets20etaCutSelH","",11,-0.5,10.5);

  TH1D * HT30SelH       = new TH1D("HT30SelH","",50,0,500);
  TH1D * HT30etaCutSelH = new TH1D("HT30etaCutSelH","",50,0,500);
  TH1D * HT20SelH       = new TH1D("HT20SelH","",50,0,500);
  TH1D * HT20etaCutSelH = new TH1D("HT20etaCutSelH","",50,0,500);
  
  TH1F * NumberOfVerticesH = new TH1F("NumberOfVerticesH","",51,-0.5,50.5);
  
  TH1D * EleSF_IdIso_Ele1H = new TH1D("EleIdIsoSF_Ele1H", "EleIdIsoSF_Ele1", 100, 0.5,1.5);
  TH1D * EleSF_IdIso_Ele2H = new TH1D("EleIdIsoSF_Ele2H", "EleIdIsoSF_Ele2", 100, 0.5,1.5);

  int nPtBins = 6;
  float ptBins[7] = {13,20,25,30,40,60,1000};

  int nPtBinsTrig = 16;
  float ptBinsTrig[17] = {10,
			  13,
			  16,
			  19,
			  22,
			  25,
			  28,
			  31,
			  34,
			  37,
			  40,
			  45,
			  50,
			  60,
			  70,
			  100,
			  1000};  
  
  int nEtaBins = 2;
  float etaBins[3] = {0,1.48,2.5}; 
  
  TString PtBins[6] = {"Pt13to20",
		       "Pt20to25",
		       "Pt25to30",
		       "Pt30to40",
		       "Pt40to60",
		       "PtGt60"};
  

  TString EtaBins[2] = {"EtaLt1p48",
			"EtaGt1p48"};

  TString PtBinsTrig[16] = {"Pt10to13",
			    "Pt13to16",
			    "Pt16to19",
			    "Pt19to22",
			    "Pt22to25",
			    "Pt25to28",
			    "Pt28to31",
			    "Pt31to34",
			    "Pt34to37",
			    "Pt37to40",
			    "Pt40to45",
			    "Pt45to50",
			    "Pt50to60",
			    "Pt60to70",
			    "Pt70to100",
			    "PtGt100"};

  TString JetBins[3] = {"Jet0","Jet1","JetGe2"};

  //*****  create eta histogram with eta ranges associated to their names (eg. endcap, barrel)   ***** //



  TH1F * etaBinsH = new TH1F("etaBinsH", "etaBinsH", nEtaBins, etaBins);
  etaBinsH->Draw();
  etaBinsH->GetXaxis()->Set(nEtaBins, etaBins);
  for (int i=0; i<nEtaBins; i++){ etaBinsH->GetXaxis()->SetBinLabel(i+1, EtaBins[i]);}
  etaBinsH->Draw();
  file->cd();
  etaBinsH->Write("etaBinsH");

  //*****  create pt histogram_s with pt ranges associated to their names (eg. Pt10to13, ..)   ***** //
  //*****  two different pT binning, one for IdIso and one for trigger   ***** //

  TH1D * ptBinsH =  new TH1D("ptBinsH", "ptBinsH", nPtBins, ptBins);
  ptBinsH->Draw();
  ptBinsH->GetXaxis()->Set(nPtBins, ptBins);
  for (int i=0; i<nPtBins; i++){ ptBinsH->GetXaxis()->SetBinLabel(i+1, PtBins[i]);}
  ptBinsH->Draw();
  file->cd();
  ptBinsH->Write("ptBinsH");

  TH1D * ptBinsTrigH =  new TH1D("ptBinsTrigH", "ptBinsTrigH", nPtBinsTrig, ptBinsTrig);
  ptBinsTrigH->Draw();
  ptBinsTrigH->GetXaxis()->Set(nPtBinsTrig, ptBinsTrig);
  for (int i=0; i<nPtBinsTrig; i++){ ptBinsTrigH->GetXaxis()->SetBinLabel(i+1, PtBinsTrig[i]);}
  ptBinsTrigH->Draw();
  file->cd();
  ptBinsTrigH->Write("ptBinsTrigH");

  TH1D * ZMassPass = new TH1D("ZMassPass","",80,50,130);
  TH1D * ZMassFail = new TH1D("ZMassFail","",80,50,130);

  TH1F * ZMassJetEtaPtPass[2][3][6];
  TH1F * ZMassJetEtaPtFail[2][3][6];

  TH1F * ZMassEtaPtPass[2][6];
  TH1F * ZMassEtaPtFail[2][6];

  TH1F * PromptPtPass[2];
  TH1F * PromptPtFail[2];

  TH1F * NonPromptPtPass[2];
  TH1F * NonPromptPtFail[2];

  TH1F * PromptSelPtPass[2];
  TH1F * PromptSelPtFail[2];

  TH1F * NonPromptSelPtPass[2];
  TH1F * NonPromptSelPtFail[2];

  TH1F * PromptSelJetPtPass[2][3];
  TH1F * PromptSelJetPtFail[2][3];

  TH1F * NonPromptSelJetPtPass[2][3];
  TH1F * NonPromptSelJetPtFail[2][3];

  TH1F * ZMassEle23EtaPtPass[2][16];
  TH1F * ZMassEle23EtaPtFail[2][16];

  TH1F * ZMassEle17EtaPtPass[2][16];
  TH1F * ZMassEle17EtaPtFail[2][16];

  TH1F * ZMassEle12EtaPtPass[2][16];
  TH1F * ZMassEle12EtaPtFail[2][16];

  TH1F * ZMassIsoEleEtaPtPass[2][16];
  TH1F * ZMassIsoEleEtaPtFail[2][16];

  for (int iEta=0; iEta<nEtaBins; ++iEta) {
    PromptPtPass[iEta] = new TH1F("PromptPt"+EtaBins[iEta]+"Pass","",nPtBins,ptBins);
    PromptPtFail[iEta] = new TH1F("PromptPt"+EtaBins[iEta]+"Fail","",nPtBins,ptBins);
    NonPromptPtPass[iEta] = new TH1F("NonPromptPt"+EtaBins[iEta]+"Pass","",nPtBins,ptBins);
    NonPromptPtFail[iEta] = new TH1F("NonPromptPt"+EtaBins[iEta]+"Fail","",nPtBins,ptBins);
    PromptSelPtPass[iEta] = new TH1F("PromptSelPt"+EtaBins[iEta]+"Pass","",nPtBins,ptBins);
    PromptSelPtFail[iEta] = new TH1F("PromptSelPt"+EtaBins[iEta]+"Fail","",nPtBins,ptBins);
    NonPromptSelPtPass[iEta] = new TH1F("NonPromptSelPt"+EtaBins[iEta]+"Pass","",nPtBins,ptBins);
    NonPromptSelPtFail[iEta] = new TH1F("NonPromptSelPt"+EtaBins[iEta]+"Fail","",nPtBins,ptBins);
    for (int iJet=0; iJet<3; ++iJet) {
      PromptSelJetPtPass[iEta][iJet] = new TH1F("PromptSelPt"+EtaBins[iEta]+JetBins[iJet]+"Pass","",nPtBins,ptBins);
      PromptSelJetPtFail[iEta][iJet] = new TH1F("PromptSelPt"+EtaBins[iEta]+JetBins[iJet]+"Fail","",nPtBins,ptBins);
      NonPromptSelJetPtPass[iEta][iJet] = new TH1F("NonPromptSelPt"+EtaBins[iEta]+JetBins[iJet]+"Pass","",nPtBins,ptBins);
      NonPromptSelJetPtFail[iEta][iJet] = new TH1F("NonPromptSelPt"+EtaBins[iEta]+JetBins[iJet]+"Fail","",nPtBins,ptBins);
    }
    for (int iPt=0; iPt<nPtBins; ++iPt) {
      ZMassEtaPtPass[iEta][iPt] = new TH1F("ZMass"+EtaBins[iEta]+PtBins[iPt]+"Pass","",80,50,130);
      ZMassEtaPtFail[iEta][iPt] = new TH1F("ZMass"+EtaBins[iEta]+PtBins[iPt]+"Fail","",80,50,130);
      for (int iJet=0; iJet<3; ++iJet) {
	ZMassJetEtaPtPass[iEta][iJet][iPt] = new TH1F("ZMass"+EtaBins[iEta]+JetBins[iJet]+PtBins[iPt]+"Pass","",80,50,130);
	ZMassJetEtaPtFail[iEta][iJet][iPt] = new TH1F("ZMass"+EtaBins[iEta]+JetBins[iJet]+PtBins[iPt]+"Fail","",80,50,130);
      }
    }
    for (int iPt=0; iPt<nPtBinsTrig; ++iPt) {
      ZMassEle23EtaPtPass[iEta][iPt] = new TH1F("ZMassEle23"+EtaBins[iEta]+PtBinsTrig[iPt]+"Pass","",80,50,130);
      ZMassEle23EtaPtFail[iEta][iPt] = new TH1F("ZMassEle23"+EtaBins[iEta]+PtBinsTrig[iPt]+"Fail","",80,50,130);
      ZMassEle17EtaPtPass[iEta][iPt] = new TH1F("ZMassEle17"+EtaBins[iEta]+PtBinsTrig[iPt]+"Pass","",80,50,130);
      ZMassEle17EtaPtFail[iEta][iPt] = new TH1F("ZMassEle17"+EtaBins[iEta]+PtBinsTrig[iPt]+"Fail","",80,50,130);
      ZMassEle12EtaPtPass[iEta][iPt] = new TH1F("ZMassEle12"+EtaBins[iEta]+PtBinsTrig[iPt]+"Pass","",80,50,130);
      ZMassEle12EtaPtFail[iEta][iPt] = new TH1F("ZMassEle12"+EtaBins[iEta]+PtBinsTrig[iPt]+"Fail","",80,50,130);
      ZMassIsoEleEtaPtPass[iEta][iPt] = new TH1F("ZMassIsoEle"+EtaBins[iEta]+PtBinsTrig[iPt]+"Pass","",80,50,130);
      ZMassIsoEleEtaPtFail[iEta][iPt] = new TH1F("ZMassIsoEle"+EtaBins[iEta]+PtBinsTrig[iPt]+"Fail","",80,50,130);
    }
  }

  TH1D * PUweightsOfficialH = new TH1D("PUweightsOfficialH","PU weights w/ official reweighting",1000, 0, 10);

  // PILE UP REWEIGHTING - OPTIONS

  if (applyPUreweighting_vertices and applyPUreweighting_official) 
	{std::cout<<"ERROR: Choose only ONE PU reweighting method (vertices or official, not both!) " <<std::endl; exit(-1);}

  // reweighting with vertices

  // reading vertex weights
  TFile * fileDataNVert = new TFile(TString(cmsswBase)+"/src/"+vertDataFileName);
  TFile * fileMcNVert   = new TFile(TString(cmsswBase)+"/src/"+vertMcFileName);

  TH1F * hvertWeight = new TH1F("hvertWeight","",40,0,1);
  TH1F * hNvert = new TH1F("hNvert","",51,-0.5,50.5);
  
  TH1D *hNvertData = (TH1D*)fileDataNVert->Get(TString(vertHistName));
  TH1D *hNvertMC =(TH1D*)fileMcNVert->Get(TString(vertHistName));
  Float_t normData = hNvertData->GetSumOfWeights();   
  Float_t normMC =  hNvertMC->GetSumOfWeights();
  hNvertData->Scale(1/normData);
  hNvertMC->Scale(1/normMC);


  // reweighting official recipe 
  // initialize pile up object
  PileUp * PUofficial = new PileUp();
  
  if (applyPUreweighting_official) {
    TFile * filePUdistribution_data = new TFile(TString(cmsswBase)+"/src/DesyTauAnalyses/NTupleMaker/data/PileUpDistrib/Data_Pileup_2015D_Nov17.root","read"); 
    TFile * filePUdistribution_MC = new TFile (TString(cmsswBase)+"/src/DesyTauAnalyses/NTupleMaker/data/PileUpDistrib/MC_Spring15_PU25_Startup.root", "read"); 
    TH1D * PU_data = (TH1D *)filePUdistribution_data->Get("pileup");
    TH1D * PU_mc = (TH1D *)filePUdistribution_MC->Get("pileup");
    PUofficial->set_h_data(PU_data); 
    PUofficial->set_h_MC(PU_mc);
  }

// Lepton Scale Factors 

  ScaleFactor * SF_electronIdIso; 
  if (applyLeptonSF) {
    SF_electronIdIso = new ScaleFactor();
    SF_electronIdIso->init_ScaleFactor(TString(cmsswBase)+"/src/"+TString(ElectronIdIsoFile));
  }
  
  int nFiles = 0;
  int nEvents = 0;
  int selEventsDielectrons = 0;
  int nTotalFiles = 0;
  std::string dummy;
  // count number of files --->
  while (fileList0 >> dummy) nTotalFiles++;

  unsigned int RunMin = 99999999;
  unsigned int RunMax = 0;

  std::vector<unsigned int> allRuns; allRuns.clear();
		
  for (int iF=0; iF<nTotalFiles; ++iF) {

    std::string filen;
    fileList >> filen;
    
    std::cout << "file " << iF+1 << " out of " << nTotalFiles << " filename : " << filen << std::endl;
    TFile * file_ = TFile::Open(TString(filen));
    if (file_->IsZombie()) {std::cout << "Failed to open file "<< filen << std::endl; exit(-1);} 

    TH1D * histoInputEvents = NULL;
    histoInputEvents = (TH1D*)file_->Get("makeroottree/nEvents");
    if (histoInputEvents==NULL) {
      cout << "No histogram makeroottree/nEvents is found, skipping file" << endl;
      continue;
    }
    int NE = int(histoInputEvents->GetEntries());
    for (int iE=0;iE<NE;++iE)
      inputEventsH->Fill(0.);
    std::cout << "      number of input events         = " << NE << std::endl;

    TTree * _inittree = NULL;
    _inittree = (TTree*)file_->Get(TString(initNtupleName));
    if (_inittree==NULL) { 
      cout << "No " << initNtupleName << " is found, skipping file" << endl;
      continue;
    }
    Float_t genweight;
    if (!isData)
      _inittree->SetBranchAddress("genweight",&genweight);
    Long64_t numberOfEntriesInitTree = _inittree->GetEntries();
    std::cout << "      number of entries in Init Tree = " << numberOfEntriesInitTree << std::endl;
    for (Long64_t iEntry=0; iEntry<numberOfEntriesInitTree; iEntry++) {
      _inittree->GetEntry(iEntry);
      if (isData) 
	histWeightsH->Fill(0.,1.);
      else
	histWeightsH->Fill(0.,genweight);
    }
	
    TTree * _tree = NULL;
    _tree = (TTree*)file_->Get(TString(ntupleName));
    if (_tree==NULL) { 
      cout << "No " << ntupleName << " is found, skipping file" << endl;
      continue;
    }
    Long64_t numberOfEntries = _tree->GetEntries();
    std::cout << "      number of entries in Tree      = " << numberOfEntries << std::endl;
    AC1B analysisTree(_tree);
  
    // EVENT LOOP //
    
    for (Long64_t iEntry=0; iEntry<numberOfEntries; iEntry++) { 

      analysisTree.GetEntry(iEntry);
      nEvents++;

      if (nEvents%10000==0) 
	cout << "      processed " << nEvents << " events" << endl; 

      
      float weight = 1;

      if (!isData) {
	weight *= analysisTree.genweight;
	hNvert->Fill(analysisTree.primvertex_count,weight);
      }
      histWeightsSkimmedH->Fill(float(0),weight);

      // PU reweighting with vertices 
      if (!isData && applyPUreweighting_vertices) {
	
	int binNvert = hNvert->FindBin(analysisTree.primvertex_count);
	float_t dataNvert = hNvertData->GetBinContent(binNvert);
	float_t mcNvert = hNvertMC->GetBinContent(binNvert);
	if (mcNvert < 1e-10){mcNvert=1e-10;}
	float_t vertWeight = dataNvert/mcNvert;
	hvertWeight->Fill(vertWeight);
	weight *= vertWeight;
	//	cout << "NVert = " << analysisTree.primvertex_count << "  : " << vertWeight << endl;
      }

      // PU reweighting with Ninteractions (official recipe) 
      if (!isData && applyPUreweighting_official) {
	double Ninteractions = analysisTree.numtruepileupinteractions;
	double PUweight = PUofficial->get_PUweight(Ninteractions);
	weight *= PUweight;
	PUweightsOfficialH->Fill(PUweight);
	}

      if (isData && applyGoodRunSelection){

     	bool lumi = false;
        int n=analysisTree.event_run;
        int lum = analysisTree.event_luminosityblock;
	
	std::string num = std::to_string(n);
	std::string lnum = std::to_string(lum);
	for(const auto& a : periods)
	  {
	    
	    if ( num.c_str() ==  a.name ) {
	      //	      std::cout<< " Eureka "<<num<<"  "<<a.name<<" ";
	      //std::cout <<"min "<< last->lower << "- max last " << last->bigger << std::endl;
	      
	      for(auto b = a.ranges.begin(); b != std::prev(a.ranges.end()); ++b) {
		
		//   cout<<b->lower<<"  "<<b->bigger<<endl;
                if (lum  >= b->lower && lum <= b->bigger ) lumi = true;

	      }
	      auto last = std::prev(a.ranges.end());
	      // std::cout <<"min "<< last->lower << "- max last " << last->bigger << std::endl;
	      if (  (lum >=last->lower && lum <= last->bigger )) lumi=true;
	      

	    }
	    
	  }
	if (!lumi) continue;
	
      }

      
      if (analysisTree.event_run<RunMin)
	RunMin = analysisTree.event_run;
      
      if (analysisTree.event_run>RunMax)
	RunMax = analysisTree.event_run;
      
      bool isNewRun = true;
      if (allRuns.size()>0) {
	for (unsigned int iR=0; iR<allRuns.size(); ++iR) {
	  if (analysisTree.event_run==allRuns.at(iR)) {
	    isNewRun = false;
	    break;
	  }
	}
      }
	
      if (isNewRun) 
	allRuns.push_back(analysisTree.event_run);

      bool isTriggerElectron = false;
      for (std::map<string,int>::iterator it=analysisTree.hltriggerresults->begin(); it!=analysisTree.hltriggerresults->end(); ++it) {
	TString trigName(it->first);
	if (trigName.Contains(ElectronHLTName)) {
	  //	  std::cout << it->first << " : " << it->second << std::endl;
	  if (it->second==1)
            isTriggerElectron = true;
	}
      }

      if (applyTrigger && !isTriggerElectron) continue;

      unsigned int nElectronFilter = 0;
      bool isElectronFilter = false;
      
      unsigned int nEle23Filter = 0;
      bool isEle23Filter = false;
      
      unsigned int nEle17Filter = 0;
      bool isEle17Filter = false;
      
      unsigned int nEle12Filter = 0;
      bool isEle12Filter = false;
      
      unsigned int nSingleEleFilter = 0;
      bool isSingleEleFilter = false;
      
      unsigned int nfilters = analysisTree.run_hltfilters->size();
      for (unsigned int i=0; i<nfilters; ++i) {
        TString HLTFilter(analysisTree.run_hltfilters->at(i));
	if (HLTFilter==ElectronHLTFilterName) {
	  nElectronFilter = i;
	  isElectronFilter = true;
	}
	if (HLTFilter==ElectronEle23FilterName) {
	  nEle23Filter = i;
	  isEle23Filter = true;
	}
	if (HLTFilter==ElectronEle17FilterName) {
	  nEle17Filter = i;
	  isEle17Filter = true;
	}
	if (HLTFilter==ElectronEle12FilterName) {
	  nEle12Filter = i;
	  isEle12Filter = true;
	}
	if (HLTFilter==ElectronSingleEleFilterName) {
	  nSingleEleFilter = i;
	  isSingleEleFilter = true;
	}
      }

      if (!isElectronFilter) {
	cout << "Filter " << ElectronHLTFilterName << " not found" << endl;
	exit(-1);
      }
      if (!isEle23Filter) {
	cout << "Filter " << ElectronEle23FilterName << " not found" << endl;
	exit(-1);
      }
      if (!isEle17Filter) {
	cout << "Filter " << ElectronEle17FilterName << " not found" << endl;
	exit(-1);
      }
      if (!isEle12Filter) {
	cout << "Filter " << ElectronEle12FilterName << " not found" << endl;
	exit(-1);
      }
      if (!isSingleEleFilter) {
	cout << "Filter " << ElectronSingleEleFilterName << " not found" << endl;
	exit(-1);
      }

      float pfmet_ex = analysisTree.pfmet_ex;
      float pfmet_ey = analysisTree.pfmet_ey;
      float pfmet_phi = analysisTree.pfmet_phi;
      float pfmet = TMath::Sqrt(pfmet_ex*pfmet_ex+pfmet_ey*pfmet_ey);
      float puppimet_ex = analysisTree.puppimet_ex;
      float puppimet_ey = analysisTree.puppimet_ey;
      float puppimet_phi = analysisTree.puppimet_phi;
      float puppimet = TMath::Sqrt(puppimet_ex*puppimet_ex+puppimet_ey*puppimet_ey);


      // vertex cuts
      //      if (fabs(analysisTree.primvertex_z)>zVertexCut) continue;
      //      if (analysisTree.primvertex_ndof<ndofVertexCut) continue;
      //      float dVertex = (analysisTree.primvertex_x*analysisTree.primvertex_x+
      //		       analysisTree.primvertex_y*analysisTree.primvertex_y);
      //      if (dVertex>dVertexCut) continue;
     
      // electron selection
      vector<unsigned int> allElectrons; allElectrons.clear();
      vector<unsigned int> isoIdElectrons; isoIdElectrons.clear();
      vector<bool> allElectronsIsLeg23Matched; allElectronsIsLeg23Matched.clear();
      vector<bool> allElectronsIsLeg17Matched; allElectronsIsLeg17Matched.clear();
      vector<bool> allElectronsIsLeg12Matched; allElectronsIsLeg12Matched.clear();
      vector<bool> allElectronsIsLegSingleEleMatched; allElectronsIsLegSingleEleMatched.clear();


      vector<bool> allElectronsIsTriggerMatched; allElectronsIsTriggerMatched.clear();
      vector<bool> isoIdElectronsIsTriggerMatched; isoIdElectronsIsTriggerMatched.clear();

      vector<float> allElectronsIso; allElectronsIso.clear();
      vector<float> isoIdElectronsIso; isoIdElectronsIso.clear();

      vector<bool> isElectronPassedIdIso; isElectronPassedIdIso.clear();

      for (unsigned int im = 0; im<analysisTree.electron_count; ++im) {

	// selecting sample of probes
	if (analysisTree.electron_pt[im]<ptBins[0]) continue;
	if (fabs(analysisTree.electron_eta[im])>etaBins[nEtaBins]) continue;
	if (fabs(analysisTree.electron_dxy[im])>dxyElectronLooseCut) continue;
	if (fabs(analysisTree.electron_dz[im])>dzElectronLooseCut) continue;

	bool electronTriggerMatch = false;
	bool electronEle23Match = false;
	bool electronEle17Match = false;
	bool electronEle12Match = false;
	bool electronSingleEleMatch = false;
	for (unsigned int iT=0; iT<analysisTree.trigobject_count; ++iT) {
	  float dRtrig = deltaR(analysisTree.electron_eta[im],analysisTree.electron_phi[im],
				analysisTree.trigobject_eta[iT],analysisTree.trigobject_phi[iT]);
	  if (dRtrig>DRTrigMatch) continue;
	  if (analysisTree.trigobject_filters[iT][nElectronFilter] &&
	      analysisTree.trigobject_pt[iT]>eleTriggerPtCut&&
	      fabs(analysisTree.trigobject_eta[iT])<eleTriggerEtaCut)  // Electron Leg of electron trigger
	    electronTriggerMatch = true;
	  if (analysisTree.trigobject_filters[iT][nEle23Filter])
	    electronEle23Match = true;
	  if (analysisTree.trigobject_filters[iT][nEle17Filter])
	    electronEle17Match = true;
	  if (analysisTree.trigobject_filters[iT][nEle12Filter])
	    electronEle12Match = true;
	  if (analysisTree.trigobject_filters[iT][nSingleEleFilter]&&
	      analysisTree.trigobject_pt[iT]>singleEleTriggerPtCut&&
	      fabs(analysisTree.trigobject_eta[iT])<singleEleTriggerEtaCut)
	    electronSingleEleMatch = true;
	    
	}

        allElectrons.push_back(im);
	allElectronsIsTriggerMatched.push_back(electronTriggerMatch);
	allElectronsIsLeg23Matched.push_back(electronEle23Match);
	allElectronsIsLeg17Matched.push_back(electronEle17Match);
	allElectronsIsLeg12Matched.push_back(electronEle12Match);
	allElectronsIsLegSingleEleMatched.push_back(electronSingleEleMatch);
	
	bool isPassed = true;

	if (fabs(analysisTree.electron_dxy[im])>dxyElectronCut) isPassed = false;
	if (fabs(analysisTree.electron_dz[im])>dzElectronCut)  isPassed = false;
	// isolation
	float absIso = 0; 
	if(isoDR03) {
	  absIso = analysisTree.electron_r03_sumChargedHadronPt[im];
	  float neutralIso = 
	  analysisTree.electron_r03_sumNeutralHadronEt[im] + 
	  analysisTree.electron_r03_sumPhotonEt[im] - 
	  0.5*analysisTree.electron_r03_sumPUPt[im];
	  neutralIso = TMath::Max(float(0),neutralIso); 
	  absIso += neutralIso;
	}
	else {
	  absIso = analysisTree.electron_chargedHadIso[im];
          float neutralIso = analysisTree.electron_neutralHadIso[im] +
            analysisTree.electron_photonIso[im] -
            0.5*analysisTree.electron_puIso[im];
          neutralIso = TMath::Max(float(0),neutralIso);
          absIso += neutralIso;
	}
	float relIso = absIso/analysisTree.electron_pt[im];
	allElectronsIso.push_back(relIso);
	bool electronId = analysisTree.electron_mva_wp80_nontrig_Spring15_v1[im];
	if (electronIdType==1)
	  electronId = analysisTree.electron_mva_wp90_nontrig_Spring15_v1[im];
	else if (electronIdType==2)
	  electronId = analysisTree.electron_mva_wp80_trig_Spring15_v1[im];
	else if (electronIdType==3)
	  electronId = analysisTree.electron_mva_wp90_trig_Spring15_v1[im];
	else if (electronIdType==4)
	  electronId = analysisTree.electron_cutId_loose_Spring15[im];
	else if (electronIdType==5)
	  electronId = analysisTree.electron_cutId_medium_Spring15[im];
	else if (electronIdType==6)
	  electronId = analysisTree.electron_cutId_tight_Spring15[im];
	else if (electronIdType==7)
	  electronId = analysisTree.electron_cutId_veto_Spring15[im];
	if (!analysisTree.electron_pass_conversion[im]) electronId = false;
	if (analysisTree.electron_nmissinginnerhits[im]>1) electronId = false;
	bool isPassedProbe = isPassed && electronId && relIso<isoElectronProbeCut;
	isElectronPassedIdIso.push_back(isPassedProbe);
	isPassed = isPassed && electronId && relIso<isoElectronCut;
	if (isPassed) { 
	  isoIdElectrons.push_back(im);
	  isoIdElectronsIsTriggerMatched.push_back(electronTriggerMatch);
	  isoIdElectronsIso.push_back(relIso);
	}
      }

      // end of electron selection

      // Monte Carlo analysis
      vector<unsigned int> promptElectrons; promptElectrons.clear();
      vector<unsigned int> nonpromptElectrons; nonpromptElectrons.clear();
      if (!isData) {
	for (unsigned int igen=0; igen<analysisTree.genparticles_count; ++igen) {
	  if (fabs(analysisTree.genparticles_pdgid[igen])==11&&analysisTree.genparticles_status[igen]==1) {
	    if (analysisTree.genparticles_info[igen]==1)
	      promptElectrons.push_back(igen);
	    if (analysisTree.genparticles_info[igen]==5)
	      nonpromptElectrons.push_back(igen);
	  }
	}
      }

      vector<bool> isElectronPrompt; isElectronPrompt.clear();
      for (unsigned int iRecoElectrons=0; iRecoElectrons<allElectrons.size(); iRecoElectrons++) {
	unsigned int irec = allElectrons[iRecoElectrons];
	bool isPrompt = false;
	TLorentzVector recElectron; recElectron.SetXYZM(analysisTree.electron_px[irec],
							analysisTree.electron_py[irec],
							analysisTree.electron_pz[irec],
							electronMass);

	for (unsigned int iElectrons=0; iElectrons<promptElectrons.size(); ++iElectrons) {
	  unsigned int igen = promptElectrons[iElectrons];
	  TLorentzVector genElectron; genElectron.SetXYZM(analysisTree.genparticles_px[igen],
							  analysisTree.genparticles_py[igen],
							  analysisTree.genparticles_pz[igen],
							  electronMass);
	  

	  float relativeDifference = (genElectron-recElectron).P()/genElectron.P();
	  if (relativeDifference<0.05) {
	    unsigned int iEta = 0;
	    isPrompt = true;
	    if (TMath::Abs(genElectron.Eta())<1.48) 
	      iEta = 1;
	    if (isElectronPassedIdIso[iRecoElectrons]) 
	      PromptPtPass[iEta]->Fill(genElectron.Pt(),weight);
	    else
	      PromptPtFail[iEta]->Fill(genElectron.Pt(),weight);
	  }
	}
	isElectronPrompt.push_back(isPrompt);
      }

      vector<bool> isElectronNonPrompt; isElectronNonPrompt.clear();
      for (unsigned int iRecoElectrons=0; iRecoElectrons<allElectrons.size(); iRecoElectrons++) {
	unsigned int irec = allElectrons[iRecoElectrons];
	bool isNonPrompt = false;
	TLorentzVector recElectron; recElectron.SetXYZM(analysisTree.electron_px[irec],
							analysisTree.electron_py[irec],
							analysisTree.electron_pz[irec],
							electronMass);

	for (unsigned int iElectrons=0; iElectrons<nonpromptElectrons.size(); ++iElectrons) {
	  unsigned int igen = nonpromptElectrons[iElectrons];
	  TLorentzVector genElectron; genElectron.SetXYZM(analysisTree.genparticles_px[igen],
							  analysisTree.genparticles_py[igen],
							  analysisTree.genparticles_pz[igen],
							  electronMass);
	  
	  float relativeDifference = (genElectron-recElectron).P()/genElectron.P();
	  if (relativeDifference<0.05) {
	    unsigned int iEta = 0;
	    isNonPrompt = true;
	    if (TMath::Abs(genElectron.Eta())<1.48) 
	      iEta = 1;
	    if (isElectronPassedIdIso[iRecoElectrons]) 
	      NonPromptPtPass[iEta]->Fill(genElectron.Pt(),weight);
	    else
	      NonPromptPtFail[iEta]->Fill(genElectron.Pt(),weight);
	  }
	}
	isElectronNonPrompt.push_back(isNonPrompt);
      }

      bool isElectronsPair = false;
      if (isoIdElectrons.size()>0) {
	unsigned int iE1 = 0;
	unsigned int iE2 = 0;
	bool isPairFound = false;
	float minIso = 999999;
	for (unsigned int im1=0; im1<isoIdElectrons.size(); ++im1) {
	  unsigned int index1 = isoIdElectrons[im1];
	  bool isTriggerMatched = isoIdElectronsIsTriggerMatched[im1];
	  if (isTriggerMatched &&
	      analysisTree.electron_pt[index1]>ptElectronHighCut&&
	      fabs(analysisTree.electron_eta[index1])<etaElectronHighCut) {
	    for (unsigned int iE=0; iE<allElectrons.size(); ++iE) {
	      unsigned int indexProbe = allElectrons[iE];
	      if (index1==indexProbe) continue;
	      float q1 = analysisTree.electron_charge[index1];
	      float q2 = analysisTree.electron_charge[indexProbe];
	      if (q1*q2>0) continue;
	      float dR = deltaR(analysisTree.electron_eta[index1],analysisTree.electron_phi[index1],
				analysisTree.electron_eta[indexProbe],analysisTree.electron_phi[indexProbe]);
	      if (dR<dRleptonsCut) continue;
	      float dPhi = dPhiFrom2P(analysisTree.electron_px[index1],analysisTree.electron_py[index1],
				analysisTree.electron_px[indexProbe],analysisTree.electron_py[indexProbe]);
	      if (dPhi>dPhileptonsCut) continue;
	      float ptProbe = TMath::Min(float(analysisTree.electron_pt[indexProbe]),float(ptBins[nPtBins]-0.01));
	      float absEtaProbe = TMath::Min(fabs(analysisTree.electron_eta[indexProbe]),float(etaBins[nEtaBins]-0.01));
	      int ptBin = binNumber(ptProbe,nPtBins,ptBins);
	      int etaBin = binNumber(absEtaProbe,nEtaBins,etaBins);
	      int ptBinTrig = binNumber(ptProbe,nPtBinsTrig,ptBinsTrig);

	      if (ptBin<0) continue;
	      if (etaBin<0) continue;
	      if (ptBinTrig<0) continue;

	      TLorentzVector electron1; electron1.SetXYZM(analysisTree.electron_px[index1],
							  analysisTree.electron_py[index1],
							  analysisTree.electron_pz[index1],
							  electronMass);
	      TLorentzVector electron2; electron2.SetXYZM(analysisTree.electron_px[indexProbe],
							  analysisTree.electron_py[indexProbe],
							  analysisTree.electron_pz[indexProbe],
							  electronMass);

	      // number of jets
	      int nJets30 = 0;
	      int nJets30etaCut = 0;
	
	      for (unsigned int jet=0; jet<analysisTree.pfjet_count; ++jet) {
		float absJetEta = fabs(analysisTree.pfjet_eta[jet]);
		if (absJetEta>jetEtaCut) continue;
	  
		float dR1 = deltaR(analysisTree.pfjet_eta[jet],analysisTree.pfjet_phi[jet],
				   analysisTree.electron_eta[index1],analysisTree.electron_phi[index1]);
		if (dR1<dRJetLeptonCut) continue;
		
		float dR2 = deltaR(analysisTree.pfjet_eta[jet],analysisTree.pfjet_phi[jet],
				   analysisTree.electron_eta[indexProbe],analysisTree.electron_phi[indexProbe]);		
		if (dR2<dRJetLeptonCut) continue;
	  
		// pfJetId
		bool isPFJetId = looseJetiD(analysisTree,int(jet));
		if (!isPFJetId) continue;

		if (analysisTree.pfjet_pt[jet]>jetPtHighCut) {
		  nJets30++;
		  if (fabs(analysisTree.pfjet_eta[jet])<jetEtaTrkCut) {
		    nJets30etaCut++;
		  }
		}
	      }	

	      int JetBin = nJets30etaCut;
	      if (JetBin>2) JetBin = 2;

	      float mass = (electron1+electron2).M();
	      if (isElectronPassedIdIso[iE]) {
		ZMassPass->Fill(mass,weight);
		ZMassEtaPtPass[etaBin][ptBin]->Fill(mass,weight);
		ZMassJetEtaPtPass[etaBin][JetBin][ptBin]->Fill(mass,weight);
		if (isElectronPrompt[iE]) {
		  PromptSelPtPass[etaBin]->Fill(ptProbe,weight); 
		  PromptSelJetPtPass[etaBin][JetBin]->Fill(ptProbe,weight);
		}
		if (isElectronNonPrompt[iE]) {
		  NonPromptSelPtPass[etaBin]->Fill(ptProbe,weight);
		  NonPromptSelJetPtPass[etaBin][JetBin]->Fill(ptProbe,weight);
		}

		// ele23 filter
		if (allElectronsIsLeg23Matched[iE])
		  ZMassEle23EtaPtPass[etaBin][ptBinTrig]->Fill(mass,weight);
		else 
		  ZMassEle23EtaPtFail[etaBin][ptBinTrig]->Fill(mass,weight);
		// ele17 filter
		if (allElectronsIsLeg17Matched[iE])
		  ZMassEle17EtaPtPass[etaBin][ptBinTrig]->Fill(mass,weight);
		else 
		  ZMassEle17EtaPtFail[etaBin][ptBinTrig]->Fill(mass,weight);
		// ele12 filter
		if (allElectronsIsLeg12Matched[iE])
		  ZMassEle12EtaPtPass[etaBin][ptBinTrig]->Fill(mass,weight);
		else 
		  ZMassEle12EtaPtFail[etaBin][ptBinTrig]->Fill(mass,weight);
		// single ele filter
		if (absEtaProbe<singleEleTriggerEtaCut) {
		  if (allElectronsIsLegSingleEleMatched[iE])
		    ZMassIsoEleEtaPtPass[etaBin][ptBinTrig]->Fill(mass,weight);
		  else 
		    ZMassIsoEleEtaPtFail[etaBin][ptBinTrig]->Fill(mass,weight);
		}
	      }
	      else {
		ZMassFail->Fill(mass,weight);
		ZMassEtaPtFail[etaBin][ptBin]->Fill(mass,weight);
		ZMassJetEtaPtFail[etaBin][JetBin][ptBin]->Fill(mass,weight);
		if (isElectronPrompt[iE]) {
		  PromptSelPtFail[etaBin]->Fill(ptProbe,weight); 
		  PromptSelJetPtFail[etaBin][JetBin]->Fill(ptProbe,weight);
		}
		if (isElectronNonPrompt[iE]) {
		  NonPromptSelPtFail[etaBin]->Fill(ptProbe,weight);
		  NonPromptSelJetPtFail[etaBin][JetBin]->Fill(ptProbe,weight);
		}
	      }
	    }
	  }
	  for (unsigned int im2=im1+1; im2<isoIdElectrons.size(); ++im2) {
	    unsigned int index2 = isoIdElectrons[im2];
	    float q1 = analysisTree.electron_charge[index1];
	    float q2 = analysisTree.electron_charge[index2];
	    bool isTriggerMatched1 = isoIdElectronsIsTriggerMatched[im1] && 
	      analysisTree.electron_pt[index1]>ptElectronHighCut&&
	      fabs(analysisTree.electron_eta[index1])<etaElectronHighCut;
	    bool isTriggerMatched2 = isoIdElectronsIsTriggerMatched[im2]&& 
	      analysisTree.electron_pt[index2]>ptElectronHighCut &&
	      fabs(analysisTree.electron_eta[index2])<etaElectronHighCut; 
	    bool isTriggerMatched = 
	      (isTriggerMatched1 
	       && analysisTree.electron_pt[index2]>ptElectronLowCut 
	       && fabs(analysisTree.electron_eta[index2])<etaElectronCut) ||
	      (isTriggerMatched2 
	       && analysisTree.electron_pt[index1]>ptElectronLowCut
	       && fabs(analysisTree.electron_eta[index1])<etaElectronCut);
	    bool sign = q1*q2>0;
	    float deltaREE = deltaR(analysisTree.electron_eta[index1],analysisTree.electron_phi[index1],
				    analysisTree.electron_eta[index2],analysisTree.electron_phi[index2]);
	    if (oppositeSign)
	      sign = q1*q2 < 0;
	    if (sign && isTriggerMatched && deltaREE>dRleptonsCut) {
	      float isoSum = isoIdElectronsIso[im1] + isoIdElectronsIso[im2];
	      if (isoSum<minIso) {
		minIso = isoSum;
		isPairFound = true;
		iE1 = index1;
		iE2 = index2;
		isElectronsPair = true;
	      }
	    }
	  }
	}
	if (isPairFound) {
	  TLorentzVector electron1; electron1.SetXYZM(analysisTree.electron_px[iE1],
						      analysisTree.electron_py[iE1],
						      analysisTree.electron_pz[iE1],
						      electronMass);
	  TLorentzVector electron2; electron2.SetXYZM(analysisTree.electron_px[iE2],
						      analysisTree.electron_py[iE2],
						      analysisTree.electron_pz[iE2],
						      electronMass);
	  float mass = (electron1+electron2).M();

	  // selecting good jets --->
	  
	  // HT variables
	  float HT30 = 0;
	  float HT20 = 0;
	  float HT30etaCut = 0;
	  float HT20etaCut = 0;
	  
	  // number of jets
	  int nJets30 = 0;
	  int nJets20 = 0;
	  int nJets30etaCut = 0;
	  int nJets20etaCut = 0;

	  if (!isData&&applyLeptonSF) {
	    // insert code for leptons SF here
	    // SF1 - scale factor for first electron index = iE1
	    // pt1 = analysisTree.electron_pt[iE1];
	    // eta2 = analysisTree.electron_eta[iE1];
	    // SF2 - scale factor for the second electron index = iE2
	    // pt2 = analysisTree.electron_pt[iE2];
	    // eta2 = analysisTree.electron_eta[iE2];
	    // weight = weight*SF1*SF2
	    double ptEle1 = (double)analysisTree.electron_pt[iE1];
	    double ptEle2 = (double)analysisTree.electron_pt[iE2];
	    double etaEle1 = (double)analysisTree.electron_eta[iE1];
	    double etaEle2 = (double)analysisTree.electron_eta[iE2];
	    double IdIsoSF_ele1 = SF_electronIdIso->get_ScaleFactor(ptEle1, etaEle1);
	    double IdIsoSF_ele2 = SF_electronIdIso->get_ScaleFactor(ptEle2, etaEle2);
	
	    EleSF_IdIso_Ele1H->Fill(IdIsoSF_ele1);
	    EleSF_IdIso_Ele2H->Fill(IdIsoSF_ele2);
	    //	    if (ptEle1<20||ptEle2<20) {
	    //	      std::cout << "ele 1 ->  pt = " << ptEle1 << "   eta = " << etaEle1 << std::endl;
	    //	      std::cout << "eff data ele 1 = " << SF_electronIdIso->get_EfficiencyData(ptEle1, etaEle1)<< " |  eff mc ele 1 = " << SF_electronIdIso->get_EfficiencyMC(ptEle1, etaEle1)<<std::endl;
	    //	      std::cout << "ele 2 ->  pt = " << ptEle2 << "   eta = " << etaEle2 << std::endl;
	    //	      std::cout << "eff data ele 2 = " << SF_electronIdIso->get_EfficiencyData(ptEle2, etaEle2)<< " |  eff mc ele 2 = " << SF_electronIdIso->get_EfficiencyMC(ptEle2, etaEle2)<<std::endl;
	    //	      std::cout << "SF ele1 = " << IdIsoSF_ele1 << std::endl;
	    //	      std::cout << "SF ele2 = " << IdIsoSF_ele2 << std::endl;
	    //	      
	    //	      std::cout << " mass = " << mass << std::endl;
	    //	      std::cout << std::endl;
	    //	    }
	    weight = weight*IdIsoSF_ele1*IdIsoSF_ele2;
	  }
	   
	  for (unsigned int jet=0; jet<analysisTree.pfjet_count; ++jet) {
	    float absJetEta = fabs(analysisTree.pfjet_eta[jet]);
	    if (absJetEta>jetEtaCut) continue;
	    
	    float dR1 = deltaR(analysisTree.pfjet_eta[jet],analysisTree.pfjet_phi[jet],
			       analysisTree.electron_eta[iE1],analysisTree.electron_phi[iE1]);
	    if (dR1<dRJetLeptonCut) continue;
	    
	    float dR2 = deltaR(analysisTree.pfjet_eta[jet],analysisTree.pfjet_phi[jet],
			       analysisTree.electron_eta[iE2],analysisTree.electron_phi[iE2]);
	    
	    if (dR2<dRJetLeptonCut) continue;
	  
	    // pfJetId

	    bool isPFJetId = looseJetiD(analysisTree,int(jet));
	    if (!isPFJetId) continue;
	    
	    if (analysisTree.pfjet_pt[jet]>jetPtHighCut) {
	      nJets30++;
	      HT30 += analysisTree.pfjet_pt[jet];
	      if (fabs(analysisTree.pfjet_eta[jet])<jetEtaTrkCut) {
		HT30etaCut += analysisTree.pfjet_pt[jet];
		nJets30etaCut++;
	      }
	    }
	    
	    if (analysisTree.pfjet_pt[jet]>jetPtLowCut) {
	      nJets20++;
	      HT20 += analysisTree.pfjet_pt[jet]; 
	      if (fabs(analysisTree.pfjet_eta[jet])<jetEtaTrkCut) {
		HT20etaCut += analysisTree.pfjet_pt[jet];
		nJets20etaCut++;
	      }
	    }	  
	    

	  }
          float ptLeadingE = analysisTree.electron_pt[iE1];
	  float etaLeadingE = analysisTree.electron_eta[iE1];
	  float ptTrailingE = analysisTree.electron_pt[iE2];
	  float etaTrailingE = analysisTree.electron_eta[iE2];
	  if (ptTrailingE>ptLeadingE) {
	    float temp = ptLeadingE;
	    ptLeadingE = ptTrailingE;
	    ptTrailingE = temp;
	    temp = etaLeadingE;
	    etaLeadingE = etaTrailingE;
	    etaTrailingE = temp;
	    float itemp = iE1;
	    iE1 = iE2;
	    iE2 = itemp;
	  } 

	  massSelH->Fill(mass,weight);
	  massSelLargeRangeH->Fill(mass,weight);
	  for (int iScale=0; iScale<21; ++ iScale) {
	    float scaleFactor = 0.98 + 0.002*float(iScale);
	    massSelScaleH[iScale]->Fill(mass*scaleFactor,weight);
	  }


	  if (mass>dielectronMassCut) {
	    nJets30SelH->Fill(nJets30,weight);
	    nJets20SelH->Fill(nJets20,weight);
	    nJets30etaCutSelH->Fill(nJets30etaCut,weight);
	    nJets20etaCutSelH->Fill(nJets20etaCut,weight);
	    ptLeadingEleSelH->Fill(ptLeadingE,weight);
	    ptTrailingEleSelH->Fill(ptTrailingE,weight);
	    etaLeadingEleSelH->Fill(etaLeadingE,weight);
	    etaTrailingEleSelH->Fill(etaTrailingE,weight);
	    NumberOfVerticesH->Fill(float(analysisTree.primvertex_count),weight);
	    metSelH->Fill(pfmet,weight);
	    puppimetSelH->Fill(puppimet,weight);
	    for (int iScale=0; iScale<21; ++ iScale) {
	      float scaleFactor = 0.9 + 0.01*float(iScale);
	      metSelScaleH[iScale]->Fill(pfmet*scaleFactor,weight);
	      puppimetSelScaleH[iScale]->Fill(puppimet*scaleFactor,weight);
	    }
	  }
	}
      }
      
      if (isElectronsPair) selEventsDielectrons++;
    } // end of file processing (loop over events in one file)
    nFiles++;
    delete _tree;
    file_->Close();
    delete file_;
  }
  std::cout << std::endl;
  int allEvents = int(inputEventsH->GetEntries());
  std::cout << "Total number of input events                              = " << allEvents << std::endl;
  std::cout << "Total number of events in Tree                            = " << nEvents << std::endl;
  std::cout << "Total number of selected events (electron pairs)          = " << selEventsDielectrons << std::endl;
  std::cout << std::endl;
  std::cout << "RunMin = " << RunMin << std::endl;
  std::cout << "RunMax = " << RunMax << std::endl;

  // using object as comp
  std::sort (allRuns.begin(), allRuns.end(), myobject);
  std::cout << "Runs   :";
  for (unsigned int iR=0; iR<allRuns.size(); ++iR)
    std::cout << " " << allRuns.at(iR);
  std::cout << std::endl;
  
  file->Write();
  file->Close();
  delete file;
  
  
}
