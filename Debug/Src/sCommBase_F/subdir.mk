################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/sCommBase_F/CommLib_F.cpp 

OBJS += \
./Src/sCommBase_F/CommLib_F.o 

CPP_DEPS += \
./Src/sCommBase_F/CommLib_F.d 


# Each subdirectory must supply rules for building sources it contributes
Src/sCommBase_F/%.o: ../Src/sCommBase_F/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/root/workspace/CommLib_F/Src/sCommBase_F" -I"/root/workspace/CommLib_F/Src/sDebugEx" -I"/root/workspace/CommLib_F/Src/sNetwork" -I"/root/workspace/CommLib_F/Src/sFileEx_F" -I"/root/workspace/CommLib_F/Src/sMathEx_F" -I"/root/workspace/CommLib_F/Src/sMemMonitor" -I"/root/workspace/CommLib_F/Src/sSerial_F" -I"/root/workspace/CommLib_F/Src/sThreadEx_F" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


