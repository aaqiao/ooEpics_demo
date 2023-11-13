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
//-----------------------------------------------
ModuleConfig_RVRF gobj_ModuleConfig_RVRF;

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
    if(strcmp(cmd, "SET_RPVMAP_FILE") == 0) {                       // the first 3 data are used: path, filename and macros

        if(data[1] && data[1][0]) {

            // clear
            mod -> rpvMapFilePath.assign            ("");
            mod -> rpvMapFileName.assign            ("");
            mod -> rpvMapMacrosFileSpecific.assign  ("");

            // get values
            if(data[0]) mod -> rpvMapFilePath.assign(data[0]);
            if(data[1]) mod -> rpvMapFileName.assign(data[1]);
            if(data[2]) mod -> rpvMapMacrosFileSpecific.assign(data[2]);

            // map the RPV names
            mod -> initRPVMaps();

        } else {
            cout << "ERROR:ModuleConfig_RVRF: Command SET_RPVMAP_FILE requires 3 parameters: path(optional), filename and macros(optional)!" << endl; 
            return 1;
        }

    } else if(strcmp(cmd, "SET_RPVMAP_GMACRO") == 0) {

        if(data[0] && data[0][0]) {
            mod -> rpvMapMacrosGeneral.assign(data[0]);
        } else {
            cout << "ERROR:ModuleConfig_RVRF: Command SET_RPVMAP_GMACRO requires 1 parameters: general macro string!" << endl; 
            return 1;
        }

    } else if(strcmp(cmd, "CONN_RPV") == 0) {
        mod -> initChannelAccess();

    } else if(strcmp(cmd, "PRT_RPV") == 0) {
        if(data[0]) {
            if(strcmp(data[0], "S") == 0) {                         // print the summary
                mod -> printRPVList(RPVLIST_PNT_SUMMARY);
            } else if(strcmp(data[0], "C") == 0) {                  // print the connected
                mod -> printRPVList(RPVLIST_PNT_CONN);
            } else if(strcmp(data[0], "N") == 0) {                  // print the not-connected
                mod -> printRPVList(RPVLIST_PNT_NCONN);
            } else {                                                // print all
                mod -> printRPVList(RPVLIST_PNT_ALL);
            }
        } else {
            mod -> printRPVList(RPVLIST_PNT_ALL);
        }

    } else {
        cout << "ERROR:ModuleConfig_RVRF: Command " << cmd << " not supported!" << endl;
        return 1;
    }

    return 0;
}






