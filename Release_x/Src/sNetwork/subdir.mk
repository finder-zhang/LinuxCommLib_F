################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/sNetwork/FdSelector_F.cpp \
../Src/sNetwork/Socket_F.cpp \
../Src/sNetwork/TcpUdp_F.cpp \
../Src/sNetwork/socket_f.cpp \
../Src/sNetwork/tcp_client_f.cpp \
../Src/sNetwork/tcp_server_f.cpp 

OBJS += \
./Src/sNetwork/FdSelector_F.o \
./Src/sNetwork/Socket_F.o \
./Src/sNetwork/TcpUdp_F.o \
./Src/sNetwork/socket_f.o \
./Src/sNetwork/tcp_client_f.o \
./Src/sNetwork/tcp_server_f.o 

CPP_DEPS += \
./Src/sNetwork/FdSelector_F.d \
./Src/sNetwork/Socket_F.d \
./Src/sNetwork/TcpUdp_F.d \
./Src/sNetwork/socket_f.d \
./Src/sNetwork/tcp_client_f.d \
./Src/sNetwork/tcp_server_f.d 


# Each subdirectory must supply rules for building sources it contributes
Src/sNetwork/%.o: ../Src/sNetwork/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -I"/root/workspace/CommLib_F/Src/cJSON" -I"/root/workspace/CommLib_F/Src/sCommBase_F" -I"/root/workspace/CommLib_F/Src/sDebugEx" -I"/root/workspace/CommLib_F/Src/sFileEx_F" -I"/root/workspace/CommLib_F/Src/sMathEx_F" -I"/root/workspace/CommLib_F/Src/sMemMonitor" -I"/root/workspace/CommLib_F/Src/sNetwork" -I"/root/workspace/CommLib_F/Src/sSerial_F" -I"/root/workspace/CommLib_F/Src/sThreadEx_F" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


