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


void SummonManager::SummonUnit(TipoUnidade tipoUnidade, Hex* hex, Player* player) {

	/*switch (tipoUnidade) {
	case TipoUnidade::ARCHER:
		Unit* archer = new Archer(hex, player);
		Game::GetInstance()->GetCurrentState().AddObject(archer);
		ArenaState::turnLogic.allUnits.emplace_back(archer);
		break;
	case TipoUnidade::SOLDIER:
		Unit* archer = new Soldier(hex, player);
		Game::GetInstance()->GetCurrentState().AddObject(archer);
		ArenaState::turnLogic.allUnits.emplace_back(archer);


	}


*/



}



