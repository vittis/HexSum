/*
 * Sound.cpp
 *
 *  Created on: 23/05/2015
 *      Author: Isaac
 */

#include "Sound.h"
#include "Resources.h"

Sound::Sound():chunk(NULL){
}

Sound::Sound(std::string file){
	Open(file);
}

void Sound::Open(std::string file){
	chunk = Resources::GetSound(file);
}


void Sound::Play(int times){
	channel = Mix_PlayChannel (-1, chunk, times);
}

void Sound::Stop(){
	Mix_HaltChannel (channel);
}

bool Sound::IsOpen(){
	return chunk != NULL;
}
