
model=$1
#ls $1*.root | awk -F "_B.root" '{print $1}' > model$1



for i in `ls Templ*${model}*.root`
#for i in `ls Templates_MTtot_MT2lester_*_${model}*.root`
#for i in `ls Templates_met_MT2lester_*_${model}*.root`
#for i in `ls Templates_MTtot_MT2lester_*_${model}*.root`
do

ln=`echo $i  | cut -d '.' -f1`

echo the file is $ln
. cards.sh $ln $1
#. cards.sh $ln C1N2
#. cards.sh $ln C1C1

done
