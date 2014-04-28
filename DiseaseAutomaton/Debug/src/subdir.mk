################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Cell.cpp \
../src/Grid.cpp \
../src/HelperFunctions.cpp \
../src/HelperFunctions_test.cpp \
../src/Person.cpp \
../src/main.cpp 

OBJS += \
./src/Cell.o \
./src/Grid.o \
./src/HelperFunctions.o \
./src/HelperFunctions_test.o \
./src/Person.o \
./src/main.o 

CPP_DEPS += \
./src/Cell.d \
./src/Grid.d \
./src/HelperFunctions.d \
./src/HelperFunctions_test.d \
./src/Person.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


