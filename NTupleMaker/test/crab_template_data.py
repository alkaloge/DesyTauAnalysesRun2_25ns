from CRABClient.UserUtilities import config, getUsernameFromSiteDB
from WMCore.Configuration import Configuration
config = config()

config.General.requestName = 'ntuples_2016_NAMEHERE'
config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'TreeProducerFromMiniAOD_9411_Data_template_2016_NAMEHERE.py'

config.JobType.maxJobRuntimeMin = 3000
config.Data.inputDataset = 'DATASETHERE'
config.Data.inputDBS = 'global'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
NJOBS = 10
#config.Data.totalUnits = 
config.Data.outLFNDirBase = '/store/user/alkaloge/2016/'
config.Data.publication = False
config.Data.outputDatasetTag = 'ntuples_2016_metv2'
config.Site.storageSite = 'T2_DE_DESY'
