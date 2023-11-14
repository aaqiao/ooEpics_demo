//=========================================================
// Module_RVRF.h
// 
// Class definition for the RVRF module
// Auto created from the template of ooEpics framework
//=========================================================
#ifndef MODULE_RVRF_H
#define MODULE_RVRF_H

// C/C++ standard libraries
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <fstream>

// ooEpics
#include "ControlDevice.h"
#include "DomainDevice.h"
#include "Application.h"
#include "LocalPV.h"
#include "RemotePV.h"
#include "dbCommon.h"
#include "ooEpicsMisc.h"
#include "MessageLogs.h"
#include "EPICSLib_wrapper.h"

// local classes for this module
#include "Coordinator_Jobs.h"
#include "Job_Example.h"
#include "Service_Example.h"
#include "FSM_Example.h"

using namespace std;

// NOTE: please change these strings before making a GIT or CVS tag
#define RVRF_VERS "1.0.0"                     // version of the module
#define RVRF_DATE "14.11.2023"                // release date

//-----------------------------------------------
// class definition for Module_RVRF
//-----------------------------------------------
class Module_RVRF : public OOEPICS::Application
{
public:
    Module_RVRF(const char *moduleName, int priority);
    virtual ~Module_RVRF();

    // start threads in this module
    void startThreads();

    // interface for channel access initialization for this module
    void initChannelAccess();                           // init channel access in this module

private:
    // channel access
    OOEPICS::ChannelAccessContext caContext;            // channel access client context for this module

    // objects of this module
    Coordinator_Jobs  var_crd_Jobs;                     // coordinator to execute jobs
    Job_Example       var_job_Example;                  // example job
    Service_Example   var_srv_Example;                  // example service
    FSM_Example       var_fsm_Example;                  // example FSM
   
    // local PVs (EPICS records) for top level control of the module
    OOEPICS::LocalPV  lpv_cmd_jobExampleSet;            // bo, command to execute the example job to set remote data
    OOEPICS::LocalPV  lpv_cmd_jobExampleGet;            // bo, command to execute the example job to get remote data
    OOEPICS::LocalPV  lpv_cmd_fsmExample;               // mbbo, command the FSM

    OOEPICS::LocalPV  lpv_msgLog[MSGLOG_MAX_NUM];       // stringin[], display the run-time messages

    OOEPICS::LocalPV  lpv_versionStr;                   // stringin, display the version
    OOEPICS::LocalPV  lpv_compileDateStr;               // stringin, display the release (compile) date

    // module private data
    OOEPICS::MessageLogs  var_msgLog;                   // run-time message for this module

    // private routines
    void initLocalPVs();

    // callback functions
    static void lpvWcb_cmdJobExample    (void *arg);    // callback function when user setting the example job execution PVs
    static void lpvWcb_cmdFSMExample    (void *arg);    // callback function when user setting the example FSM command
    static void lpvRcb_getLogMsg        (void *arg);    // callback function for getting run-time messages in PVs
};

#endif

