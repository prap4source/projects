################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../kernelspace/main.c \
../kernelspace/modproj.mod.c \
../kernelspace/modproj.sdtinfo.c 

O_SRCS += \
../kernelspace/main.o \
../kernelspace/modproj.mod.o \
../kernelspace/modproj.o \
../kernelspace/modproj.sdtstub.o 

S_UPPER_SRCS += \
../kernelspace/modproj.sdtstub.S 

OBJS += \
./kernelspace/main.o \
./kernelspace/modproj.mod.o \
./kernelspace/modproj.sdtinfo.o \
./kernelspace/modproj.sdtstub.o 

C_DEPS += \
./kernelspace/main.d \
./kernelspace/modproj.mod.d \
./kernelspace/modproj.sdtinfo.d 


# Each subdirectory must supply rules for building sources it contributes
kernelspace/%.o: ../kernelspace/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	make CC=CFLAGS -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

kernelspace/%.o: ../kernelspace/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Assembler'
	as  -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


