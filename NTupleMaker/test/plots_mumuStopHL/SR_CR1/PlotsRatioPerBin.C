#include <iostream>
#include <vector>
//#include <map>
//#include "boost/lexical_cast.hpp"
//#include "boost/algorithm/string.hpp"
//#include "boost/format.hpp"
//#include "boost/program_options.hpp"
//#include "boost/range/algorithm.hpp"
//#include "boost/range/algorithm_ext.hpp"
#include "Plotting.h"
#include "Plotting_Style.h"
#include "HttStylesNew.cc"
#include "TPad.h"
#include "TROOT.h"
#include "TColor.h"
#include "TEfficiency.h"
#include "TMath.h"
////Templ_met_MTDil_17_100invfb_mt_StopC1Stau_SR_CR1.root
//WithoutNPV/
void PlotsRatioPerBin(TString directory = "",
	  TString suffix = "",
	  TString File = "Templ_met_MTDil4_9_3000invfb_mm_Stop_SR_CR1.root",
	  TString variable = "",
	  TString Suffix = "",
	  TString xtitle = "",
	  TString ytitle = "Events",
      bool logY = true,
 	    bool BlindData = false

          )


{
	  vector<TString> vars_;vars_.clear();
	  vars_.push_back("met_MTDil4_9");
  //ModTDRStyle();



int mycolor=TColor::GetColor("#ffcc66");
int mycolorvv=TColor::GetColor("#8646ba");
//int mycolorvv=TColor::GetColor("#FF6633");
int mycolorww=TColor::GetColor("#6F2D35");
int mycolorqcd=TColor::GetColor("#ffccff");
int mycolortt=TColor::GetColor("#de5a6a");
int mycolorst=TColor::GetColor("#b6d0ea");
//int mycolorttx=TColor::GetColor("#bbccdd");
int mycolorttx=TColor::GetColor("#33CCFF");
//int mycolorwjet=TColor::GetColor("#de5a6a");
int mycolorwjet=TColor::GetColor("#b6d0ea");
//int mycolorwjet=TColor::GetColor("#66CC66");
int mycolordyj=TColor::GetColor("#ffcc66");
int mycolorztt=TColor::GetColor("#58d885");

  bool plotLeg = true;
  int position = 2; // 0 - right, 1 - left, 2 - central
  int npos = 1;

  TH1::SetDefaultSumw2();
  TH2::SetDefaultSumw2();


  //  TString topweight("");



	directory="";
    TFile * filee ;//
    TH1D * fitHisto, *fitHisto2, *fitHistoPostH0, *fitHistoPostH1;
    int nB=1;

    TFile * file = new TFile(File,"read");
    
for (int svar=0;svar<vars_.size();++svar)
{


	TString Variable=vars_.at(svar);

    TH1D * TT = (TH1D*)file->Get("tt_"+Variable);
    TH1D * WJ = (TH1D*)file->Get("wj_"+Variable);
    TH1D * DY = (TH1D*)file->Get("dyj_"+Variable);
//    TH1D * ZTT = (TH1D*)file->Get("ztt_"+Variable);
    TH1D * ST = (TH1D*)file->Get("sT_"+Variable);
    TH1D * VV = (TH1D*)file->Get("dib_"+Variable);
    TH1D * WW = (TH1D*)file->Get("ww_"+Variable);
    TH1D * TTX = (TH1D*)file->Get("ttx_"+Variable);
 //   TH1D * QCD = (TH1D*)file->Get("fakes_"+Variable);
    TH1D * allbkg = (TH1D*)file->Get("allbkg_"+Variable);
    TH1D * histData = (TH1D*)file->Get("allbkg_"+Variable);
    TH1D * histSignal = (TH1D*)file->Get("single-stop14TeV_175_LSP1_B_"+Variable);
    TH1D * histSignal2 = (TH1D*)file->Get("single-stop14TeV_2X_175_LSP67_B_"+Variable);
    TH1D * histSignal3 = (TH1D*)file->Get("single-stop14TeV_200_LSP25_B_"+Variable);
    TH1D * histSignal4 = (TH1D*)file->Get("single-stop14TeV_2X_250_LSP105_B_"+Variable);




int nBins  =   histData->GetNbinsX();
if (BlindData) {for (int iB=1; iB<=nBins; ++iB) {histData->SetBinContent(iB,0);}}
//{for (int iB=1; iB<=nBins; ++iB) {TTcl->SetBinContent(iB,0);}}

  TH1D * TTcl = (TH1D*)TT->Clone("dummy");

cout<<" ok, read templates"<<endl;

  std::cout << "TT  : " << TT->GetSumOfWeights() << " : "  <<" GetNbinsX= " << TT->GetNbinsX()<< "  Purity  "<<TT->GetSumOfWeights()/allbkg->GetSumOfWeights()<< std::endl;
  std::cout << "TTcl  : " << TTcl->GetSumOfWeights() << " : "  <<" GetNbinsX= " << TTcl->GetNbinsX()<< "  Purity  "<<TTcl->GetSumOfWeights()/allbkg->GetSumOfWeights()<< std::endl;
  std::cout << "WJ   : " << WJ->GetSumOfWeights() << " : "  <<" GetNbinsX= " << WJ->GetNbinsX()<< "  Purity  "<<WJ->GetSumOfWeights()/allbkg->GetSumOfWeights()<< std::endl;
  std::cout << "DY : " << DY->GetSumOfWeights() << " : "  <<" GetNbinsX= " << DY->GetNbinsX()<< "  Purity  "<<DY->GetSumOfWeights()/allbkg->GetSumOfWeights()<< std::endl;
  std::cout << "ST   : " << ST->GetSumOfWeights() << " : "  <<" GetNbinsX= " << ST->GetNbinsX()<< "  Purity  "<<ST->GetSumOfWeights()/allbkg->GetSumOfWeights()<< std::endl;
  std::cout << "WW   : " << WW->GetSumOfWeights() << " : "  <<" GetNbinsX= " << WW->GetNbinsX() << "  Purity  "<<WW->GetSumOfWeights()/allbkg->GetSumOfWeights()<< std::endl;
  std::cout << "Dib   : " << VV->GetSumOfWeights() << " : "  <<" GetNbinsX= " << VV->GetNbinsX() << "  Purity  "<<VV->GetSumOfWeights()/allbkg->GetSumOfWeights()<< std::endl;
  std::cout << "TTX  : " << TTX->GetSumOfWeights() << " : "  <<" GetNbinsX= " << TTX->GetNbinsX()<< "  Purity  "<<TTX->GetSumOfWeights()/allbkg->GetSumOfWeights()<< std::endl;
  std::cout << "histData : " << histData->GetSumOfWeights() << " : "  <<" GetNbinsX= " << histData->GetNbinsX()<< endl;
  std::cout << "histSignal : " << histSignal2->GetSumOfWeights() << " : "  <<" GetNbinsX= " << histSignal2->GetNbinsX()<<endl;

  std::cout << "BKG : " << allbkg->GetSumOfWeights() << " : " << allbkg->GetSumOfWeights() << std::endl;
  std::cout << "DAT : " << histData->GetSumOfWeights() << " : " << histData->GetSumOfWeights() << std::endl;
  std::cout << "DAT/BKG = " << histData->GetSumOfWeights()/allbkg->GetSumOfWeights() << "+/-" 
	    << TMath::Sqrt(histData->GetSumOfWeights())/allbkg->GetSumOfWeights() << std::endl;
cout<<"==========="<<endl;
///////////////////////////////////////////////////////////////////////////////////////////////
    //ModTDRStyle();

    ModTDRStyle();

     char bN[20];
     int BTag=0;
    std::vector<TH1*> h = CreateAxisHists(2, histData, histData->GetXaxis()->GetXmin(), histData->GetXaxis()->GetXmax()-.01);
     for (int iB=1; iB<=nBins; ++iB) {
	     if (iB>10) BTag=1 ; 
             sprintf(bN,"%iB%i",iB,BTag);
	     histData->GetXaxis()->SetBinLabel(iB,bN);
	     h[0]->GetXaxis()->SetBinLabel(iB,bN);
	  //   TT->GetXaxis()->SetBinLabel(iB,bN);
	  //   TTcl->GetXaxis()->SetBinLabel(iB,bN);
     
     	}

    

//                   cout<<" nB  TT & WJets  & DYJets & ZTT & sT & QCD & WW  & Rest \\\\\\hline "<<endl;

cout<<" Relative  tt "<< TT->GetBinContent(nB)/allbkg->GetSumOfWeights()<<"  dyj  "<<DY->GetBinContent(nB)/allbkg->GetSumOfWeights()<<endl;


cout<<" & Composition (\\%)   & \\ttbar  & $\\PZ\\rightarrow \\ell \\ell   &  Rest & Sum   & S1 & S2 & S3 \\\\ \\hline"<<endl;
		   float allsum=0;
		   float sums[10]={0.};
  for (int nB=1;nB<TTcl->GetNbinsX()+1;++nB) {
	  
float tty  = TT->GetBinContent(nB)/allbkg->GetSumOfWeights();
//float ztty  = ZTT->GetBinContent(nB)/allbkg->GetSumOfWeights();
float dyjy  = DY->GetBinContent(nB)/allbkg->GetSumOfWeights();
float sTy  = ST->GetBinContent(nB)/allbkg->GetSumOfWeights();
float wwy  = WW->GetBinContent(nB)/allbkg->GetSumOfWeights();
float vvy  = VV->GetBinContent(nB)/allbkg->GetSumOfWeights();
float ttxy  = TTX->GetBinContent(nB)/allbkg->GetSumOfWeights();
//float qcdy  = QCD->GetBinContent(nB)/allbkg->GetSumOfWeights();
float wjy  = WJ->GetBinContent(nB)/allbkg->GetSumOfWeights();

float s1 = histSignal->GetBinContent(nB);
float s2 = histSignal2->GetBinContent(nB);
float s3 = histSignal3->GetBinContent(nB);
float s4 = histSignal4->GetBinContent(nB);

float es1, es2, es3, es4;

es1=histSignal->GetBinError(nB);
es2=histSignal2->GetBinError(nB);
es3=histSignal3->GetBinError(nB);
es4=histSignal4->GetBinError(nB);

tty  = TT->GetBinContent(nB);///allbkg->GetSumOfWeights();


dyjy  = DY->GetBinContent(nB);
sTy  = ST->GetBinContent(nB);///allbkg->GetSumOfWeights();
wwy  = WW->GetBinContent(nB);///allbkg->GetSumOfWeights();
vvy  = VV->GetBinContent(nB);///allbkg->GetSumOfWeights();
ttxy  = TTX->GetBinContent(nB);///allbkg->GetSumOfWeights();
//float qcdy  = QCD->GetBinContent(nB)/allbkg->GetSumOfWeights();
wjy  = WJ->GetBinContent(nB);;//allbkg->GetSumOfWeights();

wjy+=sTy+wwy+vvy+ttxy;

float etty = TT->GetBinError(nB);
float ewjy = sqrt(WJ->GetBinError(nB)*WJ->GetBinError(nB) + ST->GetBinError(nB)*ST->GetBinError(nB) + WW->GetBinError(nB)*WW->GetBinError(nB)+ VV->GetBinError(nB)*VV->GetBinError(nB) +TTX->GetBinError(nB)*TTX->GetBinError(nB));
float edyjy = DY->GetBinError(nB);
float etot = sqrt(etty*etty+ewjy*ewjy+edyjy*edyjy);


float sum = tty+wjy+dyjy+sTy+wwy+fabs(vvy) + fabs(ttxy);

	  //cout<<nB<<" & $ "<<TTcl->GetXaxis()->GetBinLabel(nB)<<" $ & "<<std::fixed<<std::setprecision(1)<<tty<<"  & "<<wjy<<" &  "<<dyjy<<" &  "<<sTy<<" &  "<<wwy<<" &  "<<fabs(vvy)+fabs(ttxy)<<" & "<<sum<<" \\\\\\hline"<<endl;
	  //cout<<" bin "<<nB<<" & "<<std::fixed<<std::setprecision(2)<<tty<<"   $\\pm$ "<<etty<<" & "<<dyjy<<" $\\pm$  "<<edyjy<<" &  "<<wjy<<" $\\pm$ "<<ewjy<<" & "<<sum<<" $\\pm $ " <<etot<<" & "<<s1<<" $\\pm$ "<<es1<<" & "<<s2<<" $\\pm$ "<<es2<<"  &  "<<s3<<" $\\pm$ "<<es3<<" &  "<<s4<<" $\\pm$ "<<es4 <<" \\\\\\hline"<<endl;
	  cout<<histData->GetXaxis()->GetBinLabel(nB)<<" & "<<std::fixed<<std::setprecision(2)<<tty<<"   $\\pm$ "<<etty<<" & "<<dyjy<<" $\\pm$  "<<edyjy<<" &  "<<wjy<<" $\\pm$ "<<ewjy<<" & "<<sum<<" $\\pm $ " <<etot<<" & "<<s1<<" $\\pm$ "<<es1<<" & "<<s2<<" $\\pm$ "<<es2<<"  &  "<<s3<<" $\\pm$ "<<es3<<" &  "<<s4<<" $\\pm$ "<<es4 <<" \\\\\\hline"<<endl;

	  /*
sums[0] +=tty;
sums[1] +=wjy;
sums[2] +=dyjy;
sums[3] +=sTy;
sums[4] +=wwy;
sums[5] +=vvy+ttxy;
allsum +=sum;
*/
}

	  //cout<<"  & Sum & "<<std::fixed<<std::setprecision(1)<<sums[0]<<"  & "<<sums[1]<<" & "<<sums[2]<<" & "<<sums[3]<<" &  "<<sums[4]<<" & "<<sums[5]<<"  & "<<allsum<<" \\\\\\hline  "<<endl;
	  //cout<<"  Sum Events & "<<std::fixed<<std::setprecision(1)<<sums[0]*allbkg->GetSumOfWeights()<<"  & "<<sums[1]*allbkg->GetSumOfWeights()<<" & "<<sums[2]*allbkg->GetSumOfWeights()<<" & "<<sums[3]*allbkg->GetSumOfWeights()<<" &  "<<sums[4]*allbkg->GetSumOfWeights()<<" & "<<sums[5]*allbkg->GetSumOfWeights()<<" & "<<allsum*allbkg->GetSumOfWeights()<<" \\\\\\hline  "<<endl;
//	  cout<<"  & Sum & "<<std::fixed<<std::setprecision(1)<<sums[0]<<"  & "<<sums[2]<<" & "<<sums[1]<<"  & "<<allsum<<" \\\\\\hline  "<<endl;
//	  cout<<"  Sum Events & "<<std::fixed<<std::setprecision(1)<<sums[0]*allbkg->GetSumOfWeights()<<"  & "<<sums[2]*allbkg->GetSumOfWeights()<<" & "<<sums[1]*allbkg->GetSumOfWeights()<<" \\\\\\hline  "<<endl;


    TCanvas* canv1 = new TCanvas("c1", "c1",1800,1200);
    canv1->cd();
    std::vector<TPad*> pads = TwoPadSplit(0.1, 0.00, 0.00);
    pads[0]->SetLogy(logY);
    histData->GetXaxis()->SetLabelSize(0.03);
    histData->GetXaxis()->SetTitle("bin");
    histData->GetXaxis()->SetTitleSize(0.03);
    histData->GetYaxis()->SetTitle("Events / bin");
    histData->GetYaxis()->SetNdivisions(512);
    histData->GetXaxis()->SetTimeFormat("#splitline{%s}{%s}");
    histData->GetXaxis()->SetLabelOffset(0.08);
    histData->GetXaxis()->SetLabelFont(42);
    histData->GetXaxis()->SetLabelSize(0.05);
     //for (int iB=1; iB<=nBins; ++iB) {histData->GetXaxis()->SetBinLabel(iB,BinLabels[iB-1]);}
     //
 //   std::vector<TH1*> h = CreateAxisHists(2, histData, histData->GetXaxis()->GetXmin(), histData->GetXaxis()->GetXmax());
    //histData->Reset();
    histData->Draw();
    h[0]->GetXaxis()->SetTitle("bin");
    h[0]->GetYaxis()->SetTitle("Events/ bin");
    h[0]->Draw();
    
    
    std::string units="";
    std::string xtitle_ = (std::string) xtitle;
    size_t pos = xtitle_.find("[");
    if(pos!=std::string::npos) {
        units = xtitle_.substr(pos+1, xtitle_.find("]") - pos -1 );
        xtitle_ = xtitle_.substr(0, pos);
    }
    

    pads[0]->cd();
    
    // Setup legend
    TLegend *legend = PositionedLegend(0.58, 0.25, 3, 0.03);
    legend->SetTextFont(42);
    legend->SetTextSize(0.0375);
    legend->SetNColumns(2);
    
    histData->SetMarkerColor(0);
    histData->SetLineColor(0);
    histData->SetFillColor(0);
    histData->SetFillStyle(0);
    histData->SetMarkerStyle(20);
    histData->SetMarkerSize(1);


    int color = CreateTransparentColor(13,0.);
    color=kBlue;
    histSignal->SetMarkerColor(kBlue);
    histSignal->SetLineColor(color);
    histSignal->SetFillColor(color);
    histSignal->SetFillStyle(0);
    //histSignal->SetLineWidth(2);
    histSignal->SetMarkerStyle(33);
    histSignal->SetMarkerSize(3);
    color=kRed;
    histSignal2->SetMarkerColor(color);
    histSignal2->SetLineColor(color);
    histSignal2->SetFillColor(color);
    histSignal2->SetFillStyle(0);
    histSignal2->SetMarkerStyle(33);
    histSignal2->SetMarkerSize(3);

    color=TColor::GetColor("#514626");
    histSignal3->SetMarkerColor(color);
    histSignal3->SetLineColor(color);
    histSignal3->SetFillColor(color);
    histSignal3->SetFillStyle(0);
    histSignal3->SetMarkerStyle(33);
    histSignal3->SetMarkerSize(3);
    color=TColor::GetColor("#4f7a3b");
    histSignal4->SetMarkerColor(color);
    histSignal4->SetLineColor(color);
    histSignal4->SetFillColor(color);
    histSignal4->SetFillStyle(0);
    histSignal4->SetMarkerStyle(33);
    histSignal4->SetMarkerSize(3);



    //InitHist(QCD,mycolorqcd);
    InitHist(DY,mycolordyj);
 //   InitHist(ZTT,mycolorztt);
    InitHist(TT,mycolortt);
    InitHist(TTcl,mycolortt);
    InitHist(ST,mycolorst);
    InitHist(TTX,mycolorttx);
    InitHist(WJ,mycolorwjet);
    InitHist(VV,mycolorvv);
    InitHist(WW,mycolorww);
    
    legend->AddEntry(histSignal,"#tilde{t}_{1}/#tilde{#chi}_{1}^{#pm}(175), #tilde{#chi}_{1}^{0}(1) (SA)","ple");
    legend->AddEntry(TT,"Top quark","f");
//    legend->AddEntry(ST,"singleTop","f");
//    legend->AddEntry(TTX,"TTX/TG","f");
     legend->AddEntry(histSignal2,"#tilde{t}_{1}(175)/#tilde{#chi}_{1}^{#pm}(87.5), #tilde{#chi}_{1}^{0}(67.5) (SB)","ple");
    legend->AddEntry(DY,"Z#rightarrow ll","f");
  //  legend->AddEntry(QCD,"QCD","f");
    legend->AddEntry(histSignal3,"#tilde{t}_{1}/#tilde{#chi}_{1}^{#pm}(200), #tilde{#chi}_{1}^{0}(25) (SC)","ple");
    legend->AddEntry(WJ,"Other SM","f");
 //   legend->AddEntry(ZTT,"Z#rightarrow#tau#tau","f");
//    legend->AddEntry(WW,"WW","f");
//    legend->AddEntry(VV,"VV(V)","f");
    legend->AddEntry(histSignal4,"#tilde{t}_{1}(250)/#tilde{#chi}_{1}^{#pm}(125), #tilde{#chi}_{1}^{0}(105) (SD)","ple");


//for (int iB=1; iB<=nBins; ++iB) {WJ->SetBinError(iB,0);TT->SetBinError(iB,0);TTcl->SetBinError(iB,0);DY->SetBinError(iB,0);VV->SetBinError(iB,0);WW->SetBinError(iB,0);TTX->SetBinError(iB,0);ST->SetBinError(iB,0);}
    WJ->SetMarkerStyle(0);
    TT->SetMarkerStyle(0);
    TTcl->SetMarkerStyle(0);
    DY->SetMarkerStyle(0);
    //ZTT->SetMarkerStyle(0);
    //QCD->SetMarkerStyle(0);
    VV->SetMarkerStyle(0);
    WW->SetMarkerStyle(0);
    TTX->SetMarkerStyle(0);
    ST->SetMarkerStyle(0);

    WJ->Add(WW);
    WJ->Add(VV);
    WJ->Add(TTX);
    WJ->Add(ST);

    THStack *hs = new THStack("","");
    hs->Add(WJ);
//    hs->Add(WW);
//    hs->Add(VV);
    hs->Add(DY);
    hs->Add(TT);
//    hs->Add(ST);
//    hs->Add(TTX);
    //hs->Add(ZTT);
    //hs->Add(QCD);

    


    TH1D *hsum = ((TH1D*)(hs->GetStack()->Last()));
 //   */
 
  hs->SetMinimum(1);
  hsum->SetMinimum(1);
  WJ->SetLineStyle(0);
  TT->SetLineStyle(0);
  TTX->SetLineStyle(0);
  VV->SetLineStyle(0);
  ST->SetLineStyle(0);
  WJ->SetLineColor(kBlack);



 histData->GetXaxis()->SetLabelSize(0.02);
 histData->GetXaxis()->SetTitleSize(0.03);
  
  //histData->Draw("hist");

  hsum->GetXaxis()->SetTitle(" bin ");
  hsum->Draw("same hist");
  hs->Draw("same hist");

    histSignal->Draw("same e1 hist");
    histSignal2->Draw("same e1 hist");
    histSignal3->Draw("same e1 hist");
    histSignal4->Draw("same e1 hist");

/*
   TLine *l1 = new TLine (2, 0,2, hsum->GetMaximum()*10);
   TLine *l2 = new TLine (7, 0,7, hsum->GetMaximum()*10);
   TLine *l3 = new TLine (14, 0,14, hsum->GetMaximum()*10);
   TLine *l4 = new TLine (19, 0,19, hsum->GetMaximum()*10);
   TLine *l5 = new TLine (24, 0,24, hsum->GetMaximum()*10);
   l1->SetLineWidth(2);
   l1->SetLineStyle(2);
   l1->SetLineColor(kBlue);
   l1->Draw("same");

   l2->SetLineWidth(2);
   l2->SetLineStyle(2);
   l2->SetLineColor(kBlue);
   l2->Draw("same");
   l3->SetLineWidth(2);
   l3->SetLineStyle(2);
   l3->SetLineColor(kBlue);
   l3->Draw("same");
   l4->SetLineWidth(2);
   l4->SetLineStyle(2);
   l4->SetLineColor(kBlue);
   l4->Draw("same text");
   l5->SetLineWidth(2);
   l5->SetLineStyle(2);
   l5->SetLineColor(kBlue);
   l5->Draw("same");

    TLatex *texta,*textb, *textc, *textd,*texte;
    texta = new TLatex(2.5,1e5,"prompt #tau");
    texta->SetTextSize(0.035);
    texta->Draw("same");
    textb = new TLatex(9.5,1e5,"quark#rightarrow#tau");
    textb->SetTextSize(0.035);
    textb->Draw("same");
    textc = new TLatex(15.5,1e5,"#mu#rightarrow#tau");
    textc->SetTextSize(0.035);
    textc->Draw("same");
    textd = new TLatex(20.5,1e5,"e#rightarrow#tau");
    textd->SetTextSize(0.035);
    textd->Draw("same");
    texte = new TLatex(25.5,1e5,"Gluon#rightarrow#tau");
    texte->SetTextSize(0.035);
    texte->Draw("same");

*/	
   


float sum=0;
//    for (int b=1;b<allbkg->GetNbinsX()+1;++b) cout<< "  b  "<<b<<" mc "<<allbkg->GetBinContent(b)<<" data  "<<histData->GetBinContent(b)<<"  "<<histData->GetBinContent(b)/allbkg->GetBinContent(b)<<" deviation "<<(histData->GetBinContent(b) - allbkg->GetBinContent(b))/sqrt(histData->GetBinContent(b))<<" DYJets "<<DY->GetBinContent(b)<<" TT "<<TTcl->GetBinContent(b)<<endl;

    cout<<" =============== SF study  ======================"<<endl;
    for (int b=1;b<allbkg->GetNbinsX()+1;++b) {
	    
 float SFw = 1; if (WJ->GetBinContent(b) > 0) SFw = (histData->GetBinContent(b) - (allbkg->GetBinContent(b)-WJ->GetBinContent(b))) / WJ->GetBinContent(b); 
 float SFdyj = 1; if (DY->GetBinContent(b)> 0) SFdyj = (histData->GetBinContent(b) - (allbkg->GetBinContent(b)-DY->GetBinContent(b))) / DY->GetBinContent(b); 
 float SFtt = 1; if (TTcl->GetBinContent(b)> 0)  SFtt = (histData->GetBinContent(b) - (allbkg->GetBinContent(b)-TTcl->GetBinContent(b))) / TTcl->GetBinContent(b); 

 float purW =  WJ->GetBinContent(b)/allbkg->GetBinContent(b);
 float purtt =  TTcl->GetBinContent(b)/allbkg->GetBinContent(b);
 float purdyj =  DY->GetBinContent(b)/allbkg->GetBinContent(b);
	    
sum +=allbkg->GetBinContent(b);

    
    }

    canv1->Update();

 


    pads[0]->cd();
   

    string v="Phase-2 Simulation";
    v="";

    //FixTopRange(pads[0], GetPadYMax(pads[0]), 0.5);
    //DrawCMSLogo(pads[0], "CMS", "", 11, 0.045, 0.035, 1.2);
//    DrawTitle(pads[0], "3 ab^{-1} (14 TeV)", 3);
  //  DrawTitle(pads[0], v, 1);

    FixTopRange(pads[0], GetPadYMax(pads[0]), 0.65);
    DrawCMSLogo(pads[0], "CMS", "Phase-2 Simulation", 11, 0.045, 0.035, 1.2);
    DrawTitle(pads[0], "3 ab^{-1} (14 TeV)", 3);
    DrawTitle(pads[0], v, 1);

    TLatex *tex,*texx,*texch, *texSR;
    tex = new TLatex(5,1e5,"0-btag");
    //tex->SetLineWidth(2);
    texx = new TLatex(15,1e5,"1-btag");
    texch = new TLatex(3,1e7,"#mu#mu");
    texch->SetTextFont(132);
    //texx->SetLineWidth(2);
//    tex->SetTextSize(0.02);
    tex->Draw();
    texx->Draw();
    texch->Draw();

    FixBoxPadding(pads[0], legend, 0.18);
    legend->Draw();
    TLine *l=new TLine(11,1,11,3e6);
    TArrow *lr=new TArrow(20,15e3,25,15e3,0.02,"|>");
    TArrow *ll=new TArrow(20,15e3,16,15e3,0.02,"|>");
    l->SetLineStyle(2);
    l->SetLineWidth(3);
    l->SetLineColor(kBlack);
    l->Draw();
//    l->Draw();
//    lr->Draw();
//    ll->Draw();
    FixOverlay();
    pads[1]->cd();
    texSR = new TLatex(0.05,0.05,"SR :");
   // texSR->Draw();

  //  FixBoxPadding(pads[0], legend, 0.05);
 //   legend->Draw();
//    FixOverlay();
    canv1->Update();
    pads[0]->GetFrame()->Draw();
    canv1->Print(Variable+Suffix+suffix+"_MuMu.pdf");
    canv1->Print(Variable+Suffix+suffix+"_MuMu.png");
}
}
