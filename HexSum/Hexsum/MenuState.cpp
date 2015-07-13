/*
 * MenuState.cpp
 *
 *  Created on: 12/06/2015
 *      Author: Isaac
 */

#include "MenuState.h"
#include "../Game.h"

MenuState::MenuState() : bg("img/fundo.png",1,0){
	if (!musicMenu.IsOpen()) {
		musicMenu.Open("music/Menu_musica.mp3");
		musicMenu.Play(-1);
	}

}

void MenuState::Render(){
	bg.Render(0, 0, 0);

	/*
	int r = rand() % 4 + 1;

		switch(r) {
		case 1:
			bg1.Render(0, 0, 0);
			break;
		case 2:
			bg2.Render(0, 0, 0);
			break;
		case 3:
			bg3.Render(0, 0, 0);
			break;
		case 4:
			bg4.Render(0, 0, 0);
			break;
		}*/

	RenderArray();
	RenderUIArray();
}

void MenuState::Resume(){

}

void MenuState::Pause(){

}

void MenuState::Update(float dt){
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		quitRequested = true;
	}

	if (InputManager::GetInstance().KeyPress(SDLK_SPACE)) {
		Game::GetInstance()->Push(new SelectState());
	}

	UpdateArray(dt);
	UpdateUIArray(dt);
}
