#include "TH2.h"
#include "TH1.h"
#include "TFile.h"

void getWeights(){

	int Names =6;
	
	string Model="Stop";
	TString channel = "mutau";
	string channelv ="mutau";
	string Channel = "#mu-#tau";

	if (channel =="eltau") Channel="e-#tau";
	if (channel =="muel") Channel="#mu-e";
	
	gStyle->SetPaintTextFormat("4.4f");

	TH2D *eff[20];
	int xmin=200;
	int ymin=0;
	int xmax=425;
	int ymax=75;

	float bwidth=25;
	//if (Model != "C1N2") bwidth = 50;
	int xbins = (xmax-xmin)/bwidth;
	int ybins = (ymax-ymin)/bwidth;
	char name_[100];
	TCanvas *c1 ;
	c1 = new TCanvas("c1","c1",800,800);

	for (int iB =12; iB<19 ; iB++)
	eff[iB] = new TH2D ("eff","",xbins,xmin,xmax,ybins,ymin,ymax);

	vector <string> titles;
	ifstream ifs("datasetEffs");


	cout<<" will use ... "<<Model<<endl;

	string line;
	while(std::getline(ifs, line)) // read one line from ifs
	{
		istringstream iss(line); // access line as a stream
		string dataname;
		float XSec;	
		float xs,fact,xvalue,yvalue;
		xs=0;fact=1;xvalue=0;yvalue=0;
		iss >> dataname >>  xvalue >> yvalue;


		titles.push_back(dataname+"_B.root"); 


		TFile *ff = new TFile (titles[0].c_str(),"read");

	TH1D* histo , *cutFlow, *hmet;
	//ff->ls();
	histo = 	(TH1D*)ff->Get(channel+"/histWeightsH");
	cutFlow = 	(TH1D*)ff->Get(channel+"/CutFlowUnW");


	
	//cout<<" ================================================================================================== "<<endl;
	cout<<dataname<<endl;
	for (int iB =12; iB<19 ; iB++){
	//cout<<cutFlow->GetXaxis()->GetBinLabel(iB)<<" & "<<setprecision(2)<<cutFlow->GetBinContent(iB)/histo->GetSumOfWeights()<<endl;
	
	sprintf(name_,"%s/met_MTDil_%i",channelv.c_str(),iB);
	hmet = 	(TH1D*)ff->Get(name_);
	float effs = cutFlow->GetBinContent(iB)/histo->GetSumOfWeights();
	//float effs = hmet->GetSumOfWeights()/histo->GetSumOfWeights();

	eff[iB]->Fill(xvalue,yvalue,effs);
	
	sprintf(name_,"%s",cutFlow->GetXaxis()->GetBinLabel(iB));
	eff[iB]->SetName(name_);

		}
	titles.clear();
	}

	 TPad *pad = new TPad("pad","pad",0, 0, 0.95,0.95);
	TFile *out ; out = new TFile("effs.root","recreate");
	out->cd();
	for (int iB =12; iB<19 ; iB++)
	{
	
	eff[iB]->SetStats(00000);	
	//eff[iB]->Fill(0,0,0.);
	//eff[iB]->GetZaxis()->SetRangeUser(0.0001, 1.1*eff[iB]->GetMaximum());
	
        eff[iB]->GetZaxis()->SetLabelFont(42);
        eff[iB]->GetZaxis()->SetTitleFont(42);
        eff[iB]->GetZaxis()->SetLabelSize(0.02);
        eff[iB]->GetZaxis()->SetTitleSize(0.025);
        //eff[iB]->GetZaxis()->SetTitle("Efficiency");
        eff[iB]->GetZaxis()->SetTitleOffset(1);
        eff[iB]->GetZaxis()->SetRangeUser(0.9*eff[iB]->GetMinimum(),1.1*eff[iB]->GetMaximum());

        # define the palette for z axis
	const int        NRGBs = 5;
	const int        NCont = 255;
	gStyle->SetNumberContours(NCont);
	Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
	Double_t red[NRGBs]   = { 0.50, 0.50, 1.00, 1.00, 1.00 };
	Double_t green[NRGBs] = { 0.50, 1.00, 1.00, 0.60, 0.50 };
	Double_t blue[NRGBs]  = { 1.00, 1.00, 0.50, 0.40, 0.50 };
	TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
	c1->cd();	
	pad->Draw();
	pad->cd();
	eff[iB]->Draw("colz text");

	gPad->Update();
	TPaletteAxis *palette = (TPaletteAxis*)eff[iB]->GetListOfFunctions()->FindObject("palette");
        palette->SetX1NDC(1.-0.013);
        palette->SetY1NDC(0.1);
        palette->SetX2NDC(1-0.08);
        palette->SetY2NDC(1.-0.1);
        palette->SetLabelFont(42);
        palette->SetLabelSize(0.035);

	TLatex textCOLZ; 
	const char *longstring = "Efficiency";
        textCOLZ.SetNDC();
        textCOLZ.SetTextAlign(13);
        textCOLZ.SetTextFont(42);
        textCOLZ.SetTextSize(0.035);
        textCOLZ.SetTextAngle(90);
//        textCOLZ.DrawLatex(0.95,0.15,longstring);
//	textCOLZ.Draw("sames");

	eff[iB]->GetYaxis()->SetTitle("m_{#lower[-0.12]{#tilde{#chi}}#lower[0.2]{#scale[0.85]{^{0}}}#kern[-1.3]{#scale[0.85]{_{1}}}} [GeV] ");
	eff[iB]->GetYaxis()->SetTitleOffset(1.4);
	eff[iB]->GetXaxis()->SetTitle("m#kern[0.1]{_{#lower[-0.12]{#tilde{t_{1}}/#tilde{#chi}_{1}^{#pm}}}} [GeV]");
	sprintf (name_,"Efficiency for %s (%s)",Model.c_str(), Channel.c_str());
	eff[iB]->SetTitle(name_);

	eff[iB]->Write();
	
	sprintf(name_,"effs_%s_%s_%s.png",Model.c_str(),channelv.c_str(),eff[iB]->GetName());
	c1->Print(name_);
	sprintf(name_,"effs_%s_%s_%s.C",Model.c_str(),channelv.c_str(),eff[iB]->GetName());
	c1->Print(name_);
	}
	
	cout<<"  "<<endl;
	
}


