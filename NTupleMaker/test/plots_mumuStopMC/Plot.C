#include "HttStylesNew.cc"
#include "CMS_lumi.C"
#include <iostream>
#include <sstream>
using namespace std;
void Plot(TString directory = "./",
		TString Variable = "Dzeta",
		TString Suffix = "inclusive",
		int nBins  =     10,
		float xmin =       -500,
		float xmax =      200,
		//TString Weight = "mcweight*puweight*effweight*0.978824*0.985*",
		TString Weight = "all_weight",
		
		//TString Weight = "gen_weight*pu_weight*trig_weight && mu_relIso[0]<0.15 && ta_IsoFlagTight[0]>0.5 &&",
		//TString Cuts = " mu_relIso[0] <0.15 && ta_IsoFlagTight[0]>0.5 && ta_relIso[0]>0.85 && njets>0 && njets<4 && nbtag<2",
		TString Cuts = "mu_relIso[0] <0.15 && ta_IsoFlagTight[0]>0.5 && njets>0 && njets<4 && nbtag<2",
	//	TString Cuts = " Ptmiss>0 && mu_relIso[0] <0.15 && ta_IsoFlagTight[0]>0.5",
		//	  TString Cuts = "&&iso_1<0.15&&iso_2<0.2&&extraelec_veto<0.5&&extramuon_veto<0.5&&pt_1>13&&pt_2>15&&TMath::Max(pt_1,pt_2)>24",
		//	  TString Cuts = "&&dzeta<-40&&met>100&&iso_1<0.15&&iso_2<0.2&&extraelec_veto<0.5&&extramuon_veto<0.5&&pt_1>13&&pt_2>15&&TMath::Max(pt_1,pt_2)>24",
		TString CutsCategory = "",
		TString xtitle = "muon p_{T} [GeV]",
		TString ytitle = "Events / 5 GeV"
	 ) {

	SetStyle();

//	Cuts += CutsCategory;

	bool blindData = false;
	int nbMin = 12;
	int nbMax = 20;
	bool plotLeg = true;
	int position = 0; // 0 - right, 1 - left, 2 - central
	//  bool showSignal = true;
	bool showSignal = true;
	bool logY = true;

	TH1::SetDefaultSumw2();
	TH2::SetDefaultSumw2();

	double lumi = 35864;
	double TTnorm = 1.0;
	double Wnorm  = 1.0;
	double DYnorm  = 1.0;
	double scaleSignal = 50;

	TString Channel="mutau";

	string datasetName;
	ifstream fileIn;
	int pos_=0;
	string sampleNames[100] ;
	double xsec[100];

	fileIn.open("datasetsMC");

	string line;
	while(std::getline(fileIn, line))
	{
		float xsecs, xsec1, xsec2,xsec3;
		xsecs=1;xsec1=1;xsec2=1;xsec3=1;

		istringstream iss(line);
		iss >> datasetName >> xsecs >> xsec1 >> xsec2;
		xsecs *=  xsec1 * xsec2;
		sampleNames[pos_]=datasetName.c_str();
		xsec[pos_]=xsecs;
		pos_++;
		cout<< " read in  "<<datasetName<<"  "<<xsecs<<"  "<<xsec1<<"  "<<xsec2<<endl;
	
		//if (!fileIn.good()) break;
	}


	TString cuts[100];

	for (int i=0; i<pos_; ++i) {

	if (std::string::npos != sampleNames[i].find("JetsToLL")) Weight = "all_weight * zptmassweight";
	else Weight = "all_weight ";
		cout<<" sampleNames "<<sampleNames[i]<<"  "<<Weight<<endl;

	if (i==0)	cuts[i] = Weight + "&&  met_flag>0.5 &&"+ Cuts;


	else	cuts[i] = Weight + " && " + Cuts;

	}


	TH1D * hist[100];

	TH1D *hwj, *hdyj, *hztt, *hrest, *htt, *hstop, *hqcd;
	int nSamples = pos_;

	TCanvas * dummyCanv = new TCanvas("dummy","",600,600);

	TH1D* WInclw,*W1Jw,*W2Jw,*W3Jw,*W4Jw;
	TH1D* DYInclw,*DY1Jw,*DY2Jw,*DY3Jw,*DY4Jw;
	TString WInclname, W1Jname, W2Jname, W3Jname, W4Jname;
	TString DYInclname, DY1Jname, DY2Jname, DY3Jname, DY4Jname;
	TString app_="_Nominal_B";

	WInclname = "./WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0Parton"+app_+".root";
	W1Jname = "./W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+app_+".root";
	W2Jname = "./W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+app_+".root";
	W3Jname = "./W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+app_+".root";
	W4Jname = "./W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+app_+".root";

	DYInclname = "./DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_0Parton"+app_+".root";
	DY1Jname = "./DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+app_+".root";
	DY2Jname = "./DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+app_+".root";
	DY3Jname = "./DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+app_+".root";
	DY4Jname = "./DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"+app_+".root";

	TFile *WIncl = TFile::Open (WInclname, "read");

	TFile *W1J = TFile::Open (W1Jname, "read");
	TFile *W2J = TFile::Open (W2Jname, "read");
	TFile *W3J = TFile::Open (W3Jname, "read");
	TFile *W4J = TFile::Open (W4Jname, "read");
	TFile *DYIncl = TFile::Open (DYInclname, "read");
	TFile *DY1J = TFile::Open (DY1Jname, "read");
	TFile *DY2J = TFile::Open (DY2Jname, "read");
	TFile *DY3J = TFile::Open (DY3Jname, "read");
	TFile *DY4J = TFile::Open (DY4Jname, "read");


	DYInclw= (TH1D*)DYIncl->Get(Channel+"/"+"histWeightsH");
	DY1Jw= (TH1D*)DY1J->Get(Channel+"/"+"histWeightsH");
	DY2Jw= (TH1D*)DY2J->Get(Channel+"/"+"histWeightsH");
	DY3Jw= (TH1D*)DY3J->Get(Channel+"/"+"histWeightsH");
	DY4Jw= (TH1D*)DY4J->Get(Channel+"/"+"histWeightsH");
	WInclw= (TH1D*)WIncl->Get(Channel+"/"+"histWeightsH");
	W1Jw= (TH1D*)W1J->Get(Channel+"/"+"histWeightsH");
	W2Jw= (TH1D*)W2J->Get(Channel+"/"+"histWeightsH");
	W3Jw= (TH1D*)W3J->Get(Channel+"/"+"histWeightsH");
	W4Jw= (TH1D*)W4J->Get(Channel+"/"+"histWeightsH");


	htt = new TH1D("htt","",nBins,xmin,xmax);
	hwj = new TH1D("hwj","",nBins,xmin,xmax);
	hdyj = new TH1D("hdyj","",nBins,xmin,xmax);
	hztt = new TH1D("hztt","",nBins,xmin,xmax);
	hstop = new TH1D("hstop","",nBins,xmin,xmax);
	hrest = new TH1D("hrest","",nBins,xmin,xmax);
	hqcd = new TH1D("hqcd","",nBins,xmin,xmax);

	htt->Reset();
	hwj->Reset();
	hdyj->Reset();
	hztt->Reset();
	hstop->Reset();
	hrest->Reset();
	hqcd->Reset();

	// filling histograms
	TFile *file;
	TTree *tree;
	TH1D* histWeightsH;
	for (int i=0; i<nSamples; ++i) {
		string fname = sampleNames[i];

		//    std::cout << sampleNames[i] << std::endl;
		file = new TFile(directory+sampleNames[i]+"_Nominal_B.root");
		histWeightsH = (TH1D*)file->Get(Channel+"/"+"histWeightsH");

		tree = (TTree*)file->Get("T");
		float norm = float(xsec[i]*lumi)/float(histWeightsH->GetSumOfWeights());

		//norm=1;
	//	norm *=all_weights;

		if (std::string::npos != fname.find("WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_1Parton") || std::string::npos != fname.find("W1JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"))
			norm = lumi/ ( WInclw->GetSumOfWeights()/float(61526.7*Wnorm) + W1Jw->GetSumOfWeights()/float(1.221*9644.5*Wnorm));


		if (std::string::npos != fname.find("WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2Parton") || std::string::npos != fname.find("W2JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"))
			norm = lumi/ ( WInclw->GetSumOfWeights()/float(61526.7*Wnorm) + W2Jw->GetSumOfWeights()/float(1.221*3144.5*Wnorm));

		if (std::string::npos != fname.find("WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_3Parton") || std::string::npos != fname.find("W3JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"))
			norm = lumi/ ( WInclw->GetSumOfWeights()/float(61526.7*Wnorm) + W3Jw->GetSumOfWeights()/float(1.221*954.8*Wnorm));

		if (std::string::npos != fname.find("WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_4Parton") || std::string::npos != fname.find("W4JetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"))
			norm = lumi/ ( WInclw->GetSumOfWeights()/float(61526.7*Wnorm) + W4Jw->GetSumOfWeights()/float(1.221*485.6*Wnorm));


		if (std::string::npos != fname.find("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_1Parton") || std::string::npos != fname.find("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_isZTT_1Parton") || std::string::npos != fname.find("DY1JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"))
			norm = lumi/ ( float(DYInclw->GetSumOfWeights())/float(5765.4*DYnorm) + float(DY1Jw->GetSumOfWeights())/float(1.1637*1012.5*DYnorm));


		if (std::string::npos != fname.find("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_2Parton") || std::string::npos != fname.find("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_isZTT_2Parton") || std::string::npos != fname.find("DY2JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"))
			norm = lumi/ ( DYInclw->GetSumOfWeights()/float(5765.4*DYnorm) + float(DY2Jw->GetSumOfWeights())/float(1.1637*332.8*DYnorm));

		if (std::string::npos != fname.find("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_3Parton") || std::string::npos != fname.find("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_isZTT_3Parton") || std::string::npos != fname.find("DY3JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"))
			norm = lumi/ ( DYInclw->GetSumOfWeights()/float(5765.4*DYnorm) + float(DY3Jw->GetSumOfWeights())/float(1.1637*101.8*DYnorm));

		if (std::string::npos != fname.find("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_4Parton") || std::string::npos != fname.find("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_isZTT_4Parton") || std::string::npos != fname.find("DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"))
			norm = lumi/ ( DYInclw->GetSumOfWeights()/float(5765.4*DYnorm) + float(DY4Jw->GetSumOfWeights())/float(1.1637*54.8*DYnorm));


		
		if (std::string::npos != fname.find("Single")) norm=1;


		TString histName = sampleNames[i] + Variable ;
		hist[i] = new TH1D(histName,"",nBins,xmin,xmax);
		//    hist[i] = new TH1D(histName,"",nBins,xbins);
		hist[i]->Sumw2();
		tree->Draw(Variable+">>"+histName,cuts[i]);
		
	//	if (i>0) {
			for (int iB=1; iB<=nBins; ++iB) {
				double x = hist[i]->GetBinContent(iB);
				double e = hist[i]->GetBinError(iB);
				hist[i]->SetBinContent(iB,x);
				hist[i]->SetBinError(iB,e);
			}
	//	}
		hist[i]->Scale(norm);
		hist[i]->Sumw2();
		std::cout << "Sample " <<sampleNames[i] << " " << hist[i]->GetEntries() << " " << hist[i]->Integral(0,nBins+1) <<" xsec "<<xsec[i]<<" norm  "<<norm<<"  "<<cuts[i]<< "  "<<endl;

		//if (std::string::npos == fname.find("Stop") && std::string::npos == fname.find("Single")) allbkg->Add(hist[i]);

		if ((std::string::npos != fname.find("wJets")|| std::string::npos != fname.find("WJetsToLNu") || std::string::npos != fname.find("W1JetsToLNu") || std::string::npos != fname.find("W2JetsToLNu") 						                        || std::string::npos != fname.find("W3JetsToLNu") || std::string::npos != fname.find("W4JetsToLNu")) && std::string::npos == fname.find("TTW") )  hwj->Add(hist[i]);

		if (std::string::npos != fname.find("TT_Tune")) htt->Add(hist[i]);
		if (std::string::npos != fname.find("QCD")) hqcd->Add(hist[i]);
		if ( (std::string::npos != fname.find("DYJets") || std::string::npos != fname.find("DY1Jets") ||  std::string::npos != fname.find("DY2Jets") || std::string::npos != fname.find("DY3Jets") || std::string::npos != fname.find("DY4Jets") )&& std::string::npos == fname.find("isZTT") )  hdyj->Add(hist[i]);

		if ( std::string::npos != fname.find("isZTT")) hztt->Add(hist[i]);
		if  ( std::string::npos != fname.find("ST_") || std::string::npos != fname.find("channel") ) hstop->Add(hist[i]);

		if ( std::string::npos != fname.find("WWTo")  ) {hrest->Add(hist[i]);}


		if ( (std::string::npos != fname.find("WW") || std::string::npos != fname.find("ZZ") ||  std::string::npos != fname.find("WZ") || std::string::npos != fname.find("WG") || std::string::npos != fname.find("ZG") ) && std::string::npos == fname.find("WWTo") ) {hrest->Add(hist[i]);}


		if ( std::string::npos != fname.find("TTW") || std::string::npos != fname.find("TTZ") || std::string::npos != fname.find("TG") || std::string::npos != fname.find("tG") || std::string::npos != fname.find("TTG") || std::string::npos != fname.find("ttW") || std::string::npos != fname.find("tZ") || std::string::npos != fname.find("TTT_") ) {hrest->Add(hist[i]);}


	}


	//TH1D * histData = (TH1D*)hist[0]->Clone("data_obs");
	TH1D * QCD = (TH1D*)hqcd->Clone("QCD");
	TH1D * ZTT = (TH1D*)hztt->Clone("ZTT");
	TH1D * ZLL = (TH1D*)hdyj->Clone("ZLL");
	TH1D * W   = (TH1D*)hwj->Clone("W");
	TH1D * TT  = (TH1D*)htt->Clone("TT");
	TH1D * SingleT  = (TH1D*)hstop->Clone("SingleT");
	TH1D * Rest  = (TH1D*)hrest->Clone("Rest");
	TH1D * StopA = (TH1D*)hist[1]->Clone("StopA");
	TH1D * StopB = (TH1D*)hist[2]->Clone("StopB");

	TH1D *allbkg = (TH1D*)htt->Clone("allbkg");
	allbkg->Add(SingleT);
	allbkg->Add(QCD);
	allbkg->Add(ZTT);
	allbkg->Add(ZLL);
	allbkg->Add(W);
	allbkg->Add(Rest);

	TH1D * histData = (TH1D*)allbkg->Clone("data_obs");

	TT->Add(SingleT);

	cout<<" ok here "<<endl;
	std::cout << "QCD : " << QCD->GetSumOfWeights() << " : " << QCD->Integral(1,nBins+1) << std::endl;
	std::cout << "Rest  : " << Rest->GetSumOfWeights() << " : " << Rest->Integral(1,nBins+1) << std::endl;
	std::cout << "W   : " << W->GetSumOfWeights() << " : " << W->Integral(1,nBins+1) << std::endl;
	std::cout << "TT  : " << TT->GetSumOfWeights() << " : " << TT->Integral(1,nBins+1) << std::endl;
	std::cout << "ZLL : " << ZLL->GetSumOfWeights() << " : " << ZLL->Integral(1,nBins+1) << std::endl;
	std::cout << "ZTT : " << ZTT->GetSumOfWeights() << " : " << ZTT->Integral(1,nBins+1) << std::endl;

	// ***********************************
	// **** Systematic uncertainties *****
	// ***********************************
	TH1D * dummy = (TH1D*)allbkg->Clone("dummy");
	float errlumi = 0.025;
	float errMuon = 0.02;
	float errElectron = 0.02;
	float errQCD = 0.; // normalization of QCD background
	float errRest = 0.15;  // normalization of Rest background
	float errW = 0.1;    // normalization of W+Jets background
	float errTT = 0.07;  // normalization of TT background
	float errZ  = 0.03;  // normalization of Z background
	for (int iB=1; iB<=nBins; ++iB) {
		float eQCD = errQCD*QCD->GetBinContent(iB);
		float eRest = errRest*Rest->GetBinContent(iB);
		float eW = errW*W->GetBinContent(iB);
		float eTT = errTT*TT->GetBinContent(iB);
		float eZ  = errZ*ZTT->GetBinContent(iB);
		float err2 = eQCD*eQCD + eRest*eRest + eW*eW + eTT*eTT;
		float errTot = TMath::Sqrt(err2);
		dummy->SetBinError(iB,errTot);
	}


	std::cout << "BKG : " << allbkg->GetSumOfWeights() << " : " << allbkg->Integral(0,nBins+1) << std::endl;
	std::cout << "DAT : " << histData->GetSumOfWeights() << " : " << histData->Integral(0,nBins+1) << std::endl;
	std::cout << "DAT/BKG = " << histData->GetSumOfWeights()/allbkg->GetSumOfWeights() << "+/-" 
		<< TMath::Sqrt(histData->GetSumOfWeights())/allbkg->GetSumOfWeights() << std::endl;

	TH1D * bkgdErr = (TH1D*)allbkg->Clone("bkgdErr");
	bkgdErr->SetFillStyle(3013);
	bkgdErr->SetFillColor(1);
	bkgdErr->SetMarkerStyle(21);
	bkgdErr->SetMarkerSize(0);

	for (int iB=1; iB<=nBins; ++iB) {
		QCD->SetBinError(iB,0);
		Rest->SetBinError(iB,0);
		TT->SetBinError(iB,0);
		W->SetBinError(iB,0);
		ZLL->SetBinError(iB,0);
		ZTT->SetBinError(iB,0);
	//	allbkg->SetBinError(iB,0);
		float eStat =  bkgdErr->GetBinError(iB);
		float X = bkgdErr->GetBinContent(iB);
		float elumi = errlumi * X;
		float eMuon = errMuon * X;
		float eElectron = errElectron * X;
		float eBkg = dummy->GetBinError(iB);
		float Err = TMath::Sqrt(eStat*eStat+elumi*elumi+eBkg*eBkg+eMuon*eMuon+eElectron*eElectron);
		bkgdErr->SetBinError(iB,Err);
		bkgdErr->SetBinContent(iB,allbkg->GetBinContent(iB));
	//	StopA->SetBinError(iB,0);
	//	StopB->SetBinError(iB,0);
	
	}


	histData->SetMarkerColor(1);
	histData->SetLineColor(1);
	histData->SetFillColor(1);
	histData->SetFillStyle(0);
	histData->SetLineWidth(2);
	histData->SetMarkerStyle(20);
	histData->SetMarkerSize(1.2);
	histData->SetLabelSize(0);

	StopA->Scale(scaleSignal);
	StopB->Scale(scaleSignal);
	StopA->SetLineColor(2);
	StopA->SetMarkerColor(2);
	StopB->SetLineColor(4);
	StopB->SetMarkerColor(4);
	StopB->SetFillColor(0);
	StopA->SetFillColor(0);


	int mycolor=TColor::GetColor("#ffcc66");
	int mycolorvv=TColor::GetColor("#8646ba");
	int mycolorqcd=TColor::GetColor("#ffccff");
	int mycolortt=TColor::GetColor("#9999cc");
	int mycolorttx=TColor::GetColor("#33CCFF");
	int mycolorwjet=TColor::GetColor("#de5a6a");
	int mycolordyj=TColor::GetColor("#ffcc66");
	int mycolorztt=TColor::GetColor("#58d885");
	int mycolorst=TColor::GetColor("#b6d0ea");

	int mycolorww=TColor::GetColor("#C390D4");

	InitData(histData); histData->GetXaxis()->SetRangeUser(xmin,xmax);  
	InitHist(QCD,TColor::GetColor("#ffccff"));
	InitHist(ZLL,TColor::GetColor("#ffcc66"));
	InitHist(TT,TColor::GetColor("#9999cc"));
	InitHist(Rest,TColor::GetColor("#8646ba"));
	InitHist(W,TColor::GetColor("#de5a6a"));
	InitHist(ZTT,TColor::GetColor("#58d885"));

	histData->GetXaxis()->SetTitle(xtitle);
	histData->GetYaxis()->SetTitle(ytitle);
	histData->GetYaxis()->SetTitleSize(0.06);
	histData->SetMarkerSize(1.2);
	histData->GetYaxis()->SetTitleOffset(1.5);

	float yUpper = histData->GetMaximum();
	if (logY)
		histData->GetYaxis()->SetRangeUser(0.5,15*yUpper);
	else
		histData->GetYaxis()->SetRangeUser(0,1.2*yUpper);

	float yMin = 0.5;
	float yMax = 10*yUpper;

	//  nData = histData->GetSum();
	//  float nMC   = TT->GetSum();
	//  float eData = TMath::Sqrt(nData);

	float chi2 = 0;
	for (int iB=1; iB<=nBins; ++iB) {
		float xData = histData->GetBinContent(iB);
		float xMC = allbkg->GetBinContent(iB);
		if (xMC>1e-1) {
			float diff2 = (xData-xMC)*(xData-xMC);
			chi2 += diff2/xMC;
		}

/*		if (blindData) {
			if (iB>=nbMin&&iB<=nbMax) {
				histData->SetBinContent(iB,100000);
				histData->SetBinError(iB,0);
			}
		}
*/

	}
	std::cout << std::endl;
	std::cout << "Chi2 = " << chi2 << std::endl;
	std::cout << std::endl;

	TCanvas * canv1 = MakeCanvas("canv1", "", 600, 600);
	//TPad *upper = new TPad("upper", "pad",0,0.31,1,1);
	TPad *upper = new TPad("upper", "pad",0,0,1,1);
	upper->Draw();
	upper->cd();
	upper->SetFillColor(0);
	upper->SetBorderMode(0);
	upper->SetBorderSize(10);
	upper->SetTickx(1);
	upper->SetTicky(1);
	upper->SetLeftMargin(0.20);
	upper->SetRightMargin(0.05);
	upper->SetBottomMargin(0.02);
	upper->SetBottomMargin(0.1);
	upper->SetFrameFillStyle(0);
	upper->SetFrameLineStyle(0);
	upper->SetFrameLineWidth(2);
	upper->SetFrameBorderMode(0);
	upper->SetFrameBorderSize(10);
	upper->SetFrameFillStyle(0);
	upper->SetFrameLineStyle(0);
	upper->SetFrameLineWidth(2);
	upper->SetFrameBorderMode(0);
	upper->SetFrameBorderSize(10);

	allbkg->SetMarkerColor(kBlue);
	allbkg->SetFillColor(kBlue);
	allbkg->SetLineColor(kBlue);
	allbkg->SetLineWidth(1);
	allbkg->SetFillStyle(3022);

	histData->Draw("e1");
	//allbkg->Draw("sameh");
	
        THStack *hs = new THStack("hs","");
	
	hs->Add(QCD);
	hs->Add(Rest);
	hs->Add(ZLL);
	hs->Add(ZTT);
	hs->Add(TT);
	hs->Add(W);
	/*
	ZLL->Draw("sameh");
	Rest->Draw("sameh");
	QCD->Draw("sameh");
	ZTT->Draw("sameh");
//	TT->Draw("sameh");

//	W->Draw("sameh");
*/
//	histData->Draw("e1same");
//	bkgdErr->Draw("e2same");
	
	TH1D *hsum = ((TH1D*)(hs->GetStack()->Last()));
	hsum->Draw("h");
	hs->Draw("sameh");

	if (showSignal) {
		StopA->Draw("hsame");
		StopB->Draw("hsame");
	}    

	TLegend * leg = new TLegend(0.65,0.45,0.85,0.8);
	if (position==1)
		leg = new TLegend(0.24,0.5,0.4,0.9);
	SetLegendStyle(leg);
	leg->SetTextSize(0.05);
	//leg->AddEntry(histData,"Data","lp");
	leg->AddEntry(Rest,"Rest","f");
	leg->AddEntry(ZTT,"Z#rightarrow #tau#tau","f");
	leg->AddEntry(ZLL,"Z#rightarrow ll","f");
	leg->AddEntry(TT,"t#bar{t}","f");
	leg->AddEntry(QCD,"QCD","f");
	leg->AddEntry(W,"E/W","f");

	if (showSignal) {
		leg->AddEntry(StopA,"StopA(x50)","l");
		leg->AddEntry(StopB,"StopB(x50)","l");
	}
	if (plotLeg)
		leg->Draw();
	writeExtraText = true;
	extraText = "Preliminary";
	CMS_lumi(upper,4,33); 
	plotchannel("#mu#tau",0.25,0.84);

	char KT[100];
	sprintf(KT,"#chi^{2} : %5.1f",chi2);
	TLatex * cms = new TLatex(0.25,0.85,KT);
	cms->SetNDC();
	cms->SetTextSize(0.05);
	//  cms->Draw();

	if (logY) upper->SetLogy(true);

	upper->Draw("SAME");
	upper->RedrawAxis();
	upper->Modified();
	upper->Update();
	canv1->cd();

	TH1D * ratioH = (TH1D*)histData->Clone("ratioH");
	TH1D * ratioErrH = (TH1D*)bkgdErr->Clone("ratioErrH");
	ratioH->SetMarkerColor(1);
	ratioH->SetMarkerStyle(20);
	ratioH->SetMarkerSize(1.4);
	ratioH->SetLineColor(1);
	ratioH->GetYaxis()->SetRangeUser(0.41,1.59);
	ratioH->GetYaxis()->SetNdivisions(505);
	ratioH->GetXaxis()->SetLabelFont(42);
	ratioH->GetXaxis()->SetLabelOffset(0.04);
	ratioH->GetXaxis()->SetLabelSize(0.14);
	ratioH->GetXaxis()->SetTitleSize(0.12);
	ratioH->GetXaxis()->SetTitleOffset(1.4);
	ratioH->GetYaxis()->SetTitle("obs/exp");
	ratioH->GetYaxis()->SetLabelFont(42);
	ratioH->GetYaxis()->SetLabelOffset(0.015);
	ratioH->GetYaxis()->SetLabelSize(0.13);
	ratioH->GetYaxis()->SetTitleSize(0.14);
	ratioH->GetYaxis()->SetTitleOffset(0.6);
	ratioH->GetXaxis()->SetTickLength(0.07);
	ratioH->GetYaxis()->SetTickLength(0.02);
	ratioH->GetYaxis()->SetLabelOffset(0.01);
	ratioH->SetMarkerSize(1.2);

	for (int iB=1; iB<=nBins; ++iB) {
		float x1 = histData->GetBinContent(iB);
		float x2 = allbkg->GetBinContent(iB);
		ratioErrH->SetBinContent(iB,1.0);
		ratioErrH->SetBinError(iB,0.0);
		float xBkg = bkgdErr->GetBinContent(iB);
		float errBkg = bkgdErr->GetBinError(iB);
		if (xBkg>0) {
			float relErr = errBkg/xBkg;
			ratioErrH->SetBinError(iB,relErr);

		}
		if (x1>0&&x2>0) {
			float e1 = histData->GetBinError(iB);
			float ratio = x1/x2;
			float eratio = e1/x2;
			ratioH->SetBinContent(iB,ratio);
			ratioH->SetBinError(iB,eratio);
		}
		else {
			ratioH->SetBinContent(iB,1000);
		}
	}

	// ------------>Primitives in pad: lower
	TPad * lower = new TPad("lower", "pad",0,0,1,0.30);
	//lower->Draw();
	lower->cd();
	lower->SetFillColor(0);
	lower->SetBorderMode(0);
	lower->SetBorderSize(10);
	lower->SetGridy();
	lower->SetTickx(1);
	lower->SetTicky(1);
	lower->SetLeftMargin(0.20);
	lower->SetRightMargin(0.05);
	lower->SetTopMargin(0.026);
	lower->SetBottomMargin(0.35);
	lower->SetFrameFillStyle(0);
	lower->SetFrameLineStyle(0);
	lower->SetFrameLineWidth(2);
	lower->SetFrameBorderMode(0);
	lower->SetFrameBorderSize(10);
	lower->SetFrameFillStyle(0);
	lower->SetFrameLineStyle(0);
	lower->SetFrameLineWidth(2);
	lower->SetFrameBorderMode(0);
	lower->SetFrameBorderSize(10);

	ratioH->Draw("e1");
	ratioErrH->Draw("e2same");

	lower->Modified();
	lower->RedrawAxis();
	canv1->cd();
	canv1->Modified();
	canv1->cd();
	canv1->SetSelected(canv1);

	if (logY) {
		canv1->Print("figures/"+Variable+"_"+Suffix+"_logY.png");
		//      canv1->Print("figures/"+Variable+"_"+Suffix+"_logY.pdf","Portrait pdf");
	}
	else {
		canv1->Print("figures/"+Variable+"_"+Suffix+".png");
		//      canv1->Print("figures/"+Variable+"_"+Suffix+".pdf","Portrait pdf");
	}

}
