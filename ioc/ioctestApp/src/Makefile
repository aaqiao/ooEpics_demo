TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application
PROD_IOC = ioctest

# ioctest.dbd will be created and installed
DBD += ioctest.dbd
ioctest_DBD += base.dbd
ioctest_DBD += ooEpics.dbd

# ioctest_registerRecordDeviceDriver.cpp derives from ioctest.dbd
ioctest_SRCS += ioctest_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
ioctest_SRCS_DEFAULT += ioctestMain.cpp

# Add the library
ioctest_LIBS += ooEpics
ioctest_LIBS += RVRF

# Finally link to the EPICS Base libraries
ioctest_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE
