################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/sAlsaSound_F/AlsaPcmProtected_F.cpp \
../Src/sAlsaSound_F/AlsaPcm_F.cpp \
../Src/sAlsaSound_F/AlsaPlayCtrl_F.cpp \
../Src/sAlsaSound_F/AlsaSineWave_F.cpp \
../Src/sAlsaSound_F/AlsaWaveData_F.cpp 

OBJS += \
./Src/sAlsaSound_F/AlsaPcmProtected_F.o \
./Src/sAlsaSound_F/AlsaPcm_F.o \
./Src/sAlsaSound_F/AlsaPlayCtrl_F.o \
./Src/sAlsaSound_F/AlsaSineWave_F.o \
./Src/sAlsaSound_F/AlsaWaveData_F.o 

CPP_DEPS += \
./Src/sAlsaSound_F/AlsaPcmProtected_F.d \
./Src/sAlsaSound_F/AlsaPcm_F.d \
./Src/sAlsaSound_F/AlsaPlayCtrl_F.d \
./Src/sAlsaSound_F/AlsaSineWave_F.d \
./Src/sAlsaSound_F/AlsaWaveData_F.d 


# Each subdirectory must supply rules for building sources it contributes
Src/sAlsaSound_F/%.o: ../Src/sAlsaSound_F/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


