//=========================================================
// Service_Example.cc
// 
// Class implementation for the example service
// Auto created from the template of ooEpics framework
//=========================================================
#include <cstdlib>
#include "Service_Example.h"

using namespace std;

//-----------------------------------------------
// construction
//-----------------------------------------------
Service_Example::Service_Example(const char *moduleName, const char *serviceName) : 
    OOEPICS::Service(moduleName, serviceName),
    rpv_setBO      (string("RPV-SET-BO")),				// here you need to set the remote PV names
    rpv_setMBBO    (string("RPV-SET-MBBO")),
    rpv_setLO      (string("RPV-SET-LO")),
    rpv_setAO      (string("RPV-SET-AO")),
    rpv_setWFO     (string("RPV-SET-WFO")),
    rpv_setSO      (string("RPV-SET-SO")),
    rpv_getBI      (string("RPV-MON-BI")),
    rpv_getMBBI    (string("RPV-MON-MBBI")),
    rpv_getLI      (string("RPV-GET-LI")),
    rpv_getAI      (string("RPV-GET-AI")),
    rpv_getWFIXaxis(string("RPV-MON-WFI-X")),
    rpv_getWFI     (string("RPV-GET-WFI")),
    rpv_getSI      (string("RPV-MON-SI"))
{
    // init the locks
    var_lockCAMonitors = EPICSLIB_func_mutexMustCreate();

    cout << "INFO:Service_Example: Object " << srvName << " created." << endl;
}

//-----------------------------------------------
// distruction
//-----------------------------------------------
Service_Example::~Service_Example()
{
    // destroy the epics mutex
    if(var_lockCAMonitors)  
        EPICSLIB_func_mutexDestroy(var_lockCAMonitors);

    cout << "INFO:Service_Example: Object " << srvName << " deleted." << endl;
}

//-----------------------------------------------
// init the remote PVs
//-----------------------------------------------
void Service_Example::initChannelAccess()
{
    // create channel access
    //      int createCA(   unsigned long             reqElemsReadIn,   // number of elements of the CA request
    //                      CA_enum_readCtrl          rdCtrlIn,         // reading type
    //                      CA_enum_writeCtrl         wtCtrlIn,         // writing type
    //                      EPICSLIB_type_mutexId     mutexIdIn,        // used to lock the data buffer when monitoring or callback reading have data arrived
    //                      EPICSLIB_type_eventId     eventIn);         // general event for connection, read and write callbacks
    //
    rpv_setBO.createCA          (1,                 OOEPICS::CA_READ_MONITOR, OOEPICS::CA_WRITE_PULL,     var_lockCAMonitors, NULL);    // writing PVs can also be monitored to verify the changes
    rpv_setMBBO.createCA        (1,                 OOEPICS::CA_READ_MONITOR, OOEPICS::CA_WRITE_PULL,     var_lockCAMonitors, NULL);
    rpv_setLO.createCA          (1,                 OOEPICS::CA_READ_MONITOR, OOEPICS::CA_WRITE_PULL,     var_lockCAMonitors, NULL);
    rpv_setAO.createCA          (1,                 OOEPICS::CA_READ_MONITOR, OOEPICS::CA_WRITE_PULL,     var_lockCAMonitors, NULL);
    rpv_setWFO.createCA         (SRVEXAM_BUF_SIZE,  OOEPICS::CA_READ_MONITOR, OOEPICS::CA_WRITE_PULL,     var_lockCAMonitors, NULL);
    rpv_setSO.createCA          (1,                 OOEPICS::CA_READ_MONITOR, OOEPICS::CA_WRITE_PULL,     var_lockCAMonitors, NULL);
    
    rpv_getBI.createCA          (1,                 OOEPICS::CA_READ_MONITOR, OOEPICS::CA_WRITE_DISABLED, var_lockCAMonitors, NULL);
    rpv_getMBBI.createCA        (1,                 OOEPICS::CA_READ_MONITOR, OOEPICS::CA_WRITE_DISABLED, var_lockCAMonitors, NULL);
    rpv_getLI.createCA          (1,                 OOEPICS::CA_READ_PULL,    OOEPICS::CA_WRITE_DISABLED, NULL,               NULL);
    rpv_getAI.createCA          (1,                 OOEPICS::CA_READ_PULL,    OOEPICS::CA_WRITE_DISABLED, NULL,               NULL);
    rpv_getWFIXaxis.createCA    (SRVEXAM_BUF_SIZE,  OOEPICS::CA_READ_MONITOR, OOEPICS::CA_WRITE_DISABLED, var_lockCAMonitors, NULL);
    rpv_getWFI.createCA         (SRVEXAM_BUF_SIZE,  OOEPICS::CA_READ_PULL,    OOEPICS::CA_WRITE_DISABLED, NULL,               NULL);
    rpv_getSI.createCA          (1,                 OOEPICS::CA_READ_MONITOR, OOEPICS::CA_WRITE_DISABLED, var_lockCAMonitors, NULL);
}

//-----------------------------------------------
// set the remote PV data (similar as caput)
//-----------------------------------------------
int Service_Example::setRemoteDataPull (epicsUInt16     boVal,
                                        epicsUInt16     mbboVal,
                                        epicsInt32      loVal,
                                        epicsFloat64    aoVal,
                                        epicsFloat64   *wfoVals,
                                        const char     *soStr,
                                        unsigned int    wfoPno)
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // DEBUG (2023.11.14): emulate the data setting
    cout << "------ set data via remote PV -------" << endl;
    cout << "boVal   = " << boVal << endl;
    cout << "mbboVal = " << mbboVal << endl;
    cout << "loVal   = " << loVal << endl;
    cout << "aoVal   = " << aoVal << endl;
    cout << "soStr   = " << soStr << endl;
    cout << "wfoVals = " << endl;
    for (int i = 0; i < (int)wfoPno; i ++) {
        cout << wfoVals[i] << ", ";
    }
    cout << endl;
    
    return RVRF_RPVACCESS_SUCCESS;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    /////////// below are the nominal code //////////////////
    int status;

    // check the input
    if(!wfoVals || !soStr || wfoPno <= 0)
        return RVRF_RPVACCESS_FAILED;

    // check the connection
    if( !rpv_setBO.isConnected()    ||
        !rpv_setMBBO.isConnected()  ||
        !rpv_setLO.isConnected()    ||
        !rpv_setAO.isConnected()    ||
        !rpv_setWFO.isConnected()   ||
        !rpv_setSO.isConnected())
        return RVRF_RPVACCESS_NOT_CONNECTED;

    // prepare the CA write requests
    rpv_setBO.caWriteRequestVal     (boVal);
    rpv_setMBBO.caWriteRequestVal   (mbboVal);
    rpv_setLO.caWriteRequestVal     (loVal);
    rpv_setAO.caWriteRequestVal     (aoVal);

    rpv_setWFO.caWriteRequestWf     (wfoVals, wfoPno);

    rpv_setSO.caWriteRequestStr     (soStr);

    // send the requests
    status = sendCARequestAndWaitFinish(CA_DEFAULT_TIMEOUT);

    // check the return status
    if(status == ECA_NORMAL) 
        return RVRF_RPVACCESS_SUCCESS;
    else if(status == ECA_TIMEOUT) 
        return RVRF_RPVACCESS_TIMEOUT;
    else
        return RVRF_RPVACCESS_FAILED;
}

//-----------------------------------------------
// get the remote PV data (similar as caget)
//-----------------------------------------------
int Service_Example::getRemoteDataPull (epicsInt32     *liVal,
                                        epicsFloat64   *aiVal,
                                        epicsFloat64   *wfiVals,
                                        unsigned int    wfiPno)
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // DEBUG (2023.11.14): emulate the data reading
    *liVal 	= 12345;
    *aiVal  = 5.2316;
    for(int i = 0; i < (int)wfiPno; i ++) {
        wfiVals[i] = rand();	
    }
	return RVRF_RPVACCESS_SUCCESS;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    	
    /////////// below are the nominal code //////////////////
    int status;

    // check the input
    if(!liVal || !aiVal || !wfiVals || wfiPno <= 0)
        return RVRF_RPVACCESS_FAILED;

    // check the connection
    if( !rpv_getLI.isConnected()    ||
        !rpv_getAI.isConnected()    ||
        !rpv_getWFI.isConnected())
        return RVRF_RPVACCESS_NOT_CONNECTED;

    // prepare the CA read requests
    rpv_getLI.caReadRequest     ();
    rpv_getAI.caReadRequest     ();
    rpv_getWFI.caReadRequest    ();

    // send the requests
    status = sendCARequestAndWaitFinish(CA_DEFAULT_TIMEOUT);

    // check the return status, if good, get the data
    if(status == ECA_NORMAL) {
        // get data
        *liVal = rpv_getLI.getValueInt32();
        *aiVal = rpv_getAI.getValueFloat64();
        
        rpv_getWFI.getValues(wfiVals, wfiPno);

        return RVRF_RPVACCESS_SUCCESS;

    } else if(status == ECA_TIMEOUT) {
        return RVRF_RPVACCESS_TIMEOUT;
    } else {
        return RVRF_RPVACCESS_FAILED;    
    }
}

//-----------------------------------------------
// get monitored remote PV data (similar as camonitor)
//-----------------------------------------------
int Service_Example::getRemoteDataMonitor  (epicsUInt16    *biVal,
                                            epicsUInt16    *mbbiVal,
                                            epicsFloat64   *wfiXaxisVals,
                                            char           *siStr,
                                            unsigned int    wfiPno)
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // DEBUG (2023.11.14): emulate the data reading
    if(rand() > RAND_MAX/2) {
        *biVal   = 0;
        *mbbiVal = 5;
    } else { 
        *biVal   = 1;
        *mbbiVal = 10;
	}
	
	for(int i = 0; i < (int)wfiPno; i ++) {
	    wfiXaxisVals[i] = (epicsFloat64)i;
	}
	
	strcpy(siStr, "A test string...");
	return RVRF_RPVACCESS_SUCCESS;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
    /////////// below are the nominal code //////////////////
    // check the input
    if(!biVal || !mbbiVal || !wfiXaxisVals || !siStr || wfiPno <= 0)
        return RVRF_RPVACCESS_FAILED;

    // check the connection
    if( !rpv_getBI.isConnected()        ||
        !rpv_getMBBI.isConnected()      ||
        !rpv_getWFIXaxis.isConnected()  ||
        !rpv_getSI.isConnected())
        return RVRF_RPVACCESS_NOT_CONNECTED;

    // directly get the values because the PVs should contain the latest monitoring results
    *biVal   = rpv_getBI.getValueUInt16();
    *mbbiVal = rpv_getMBBI.getValueUInt16();
    
    rpv_getWFIXaxis.getValues(wfiXaxisVals, wfiPno);

    rpv_getSI.getValueString(siStr);

    // return success
    return RVRF_RPVACCESS_SUCCESS;
}







