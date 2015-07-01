/*
 * MenuState.h
 *
 *  Created on: 12/06/2015
 *      Author: Isaac
 */

#ifndef HEXSUM_MENUSTATE_H_
#define HEXSUM_MENUSTATE_H_
#include "../State.h"
#include "SelectReiState.h"
#include "Image.h"
#include "Button.h"
#include "../Sprite.h"

class MenuState : public State {
private:
	Sprite bg;

	static void Printa();

public:
	MenuState();

	void Update(float dt);
	void Render();
	void Pause();
	void Resume();

};

#endif /* HEXSUM_MENUSTATE_H_ */
