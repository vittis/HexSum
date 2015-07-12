/*
 * Tower.cpp
 *
 *  Created on: Jul 12, 2015
 *      Author: Vitor
 */

#include "Tower.h"

Tower::Tower(Hex* hex) {
	animating=false;
	sp.Open("img/torre.png");
	location = hex;
	location->isEmpty=false;
	location->isTower=true;
	owner = NULL;
	box.x = location->center.x-sp.GetWidth()/2;
	box.y = location->center.y-sp.GetHeight();
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	hex->tower = this;
}
void Tower::Update(float dt){
	if (animating) {
		if (bandeira.currentFrame == bandeira.frameCount-1) {
			bandeira.SetFrame(bandeira.frameCount-1);
			animating=false;
			bandeira.SetFrameTime(10000);
		}
	}
	bandeira.Update(dt);
}
void Tower::BeCaptured(Player *player) {
	owner = player;
	animating=true;
	switch (owner->color) {
	case Player::BLUE:
		location->Highlight(Hex::AZUL);
		location->originalColor = Hex::AZUL;
		bandeira.Open("img/bandeira_azul.png");
		bandeira.SetFrameCount(37);
		bandeira.SetFrameTime(0.03);
		break;
	case Player::RED:
		location->Highlight(Hex::VERMELHO);
		location->originalColor = Hex::VERMELHO;
		bandeira.Open("img/bandeira_vermelha.png");
		bandeira.SetFrameCount(37);
		bandeira.SetFrameTime(0.03);
		break;
	case Player::GREEN:
		location->Highlight(Hex::VERDE);
		location->originalColor = Hex::VERDE;
		bandeira.Open("img/bandeira_verde.png");
			bandeira.SetFrameCount(37);
			bandeira.SetFrameTime(0.03);
		break;
	case Player::PURPLE:
		location->Highlight(Hex::ROXO);
		location->originalColor = Hex::ROXO;
		bandeira.Open("img/bandeira_roxa.png");
		bandeira.SetFrameCount(37);
		bandeira.SetFrameTime(0.03);
		break;
	}
}
void Tower::Render() {
	sp.Render(box.x+1.5, box.y+10, 0);
	if (owner != NULL) {
		bandeira.Render(box.x+9, box.y-35, 0);
	}
}




bool Tower::IsDead(){
	return false;
}
void Tower::NotifyCollision(GameObject& other) {}
bool Tower::Is(std::string type) {
	return type == "Tower";
}
