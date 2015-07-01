/*
 * InputManager.h
 *
 *  Created on: 23/04/2015
 *      Author: Isaac
 */

#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

#include <SDL.h>
#include <unordered_map>

class InputManager {
private:
	bool mouseState[6];
	int mouseUpdate[6];

	bool quitRequested;
	int mouseX;
	int mouseY;
	int updateCounter;
	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;

public:
	InputManager();
	virtual ~InputManager();
	void Update();
	bool KeyPress (int);
	bool KeyRelease (int);
	bool IsKeyDown (int);
	bool MousePress (int);
	bool MouseRelease (int);
	bool IsMouseDown(int);
	int GetMouseX();
	int GetMouseY();
	bool QuitRequested();
	static InputManager& GetInstance();

};

#endif /* INPUTMANAGER_H_ */
