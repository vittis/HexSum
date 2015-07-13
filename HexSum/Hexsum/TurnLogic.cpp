/*
 * TurnLogic.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: Vitor
 */
#include "TurnLogic.h"
#include <algorithm>
#include "ArenaState.h"

TurnLogic::TurnLogic() {
	indice=-1;
	currentTurn=0;
}
void TurnLogic::PassTurnToNextUnit() {
	currentTurn++;
	std::cout<<currentTurn<<std::endl;
	if (indice < allUnits.size()-1)
		indice++;
	else
		indice=0;
	ArenaState::selectedUnit = allUnits[indice];
	ArenaState::selectedUnit->BeginTurnSetup();
}
void TurnLogic::RemoveUnit(Unit* unit) {
	allUnits.erase(std::remove(allUnits.begin(), allUnits.end(), unit), allUnits.end());
}
