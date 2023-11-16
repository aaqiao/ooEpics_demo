#!../../bin/linux-x86_64/ioctest

#- You may have to change ioctest to something else
#- everywhere it appears in this file

< envPaths

cd "${TOP}"

# Register all support components
dbLoadDatabase "dbd/ioctest.dbd"
ioctest_registerRecordDeviceDriver pdbbase

# define environment variables
epicsEnvSet("MODULE_INST_NAME", "MODT")
epicsEnvSet("THREAD_PRIORITY", "10")

# execute the module script
cd "${TOP}/iocBoot/${IOC}"
< $(RVRF)/startup_RVRF.cmd

# start the IOC
iocInit


