/*
 * Cleric.cpp
 *
 *  Created on: Jul 6, 2015
 *      Author: Vitor
 */

#include "Cleric.h"
#include "ArenaState.h"
#include "Constants.h"
#include "../InputManager.h"
#include "../Game.h"
#include "../StillAnimation.h"

Cleric::Cleric(Hex* hex, Player* player) : Unit(hex, player){
	if (player->color == Player::BLUE) {
		sprite_idle = Sprite("img/ClerigoAzul/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/ClerigoAzul/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/ClerigoAzul/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/ClerigoAzul/Cast.png", 37, 0.03);
		sprite_damage = Sprite("img/ClerigoAzul/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/cleric_blue.png",1,0);
	}
	else if (player->color == Player::RED) {
		sprite_idle = Sprite("img/ClerigoVermelho/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/ClerigoVermelho/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/ClerigoVermelho/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/ClerigoVermelho/Cast.png", 37, 0.03);
		sprite_damage = Sprite("img/ClerigoVermelho/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/cleric_red.png",1,0);
	}
	else if (player->color == Player::GREEN) {
		sprite_idle = Sprite("img/ClerigoVerde/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/ClerigoVerde/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/ClerigoVerde/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/ClerigoVerde/Cast.png", 37, 0.03);
		sprite_damage = Sprite("img/ClerigoVerde/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/cleric_green.png",1,0);
	}
	else if (player->color == Player::PURPLE) {
		sprite_idle = Sprite("img/ClerigoRoxo/Stand.png", 37, 0.06);
		sprite_walking = Sprite("img/ClerigoRoxo/Walk.png", 37, 0.03);
		sprite_attacking = Sprite("img/ClerigoRoxo/Attack.png", 37, 0.01);
		sprite_casting = Sprite("img/ClerigoRoxo/Cast.png", 37, 0.03);
		sprite_damage = Sprite("img/ClerigoRoxo/Damage.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/cleric_purple.png",1,0);
	}

	spAtual = sprite_idle;
	hp=3;
	atk=1;
	ap=3;
	maxAP=ap;
	type=UnitType::MELEE;
	specialAbilityCost=3;
}


void Cleric::Update(float dt) {
	Unit::Update(dt);
	if (ArenaState::selectedUnit == this) {
		if (InputManager::GetInstance().KeyPress(SDLK_v)) {
			ActionIntent(Action::SPECIAL_ABILITY);
		}
		if (InputManager::GetInstance().MousePress(1)) {
			for (int i=0; i<highlightedHexs.size(); i++) {
				if (highlightedHexs[i]->box.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
					switch (highlightedHexs[i]->color) {
						case Constants::SPECIAL_ABILITY_RANGE:
							TakeAction(Action::SPECIAL_ABILITY, highlightedHexs[i]);
							break;
						}
				}
			}
		}
	}
}
void Cleric::PrepareSpecialAbility() {
	ShowSummonRange();
}
void Cleric::PerformSpecialAbility(Hex* hex) {
	SetAnimacao(AnimationType::CASTING);
	Game::GetInstance()->GetCurrentState().AddObject(new StillAnimation(hex->center.x, hex->center.y-85, 0, Sprite("img/escudo.png", 37, 0.03), 1, true));
	static_cast<Unit*>(hex->unit)->hasDivineShield=true;
	std::cout<<"Cleric usou divine shield!!"<<std::endl;
}
void Cleric::ShowSummonRange() {
	for (int i=0; i<ArenaState::grid->hex_directions.size(); i++) {
		if (ArenaState::grid->GetNeighbor(*location, i).unit != NULL && static_cast<Unit*>(ArenaState::grid->GetNeighbor(*location, i).unit)->owner->color == owner->color) {
			ArenaState::grid->GetNeighbor(*location, i).Highlight(Constants::SPECIAL_ABILITY_RANGE);
			highlightedHexs.emplace_back(&ArenaState::grid->GetNeighbor(*location, i));
		}
	}
}
bool Cleric::Is(string type) {
	return type == "Cleric";
}


