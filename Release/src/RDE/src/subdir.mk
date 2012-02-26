################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/RDE/src/CollisionPoint.cpp \
../src/RDE/src/rBody.cpp \
../src/RDE/src/rColinfo.cpp \
../src/RDE/src/rDynamics.cpp \
../src/RDE/src/rGeometry.cpp \
../src/RDE/src/rMaterial.cpp \
../src/RDE/src/rWorld.cpp 

OBJS += \
./src/RDE/src/CollisionPoint.o \
./src/RDE/src/rBody.o \
./src/RDE/src/rColinfo.o \
./src/RDE/src/rDynamics.o \
./src/RDE/src/rGeometry.o \
./src/RDE/src/rMaterial.o \
./src/RDE/src/rWorld.o 

CPP_DEPS += \
./src/RDE/src/CollisionPoint.d \
./src/RDE/src/rBody.d \
./src/RDE/src/rColinfo.d \
./src/RDE/src/rDynamics.d \
./src/RDE/src/rGeometry.d \
./src/RDE/src/rMaterial.d \
./src/RDE/src/rWorld.d 


# Each subdirectory must supply rules for building sources it contributes
src/RDE/src/%.o: ../src/RDE/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


