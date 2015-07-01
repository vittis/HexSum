#include "Game.h"
#include "Sprite.h"
#include "Resources.h"

Sprite::Sprite(): width(0), height(0), currentFrame(0), timeElapsed(0){
	texture = NULL;
}

Sprite::Sprite(string file, int frameCount, float frameTime) : frameCount(frameCount), currentFrame(0), timeElapsed(0), frameTime(frameTime) {
	Open(file);
}


Sprite::Sprite(string file, int frameCount, int rows, int cols, float frameTime) : frameCount(frameCount), cols(cols),rows(rows), currentFrame(0), timeElapsed(0), frameTime(frameTime) {
	Open(file);
}

void Sprite::Update(float dt){
	timeElapsed+=dt;

	if(timeElapsed > frameTime){

		currentFrame++;

		if(currentFrame == frameCount){
			currentFrame = 0;
		}

		SetFrame(currentFrame);
		timeElapsed = 0;
	}

}

void Sprite::SetFrame(int frame){
	currentFrame = frame;

	float frameWidth = width/cols;
	float frameHeight = height/rows;
	if(rows == 1){
		SetClip((width/frameCount)*currentFrame,0, width/frameCount, height);
	}else{
		SetClip((currentFrame%cols)*frameWidth, (currentFrame/cols)*frameHeight, frameWidth, frameHeight);
	}

}

void Sprite::SetFrameCount(int frameCount){
	this->frameCount = frameCount;
}

void Sprite::SetFrameTime(float frameTime){
	this->frameTime = frameTime;
}

void Sprite::Open(string file){
		texture = Resources::GetImage(file);
		

		if(texture == NULL){
			cout <<  IMG_GetError() << endl;
		}else{
			SDL_QueryTexture ( texture , NULL , NULL , &width , &height);
		}

		if(rows == 1){
			SetClip(0,0, width/frameCount, height);
		}else{
			SetClip(0,0, width/cols, height/rows);
		}


}

void Sprite::SetClip(float x, float y, float w, float h){
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(float x, float y, float angle){
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = clipRect.w*scaleX;
	rect.h = clipRect.h*scaleY;
	
	if(!flipped){
		if(SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture, &clipRect, &rect, angle, NULL, SDL_FLIP_NONE) != 0)
			cout << SDL_GetError() << endl;
	}else{
		if(SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture, &clipRect, &rect, angle, NULL, SDL_FLIP_HORIZONTAL) != 0)
					cout << SDL_GetError() << endl;
	}
}

int Sprite::GetWidth(){
	if(rows == 1)
		return (width/frameCount)*scaleX;
	else
		return (width/cols)*scaleX;

}

int Sprite::GetHeight(){
	return (height/rows)*scaleY;
}

bool Sprite::isOpen(){
	if(texture == NULL)
		return false;
	else
		return true;
}

Sprite::~Sprite() {
}

void Sprite::SetIndex(int rows, int cols){
	this->rows = rows;
	this->cols = cols;
}


void Sprite::SetFlipped(bool flipped){
	this->flipped = flipped;
}

void Sprite::SetScaleX(float scale){
	scaleX = scale;
}

void Sprite::SetScaleY(float scale){
	scaleY = scale;
}
