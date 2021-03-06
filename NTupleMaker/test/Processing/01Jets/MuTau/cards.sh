#variable=met_MTsum_14

#file=Templates_met_MTsum_14_2320invfb
## syntax = cards.sh FILE_WITH_2D.root text_with_signal
while read line 
do

file=$1.root

channel=mt

if [[ ! -f $file ]]; then

echo the $1 is not a valid input...
return 0
fi

variable=`echo $1  | cut -d "_" -f2-4`

lumi=`echo $1 | cut -d "_" -f5 | cut -d "i" -f1`



if [[ ! -f cards_${channel}/${line}_${variable}_${channel}_${lumi}invfb.txt ]] ;then

echo Will create the card for channel $channel, signal $line, variable $variable and lumi $lumi...

cp CreateDatacards_C CreateDatacards_${variable}_${channel}_${lumi}.C

sed  -i  's/CHANNEL/'$channel'/g' CreateDatacards_${variable}_${channel}_${lumi}.C
sed  -i  's/FILE/'$file'/g' CreateDatacards_${variable}_${channel}_${lumi}.C
sed  -i  's/VARIABLE/'$variable'/g' CreateDatacards_${variable}_${channel}_${lumi}.C
sed  -i  's/SIGNAL/'$line'/g' CreateDatacards_${variable}_${channel}_${lumi}.C
sed  -i  's/LUMI/'$lumi'/g' CreateDatacards_${variable}_${channel}_${lumi}.C



root -q -b -l CreateDatacards_${variable}_${channel}_${lumi}.C

rm CreateDatacards_${variable}_${channel}_${lumi}.C
fi


done<$2
