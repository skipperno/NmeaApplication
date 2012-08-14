################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/InitMultiBox.cpp \
../src/Main.cpp \
../src/MsgInHandler.cpp \
../src/NmeaComm.cpp \
../src/Selftest.cpp 

OBJS += \
./src/InitMultiBox.o \
./src/Main.o \
./src/MsgInHandler.o \
./src/NmeaComm.o \
./src/Selftest.o 

CPP_DEPS += \
./src/InitMultiBox.d \
./src/Main.d \
./src/MsgInHandler.d \
./src/NmeaComm.d \
./src/Selftest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-angstrom-linux-gnueabi-g++ -I/home/ernad/CodeSourcery/Sourcery_G++_Lite/arm-none-linux-gnueabi/libc/usr/include -I/home/ernad/Buildroot/output/target2/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


