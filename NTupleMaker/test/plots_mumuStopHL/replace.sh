
while read line

do
	echo $line
	python renameHisto.py $line
	mv temp.root $line
done<$1
