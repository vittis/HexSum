/*
 * SelectCampoState.h
 *
 *  Created on: 19/06/2015
 *      Author: Thiago
 */

#ifndef SELECTCAMPOSTATE_H_
#define SELECTCAMPOSTATE_H_

#include "../State.h"
#include "../Sprite.h"
#include "../Text.h"
#include "../GameObject.h"
#include "../Color.h"
#include "Image.h"
#include "Button.h"
#include "ArenaState.h"
#include "StateData.h"

class SelectCampoState : public State {
private:
	Sprite bg, campo1, campo2, campo3;
	Image cortina_fundo, cortina_esquerda, cortina_direita;
	static Text * textCampo;
	int x1, x2, x3, y1, y2, y3;
	float scale1, scale2;
	static int escolhaCampo;
	Rect box1, box2, box3;
	static StateData *stateData;
public:
	SelectCampoState(StateData stateData);
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	void OnClick();
	void HighlightCampo();
	int GetCampo();
	static void NextStateCampo();
};

#endif /* SELECTCAMPOSTATE_H_ */
