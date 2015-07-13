/*
 * TurnLogic.h
 *
 *  Created on: Jun 11, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_TURNLOGIC_H_
#define HEXSUM_TURNLOGIC_H_

#include <vector>
#include "Unit.h"

class TurnLogic {
public:
	TurnLogic();
	vector<Unit*> allUnits;
	int indice;
	int currentTurn;
	void PassTurnToNextUnit();
	void RemoveUnit(Unit* unit);

};



#endif /* HEXSUM_TURNLOGIC_H_ */
