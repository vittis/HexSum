/*
 * Button.h
 *
 *  Created on: 12/06/2015
 *      Author: Isaac
 */

#ifndef HEXSUM_BUTTON_H_
#define HEXSUM_BUTTON_H_
#include "UIElement.h"
#include "../Sprite.h"
#include "SDL.h"


class Button : public UIElement{
private:
	Sprite spMouseOver;
	Sprite spMouseOut;
	void (*function)();

public:
	Button(int x, int y, string mouseOver, string mouseOut, void (*function)());
	void Update(float);
	void Render();
	void OnClick();
	void SetScale(float Scale);
};

#endif /* HEXSUM_BUTTON_H_ */
