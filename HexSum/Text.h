/*
 * Text.h
 *
 *  Created on: 24/05/2015
 *      Author: Isaac
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "string"
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "Geometry.h"

enum TextStyle{SOLID, SHADED, BLENDED};

class Text {

private:
	void RemakeTexture();
	TTF_Font* font;
	SDL_Texture* texture;
	std::string text ;
	TextStyle style;
	int fontSize;
	SDL_Color color;


public:
	SDL_Rect box ;

	Text (std::string fontFile, int fontSize, TextStyle style, std::string text,SDL_Color color, int x, int y);
	~Text();
	void Render(int cameraX, int cameraY);
	void SetPos(int x, int y, bool centerX, bool centerY);
	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontSize(int fontSize);
	std::string GetText();
};

#endif /* TEXT_H_ */
