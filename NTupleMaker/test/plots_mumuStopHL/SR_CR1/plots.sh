vars="met_MTDil_15 met_MTDil_16 met_MTDil_17 met_MTDil_18 met_MTDil_19 met_MTDil_20 met_MTDil_21"
vars="met_MTDil_19 met_MTDil2_19 met_MTDil3_19 met_MTDil4_19"
vars="met_MTDil met_MTDil2  met_MTDil3  met_MTDil4  met_MTDil5  met_MTDil6  met_MTDil7  met_MTDil8"

cuts="10 11 12 13 14"

for varr in $vars
do
unset cut
	for cut in $cuts
	do
	var=${varr}_${cut}
	cp PlotsRatioPerBin_C PlotsRatioPerBin.C
	sed -i 's/VARHERE/'$var'/g' PlotsRatioPerBin.C
	root -l -q -b PlotsRatioPerBin.C
done
done
