#ifndef ScaleFactor_h
#define ScaleFactor_h

#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include <map>
#include <cmath>
#include <string>




class ScaleFactor {

	private: 
	std::map<std::string, TGraphAsymmErrors *> eff_data;
	std::map<std::string, TGraphAsymmErrors *> eff_mc;

	TH1D * etaBinsH;

	void  SetAxisBins(TGraphAsymmErrors*);
	void  SetAxisBins(TH1D*);
	bool  check_SameBinning(TGraphAsymmErrors*, TGraphAsymmErrors*);

	public:
		ScaleFactor(){}; 
		void init_ScaleFactor(TString);
		void init_ScaleFactor(TString,std::string);
		void init_ScaleFactorb(TString,bool);
		~ ScaleFactor();
		double get_EfficiencyData(double, double); //pt, eta
		double get_EfficiencyMC(double, double);
		double get_ScaleFactor(double, double); 
	
};


#endif


