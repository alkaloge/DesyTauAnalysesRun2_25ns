
#systematics="Nominal JetEnUp JetEnDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown"
systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown TFRJetEnUp TFRJetEnDown TFRMuEnUp TFRMuEnDown TFRTauEnUp TFRTauEnDown METUp METDown BTagUp BTagDown EWKUp EWKDown"

systematics="Nominal JetEnUp JetEnDown TopPtUp TopPtDown ZPtUp ZPtDown TauEnUp TauEnDown ElEnUp ElEnDown MuEnUp MuEnDown UnclEnUp UnclEnDown ScalesDown ScalesUp PDFUp PDFDown METUp METDown BTagUp BTagDown EWKUp EWKDown METRecoilUp METRecoilDown"


systematics="Nominal"

region="SR_CR1"


for rg in $region
do

for syst in $systematics
do

		root -l -q -b 'Overlap1DMod.C("'$syst'", "'$rg'")' 
done
done
