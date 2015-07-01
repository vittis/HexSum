/*
 * Farmer.h
 *
 *  Created on: Jun 8, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_SOLDIER_H_
#define HEXSUM_SOLDIER_H_

#include "Unit.h"

class Soldier : public Unit {
public:
	Soldier(Hex *hex, Player* player);
	void BeginTurnSetup();
	bool Is(std::string type);
};



#endif /* HEXSUM_SOLDIER_H_ */
