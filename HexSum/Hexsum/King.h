/*
 * King.h
 *
 *  Created on: Jun 23, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_KING_H_
#define HEXSUM_KING_H_

#include "Unit.h"

class King : public Unit {
public:
	King(Hex *hex, Player* player, int initialMana);
	void BeginTurnSetup();
	bool Is(std::string type);
	void Update(float dt);
	int mana;
	void PrepareSpecialAbility();
	void PerformSpecialAbility(Hex *hex);
	void ShowSummonRange();
};

#endif /* HEXSUM_KING_H_ */
