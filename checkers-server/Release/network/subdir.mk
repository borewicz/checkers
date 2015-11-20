################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../network/TCPClientAcceptor.cpp \
../network/TCPClientConnection.cpp 

OBJS += \
./network/TCPClientAcceptor.o \
./network/TCPClientConnection.o 

CPP_DEPS += \
./network/TCPClientAcceptor.d \
./network/TCPClientConnection.d 


# Each subdirectory must supply rules for building sources it contributes
network/%.o: ../network/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=c++11 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


