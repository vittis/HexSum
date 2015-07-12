/*
 * Player.h
 *
 *  Created on: Jun 11, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_PLAYER_H_
#define HEXSUM_PLAYER_H_

#include "../GameObject.h"

class Player {
public:
	enum Color{
		RED,
		BLUE,
		GREEN,
		PURPLE
	};
	Player(Color color);
	Color color;
	GameObject *king;
	void SetKing(GameObject* _king);



};



#endif /* HEXSUM_PLAYER_H_ */
