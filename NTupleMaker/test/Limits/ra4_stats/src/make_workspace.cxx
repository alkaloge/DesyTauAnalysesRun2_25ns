#include "make_workspace.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <initializer_list>
#include <vector>
#include <string>
#include <stdlib.h>

#include <unistd.h>
#include <getopt.h>

#include "TString.h"

#include "bin.hpp"
#include "process.hpp"
#include "utilities.hpp"
#include "systematic.hpp"
#include "cut.hpp"

#include "workspace_generator.hpp"

using namespace std;


namespace{
  double lumi = 16.;
  double sig_strength = 0.;
  BlindLevel blind_level = BlindLevel::blinded;
  bool no_kappa = false;
  bool do_syst = true;
  bool use_r4 = false;
  string method("m135");
  string minjets("6");
  string hijets("9");
  string himet("400");
  string mjthresh("400");
  unsigned n_toys = 0;
  string identifier = "";
}

int main(int argc, char *argv[]){
  cout << fixed << setprecision(2);
  GetOptions(argc, argv);
  string midjets(""); midjets += to_string(atoi(hijets.c_str())-1);
  string minjets2l(""); minjets2l += to_string(atoi(minjets.c_str())-1);
  string midjets2l(""); midjets2l += to_string(atoi(midjets.c_str())-1);

  string hostname = execute("echo $HOSTNAME");
  string basefolder("/net/cms2/cms2r0/babymaker/");
  if(Contains(hostname, "lxplus")) basefolder = "/afs/cern.ch/user/m/manuelf/work/";
  string skim("skim_1lht500met200/");
  string foldermc(basefolder+"babies/2015_11_28/mc/"+skim);
  string folderdata(basefolder+"babies/2016_02_04/data/singlelep/combined/"+skim);

  //Define processes. Try to minimize splitting
  string stitch_cuts("stitch");
  Process ttbar{"ttbar", {
      {foldermc+"/*TTJets*Lept*.root/tree"},
        {foldermc+"/*TTJets_HT*.root/tree"}
    },stitch_cuts};
  Process other{"other", {
      {foldermc+"/*_WJetsToLNu*.root/tree"},
        {foldermc+"/*_TTWJets*.root/tree"},
          {foldermc+"/*_TTZTo*.root/tree"},
            {foldermc+"/*_ST_*.root/tree"},
              {foldermc+"/*DYJetsToLL*.root/tree"},
                {foldermc+"/*QCD_HT*.root/tree"},
                  {foldermc+"/*_WWTo*.root/tree"},
                    {foldermc+"/*_TTGJets*.root/tree"},
		      {foldermc+"/*_TTTT*.root/tree"},
			{foldermc+"/*_WZ*.root/tree"},
			  {foldermc+"/*ttHJetTobb*.root/tree"}
    },stitch_cuts};
  Process signal_nc{"signal", {
      {foldermc+"/*T1tttt*1500*100*.root/tree"}
    }, Cut(), false, true};
  Process signal_c{"signal", {
      {foldermc+"/*T1tttt*1200*800*.root/tree"}
    }, Cut(), false, true};

  string data_cuts("(trig[4]||trig[8])&&pass&&nonblind");
  if(method!="m135") {
    data_cuts = "(trig[4]||trig[8])&&pass";
  }
  Process data{"data", {
      {folderdata+"/*.root/tree"}
    }, data_cuts, true};

  //Make list of all backgrounds. Backgrounds assumed to be orthogonal
  set<Process> backgrounds{ttbar, other};

  //Baseline selection applied to all bins and processes
  Cut baseline{"pass&&mj>250&&ht>500&&met>200&&njets>="+minjets+"&&nbm>=2&&nleps==1"};
  Cut baseline1b{"pass&&mj>250&&ht>500&&met>200&&njets>="+minjets+"&&nbm>=1&&nleps==1"};
  Cut baseline2l{"pass&&mj>250&&ht>500&&met>200&&met<=400"};
  Cut baseline_135{"pass&&mj>250&&ht>450&&met>150"};

  //Declare bins
  //Method 2, m1b, and m1bk
  Bin r1_lowmet_1b{"r1_lowmet_1b", "mt<=140&&mj<="+mjthresh+"&&met<="+himet+"&&nbm==1",
      blind_level>=BlindLevel::blinded};
  Bin r1_highmet_1b{"r1_highmet_1b", "mt<=140&&mj<="+mjthresh+"&&met>"+himet+"&&nbm==1",
      blind_level>=BlindLevel::blinded};
  Bin r1_lowmet_2b{"r1_lowmet_2b", "mt<=140&&mj<="+mjthresh+"&&met<="+himet+"&&nbm==2",
      blind_level>=BlindLevel::blinded};
  Bin r1_lowmet_3b{"r1_lowmet_3b", "mt<=140&&mj<="+mjthresh+"&&met<="+himet+"&&nbm>2",
      blind_level>=BlindLevel::blinded};
  Bin r1_highmet_2b{"r1_highmet_2b", "mt<=140&&mj<="+mjthresh+"&&met>"+himet+"&&nbm>=2",
      blind_level>=BlindLevel::blinded};

  Bin r1_lowmet_allnb{"r1_lowmet_allnb", "mt<=140&&mj<="+mjthresh+"&&met<="+himet,
      blind_level>=BlindLevel::blinded};
  Bin r1_highmet_allnb{"r1_highmet_allnb", "mt<=140&&mj<="+mjthresh+"&&met>"+himet,
      blind_level>=BlindLevel::blinded};
  Bin r1_allnb{"r1_allnb", "mt<=140&&mj<="+mjthresh,
      blind_level>=BlindLevel::blinded};

  Bin r2_lowmet_lownj_1b{"r2_lowmet_lownj_1b", "mt<=140&&mj>"+mjthresh+"&&met<="+himet+"&&njets<="+midjets+"&&nbm==1",
      blind_level>=BlindLevel::blinded};
  Bin r2_highmet_lownj_1b{"r2_highmet_lownj_1b", "mt<=140&&mj>"+mjthresh+"&&met>"+himet+"&&njets<="+midjets+"&&nbm==1",
      blind_level>=BlindLevel::blinded};
  Bin r2_lowmet_highnj_1b{"r2_lowmet_highnj_1b", "mt<=140&&mj>"+mjthresh+"&&met<="+himet+"&&njets>"+midjets+"&&nbm==1",
      blind_level>=BlindLevel::blinded};
  Bin r2_highmet_highnj_1b{"r2_highmet_highnj_1b", "mt<=140&&mj>"+mjthresh+"&&met>"+himet+"&&njets>"+midjets+"&&nbm==1",
      blind_level>=BlindLevel::blinded};
  Bin r2_lowmet_lownj_2b{"r2_lowmet_lownj_2b", "mt<=140&&mj>"+mjthresh+"&&met<="+himet+"&&njets<="+midjets+"&&nbm==2",
      blind_level>=BlindLevel::blinded};
  Bin r2_lowmet_lownj_3b{"r2_lowmet_lownj_3b", "mt<=140&&mj>"+mjthresh+"&&met<="+himet+"&&njets<="+midjets+"&&nbm>2",
      blind_level>=BlindLevel::blinded};
  Bin r2_lowmet_highnj_2b{"r2_lowmet_highnj_2b", "mt<=140&&mj>"+mjthresh+"&&met<="+himet+"&&njets>"+midjets+"&&nbm==2",
      blind_level>=BlindLevel::blinded};
  Bin r2_lowmet_highnj_3b{"r2_lowmet_highnj_3b", "mt<=140&&mj>"+mjthresh+"&&met<="+himet+"&&njets>"+midjets+"&&nbm>2",
      blind_level>=BlindLevel::blinded};
  Bin r2_highmet_lownj_2b{"r2_highmet_lownj_2b", "mt<=140&&mj>"+mjthresh+"&&met>"+himet+"&&njets<="+midjets+"&&nbm>=2",
      blind_level>=BlindLevel::blinded};
  Bin r2_highmet_highnj_2b{"r2_highmet_highnj_2b", "mt<=140&&mj>"+mjthresh+"&&met>"+himet+"&&njets>"+midjets+"&&nbm>=2",
      blind_level>=BlindLevel::blinded};

  Bin r3_lowmet_1b{"r3_lowmet_1b", "mt>140&&mj<="+mjthresh+"&&met<="+himet+"&&nbm==1",
      blind_level>=BlindLevel::blinded};
  Bin r3_highmet_1b{"r3_highmet_1b", "mt>140&&mj<="+mjthresh+"&&met>"+himet+"&&nbm==1",
      blind_level>=BlindLevel::blinded};
  Bin r3_lowmet_2b{"r3_lowmet_2b", "mt>140&&mj<="+mjthresh+"&&met<="+himet+"&&nbm==2",
      blind_level>=BlindLevel::blinded};
  Bin r3_lowmet_3b{"r3_lowmet_3b", "mt>140&&mj<="+mjthresh+"&&met<="+himet+"&&nbm>2",
      blind_level>=BlindLevel::blinded};
  Bin r3_highmet_2b{"r3_highmet_2b", "mt>140&&mj<="+mjthresh+"&&met>"+himet+"&&nbm>=2",
      blind_level>=BlindLevel::blinded};

  Bin r3_lowmet_allnb{"r3_lowmet_allnb", "mt>140&&mj<="+mjthresh+"&&met<="+himet,
      blind_level>=BlindLevel::blinded};
  Bin r3_highmet_allnb{"r3_highmet_allnb", "mt>140&&mj<="+mjthresh+"&&met>"+himet,
      blind_level>=BlindLevel::blinded};
  Bin r3_allnb{"r3_allnb", "mt>140&&mj<="+mjthresh,
      blind_level>=BlindLevel::blinded};

  Bin r4_lowmet_lownj_1b{"r4_lowmet_lownj_1b", "mt>140&&mj>"+mjthresh+"&&met<="+himet+"&&njets<="+midjets+"&&nbm==1",
      blind_level>BlindLevel::unblind_1b};
  Bin r4_highmet_lownj_1b{"r4_highmet_lownj_1b", "mt>140&&mj>"+mjthresh+"&&met>"+himet+"&&njets<="+midjets+"&&nbm==1",
      blind_level>BlindLevel::unblind_1b};
  Bin r4_lowmet_highnj_1b{"r4_lowmet_highnj_1b", "mt>140&&mj>"+mjthresh+"&&met<="+himet+"&&njets>"+midjets+"&&nbm==1",
      blind_level>BlindLevel::unblind_1b};
  Bin r4_highmet_highnj_1b{"r4_highmet_highnj_1b", "mt>140&&mj>"+mjthresh+"&&met>"+himet+"&&njets>"+midjets+"&&nbm==1",
      blind_level>BlindLevel::unblind_1b};

  Bin r4_lowmet_lownj_2b{"r4_lowmet_lownj_2b", "mt>140&&mj>"+mjthresh+"&&met<="+himet+"&&njets<="+midjets+"&&nbm==2",
      blind_level>BlindLevel::unblinded};
  Bin r4_lowmet_lownj_3b{"r4_lowmet_lownj_3b", "mt>140&&mj>"+mjthresh+"&&met<="+himet+"&&njets<="+midjets+"&&nbm>2",
      blind_level>BlindLevel::unblinded};
  Bin r4_lowmet_highnj_2b{"r4_lowmet_highnj_2b", "mt>140&&mj>"+mjthresh+"&&met<="+himet+"&&njets>"+midjets+"&&nbm==2",
      blind_level>BlindLevel::unblinded};
  Bin r4_lowmet_highnj_3b{"r4_lowmet_highnj_3b", "mt>140&&mj>"+mjthresh+"&&met<="+himet+"&&njets>"+midjets+"&&nbm>2",
      blind_level>BlindLevel::unblinded};
  Bin r4_highmet_lownj_2b{"r4_highmet_lownj_2b", "mt>140&&mj>"+mjthresh+"&&met>"+himet+"&&njets<="+midjets+"&&nbm>=2",
      blind_level>BlindLevel::unblinded};
  Bin r4_highmet_highnj_2b{"r4_highmet_highnj_2b", "mt>140&&mj>"+mjthresh+"&&met>"+himet+"&&njets>"+midjets+"&&nbm>=2",
      blind_level>BlindLevel::unblinded};

  // Dilepton blocks
  Bin r1c_allnj{"r1c_allnj", "mt<=140&&mj<="+mjthresh+"&&nbm>=1&&njets>="+minjets+"&&nleps==1",
      blind_level>=BlindLevel::blinded};

  Bin r2c_lownj{"r2c_lownj", "mt<=140&&mj>"+mjthresh+"&&nbm>=1&&njets>="+minjets+"&&njets<="+midjets+"&&nleps==1",
      blind_level>=BlindLevel::blinded};
  Bin r2c_highnj{"r2c_highnj", "mt<=140&&mj>"+mjthresh+"&&nbm>=1&&njets>"+midjets+"&&nleps==1",
      blind_level>=BlindLevel::blinded};

  Bin d3_allnj{"d3_allnj", "mj<="+mjthresh+"&&njets>="+minjets2l+"&&nbm<=2&&nleps==2",
      blind_level>=BlindLevel::blinded};

  Bin d4_lownj{"d4_lownj", "mj>"+mjthresh+"&&njets>="+minjets2l+"&&njets<="+midjets2l+"&&nbm<=2&&nleps==2",
      blind_level>=BlindLevel::blinded};
  Bin d4_highnj{"d4_highnj", "mj>"+mjthresh+"&&njets>="+minjets2l+"&&njets>"+midjets2l+"&&nbm<=2&&nleps==2",
      blind_level>=BlindLevel::blinded};

  //Method 135
  Bin r1{"r1", "mt<=140&&mj<="+mjthresh+"&&njets>="+minjets+"&&nbm>=1&&nleps==1",
      blind_level>=BlindLevel::blinded};
  Bin r2{"r2", "mt<=140&&mj>"+mjthresh+"&&njets>="+minjets+"&&nbm>=1&&nleps==1",
      blind_level>=BlindLevel::blinded};
  Bin r3{"r3", "mt>140&&mj<="+mjthresh+"&&njets>="+minjets+"&&nbm>=1&&nleps==1",
      blind_level>=BlindLevel::blinded};
  Bin r4{"r4", "mt>140&&mj>"+mjthresh+"&&njets>="+minjets+"&&nbm>=1&&nleps==1",
      blind_level>BlindLevel::unblinded};
  Bin d3{"d3", "mj<="+mjthresh+"&&njets>="+minjets2l+"&&nbm>=0&&nleps==2",
      blind_level>=BlindLevel::blinded};
  Bin d4{"d4", "mj>"+mjthresh+"&&njets>="+minjets2l+"&&nbm>=0&&nleps==2",
      blind_level>=BlindLevel::blinded};

  //// METHOD 1BK: Adding 1b, fat R1/R3 integrated over njets, nb, but not MET
  set<Block> blocks_1bk{
    {"lowmet", {{r1_lowmet_allnb, r2_lowmet_lownj_1b, r2_lowmet_highnj_1b, r2_lowmet_lownj_2b, r2_lowmet_highnj_2b,
            r2_lowmet_lownj_3b, r2_lowmet_highnj_3b},
          {r3_lowmet_allnb, r4_lowmet_lownj_1b, r4_lowmet_highnj_1b, r4_lowmet_lownj_2b, r4_lowmet_highnj_2b,
              r4_lowmet_lownj_3b, r4_lowmet_highnj_3b}}},
      {"highmet", {{r1_highmet_allnb, r2_highmet_lownj_1b, r2_highmet_highnj_1b, r2_highmet_lownj_2b, r2_highmet_highnj_2b},
            {r3_highmet_allnb, r4_highmet_lownj_1b, r4_highmet_highnj_1b, r4_highmet_lownj_2b, r4_highmet_highnj_2b}}}
  };

  //// METHOD 135: simple ABCD for 135 ipb
  set<Block> blocks_135{
    {"all", {{r1, r2}, {r3, r4}}}
  };

  set<Block> blocks_135_2l{
    {"all", {{r1, r2}, {d3, d4}}}
  };

  //// METHOD 2l: Dilepton closure
  set<Block> blocks_2l{
    {"all", {{r1c_allnj, r2c_lownj, r2c_highnj},
          {d3_allnj, d4_lownj, d4_highnj}}}
  };

  Cut *pbaseline(&baseline1b);
  set<Block> *pblocks(&blocks_1bk);
  string sysfile("txt/systematics/m1bk.txt");
  if(method == "m1bk"){
    pbaseline = &baseline1b;
    pblocks = &blocks_1bk;
    sysfile = "txt/systematics/m1bk_c.txt";
  } else if(method == "m1bk_nodilep"){
    pbaseline = &baseline1b;
    pblocks = &blocks_1bk;
    sysfile = "txt/systematics/m1bk_nodilep.txt";
  } else if(method == "m1bk_onlydilep"){
    pbaseline = &baseline1b;
    pblocks = &blocks_1bk;
    sysfile = "txt/systematics/m1bk_onlydilep.txt";
  }else if(method == "m2l"){
    pbaseline = &baseline2l;
    pblocks = &blocks_2l;
    sysfile = "txt/systematics/m2l.txt";
  }else if(method == "m135"){
    pbaseline = &baseline_135;
    pblocks = &blocks_135;
    sysfile = "txt/systematics/m135.txt";
  }else if(method == "m135_2l"){
    pbaseline = &baseline_135;
    pblocks = &blocks_135_2l;
    sysfile = "txt/systematics/m135_2l.txt";
  }

  TString lumi_s("_lumi"); lumi_s += lumi; lumi_s.ReplaceAll(".","p"); 
  lumi_s.ReplaceAll("00000000000001",""); lumi_s.ReplaceAll("39999999999999","4");
  TString sig_s("_sig"); sig_s += sig_strength; sig_s.ReplaceAll(".","p"); 
  sig_s.ReplaceAll("00000000000001","");
  string blind_name = "";
  if(blind_level == BlindLevel::unblinded){
    blind_name = "_unblinded";
  }else if(blind_level == BlindLevel::unblind_1b){
    blind_name = "_1bunblinded";
  }else if(blind_level == BlindLevel::r4_blinded){
    blind_name = "_r4blinded";
  }
  if(identifier != "") identifier = "_" + identifier;
  string outname(method+(do_syst ? "" : "_nosys")+(use_r4 ? "" : "_nor4")
                 +(no_kappa ? "_nokappa" : "")+string("_c_met")
                 +himet+"_mj"+mjthresh+"_nj"+minjets+hijets
                 +sig_s+lumi_s.Data()+blind_name+identifier+".root");

  // Compressed SUSY
  WorkspaceGenerator wgc(*pbaseline, *pblocks, backgrounds, signal_c, data, sysfile, use_r4, sig_strength);
  wgc.SetKappaCorrected(!no_kappa);
  wgc.SetDoSystematics(do_syst);
  wgc.SetLuminosity(lumi);
  wgc.SetDoDilepton(false); // Applying dilep syst in text file
  wgc.SetDoSystematics(do_syst);
  wgc.AddToys(n_toys);
  ReplaceAll(outname, "_nc_", "_c_");
  wgc.WriteToFile(outname);

  // Non-compressed SUSY
  ReplaceAll(sysfile, "_c", "_nc");
  WorkspaceGenerator wgnc(*pbaseline, *pblocks, backgrounds, signal_nc, data, sysfile, use_r4, sig_strength);
  wgnc.SetKappaCorrected(!no_kappa);
  wgnc.SetDoSystematics(do_syst);
  wgnc.SetLuminosity(lumi);
  wgnc.SetDoDilepton(false); // Applying dilep syst in text file
  wgnc.SetDoSystematics(do_syst);
  wgnc.AddToys(n_toys);
  ReplaceAll(outname, "_c_", "_nc_");
  wgnc.WriteToFile(outname);
}

void GetOptions(int argc, char *argv[]){
  while(true){
    static struct option long_options[] = {
      {"lumi", required_argument, 0, 'l'},
      {"unblind", required_argument, 0, 'u'},
      {"no_syst", no_argument, 0, 0},
      {"lowj", required_argument, 0, 'j'},
      {"hij", required_argument, 0, 'h'},
      {"himet", required_argument, 0, 'm'},
      {"mj", required_argument, 0, 's'},
      {"nokappa", no_argument, 0, 'k'},
      {"method", required_argument, 0, 't'},
      {"use_r4", no_argument, 0, '4'},
      {"toys", required_argument, 0, 0},
      {"sig_strength", required_argument, 0, 'g'},
      {"identifier", required_argument, 0, 'i'},
      {0, 0, 0, 0}
    };

    char opt = -1;
    int option_index;
    opt = getopt_long(argc, argv, "l:u:j:h:m:s:kt:4g:i:", long_options, &option_index);
    if( opt == -1) break;

    string optname;
    switch(opt){
    case 'l':
      lumi = atof(optarg);
      break;
    case 'g':
      sig_strength = atof(optarg);
      break;
    case 'u':
      if(string(optarg)=="all"){
        blind_level = BlindLevel::unblinded;
      }else if(string(optarg)=="sideband"){
        blind_level = BlindLevel::r4_blinded;
      }else if(string(optarg)=="1b"){
        blind_level = BlindLevel::unblind_1b;
      }else{
        blind_level = BlindLevel::blinded;
      }
      break;
    case 'j':
      minjets = optarg;
      break;
    case 'h':
      hijets = optarg;
      break;
    case 'm':
      himet = optarg;
      break;
    case 'k':
      no_kappa = true;
      break;
    case '4':
      use_r4 = true;
      break;
    case 's':
      mjthresh = optarg;
      break;
    case 't':
      method = optarg;
      break;
    case 'i':
      identifier = optarg;
      break;
    case 0:
      optname = long_options[option_index].name;
      if(optname == "no_syst"){
        do_syst = false;
      }else if(optname == "toys"){
        n_toys = atoi(optarg);
      }else{
        printf("Bad option! Found option name %s\n", optname.c_str());
      }
      break;
    default:
      printf("Bad option! getopt_long returned character code 0%o\n", opt);
      break;
    }
  }
}
