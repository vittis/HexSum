/*
 * Sound.h
 *
 *  Created on: 23/05/2015
 *      Author: Isaac
 */

#ifndef SOUND_H_
#define SOUND_H_

#include "SDL_Mixer.h"
#include <string>

class Sound {
private:
	Mix_Chunk* chunk;
	int channel;

public:
	Sound();
	Sound(std::string file);

	void Play(int);
	void Stop();
	void Open(std::string);
	bool IsOpen();
};

#endif /* SOUND_H_ */
