/*
 * Music.cpp
 *
 *  Created on: 23/05/2015
 *      Author: Isaac
 */

#include "Music.h"
#include "Resources.h"

Music::Music():music(NULL) {
}

Music::Music(std::string file){
	Open(file);
}

void Music::Open(std::string file){
	music = Resources::GetMusic(file);
}


void Music::Play(int times){
	Mix_PlayMusic (music, times);
}

void Music::Stop(){
	Mix_FadeOutMusic (0);
}

bool Music::IsOpen(){
	return music != NULL;
}
