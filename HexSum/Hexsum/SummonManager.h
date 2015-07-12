/*
 * SummonManager.h
 *
 *  Created on: Jul 3, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_SUMMONMANAGER_H_
#define HEXSUM_SUMMONMANAGER_H_

#include "Hex.h"
#include "Player.h"
#include "Unit.h"

class SummonManager {
public:
	enum TipoUnidade {
		SOLDIER,
		CLERIGO,
		ARCHER
	};
	SummonManager(Unit* king);
	void SummonUnit(TipoUnidade tipoUnidade, Hex* hex, Player* player);
	int GetCustoManaUnidade(int tipoUnidade);
private:
	Unit* king;
};


#endif /* HEXSUM_SUMMONMANAGER_H_ */
