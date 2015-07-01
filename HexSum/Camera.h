/*
 * Camera.h
 *
 *  Created on: 24/04/2015
 *      Author: Isaac
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "GameObject.h"
#include "InputManager.h"
#include "Geometry.h"
#include <iostream>

class Camera {

private:
	static GameObject* focus;

public:

	static Point pos;
	static Point speed;
	static void Follow(GameObject*);
	static void Unfollow();
	static void Update(float);

};

#endif /* CAMERA_H_ */
