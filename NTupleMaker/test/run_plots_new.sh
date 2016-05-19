#!/bin/sh
#
#(make sure the right shell will be used)
#$ -S /bin/sh
#
#(the cpu time for this job)
#$ -l h_cpu=1:29:00
#
#(the maximum memory usage of this job)
#$ -l h_vmem=5000M
#
#(use hh site)
#$ -l site=hh
#(stderr and stdout are merged together to stdout)
#$ -j y
#
# use SL5
#$ -l os=sld6
#
# use current dir and current environment
#$ -cwd
#$ -V
#



cd /nfs/dust/cms/user/alkaloge/TauAnalysis/new/new/CMSSW_7_6_3_patch2/src/DesyTauAnalyses/NTupleMaker/test;eval `scramv1 runtime -sh` ;


dir="/nfs/dust/cms/user/alkaloge/TauAnalysis/new/new/CMSSW_7_6_3_patch2/src/DesyTauAnalyses/NTupleMaker/test"

channel=$2
btag="0.800"

while read line
do

unset file
file=`echo $line | cut -d '/' -f2`
	
mkdir dir_$file
cd dir_$file
echo ==============================================
pwd
echo ==============================================

if [[ $line == *"stau"* || $line == *"C1"* ]] ; then
lsp=`echo $line | awk -F "_LSP" '{print $2}' | cut -d '_' -f1`
else
lsp=0

fi


cp $dir/analyzer_h .
cp $dir/analyzer${channel}_C .


#cp $dir/analyzer_InvMET_C .

sed -i 's/CHIMASSS/'$lsp'/g' analyzer*C
sed -i 's/CHANNELHERE/'$channel'/g' analyzer*


cp $dir/runme.C .
cp $dir/plots.h .


unset fileB
fileB=`echo $file | awk -F "_B_OS" '{print $1}'`


echo $line , $fileB

######### signal

if [[ $file == *"B_OS"*  ]] && [[ $file == *"stau"*  || $file == *"C1"* ]];then

cp analyzer_h analyzer.h
cp analyzer${channel}_C analyzer.C

echo Signal file here .....
ls


if [[ ! -f $dir/plots_$channel/${fileB}_B.root ]] ; then
echo the signal filein : $file , the fileout : ${fileB}_B.root

sed -i 's/FILEIN/'$file'/g' analyzer*
sed -i 's/LEPTONHERE/false/g' analyzer.C
sed -i 's/SIGNHERE/OS/g' analyzer.C
sed -i 's/CHANNELHERE/'$channel'/g' analyzer*
sed -i 's/BTAGCUT/0.89/g' analyzer*



rm plots.root
root -l -q -b runme.C 
# g++ `$ROOTSYS/bin/root-config --cflags --glibs` analyzer.C -o a;./a
mv plots.root $dir/plots_$channel/${fileB}_B.root
fi

fi



if [[ $file == *"B_OS"* ]];then

cp analyzer_h analyzer.h


######### B region non inverted SS

if [[ ! -f $dir/plots_$channel/${fileB}_B.root  ]] &&  [[ $file != *"stau"* && $file != *"C1"* ]]; then
cp analyzer_h analyzer.h
cp analyzer${channel}_C analyzer.C

echo the filein : $file , the fileout : ${fileB}_B.root NonInvertedLepton OS
sed -i 's/FILEIN/'$file'/g' analyzer*
sed -i 's/LEPTONHERE/false/g' analyzer.C
sed -i 's/SIGNHERE/OS/g' analyzer.C
sed -i 's/CHANNELHERE/'$channel'/g' analyzer*
sed -i 's/BTAGCUT/'$btag'/g' analyzer*

rm plots.root
root -l -q -b runme.C 
mv plots.root $dir/plots_$channel/${fileB}_B.root

fi


######### A region non inverted SS

if [[ ! -f $dir/plots_$channel/${fileB}_A.root ]]  && [[ $file != *"stau"* && $file != *"C1"*  ]]; then
cp analyzer_h analyzer.h
cp analyzer${channel}_C analyzer.C

echo the filein : $file , the fileout : ${fileB}_A.root , NonInvertedLepton SS
sed -i 's/FILEIN/'$file'/g' analyzer*
sed -i 's/LEPTONHERE/false/g' analyzer.C
sed -i 's/SIGNHERE/SS/g' analyzer.C
sed -i 's/CHANNELHERE/'$channel'/g' analyzer*
sed -i 's/BTAGCUT/'$btag'/g' analyzer*

rm plots.root
root -l -q -b runme.C 
mv plots.root $dir/plots_$channel/${fileB}_A.root

fi




######## D region
if [[ ! -f $dir/plots_$channel/${fileB}_D.root  ]] &&  [[ $file != *"stau"*  && $file != *"C1"* ]]; then
cp analyzer${channel}_C analyzer.C
cp analyzer_h analyzer.h


echo the filein : $file , the fileout : ${fileB}_D.root InvertedLepton SS

sed -i 's/FILEIN/'$file'/g' analyzer*
sed -i 's/LEPTONHERE/true/g' analyzer.C
sed -i 's/SIGNHERE/SS/g' analyzer.C
sed -i 's/CHANNELHERE/'$channel'/g' analyzer*
sed -i 's/BTAGCUT/'$btag'/g' analyzer*

rm plots.root
root -l -q -b runme.C 
mv plots.root $dir/plots_$channel/${fileB}_D.root


fi





####### C region
if [[ ! -f $dir/plots_$channel/${fileB}_C.root  ]] &&  [[ $file != *"stau"* && $file != *"C1"*  ]]; then
cp analyzer${channel}_C analyzer.C
cp analyzer_h analyzer.h



echo the filein : $file , the fileout : ${fileB}_C.root  InvertedLepton OS
sed -i 's/FILEIN/'$file'/g' analyzer*
sed -i 's/LEPTONHERE/true/g' analyzer.C
sed -i 's/SIGNHERE/OS/g' analyzer.C
sed -i 's/CHANNELHERE/'$channel'/g' analyzer*
sed -i 's/BTAGCUT/'$btag'/g' analyzer*

rm plots.root
root -l -q -b runme.C 

mv plots.root $dir/plots_$channel/${fileB}_C.root


fi

fi

cd ${dir}

rm -fr dir_$line
done<$1
