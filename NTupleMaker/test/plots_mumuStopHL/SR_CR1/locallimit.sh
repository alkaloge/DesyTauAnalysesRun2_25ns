cd /nfs/dust/cms/user/alkaloge/Workdir/CMSSW_8_1_0/src/Limits;eval `scramv1 runtime -sh`;cd -
cat card.txt
combine -M AsymptoticLimits card.txt | grep "Expected 50.0%"  | awk -F "< " '{print $2}' > limit_bin
eval `scramv1 runtime -sh`
echo limits done

