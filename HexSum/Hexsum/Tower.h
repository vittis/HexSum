/*
 * Tower.h
 *
 *  Created on: Jul 12, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_TOWER_H_
#define HEXSUM_TOWER_H_

#include "Hex.h"
#include "Player.h"
#include "../GameObject.h"
#include "../Sprite.h"

class Tower : public GameObject{
public:
	Tower(Hex* hex);
	void Update(float);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject &other);
	bool Is(std::string type);
	Hex* location;
	Player* owner;
	void BeCaptured(Player* player);
private:
	Sprite sp;
	Sprite bandeira;
	bool animating;
};



#endif /* HEXSUM_TOWER_H_ */
