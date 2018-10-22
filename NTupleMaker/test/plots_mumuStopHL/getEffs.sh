
models="Stop"

channel="mutau"

for model in $models
do

	cp getWeights_C getWeights.C

	cp datasets$model datasetEffs
	sed -i 's/CHANNELHERE/'$channel'/g' getWeights.C
	sed -i 's/MODELHERE/'$model'/g' getWeights.C

	root -l -q -b getWeights.C


done

