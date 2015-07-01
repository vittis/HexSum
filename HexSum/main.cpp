/*
 * main.cpp
 *
 *  Created on: 31/03/2015
 *      Author: Isaac
 */

#include "Game.h"
#include "Hexsum/ArenaState.h"
#include "Hexsum/MenuState.h"

int main (int argc, char** argv) {
	Game game("HexSum", 1280, 768);
	game.Push(new MenuState() );
	game.Run();
    return 0;
}

