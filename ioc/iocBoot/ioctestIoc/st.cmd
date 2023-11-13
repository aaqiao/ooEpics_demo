#!../../bin/RHEL7-x86_64/testIoc

#- You may have to change testIoc to something else
#- everywhere it appears in this file

< envPaths

cd "${TOP}"

# Register all support components
dbLoadDatabase "dbd/testIoc.dbd"
testIoc_registerRecordDeviceDriver pdbbase

# define environment variables
epicsEnvSet("MODULE_INST_NAME", "MODT")
epicsEnvSet("THREAD_PRIORITY", "10")

# execute the module script
< $(RVRF)/startup_RVRF.cmd

# start the IOC
cd "${TOP}/iocBoot/${IOC}"
iocInit


