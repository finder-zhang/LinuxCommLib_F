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
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

