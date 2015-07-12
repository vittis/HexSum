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
	static Player* player1;
	static Player* player2;
	static TurnLogic turnLogic;
	static int tipoCampo;

	static string GetPrefixo();
	static int summonSelecionado;
private:

	Sprite bg, bg2, bg3;

	Sprite timeLine;
	Sprite ampulheta;
	Sprite painel_esquerda;
	Sprite painel_direita;
	Sprite bandeira;

	Button *passButton;
	Button *attackButton;
	Button *moveButton;
	Button *spellButton;

	Button *soldierButton;
	Button *clericButton;
	Button *archerButton;


	Text* ap;
	Text* atk;
	Text* hp;
	Text* mana;
	//Text* time;
	//static Timer timerTurno;

	string MakeText(string, int);
	Timer timerAmpulheta;
	static bool passou;
	static void SelectedUnitAttack();
	static void PassTurn();
	static void SelectedUnitMove();
	static void SelectedUnitSpell();
	static void SelectArcher();
	static void SelectSoldier();
	static void SelectCleric();
};



#endif /* HEXSUM_ARENASTATE_H_ */
