################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/cJSON/cJSON.cpp 

OBJS += \
./Src/cJSON/cJSON.o 

CPP_DEPS += \
./Src/cJSON/cJSON.d 


# Each subdirectory must supply rules for building sources it contributes
Src/cJSON/%.o: ../Src/cJSON/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -DDEBUG_F -I"/root/workspace/CommLib_F/Src/sCommBase_F" -I"/root/workspace/CommLib_F/Src/sEnDecode_F" -I"/root/workspace/CommLib_F/Src/sDebugEx" -I"/root/workspace/CommLib_F/Src/sMathEx_F" -I"/root/workspace/CommLib_F/Src/sMemMonitor" -I"/root/workspace/CommLib_F/Src/sNetwork" -I"/root/workspace/CommLib_F/Src/sSerial_F" -I"/root/workspace/CommLib_F/Src/sThreadEx_F" -I"/root/workspace/CommLib_F/Src/sFileEx_F" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


