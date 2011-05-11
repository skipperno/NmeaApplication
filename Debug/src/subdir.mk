################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Main.cpp \
../src/NmeaComm.cpp \
../src/NmeaHandler.cpp \
../src/nmeaApplication.cpp 

OBJS += \
./src/Main.o \
./src/NmeaComm.o \
./src/NmeaHandler.o \
./src/nmeaApplication.o 

CPP_DEPS += \
./src/Main.d \
./src/NmeaComm.d \
./src/NmeaHandler.d \
./src/nmeaApplication.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	arm-none-linux-gnueabi-g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


