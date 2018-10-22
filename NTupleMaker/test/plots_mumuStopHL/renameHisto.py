######!/usr/bin/env python
from ROOT import *
import ROOT
import re
import fnmatch
import array
import sys

file=TFile(sys.argv[1],"r")

fileout=TFile("temp.root","recreate")
file.cd()

h1=""

dirList = gDirectory.GetListOfKeys()
for k1 in dirList:

      h1 = k1.ReadObj()
      htest=h1.Clone()
      #if "p5" in h1.GetName() :
      newname=htest.GetName().replace("p5","")
      htest.SetName(newname)
      fileout.cd()
      htest.Write()





