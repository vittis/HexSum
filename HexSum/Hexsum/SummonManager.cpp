/*
 * SummonManager.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: Vitor
 */

#include "SummonManager.h"

#include "Unit.h"
#include "ArenaState.h"
#include "../Game.h"
#include "Archer.h"
#include "Soldier.h"
#include "Cleric.h"


void SummonManager::SummonUnit(TipoUnidade tipoUnidade, Hex* hex, Player* player) {
	Unit* unit;
	switch (tipoUnidade) {
	case TipoUnidade::ARCHER:
		unit = new Archer(hex, player);
		Game::GetInstance()->GetCurrentState().AddObject(unit);
		ArenaState::turnLogic.allUnits.emplace_back(unit);
		break;
	case TipoUnidade::SOLDIER:
		unit = new Soldier(hex, player);
		Game::GetInstance()->GetCurrentState().AddObject(unit);
		ArenaState::turnLogic.allUnits.emplace_back(unit);
		break;
	case TipoUnidade::CLERIGO:
		unit = new Cleric(hex, player);
		Game::GetInstance()->GetCurrentState().AddObject(unit);
		ArenaState::turnLogic.allUnits.emplace_back(unit);
		break;
	}



}



