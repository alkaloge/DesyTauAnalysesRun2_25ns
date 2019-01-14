model=C1N2

# 1rst input should be the list of points
while read line 
do

susy=`echo $line | awk -F " " '{print $1}'`
lsp=`echo $line | awk -F " " '{print $2}'`

if [[ $lsp == "0 " ]] ; then
	lsp=1
fi

xsec=`cat $2 | grep "${susy} " | awk -F " " '{print $2}'`

xsec2=`echo "${xsec} * 0.001" | bc -l`
echo " "${model}_${susy}_LSP$lsp $xsec2 

done<$1


