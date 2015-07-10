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

HexGrid* ArenaState::grid = NULL;
Unit* ArenaState::selectedUnit = NULL;
Player* ArenaState::player1 = NULL;
Player* ArenaState::player2 = NULL;
TurnLogic ArenaState::turnLogic;
//Timer ArenaState::timerTurno;

ArenaState::ArenaState(int n, int m, StateData stateData) {

	player1 = new Player(static_cast<Player::Color>((int)stateData.rei1));
	player2 = new Player(static_cast<Player::Color>((int)stateData.rei2));

	card_blue = Sprite("img/P1.png",1,0);
	card_red = Sprite("img/P2.png",1,0);
	campo = Sprite("img/campo.png",1,0);
	first = Sprite("img/prima.png",1,0);
	bg.Open("img/castelo_fundo.png");
	bg2.Open("img/castelo_baixo.png");
	bg3.Open("img/castelo_cima.png");
	grid = new HexGrid(n, m);

	//Unit* farmer=new Farmer(&grid->At(0,4), player2);
	//AddObject(farmer);
	//turnLogic.allUnits.emplace_back(farmer);

	//Unit* farmer2=new Farmer(&grid->At(-2,4), player2);
	//AddObject(farmer2);
	//turnLogic.allUnits.emplace_back(farmer2);

	//Unit* farmer3=new Farmer(&grid->At(2,3), player1);
	//AddObject(farmer3);
	//turnLogic.allUnits.emplace_back(farmer3);

	Unit* king = new King(&grid->At(0, 6), player2, 3-1);
	AddObject(king);
	turnLogic.allUnits.emplace_back(king);

	Unit* king2 = new King(&grid->At(0, -6), player1, 3-1);
	AddObject(king2);
	turnLogic.allUnits.emplace_back(king2);

	//Unit* archer = new Archer(&grid->At(1,2), player1);
	//AddObject(archer);
	//turnLogic.allUnits.emplace_back(archer);

	AddUIElement(new Button(50, 50, "img/button_attack_over.png", "img/button_attack_out.png", &SelectedUnitAttack));
	AddUIElement(new Button(120, 50, "img/button_pass_over.png", "img/button_pass_out.png", &PassTurn));
	Setup();
	turnLogic.PassTurnToNextUnit();

	ap = new Text("font/teste.TTF", 16, TextStyle::SOLID, " ", Color::GetColor(0,255,0,0), 100, 600);
	hp = new Text("font/teste.TTF", 16, TextStyle::SOLID, " ", Color::GetColor(0,255,255,0), 100,620);
	atk = new Text("font/teste.TTF", 16, TextStyle::SOLID, " ", Color::GetColor(255,0,255,0), 100, 640);
	mana = new Text("font/teste.TTF", 16, TextStyle::SOLID, " ", Color::GetColor(255,0,255,0), 100, 660);

	//time = new Text("font/teste.TTF", 16, TextStyle::SOLID, " ", Color::GetColor(255,0,255,0), 100, 660);

	//timerTurno = Timer();

}


void ArenaState::Setup() {
	for (int i=0; i<grid->hex_directions.size(); i++) {
		grid->GetNeighbor(grid->At(0,0), i).SetOriginalHeight(-15);
		grid->GetNeighbor(grid->At(0,0), i).isEmpty=false;
	}
	grid->At(grid->m/2,grid->m/2).Highlight(Hex::Cor::BEGE);
	grid->At(grid->m/2,grid->m/2).originalColor = Hex::Cor::BEGE;
	grid->At(-grid->m/2,-grid->m/2).Highlight(Hex::Cor::BEGE);
	grid->At(-grid->m/2,-grid->m/2).originalColor = Hex::Cor::BEGE;

	grid->At(-1*(grid->n/2 + 1),grid->m).Highlight(Hex::Cor::BEGE);
	grid->At(-1*(grid->n/2 + 1),grid->m).originalColor = Hex::Cor::BEGE;
	grid->At((grid->n/2 + 1),-grid->m).Highlight(Hex::Cor::BEGE);
	grid->At((grid->n/2 + 1),-grid->m).originalColor = Hex::Cor::BEGE;

	//grid->At(0,(grid->n+grid->m)/2-1).Highlight(Hex::Cor::VERDE);
	//grid->At(0,(grid->n+grid->m)/2-1).originalColor = Hex::Cor::VERDE;
//	grid->At(0,-1*((grid->n+grid->m)/2-1)).Highlight(Hex::Cor::VERDE);
//	grid->At(0,-1*((grid->n+grid->m)/2-1)).originalColor = Hex::Cor::VERDE;
	for (int i=0; i<turnLogic.allUnits.size(); i++) {
		if (turnLogic.allUnits[i]->owner->color == Player::RED)
			turnLogic.allUnits[i]->location->Highlight(Hex::VERMELHO);
		else
			turnLogic.allUnits[i]->location->Highlight(Hex::AZUL);
	}
}
ArenaState::~ArenaState() {
	delete grid;
}

void ArenaState::Update(float dt) {
	//std::cout<<InputManager::GetInstance().GetMouseX()<<", "<<InputManager::GetInstance().GetMouseY()<<std::endl;

	//timerTurno.Update(dt);
	ap->SetText(MakeText("Ap: ", selectedUnit->ap));
	hp->SetText(MakeText("Hp: ", selectedUnit->hp));
	atk->SetText(MakeText("Atk: ", selectedUnit->atk));
	if (selectedUnit->Is("King"))
		atk->SetText(MakeText("Mana: ", static_cast<King*>(selectedUnit)->mana));

	//if(10000-timerTurno.Get() < 0){
	//	PassTurn();
	//}else{
	//	time->SetText(MakeText("Time: ", 1000-timerTurno.Get()));
	//}

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
	for (int i=0; i< grid->size(); i++) {
		if (grid->At(i).unit != NULL)
			grid->At(i).unit->Render();
	}
	bg2.Render(0, 404, 0);


	campo.Render(580,640,0);

	for (int i =0; i< objectArray.size(); i++) {
		if (objectArray[i].get()->Is("StillAnimation"))
			objectArray[i].get()->Render();
	}

	for(int i = turnLogic.indice; i < turnLogic.allUnits.size(); i++){
		turnLogic.allUnits[i]->card.Render(600+(i-(turnLogic.indice))*600/turnLogic.allUnits.size(), 650,0);

		if(turnLogic.allUnits[i]->owner->color == Player::BLUE){
			card_blue.Render(600+(i-(turnLogic.indice))*600/turnLogic.allUnits.size(),650,0);
		}else{
			card_red.Render(600+(i-(turnLogic.indice))*600/turnLogic.allUnits.size(),650,0);
		}
	}

	for(int i = 0; i < turnLogic.indice; i++){
		turnLogic.allUnits[i]->card.Render(600+(turnLogic.allUnits.size()-1-(turnLogic.indice-(i+1)))*600/turnLogic.allUnits.size(), 650,0);

		if(turnLogic.allUnits[i]->owner->color == Player::BLUE){
			card_blue.Render(600+(turnLogic.allUnits.size()-1-(turnLogic.indice-(i+1)))*600/turnLogic.allUnits.size(), 650,0);
		}else{
			card_red.Render(600+(turnLogic.allUnits.size()-1-(turnLogic.indice-(i+1)))*600/turnLogic.allUnits.size(), 650,0);
		}
	}

	first.Render(600,650,0);

	ap->Render(0,0);
	hp->Render(0,0);
	atk->Render(0,0);
	//time->Render(100,660);

	RenderUIArray();

}

void ArenaState::Pause(){}

void ArenaState::Resume(){}

void ArenaState::SelectedUnitAttack(){
	ArenaState::selectedUnit->ActionIntent(ArenaState::selectedUnit->Action::ATTACK);
}

void ArenaState::PassTurn(){
	ArenaState::selectedUnit->ActionIntent(ArenaState::selectedUnit->Action::PASS);
	//timerTurno.Restart();
}

string ArenaState::MakeText(string t1, int t2){
	char Result[5];
	string texto = t1;

	sprintf ( Result, "%d", t2 );
	texto.append(Result);

	return texto;
}
