#ifndef GAME_H_
#define GAME_H_

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "State.h"
#include "Resources.h"
#include "InputManager.h"
#include "Camera.h"
#include <memory>
#include <stack>

using namespace std;

class Game {
	private:

		float dt;
		int frameStart;


		SDL_Renderer* renderer;
		SDL_Window* window;
		State* storedState;
		static Game* instance;
		stack<unique_ptr<State>> stateStack;

		void CalculateDeltaTime();

	public:
		
		Game(string, int, int);
		~Game();
		void Run();
		SDL_Renderer* GetRenderer();
		static Game* GetInstance();
		float GetDeltaTime();
		void Push(State*);
		State& GetCurrentState();
};

#endif /* GAME_H_ */
