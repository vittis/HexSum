/*
 * ArenaState.cpp
 *
 *  Created on: Jun 1, 2015
 *      Author: Vitor
 */

#include "ArenaState.h"
#include "HexGrid.h"
#include "../InputManager.h"
#include "../Game.h"
#include "Archer.h"
#include "Hex.h"
#include "Unit.h"
#include "Soldier.h"
#include "Archer.h"
#include "King.h"
#include <stdio.h>
#include "MenuState.h"
#include "Constants.h"
#include "Tower.h"

HexGrid* ArenaState::grid = NULL;
Unit* ArenaState::selectedUnit = NULL;
Player* ArenaState::player1 = NULL;
Player* ArenaState::player2 = NULL;
TurnLogic ArenaState::turnLogic;
int ArenaState::tipoCampo=-1;
bool ArenaState::passou = false;
//Timer ArenaState::timerTurno;
int ArenaState::summonSelecionado=0;

ArenaState::ArenaState(int n, int m, StateData stateData) {
	tipoCampo = (int)stateData.campo;
	player1 = new Player(static_cast<Player::Color>((int)stateData.rei1));
	player2 = new Player(static_cast<Player::Color>((int)stateData.rei2));


	timerAmpulheta = Timer();

	timeLine = Sprite("img/Main UI cortada/Timeline/timeline.png", 1,0);
	ampulheta = Sprite("img/Main UI cortada/Timeline/hourglass_anim.png", 10, 0);
	painel_esquerda = Sprite("img/Main UI cortada/Card/card_alt.png", 1,0);
	painel_esquerda.SetFlipped(true);
	painel_direita = Sprite("img/Main UI cortada/Card/card_alt.png", 1,0);
	bandeira = Sprite("img/Main UI cortada/Card/bandeira_red.png", 1,0);

	bg.Open("img/"+GetPrefixo()+"_fundo.png");
	switch (tipoCampo) {
	case 0:
		bg2.Open("img/floresta_baixo.png");
		bg3.Open("img/floresta_cima.png");
		bg.Open("img/fundo_preto.jpg");
		break;
	case 1:
		bg2.Open("img/gelo_baixo.png");
		bg3.Open("img/gelo_cima.png");
		bg.Open("img/fundo_preto.jpg");
		break;
	case 2:
		bg2.Open("img/castelo_baixo.png");
		bg3.Open("img/castelo_cima.png");
		break;
	}

	AddUIElement(new Button(125, 51, "img/Main UI cortada/Botoes/menu_button_hover.png","img/Main UI cortada/Botoes/menu_button.png",  NULL)) ;
	AddUIElement(new Button(50, 114, "img/Main UI cortada/Botoes/pause_button_hover.png","img/Main UI cortada/Botoes/pause_button.png",  NULL)) ;
	AddUIElement(new Button(127, 114, "img/Main UI cortada/Botoes/sound_button_hover.png","img/Main UI cortada/Botoes/sound_button.png",  NULL)) ;
	AddUIElement(new Button(196, 114, "img/Main UI cortada/Botoes/help_button_hover.png","img/Main UI cortada/Botoes/help_button.png",  NULL)) ;

	grid = new HexGrid(n, m);

	Unit* king = new King(&grid->At(0, 6), player1, Constants::manaInicial);
	AddObject(king);
	turnLogic.allUnits.emplace_back(king);

	Unit* king2 = new King(&grid->At(0, -6), player2, Constants::manaInicial);
	AddObject(king2);
	turnLogic.allUnits.emplace_back(king2);

	attackButton = new Button(50, 558, "img/Main UI cortada/Botoes/attack_hover.png", "img/Main UI cortada/Botoes/attack.png", &SelectedUnitAttack);
	moveButton = new Button(126, 514, "img/Main UI cortada/Botoes/move_hover.png", "img/Main UI cortada/Botoes/move.png", &SelectedUnitMove);
	spellButton = new Button(203, 558, "img/Main UI cortada/Botoes/spell_hover.png", "img/Main UI cortada/Botoes/spell.png", &SelectedUnitSpell);
	passButton = new Button(279, 514, "img/Main UI cortada/Botoes/pass_hover.png", "img/Main UI cortada/Botoes/pass.png", &PassTurn);

	archerButton = new Button(906, 668, "img/Main UI cortada/Fotos/archer.png", "img/Main UI cortada/Fotos/archer.png", &SelectArcher);
	soldierButton = new Button(1045, 668, "img/Main UI cortada/Fotos/soldier.png", "img/Main UI cortada/Fotos/soldier.png", &SelectSoldier);
	clericButton = new Button(1177, 668, "img/Main UI cortada/Fotos/cleric.png", "img/Main UI cortada/Fotos/cleric.png", &SelectCleric);


	AddUIElement(attackButton);
	AddUIElement(passButton);
	AddUIElement(moveButton);
	AddUIElement(spellButton);
	AddUIElement(archerButton);
	AddUIElement(soldierButton);
	AddUIElement(clericButton);

	Setup();
	turnLogic.PassTurnToNextUnit();

	hp = new Text("font/mask.ttf", 25, TextStyle::BLENDED, " ", Color::GetColor(0,0,0,0), 10, 650);
	ap = new Text("font/mask.ttf", 26, TextStyle::BLENDED, " ", Color::GetColor(0,0,0,0), 200, 635);
	atk = new Text("font/mask.ttf", 26, TextStyle::BLENDED, " ", Color::GetColor(0,0,0,0), 200, 665);
	mana = new Text("font/mask.ttf", 26, TextStyle::BLENDED, " ", Color::GetColor(0,0,0,0), 200, 695);

	//time = new Text("font/teste.TTF", 16, TextStyle::SOLID, " ", Color::GetColor(255,0,255,0), 100, 660);
	//timerTurno = Timer();
}
void ArenaState::SelectArcher() {
	summonSelecionado=2;
}
void ArenaState::SelectCleric() {
	summonSelecionado=1;
}
void ArenaState::SelectSoldier() {
	summonSelecionado=0;
}
string ArenaState::GetPrefixo() {
	switch(tipoCampo) {
		case 0:
			return "Floresta";
			break;
		case 1:
			return "Gelo";
			break;
		case 2:
			return "Castelo";
			break;
		}
}

void ArenaState::Setup() {
	for (int i=0; i<grid->hex_directions.size(); i++) {
		grid->GetNeighbor(grid->At(0,0), i).SetOriginalHeight(-15);
		grid->GetNeighbor(grid->At(0,0), i).isEmpty=false;
	}
//	AddObject(new Tower(&grid->At(0,0)));

	grid->At(grid->m/2,grid->m/2).Highlight(Hex::Cor::BEGE);
	grid->At(grid->m/2,grid->m/2).originalColor = Hex::Cor::BEGE;
	AddObject(new Tower(&grid->At(grid->m/2,grid->m/2)));

	grid->At(-grid->m/2,-grid->m/2).Highlight(Hex::Cor::BEGE);
	grid->At(-grid->m/2,-grid->m/2).originalColor = Hex::Cor::BEGE;
	AddObject(new Tower(&grid->At(-grid->m/2,-grid->m/2)));


	grid->At(-1*(grid->n/2 + 1),grid->m).Highlight(Hex::Cor::BEGE);
	grid->At(-1*(grid->n/2 + 1),grid->m).originalColor = Hex::Cor::BEGE;
	AddObject(new Tower(&grid->At(-1*(grid->n/2 + 1),grid->m)));


	grid->At((grid->n/2 + 1),-grid->m).Highlight(Hex::Cor::BEGE);
	grid->At((grid->n/2 + 1),-grid->m).originalColor = Hex::Cor::BEGE;
	AddObject(new Tower(&grid->At((grid->n/2 + 1),-grid->m)));

}
ArenaState::~ArenaState() {
	delete grid;
}

void ArenaState::Update(float dt) {
	//timerTurno.Update(dt);

	if(ArenaState::passou == true){

		timerAmpulheta.Update(dt);
		ampulheta.SetFrameTime(0.05);
		if(timerAmpulheta.Get() >= 0.6){
			ArenaState::passou = false;
			timerAmpulheta.Restart();
		}
	}else{
		ampulheta.SetFrame(9);
		ampulheta.SetFrameTime(0);
	}

	ap->SetText(MakeText("Ap: ", selectedUnit->ap));
	hp->SetText(MakeText("hp: ", selectedUnit->hp));
	atk->SetText(MakeText("Atk: ", selectedUnit->atk));

	if (selectedUnit->Is("King"))
		mana->SetText(MakeText("Mana: ", static_cast<King*>(selectedUnit)->mana));

	//if(10000-timerTurno.Get() < 0){
	//	PassTurn();
	//}else{
	//	time->SetText(MakeText("Time: ", 1000-timerTurno.Get()));
	//}

	if(selectedUnit->owner->color == Player::RED){
		bandeira.Open("img/Main UI cortada/Card/bandeira_red.png");
	}else if(selectedUnit->owner->color == Player::BLUE){
		bandeira.Open("img/Main UI cortada/Card/bandeira_blue.png");
	}else if(selectedUnit->owner->color == Player::GREEN){
		bandeira.Open("img/Main UI cortada/Card/bandeira_green.png");
	}else if(selectedUnit->owner->color == Player::PURPLE){
		bandeira.Open("img/Main UI cortada/Card/bandeira_purple.png");
	}

ampulheta.Update(dt);
	grid->GridUpdate();
	UpdateArray(dt);
	UpdateUIArray(dt);
}

void ArenaState::Render(){
	bg.Render(0,0,0);
	bg3.Render(0,0, 0);
	for (int i=0; i< grid->size(); i++) {
		grid->At(i).Render();
	}

	bg2.Render(0, 404, 0);

	timeLine.Render(415,45,0);

	for(int i = turnLogic.indice; i < turnLogic.allUnits.size(); i++){
		if(turnLogic.allUnits.size() > 8)
			turnLogic.allUnits[i]->card.Render(445+(i-(turnLogic.indice))*790/(turnLogic.allUnits.size()+1), 10,0);
		else
			turnLogic.allUnits[i]->card.Render(445+(i-(turnLogic.indice))*790/8, 10,0);
	}

	for(int i = 0; i < turnLogic.indice; i++){
		if(turnLogic.allUnits.size() > 8)
			turnLogic.allUnits[i]->card.Render(445+(turnLogic.allUnits.size()-1-(turnLogic.indice-(i+1)))*790/(turnLogic.allUnits.size()+1), 10,0);
		else
			turnLogic.allUnits[i]->card.Render(445+(turnLogic.allUnits.size()-1-(turnLogic.indice-(i+1)))*790/8, 10,0);
	}

	for (int i=0; i< grid->size(); i++) {
			if (grid->At(i).unit != NULL)
				grid->At(i).unit->Render();
			if (grid->At(i).tower != NULL)
				grid->At(i).tower->Render();
		}

	for (int i =0; i < objectArray.size(); i++) {
		if (objectArray[i].get()->Is("StillAnimation") /*|| objectArray[i].get()->Is("Tower")*/)
			objectArray[i].get()->Render();
	}

	ampulheta.Render(300,21,0);
	painel_direita.Render(735,600,0);
	painel_esquerda.Render(0,600,0);
	bandeira.Render(315,585,0);
	selectedUnit->card.Render(70,625,0);

	ap->Render(0,0);
	hp->Render(0,0);
	atk->Render(0,0);

	if (selectedUnit->Is("King")){
		mana->Render(0,0);
	}
	//time->Render(100,660);

	RenderUIArray();

}

void ArenaState::Pause(){}

void ArenaState::Resume(){}

void ArenaState::SelectedUnitAttack(){
	ArenaState::selectedUnit->ActionIntent(ArenaState::selectedUnit->Action::ATTACK);
}

void ArenaState::SelectedUnitMove(){
	ArenaState::selectedUnit->ActionIntent(ArenaState::selectedUnit->Action::MOVE);
}

void ArenaState::SelectedUnitSpell(){
	ArenaState::selectedUnit->ActionIntent(ArenaState::selectedUnit->Action::SPECIAL_ABILITY);
}


void ArenaState::PassTurn(){
	ArenaState::selectedUnit->ActionIntent(ArenaState::selectedUnit->Action::PASS);
	ArenaState::passou = true;


	//timerTurno.Restart();
}

string ArenaState::MakeText(string t1, int t2){
	char Result[5];
	string texto = t1;

	sprintf ( Result, "%d", t2 );
	texto.append(Result);

	return texto;
}
