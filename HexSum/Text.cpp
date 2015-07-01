#include "Text.h"
#include "Resources.h"
#include "Game.h"
#include "Color.h"

Text::Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x, int y){
	this->fontSize = fontSize;
	this->style = style;
	this->text = text;
    this->font = Resources::GetFont(fontFile, fontSize);
    this->texture = NULL;
    this->color = color;
    if(font != NULL){
    	RemakeTexture();
    }
    box.x = x;
    box.y = y;
}

Text::~Text(){
	if(texture != NULL)
		SDL_DestroyTexture(texture);
}

void Text::RemakeTexture(){
	if(texture != NULL)
		SDL_DestroyTexture(texture);
	SDL_Surface* aux;

	switch(style){
	case SOLID:
		aux = TTF_RenderText_Solid(font, text.c_str(), color);
		break;
	case SHADED:
		aux = TTF_RenderText_Shaded(font, text.c_str(), color, Color::GetColor(0,0,0,0));
		break;
	case BLENDED:
		aux = TTF_RenderText_Blended(font, text.c_str(), color);
	    break;
	}

	texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(), aux);
	SDL_FreeSurface(aux);

	int w, h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	box.w = w;
	box.h = h;

}

void Text::Render(int cameraX, int cameraY){
	if(texture != NULL){
		SDL_Rect pos, rect;
		pos.x = box.x - cameraX;
		pos.y = box.y - cameraY;
		pos.w = box.w;
		pos.h = box.h;

		rect.x = 0;
		rect.y = 0;
		rect.w = box.w;
		rect.h = box.h;

		SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture, &rect, &pos);
	}
}



void Text::SetPos(int x, int y, bool centerX, bool centerY){
	if(centerX)
		box.x = x - box.w/2;
	else
		box.x = x;
	if(centerY)
		box.y = y - box.h/2;
	else
		box.y = y;
}

void Text::SetColor(SDL_Color color){
	this->color = color;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize){
	this->fontSize = fontSize;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style){
	this->style = style;
	RemakeTexture();
}

void Text::SetText(std::string text){
	this->text = text;
	RemakeTexture();
}
