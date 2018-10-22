

systematics="JetEnUp JetEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown"

systematics="Nominal"

unset systematics

systematics="$3"

if [[ $3 == "syst" ]] ; then

#systematics="UnclEnUp UnclEnDown"
systematics="Nominal JetEnUp JetEnDown UnclEnUp UnclEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown"
systematics="JetEnUp JetEnDown UnclEnUp UnclEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown BTagUp BTagDown"
fi

if [[ $3 == "list" ]] ; then

#systematics="UnclEnUp UnclEnDown"
systematics="Nominal JetEnUp JetEnDown UnclEnUp UnclEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown BTagUp BTagDown"
#systematics="JetEnUp JetEnDown UnclEnUp UnclEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown BTagUp BTagDown"
#systematics="Nominal JetEnUp JetEnDown UnclEnUp UnclEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown"
#systematics="TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown BTagUp BTagDown"
fi

if [[ $3 == "listDY" ]] ; then

#systematics="UnclEnUp UnclEnDown"
systematics="JetEnUp JetEnDown UnclEnUp UnclEnDown MuEnUp MuEnDown"
fi

if [[ $3 == "listTT" ]] ; then

#systematics="UnclEnUp UnclEnDown"
systematics="JetEnUp JetEnDown UnclEnUp UnclEnDown ElEnUp ElEnDown MuEnUp MuEnDown BTagUp BTagDown"
fi

if [[ $3 == "Jes" ]] ; then

#systematics="UnclEnUp UnclEnDown"
systematics="JetEnUp JetEnDown"
fi

if [[ $3 == "Uncl" ]] ; then

#systematics="UnclEnUp UnclEnDown"
systematics="UnclEnUp UnclEnDown"
fi

if [[ $3 == "lept" ]] ; then

#systematics="UnclEnUp UnclEnDown"
systematics="TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown"
fi

if [[ $3 == "el" ]] ; then

#systematics="UnclEnUp UnclEnDown"
systematics="ElEnUp ElEnDown"
fi


if [[ $3 == "mu" ]] ; then

#systematics="UnclEnUp UnclEnDown"
systematics="MuEnUp MuEnDown"
fi



if [[ $3 == "tau" ]] ; then

#systematics="UnclEnUp UnclEnDown"
systematics="TauEnUp TauEnDown"
fi


if [[ $3 == "BTag" ]] ; then

systematics="BTagUp BTagDown"
fi

cd /afs/cern.ch/user/a/alkaloge/work/HLLHC/CMSSW_8_0_29/src/DesyTauAnalyses/NTupleMaker/test
wdir=/afs/cern.ch/user/a/alkaloge/work/HLLHC/CMSSW_8_0_29/src/DesyTauAnalyses/NTupleMaker/test
while read line
do

lt=`echo ${line}`
echo ${line} > $lt

for syst in $systematics
do
	



	#echo ${line} > dt
	
	echo submitting  run_mc.sh ${line} for $2 channel and systematic = $syst
	chmod 777 run_mc2_HL.sh
	#chmod 777 run_mc2_HL_condor.sh
	
	#cp submit_template.submit subm_${line}.submit
	#sed -i 's/EXECHERE/run_mc2.sh/g' subm_${line}.submit
	#sed -i 's@arguments@arguments = '${line}' '$2' '${syst}'@' subm_${line}.submit
	#condor_submit subm_${line}.submit

	#bsub -R "rusage[mem=2000:pool=1000]"  -q 1nh -J subm${line}_$syst -i /dev/null -o logs/subm_${line}_${2}_$syst.log -e /dev/null  $wdir/run_mc2_HL_condor.sh ${line} $2 $syst  
	bsub -R "rusage[mem=2000:pool=1000]"  -q 1nh -J subm${line}_$syst -i /dev/null -o logs/subm_${line}_${2}_$syst.log -e /dev/null  $wdir/run_mc2_HL.sh ${line} $2 $syst  

done
done<$1
