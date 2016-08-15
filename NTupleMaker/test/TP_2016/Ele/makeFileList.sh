#!/bin/bash
#$1 = full sample name 

cd /nfs/dust/cms/group/higgs-kit/80x_v3/
ls $PWD/$1/*.root > /nfs/dust/cms/user/bottav/CMSSW_8_0_12/src/DesyTauAnalyses/NTupleMaker/test/TP_2016/Ele/$1
cd -

