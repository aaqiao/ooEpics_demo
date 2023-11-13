//=========================================================
// ModuleConfig_RVRF.h
// 
// Class definition for the RVRF module configuration
// Auto created from the template of ooEpics framework
//=========================================================
#ifndef MODULECONFIG_RVRF_H
#define MODULECONFIG_RVRF_H

#include <cstdlib>
#include <cstring>
#include <cstddef>
#include <iostream>
#include <fstream>

#include "ModuleConfig.h"

using namespace std;

//-----------------------------------------------
// class forward declaration
//-----------------------------------------------
class Module_RVRF;

//-----------------------------------------------
// class definition of the module configuration of ModuleConfig_RVRF
//-----------------------------------------------
class ModuleConfig_RVRF : public OOEPICS::ModuleConfig
{
public:
    ModuleConfig_RVRF();
    virtual ~ModuleConfig_RVRF();

    virtual int moduleCreate(const char *moduleName, const char *moduleInfo, int priority);
    virtual int moduleInit(OOEPICS::ModuleInstance *module);
    virtual int moduleSet(OOEPICS::ModuleInstance *module, const char *cmd, char **data);
};

#endif
