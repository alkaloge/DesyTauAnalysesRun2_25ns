#!/bin/sh
#


################3 CHANGE THIS TO YOUR WORKING DIR
wdir="/afs/cern.ch/work/a/alkaloge/HLLHC/CMSSW_8_0_29/src/DesyTauAnalyses/NTupleMaker/test/"

cd $wdir/;eval `scramv1 runtime -sh` ;


channel=$2 

##type MC or Data
type=MC


mkdir Jobs
systematics="$3"

if [[ $3 == "all" || $3 == "All"  || $3 == "list" ]];then
#systematics="Nominal JetEnUp JetEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown"
systematics="Nominal JetEnUp JetEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown BTagUp BTagDown"
#systematics="JetEnUp JetEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown BTagUp BTagDown"
#systematics="JetEnUp JetEnDown UnclEnUp UnclEnDown"

fi

if [[ -z $3  ]];then
systematics="Nominal"
syst="1"
fi

cp *.conf Jobs/.

for syst in $systematics
do


export dir=${2}_${syst}


if [[ $syst == "Nominal" ]] || [[ -z $3  ]];then
export	dir=${channel}
fi


while read line
do

f=`echo $line | awk -F "_200PU" '{print $1}'`


ct=`ls ${dir}/${line}*.root | wc -l`

echo ======= $f $ct


ctt=`cat ${dir}/${line} | wc -l`


echo There are  $ct out of $ctt for $line in ${dir} dir for systematic $syst

if [[ $ct -ge $ctt ]] ;then
	continue;
fi

#unset xsec
xsec=1
unset f
while read f
	do

#echo $f
unset bas
bas=`basename $f | awk -F ".root" '{print $1}'`

if [ ! -f ${dir}/${bas}.root ] 
then

if [[ ! -f ${dir}/$bas ]] ; then
echo $f > ${dir}/$bas
fi

#	echo " "$bas $xsec >> xsecs


if [ -f Jobs/j${bas}_${dir}_${syst}.sh ] ; then
rm Jobs/j${bas}_${dir}_${syst}.sh
fi





if [ ! -f ${dir}/${bas}_B_OS.root ] ;then

cat bss > Jobs/j${bas}_${dir}_${syst}.sh
echo $bas $xsec ${dir}

	#echo file should be ${bas}_B_OS.root

	echo SUSY$channel analysisMacroSUSY_MC_B_HL.conf ${bas} ${channel} 1 $syst>> Jobs/j${bas}_${dir}_${syst}.sh
	chmod 777 Jobs/j${bas}_${dir}_${syst}.sh
 	bsub -R "rusage[mem=2048:pool=2000]"  -q 1nh -J ${channel}_${bas}_$syst -i /dev/null -o logs/job${channel}_${bas}_${dir}_B${syst}.log -e /dev/null $wdir/Jobs/j${bas}_${dir}_${syst}.sh
	#. Jobs/j${bas}_${dir}_${syst}.sh
fi


fi

done<${dir}/${line}
done<$1
done
