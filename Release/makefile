################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Src/sTimeEx_F/subdir.mk
-include Src/sThreadEx_F/subdir.mk
-include Src/sSerial_F/subdir.mk
-include Src/sProcessEx_F/subdir.mk
-include Src/sNetwork/subdir.mk
-include Src/sMemMonitor/subdir.mk
-include Src/sMathEx_F/subdir.mk
-include Src/sFileEx_F/subdir.mk
-include Src/sEnDecode_F/subdir.mk
-include Src/sDebugEx/subdir.mk
-include Src/sCommBase_F/subdir.mk
-include Src/sAes_F/subdir.mk
-include Src/cJSON/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: libCommLib_F.so

# Tool invocations
libCommLib_F.so: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -fno-common -shared -o "libCommLib_F.so" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(LIBRARIES)$(CPP_DEPS)$(CXX_DEPS)$(C_UPPER_DEPS) libCommLib_F.so
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
