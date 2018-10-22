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
#include "TRandom3.h"
#include "TGraphAsymmErrors.h"
#include <stdlib.h>

#include "DesyTauAnalyses/NTupleMaker/interface/Jets.h"
#include "DesyTauAnalyses/NTupleMaker/interface/AnalysisMacro.h"
int main(int argc, char * argv[]) {



  // **** configuration
  Config cfg(argv[1]);
  string Channel="elel";

  // kinematic cuts on electrons
  const bool isData = cfg.get<bool>("IsData");
  
  
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



  // kinematics electrons
  const float  ptElectronCut       = cfg.get<float>("ptElectronCuteltau");
  const double etaElectronCut     = cfg.get<double>("etaElectronCuteltau");
  const double dxyElectronCut     = cfg.get<double>("dxyElectronCuteltau");
  const double dzElectronCut      = cfg.get<double>("dzElectronCuteltau");
  const double isoElectronLowCut  = cfg.get<double>("isoElectronLowCuteltau");
  const bool applyElectronId     = cfg.get<bool>("ApplyElectronId");




////////////muons

  const double ptMuonCut   = cfg.get<double>("ptMuonCut");
  const double etaMuonCut     = cfg.get<double>("etaMuonCut");
  const double dxyMuonCut     = cfg.get<double>("dxyMuonCut");
  const double dzMuonCut      = cfg.get<double>("dzMuonCut");
  const double isoMuonLowCut  = cfg.get<double>("isoMuonLowCut");
  const bool applyMuonId     = cfg.get<bool>("ApplyMuonId");

////// tau
  const double ptTauCut = cfg.get<double>("ptTauCut"); 
  const double etaTauCut = cfg.get<double>("etaTauCut"); 
  const double decayModeFinding    = cfg.get<double>("decayModeFinding");
  const double  againstElectronVLooseMVA6  = cfg.get<double>("againstElectronVLooseMVA6");
  const double  againstMuonTight3  = cfg.get<double>("againstMuonTight3");
  const double  vertexz =  cfg.get<double>("vertexz");
  const double  byCombinedIsolationDeltaBetaCorrRaw3Hits = cfg.get<double>("byCombinedIsolationDeltaBetaCorrRaw3Hits");


  // veto muons
  const float ptVetoMuonCut   = cfg.get<float>("ptVetoMuonCut");
  const float etaVetoMuonCut  = cfg.get<float>("etaVetoMuonCut");
  const float dxyVetoMuonCut   = cfg.get<float>("dxyVetoMuonCut");
  const float dzVetoMuonCut   = cfg.get<float>("dzVetoMuonCut");
  const float isoVetoMuonCut   = cfg.get<float>("isoVetoMuonCut");
  const bool applyVetoMuonId     = cfg.get<bool>("ApplyVetoMuonId");

  // dilemuon veto 
  const float ptDilepMuonCut = cfg.get<float>("ptDilepMuonCut");
  const float etaDilepMuonCut = cfg.get<float>("etaDilepMuonCut");
  const float dxyDilepMuonCut = cfg.get<float>("dxyDilepMuonCut");
  const float dzDilepMuonCut = cfg.get<float>("dzDilepMuonCut");
  const float isoDilepMuonCut = cfg.get<float>("isoDilepMuonCut");
  const float dRDilepVetoCut = cfg.get<float>("dRDilepVetoCut");


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



  const string ElectronIdIsoEffFile = cfg.get<string>("ElectronIdIsoEffFile");
  const string ElectrontrigEffFile = cfg.get<string>("ElectrontrigEffFile");


  const string Region  = cfg.get<string>("Region");
  const string Sign  = cfg.get<string>("Sign");




  // kinematic cuts on Jets
  const double etaJetCut   = cfg.get<double>("etaJetCut");
  const double ptJetCut   = cfg.get<double>("ptJetCut");

  const double dRleptonsCut   = cfg.get<double>("dRleptonsCut");
  const double deltaRTrigMatch = cfg.get<double>("DRTrigMatch");

  const string TrigLeg  = cfg.get<string>("SingleElectronFilterName") ;
  const double SingleElectronTriggerPtCut = cfg.get<double>("SingleElectronTriggerPtCut");


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



	
	//TFile * SFfile = new TFile(TString(cmsswBase)+"/src/DesyTauAnalyses/NTupleMaker/data/ElectronTight_PTEta.root","read");
	//TH2D * SFhisto = (TH2D*)SFfile->Get("FullSimOverDelphes");



    for (Long64_t iEntry=0; iEntry<numberOfEntries; ++iEntry) { 

      Float_t weight = 1.;
      
      all_weight = 1.;
      gen_weight = 1.;

      analysisTree.GetEntry(iEntry);
      nEvents++;

      //std::cout << "      number of entries in Tree = " << numberOfEntries <<" starting weight "<<weight<< std::endl;

      if (nEvents%50000==0) 
	cout << "      processed " << nEvents << " events" << endl; 


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

	    weight *= analysisTree.genweight;
	    gen_weight *=analysisTree.genweight;
					

	
      vector<unsigned int> isoElectrons; isoElectrons.clear();
      vector<int> electrons; electrons.clear();
      vector<int> allElectrons ; allElectrons.clear();
      vector<float> isoElectronsValue; isoElectronsValue.clear();
      for (unsigned int ie = 0; ie<analysisTree.electron_count; ++ie) {
	allElectrons.push_back(ie);

	if (analysisTree.electron_pt[ie]<SingleElectronTriggerPtCut) continue;
	if (fabs(analysisTree.electron_eta[ie])>etaElectronCut) continue;
	if (fabs(analysisTree.electron_charge[ie]) !=1) continue;

	float relIso=analysisTree.electron_relIso[ie];
	if (relIso>0.3) continue;

	  electrons.push_back((int)ie);
	  isoElectrons.push_back(ie);
	  isoElectronsValue.push_back(relIso);


      }

      	if (electrons.size()==0) continue;


      int indx1 = -1;
      int indx2 = -1;
      bool isIsoElectronsPair = false;
      float isoMin = 999;
      if (isoElectrons.size()>0) {
	for (unsigned int im1=0; im1<isoElectrons.size(); ++im1) {
	  unsigned int index1 = isoElectrons[im1];

	    for (unsigned int iEl=0; iEl<allElectrons.size(); ++iEl) {
	      unsigned int indexProbe = allElectrons[iEl];

	      if (index1==indexProbe) continue;
	      float q1 = analysisTree.electron_charge[index1];
	      float q2 = analysisTree.electron_charge[indexProbe];
	      if (q1*q2>0) continue;
	      float dR = deltaR(analysisTree.electron_eta[index1],analysisTree.electron_phi[index1],
				analysisTree.electron_eta[indexProbe],analysisTree.electron_phi[indexProbe]);
	      if (dR<dRleptonsCut) continue; 
	    }

	  for (unsigned int im2=im1+1; im2<isoElectrons.size(); ++im2) {
	    unsigned int index2 = isoElectrons[im2];
	    float q1 = analysisTree.electron_charge[index1];
	    float q2 = analysisTree.electron_charge[index2];
	      if (q1*q2>0) continue;


	    float dRelel = deltaR(analysisTree.electron_eta[index1],analysisTree.electron_phi[index1],
				  analysisTree.electron_eta[index2],analysisTree.electron_phi[index2]);

	    if (dRelel>dRleptonsCut) {
	     //double sumIso = analysisTree.electron_pt[im1]+analysisTree.electron_pt[im2];
	     double sumIso = isoElectronsValue[im1]+isoElectronsValue[im2] ; 
	      if (sumIso<isoMin) {
		isIsoElectronsPair = true;
		isoMin = sumIso;
		if (analysisTree.electron_pt[index1]>analysisTree.electron_pt[index2]) {
		  indx1 = (int)index1;
		  indx2 = (int)index2;
		}
		else {
		  indx2 = (int)index1;
		  indx1 = (int)index2;
		}
	      }
	    }
	  }
	}
      }//isElectrons



      int el_index_1 = indx1;
      int el_index_2 = indx2;
      int el_index_3 = -1;

      if (el_index_1 <0 || el_index_2 <0)continue;


      
      double q = analysisTree.electron_charge[el_index_1] * analysisTree.electron_charge[el_index_2];
      event_sign  = q;
	
      if (event_sign >0) continue;



  bool          dilepton_veto=false;
  bool          extraelec_veto=false;
  bool          extramuon_veto=false;

  event_secondLeptonVeto = false;
  event_thirdLeptonVeto = false;

      // looking for extra electron
      bool foundExtraElectron = false;
      int foundThirdLepton =0;
      for (unsigned int ie = 0; ie<analysisTree.electron_count; ++ie) {
	if (int(ie)==(int)el_index_1) continue;
	if (int(ie)==(int)el_index_2) continue;

	if (analysisTree.electron_pt[ie]<ptVetoElectronCut) continue;
	if (fabs(analysisTree.electron_eta[ie])>etaVetoElectronCut) continue;
	float relIsoEle = analysisTree.electron_relIso[ie];	
	if (relIsoEle>isoVetoElectronCut) continue;
	foundExtraElectron = true;
	foundThirdLepton++;
	if (foundThirdLepton==1) el_index_3 = (int)ie;
      }


      // looking for extra muon
      bool foundExtraMuon = false;
      for (unsigned int im = 0; im<analysisTree.muon_count; ++im) {
	if (analysisTree.muon_pt[im]<ptVetoMuonCut) continue;
	if (fabs(analysisTree.muon_eta[im])>etaVetoMuonCut) continue;
	float relIsoMu = analysisTree.muon_relIso[im];	
	if (relIsoMu>isoVetoMuonCut) continue;
	foundExtraMuon = true;
      }


      extraelec_veto = foundExtraElectron;
      extramuon_veto = foundExtraMuon;

	if(extraelec_veto || extramuon_veto)   event_thirdLeptonVeto = true;

//	if (event_thirdLeptonVeto) continue;
//	if (event_thirdLeptonVeto && foundThirdLepton>1) continue;



      //////////////////////////////////////////////
      electron_index_1 = (int)el_index_1;
      electron_index_2 = (int)el_index_2;
      electron_index = (int)el_index_3;

      mu_count= (int)analysisTree.muon_count;
      //cout<<" here ============================> "<<iEntry<<"  "<<mu_count<<"  "<<(int)analysisTree.muon_count<<"  "<<analysisTree.muon_count<<endl;

      el_count=(int)electrons.size();

      for (unsigned int ie=0;ie<electrons.size(); ++ie){
	unsigned int eIndex = electrons[ie];
	el_px[ie]=analysisTree.electron_px[eIndex];
	el_py[ie]=analysisTree.electron_py[eIndex];
	el_pz[ie]=analysisTree.electron_pz[eIndex];
	el_eta[ie]=analysisTree.electron_eta[eIndex];
	el_pt[ie]=analysisTree.electron_pt[eIndex];
	el_phi[ie]=analysisTree.electron_phi[eIndex];
	el_charge[ie]=analysisTree.electron_charge[eIndex];
	el_relIsoEl[ie]  = analysisTree.electron_relIso[eIndex] ;
      }
	el_relIso[0]  = analysisTree.electron_relIso[el_index_1] ;
	el_relIso[1]  = analysisTree.electron_relIso[el_index_2] ;


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
	jet_btag[jj] = analysisTree.pfjet_btag[jj][0];
      }



      ////////jets cleaning 
      TLorentzVector leptonsV, muonJ, jetsLV;



      /////////////////////////////////////////////////


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

	double Dr=deltaR(analysisTree.electron_eta[el_index_1],analysisTree.electron_phi[el_index_1],
			 analysisTree.pfjet_eta[jet],analysisTree.pfjet_phi[jet]);
	if (  Dr  < DRmax)  cleanedJet=false;


	double Drr=deltaR(analysisTree.electron_eta[el_index_2],analysisTree.electron_phi[el_index_2],
						  analysisTree.pfjet_eta[jet],analysisTree.pfjet_phi[jet]);

	if ( Drr < DRmax) cleanedJet=false;

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
  CutFlowUnW->Write();
  file->Write();
  file->Close();





  cout<<"done"<<endl;
  delete file;

}
