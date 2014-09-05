################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/sFileEx_F/FileFdMmap_F.cpp \
../Src/sFileEx_F/FileFd_F.cpp \
../Src/sFileEx_F/FileRecord_F.cpp \
../Src/sFileEx_F/File_F.cpp 

OBJS += \
./Src/sFileEx_F/FileFdMmap_F.o \
./Src/sFileEx_F/FileFd_F.o \
./Src/sFileEx_F/FileRecord_F.o \
./Src/sFileEx_F/File_F.o 

CPP_DEPS += \
./Src/sFileEx_F/FileFdMmap_F.d \
./Src/sFileEx_F/FileFd_F.d \
./Src/sFileEx_F/FileRecord_F.d \
./Src/sFileEx_F/File_F.d 


# Each subdirectory must supply rules for building sources it contributes
Src/sFileEx_F/%.o: ../Src/sFileEx_F/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	mipsel-linux-uclibc-g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


