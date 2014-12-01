################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/mem_monitor/mem_monitor_f.cpp 

OBJS += \
./src/mem_monitor/mem_monitor_f.o 

CPP_DEPS += \
./src/mem_monitor/mem_monitor_f.d 


# Each subdirectory must supply rules for building sources it contributes
src/mem_monitor/mem_monitor_f.o: ../src/mem_monitor/mem_monitor_f.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -DDEBUG_F -I"/root/workspace/comm_lib_f/src/aes_f" -I"/root/workspace/comm_lib_f/src/cjson_f" -I"/root/workspace/comm_lib_f/src/comm_base_f" -I"/root/workspace/comm_lib_f/src/debug_f" -I"/root/workspace/comm_lib_f/src/en_decode_f" -I"/root/workspace/comm_lib_f/src/file_f" -I"/root/workspace/comm_lib_f/src/math_F" -I"/root/workspace/comm_lib_f/src/mem_monitor" -I"/root/workspace/comm_lib_f/src/network_f" -I"/root/workspace/comm_lib_f/src/process_f" -I"/root/workspace/comm_lib_f/src/serial_f" -I"/root/workspace/comm_lib_f/src/thread_f" -I"/root/workspace/comm_lib_f/src/time_f" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/mem_monitor/mem_monitor_f.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


