################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/sMemMonitor/MemMonitor_F.cpp 

OBJS += \
./Src/sMemMonitor/MemMonitor_F.o 

CPP_DEPS += \
./Src/sMemMonitor/MemMonitor_F.d 


# Each subdirectory must supply rules for building sources it contributes
Src/sMemMonitor/MemMonitor_F.o: ../Src/sMemMonitor/MemMonitor_F.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -DDEBUG_F -I"/root/workspace/comm_lib_f/Src/sFileEx_F" -I"/root/workspace/comm_lib_f/Src/sMathEx_F" -I"/root/workspace/comm_lib_f/Src/sMemMonitor" -I"/root/workspace/comm_lib_f/Src/sNetwork" -I"/root/workspace/comm_lib_f/Src/sSerial_F" -I"/root/workspace/comm_lib_f/Src/sThreadEx_F" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"Src/sMemMonitor/MemMonitor_F.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


