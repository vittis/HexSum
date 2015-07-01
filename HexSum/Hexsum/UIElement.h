/*
 * UIElement.h
 *
 *  Created on: 12/06/2015
 *      Author: Isaac
 */

#ifndef HEXSUM_UIELEMENT_H_
#define HEXSUM_UIELEMENT_H_

#include "../Sprite.h"
#include "../GameObject.h"

class UIElement {
protected:
	Sprite sp;
	Rect box;
public:
	UIElement(float x, float y , string str);

	void SetSprite(std::string sp);
	Sprite GetSprite();

	float GetX();
	float GetY();
	float GetHeight();
	float GetWidth();

	void SetPos(float x, float y);
	virtual void SetScale(float scale);
	virtual void Update(float);
	virtual void Render();
	bool IsDead();
	void NotifyCollision(GameObject &other);
	bool Is(std::string);
};

#endif /* HEXSUM_UIELEMENT_H_ */
