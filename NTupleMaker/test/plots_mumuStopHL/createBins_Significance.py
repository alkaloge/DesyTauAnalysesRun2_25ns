#!/usr/bin/env python
from ROOT import *
import ROOT
import re
import array
import os
import sys
import fnmatch
import math


#Templ_met_MTDil_10_3000invfb_mm_Stop_SR_CR1.root



vars=["met_MTDil_","met_MTDil2","met_MTDil3","met_MTDil4","met_MTDil5","met_MTDil6","met_MTDil7","met_MTDil8"]



cutss=['9', '10', '11', '12', '13', '14']
#cutss=['10']


for var in range(len(vars)):
    
    for cut in range(len(cutss)):
		
	if int(var) == 0 : vars[var]="met_MTDil"
	name="Templ_"+str(vars[var])+"_"+str(cutss[cut])+"_3000invfb_mm_Stop_SR_CR1.root"
        file1=ROOT.TFile(name,"read")

        file1.cd()
	#file1.ls()
	hsign = file1.Get("single-stop14TeV_175_LSP1_B_"+str(vars[var])+"_"+str(cutss[cut]))
	hbkg = file1.Get("allbkg_"+str(vars[var])+"_"+str(cutss[cut]))



        print "================================",  hbkg.GetName(), hsign.GetName(), str(vars[var])+"_"+str(cutss[cut])
	filename="bins_%s"
	text_file = open("bins_2_%s_%s" %(str(vars[var]), str(cutss[cut])), "w")
	for ibin in range(1,int(hsign.GetNbinsX()+1)) :
	    S=hsign.GetBinContent(ibin)
	    B=hbkg.GetBinContent(ibin)
	    sB=math.sqrt(float(B))
	    if float(B) > 0 and float(S/sB) > 2 : 
	        print "for ",ibin, float(S/sB)
	        text_file.write("%s\n" %ibin )
	text_file.close()



