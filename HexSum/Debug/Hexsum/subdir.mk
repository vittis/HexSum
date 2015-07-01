################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Hexsum/Archer.cpp \
../Hexsum/ArenaState.cpp \
../Hexsum/Button.cpp \
../Hexsum/Hex.cpp \
../Hexsum/HexGrid.cpp \
../Hexsum/Image.cpp \
../Hexsum/King.cpp \
../Hexsum/MenuState.cpp \
../Hexsum/Player.cpp \
../Hexsum/SelectCampoState.cpp \
../Hexsum/SelectReiState.cpp \
../Hexsum/Soldier.cpp \
../Hexsum/StateData.cpp \
../Hexsum/TurnLogic.cpp \
../Hexsum/UIElement.cpp \
../Hexsum/Unit.cpp 

OBJS += \
./Hexsum/Archer.o \
./Hexsum/ArenaState.o \
./Hexsum/Button.o \
./Hexsum/Hex.o \
./Hexsum/HexGrid.o \
./Hexsum/Image.o \
./Hexsum/King.o \
./Hexsum/MenuState.o \
./Hexsum/Player.o \
./Hexsum/SelectCampoState.o \
./Hexsum/SelectReiState.o \
./Hexsum/Soldier.o \
./Hexsum/StateData.o \
./Hexsum/TurnLogic.o \
./Hexsum/UIElement.o \
./Hexsum/Unit.o 

CPP_DEPS += \
./Hexsum/Archer.d \
./Hexsum/ArenaState.d \
./Hexsum/Button.d \
./Hexsum/Hex.d \
./Hexsum/HexGrid.d \
./Hexsum/Image.d \
./Hexsum/King.d \
./Hexsum/MenuState.d \
./Hexsum/Player.d \
./Hexsum/SelectCampoState.d \
./Hexsum/SelectReiState.d \
./Hexsum/Soldier.d \
./Hexsum/StateData.d \
./Hexsum/TurnLogic.d \
./Hexsum/UIElement.d \
./Hexsum/Unit.d 


# Each subdirectory must supply rules for building sources it contributes
Hexsum/%.o: ../Hexsum/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Dmain=SDL_main -D__GXX_EXPERIMENTAL_CXX0X__ -D__cplusplus=201103L -I"C:\SDL2-2.0.3\include\SDL2" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


