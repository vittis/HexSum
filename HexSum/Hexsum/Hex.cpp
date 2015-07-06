/*
 * Hex.cpp
 *
 *  Created on: May 31, 2015
 *      Author: Vitor
 */

#include "Hex.h"
#include "../InputManager.h"
#include <math.h>
#include "ArenaState.h"
#include "HexGrid.h"
#include "Constants.h"


Hex::Hex(int q, int r): q(q), r(r), originalColor(Cor::PADRAO) {
	unit = NULL;
	SetOriginalHeight(0);
	color = Hex::PADRAO;
	isEmpty=true;
	sp.SetScaleX(0.4);
	sp.SetScaleY(0.4);
	if (q == 0 && r ==0) {
		Highlight(Cor::VERMELHO);
		originalColor = Cor::VERMELHO;
	}
	else {
		sp.Open("img/hex.png");
	}
	center.x = 640 + (r * Constants::HexLayout::f1 + q *Constants::HexLayout::f0) * sp.GetWidth() / 2;
	center.y = 384+ (r * Constants::HexLayout::f3 + q *Constants::HexLayout::f2) * sp.GetHeight() / 11.1-sp.GetHeight()/5;
	box = Rect(center.x-sp.GetWidth()/4, center.y-13, 50, 25);
}
void Hex::Update() {
	/*if (InputManager::GetInstance().MousePress(1)) {
		if (box.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
			std::cout<<q<<", "<<r<<std::endl;
			if (color == Cor::AMARELO && ArenaState::selectedUnit != NULL) {
				ArenaState::selectedUnit->location->UnHighlight();
				for (int i=0; i<ArenaState::grid->hex_directions.size(); i++) {
					if (ArenaState::grid->GetNeighbor(*ArenaState::selectedUnit->location, i).isEmpty)
						ArenaState::grid->GetNeighbor(*ArenaState::selectedUnit->location, i).UnHighlight();
				}
				ArenaState::selectedUnit->MoveTo(this);
				ArenaState::selectedUnit->state = Unit::UnitState::IDLE;
				ArenaState::selectedUnit->EndAction();
			}
		}
	}*/
}
void Hex::Highlight(Cor cor) {
	if (color != cor) {
		switch (cor) {
			case Cor::AMARELO:
				sp.Open("img/hex_amarelo.png");
				break;
			case Cor::VERMELHO:
				sp.Open("img/hex_vermelho.png");
				break;
			case Cor::VERDE:
				sp.Open("img/hex_verde.png");
				break;
			case Cor::BEGE:
				sp.Open("img/hex_bege.png");
				break;
			case Cor::AZUL:
				sp.Open("img/hex_azul.png");
				break;
			case Cor::ROXO:
				sp.Open("img/hex_roxo.png");
				break;
			case Cor::CIANO:
				sp.Open("img/hex_ciano.png");
				break;
			case Cor::LARANJA:
				sp.Open("img/hex_laranja.png");
				break;
			default:
				break;
		}
		color = cor;
	}
}
void Hex::SetOriginalHeight(int _altura) {
	height = _altura;
	originalHeight = _altura;
}

void Hex::UnHighlight() {
	switch (originalColor) {
			case Cor::AMARELO:
				sp.Open("img/hex_amarelo.png");
				break;
			case Cor::VERMELHO:
				sp.Open("img/hex_vermelho.png");
				break;
			case Cor::VERDE:
				sp.Open("img/hex_verde.png");
				break;
			case Cor::BEGE:
				sp.Open("img/hex_bege.png");
				break;
			default:
				sp.Open("img/hex.png");
				break;
		}
	color = originalColor;
}
void Hex::Render() {
	sp.Render(center.x-sp.GetWidth()/2, 384+height+(r * sqrt(3.0f) + q *sqrt(3.0f) / 2.0f) * sp.GetHeight() / 11.1-sp.GetWidth()/2, 0);
}
int Hex::GetQ() {
	return q;
}
int Hex::GetR() {
	return r;
}
int Hex::GetS() {
	return -q-r;
}
bool Hex::operator ==(const Hex &a){
	return (this->q == a.q) && (this->r == a.r);
}
bool Hex::operator !=(const Hex &a){
	return !(*this == a);
}
