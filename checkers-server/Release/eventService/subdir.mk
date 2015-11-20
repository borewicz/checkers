################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../eventService/RequestBoard.cpp \
../eventService/RequestConnect.cpp \
../eventService/RequestDisconnect.cpp \
../eventService/RequestError.cpp \
../eventService/RequestManager.cpp \
../eventService/RequestMessage.cpp \
../eventService/RequestMovement.cpp \
../eventService/RequestService.cpp 

OBJS += \
./eventService/RequestBoard.o \
./eventService/RequestConnect.o \
./eventService/RequestDisconnect.o \
./eventService/RequestError.o \
./eventService/RequestManager.o \
./eventService/RequestMessage.o \
./eventService/RequestMovement.o \
./eventService/RequestService.o 

CPP_DEPS += \
./eventService/RequestBoard.d \
./eventService/RequestConnect.d \
./eventService/RequestDisconnect.d \
./eventService/RequestError.d \
./eventService/RequestManager.d \
./eventService/RequestMessage.d \
./eventService/RequestMovement.d \
./eventService/RequestService.d 


# Each subdirectory must supply rules for building sources it contributes
eventService/%.o: ../eventService/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=c++11 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


