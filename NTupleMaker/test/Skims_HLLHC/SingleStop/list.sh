dir=/nfs/dust/cms/user/alkaloge/TauAnalysis/new/new/StauAnalysis/New8025/CMSSW_8_0_25/src/DesyTauAnalyses/NTupleMaker/test
systematics="Nominal _JetEnUp _JetEnDown _UnclEnUp _UnclEnDown _TauEnUp _TauEnDown _ElEnUp _ElEnDown _MuEnUp _MuEnDown _BTagUp _BTagDown"
systematics="Nominal"


dirm=${dir}/mutauStopHL
dire=${dir}/eltauStopHL
dirme=${dir}/muelStopHL
dirme=${dir}/mumuStopHL

dirs="mutauStopHL" # eltauStop muelStop mumuStop elelStop"

rm $dir/$1


for dirr in $dirs
do

dirm=${dir}/${dirr}
for syst in $systematics
do

	
if [[ $syst != "Nominal" ]] ;then

dirm=${dir}/${dirr}${syst}
fi

echo $dirm
for i in `\ls $1*.root`
do
	f=`echo $i | awk -F ".root" '{print $1}'`
	\ls `pwd`/$i > $dirm/$f


	#echo $i | awk -F ".root" '{print $1}' > $dir/$f

if [[ $syst == "Nominal" ]] ;then
	echo $f >> $dir/$1
fi

done
done
done

cat $dir/$1 | sort -u > $dir/t ; mv $dir/t $dir/$1
