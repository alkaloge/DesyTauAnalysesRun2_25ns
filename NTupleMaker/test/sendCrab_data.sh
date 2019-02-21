while read line
do
	
fp=`echo $line | awk -F "/MINI" '{print $1}'`

fpp=`echo $fp | tr / _`
fp2=`echo $fpp | cut -d '_' -f2-15`

fpp=$fp2

#fpp=`echo $fp2 | awk -F "/" '{print $2}'`

cp crab_template_data.py crab_${fpp}.py

sed -i 's@DATASETHERE@'$line'@g' crab_${fpp}.py
sed -i 's@NAMEHERE@'$fpp'@g' crab_${fpp}.py

cp TreeProducerFromMiniAOD_9411_Data_template_2016_crab.py  TreeProducerFromMiniAOD_9411_Data_template_2016_${fpp}.py

sed -i 's@NAMEHERE@'$fpp'@g' TreeProducerFromMiniAOD_9411_Data_template_2016_${fpp}.py

crab submit crab_${fpp}.py

done<$1
