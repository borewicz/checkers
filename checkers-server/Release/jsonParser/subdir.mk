################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../jsonParser/jsoncpp.cpp 

OBJS += \
./jsonParser/jsoncpp.o 

CPP_DEPS += \
./jsonParser/jsoncpp.d 


# Each subdirectory must supply rules for building sources it contributes
jsonParser/%.o: ../jsonParser/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -std=c++11 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


