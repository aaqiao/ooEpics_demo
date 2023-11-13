##########################################################
# Makefile
# 
# Makefile for ooEpics demo module
# 
# Created by Zheqiao Geng (gengzheqiao@126.com) on 2023.11.13
##########################################################
TOP=../..

include $(TOP)/configure/CONFIG

#==================================================
# build a support library
#==================================================
# library name
LIBRARY_IOC += RVRF

# DBD files
#DBD += RVRF.dbd

# include files
INC += Coordinator_Jobs.h
INC += FSM_Example.h
INC += Job_Example.h
INC += ModuleConfig_RVRF.h
INC += ModuleDefs_RVRF.h
INC += Module_RVRF.h
INC += Service_Example.h

# source files
RVRF_SRCS += Coordinator_Jobs.cc
RVRF_SRCS += FSM_Example.cc
RVRF_SRCS += Job_Example.cc
RVRF_SRCS += ModuleConfig_RVRF.cc
RVRF_SRCS += Module_RVRF.cc
RVRF_SRCS += Service_Example.cc

# EPICS base library
RVRF_LIBS += $(EPICS_BASE_IOC_LIBS)

include $(TOP)/configure/RULES


