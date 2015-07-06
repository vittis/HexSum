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

class SummonManager {
public:
	enum TipoUnidade {
		SOLDIER,
		CLERIGO,
		ARCHER
	};
	void SummonUnit(TipoUnidade tipoUnidade, Hex* hex, Player* player);

};


#endif /* HEXSUM_SUMMONMANAGER_H_ */
