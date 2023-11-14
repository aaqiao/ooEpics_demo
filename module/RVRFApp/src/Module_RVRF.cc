//=========================================================
// Module_RVRF.cc
// 
// Class implementation for the RVRF module
// Auto created from the template of ooEpics framework
//=========================================================
#include "Module_RVRF.h"

using namespace std;

//-----------------------------------------------
// construction
// NOTE: strings to generate PV names: $(moduleName)-RTST-CRDJOBS:xxx. You can change the names as expected
//-----------------------------------------------
Module_RVRF::Module_RVRF(const char *moduleName, int priority) : 
    OOEPICS::Application(moduleName),
    caContext           (OOEPICS::CA_MULTIPLE_THREAD),
    var_crd_Jobs        (moduleName, "RTST-CRDJOBS", priority, &caContext),
    var_job_Example     (moduleName, "RTST-JOBEXAM"),
    var_srv_Example     (moduleName, "RTST-SRVEXAM"), 
    var_fsm_Example     (moduleName, "RTST-FSMEXAM", priority + 1),         // higher priority than the coordinator
    var_msgLog          (moduleName)

{
    // init the local and remote PVs in this top module
    initLocalPVs();

    // init and show the FSMs
    var_fsm_Example.initFSM();
    var_fsm_Example.printFSM();

    // build up the associations, the module top class is an container
    var_crd_Jobs.registerJob            (&var_job_Example,  (int)CRDJOBS_JOBCODE_EXAMPLE);  // Coordinator executes the jobs

    var_job_Example.setService_Example  (&var_srv_Example);                                 // Job uses functions provided by services
    var_job_Example.setMessageLogging   (&var_msgLog);                                      // Job logs run-time messages

    cout << "INFO:RVRF: Module " << name << " created." << endl;
}

//-----------------------------------------------
// destruction
//-----------------------------------------------
Module_RVRF::~Module_RVRF()
{
    cout << "INFO:RVRF: Module " << name << " deleted." << endl;
}

//-----------------------------------------------
// start all threads in this module
//-----------------------------------------------
void Module_RVRF::startThreads()
{
    var_crd_Jobs.startThread();
    var_fsm_Example.startThread();
}

//-----------------------------------------------
// init the local PVs
//-----------------------------------------------
void Module_RVRF::initLocalPVs()
{
    int i;
    string strId; 
    stringstream strIdStream;

    string modn(name);                                      // module name part in PV name
    string devn("RTST");                                    // device name part in PV name
    string fsmcmd("Light Off;Light On");
                                                          
    // create the local PVs, the definition is as below
    // void init( string                  moduleName, 
    //            string                  devName, 
    //            string                  valName,
    //            string                  supStr,
    //            string                  unitStr,
    //            unsigned int            pointNum,
    //            void                   *privatePtr,
    //            INTD_CALLBACK           callback,
    //            INTD_enum_recordType    recordType,
    //            INTD_enum_scanType      scanType,
    //            IOSCANPVT              *ioIntScan, 
    //            epicsMutexId            mutexId, 
    //            epicsEventId            eventId); 

    lpv_cmd_jobExampleSet.init  (modn, devn, "CMD-JOBEXAM-SET", "", "", 1, (void *)this, lpvWcb_cmdJobExample, INTD_BO,   INTD_PASSIVE, NULL, NULL, NULL);
    lpv_cmd_jobExampleGet.init  (modn, devn, "CMD-JOBEXAM-GET", "", "", 1, (void *)this, lpvWcb_cmdJobExample, INTD_BO,   INTD_PASSIVE, NULL, NULL, NULL);
    lpv_cmd_fsmExample.init     (modn, devn, "CMD-FSMEXAM", fsmcmd, "", 1, (void *)this, lpvWcb_cmdFSMExample, INTD_MBBO, INTD_PASSIVE, NULL, NULL, NULL);

    for(i = 0; i < MSGLOG_MAX_NUM; i ++) {
        strIdStream.str("");
        strIdStream << i;
        strId = strIdStream.str();
        
        lpv_msgLog[i].setWfDataType(INTD_CHAR);

        if(i == 0) {
            lpv_msgLog[i].init(modn, devn, "MON-MSG-LOG" + strId, "", "", MSGLOG_MAX_LEN, (void *)this, lpvRcb_getLogMsg, INTD_WFI, INTD_1S, NULL, NULL, NULL);
        } else {
            lpv_msgLog[i].init(modn, devn, "MON-MSG-LOG" + strId, "", "", MSGLOG_MAX_LEN, (void *)this,             NULL, INTD_WFI, INTD_1S, NULL, NULL, NULL);
        }
    }
  
    lpv_versionStr.init     (modn, devn, "VERSION",        "", "", INTD_STR_RECORD_LEN, (void *)this, NULL, INTD_SI, INTD_10S, NULL, NULL, NULL);
    lpv_compileDateStr.init (modn, devn, "COMPILE-DATE",   "", "", INTD_STR_RECORD_LEN, (void *)this, NULL, INTD_SI, INTD_10S, NULL, NULL, NULL);

    // init default values
    lpv_versionStr.setString        (string(RVRF_VERS));
    lpv_compileDateStr.setString    (string(RVRF_DATE));
}

//-----------------------------------------------
// init CA in this module
//-----------------------------------------------
void Module_RVRF::initChannelAccess()
{   
    // connect the remote PVs in the services
    var_srv_Example.initChannelAccess();
}

//-----------------------------------------------
// implement the callback functions for local PVs
//-----------------------------------------------
// execute the example job
void Module_RVRF::lpvWcb_cmdJobExample(void *arg)
{
    Module_RVRF *mod = (Module_RVRF *)arg;
    if(!mod) return;

    // check the set value command
    if(mod -> lpv_cmd_jobExampleSet.getValueInt16() == 1) {
        mod -> var_crd_Jobs.sendEvent(CRDJOBS_EVENT_JOB, CRDJOBS_JOBCODE_EXAMPLE, JOBEXAM_SET_VALUE);
    } 

    // check the get value command
    if(mod -> lpv_cmd_jobExampleGet.getValueInt16() == 1) {
        mod -> var_crd_Jobs.sendEvent(CRDJOBS_EVENT_JOB, CRDJOBS_JOBCODE_EXAMPLE, JOBEXAM_GET_VALUE);
    } 
}

// execute the example FSM
void Module_RVRF::lpvWcb_cmdFSMExample(void *arg)
{
    Module_RVRF *mod = (Module_RVRF *)arg;
    if(!mod) return;

    // check the command
    switch(mod -> lpv_cmd_fsmExample.getValueInt16()) {
        case 0: mod -> var_fsm_Example.userCommand(FSMEXM_CMD_OFF); break;
        case 1: mod -> var_fsm_Example.userCommand(FSMEXM_CMD_ON);  break;
        default: break;
    }  
}

// get the logging message
void Module_RVRF::lpvRcb_getLogMsg(void *arg)
{
    int i;
    epicsInt8 msgStr[MSGLOG_MAX_LEN];

    Module_RVRF *mod = (Module_RVRF *)arg; 
    if(!mod) return;

    for(i = 0; i < MSGLOG_MAX_NUM; i ++) {
        mod -> var_msgLog.copyMessage((char *)msgStr, i); 
        mod -> lpv_msgLog[i].setValues(msgStr, MSGLOG_MAX_LEN);
    }
}














