#include "Game.h"

Game* Game::instance = NULL;


Game::Game(string title, int width, int height) : dt (0), frameStart(SDL_GetTicks()) {
	if(instance == NULL){
		this->instance = this;
	}else{
		cout << "deu ruim" << endl;
	}

	if( SDL_Init(SDL_INIT_EVERYTHING) != 0){
		cout <<  SDL_GetError() << endl;
	}


	if( IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) != 0){
		cout <<  IMG_GetError() << endl;
	}

	Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);

	if(TTF_Init() != 0){
		cout << "ttf_erro" << endl;
	}

	window = SDL_CreateWindow ( title.c_str(), 50 , 25 , width , height , SDL_WINDOW_OPENGL);

	if(window != 0){
		cout <<  SDL_GetError() << endl;
	}

	if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) != 0){
		cout << "erro open audio" << endl;
	}

	if((renderer = SDL_CreateRenderer ( window , -1 , SDL_RENDERER_ACCELERATED)) != 0){
		cout <<  SDL_GetError() << endl;
	}

	storedState = NULL;

}

Game::~Game(){
	if(storedState != NULL){
		delete storedState;

		while(!stateStack.empty())
			stateStack.pop();
	}
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
    SDL_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
}

SDL_Renderer* Game::GetRenderer(){
	return renderer;
}

Game* Game::GetInstance(){
	return instance;
}

State& Game::GetCurrentState(){
	return *stateStack.top();
}

void Game::Push(State* state){
	storedState = state;
}

void Game::Run(){
	if (storedState != NULL) {
		stateStack.emplace(storedState);
		storedState = NULL;
	}
	if (stateStack.empty() || GetCurrentState().QuitRequested())
		SDL_Quit();
	while(!stateStack.empty() && !GetCurrentState().QuitRequested()){
		if(GetCurrentState().PopRequested()){
			stateStack.pop();
			stateStack.top()->Resume();
		}
		if(storedState != NULL){
			stateStack.top()->Pause();
			stateStack.emplace(storedState);
			storedState = NULL;
		}
		CalculateDeltaTime();
		InputManager::GetInstance().Update();
		GetCurrentState().Update(GetDeltaTime());
		GetCurrentState().Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
	Resources::ClearImages();
	Resources::ClearSounds();
	Resources::ClearMusic();
	Resources::ClearFonts();
}

void Game::CalculateDeltaTime(){
	dt = (float)(SDL_GetTicks() - frameStart)/1000;
	frameStart = SDL_GetTicks();
}

float Game::GetDeltaTime(){
	return dt;
}
