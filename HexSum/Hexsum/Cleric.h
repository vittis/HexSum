/*
 * Cleric.h
 *
 *  Created on: Jul 6, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_CLERIC_H_
#define HEXSUM_CLERIC_H_
#include "Unit.h"
class Cleric : public Unit{
public:
	Cleric(Hex *hex, Player* player);
	bool Is(string type);
	void Update(float dt);
	void PrepareSpecialAbility();
	void PerformSpecialAbility(Hex *hex);
	void ShowSummonRange();
};



#endif /* HEXSUM_CLERIC_H_ */
