#!/bin/bash


cd /nfs/dust/cms/user/alkaloge/TauAnalysis/new/new/StauAnalysis/New8025/CMSSW_8_0_25/src/DesyTauAnalyses/NTupleMaker/test;eval `scramv1 runtime -sh` ;cmsenv;

export CVS_RSH=/usr/bin/ssh

dir="/nfs/dust/cms/user/alkaloge/TauAnalysis/new/new/StauAnalysis/New8025/CMSSW_8_0_25/src/DesyTauAnalyses/NTupleMaker/test"

channel=$2
channel2=$2
dirhere=$2
btag="0.8484"

whichcut=$4
plotsFile=""

systematics="$3"

if [[  $3 == "list" ||  $3 == "all" ]];then
systematics="Nominal TopPtUp TopPtDown ZPtUp ZPtDown JetEnUp JetEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown genMET ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown METRecoilUp METRecoilDown"
systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown METRecoilUp METRecoilDown TFRJetEnUp TFRJetEnDown TFRMuEnUp TFRMuEnDown TFRTauEnUp TFRTauEnDown"
systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown METRecoilUp METRecoilDown"
#systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown genMET ScalesDown ScalesUp PDFUp PDFDown"
#systematics="JetEnUp JetEnDown UnclEnUp UnclEnDown"
fi

if [[  $3 == "listme" ]];then
systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown METRecoilUp METRecoilDown"
fi

if [[  $3 == "listSignal" ]];then
systematics="Nominal JetEnUp JetEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown genMET ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown EWKUp EWKDown"
#systematics="ScalesDown ScalesUp PDFUp PDFDown"
systematics="Nominal genMET"
fi

if [[  $3 == "New" ]];then
systematics="genMET ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown METRecoilUp METRecoilDown"
#systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown genMET ScalesDown ScalesUp PDFUp PDFDown"
fi


if [[  $3 == "listTT" ]];then
systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown METRecoilUp METRecoilDown"
#systematics="JetEnUp JetEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown BTagUp BTagDown"
#systematics="Nominal  TopPtUp TopPtDown ZPtUp ZPtDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown METRecoilUp METRecoilDown"
fi

if [[  $3 == "listDY" ]];then
systematics="Nominal JetEnUp JetEnDown ZPtUp ZPtDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown METRecoilUp METRecoilDown"

fi

if [[  $3 == "listWJ" ]];then
systematics="Nominal ZpTUp ZPtDown TopPtUp TopPtDown JetEnUp JetEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown METRecoilUp METRecoilDown  BTagUp BTagDown"
#systematics="JetEnUp JetEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown METRecoilUp METRecoilDown  BTagUp BTagDown"

fi

if [[ -z $3 ]];then
systematics="Nominal"
echo You will run with nominal systematics
fi

if [[ $2 == "Ttemplate" ]] 
then
	channel2="muel"
fi

if [[ $2 == "Wtemplate"   ||   $2 == *"fakesmu"*  || $2 == "Wtemplate2" || $2 == "mutauInvertedTauIso"  || $2 = "WJetsCRMuTau"  || $2 = "mutauByBin" || $2 = "WJetsCRMuTauVLoose" || $2 == "mutauQCD"  ]]
then
	channel2="mutau"
fi

if [[ $2 == "WJetsmu" ]]
then
	channel2="mutau"
fi

if [[ $2 == *"mutauStop"*  || $2 == "fakesmuStop" ]]
then
	channel2="mutauStop"
	dirhere="mutau"
	plotsFile="Stop"
fi

if [[ $2 == *"mutauVStop"*  || $2 == "fakesmuStop" ]]
then
	channel2="mutauVStop"
	dirhere="mutau"
	plotsFile="Stop"
fi





if [[ $2 == *"eltauStop"*  || $2 == "fakeselStop" ]]
then
	channel2="eltauStop"
	dirhere="eltau"
	plotsFile="Stop"
fi

if [[ $2 == *"muelStop"*   ]]
then
	channel2="muelStop"
	dirhere="muel"
	plotsFile="Stop"
fi

if [[ $2 == *"mumuStop"*   ]]
then
	channel2="mumuStop"
	dirhere="mumu"
	plotsFile="Stop"
fi

if [[ $2 == *"mumuCR"*   ]]
then
	channel2="mumuStop"
	dirhere="mumu"
	plotsFile="Stop"
fi




if [[ $2 == *"elelStop"*   ]]
then
	channel2="elelStop"
	dirhere="elel"
	plotsFile="Stop"
fi

if [[ $2 == *"tautauStop"*   ]]
then
	channel2="tautauStop"
	dirhere="tautau"
	plotsFile="Stop"
fi

if [[ $2 == "WJetsCRElTau" || $2 == "eltauQCD" ]]
then
	channel2="eltau"
fi


###########start looking 
while read line
do

#unset isDataSyst
isDataSyst=0

unset isSystTopZpt
export isSystTopZPt=0


for syst in $systematics
do

unset file
file=`echo $line | cut -d '/' -f2`
unset fileB
fileB=`echo $file | awk -F "_B_OS" '{print $1}'`
	
mkdir dir_${file}_${channel}_$syst
cd dir_${file}_${channel}_$syst
#echo ==============================================


if [[ $file == *"Single"* || $file == *"MuonEG"* ]] && [[ $syst != "Nominal" ]]; then

	echo For data we dont run systematics....
isDataSyst=1
fi

if  [[ $syst == "genMET" ]]; then

#if [[ $file == *"stau"* || $file == *"Chi"* || $file == *"C1"* ]] ; then
#if [[  $file == *"Chi"*  ]] ; then

isDataSyst=0
	echo we will run genMET syst only for signal ....$file , isData $isDataSyst
#fi

fi

#######Do something is systematic is the TopPt or ZPt Up/Down

#if [[  $syst -eq "TopPtUp" || $syst -eq "TopPtDown" || $syst -eq "ZPtUp" || $syst -eq "ZPtDown" ]]; then

#isSystTopZPt=1

#fi


if [[ $isDataSyst == 0 ]] ; then

if [[ $line == *"stau"* || $line == *"C1"* || $line == *"Chi"* ]] ; then
lsp=`echo $line | awk -F "_LSP" '{print $2}' | cut -d '_' -f1`
else
lsp=0

fi




export prefx=""
export fileB=${fileB}_${pref}${syst}
#fi


######### B region non inverted OS
echo $line , $file, $fileB, $channel, $channel2

######### signal

if [[ $whichcut -gt 12 ]] ; then
	fileB=${fileB}_NoCut_${whichcut};
fi

#if [[ $file == *"B_OS"*  ]] && [[ $file == *"stau"*  || $file == *"C1"*  || $file == *"Chi"* ]];then
if [[ $file == *"B_OS"*  ]]  &&  [[ ! -f $dir/plots_$channel/${fileB}_B.root ]] ; then
	#&& [[ $file == *"stau"*  || $file == *"C1"*  || $file == *"Chi"* ]];then


#echo Signal file here .....

if [[ $file == *"DYY"*  && $2 == *"mumuStop"* ]] ; then

bOOls="true false" 

fileC=$fileB

for flag_ in $bOOls

do


	echo will work now for $flag_ and $fileB


cp $dir/analyzer_h analyzer.h
cp $dir/analyzer${channel}_C analyzer.C


sed -i 's/CHIMASSS/'$lsp'/g' analyzer*C
sed -i 's/CHANNELHERE/'$channel2'/g' analyzer*
sed -i 's/DIRHERE/'$dirhere'/g' analyzer*

sed -i 's/SYSTEMATICHERE/'$syst'/g' analyzer*

cp $dir/runme.C .
cp $dir/plots${plotsFile}.h plots.h

sed -i 's/FILEIN/'$file'/g' analyzer*
sed -i 's/LEPTONHERE/false/g' analyzer.C
sed -i 's/SIGNHERE/OS/g' analyzer.C
sed -i 's/CHANNELHERE/'$channel2'/g' analyzer*
sed -i 's/DIRHERE/'$dirhere'/g' analyzer*
sed -i 's/BTAGCUT/0.8484/g' analyzer*
sed -i 's/ISZTTHERE/'${flag_}'/g' analyzer.C
sed -i 's/WHICHCUT/'$whichcut'/g' analyzer*


sed -i 's/SYSTEMATICHERE/'$syst'/g' analyzer*

rm plots.root
root -l -q -b runme.C 
# g++ `$ROOTSYS/bin/root-config --cflags --glibs` analyzer.C -o a;./a
if [[ $flag_ == *"true"* ]] ;then

	prefx="isZTT_"

	systt=`echo $fileB | rev | cut -d'_' -f 1 | rev`
	fileC=`echo $fileB | rev | cut -d'_' -f 2-10 | rev` 
mv plots.root $dir/plots_$channel/${fileC}_${prefx}${systt}_B.root
else
	mv plots.root $dir/plots_$channel/${fileB}_B.root
fi

#else
#mv plots.root $dir/plots_$channel/${fileB}_B.root



done

fi


if [[ $file != *"dY"*  ]] ; then
echo the signal filein : $file , the fileout : ${fileB}_B.root

cp $dir/analyzer_h analyzer.h
cp $dir/analyzer${channel}_C analyzer.C

#cp $dir/analyzer_InvMET_C .

sed -i 's/CHIMASSS/'$lsp'/g' analyzer*C
sed -i 's/CHANNELHERE/'$channel2'/g' analyzer*
sed -i 's/DIRHERE/'$dirhere'/g' analyzer*

sed -i 's/SYSTEMATICHERE/'$syst'/g' analyzer*

cp $dir/runme.C .
cp $dir/plots${plotsFile}.h plots.h

#cp analyzer_h analyzer.h
#cp analyzer${channel}_C analyzer.C

sed -i 's/FILEIN/'$file'/g' analyzer*
sed -i 's/LEPTONHERE/false/g' analyzer.C
sed -i 's/SIGNHERE/OS/g' analyzer.C
#sed -i 's/ISZTTHERE/false/g' analyzer.C
sed -i 's/CHANNELHERE/'$channel2'/g' analyzer*
sed -i 's/DIRHERE/'$dirhere'/g' analyzer*
sed -i 's/BTAGCUT/0.8484/g' analyzer*
sed -i 's/WHICHCUT/'$whichcut'/g' analyzer*


sed -i 's/SYSTEMATICHERE/'$syst'/g' analyzer*

rm plots.root
root -l -q -b runme.C 
# g++ `$ROOTSYS/bin/root-config --cflags --glibs` analyzer.C -o a;./a
mv plots.root $dir/plots_$channel/${fileB}_B.root
fi


fi



######### A region non inverted SS

if [[ ! -f $dir/plots_$channel/${fileB}_A.root ]] && [[ $file != *"stau"* && $file != *"C1"*  &&  $file != *"Chi"* && $2 != "Ttemplate" && $2 != "mumu" && $2 != "WJETSMU"    &&  $2 != *"fakesmu"*  &&  $2 != *"WJetsCR"*  &&  $2 != *"mutau"*   &&  $2 != *"eltau"*  && $2 != *"Stop"*   &&  $2 != *"tautau"* ]] ;then
#if [[ ! -f $dir/plots_$channel/${fileB}_A.root ]] ; then
#if [[ ! -f $dir/plots_$channel/${fileB}_A.root ]]  &&  [[ $2 != "Ttemplate" ]] && [[ $2 != "mumu" ]]  && [[ $file == *"stau"*  || $file == *"C1"* ]]; then
cp $dir/analyzer_h analyzer.h
cp $dir/analyzer${channel}_C analyzer.C

echo the filein : $file , the fileout : ${fileB}_A.root , NonInvertedLepton SS
sed -i 's/FILEIN/'$file'/g' analyzer*
sed -i 's/LEPTONHERE/false/g' analyzer.C
sed -i 's/SIGNHERE/SS/g' analyzer.C
sed -i 's/CHANNELHERE/'$channel2'/g' analyzer*
sed -i 's/DIRHERE/'$dirhere'/g' analyzer*
sed -i 's/BTAGCUT/'$btag'/g' analyzer*


sed -i 's/SYSTEMATICHERE/'$syst'/g' analyzer*
#if [[ $channel == "muel" ]] ; then

#sed -i '217 a            bqcd=true;' analyzer.C
#fi

rm plots.root
root -l -q -b runme.C 
mv plots.root $dir/plots_$channel/${fileB}_A.root

fi




######## D region
if [[ ! -f $dir/plots_$channel/${fileB}_D.root ]] && [[ $file != *"stau"* && $file != *"C1"*  &&  $file != *"Chi"* && $2 != "Ttemplate" && $2 != "mumu" && $2 != "WJETSMU"    &&  $2 != *"fakesmu"*  &&  $2 != *"WJetsCR"*  &&  $2 != *"mutau"*   &&  $2 != *"eltau"*  && $2 != *"Stop"*  &&  $2 != *"tautau"* ]] ;then
cp $dir/analyzer${channel}_C analyzer.C
cp $dir/analyzer_h analyzer.h


echo the filein : $file , the fileout : ${fileB}_D.root InvertedLepton SS

sed -i 's/FILEIN/'$file'/g' analyzer*
sed -i 's/LEPTONHERE/true/g' analyzer.C
sed -i 's/SIGNHERE/SS/g' analyzer.C
sed -i 's/CHANNELHERE/'$channel2'/g' analyzer*
sed -i 's/DIRHERE/'$dirhere'/g' analyzer*
sed -i 's/BTAGCUT/'$btag'/g' analyzer*


sed -i 's/SYSTEMATICHERE/'$syst'/g' analyzer*
rm plots.root
root -l -q -b runme.C 
mv plots.root $dir/plots_$channel/${fileB}_D.root

fi


####### C region
if [[ ! -f $dir/plots_$channel/${fileB}_C.root ]] && [[ $file != *"stau"* && $file != *"C1"*  &&  $file != *"Chi"* && $2 != "Ttemplate" && $2 != "mumu" && $2 != "WJETSMU"    &&  $2 != *"fakesmu"*  &&  $2 != *"WJetsCR"*  &&  $2 != *"mutau"*   &&  $2 != *"eltau"*  && $2 != *"Stop"*  &&  $2 != *"tautau"* ]] ;then
cp $dir/analyzer${channel}_C analyzer.C
cp $dir/analyzer_h analyzer.h



echo the filein : $file , the fileout : ${fileB}_C.root  InvertedLepton OS
sed -i 's/FILEIN/'$file'/g' analyzer*
sed -i 's/LEPTONHERE/true/g' analyzer.C
sed -i 's/SIGNHERE/OS/g' analyzer.C
sed -i 's/CHANNELHERE/'$channel2'/g' analyzer*
sed -i 's/DIRHERE/'$dirhere'/g' analyzer*
sed -i 's/BTAGCUT/'$btag'/g' analyzer*


sed -i 's/SYSTEMATICHERE/'$syst'/g' analyzer*

rm plots.root
root -l -q -b runme.C 

mv plots.root $dir/plots_$channel/${fileB}_C.root


fi

fi

cd ${dir}

rm -fr dir_${file}_${channel}_$syst

done
done<$1
