/*
 * Color.h
 *
 *  Created on: 13/06/2015
 *      Author: Isaac
 */

#ifndef COLOR_H_
#define COLOR_H_

#include "SDL.h"

class Color {
public:
	static SDL_Color GetColor(int r, int g, int b, int a){
		SDL_Color color;
		color.a = a;
		color.r = r;
		color.g = g;
		color.b = b;

		return color;
	}
};

#endif /* COLOR_H_ */
