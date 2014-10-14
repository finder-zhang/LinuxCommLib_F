################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/sThreadEx_F/Mutex_F.cpp \
../Src/sThreadEx_F/ThreadEvent_F.cpp \
../Src/sThreadEx_F/ThreadSem_F.cpp \
../Src/sThreadEx_F/Thread_F.cpp 

OBJS += \
./Src/sThreadEx_F/Mutex_F.o \
./Src/sThreadEx_F/ThreadEvent_F.o \
./Src/sThreadEx_F/ThreadSem_F.o \
./Src/sThreadEx_F/Thread_F.o 

CPP_DEPS += \
./Src/sThreadEx_F/Mutex_F.d \
./Src/sThreadEx_F/ThreadEvent_F.d \
./Src/sThreadEx_F/ThreadSem_F.d \
./Src/sThreadEx_F/Thread_F.d 


# Each subdirectory must supply rules for building sources it contributes
Src/sThreadEx_F/%.o: ../Src/sThreadEx_F/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -DDEBUG_F -I"/root/workspace/CommLib_F/Src/sCommBase_F" -I"/root/workspace/CommLib_F/Src/sEnDecode_F" -I"/root/workspace/CommLib_F/Src/sDebugEx" -I"/root/workspace/CommLib_F/Src/sMathEx_F" -I"/root/workspace/CommLib_F/Src/sMemMonitor" -I"/root/workspace/CommLib_F/Src/sNetwork" -I"/root/workspace/CommLib_F/Src/sSerial_F" -I"/root/workspace/CommLib_F/Src/sThreadEx_F" -I"/root/workspace/CommLib_F/Src/sFileEx_F" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


