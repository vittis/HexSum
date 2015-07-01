/*
 * Farmer.cpp
 *
 *  Created on: Jun 9, 2015
 *      Author: Vitor
 */

#include "Soldier.h"
#include "ArenaState.h"
#include "Constants.h"

Soldier::Soldier(Hex *hex, Player* player) : Unit(hex, player) {
	sprite_idle = Sprite("img/king_idle.png", 37, 0.03);
	sprite_walking = Sprite("img/king_andando.png", 37, 0.03);
	sprite_attacking = Sprite("img/king_atacando.png", 37, 0.03);
	sprite_casting = Sprite("img/king_casting.png", 20, 0.03);
	sprite_damage = Sprite("img/king_dano.png", 62, 2, 37, 0.03);
	card = Sprite("img/card_farmer.jpg",1,0);
	spAtual = sprite_idle;
	hp=2;
	atk=1;
	ap=2;
	maxAP=ap;
	type=UnitType::MELEE;
}
void Soldier::BeginTurnSetup() {
	Unit::BeginTurnSetup();
	for (int i=0; i<ArenaState::grid->hex_directions.size(); i++) {
		if (ArenaState::grid->GetNeighbor(*location, i).unit != NULL) {
			if (owner->color == static_cast<Unit*>(ArenaState::grid->GetNeighbor(*location, i).unit)->owner->color) {
				if (static_cast<Unit*>(ArenaState::grid->GetNeighbor(*location, i).unit)->Is("Farmer")) {
					ap++;
					std::cout<<"Farmer ganhou 1 bonus AP por estar perto de um outro Farmer!!!!!!"<<std::endl;
				}
			}
		}
	}
}
bool Soldier::Is(string type) {
	return (type == "Farmer");
}
