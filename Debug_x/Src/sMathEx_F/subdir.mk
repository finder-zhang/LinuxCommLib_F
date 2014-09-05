################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/sMathEx_F/Fraction_F.cpp \
../Src/sMathEx_F/Random_F.cpp 

OBJS += \
./Src/sMathEx_F/Fraction_F.o \
./Src/sMathEx_F/Random_F.o 

CPP_DEPS += \
./Src/sMathEx_F/Fraction_F.d \
./Src/sMathEx_F/Random_F.d 


# Each subdirectory must supply rules for building sources it contributes
Src/sMathEx_F/%.o: ../Src/sMathEx_F/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


