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

SummonManager::SummonManager(Unit* king) {
	this->king = king;
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



