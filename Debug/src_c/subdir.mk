################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src_c/arrayTests.c \
../src_c/bitsTests.c \
../src_c/cbasic.c \
../src_c/checksum.c \
../src_c/list.c \
../src_c/locking.c \
../src_c/main_c.c \
../src_c/misc.c \
../src_c/sLists.c \
../src_c/share_mem.c \
../src_c/shash.c \
../src_c/ssocket.c \
../src_c/stringTests.c \
../src_c/tests.c \
../src_c/thread.c 

OBJS += \
./src_c/arrayTests.o \
./src_c/bitsTests.o \
./src_c/cbasic.o \
./src_c/checksum.o \
./src_c/list.o \
./src_c/locking.o \
./src_c/main_c.o \
./src_c/misc.o \
./src_c/sLists.o \
./src_c/share_mem.o \
./src_c/shash.o \
./src_c/ssocket.o \
./src_c/stringTests.o \
./src_c/tests.o \
./src_c/thread.o 

C_DEPS += \
./src_c/arrayTests.d \
./src_c/bitsTests.d \
./src_c/cbasic.d \
./src_c/checksum.d \
./src_c/list.d \
./src_c/locking.d \
./src_c/main_c.d \
./src_c/misc.d \
./src_c/sLists.d \
./src_c/share_mem.d \
./src_c/shash.d \
./src_c/ssocket.d \
./src_c/stringTests.d \
./src_c/tests.d \
./src_c/thread.d 


# Each subdirectory must supply rules for building sources it contributes
src_c/%.o: ../src_c/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	make CC=CFLAGS -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


