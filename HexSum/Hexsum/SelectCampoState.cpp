/*
 * SelectCampoState.cpp
 *
 *  Created on: 19/06/2015
 *      Author: Thiago
 */

#include "SelectCampoState.h"
#include "../Game.h"

using std::cout;
using std::endl;

Text * SelectCampoState::textCampo = NULL;
StateData * SelectCampoState::stateData = new StateData();
int SelectCampoState::escolhaCampo = 0;

SelectCampoState::SelectCampoState(StateData stateData): bg("img/fundo_preto.jpg", 1, 0), cortina_fundo(640,384, "img/cortina_frente.png"),
		cortina_esquerda(400, 384, "img/cortina_esquerda.png"), cortina_direita(891, 384, "img/cortina_direita.png"){

	textCampo = new Text("font/teste.TTF", 24, TextStyle::SOLID, "Escolha o campo", Color::GetColor(255,255,255,0), 0, 0);

	escolhaCampo = 0;

	this->stateData->rei1 = stateData.rei1;
	this->stateData->rei2 = stateData.rei2;

	campo1.Open("img/cenario floresta.png");
	campo2.Open("img/cortina_frente.png");
	campo3.Open("img/cenario castelo.png");

	x1=550, x2=400, x3=700, y1=300, y2=450, y3=450;
	scale1 = 0.12; scale2 = 0.2;

	box1.x = x1;
	box1.y = y1;
	box1.w = campo1.GetWidth();
	box1.h = campo1.GetHeight();

	box2.x = x2;
	box2.y = y2;
	box2.w = campo2.GetWidth();
	box2.h = campo2.GetHeight();

	box3.x = x3;
	box3.y = y2;
	box3.w = campo3.GetWidth();
	box3.h = campo3.GetHeight();

	Button * buttonPlay = new Button(680, 670, "img/button_over.png", "img/button_out.png", &NextStateCampo);
	buttonPlay->SetScale(0.5);
	AddUIElement(buttonPlay);
}

void SelectCampoState::Render(){
	bg.Render(0, 0, 0);

	RenderArray();

	RenderUIArray();

	HighlightCampo();

	campo1.Render(box1.x, box1.y, 0);
	campo2.Render(box2.x, box2.y, 0);
	campo3.Render(box3.x, box3.y, 0);

	this->textCampo->Render(420,184);
	cortina_esquerda.Render();
	cortina_direita.Render();
	cortina_fundo.Render();
}

void SelectCampoState::Resume(){

}

void SelectCampoState::Pause(){

}

void SelectCampoState::Update(float dt){
	if(!(cortina_esquerda.GetX() <= -cortina_esquerda.GetWidth()/2)){
		cortina_esquerda.SetPos(cortina_esquerda.GetX()-5, cortina_esquerda.GetY());
		cortina_direita.SetPos(cortina_direita.GetX()+5, cortina_esquerda.GetY());
	}

	OnClick();
	UpdateArray(dt);
	UpdateUIArray(dt);
}

void SelectCampoState::OnClick() {
	if (InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON)) {
		if (box1.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY()))
			escolhaCampo = 1;
		else if (box2.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY()))
			escolhaCampo = 2;
		else if (box3.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY()))
			escolhaCampo = 3;
	}
}

void SelectCampoState::NextStateCampo(){
	std::cout<<"teste1"<<std::endl;
	if (escolhaCampo != 0) {
		stateData->SetCampo(escolhaCampo);
		Game::GetInstance()->Push(new ArenaState(8, 6, *stateData));
	}
}

void SelectCampoState::HighlightCampo() {
	if (escolhaCampo == 1) {
		campo1.SetScaleX(scale2);
		campo1.SetScaleY(scale2);
		box1.x = x1 - (scale2-scale1)*campo1.GetWidth()/(2*scale2);
		box1.y = y1 - (scale2-scale1)*campo1.GetHeight()/(2*scale2);
	}
	else {
		campo1.SetScaleX(scale1);
		campo1.SetScaleY(scale1);
		box1.x = x1;
		box1.y = y1;
	}
	if (escolhaCampo == 2) {
		campo2.SetScaleX(scale2);
		campo2.SetScaleY(scale2);
		box2.x = x2 - (scale2-scale1)*campo2.GetWidth()/(2*scale2);
		box2.y = y2 - (scale2-scale1)*campo2.GetHeight()/(2*scale2);
	}
	else {
		campo2.SetScaleX(scale1);
		campo2.SetScaleY(scale1);
		box2.x = x2;
		box2.y = y2;
	}
	if (escolhaCampo == 3) {
		campo3.SetScaleX(scale2);
		campo3.SetScaleY(scale2);
		box3.x = x3 - (scale2-scale1)*campo3.GetWidth()/(2*scale2);
		box3.y = y3 - (scale2-scale1)*campo3.GetHeight()/(2*scale2);
	}
	else {
		campo3.SetScaleX(scale1);
		campo3.SetScaleY(scale1);
		box3.x = x3;
		box3.y = y3;
	}

	box1.w = campo1.GetWidth();
	box2.w = campo2.GetWidth();
	box3.w = campo3.GetWidth();
	box1.h = campo1.GetHeight();
	box2.h = campo2.GetHeight();
	box3.h = campo3.GetHeight();
}

int SelectCampoState::GetCampo() {
	return escolhaCampo;
}
