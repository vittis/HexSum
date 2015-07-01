#ifndef HEXSUM_SELECTREISTATE_H_
#define HEXSUM_SELECTREISTATE_H_

#include "../State.h"
#include "../Sprite.h"
#include "../Text.h"
#include "../GameObject.h"
#include "../Color.h"
#include "Image.h"
#include "Button.h"
#include "SelectCampoState.h"
#include "StateData.h"

class SelectReiState: public State {
private:
	Sprite bg, rei1, rei2, rei3, rei4;
	Image cortina_fundo, cortina_esquerda, cortina_direita;
	static Text * text;
	int x1, x2, x3, x4, y1, y2, y3, y4;
	float scale1, scale2;
	static int vez, escolha1, escolha2;
	Rect box1, box2, box3, box4;
	static StateData *stateData;
public:
	SelectReiState();
	void Update(float dt);
	void Render();
	void Pause();
	void Resume();
	void OnClick();
	void HighlightRei();
	int GetRei1();
	int GetRei2();
	static void NextState();
};

#endif /* HEXSUM_SELECTREISTATE_H_ */
