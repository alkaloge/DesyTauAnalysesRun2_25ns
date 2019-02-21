while read line
do
	
pdset=`echo $line | awk -F " " '{print $1}'`
fp=`echo $line | awk -F " " '{print $1}' | awk -F "/RunII" '{print $1}'`

unset ex
ex=`echo $line | awk -F " " '{print $2}'`

exx=_$ex

if [[ $ex == "" ]] ;then
	exx=""
fi

fpp=`echo $fp | awk -F "/" '{print $2}'`

fpp=${fpp}${exx}

cp crab_template.py crab_${fpp}.py

sed -i 's@DATASETHERE@'$pdset'@g' crab_${fpp}.py
sed -i 's@NAMEHERE@'$fpp'@g' crab_${fpp}.py
#sed -i 's@EXTHERE@'$exx'@g' crab_${fpp}.py


cp TreeProducerFromMiniAOD_9411_MC_template_2016_crab.py  TreeProducerFromMiniAOD_9411_MC_template_2016_${fpp}.py

sed -i 's@NAMEHERE@'$fpp'@g' TreeProducerFromMiniAOD_9411_MC_template_2016_${fpp}.py

crab submit crab_${fpp}.py

done<$1
