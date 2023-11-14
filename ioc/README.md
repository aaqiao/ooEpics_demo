# Test IOC for RVRF Module
This is an IOC project (`ioctest`) to run the `RVRF` module. The IOC is only an assembler of the modules (`RVRF` and `ooEpics`) and does not implement new functions. See the file `ioctestApp/src/Makefile` for details of how the modules are assembled. 

Note: in the CPP file `ioctestApp/src/ioctestMain.cpp` that defines the entry point of the IOC executable, we have added the code below to define the global configuration object for the `RVRF` module. This is to overcome the problem of creating global object in the `../module/RVRFApp/src/ModuleConfig_RVRF.cc` file. A global configuration object should be created for every module designed with `ooEpics`.
   ```
   #include "ModuleConfig_RVRF.h"

   ModuleConfig_RVRF gobj_ModuleConfig_RVRF;
   ```

## Code Compilation
Follow the steps below to compile the test IOC (`ioctest`) code as an executable.
1. Edit the file `configure/RELEASE` to assign the absolute paths of EPICS base, `ooEpics`, and `RVRF` (change to your installation locations):
   ```
   EPICS_BASE=/home/aqiao/epics/base-7.0.7
   OOEPICS=/home/aqiao/code_pub/ooEpics
   RVRF=/home/aqiao/code_pub/ooEpics_demo/module
   ```
3. Edit the file `configure/CONFIG_SITE` to define the cross-compiler targets (change to your target architectures, if left empty, will only compile for the host architecture):
   ```
   CROSS_COMPILER_TARGET_ARCHS = vxWorks-68040
   ```
4. Go to the folder of `ioc` and type `make` to compile it.

## Run the IOC
Go to the folder `iocBoot/ioctestIoc` and execute the command
   ```
   ./st.cmd
   ```
If the script is not executable, you can change its mode with 
   ```
   chmod +x st.cmd
   ```
