################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/comm_base_f/comm_lib_f.cpp 

OBJS += \
./Src/comm_base_f/comm_lib_f.o 

CPP_DEPS += \
./Src/comm_base_f/comm_lib_f.d 


# Each subdirectory must supply rules for building sources it contributes
Src/comm_base_f/%.o: ../Src/comm_base_f/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -DDEBUG_F -I"/root/workspace/comm_lib_f/Src/sEnDecode_F" -I"/root/workspace/comm_lib_f/Src/sMathEx_F" -I"/root/workspace/comm_lib_f/Src/sMemMonitor" -I"/root/workspace/comm_lib_f/Src/sNetwork" -I"/root/workspace/comm_lib_f/Src/sSerial_F" -I"/root/workspace/comm_lib_f/Src/sThreadEx_F" -I"/root/workspace/comm_lib_f/Src/sFileEx_F" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


