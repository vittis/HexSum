/*
 * SelectState.cpp
 *
 *  Created on: 11/07/2015
 *      Author: Thiago
 */

#include "SelectState.h"
#include "../Game.h"
#include "../StillAnimation.h"

StateData * SelectState::stateData = new StateData();
int SelectState::escolhaCampo = 0;
int SelectState::escolhaRei1 = 0;
int SelectState::escolhaRei2 = 0;
int SelectState::vez = 0;

SelectState::SelectState():  bg("img/Pre-Jogo/pre_jogo_fundo.png", 1, 0), cortina_fundo(640,384, "img/Pre-Jogo/cortinas_boas.png"),
		cortina_esquerda(305, 384, "img/Pre-Jogo/cortina_esquerda.png"), cortina_direita(975, 384, "img/Pre-Jogo/cortina_direita.png"),
		sombra_cima(640, 384, "img/Pre-Jogo/sombra_preta_cima.png"), sombra_baixo(640, 384, "img/Pre-Jogo/sombra_preta_baixo.png"),
		campo1min(640, 225, "img/Pre-Jogo/gelo.png"), campo2min(640, 225, "img/Pre-Jogo/floresta.png"),
		campo4min(640, 225, "img/Pre-Jogo/castelo.png") {

	vez = 0; escolhaRei1 = 0; escolhaRei2 = 0; escolhaCampo = 0;

	sombra_anim = Sprite("img/Pre-Jogo/sombra_preta_anim.png", 10, 0.1);

	restartTimer = false;

	text1 = new Text("font/mask.ttf", 26, TextStyle::BLENDED, "CRAZY FREEZING", Color::GetColor(0,0,0,0), 555, 280);
	text2 = new Text("font/mask.ttf", 26, TextStyle::BLENDED, "FLORESTA ENCANTADA", Color::GetColor(0,0,0,0), 535, 280);
	text4 = new Text("font/mask.ttf", 26, TextStyle::BLENDED, "DIES IRAE", Color::GetColor(0,0,0,0), 590, 280);

	rei1.Open("img/Pre-Jogo/statua_rei_azul.png"); //azul
	rei2.Open("img/Pre-Jogo/statua_rei_verde.png"); //verde
	rei3.Open("img/Pre-Jogo/statua_rei_roxo.png"); //roxo
	rei4.Open("img/Pre-Jogo/statua_rei_vermelho.png"); //vermelho

	rei1col.Open("img/Pre-Jogo/rei_azul.png"); //azul col
	rei2col.Open("img/Pre-Jogo/rei_verde.png"); //verde col
	rei3col.Open("img/Pre-Jogo/rei_roxo.png"); //roxo col
	rei4col.Open("img/Pre-Jogo/rei_vermelho.png"); //vermelho col

	campo1.Open("img/Pre-Jogo/marca_mapa_aceso.png"); //neve
	campo2.Open("img/Pre-Jogo/marca_mapa_aceso.png"); //floresta
	campo3.Open("img/Pre-Jogo/marca_mapa_apagado.png"); //n tem
	campo4.Open("img/Pre-Jogo/marca_mapa_aceso.png"); //castelo

	xRei1 = 183; xRei2 = 337; xRei3 = 725; xRei4 = 879;
	yRei1 = 210; yRei2 = 365; yRei3 = 365; yRei4 = 210;

	boxRei1.x = xRei1;
	boxRei1.y = yRei1;
	boxRei1.w = rei1.GetWidth()/2;
	boxRei1.h = rei1.GetHeight();

	boxRei2.x = xRei2;
	boxRei2.y = yRei2;
	boxRei2.w = rei2.GetWidth()/2;
	boxRei2.h = rei2.GetHeight();

	boxRei3.x = xRei3+rei3.GetWidth()/2;
	boxRei3.y = yRei3;
	boxRei3.w = rei3.GetWidth()/2;
	boxRei3.h = rei3.GetHeight();

	boxRei4.x = xRei4+rei4.GetWidth()/2;
	boxRei4.y = yRei4;
	boxRei4.w = rei4.GetWidth()/2;
	boxRei4.h = rei4.GetHeight();

	xCampo1 = 385; xCampo2 = 540; xCampo3 = 692; xCampo4 = 761;
	yCampo1 = 218; yCampo2 = 90; yCampo3 = 125; yCampo4 = 233;

	boxCampo1.x = xCampo1;
	boxCampo1.y = yCampo1;
	boxCampo1.w = campo1.GetWidth();
	boxCampo1.h = campo1.GetHeight();

	boxCampo2.x = xCampo2;
	boxCampo2.y = yCampo2;
	boxCampo2.w = campo2.GetWidth();
	boxCampo2.h = campo2.GetHeight();

	boxCampo3.x = xCampo3;
	boxCampo3.y = yCampo3;
	boxCampo3.w = campo3.GetWidth();
	boxCampo3.h = campo3.GetHeight();

	boxCampo4.x = xCampo4;
	boxCampo4.y = yCampo4;
	boxCampo4.w = campo4.GetWidth();
	boxCampo4.h = campo4.GetHeight();

	Button * buttonPlay = new Button(730, 670, "img/button_play_over.png", "img/button_play_out.png", &NextState);
	buttonPlay->SetScale(0.5);
	AddUIElement(buttonPlay);
}

void SelectState::Update(float dt) {
	if (InputManager::GetInstance().KeyPress(ESCAPE_KEY) || InputManager::GetInstance().QuitRequested()) {
		popRequested = true;
	}

	sombra_anim.Update(dt);
	timer.Update(dt);

	MoveCortina(6);
	OnClick();
	UpdateUIArray(dt);
}

void SelectState::MoveCortina(float vel) {
	if(!(cortina_esquerda.GetX() <= -cortina_esquerda.GetWidth())){
		cortina_esquerda.SetPos(cortina_esquerda.GetX()-vel, cortina_esquerda.GetY());
		cortina_direita.SetPos(cortina_direita.GetX()+vel, cortina_esquerda.GetY());
	}
}

void SelectState::Render() {
	bg.Render(0, 0, 0);

	RenderRei();

	campo1.Render(boxCampo1.x, boxCampo1.y, 0);
	campo2.Render(boxCampo2.x, boxCampo2.y, 0);
	campo3.Render(boxCampo3.x, boxCampo3.y, 0);
	campo4.Render(boxCampo4.x, boxCampo4.y, 0);

	RenderCampoMiniatura();

	if (vez != 2) {
		sombra_cima.Render();
	}
	if (vez == 2) {
		if (!restartTimer) {
			timer.Restart();
			restartTimer = true;
		}
		if (timer.Get() >= 1)
			sombra_baixo.Render();
		else
			sombra_anim.Render(0, 0, 0);
	}

	RenderUIArray();

	cortina_esquerda.Render();
	cortina_direita.Render();
	cortina_fundo.Render();
}

void SelectState::Pause() {

}

void SelectState::Resume() {

}

void SelectState::OnClick() {
	if (InputManager::GetInstance().IsMouseDown(LEFT_MOUSE_BUTTON)) {
		if (vez != 2) {
			if (boxRei1.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
				if (vez==0) escolhaRei1 = 2;
				else if (escolhaRei1 != 2) escolhaRei2 = 2;
			}
			else if (boxRei2.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
				if (vez==0) escolhaRei1 = 3;
				else if (escolhaRei1 != 3) escolhaRei2 = 3;
			}
			else if (boxRei3.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
				if (vez==0) escolhaRei1 = 4;
				else if (escolhaRei1 != 4) escolhaRei2 = 4;
			}
			else if (boxRei4.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
				if (vez==0) escolhaRei1 = 1;
				else if (escolhaRei1 != 1) escolhaRei2 = 1;
			}
		}
		else {
			if (boxCampo1.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY()))
				escolhaCampo = 2;
			else if (boxCampo2.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY()))
				escolhaCampo = 1;
			else if (boxCampo4.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY()))
				escolhaCampo = 3;
		}

	}
}

int SelectState::GetCampo() {
	return escolhaCampo;
}

int SelectState::GetRei1() {
	return escolhaRei1;
}

int SelectState::GetRei2() {
	return escolhaRei2;
}

void SelectState::RenderRei() {
	if (escolhaRei1 == 2 || escolhaRei2 == 2)
		rei1col.Render(xRei1, boxRei1.y-22, 0);
	else
		rei1.Render(xRei1, boxRei1.y, 0);

	if (escolhaRei1 == 3 || escolhaRei2 == 3)
		rei2col.Render(xRei2, boxRei2.y-22, 0);
	else
		rei2.Render(xRei2, boxRei2.y, 0);

	if (escolhaRei1 == 4 || escolhaRei2 == 4)
		rei3col.Render(xRei3, boxRei3.y-22, 0);
	else
		rei3.Render(xRei3, boxRei3.y, 0);

	if (escolhaRei1 == 1 || escolhaRei2 == 1)
		rei4col.Render(xRei4, boxRei4.y-22, 0);
	else
		rei4.Render(xRei4, boxRei4.y, 0);
}

void SelectState::RenderCampoMiniatura() {
	if (escolhaCampo == 2) {
		campo1min.Render();
		text1->Render(0,0);
	}
	else if (escolhaCampo == 1) {
		campo2min.Render();
		text2->Render(0,0);
	}
	else if (escolhaCampo == 3) {
		campo4min.Render();
		text4->Render(0,0);
	}
}

void SelectState::NextState() {
	if (vez == 0 && escolhaRei1 != 0) {
		vez++;
	}
	else if (vez == 1 && escolhaRei2 != 0){
		vez++;
		stateData->SetRei1(escolhaRei1);
		stateData->SetRei2(escolhaRei2);
	}
	else if (vez == 2 && escolhaCampo != 0) {
		stateData->SetCampo(escolhaCampo);
		Game::GetInstance()->Push(new ArenaState(8, 6, *stateData));
	}
}
