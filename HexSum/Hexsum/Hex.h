/*
 * Hex.h
 *
 *  Created on: May 31, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_HEX_H_
#define HEXSUM_HEX_H_

#include "../Sprite.h"
#include "../Geometry.h"
#include <vector>
#include "../GameObject.h"

class Hex {
public:
	Hex(int q, int r);
	int GetQ();
	int GetR();
	int GetS();
	void Render();
	void Update();

	bool operator == (const Hex& a);
	bool operator != (const Hex& a);
	bool isEmpty;
	Point center;
	enum Cor {
		PADRAO,
		AMARELO,
		VERDE,
		VERMELHO,
		BEGE,
		AZUL
	};
	void Highlight(Cor cor);
	void UnHighlight();
	void SetOriginalHeight(int _altura);
	Cor originalColor;
	Cor color;
	Rect box;

	GameObject *unit;
	float height;
	float originalHeight;
private:
	const int q, r;
	Sprite sp;
};



#endif /* HEXSUM_HEX_H_ */
