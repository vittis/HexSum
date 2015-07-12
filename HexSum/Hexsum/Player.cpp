/*
 * Player.cpp
 *
 *  Created on: Jun 11, 2015
 *      Author: Vitor
 */

#include "Player.h"

Player::Player(Color color) {
	king= NULL;
	this->color = color;
}
void Player::SetKing(GameObject* _king) {
	king = _king;
}

