//=========================================================
// ModuleDefs_RVRF.h
//
// Global definitions for the module
// Auto created from the template of ooEpics framework
//=========================================================
#ifndef MODULE_DEFS_RVRF_H
#define MODULE_DEFS_RVRF_H

// info or error for message
#define RVRF_MSG_INFO                     0
#define RVRF_MSG_WARN                     1
#define RVRF_MSG_ERR                      2

// return code for service routines related with remote PV access
#define RVRF_RPVACCESS_FAILED            -1       // failed
#define RVRF_RPVACCESS_SUCCESS            0       // successful
#define RVRF_RPVACCESS_NOT_CONNECTED      1       // some remote PVs are not connected (some may be connected, only the connected ones will be changed)
#define RVRF_RPVACCESS_TIMEOUT            2       // timeout for PV access

// return code for jobs
#define RVRF_JOB_FAILED                  -1
#define RVRF_JOB_SUCCESS                  0
#define RVRF_JOB_STOPPED_EXCEPTION        1
#define RVRF_JOB_STOPPED_USER             2
#define RVRF_JOB_NOT_ACTIVE               3
#define RVRF_JOB_BUSY                     4

// enable and disable settings
#define RVRF_SET_DISABLED                 0
#define RVRF_SET_ENABLED                  1

#endif








