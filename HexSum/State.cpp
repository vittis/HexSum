
#include "State.h"


State::State():popRequested(false), quitRequested(false){}

State::~State(){

}

void State::Pause(){

}

void State::Resume(){

}

void State::AddObject(GameObject *ptr){
	objectArray.emplace_back(ptr);
}

void State::AddUIElement(UIElement *ptr){
	UIArray.emplace_back(ptr);
}

bool State::PopRequested(){
	return popRequested;
}

bool State::QuitRequested(){
	if(SDL_QuitRequested()){
		return true;
	}

	return quitRequested;
}

void State::UpdateArray(float dt){
	for(int i = 0; i < (int) objectArray.size(); i++){
		objectArray[i]->Update(dt);
		if(objectArray[i]->IsDead()) {
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::RenderArray(){
	for(int i = 0; i < (int) objectArray.size(); i++){
			objectArray[i]->Render();
		}
}


void State::UpdateUIArray(float dt){
	for(int i = 0; i < (int) UIArray.size(); i++){
			UIArray[i]->Update(dt);
	}
}

void State::RenderUIArray(){
	for(int i = 0; i < (int) UIArray.size(); i++){
			UIArray[i]->Render();
		}
}
