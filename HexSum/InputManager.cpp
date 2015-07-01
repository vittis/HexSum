/*
 * InputManager.cpp
 *
 *  Created on: 23/04/2015
 *      Author: Isaac
 */

#include "InputManager.h"

//Arrumar os codigo loko


InputManager::InputManager() : quitRequested(false), mouseX(0), mouseY(0), updateCounter(0) {


	for(int i =0; i < 6; i++)
		mouseState[i] = mouseUpdate[i] = 0;

}

InputManager::~InputManager() {
}


InputManager& InputManager::GetInstance(){
	static InputManager inputManager;
	return inputManager;
}

void InputManager::Update(){

    SDL_Event event;

    SDL_GetMouseState(&mouseX, &mouseY);

    quitRequested = false;
    updateCounter++;

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)) {




        // Se o evento for quit, setar a flag para terminação
        if(event.type == SDL_QUIT) {
            quitRequested = true;
        }

        if(event.type == SDL_MOUSEBUTTONDOWN) {
        	mouseState[event.button.button] = true;
        	mouseUpdate[event.button.button] = updateCounter;
		}

		if(event.type == SDL_MOUSEBUTTONUP) {
        	mouseState[event.button.button] = false;
        	mouseUpdate[event.button.button] = updateCounter;
        }

        if(!event.key.repeat){
			if( event.type == SDL_KEYDOWN ) {
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}
        }

			if( event.type == SDL_KEYUP ) {
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
			}


    }


}


bool InputManager::KeyPress(int key){
	return keyUpdate[key] == updateCounter && keyState[key];

}

bool InputManager::KeyRelease(int key){
	return keyUpdate[key] == updateCounter && !keyState[key];
}

bool InputManager::IsKeyDown(int key){
	return  keyState[key];
}

bool InputManager::MousePress(int key){
	return mouseUpdate[key] == updateCounter && mouseState[key];
}

bool InputManager::MouseRelease(int key){
	return mouseUpdate[key] == updateCounter && !mouseState[key];
}

bool InputManager::IsMouseDown(int key){
	return mouseState[key];
}

int InputManager::GetMouseX(){
	return mouseX;
}

int InputManager::GetMouseY(){
	return mouseY;
}

bool InputManager::QuitRequested(){
	return quitRequested;
}

