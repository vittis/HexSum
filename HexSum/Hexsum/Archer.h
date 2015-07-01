/*
 * Archer.h
 *
 *  Created on: Jun 2, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_ARCHER_H_
#define HEXSUM_ARCHER_H_

#include "Unit.h"

class Archer : public Unit {
public:
	Archer(Hex *hex, Player* player);
	bool Is(string type);
	void BeginTurnSetup();
	void Update(float dt);
	void PrepareSpecialAbility();
	void PerformSpecialAbility(Hex *hex);
private:
	bool usedFocus;
};


#endif /* HEXSUM_ARCHER_H_ */
