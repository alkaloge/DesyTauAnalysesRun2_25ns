variable="met_MTDil_10"

#for i in `ls Templ*root`
for i in `ls Templ*met_MTDil_10_*root`
#for i in `ls Templ*Jet*_17_*root`
do

file=`ls $i | cut -d "_" -f2-3`

unset name
name=`echo $file | cut -d "_" -f2`

if [[ $name -eq "0" ]] ; then
name=all_bins

else name=bin_${name}

fi

if [[ $file == *"L_"* ]] ; then

	name="SR_Loose!Tight"
fi

if [[ $file == *"T_"* ]] ; then

	name="SR_Tight"
fi



cp PlotsRatioPerBin_C PlotsRatioPerBin.C
sed -i 's/VARSHERE/'$variable'/g' PlotsRatioPerBin.C
sed -i 's/BINHERE/'$name'/g' PlotsRatioPerBin.C
root -l -q -b PlotsRatioPerBin.C

done
