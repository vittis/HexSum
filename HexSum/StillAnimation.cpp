/*
 * StillAnimation.cpp
 *
 *  Created on: 17/05/2015
 *      Author: Isaac
 */

#include "StillAnimation.h"

StillAnimation::StillAnimation(float x, float y, float rotation, Sprite sprite, float timeLimit, bool ends) : sp(sprite) ,timeLimit(timeLimit), oneTimeOnly(ends) {
	box.SetX(x-sp.GetWidth()/2);
	box.SetY(y-sp.GetHeight()/2);
	box.SetHeight(sp.GetHeight());
	box.SetWidth(sp.GetWidth());
	//sp.SetScaleY(1.5);
	//sp.SetScaleY(1.5);
	endTimer = Timer();
	//if (type == "death") {
	//	std::cout<<"qqq22"<<std::endl;
	//}
}


void StillAnimation::Update(float dt){
	endTimer.Update(dt);
	sp.Update(dt);
	std::cout<<"q"<<std::endl;
}

void StillAnimation::Render(){
	sp.Render(box.GetX() + Camera::pos.getX(), box.GetY() + Camera::pos.getY(), rotation);
}

bool StillAnimation::IsDead(){
	if(oneTimeOnly)
		return endTimer.Get() >= timeLimit;
	else
		return false;
}

void StillAnimation::NotifyCollision(GameObject &other){

}

bool StillAnimation::Is(string type){
	return type == "StillAnimation";
}


StillAnimation::~StillAnimation() {
}

