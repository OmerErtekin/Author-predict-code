################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/features.c \
../src/list.c \
../src/main.c \
../src/signature.c 

OBJS += \
./src/features.o \
./src/list.o \
./src/main.o \
./src/signature.o 

C_DEPS += \
./src/features.d \
./src/list.d \
./src/main.d \
./src/signature.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


