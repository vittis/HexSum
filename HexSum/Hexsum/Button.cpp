/*
 * Button.cpp
 *
 *  Created on: 12/06/2015
 *      Author: Isaac
 */

#include "Button.h"
#include "../InputManager.h"

Button::Button(int x, int y, string mouseOver, string mouseOut, void (*f)()) :  UIElement(x,y,mouseOut), spMouseOver(mouseOver,1,0), spMouseOut(mouseOut,1,0) {
	function = f;
}

void Button::Update(float dt){

		if (this->box.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())){
				sp = spMouseOver;
		}else{
				sp = spMouseOut;
		}

	OnClick();
}

void Button::Render(){
	sp.Render(box.GetX(), box.GetY(), 0);
}


void Button::OnClick(){

	if (InputManager::GetInstance().MousePress(LEFT_MOUSE_BUTTON)) {
		if (this->box.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())){
			if(function != NULL)
				(*function)();
		}
	}
}

void Button::SetScale(float Scale){
	spMouseOut.SetScaleX(Scale);
	spMouseOut.SetScaleY(Scale);
	spMouseOver.SetScaleX(Scale);
	spMouseOver.SetScaleY(Scale);

	box.SetHeight(box.h*Scale);
	box.SetWidth(box.w*Scale);
}
