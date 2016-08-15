#!/bin/zsh

main=`pwd`

for dir in `ls | grep _files` 
do
    cp ${main}/qsub.sh $dir/qsub.sh

    cd $dir
    echo $dir
    for file in `ls *.zsh`
    do
	list=`echo $file | sed 's/.zsh//g'`
	$main/resubmit ${list}_*.root
	exit=$?
	if [[ $exit -ne 0 ]]; then
	   echo "resubmit" $list
	   echo reason $exit

	   macro=`while read line; do; if [[ -n $line ]] then; if [[ $line[1] != "#" ]] then; echo $line | awk '{print $1}'; break; fi; fi; done < $file`
	   config=`while read line; do; if [[ -n $line ]] then; if [[ $line[1] != "#" ]] then; echo $line | awk '{print $2}'; break; fi; fi; done < $file`

	   ./qsub.sh $macro $config $list
	fi
    done
    cd $main
done
   
