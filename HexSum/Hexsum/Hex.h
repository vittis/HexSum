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
	bool isTower;
	Point center;
	enum Cor {
		VERMELHO,
		AZUL,
		VERDE,
		ROXO,
		BEGE,
		AMARELO,
		PADRAO,
		CIANO,
		LARANJA,
		VERDECLARO
	};
	void Highlight(Cor cor);
	void UnHighlight();
	void SetOriginalHeight(int _altura);
	Cor originalColor;
	Cor color;
	Rect box;

	GameObject *unit;
	GameObject *tower;
	float height;
	float originalHeight;
	Sprite sp;
private:
	const int q, r;

};



#endif /* HEXSUM_HEX_H_ */
