//=========================================================
// ModuleConfig_RVRF.cc
// 
// Class implementation for the RVRF module configuration
// Auto created from the template of ooEpics framework
//=========================================================
#include "ModuleConfig_RVRF.h"
#include "Module_RVRF.h"

using namespace std;

//-----------------------------------------------
// global objects and variables
// finding (2023.11.13): global variable may not be created, now create the global
//                       module configuration object for each module in the main 
//                       CPP file of the IOC
//-----------------------------------------------
//static ModuleConfig_RVRF gobj_ModuleConfig_RVRF;

//-----------------------------------------------
// construction
//-----------------------------------------------
ModuleConfig_RVRF::ModuleConfig_RVRF() : 
    ModuleConfig("RVRF")
{
    cout << "INFO:ModuleConfig_RVRF: Module Config for RVRF created." << endl;
}

//-----------------------------------------------
// destruction
//-----------------------------------------------
ModuleConfig_RVRF::~ModuleConfig_RVRF()
{
    cout << "INFO:ModuleConfig_RVRF: Module Config for RVRF deleted." << endl;
}

//-----------------------------------------------
// create a module instance and register it
//-----------------------------------------------
int ModuleConfig_RVRF::moduleCreate(const char *moduleName, const char *moduleInfo, int priority)
{
    Module_RVRF *mod;

    // create the module instance, it will be deleted in the ModuleManager desctruction function
    mod = new Module_RVRF(moduleName, priority);

    if(!mod) {
        cout << "ERROR:ModuleConfig_RVRF: Failed to create module instance!" << endl;
        return 1;
    }

    // register the module
    OOEPICS::gobj_moduleManager.moduleInstanceRegister("RVRF", this, moduleName, mod, OOEPICS_APPLICATION);

    return 0;
}

//-----------------------------------------------
// some initialization of the module, such as, starting some threads
//-----------------------------------------------
int ModuleConfig_RVRF::moduleInit(OOEPICS::ModuleInstance *module)
{
    Module_RVRF *mod;

    // check if the input module instance has the correct type
    if(strcmp(module -> moduleTypeName, "RVRF") == 0)
        mod = (Module_RVRF *)module -> app;
    else 
        return 1;

    if(!mod) {
        cout << "ERROR:ModuleConfig_RVRF: Invalid module instance!" << endl;
        return 1;
    }

    // start the threads
    mod -> startThreads();    

    return 0;
}

//-----------------------------------------------
// set the device parameter specified in the cmd
//-----------------------------------------------
int ModuleConfig_RVRF::moduleSet(OOEPICS::ModuleInstance *module, const char *cmd, char **data)
{
    Module_RVRF *mod;

    // check if the input module instance has the correct type
    if(strcmp(module -> moduleTypeName, "RVRF") == 0)
        mod = (Module_RVRF *)module -> app;
    else 
        return 1;

    if(!mod) {
        cout << "ERROR:ModuleConfig_RVRF: Invalid module instance!" << endl;
        return 1;
    }

    // define the commands to setup the module
    if(strcmp(cmd, "CONN_RPV") == 0) {
        mod -> initChannelAccess();
    } else {
        cout << "ERROR:ModuleConfig_RVRF: Command " << cmd << " not supported!" << endl;
        return 1;
    }

    return 0;
}






