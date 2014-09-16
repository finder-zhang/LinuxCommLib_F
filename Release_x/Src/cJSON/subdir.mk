################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/cJSON/cJSON.cpp 

OBJS += \
./Src/cJSON/cJSON.o 

CPP_DEPS += \
./Src/cJSON/cJSON.d 


# Each subdirectory must supply rules for building sources it contributes
Src/cJSON/%.o: ../Src/cJSON/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


