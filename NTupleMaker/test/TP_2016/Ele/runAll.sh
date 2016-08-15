#!/bin/zsh

MACRO=TagAndProbe2016_ee
CONFIG=TagAndProbe_e

#./qsub_seq.sh $MACRO $CONFIG.conf SingleElectron__Run2016B-PromptReco-v2
#./qsub_seq.sh $MACRO $CONFIG.conf SingleElectron__Run2016C-PromptReco-v2
#./qsub_seq.sh $MACRO $CONFIG.conf SingleElectron__Run2016D-PromptReco-v2

CONFIG=TagAndProbe_e_DY
./qsub_seq.sh $MACRO $CONFIG.conf DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8

