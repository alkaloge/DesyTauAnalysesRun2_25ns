#!/bin/sh
#

#systematics="Nominal JetEnUp JetEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown"
#systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown genMET ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown METRecoilUp METRecoilDown TFRJetEnUp TFRJetEnDown TFRMuEnUp TFRMuEnDown TFRTauEnUp TFRTauEnDown"
systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown genMET ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown METRecoilUp METRecoilDown"

#systematics="JetEnUp JetEnDown UnclEnUp UnclEnDown ZPtUp ZPtDown"

cd /afs/cern.ch/user/a/alkaloge/work/HLLHC/CMSSW_8_0_29/src/DesyTauAnalyses/NTupleMaker/test; eval `scramv1 runtime -sh` ;

rm jobss

channel=$2

	if [[  -z "$2" ]] ;then

		echo you must provide a channel....
		return 1
	fi

while read line
do

if [[  -z "$3" || $3 == "Nominal" ]] ;then
systematics="Nominal"
fi

if [[  $3 == "list" ]] ;then
systematics="list"
fi

if [[  $3 == "listSignal" ]] ;then
#systematics="Nominal JetEnUp JetEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown BTagUp BTagDown"
systematics="listSignal"
fi

if [[  $3 == "listmuel" ]] ;then
systematics="listmuel"
fi

if [[  $3 == "listTFR" ]] ;then
systematics="TFRJetEnUp TFRJetEnDown TFRMuEnUp TFRMuEnDown TFRTauEnUp TFRTauEnDown"
fi

if [[  $3 == "HLLHC" ]] ;then
systematics="Nominal JetEnUp JetEnDown  JetResUp JetResDown"
fi


if [[  $3 == "listTT" ]] ;then
systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown BTagUp BTagDown METRecoilUp METRecoilDown BTagUp BTagDown"
fi

if [[  $3 == "listDY" ]] ;then
systematics="Nominal JetEnUp JetEnDown ZPtUp ZPtDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown METRecoilUp METRecoilDown"
fi



if [[  $3 == "listWJ" ]] ;then
systematics="Nominal JetEnUp JetEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown METRecoilUp METRecoilDown BTagUp BTagDown ZPtUp ZPtDown TopPtUp TopPtDown"
#systematics="TopPtUp TopPtDown ZPtUp ZPtDown"
#systematics="JetEnUp JetEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown BTagUp BTagDown"
#systematics="BTagDown BTagUp"
fi

if [[  $3 == "top" ]] ;then
systematics="TopPtUp TopPtDown"
fi

if [[  $3 == "Tau" ]] ;then
systematics="TauEnUp TauEnDown"
fi
if [[  $3 == "Scales" ]] ;then
systematics="ScalesUp ScalesDown"
fi
if [[  $3 == "PDF" ]] ;then
systematics="PDFUp PDFDown"
fi
if [[  $3 == "El" ]] ;then
systematics="ElEnUp ElEnDown"
systematics="ElEnUp"
fi
if [[  $3 == "Mu" ]] ;then
systematics="MuEnUp MuEnDown"
fi

if [[  $3 == "Jet" ]] ;then
systematics="JetEnUp JetEnDown"
fi

if [[  $3 == "new" ]] ;then
systematics="PDFUp PDFDown ScalesUp ScalesDown BTagUp BTagDown"
systematics="PDFUp PDFDown ScalesUp ScalesDown"
fi

if [[  $3 == "MET" ]] ;then
systematics="METRecoilUp METRecoilDown"
fi


lt=`echo $line | cut -d '/' -f2`

whichcut=$4

	echo $lt > list_$lt
	
	for syst in $systematics
	do
	
		ltt=`echo $lt | awk -F "_B_OS.root" '{print $1}'`
		if [[ ! -f plots_${2}/${ltt}_${syst}_B.root ]] ; then

			

		echo  plots for channel $2 and syst $syst and $ltt plots_${2} ${ltt}_${syst}_B.root
	 	#bsub -R "rusage[mem=2048:pool=2000]"  -q 1nh  -J plots_${syst}_$2 -i /dev/null -o /dev/null -e /dev/null run_plots_new.sh list_$lt $2 $syst $whichcut
		cp submit_template.sub subm_plots_${syst}_${2}.sub
		cp submit_template.submit subm_plots_${syst}_${2}.sub
		sed -i 's/EXECHERE/run_plots_new.sh/g' subm_plots_${syst}_${2}.sub
		sed -i 's@arguments@arguments = list_'${lt}' '$2' '${syst}' '${shichcut}'@' subm_plots_${syst}_${2}.sub
	#        condor_submit subm_plots_${syst}_${2}.sub
	
	if [[ $lt != *"DY"* ]] && [[ $lt != *"TT"* ]]; then
	 	bsub -R "rusage[mem=2048:pool=2000]"  -q 1nh  -J plots_${syst}_$2 -i /dev/null -o /dev/null -e /dev/null run_plots_new.sh list_$lt $2 $syst $whichcut
	else
	#if [[ $lt == *"DY"* ]] || [[ $lt == *"TT_"* ]]; then
	 	bsub -R "rusage[mem=4048:pool=3000]"  -q 8nh  -J plots_${syst}_$2 -i /dev/null -o /dev/null -e /dev/null run_plots_new.sh list_$lt $2 $syst $whichcut
	fi

	fi
	done
done<$1

