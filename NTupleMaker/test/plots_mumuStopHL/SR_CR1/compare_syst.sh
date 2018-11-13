

region="SR_CR1"

systematics="METEn JetEn"
systematics="JetEn UnclEn MuEn ElEn TauEn BTag Scales PDF"
#systematics="JetEn"

processes="tt ztt dyj ww sT fakes rest allbkg"
#processes="allbkg" 

unset fullproc
unset systt

for syst in $systematics
do


systt=$syst

if [[ $syst == "JetEn" ]] ; then
	systt="JES"
fi

if [[ $syst == "METen" ]] ; then
	systt="MET"
fi

for proc in $processes 
do

systt=$syst

echo .................. $syst,  $systt, $proc

#if [[ $proc -eq "ww" || $proc -eq "ztt" || $proc -eq "dyj" ]] && [[  $syst -eq "BTag" && $proc -ne "tt" && $proc -ne "sT"  && $proc -ne "rest" && $proc -ne "fakes" ]] ; then
if [[  $proc  == "ww" || $proc == "ztt" || $proc == "dyj"  ]]  && [[  $syst == *"BTag"* ]] 
then

syst="misBTag"
systt="misBTag"

fi

if [[ $proc  != "ww" && $proc != "ztt" && $proc != "dyj"  &&   $syst == *"BTag"*  ]]  
then

syst="BTag"
systt="BTag"

fi


if [[ $proc == "tt" ]] ; then
fullproc="TTJets"
	echo will use the $proc, $fullproc
fi


if [[ $proc == "wj" ]] ; then
fullproc="WJets"

fi

if [[ $proc == "fakes" ]] ; then
fullproc="fakes"

fi


if [[ $proc == "ztt" ]] ; then
fullproc="DY#rightarrow#tau#tau"


fi

if [[ $proc == "dyj" ]] ; then
fullproc="DY#rightarrowll"


fi


if [[ $proc == "ww" ]] ; then
fullproc="WW"


fi

if [[ $proc == "dib" ]] ; then
fullproc="VV(X)"


fi


if [[ $proc == "ttx" ]] ; then
fullproc="TTXJets"


fi

if [[ $proc == "sT" ]] ; then
fullproc="singleTop"
fi

if [[ $proc == "rest" ]] ; then
fullproc="Rest"
fi

if [[ $proc == "allbkg" ]] ; then
fullproc="allbkg"
fi

echo Your systematic is $systt ... $syst
	cp PlotSys_C PlotSys.C


	sed  -i 's@SYSTEMATICS@'${systt}'@g'  PlotSys.C
	sed  -i 's@PROCESS@'${proc}'@g'  PlotSys.C
	sed  -i 's@SYSTEMATIC@'$syst'@g'  PlotSys.C
	sed  -i 's@FILEHERE@'$1'@g'  PlotSys.C
	sed  -i 's@FILEHERE@'$1'@g'  PlotSys.C
	sed  -i 's@REGION@'$region'@g'  PlotSys.C
	sed  -i 's@NAMEHERE@'${fullproc}'@g' PlotSys.C
	sed  -i 's@FILEHERE@'$1'@g' PlotSys.C

	root -l -q -b PlotSys.C
done
done


