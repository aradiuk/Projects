################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ft_ssl_md5.c \
../ft_ssl_md5_transform.c \
../ft_ssl_md5_utils.c \
../ft_ssl_sha256.c \
../main.c \
../parse_input.c \
../reading.c 

OBJS += \
./ft_ssl_md5.o \
./ft_ssl_md5_transform.o \
./ft_ssl_md5_utils.o \
./ft_ssl_sha256.o \
./main.o \
./parse_input.o \
./reading.o 

C_DEPS += \
./ft_ssl_md5.d \
./ft_ssl_md5_transform.d \
./ft_ssl_md5_utils.d \
./ft_ssl_sha256.d \
./main.d \
./parse_input.d \
./reading.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


