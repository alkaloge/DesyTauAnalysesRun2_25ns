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
#include "TCanvas.h"
#include "TPaveText.h"
#include "TRandom.h"
#include "TGraphAsymmErrors.h"
#include <stdlib.h>
#include "TRandom.h"


#include "DesyTauAnalyses/NTupleMaker/interface/Jets.h"
#include "DesyTauAnalyses/NTupleMaker/interface/AnalysisMacro.h"
int main(int argc, char * argv[]) {

  // **** configuration
  Config cfg(argv[1]);
  string Channel="muel";

  // kinematic cuts on electrons
  bool fillplots= false;
  const bool isData = cfg.get<bool>("IsData");

//////////systematics

  const bool applyLeptonSF = cfg.get<bool>("ApplyLeptonSF");

  bool ApplyTauEnergyScaleUnc = false;
  bool ApplyTauCorrectionUncSignPositive = false;
  bool ApplyElEnergyScaleUnc = false;
  bool ApplyElectronCorrectionUncSignPositive = false;
  bool ApplyMuEnergyScaleUnc = false;
  bool ApplyMuonCorrectionUncSignPositive = false;
  bool ApplyJetEnergyCorrectionUnc = false;
  bool ApplyJetEnergyCorrectionUncSignPositive = false;

  const double TauEnergyScaleUnc   = cfg.get<double>("TauEnergyScaleUnc");
  const double MuEnergyScaleUnc   = cfg.get<double>("MuEnergyScaleUnc");
  const double ElEnergyScaleUncBarrel   = cfg.get<double>("ElEnergyScaleUncBarrel");
  const double ElEnergyScaleUncEndcaps   = cfg.get<double>("ElEnergyScaleUncEndcaps");
//_Nominal _JetEnUp _JetEnDown  _ElEnUp _ElEnDown _MuEnUp _MuEnDown


  	string BTag_ = "central";
  	string Systematic=argv[5];
	if (Systematic=="1" || Systematic=="" || isData) Systematic = "Nominal";

	if (string::npos != Systematic.find("TauEnUp")){ ApplyTauEnergyScaleUnc = true; ApplyTauCorrectionUncSignPositive = true;}
	if (string::npos != Systematic.find("TauEnDown")){ ApplyTauEnergyScaleUnc = true; ApplyTauCorrectionUncSignPositive = false;}

	if (string::npos != Systematic.find("ElEnUp")){ ApplyElEnergyScaleUnc = true; ApplyElectronCorrectionUncSignPositive = true;}
	if (string::npos != Systematic.find("ElEnDown")){ ApplyElEnergyScaleUnc = true; ApplyElectronCorrectionUncSignPositive = false;}

	if (string::npos != Systematic.find("MuEnUp")){ ApplyMuEnergyScaleUnc = true; ApplyMuonCorrectionUncSignPositive = true;}
	if (string::npos != Systematic.find("MuEnDown")){ ApplyMuEnergyScaleUnc = true; ApplyMuonCorrectionUncSignPositive = false;}

	if (string::npos != Systematic.find("JetEnUp")){ ApplyJetEnergyCorrectionUnc = true; ApplyJetEnergyCorrectionUncSignPositive = true;}
	if (string::npos != Systematic.find("JetEnDown")){ ApplyJetEnergyCorrectionUnc = true; ApplyJetEnergyCorrectionUncSignPositive = false;}

	if (string::npos != Systematic.find("BTagUp")){ BTag_ = "up";}
	if (string::npos != Systematic.find("BTagDown")){ BTag_ = "down";}


////////////muons

  const float ptMuonLowCut   = cfg.get<float>("ptMuonLowCutmuel");
  const double ptMuonHighCut  = cfg.get<double>("ptMuonHighCutmuel");
  const double etaMuonCut     = cfg.get<double>("etaMuonCutmuel");
  const double dxyMuonCut     = cfg.get<double>("dxyMuonCut");
  const double dzMuonCut      = cfg.get<double>("dzMuonCut");
  const double isoMuonHighCut = cfg.get<double>("isoMuonHighCutmuel");

  // kinematic cuts on electrons
  const float ptElectronLowCut   = cfg.get<float>("ptElectronLowCutmuel");
  const float ptElectronHighCut  = cfg.get<float>("ptElectronHighCutmuel");
  const float etaElectronCut     = cfg.get<float>("etaElectronCutmuel");
  const float dxyElectronCut     = cfg.get<float>("dxyElectronCutmuel");
  const float dzElectronCut      = cfg.get<float>("dzElectronCutmuel");
  const float isoElectronLowCut  = cfg.get<float>("isoElectronLowCutmuel");
  const float isoElectronHighCut = cfg.get<float>("isoElectronHighCutmuel");
  const bool applyElectronId     = cfg.get<bool>("ApplyElectronIdmuel");
  const string lowPtLegElectron  = cfg.get<string>("LowPtLegElectron");
  const string highPtLegElectron = cfg.get<string>("HighPtLegElectron");
  const string mu8Ele23DZ = cfg.get<string>("Mu8Ele23DZ");
  const string mu23Ele12DZ = cfg.get<string>("Mu23Ele12DZ");

  // veto muons
  const float ptVetoMuonCut   = cfg.get<float>("ptVetoMuonCut");
  const float etaVetoMuonCut  = cfg.get<float>("etaVetoMuonCut");
  const float dxyVetoMuonCut   = cfg.get<float>("dxyVetoMuonCut");
  const float dzVetoMuonCut   = cfg.get<float>("dzVetoMuonCut");
  const float isoVetoMuonCut   = cfg.get<float>("isoVetoMuonCut");
  const bool applyVetoMuonId     = cfg.get<bool>("ApplyVetoMuonId");
  const string lowPtLegMuon  = cfg.get<string>("LowPtLegMuon");
  const string highPtLegMuon = cfg.get<string>("HighPtLegMuon");


//veto electrons
  const float ptVetoElectronCut   = cfg.get<float>("ptVetoElectronCut");
  const float etaVetoElectronCut  = cfg.get<float>("etaVetoElectronCut");
  const float dxyVetoElectronCut  = cfg.get<float>("dxyVetoElectronCut");
  const float dzVetoElectronCut   = cfg.get<float>("dzVetoElectronCut");
  const float isoVetoElectronCut  = cfg.get<float>("isoVetoElectronCut");
  const bool applyVetoElectronId  = cfg.get<bool>("ApplyVetoElectronId");

  // vertex cuts
  const double ndofVertexCut  = cfg.get<double>("NdofVertexCut");   
  const double zVertexCut     = cfg.get<double>("ZVertexCut");
  const double dVertexCut     = cfg.get<double>("DVertexCut");



  const string dataBaseDir = cfg.get<string>("DataBaseDir");



  const string Region  = cfg.get<string>("Region");
  const string Sign  = cfg.get<string>("Sign");


  // kinematic cuts on Jets
  const double etaJetCut   = cfg.get<double>("etaJetCut");
  const double ptJetCut   = cfg.get<double>("ptJetCut");
  // topSingleMuonTriggerFile
  const double deltaRTrigMatch = cfg.get<double>("DRTrigMatch");
  const bool oppositeSign    = cfg.get<bool>("oppositeSign");
  const bool isIsoR03 = cfg.get<bool>("IsIsoR03");
  const float dRleptonsCut   = cfg.get<float>("dRleptonsCutmuel");
  const bool applyTriggerMatch = cfg.get<bool>("ApplyTriggerMatch");


  //const string TauFakeRateFile = cfg.get<string>("TauFakeRateEff");

////////// Triggers 
  TString LowPtLegElectron(lowPtLegElectron);
  TString HighPtLegElectron(highPtLegElectron);
  TString Mu23Ele12DZ(mu23Ele12DZ);
  TString Mu8Ele23DZ(mu8Ele23DZ);
  
  TString LowPtLegMuon(lowPtLegMuon);
  TString HighPtLegMuon(highPtLegMuon);

  
  const string Muon8TriggerFile0p15 = cfg.get<string>("Muon8TriggerEff0p15");
  const string Muon23TriggerFile0p15 = cfg.get<string>("Muon23TriggerEff0p15");
  const string Electron12TriggerFile0p1 = cfg.get<string>("Electron12TriggerEff0p1");
  const string Electron23TriggerFile0p1 = cfg.get<string>("Electron23TriggerEff0p1");


  const string MuonidIsoEffFile = cfg.get<string>("MuonidIsoEffFile");
  const string ElectronIdIsoFile = cfg.get<string>("ElectronIdIsoEffFile");

  /////////////////////////////////////////////


  const double bTag   = cfg.get<double>("bTag");

  xs=1;fact=1;fact2=1;

  ifstream ifs("xsecs");
  string line;

    XSec=1.;
   xsecs=XSec;

  bool doThirdLeptVeto=true;
  bool doMuVeto=true;
  bool SUSY = false;
  char ff[100];
  sprintf(ff,"%s/%s",argv[3],argv[2]);

  int nTotalFiles = 0;

  std::string rootFileName(argv[2]);
  std::string NrootFile(argv[4]);
  std::ifstream fileList(ff);
  std::ifstream fileList0(ff);
  std::string ntupleName("AC1B");


  TString SaveDir=argv[3];

  TString TStrName(rootFileName+"_"+Region+"_"+Sign);
  datasetName = rootFileName.c_str();
  std::cout <<" The filename will be "<<TStrName <<"  "<<datasetName<<std::endl;  
  // output fileName with histograms


  TFile * file = new TFile(SaveDir+"/"+TStrName+TString(".root"),"update");
  file->mkdir(Channel.c_str());
  file->cd(Channel.c_str());

  int nFiles = 0;
  int nEvents = 0;
  int selEvents = 0;

  bool lumi=false;


  std::string dummy;
  // count number of files --->
  while (fileList0 >> dummy) nTotalFiles++;
  SetupTree(); 
  
  Float_t         sumPt;
  T->Branch("sumPt", &sumPt, "sumPt/F");
  
  //std::cout <<" Test 1  "<<std::endl;  
  if (argv[4] != NULL  && atoi(argv[4])< nTotalFiles) nTotalFiles=atoi(argv[4]);
 
for (int iF=0; iF<nTotalFiles; ++iF) {

    std::string filen;
    fileList >> filen;

    std::cout << "file " << iF+1 << " out of " << nTotalFiles << " filename : " << filen << std::endl;
    TFile * file_ = TFile::Open(TString(filen));


bool WithInit = false;


    TTree * _tree =  (TTree*)file_->Get(TString(ntupleName));
    Float_t genweight=1.;

    if (_tree==NULL) continue;
    Long64_t numberOfEntries = _tree->GetEntries();
    std::cout << "      number of entries in Tree      = " << numberOfEntries << std::endl;
    AC1B analysisTree(_tree);
		for (Long64_t iEntry=0; iEntry<numberOfEntries; ++iEntry) 
			{
//				cout<<" reading now  "<<iEntry<<endl;
			analysisTree.GetEntry(iEntry);
			histWeightsH->Fill(0.,analysisTree.genweight);
			}

	cout<<" The ============================ histWeights "<<histWeightsH->GetBinContent(1)<<endl;

	


    for (Long64_t iEntry=0; iEntry<numberOfEntries; ++iEntry) { 

      Float_t weight = 1.;


      all_weight = 1.;
      gen_weight = 1.;

      analysisTree.GetEntry(iEntry);
      nEvents++;

      //std::cout << "      number of entries in Tree = " << numberOfEntries <<" starting weight "<<weight<< std::endl;

      if (nEvents%50000==0) 
	cout << "      processed " << nEvents << " events" << endl; 

      

///////////////////////////////////////////////////////////////////////////// systematic study
	if (ApplyTauEnergyScaleUnc && !isData)
		{
			double ApplyTauCorrectionUncSign=1;
			if (!ApplyTauCorrectionUncSignPositive) ApplyTauCorrectionUncSign = -1;

		for (unsigned int it = 0; it<analysisTree.tau_count; ++it) 
			{

			analysisTree.tau_pt[it] *= (1 +ApplyTauCorrectionUncSign*TauEnergyScaleUnc);
			analysisTree.tau_px[it] *= (1 +ApplyTauCorrectionUncSign*TauEnergyScaleUnc);
			analysisTree.tau_py[it] *= (1 +ApplyTauCorrectionUncSign*TauEnergyScaleUnc);
			analysisTree.tau_pz[it] *= (1 +ApplyTauCorrectionUncSign*TauEnergyScaleUnc);
			analysisTree.tau_e[it] *= (1 +ApplyTauCorrectionUncSign*TauEnergyScaleUnc);

			//analysisTree.pfmet_ex = analysisTree.pfmet_ex+((analysisTree.tau_px[it]/TauEnergyScaleUnc)-analysisTree.tau_px[it]);
			//analysisTree.pfmet_ey = analysisTree.pfmet_ey+((analysisTree.tau_py[it]/TauEnergyScaleUnc)-analysisTree.tau_py[it]);
			}
		
		} 

	if (ApplyJetEnergyCorrectionUnc && !isData)
		{
		double ApplyJetEnergyCorrectionUncSign=1;
		for (unsigned int it = 0; it<analysisTree.pfjet_count; ++it) 
			{
			if (!ApplyJetEnergyCorrectionUncSignPositive) ApplyJetEnergyCorrectionUncSign = -1;
			analysisTree.pfjet_pt[it] *=(1 + ApplyJetEnergyCorrectionUncSign*analysisTree.pfjet_jecUncertainty[it]);
			analysisTree.pfjet_px[it] *=(1 + ApplyJetEnergyCorrectionUncSign*analysisTree.pfjet_jecUncertainty[it]);
			analysisTree.pfjet_py[it] *=(1 + ApplyJetEnergyCorrectionUncSign*analysisTree.pfjet_jecUncertainty[it]);
			analysisTree.pfjet_pz[it] *=(1 + ApplyJetEnergyCorrectionUncSign*analysisTree.pfjet_jecUncertainty[it]);
			analysisTree.pfjet_e[it] *=(1 + ApplyJetEnergyCorrectionUncSign*analysisTree.pfjet_jecUncertainty[it]);
			}
		
		} 

	if (ApplyElEnergyScaleUnc && !isData)
		{
		double ElEnergyScaleUnc=1;
			double ApplyElectronCorrectionUncSign=1;
			if (!ApplyElectronCorrectionUncSignPositive) ApplyElectronCorrectionUncSign = -1;

		for (unsigned int it = 0; it<analysisTree.electron_count; ++it) 
			{

			if (analysisTree.electron_eta[it] < 1.48)  ElEnergyScaleUnc = ElEnergyScaleUncBarrel;
			if (analysisTree.electron_eta[it] > 1.48)  ElEnergyScaleUnc = ElEnergyScaleUncEndcaps;

			analysisTree.electron_pt[it] *=(1 + ApplyElectronCorrectionUncSign*ElEnergyScaleUnc);
			analysisTree.electron_px[it] *=(1 + ApplyElectronCorrectionUncSign*ElEnergyScaleUnc);
			analysisTree.electron_py[it] *=(1 + ApplyElectronCorrectionUncSign*ElEnergyScaleUnc);
			analysisTree.electron_pz[it] *=(1 + ApplyElectronCorrectionUncSign*ElEnergyScaleUnc);

			}
		
		} 

	if (ApplyMuEnergyScaleUnc && !isData)
		{
			double ApplyMuonCorrectionUncSign=1;
			if (!ApplyMuonCorrectionUncSignPositive) ApplyMuonCorrectionUncSign = -1;

		for (unsigned int it = 0; it<analysisTree.muon_count; ++it) 
			{

			analysisTree.muon_pt[it] *= (1 + ApplyMuonCorrectionUncSign*MuEnergyScaleUnc);
			analysisTree.muon_px[it] *= (1 + ApplyMuonCorrectionUncSign*MuEnergyScaleUnc);
			analysisTree.muon_py[it] *= (1 + ApplyMuonCorrectionUncSign*MuEnergyScaleUnc);
			analysisTree.muon_pz[it] *= (1 + ApplyMuonCorrectionUncSign*MuEnergyScaleUnc);
			}
		
		} 

///////////////////////////////////////////////////////////////////////////// systematic study end


	    weight *= analysisTree.genweight;
	    gen_weight *=analysisTree.genweight;
	   // std::cout <<"analysisTree.genweight "<< float(analysisTree.genweight) << std::endl;
		


      vector<int> electrons; electrons.clear();
      for (unsigned int ie = 0; ie<analysisTree.electron_count; ++ie) {
	if (analysisTree.electron_pt[ie]<ptElectronLowCut) continue;
	if (fabs(analysisTree.electron_eta[ie])>etaElectronCut) continue;
	if (fabs(analysisTree.electron_charge[ie]) !=1) continue;
	electrons.push_back(ie);
      }
      if (electrons.size()==0) continue;

      // muon selection
      vector<int> muons; muons.clear();
      for (unsigned int im = 0; im<analysisTree.muon_count; ++im) {
	if (analysisTree.muon_pt[im]<ptMuonLowCut) continue;
	if (fabs(analysisTree.muon_eta[im])>etaMuonCut) continue;
	if (fabs(analysisTree.muon_charge[im]) != 1) continue;
	muons.push_back(im);
      }


      if (muons.size()==0) continue;

      int el_index=-1;
      int mu_index=-1;
      int tau_index=-1;

      float isoMuMin = 1e+10;
      float isoEleMin = 1e+10;

      bool isMuon23matched = false;
      bool isMuon8matched  = false;
      bool isElectron23matched = false;
      bool isElectron12matched = false;
      for (unsigned int im=0; im<muons.size(); ++im) {
	bool isMu23 = false;
	bool isMu8 = false;
	unsigned int mIndex  = muons.at(im);
	float relIsoMu=analysisTree.muon_relIso[mIndex];

	  if (analysisTree.muon_pt[mIndex]>ptMuonHighCut) isMu23 = true;
	  if (analysisTree.muon_pt[mIndex]>ptMuonLowCut) isMu8 = true;


	  bool isEle23 = false;
	  bool isEle12 = false;


	for (unsigned int ie=0; ie<electrons.size(); ++ie) {

	  unsigned int eIndex = electrons.at(ie);

	  float dR = deltaR(analysisTree.electron_eta[eIndex],analysisTree.electron_phi[eIndex],
			    analysisTree.muon_eta[mIndex],analysisTree.muon_phi[mIndex]);

	  if (dR<dRleptonsCut) continue;


	  
	  if (analysisTree.electron_pt[eIndex]>ptElectronHighCut) isEle23 = true;
	  if (analysisTree.electron_pt[eIndex]>ptElectronLowCut) isEle12 = true;
	  bool trigMatchA = (isMu23 && isEle12) ;
	  bool trigMatchB = (isMu8 && isEle23);

	  if (!isEle23 && !isEle12) continue;

	  if (!trigMatchA && !trigMatchB) continue;

	  float relIsoEle = analysisTree.electron_relIso[eIndex];

	  if ((int)mIndex!=(int)mu_index) {
	    if (relIsoMu==isoMuMin) {
	      if (analysisTree.muon_pt[mIndex]>analysisTree.muon_pt[mu_index]) {
		isoMuMin  = relIsoMu;
		mu_index = (int)mIndex;
		isoEleMin = relIsoEle;
		el_index = (int)eIndex;
		isMuon23matched = isMu23;
		isMuon8matched = isMu8;
		isElectron23matched = isEle23;
		isElectron12matched = isEle12;
	      }
	    }
	    else if (relIsoMu<isoMuMin) {
	      isoMuMin  = relIsoMu;
	      mu_index = (int)mIndex;
	      isoEleMin = relIsoEle;
	      el_index = (int)eIndex;
	      isMuon23matched = isMu23;
	      isMuon8matched = isMu8;
	      isElectron23matched = isEle23;
	      isElectron12matched = isEle12;
	    }
	  }
	  else {
	    if (relIsoEle==isoEleMin) {
	      if (analysisTree.electron_pt[eIndex]>analysisTree.electron_pt[el_index]) {
		isoEleMin = relIsoEle;
		el_index = (int)eIndex;
		isElectron23matched = isEle23;
		isElectron12matched = isEle12;
	      }
	    }
	    else if (relIsoEle<isoEleMin) {
	      isoEleMin = relIsoEle;
	      el_index = (int)eIndex;
	      isElectron23matched = isEle23;
	      isElectron12matched = isEle12;
	    }
	  }
	  
	}
      }

       //     cout << "mIndex = " << mu_index << "   eIndex = " << el_index << std::endl;

      if ((int)el_index<0) continue;
      if ((int)mu_index<0) continue;
	
      float relIsoEle = analysisTree.electron_relIso[el_index];
      float relIsoMu=analysisTree.muon_relIso[mu_index];


      el_relIso[0]=isoEleMin;
      mu_relIso[0]=isoMuMin;

      if (isoEleMin>0.2 || isoMuMin>0.2) continue;
      
      double q = analysisTree.electron_charge[el_index] * analysisTree.muon_charge[mu_index];
      event_sign  = q;


  bool          dilepton_veto=false;
  bool          extraelec_veto=false;
  bool          extramuon_veto=false;

  event_secondLeptonVeto = false;
  event_thirdLeptonVeto = false;

      // looking for extra electron
      bool foundExtraElectron = false;
      for (unsigned int ie = 0; ie<analysisTree.electron_count; ++ie) {
	if (int(ie)==(int)el_index) continue;
	if (analysisTree.electron_pt[ie]<ptVetoElectronCut) continue;
	if (fabs(analysisTree.electron_eta[ie])>etaVetoElectronCut) continue;
	float relIsoEle = analysisTree.electron_relIso[ie];	
	if (relIsoEle>isoVetoElectronCut) continue;
	foundExtraElectron = true;
      }

      // looking for extra muon
      bool foundExtraMuon = false;
      for (unsigned int im = 0; im<analysisTree.muon_count; ++im) {
	if (int(im)==(int)mu_index) continue;
	if (analysisTree.muon_pt[im]<ptVetoMuonCut) continue;
	if (fabs(analysisTree.muon_eta[im])>etaVetoMuonCut) continue;
	float relIsoMu = analysisTree.muon_relIso[im];
	if (relIsoMu>isoVetoMuonCut) continue;
	foundExtraMuon = true;
      }


      extraelec_veto = foundExtraElectron;
      extramuon_veto = foundExtraMuon;


      // applying inclusive selection

   	event_secondLeptonVeto = false;

	
	if(extraelec_veto || extramuon_veto)   event_thirdLeptonVeto = true;

//	if (event_thirdLeptonVeto) continue;


      //////////////////////////////////////////////
      muon_index = (int)mu_index;
      electron_index = (int)el_index;
      taus_index = (int)tau_index;



      mu_count= (int)muons.size();
      for (unsigned int im=0;im<muons.size(); ++im){
	  unsigned int mIndex = muons[im];
	mu_px[im]=analysisTree.muon_px[mIndex];
	mu_py[im]=analysisTree.muon_py[mIndex];
	mu_pz[im]=analysisTree.muon_pz[mIndex];
	mu_eta[im]=analysisTree.muon_eta[mIndex];
	mu_pt[im]=analysisTree.muon_pt[mIndex];
	mu_phi[im]=analysisTree.muon_phi[mIndex];
	mu_charge[im]=analysisTree.muon_charge[mIndex];

	mu_relIsoMu[im]  = analysisTree.muon_relIso[im];
   
     	}



      el_count=(int)electrons.size();
      for (unsigned int ie=0;ie<electrons.size(); ++ie){
	  unsigned int iee = electrons[ie];
	el_px[ie]=analysisTree.electron_px[iee];
	el_py[ie]=analysisTree.electron_py[iee];
	el_pz[ie]=analysisTree.electron_pz[iee];
	el_eta[ie]=analysisTree.electron_eta[iee];
	el_pt[ie]=analysisTree.electron_pt[iee];
	el_phi[ie]=analysisTree.electron_phi[iee];
	el_charge[ie]=analysisTree.electron_charge[iee];

	el_relIsoEl[ie]  = analysisTree.electron_relIso[iee];

      }


				
      jet_count=(int)analysisTree.pfjet_count;
      for (unsigned int jj=0;jj<analysisTree.pfjet_count; ++jj){

	jet_e[jj] = analysisTree.pfjet_e[jj];
	jet_px[jj] = analysisTree.pfjet_px[jj];
	jet_py[jj] = analysisTree.pfjet_py[jj];
	jet_pz[jj] = analysisTree.pfjet_pz[jj];
	jet_pt[jj] = analysisTree.pfjet_pt[jj];
	jet_eta[jj] = analysisTree.pfjet_eta[jj];
	jet_phi[jj] = analysisTree.pfjet_phi[jj];
	jet_flavour[jj] = analysisTree.pfjet_flavour[jj];
	jet_btag[jj] = analysisTree.pfjet_btag[jj][1];
      }


      TLorentzVector leptonsV, muonJ, jetsLV;


      float jetEta = 2.4;
      float DRmax = 0.5;
      float bJetEtaCut = jetEta;


      vector<unsigned int> jets; jets.clear();
      vector<unsigned int> bjets; bjets.clear();
      vector<unsigned int> bjetsL; bjetsL.clear();
      vector<unsigned int> bjetsM; bjetsM.clear();
      vector<unsigned int> bjetsT; bjetsT.clear();
      int indexLeadingJet = -1;
      float ptLeadingJet = -1;

      int indexSubLeadingJet = -1;
      float ptSubLeadingJet = -1;

      int indexLeadingBJet = -1;

      int counter_cleaned_jets = 0;

      for (int n=0;n<30;n++) jets_cleaned[n]=-1;

      for (unsigned int jet=0; jet<analysisTree.pfjet_count; ++jet) {

	if (fabs(analysisTree.pfjet_pt[jet])<ptJetCut) continue;
        float absJetEta = fabs(analysisTree.pfjet_eta[jet]);
	if (absJetEta > etaJetCut) continue;

	float jetPt = analysisTree.pfjet_pt[jet];


	bool cleanedJet = true;


	double Dr=deltaR(analysisTree.muon_eta[mu_index],analysisTree.muon_phi[mu_index],
			 analysisTree.pfjet_eta[jet],analysisTree.pfjet_phi[jet]);
	if (  Dr  < DRmax)  cleanedJet=false;

	double Dre=deltaR(analysisTree.electron_eta[el_index],analysisTree.electron_phi[el_index],
			  analysisTree.pfjet_eta[jet],analysisTree.pfjet_phi[jet]);

	if (  Dre  < DRmax )  cleanedJet=false;

	if (!cleanedJet) continue;


	if (absJetEta<bJetEtaCut) { // jet within b-tagging acceptance

	if (analysisTree.pfjet_btag[jet][1]  > 0.5) bjets.push_back(jet);

	if (analysisTree.pfjet_btag[jet][0]  > 0.5) bjetsL.push_back(jet); 
	if (analysisTree.pfjet_btag[jet][1]  > 0.5) bjetsM.push_back(jet); 
	if (analysisTree.pfjet_btag[jet][2]  > 0.5) bjetsT.push_back(jet); 
		}


	if (cleanedJet){
		
	//	cout<<"  will push to save now cleaned jet  "<<(int)jet<<"  for counter_cleaned_jet "<<(int)counter_cleaned_jets<<" event "<<iEntry<<endl;

	jets.push_back((int)jet);
	jets_cleaned[counter_cleaned_jets]=(int)jet;
	counter_cleaned_jets++;
	}


      }///loop in all jets

      njets = jets.size();
      jet_count = jets.size();
      nbtagL = bjetsL.size();
      nbtagM = bjetsM.size();
      nbtagT = bjetsT.size();


      nbtag = bjets.size();


      met_ex = analysisTree.pfmet_pt*TMath::Cos(analysisTree.pfmet_phi);
      met_ey = analysisTree.pfmet_pt*TMath::Sin(analysisTree.pfmet_phi);
      met_pt = analysisTree.pfmet_pt;
      met_phi = analysisTree.pfmet_phi;

      all_weight = weight;


      T->Fill();
	
      selEvents++;




    } // end of file processing (loop over events in one file)


    nFiles++;
    delete _tree;
    file_->Close();
    delete file_;
  }
  cout<<"done"<<endl;

  cout<<" Run range from -----> "<<RunMin<<" to  "<<RunMax<<endl;



  std::cout << std::endl;
  int allEvents = (int)inputEventsH->GetEntries();
  std::cout << "Total number of input events    = " << allEvents << std::endl;
  std::cout << "Total number of events in Tree  = " << nEvents << std::endl;
  std::cout << "Total number of selected events = " << selEvents << std::endl;
  std::cout << std::endl;


  file->cd(Channel.c_str());
  hxsec->Fill(XSec);
  hxsec->Write();
  inputEventsH->Write();
  histWeightsH->Write();
  histWeightsScalesUp->Write();
  histWeightsScalesDown->Write();
  histWeightsPDFUp->Write();
  histWeightsPDFDown->Write();
  histTopPt->Write();
  histTopPtSq->Write();
  histRuns->Write();
  histPt->Write();
  CutFlowUnW->Write();
  CutFlow->Write();
  file->Write();
  file->Close();

  cout<<"done"<<endl;
  delete file;

}


