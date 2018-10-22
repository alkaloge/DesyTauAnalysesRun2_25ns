while read line 
do

	f1=`echo $line | cut -d "_" -f2`
	f2=`echo $line | awk -F "LSP" '{print $2}' | awk -F " " '{print $1}'`

	echo $line "  " $f1 " " $f2
done<$1
