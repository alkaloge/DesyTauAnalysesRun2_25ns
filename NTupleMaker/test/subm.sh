flag=$2

while read line
do

	
lt=`echo $line`
echo $line > $lt




	echo $line > dt
	
	echo submitting  run_mc.sh $line for $2 channel and point sparticle = $3 lsp = $4
	qsub run_mc2.sh $line $2 $3 $4

done<$1

