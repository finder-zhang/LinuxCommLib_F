################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/sNetwork/Socket_F.cpp \
../Src/sNetwork/TcpUdp_F.cpp 

OBJS += \
./Src/sNetwork/Socket_F.o \
./Src/sNetwork/TcpUdp_F.o 

CPP_DEPS += \
./Src/sNetwork/Socket_F.d \
./Src/sNetwork/TcpUdp_F.d 


# Each subdirectory must supply rules for building sources it contributes
Src/sNetwork/%.o: ../Src/sNetwork/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/root/workspace/CommLib_F/Src/sCommBase_F" -I"/root/workspace/CommLib_F/Src/sFileEx_F" -I"/root/workspace/CommLib_F/Src/sMathEx_F" -I"/root/workspace/CommLib_F/Src/sMemMonitor" -I"/root/workspace/CommLib_F/Src/sSerial_F" -I"/root/workspace/CommLib_F/Src/sThreadEx_F" -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


