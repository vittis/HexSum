/*
 * MenuState.cpp
 *
 *  Created on: 12/06/2015
 *      Author: Isaac
 */

#include "MenuState.h"
#include "../Game.h"

MenuState::MenuState() : bg("img/fundo.jpg",1,0){
	AddUIElement(new Button(640, 500, "img/button_play_over.png","img/button_play_out.png", &Printa)) ;
	AddUIElement(new Button(640, 600, "img/button_over.png","img/button_out.png", NULL)) ;
	AddUIElement(new Button(640, 700, "img/button_over.png","img/button_out.png",  NULL)) ;
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
	UpdateArray(dt);
	UpdateUIArray(dt);
}

void MenuState::Printa(){
	Game::GetInstance()->Push(new SelectReiState());
}
