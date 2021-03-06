/*
 * Archer.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: Vitor
 */

#include "Archer.h"
#include "ArenaState.h"
#include "../InputManager.h"
#include "../StillAnimation.h"
#include "../Game.h"

Archer::Archer(Hex *hex, Player* player) : Unit(hex, player) {
	if (player->color == Player::BLUE) {
		sprite_idle = Sprite("img/ArqueiroAzul/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/ArqueiroAzul/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/ArqueiroAzul/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/ArqueiroAzul/Attack.png", 37, 0.03);
		sprite_damage = Sprite("img/ArqueiroAzul/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/archer_blue.png",1,0);
	}
	else if (player->color == Player::RED) {
		sprite_idle = Sprite("img/ArqueiroVermelho/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/ArqueiroVermelho/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/ArqueiroVermelho/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/ArqueiroVermelho/Attack.png", 37, 0.03);
		sprite_damage = Sprite("img/ArqueiroVermelho/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/archer_red.png",1,0);
	}
	else if (player->color == Player::GREEN) {
		sprite_idle = Sprite("img/ArqueiroVerde/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/ArqueiroVerde/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/ArqueiroVerde/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/ArqueiroVerde/Attack.png", 37, 0.03);
		sprite_damage = Sprite("img/ArqueiroVerde/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/archer_green.png",1,0);
	}
	else if (player->color == Player::PURPLE) {
		sprite_idle = Sprite("img/ArqueiroRoxo/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/ArqueiroRoxo/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/ArqueiroRoxo/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/ArqueiroRoxo/Attack.png", 37, 0.03);
		sprite_damage = Sprite("img/ArqueiroRoxo/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/archer_purple.png",1,0);
	}

	spAtual = sprite_idle;
	hp=2;
	atk=1;
	ap=2;
	maxAP=ap;
	type=UnitType::RANGED;
	usedFocus=false;
	specialAbilityCost=2;
}
void Archer::Update(float dt) {
	Unit::Update(dt);
	if (ArenaState::selectedUnit == this) {
		if (InputManager::GetInstance().KeyPress(SDLK_v)) {
			ActionIntent(Action::SPECIAL_ABILITY);
		}
	}

}
void Archer::PrepareSpecialAbility() {
	TakeAction(Action::SPECIAL_ABILITY, nullptr);
}
void Archer::PerformSpecialAbility(Hex* hex) {
	SetAnimacao(AnimationType::CASTING);
	usedFocus=true;
	Game::GetInstance()->GetCurrentState().AddObject(new StillAnimation(location->center.x, location->center.y-85, 0, Sprite("img/focus.png", 37, 0.03), 1, true));
	std::cout<<"Archer has used FOCUS!"<<std::endl;
}
void Archer::BeginTurnSetup() {
	Unit::BeginTurnSetup();
	if (usedFocus) {
		ap++;
		usedFocus=false;
	}
}
bool Archer::Is(string type) {
	return type == "Archer";
}



