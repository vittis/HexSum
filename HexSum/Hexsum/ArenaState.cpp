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
Unit* ArenaState::selectedInfoUnit = NULL;
Unit* ArenaState::selectedUnit = NULL;
Player* ArenaState::player1 = NULL;
Player* ArenaState::player2 = NULL;
TurnLogic ArenaState::turnLogic;
int ArenaState::tipoCampo=-1;
bool ArenaState::passou = false;
int ArenaState::summonSelecionado=0;
bool ArenaState::pause = false;
bool ArenaState::estadoRei = false;
bool ArenaState::muted = false;
bool ArenaState::help = false;
vector<Tower*> ArenaState::towers;

ArenaState::ArenaState(int n, int m, StateData stateData) {
	tipoCampo = (int)stateData.campo;
	player1 = new Player(static_cast<Player::Color>((int)stateData.rei1));
	player2 = new Player(static_cast<Player::Color>((int)stateData.rei2));

	timerAmpulheta = Timer();

	for(int i =0; i < 20; i++){
		cristal.push_back(Sprite("img/Main UI cortada/HP_MP/mana.png", 1,0));
		hpBar.push_back(Sprite("img/Main UI cortada/HP_MP/hp.png", 1,0));
		hpBarInfo.push_back(Sprite("img/Main UI cortada/HP_MP/hp.png", 1,0));
	}

	borda = Sprite("img/Main UI cortada/Fotos/borda.png", 1,0);
	timeLine = Sprite("img/Main UI cortada/Timeline/timeline.png", 1,0);
	ampulheta = Sprite("img/Main UI cortada/Timeline/hourglass_anim.png", 10, 0);
	painel_esquerda = Sprite("img/Main UI cortada/Card/card_alt.png", 1,0);
	painel_esquerda.SetFlipped(true);
	painel_direita = Sprite("img/Main UI cortada/Card/card_alt.png", 1,0);
	bandeira = Sprite("img/Main UI cortada/Card/bandeira_red.png", 1,0);
	bandeiraInfo = Sprite("img/Main UI cortada/Card/bandeira_red.png", 1,0);
	bandeiraInfo.SetFlipped(true);

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
		bg.Open("img/"+GetPrefixo()+"_fundo.png");
		break;
	}

	muteButton = new Button(127, 114, "img/Main UI cortada/Botoes/sound_button_hover.png","img/Main UI cortada/Botoes/sound_button.png",  &MuteButton);
	helpButton = new Button(196, 114, "img/Main UI cortada/Botoes/help_button_hover.png","img/Main UI cortada/Botoes/help_button.png",  &HelpButton);
	sairButton = new Button(928+22, 57+21, "img/Main UI cortada/Botoes/botao_sairhover.png", "img/Main UI cortada/Botoes/botao_sair.png", &HelpButton);
	AddUIElement(new Button(125, 51, "img/Main UI cortada/Botoes/menu_button_hover.png","img/Main UI cortada/Botoes/menu_button.png",  &MenuButton)) ;
	AddUIElement(new Button(50, 114, "img/Main UI cortada/Botoes/pause_button_hover.png","img/Main UI cortada/Botoes/pause_button.png",  &PauseButton)) ;
	AddUIElement(muteButton) ;
	AddUIElement(helpButton) ;

	grid = new HexGrid(n, m);

	Unit* king = new King(&grid->At(0, 6), player1, Constants::manaInicial);
	AddObject(king);
	turnLogic.allUnits.emplace_back(king);

	Unit* king2 = new King(&grid->At(0, 5), player2, Constants::manaInicial);
	AddObject(king2);
	turnLogic.allUnits.emplace_back(king2);

	attackButton = new Button(514+45, 656+44, "img/Main UI cortada/Botoes/attack_hover.png", "img/Main UI cortada/Botoes/attack.png", &SelectedUnitAttack);
	moveButton = new Button(593+45, 609+44, "img/Main UI cortada/Botoes/move_hover.png", "img/Main UI cortada/Botoes/move.png", &SelectedUnitMove);
	spellButton = new Button(674+45, 656+44, "img/Main UI cortada/Botoes/spell_hover.png", "img/Main UI cortada/Botoes/spell.png", &SelectedUnitSpell);
	passButton = new Button(589+50, 701+22, "img/Main UI cortada/Botoes/pass_cimahover.png", "img/Main UI cortada/Botoes/pass_cima.png", &PassTurn);

	archerButton = new Button(906, 668, "img/Main UI cortada/Fotos/archer.png", "img/Main UI cortada/Fotos/archer.png", &SelectArcher);
	soldierButton = new Button(1045, 668, "img/Main UI cortada/Fotos/soldier.png", "img/Main UI cortada/Fotos/soldier.png", &SelectSoldier);
	clericButton = new Button(1177, 668, "img/Main UI cortada/Fotos/cleric.png", "img/Main UI cortada/Fotos/cleric.png", &SelectCleric);

	AddUIElement(attackButton);
	AddUIElement(passButton);
	AddUIElement(moveButton);
	AddUIElement(spellButton);

	Setup();
	turnLogic.PassTurnToNextUnit();

	ap = new Text("font/mask.ttf", 26, TextStyle::BLENDED, " ", Color::GetColor(0,0,0,0), 230, 645);
	atk = new Text("font/mask.ttf", 26, TextStyle::BLENDED, " ", Color::GetColor(0,0,0,0), 230, 675);
	apInfo = new Text("font/mask.ttf", 26, TextStyle::BLENDED, " ", Color::GetColor(0,0,0,0), 996, 645);
	atkInfo = new Text("font/mask.ttf", 26, TextStyle::BLENDED, " ", Color::GetColor(0,0,0,0), 996, 675);
	pauseText = new Text("font/mask.ttf", 100, TextStyle::BLENDED, "Paused", Color::GetColor(0,0,0,0), 487, 330);

	manas.push_back(new Text("font/mask.ttf", 18, TextStyle::BLENDED, MakeText("",Constants::custoManaArcher), Color::GetColor(0,0,0,0), 944, 698));
	manas.push_back(new Text("font/mask.ttf", 18, TextStyle::BLENDED, MakeText("",Constants::custoManaSoldier), Color::GetColor(0,0,0,0), 1082,698));
	manas.push_back(new Text("font/mask.ttf", 18, TextStyle::BLENDED, MakeText("",Constants::custoManaCleric), Color::GetColor(0,0,0,0), 1216, 698));
	manas.push_back(new Text("font/mask.ttf", 18, TextStyle::BLENDED, " ", Color::GetColor(0,0,0,0), 154, 698));
	manas.push_back(new Text("font/mask.ttf", 18, TextStyle::BLENDED, " ", Color::GetColor(0,0,0,0), 1123, 698));

	musicArena.Open("music/"+GetPrefixo()+"_musica.mp3");
	musicArena.Play(-1);
	eventTrigger=false;
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
	for (int i=0; i< (int) grid->hex_directions.size(); i++) {
		grid->GetNeighbor(grid->At(0,0), i).SetOriginalHeight(-15);
		grid->GetNeighbor(grid->At(0,0), i).isEmpty=false;
	}
//	AddObject(new Tower(&grid->At(0,0)));

	grid->At(grid->m/2,grid->m/2).Highlight(Hex::Cor::BEGE);
	grid->At(grid->m/2,grid->m/2).originalColor = Hex::Cor::BEGE;
	Tower* tower1 = new Tower(&grid->At(grid->m/2,grid->m/2));
	towers.emplace_back(tower1);
	AddObject(tower1);

	grid->At(-grid->m/2,-grid->m/2).Highlight(Hex::Cor::BEGE);
	grid->At(-grid->m/2,-grid->m/2).originalColor = Hex::Cor::BEGE;
	Tower* tower2 = new Tower(&grid->At(-grid->m/2,-grid->m/2));
	towers.emplace_back(tower2);
	AddObject(tower2);


	grid->At(-1*(grid->n/2 + 1),grid->m).Highlight(Hex::Cor::BEGE);
	grid->At(-1*(grid->n/2 + 1),grid->m).originalColor = Hex::Cor::BEGE;
	Tower* tower3 = new Tower(&grid->At(-1*(grid->n/2 + 1),grid->m));
	towers.emplace_back(tower3);
	AddObject(tower3);


	grid->At((grid->n/2 + 1),-grid->m).Highlight(Hex::Cor::BEGE);
	grid->At((grid->n/2 + 1),-grid->m).originalColor = Hex::Cor::BEGE;
	Tower* tower4 = new Tower(&grid->At((grid->n/2 + 1),-grid->m));
	towers.emplace_back(tower4);
	AddObject(tower4);

}
ArenaState::~ArenaState() {
}

void ArenaState::Update(float dt) {
	if(turnLogic.currentTurn >= 15 && !eventTrigger) {
		eventTrigger=true;
		for (int i=0; i < HexGrid::hex_directions.size(); i++) {
			ArenaState::grid->GetNeighbor(grid->At(0,0), i).height=0;
			ArenaState::grid->GetNeighbor(grid->At(0,0), i).originalHeight=0;
			ArenaState::grid->GetNeighbor(grid->At(0,0), i).isEmpty=true;
			Tower* tower = new Tower(&grid->At(0,0));
			towers.emplace_back(tower);
			AddObject(tower);
		}

	}


	manas[0]->SetText(MakeText("",Constants::custoManaArcher+static_cast<King*>(selectedUnit->owner->king)->summonManager->GetCustoAdicional(2, selectedUnit->owner)));
	manas[1]->SetText(MakeText("",Constants::custoManaSoldier+static_cast<King*>(selectedUnit->owner->king)->summonManager->GetCustoAdicional(0, selectedUnit->owner)));
	manas[2]->SetText(MakeText("",Constants::custoManaCleric+static_cast<King*>(selectedUnit->owner->king)->summonManager->GetCustoAdicional(1, selectedUnit->owner)));


	if(muted){
		musicArena.SetVolume(0);
		muteButton->SetSP("img/Main UI cortada/Botoes/mute_button_hover.png","img/Main UI cortada/Botoes/mute_button.png");
	}else{
		muteButton->SetSP("img/Main UI cortada/Botoes/sound_button_hover.png","img/Main UI cortada/Botoes/sound_button.png");
		musicArena.SetVolume(100);
	}

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


	if(selectedInfoUnit != NULL && selectedInfoUnit != selectedUnit){
		apInfo->SetText(MakeText("Ap: ", selectedInfoUnit->ap));
		atkInfo->SetText(MakeText("Atk: ", selectedInfoUnit->atk));
		if(selectedInfoUnit->Is("King"))
			manas[4]->SetText(MakeText("",  static_cast<King*>(selectedInfoUnit)->mana));

	}

	ap->SetText(MakeText("Ap: ", selectedUnit->ap));
	atk->SetText(MakeText("Atk: ", selectedUnit->atk));

	if(selectedUnit->Is("King")){
		manas[3]->SetText(MakeText("",  static_cast<King*>(selectedUnit)->mana));
	}

	if(selectedUnit->owner->color == Player::RED){
		bandeira.Open("img/Main UI cortada/Card/bandeira_red.png");
	}else if(selectedUnit->owner->color == Player::BLUE){
		bandeira.Open("img/Main UI cortada/Card/bandeira_blue.png");
	}else if(selectedUnit->owner->color == Player::GREEN){
		bandeira.Open("img/Main UI cortada/Card/bandeira_green.png");
	}else if(selectedUnit->owner->color == Player::PURPLE){
		bandeira.Open("img/Main UI cortada/Card/bandeira_purple.png");
	}

	if(ArenaState::selectedInfoUnit != NULL){
		if(ArenaState::selectedInfoUnit->owner->color == Player::RED){
			bandeiraInfo.Open("img/Main UI cortada/Card/bandeira_red.png");
		}else if(ArenaState::selectedInfoUnit->owner->color == Player::BLUE){
			bandeiraInfo.Open("img/Main UI cortada/Card/bandeira_blue.png");
		}else if(ArenaState::selectedInfoUnit->owner->color == Player::GREEN){
			bandeiraInfo.Open("img/Main UI cortada/Card/bandeira_green.png");
		}else if(ArenaState::selectedInfoUnit->owner->color == Player::PURPLE){
			bandeiraInfo.Open("img/Main UI cortada/Card/bandeira_purple.png");
		}
	}

	if(InputManager::GetInstance().MousePress(1)){
			for(int i =0; i < (int) turnLogic.allUnits.size(); i++){
				if (turnLogic.allUnits[i]->location->box.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
					if(selectedUnit != NULL){
						if(selectedUnit != turnLogic.allUnits[i]){
								ArenaState::selectedInfoUnit = turnLogic.allUnits[i];
								ArenaState::estadoRei = true;
						}
					}
				}
			}
		}

	clericButton->Update(dt);
	soldierButton->Update(dt);
	archerButton->Update(dt);

	sairButton->Update(dt);

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

	for(int i = turnLogic.indice; i < (int) turnLogic.allUnits.size(); i++){
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

	for (int i =0; i < (int) objectArray.size(); i++) {
		if (objectArray[i].get()->Is("StillAnimation") )
			objectArray[i].get()->Render();
	}

	ampulheta.Render(300,21,0);
	painel_direita.Render(735,600,0);
	painel_esquerda.Render(0,600,0);
	bandeira.Render(315,585,0);

	selectedUnit->card.Render(70,625,0);

	ap->Render(0,0);
	atk->Render(0,0);


	RenderUIArray();

	if(selectedUnit->Is("King")){
		if(estadoRei){
			if(ArenaState::selectedInfoUnit != NULL && ArenaState::selectedInfoUnit != selectedUnit){
				bandeiraInfo.Render(840,585,0);
				ArenaState::selectedInfoUnit->card.Render(1122,628,0);
				apInfo->Render(0,0);
				atkInfo->Render(0,0);

				for(int i=0; i < ArenaState::selectedInfoUnit->hp;i++){
					hpBarInfo[i].Render(1220,708-i*13,0);
				}

				if(ArenaState::selectedInfoUnit->Is("King")){
					cristal[4].Render(1116,690,0);
					manas[4]->Render(0,0);
				}

			}
		}else{

			archerButton->Render();
			clericButton->Render();
			soldierButton->Render();

			switch(ArenaState::summonSelecionado){
				case 0: borda.Render(1045-47, 668-47, 0);
					break;
				case 1: borda.Render(1177-47, 668-47,0);
					break;
				case 2: borda.Render(906-47, 668-47,0);
					break;
			}
			cristal[0].Render(936,690,0);
			cristal[1].Render(1074,690,0);
			cristal[2].Render(1208,690,0);
			manas[0]->Render(0,0);
			manas[1]->Render(0,0);
			manas[2]->Render(0,0);
		}
	}else{
		if(ArenaState::selectedInfoUnit != NULL && ArenaState::selectedInfoUnit != selectedUnit){
			bandeiraInfo.Render(840,585,0);
			ArenaState::selectedInfoUnit->card.Render(1122,628,0);
			apInfo->Render(0,0);
			atkInfo->Render(0,0);

			for(int i=0; i < ArenaState::selectedInfoUnit->hp;i++){
				hpBarInfo[i].Render(1220,708-i*13,0);
			}

			if(ArenaState::selectedInfoUnit->Is("King")){
				cristal[4].Render(1116,690,0);
				manas[4]->Render(0,0);
			}
		}

	}

	if(ArenaState::pause){
		pauseText->Render(0,0);
	}

	if(ArenaState::help){
		Sprite("img/Main UI cortada/Help/tela_help.png",1,0).Render(202,24,0);
		sairButton->Render();
	}


	for(int i=0; i < selectedUnit->hp;i++){
		hpBar[i].Render(44,708-i*13,0);
	}

	if(ArenaState::selectedUnit->Is("King")){
		cristal[3].Render(147,690,0);
		manas[3]->Render(0,0);
	}
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

		if(selectedUnit->Is("King"))
			estadoRei = false;
}


void ArenaState::PassTurn(){
	ArenaState::selectedUnit->ActionIntent(ArenaState::selectedUnit->Action::PASS);
}

void ArenaState::MenuButton(){
	Game::GetInstance()->Push(new MenuState());

	ArenaState::muted = false;
	ArenaState::help = false;
	ArenaState::estadoRei = false;
	ArenaState::pause = false;
	ArenaState::passou = false;
	ArenaState::summonSelecionado=0;
	ArenaState::selectedInfoUnit = NULL;
	turnLogic.allUnits.clear();

	for(int i=0; i < (int) towers.size(); i++)
		towers[i]->owner = NULL;

}

void ArenaState::PauseButton(){
	if(!help)
		pause = !pause;
}

void ArenaState::MuteButton(){
	muted = !muted;
}

void ArenaState::HelpButton(){
	if(!ArenaState::pause)
		help = !help;
}


string ArenaState::MakeText(string t1, int t2){
	char Result[5];
	string texto = t1;

	sprintf ( Result, "%d", t2 );
	texto.append(Result);

	return texto;
}
