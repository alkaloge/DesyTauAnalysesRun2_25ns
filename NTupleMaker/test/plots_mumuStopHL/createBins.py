#!/usr/bin/env python
from ROOT import *
import ROOT
import re
import array
import os
import sys
import fnmatch


vars=["met_MTDil_","met_MTDil2","met_MTDil3","met_MTDil4","met_MTDil5","met_MTDil6","met_MTDil7","met_MTDil8"]
#vars=["DZetaRFB", "met_MTtot"]

file1=ROOT.TFile("single-stop14TeV_175_LSP1_B.root","read")


file1.cd("mumu")
#file1.ls()
dirListt = gDirectory.GetListOfKeys()
for k1 in dirListt:
    h1 = k1.ReadObj()
    #file1.cd(h1.GetName())
    #dirList2 = gDirectory.GetListOfKeys()
    #for k2 in dirListt:
    h2 = k1.ReadObj()
    if any (x in h2.GetName() for x in vars) and ( "_8" in h2.GetName() or "_9" in h2.GetName() or "_10" in h2.GetName() or "_11" in h2.GetName() or "_12" in h2.GetName() or "_13" in h2.GetName() or "_14" in h2.GetName() or  "_15" in h2.GetName()) and "TauDecayModeAll2" not in h2.GetName() and "Dil2D" not in h2.GetName():
            #print h1.GetName(),h2.GetName()

        print h2.GetName(), h2.GetSumOfWeights(), h1.GetName()
	filename="bins_%s"
	text_file = open("bins_%s" %h1.GetName(), "w")
    	
	for i in range(1,h2.GetNbinsX()+1) :  
	    
	     text_file.write("%s\n" %i )
	text_file.close()

