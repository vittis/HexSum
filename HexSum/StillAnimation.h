
#ifndef STILLANIMATION_H_
#define STILLANIMATION_H_

#include "Sprite.h"
#include <string>
#include "Timer.h"
#include "GameObject.h"
#include "Camera.h"

class StillAnimation : public GameObject {
private:
	Timer endTimer;

	Sprite sp;
	float timeLimit;
	bool oneTimeOnly;

public:
	StillAnimation(float, float, float, Sprite, float, bool);
	void Update(float dt);
	void Render();
	bool isDead();
	void NotifyCollision(GameObject &other );
	bool Is(string);

	virtual ~StillAnimation();
};

#endif /* STILLANIMATION_H_ */
