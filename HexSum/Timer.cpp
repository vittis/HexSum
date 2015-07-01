/*
 * Timer.cpp
 *
 *  Created on: 17/05/2015
 *      Author: Isaac
 */

#include "Timer.h"

Timer::Timer() : time(0){}

void Timer::Restart(){
	time = 0;
}

void Timer::Update(float dt){
	time += dt;
}

float Timer::Get(){
	return this->time;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

