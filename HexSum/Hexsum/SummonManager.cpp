/*
 * SummonManager.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: Vitor
 */

#include "SummonManager.h"

#include "ArenaState.h"
#include "../Game.h"
#include "Archer.h"
#include "Soldier.h"
#include "Cleric.h"
#include "Constants.h"

SummonManager::SummonManager(Unit* king) {
	this->king = king;
}
int SummonManager::GetCustoManaUnidade(int tipoUnidade) {
	if (tipoUnidade==0)
		return Constants::custoManaSoldier;
	else if (tipoUnidade==1)
		return Constants::custoManaCleric;
	else if (tipoUnidade == 2)
		return Constants::custoManaArcher;

	return -1;
}
int SummonManager::GetCustoAdicional(int tipoUnidade, Player *player) {
	int custoAdicional=0;
	string unidade;
	if (tipoUnidade==0)
		unidade="Soldier";
	else if (tipoUnidade==1)
		unidade="Cleric";
	else if (tipoUnidade==2)
		unidade="Archer";

	for (int i=0; i< ArenaState::turnLogic.allUnits.size(); i++) {
		if (ArenaState::turnLogic.allUnits[i]->Is(unidade) && (ArenaState::turnLogic.allUnits[i]->owner->color == player->color)) {
			custoAdicional++;
		}
	}
	return custoAdicional;
}
void SummonManager::SummonUnit(TipoUnidade tipoUnidade, Hex* hex, Player* player) {
	Unit* unit;
	switch (tipoUnidade) {
	case TipoUnidade::ARCHER:
		//if (static_cast<King*>(king)->mana >= Constants::custoManaArcher) {
			unit = new Archer(hex, player);
			Game::GetInstance()->GetCurrentState().AddObject(unit);
			ArenaState::turnLogic.allUnits.emplace_back(unit);
	//	}
		break;
	case TipoUnidade::SOLDIER:
	//	if (static_cast<King*>(king)->mana >= Constants::custoManaSoldier) {
			unit = new Soldier(hex, player);
			Game::GetInstance()->GetCurrentState().AddObject(unit);
			ArenaState::turnLogic.allUnits.emplace_back(unit);
	//	}
		break;
	case TipoUnidade::CLERIGO:
	//	if (static_cast<King*>(king)->mana >= Constants::custoManaCleric) {
			unit = new Cleric(hex, player);
			Game::GetInstance()->GetCurrentState().AddObject(unit);
			ArenaState::turnLogic.allUnits.emplace_back(unit);
	//	}
		break;
	}



}



