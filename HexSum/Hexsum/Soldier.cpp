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
	if (player->color == Player::BLUE) {
		sprite_idle = Sprite("img/SoldadoAzul/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/SoldadoAzul/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/SoldadoAzul/Attack.png", 37, 0.03);
		sprite_casting = Sprite("img/SoldadoAzul/Attack.png", 37, 0.03);
		sprite_damage = Sprite("img/SoldadoAzul/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/soldier_blue.png",1,0);
	}
	else if (player->color == Player::RED) {
		sprite_idle = Sprite("img/SoldadoVermelho/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/SoldadoVermelho/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/SoldadoVermelho/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/SoldadoVermelho/Attack.png", 37, 0.03);
		sprite_damage = Sprite("img/SoldadoVermelho/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/soldier_red.png",1,0);
	}
	else if (player->color == Player::GREEN) {
		sprite_idle = Sprite("img/SoldadoVerde/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/SoldadoVerde/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/SoldadoVerde/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/SoldadoVerde/Attack.png", 37, 0.03);
		sprite_damage = Sprite("img/SoldadoVerde/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/soldier_green.png",1,0);
	}
	else if (player->color == Player::PURPLE) {
		sprite_idle = Sprite("img/SoldadoRoxo/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/SoldadoRoxo/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/SoldadoRoxo/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/SoldadoRoxo/Attack.png", 37, 0.03);
		sprite_damage = Sprite("img/SoldadoRoxo/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/soldier_purple.png",1,0);
	}

	spAtual = sprite_idle;
	hp=3;
	atk=2;
	ap=3;
	maxAP=ap;
	type=UnitType::MELEE;
}
void Soldier::BeginTurnSetup() {
	Unit::BeginTurnSetup();
	/*for (int i=0; i<ArenaState::grid->hex_directions.size(); i++) {
		if (ArenaState::grid->GetNeighbor(*location, i).unit != NULL) {
			if (owner->color == static_cast<Unit*>(ArenaState::grid->GetNeighbor(*location, i).unit)->owner->color) {
				if (static_cast<Unit*>(ArenaState::grid->GetNeighbor(*location, i).unit)->Is("Farmer")) {
					ap++;
					std::cout<<"Soldier ganhou 1 bonus AP por estar perto de um outro Soldier!!!!!!"<<std::endl;
				}
			}
		}
	}*/
}
bool Soldier::Is(string type) {
	return (type == "Soldier");
}
