#######################################################################
# Startup script for module RVRF
#
# The following parameters should to be passed in by environment variables:
#    - $(MODULE_INST_NAME)
#    - $(THREAD_PRIORITY)
#    - $(RPVMAP_PATH)
#
# Auto created from the template of ooEpics framework
#######################################################################

#---------------------------------------------------
# Other settings before iocInit
#---------------------------------------------------
callbackSetQueueSize(4096)

#---------------------------------------------------
# Create the modules
#---------------------------------------------------
# Create an instance of a module
# Parameters: Module_Type, Module_Name, Module_Info, Thread_Priority
createModule("RVRF", "$(MODULE_INST_NAME)", "", $(THREAD_PRIORITY))

# Generate database file
# Parameters: Module_Name, File_Path, Database_File_Name
INTD_generateRecords("$(MODULE_INST_NAME)", "/tmp", "RVRF-$(MODULE_INST_NAME).db");

# Load database (standard EPICS routine)
# Parameters: Database_File_Name, Macros
dbLoadRecords("/tmp/RVRF-$(MODULE_INST_NAME).db", "name_space=,module_name=$(MODULE_INST_NAME)")

#---------------------------------------------------
# Setup the modules
#---------------------------------------------------
# Set the file containing PV names to be connected with Channel Access
# Parameters: Module_Name, Command_Set_RemotePV_Map_File, Folder, RemotePV_Map_File_Name, File_Specific_Macros
#setModule("$(MODULE_INST_NAME)", "SET_RPVMAP_FILE", "$(RPVMAP_PATH)", "RPVMaps_RVRF.txt", "module_name=$(MODULE_INST_NAME)");

# Connect the remote PVs with channel access
# Parameters: Module_Name, Command_Connect_RemotePVs
#setModule("$(MODULE_INST_NAME)", "CONN_RPV");

# Init the module and start the thread
# Parameters: Module_Name
initModule("$(MODULE_INST_NAME)")



