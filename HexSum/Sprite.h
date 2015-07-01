#ifndef SPRITE_H_
#define SPRITE_H_

#include <iostream>
#include "SDL_image.h"
#include "SDL.h"

using namespace std;

class Sprite {
	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;


		float timeElapsed;
		float frameTime = 1;

		bool flipped = false;

	public:
		int frameCount = 1;
		int rows = 1;
		int cols = 1;
		int currentFrame;
		float scaleX = 1;
		float scaleY = 1;

		Sprite();
		Sprite(string, int, float);
		Sprite(string, int, int, int, float);
		void Update(float dt);
		void Open(string);
		void SetClip(float,float,float,float);
		void Render(float, float, float);
		int GetWidth();
		int GetHeight();
		bool isOpen();
		virtual ~Sprite();

		void SetIndex(int rows, int cols);
		void SetFrame(int);
		void SetFrameCount(int);
		void SetFrameTime(float);

		void SetFlipped(bool);
		void SetScaleX(float);
		void SetScaleY(float);

};

#endif /* SPRITE_H_ */
