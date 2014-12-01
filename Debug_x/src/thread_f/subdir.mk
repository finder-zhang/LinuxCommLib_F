################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/thread_f/event_f.cpp \
../src/thread_f/mutex_f.cpp \
../src/thread_f/semaphore_f.cpp \
../src/thread_f/thread_f.cpp 

OBJS += \
./src/thread_f/event_f.o \
./src/thread_f/mutex_f.o \
./src/thread_f/semaphore_f.o \
./src/thread_f/thread_f.o 

CPP_DEPS += \
./src/thread_f/event_f.d \
./src/thread_f/mutex_f.d \
./src/thread_f/semaphore_f.d \
./src/thread_f/thread_f.d 


# Each subdirectory must supply rules for building sources it contributes
src/thread_f/%.o: ../src/thread_f/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -DDEBUG_F -I"/root/workspace/comm_lib_f/src/aes_f" -I"/root/workspace/comm_lib_f/src/cjson_f" -I"/root/workspace/comm_lib_f/src/comm_base_f" -I"/root/workspace/comm_lib_f/src/debug_f" -I"/root/workspace/comm_lib_f/src/en_decode_f" -I"/root/workspace/comm_lib_f/src/file_f" -I"/root/workspace/comm_lib_f/src/math_F" -I"/root/workspace/comm_lib_f/src/mem_monitor" -I"/root/workspace/comm_lib_f/src/network_f" -I"/root/workspace/comm_lib_f/src/process_f" -I"/root/workspace/comm_lib_f/src/serial_f" -I"/root/workspace/comm_lib_f/src/thread_f" -I"/root/workspace/comm_lib_f/src/time_f" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


