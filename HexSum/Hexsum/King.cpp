/*
 * King.cpp
 *
 *  Created on: Jun 23, 2015
 *      Author: Vitor
 */

#include "King.h"
#include "ArenaState.h"
#include "../InputManager.h"
#include "Constants.h"
#include "Archer.h"
#include "../Game.h"

King::King(Hex *hex, Player* player, int initialMana) : Unit(hex, player), mana(initialMana) {
	switch (player->color) {
	case Player::BLUE:
		sprite_idle = Sprite("img/KingAzul/parado.png", 37, 0.03);
		sprite_walking = Sprite("img/KingAzul/andando.png", 37, 0.03);
		sprite_attacking = Sprite("img/KingAzul/ataque.png", 37, 0.03);
		sprite_casting = Sprite("img/KingAzul/cast.png", 37, 0.03);
		sprite_damage = Sprite("img/KingAzul/dano.png", 37, 0.03);
		break;
	case Player::RED:
		sprite_idle = Sprite("img/KingVermelho/parado.png", 37, 0.03);
		sprite_walking = Sprite("img/KingVermelho/andando.png", 37, 0.03);
		sprite_attacking = Sprite("img/KingVermelho/ataque.png", 37, 0.03);
		sprite_casting = Sprite("img/KingVermelho/cast.png", 37, 0.03);
		sprite_damage = Sprite("img/KingVermelho/dano.png", 37, 0.03);
		break;
	case Player::GREEN:
		sprite_idle = Sprite("img/KingVerde/parado.png", 37, 0.03);
		sprite_walking = Sprite("img/KingVerde/andando.png", 37, 0.03);
		sprite_attacking = Sprite("img/KingVerde/ataque.png", 37, 0.03);
		sprite_casting = Sprite("img/KingVerde/cast.png", 37, 0.03);
		sprite_damage = Sprite("img/KingVerde/dano.png", 37, 0.03);
		break;
	case Player::PURPLE:
		sprite_idle = Sprite("img/KingRoxo/parado.png", 37, 0.03);
		sprite_walking = Sprite("img/KingRoxo/andando.png", 37, 0.03);
		sprite_attacking = Sprite("img/KingRoxo/ataque.png", 37, 0.03);
		sprite_casting = Sprite("img/KingRoxo/cast.png", 37, 0.03);
		sprite_damage = Sprite("img/KingRoxo/dano.png", 37, 0.03);
		break;
	}
	/*	 sprite_idle.SetScaleX(1.1);
	sprite_idle.SetScaleY(1.1);
	sprite_walking.SetScaleX(1.1);
	sprite_walking.SetScaleY(1.1);
	sprite_attacking.SetScaleX(1.1);
	sprite_attacking.SetScaleY(1.1);
	sprite_casting.SetScaleX(1.1);
	sprite_casting.SetScaleY(1.1);
	sprite_damage.SetScaleX(1.1);
	sprite_damage.SetScaleY(1.1);*/

	card = Sprite("img/card_farmer.jpg",1,0);
	spAtual = sprite_idle;
	hp=5;
	atk=1;
	ap=3;
	maxAP=ap;
	specialAbilityCost=3;
	type=UnitType::MELEE;
}
void King::BeginTurnSetup() {
	Unit::BeginTurnSetup();
	std::cout<<"king setup"<<std::endl;
	mana++;
}
void King::Update(float dt) {
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
void King::PrepareSpecialAbility() {
	ShowSummonRange();
}
void King::PerformSpecialAbility(Hex* hex) {
	SetAnimacao(AnimationType::CASTING);
	//if (owner->color == Player::BLUE) {
	Unit* archer = new Archer(hex, owner);
	Game::GetInstance()->GetCurrentState().AddObject(archer);
	ArenaState::turnLogic.allUnits.emplace_back(archer);
	//}
	//else {
	//	Unit* archer = new Archer(hex, ArenaState::player2);
	//	Game::GetInstance()->GetCurrentState().AddObject(archer);
	//	ArenaState::turnLogic.allUnits.emplace_back(archer);
	//}
}
void King::ShowSummonRange() {
	for (int i=0; i<ArenaState::grid->hex_directions.size(); i++) {
		if (ArenaState::grid->GetNeighbor(*location, i).isEmpty) {
			ArenaState::grid->GetNeighbor(*location, i).Highlight(Constants::SPECIAL_ABILITY_RANGE);
			highlightedHexs.emplace_back(&ArenaState::grid->GetNeighbor(*location, i));
		}
	}
}
bool King::Is(string type) {
	return type == "King";
}
