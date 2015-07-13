/*
 * ArenaState.h
 *
 *  Created on: Jun 1, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_ARENASTATE_H_
#define HEXSUM_ARENASTATE_H_

#include "../State.h"
#include "../Sprite.h"
#include "../Text.h"
#include "HexGrid.h"
#include "Unit.h"
#include "../Color.h"
#include "Player.h"
#include "TurnLogic.h"
#include "Button.h"
#include "../Timer.h"
#include "King.h"
#include "StateData.h"
#include "Tower.h"
#include "../Music.h"

class ArenaState : public State {
public:
	ArenaState(int n, int m, StateData stateData);
	~ArenaState();
	void Update(float dt);
	void Render();
	static HexGrid* grid;

	void Pause();
	void Resume();
	void Setup();
	static Unit *selectedUnit;
	static Unit *selectedInfoUnit;
	static Player* player1;
	static Player* player2;
	static TurnLogic turnLogic;
	static int tipoCampo;

	static string GetPrefixo();
	static int summonSelecionado;
	static bool pause;
	static bool estadoRei;
	static bool passou;
	static vector<Tower*> towers;
private:
	Music musicArena;
	Sprite bg, bg2, bg3;
	vector<Sprite> hpBar;
	vector<Sprite> manaBar;
	vector<Sprite> manaInfoBar;
	vector<Sprite> hpBarInfo;
	Sprite timeLine;
	Sprite ampulheta;
	Sprite painel_esquerda;
	Sprite painel_direita;
	Sprite bandeira;
	Sprite bandeiraInfo;
	Sprite borda;

	Button *passButton;
	Button *attackButton;
	Button *moveButton;
	Button *spellButton;

	Button *soldierButton;
	Button *clericButton;
	Button *archerButton;

	Text* pauseText;
	Text* apInfo;
	Text* atkInfo;

	Text* ap;
	Text* atk;
	//Text* time;
	//static Timer timerTurno;

	string MakeText(string, int);
	Timer timerAmpulheta;
	static void SelectedUnitAttack();
	static void PassTurn();
	static void SelectedUnitMove();
	static void SelectedUnitSpell();
	static void SelectArcher();
	static void SelectSoldier();
	static void SelectCleric();
	static void MenuButton();
	static void PauseButton();
};



#endif /* HEXSUM_ARENASTATE_H_ */
