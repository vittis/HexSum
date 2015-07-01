################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Camera.cpp \
../Color.cpp \
../Game.cpp \
../GameObject.cpp \
../Geometry.cpp \
../InputManager.cpp \
../Music.cpp \
../Resources.cpp \
../Sound.cpp \
../Sprite.cpp \
../State.cpp \
../StillAnimation.cpp \
../Text.cpp \
../Timer.cpp \
../main.cpp 

OBJS += \
./Camera.o \
./Color.o \
./Game.o \
./GameObject.o \
./Geometry.o \
./InputManager.o \
./Music.o \
./Resources.o \
./Sound.o \
./Sprite.o \
./State.o \
./StillAnimation.o \
./Text.o \
./Timer.o \
./main.o 

CPP_DEPS += \
./Camera.d \
./Color.d \
./Game.d \
./GameObject.d \
./Geometry.d \
./InputManager.d \
./Music.d \
./Resources.d \
./Sound.d \
./Sprite.d \
./State.d \
./StillAnimation.d \
./Text.d \
./Timer.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Dmain=SDL_main -D__GXX_EXPERIMENTAL_CXX0X__ -D__cplusplus=201103L -I"C:\SDL2-2.0.3\include\SDL2" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


