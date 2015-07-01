/*
 * Camera.cpp
 *
 *  Created on: 24/04/2015
 *      Author: Isaac
 */

#include "Camera.h"

Point Camera::pos(0,0);
Point Camera::speed(1000,1000);
GameObject* Camera::focus = NULL;

void Camera::Follow(GameObject* newFocus){
	focus = newFocus;
}

void Camera::Unfollow(){
	focus = NULL;
}
// mexer no update
void Camera::Update(float dt){

	if(focus != NULL){
		pos.setX(512 - focus->box.GetX() - focus->box.GetWidth()/2);
		pos.setY(300 - focus->box.GetY() - focus->box.GetHeight()/2);
	}

/*	if(InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)){
		pos.setY(pos.getY()+speed.getY()*dt);
	}

	if(InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)){
			pos.setY(pos.getY()-speed.getY()*dt);
		}

	if(InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
			pos.setX(pos.getX()-speed.getX()*dt);
	}

	if(InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)){
			pos.setX(pos.getX()+speed.getX()*dt);
		}*/
}
