/*
 * Music.h
 *
 *  Created on: 23/05/2015
 *      Author: Isaac
 */

#ifndef MUSIC_H_
#define MUSIC_H_

#include "SDL_mixer.h"
#include <string>


class Music {
private:
	Mix_Music* music;
public:
	Music();
	Music(std::string file);

	void Play(int);
	void Stop();
	void Open(std::string);
	bool IsOpen();
	void SetVolume(int);
};

#endif /* MUSIC_H_ */
