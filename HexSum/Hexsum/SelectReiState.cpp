/*
 * SelectState.cpp
 *
 *  Created on: 12/06/2015
 *      Author: Isaac
 */

#include "SelectReiState.h"
#include "StateData.h"
#include "../Game.h"

using std::cout;
using std::endl;

Text * SelectReiState::text = NULL;
int SelectReiState::vez = 0;
int SelectReiState::escolha1 = 0;
int SelectReiState::escolha2 = 0;
StateData *SelectReiState::stateData = new StateData();

SelectReiState::SelectReiState(): bg("img/fundo_preto.jpg", 1, 0), cortina_fundo(640,384, "img/cortina_frente.png"),
		cortina_esquerda(400, 384, "img/cortina_esquerda.png"), cortina_direita(891, 384, "img/cortina_direita.png"){

	text = new Text("font/teste.TTF", 24, TextStyle::SOLID, "Jogador 1 Escolha seu rei", Color::GetColor(255,255,255,0), 0, 0);
	vez = 0;

	rei1.Open("img/king red.png");
	rei2.Open("img/king blue.png");
	rei3.Open("img/king green.png");
	rei4.Open("img/king purple.png");

	x1=300, x2=470, x3=640, x4=810, y1=384, y2=384, y3=384, y4=384;
	scale1 = 1, scale2 = 1.2;

	box1.x = x1;
	box1.y = y1;
	box1.w = rei1.GetWidth()*scale1;
	box1.h = rei1.GetHeight()*scale1;

	box2.x = x2;
	box2.y = y2;
	box2.w = rei2.GetWidth()*scale1;
	box2.h = rei2.GetHeight()*scale1;

	box3.x = x3;
	box3.y = y3;
	box3.w = rei3.GetWidth()*scale1;
	box3.h = rei3.GetHeight()*scale1;

	box4.x = x4;
	box4.y = y4;
	box4.w = rei4.GetWidth()*scale1;
	box4.h = rei4.GetHeight()*scale1;

	Button * buttonPlay = new Button(680, 670, "img/button_over.png", "img/button_out.png", &NextState);
	buttonPlay->SetScale(0.5);
	AddUIElement(buttonPlay);
}

void SelectReiState::Render(){
	bg.Render(0, 0, 0);

	RenderArray();

	RenderUIArray();

	HighlightRei();

	rei1.Render(box1.x, box1.y, 0);
	rei2.Render(box2.x, box2.y, 0);
	rei3.Render(box3.x, box3.y, 0);
	rei4.Render(box4.x, box4.y, 0);

	this->text->Render(420,184);
	cortina_esquerda.Render();
	cortina_direita.Render();
	cortina_fundo.Render();
}


void SelectReiState::Resume(){

}

void SelectReiState::Pause(){

}

void SelectReiState::Update(float dt){
	if(!(cortina_esquerda.GetX() <= -cortina_esquerda.GetWidth()/2)){
		cortina_esquerda.SetPos(cortina_esquerda.GetX()-5, cortina_esquerda.GetY());
		cortina_direita.SetPos(cortina_direita.GetX()+5, cortina_esquerda.GetY());
	}

	OnClick();
	UpdateArray(dt);
	UpdateUIArray(dt);
}

void SelectReiState::OnClick() {
	if (InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON)) {
		if (box1.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
			if (vez==0) escolha1 = 1;
			else if (escolha1 != 1) escolha2 = 1;
		}
		else if (box2.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
			if (vez==0) escolha1 = 2;
			else if (escolha1 != 2) escolha2 = 2;
		}
		else if (box3.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
			if (vez==0) escolha1 = 3;
			else if (escolha1 != 3) escolha2 = 3;
		}
		else if (box4.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
			if (vez==0) escolha1 = 4;
			else if (escolha1 != 4) escolha2 = 4;
		}
	}
}

void SelectReiState::NextState(){
	if (vez == 0 && escolha1 != 0) {
		vez++;
		text->SetText("Jogador 2 Escolha seu rei");
	}
	else if (vez == 1 && escolha2 != 0){
		stateData->SetRei1(escolha1);
		stateData->SetRei2(escolha2);
		Game::GetInstance()->Push(new SelectCampoState(*stateData));
	}
}

void SelectReiState::HighlightRei() {
	if (escolha1 == 1 || escolha2 == 1) {
		rei1.SetScaleX(scale2);
		rei1.SetScaleY(scale2);
		box1.x = x1 - (scale2-scale1)*rei1.GetWidth()/(2*scale2);
		box1.y = y1 - (scale2-scale1)*rei1.GetHeight()/(2*scale2);
	}
	else {
		rei1.SetScaleX(scale1);
		rei1.SetScaleY(scale1);
		box1.x = x1;
		box1.y = y1;
	}

	if (escolha1 == 2 || escolha2 == 2) {
		rei2.SetScaleX(scale2);
		rei2.SetScaleY(scale2);
		box2.x = x2 - (scale2-scale1)*rei2.GetWidth()/(2*scale2);
		box2.y = y2 - (scale2-scale1)*rei2.GetHeight()/(2*scale2);
	}
	else {
		rei2.SetScaleX(scale1);
		rei2.SetScaleY(scale1);
		box2.x = x2;
		box2.y = y2;
	}

	if (escolha1 == 3 || escolha2 == 3) {
		rei3.SetScaleX(scale2);
		rei3.SetScaleY(scale2);
		box3.x = x3 - (scale2-scale1)*rei3.GetWidth()/(2*scale2);
		box3.y = y3 - (scale2-scale1)*rei3.GetHeight()/(2*scale2);;
	}
	else {
		rei3.SetScaleX(scale1);
		rei3.SetScaleY(scale1);
		box3.x = x3;
		box3.y = y3;
	}

	if (escolha1 == 4 || escolha2 == 4) {
		rei4.SetScaleX(scale2);
		rei4.SetScaleY(scale2);
		box4.x = x4 - (scale2-scale1)*rei4.GetWidth()/(2*scale2);
		box4.y = y4 - (scale2-scale1)*rei4.GetHeight()/(2*scale2);
	}
	else {
		rei4.SetScaleX(scale1);
		rei4.SetScaleY(scale1);
		box4.x = x4;
		box4.y = y4;
	}

	box1.w = rei1.GetWidth();
	box2.w = rei2.GetWidth();
	box3.w = rei3.GetWidth();
	box4.w = rei4.GetWidth();
	box1.h = rei1.GetHeight();
	box2.h = rei2.GetHeight();
	box3.h = rei3.GetHeight();
	box4.h = rei4.GetHeight();
}

int SelectReiState::GetRei1() {
	return escolha1;
}

int SelectReiState::GetRei2() {
	return escolha2;
}
