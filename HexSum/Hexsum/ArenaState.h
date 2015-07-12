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

private:

	Sprite bg, bg2, bg3;
	Sprite card_blue, card_red;
	Sprite first;
	Sprite campo;

	Text* ap;
	Text* atk;
	Text* hp;
	Text* mana;
	//Text* time;
	//static Timer timerTurno;

	string MakeText(string, int);
	static void SelectedUnitAttack();
	static void PassTurn();

};



#endif /* HEXSUM_ARENASTATE_H_ */
