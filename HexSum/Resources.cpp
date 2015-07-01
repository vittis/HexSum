/*
 * Resources.cpp
 *
 *  Created on: 15/04/2015
 *      Author: Isaac
 */

#include "Resources.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;
unordered_map<string, TTF_Font*> Resources::fontTable;


TTF_Font* Resources::GetFont(string file, int ptsize){
	unordered_map<string, TTF_Font*>::iterator i = fontTable.find(file);

	if(i != fontTable.end()){
		return i->second;
	}else{
		TTF_Font* font = TTF_OpenFont (file.c_str(), ptsize);
		file+=ptsize;
		fontTable.emplace(file, font);
		return font;
	}
}

SDL_Texture* Resources::GetImage(string file){
	unordered_map<string, SDL_Texture*>::iterator i = imageTable.find(file);

	if(i != imageTable.end()){
		return i->second;
	}else{
		SDL_Texture* texture = IMG_LoadTexture (Game::GetInstance()->GetRenderer(), file.c_str());
		imageTable.emplace(file, texture);
		return texture;
	}

}

Mix_Music* Resources::GetMusic(string file){
	unordered_map<string, Mix_Music*>::iterator i = musicTable.find(file);

	if(i != musicTable.end()){
		return i->second;
	}else{
		Mix_Music* music = Mix_LoadMUS (file.c_str());
		musicTable.emplace(file, music);
		return music;
	}
}

Mix_Chunk* Resources::GetSound(string file){
	unordered_map<string, Mix_Chunk*>::iterator i = soundTable.find(file);

	if(i != soundTable.end()){
		return i->second;
	}else{
		Mix_Chunk* sound = Mix_LoadWAV (file.c_str());
		soundTable.emplace(file, sound);
		return sound;
	}
}

void Resources::ClearSounds(){
	while(!soundTable.empty()){
		Mix_FreeChunk(soundTable.begin()->second);
		soundTable.erase(soundTable.begin());
	}
}

void Resources::ClearMusic(){
	while(!musicTable.empty()){
		Mix_FreeMusic(musicTable.begin()->second);
		musicTable.erase(musicTable.begin());
	}
}


void Resources::ClearImages(){
	while(!imageTable.empty()){
		SDL_DestroyTexture(imageTable.begin()->second);
		imageTable.erase(imageTable.begin());
	}
}

void Resources::ClearFonts(){
	while(!fontTable.empty()){
		TTF_CloseFont(fontTable.begin()->second);
		fontTable.erase(fontTable.begin());
	}
}
