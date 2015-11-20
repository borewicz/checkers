################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../game/Client.cpp \
../game/Clients.cpp \
../game/Game.cpp \
../game/Movement.cpp \
../game/Server.cpp \
../game/VotingManager.cpp 

OBJS += \
./game/Client.o \
./game/Clients.o \
./game/Game.o \
./game/Movement.o \
./game/Server.o \
./game/VotingManager.o 

CPP_DEPS += \
./game/Client.d \
./game/Clients.d \
./game/Game.d \
./game/Movement.d \
./game/Server.d \
./game/VotingManager.d 


# Each subdirectory must supply rules for building sources it contributes
game/%.o: ../game/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


