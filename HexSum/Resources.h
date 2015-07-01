
#ifndef RESOURCES_H_
#define RESOURCES_H_

#include "Game.h"
#include <SDL_Mixer.h>
#include <SDL_image.h>
#include <SDL_TTF.h>
#include <unordered_map>

using namespace std;

class Resources {
private:
	static unordered_map<string, SDL_Texture*> imageTable;
	static unordered_map<string, Mix_Music*> musicTable;
	static unordered_map<string, Mix_Chunk*> soundTable;
	static unordered_map<string, TTF_Font*> fontTable;
public:
	static void ClearImages();
	static void ClearMusic();
	static void ClearFonts();
	static void ClearSounds();

	static TTF_Font* GetFont(string file, int ptsize);
	static SDL_Texture* GetImage(string file);
	static Mix_Music* GetMusic(string file);
	static Mix_Chunk* GetSound(string file);
};

#endif /* RESOURCES_H_ */
