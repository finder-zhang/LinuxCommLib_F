################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/sSerial_F/SerialLinux_F.cpp \
../Src/sSerial_F/SerialSyncLinux_F.cpp 

OBJS += \
./Src/sSerial_F/SerialLinux_F.o \
./Src/sSerial_F/SerialSyncLinux_F.o 

CPP_DEPS += \
./Src/sSerial_F/SerialLinux_F.d \
./Src/sSerial_F/SerialSyncLinux_F.d 


# Each subdirectory must supply rules for building sources it contributes
Src/sSerial_F/%.o: ../Src/sSerial_F/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/root/workspace/CommLib_F/Src/cJSON" -I"/root/workspace/CommLib_F/Src/sCommBase_F" -I"/root/workspace/CommLib_F/Src/sDebugEx" -I"/root/workspace/CommLib_F/Src/sFileEx_F" -I"/root/workspace/CommLib_F/Src/sMathEx_F" -I"/root/workspace/CommLib_F/Src/sMemMonitor" -I"/root/workspace/CommLib_F/Src/sNetwork" -I"/root/workspace/CommLib_F/Src/sSerial_F" -I"/root/workspace/CommLib_F/Src/sThreadEx_F" -O3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


