/*
 * Player.h
 *
 *  Created on: Jun 11, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_PLAYER_H_
#define HEXSUM_PLAYER_H_

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
};



#endif /* HEXSUM_PLAYER_H_ */
