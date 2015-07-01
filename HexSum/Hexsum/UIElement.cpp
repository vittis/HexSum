/*
 * UIElement.cpp
 *
 *  Created on: 12/06/2015
 *      Author: Isaac
 */

#include "UIElement.h"

UIElement::UIElement(float x, float y, string str) : sp(str,1,0){
	box.SetX(x-sp.GetWidth()/2);
	box.SetY(y-sp.GetHeight()/2);
	box.SetHeight(sp.GetHeight());
	box.SetWidth(sp.GetWidth());
}

void UIElement::SetSprite(string str){
	sp.Open(str);
}

Sprite UIElement::GetSprite(){
	return sp;
}

float UIElement::GetX(){
	return box.GetX();
}

float UIElement::GetY(){
	return box.GetY();
}

float UIElement::GetWidth(){
	return box.GetWidth();
}

float UIElement::GetHeight(){
	return box.GetHeight();
}

void UIElement::SetPos(float x, float y){
	box.SetX(x);
	box.SetY(y);
}

void UIElement::SetScale(float scale){
	sp.SetScaleX(scale);
	sp.SetScaleY(scale);
}

void UIElement::Update(float dt){

}

void UIElement::Render(){
	sp.Render(box.GetX(), box.GetY(), 0);
}

bool UIElement::IsDead(){
	return false;
}

bool UIElement::Is(string str){
	return str == "UIElement";
}

void UIElement::NotifyCollision(GameObject& go){

}
