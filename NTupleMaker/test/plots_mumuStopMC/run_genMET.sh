
while read line
do
	cp genMET_C genMET.C
	echo working for $line
	sed -i 's/POINT/'$line'/g' genMET.C
	root -l -q -b genMET.C
done<$1
