/*
 * SelectState.h
 *
 *  Created on: 11/07/2015
 *      Author: Thiago
 */

#ifndef HEXSUM_SELECTSTATE_H_
#define HEXSUM_SELECTSTATE_H_

#include "../State.h"
#include "../Sprite.h"
#include "../Text.h"
#include "../GameObject.h"
#include "../Color.h"
#include "Image.h"
#include "Button.h"
#include "ArenaState.h"
#include "StateData.h"

class SelectState: public State {
private:
	Sprite bg, campo1, campo2, campo3, campo4, rei1, rei2, rei3, rei4;
	Image cortina_fundo, cortina_esquerda, cortina_direita, sombra_cima, sombra_baixo;
	int xRei1, xRei2, xRei3, xRei4, yRei1, yRei2, yRei3, yRei4;
	int xCampo1, xCampo2, xCampo3, xCampo4, yCampo1, yCampo2, yCampo3, yCampo4;
	float escalaCampo1, escalaCampo2;
	static int vez, escolhaRei1, escolhaRei2, escolhaCampo;
	Rect boxRei1, boxRei2, boxRei3, boxRei4, boxCampo1, boxCampo2, boxCampo3, boxCampo4;
	static StateData *stateData;
public:
	SelectState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	void OnClick();
	void MoveCortina(float vel);
	int GetCampo();
	int GetRei1();
	int GetRei2();
	void HighlightRei();
	void HighlightCampo();
	static void NextState();
};

#endif /* HEXSUM_SELECTSTATE_H_ */