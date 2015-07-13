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
#include "Cleric.h"
#include "Soldier.h"

King::King(Hex *hex, Player* player, int initialMana) : Unit(hex, player), mana(initialMana) {
	summonManager = new SummonManager(this);
	owner->SetKing(this);
	switch (player->color) {
	case Player::BLUE:
		sprite_idle = Sprite("img/KingAzul/parado.png", 37, 0.06);
		sprite_walking = Sprite("img/KingAzul/andando.png", 37, 0.03);
		sprite_attacking = Sprite("img/KingAzul/ataque.png", 37, 0.03);
		sprite_casting = Sprite("img/KingAzul/cast.png", 37, 0.03);
		sprite_damage = Sprite("img/KingAzul/dano.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/king_blue.png",1,0);
		break;
	case Player::RED:
		sprite_idle = Sprite("img/KingVermelho/parado.png", 37, 0.06);
		sprite_walking = Sprite("img/KingVermelho/andando.png", 37, 0.03);
		sprite_attacking = Sprite("img/KingVermelho/ataque.png", 37, 0.03);
		sprite_casting = Sprite("img/KingVermelho/cast.png", 37, 0.03);
		sprite_damage = Sprite("img/KingVermelho/dano.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/king_red.png",1,0);
		break;
	case Player::GREEN:
		sprite_idle = Sprite("img/KingVerde/parado.png", 37, 0.06);
		sprite_walking = Sprite("img/KingVerde/andando.png", 37, 0.03);
		sprite_attacking = Sprite("img/KingVerde/ataque.png", 37, 0.03);
		sprite_casting = Sprite("img/KingVerde/cast.png", 37, 0.03);
		sprite_damage = Sprite("img/KingVerde/dano.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/king_green.png",1,0);
		break;
	case Player::PURPLE:
		sprite_idle = Sprite("img/KingRoxo/parado.png", 37, 0.06);
		sprite_walking = Sprite("img/KingRoxo/andando.png", 37, 0.03);
		sprite_attacking = Sprite("img/KingRoxo/ataque.png", 37, 0.03);
		sprite_casting = Sprite("img/KingRoxo/cast.png", 37, 0.03);
		sprite_damage = Sprite("img/KingRoxo/dano.png", 37, 0.03);
		card = Sprite("img/Main UI cortada/Fotos/king_purple.png",1,0);
		break;
	}

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
	for(int i=0; i< ArenaState::towers.size(); i++) {
		if (ArenaState::towers[i]->owner != NULL)
			if (ArenaState::towers[i]->owner->color == owner->color)
				mana++;
	}
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
						case Constants::SPECIAL_ABILITY_RANGE://TODO: checar mana atual p sumona, arenastate::summonSelecionado
							if (mana >= summonManager->GetCustoManaUnidade(ArenaState::summonSelecionado) + summonManager->GetCustoAdicional(ArenaState::summonSelecionado, owner))
								TakeAction(Action::SPECIAL_ABILITY, highlightedHexs[i]);
							else
								std::cout<<"nao ha mana suficiente"<<std::endl;
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
	mana -= summonManager->GetCustoManaUnidade(ArenaState::summonSelecionado)+summonManager->GetCustoAdicional(ArenaState::summonSelecionado, owner);
	summonManager->SummonUnit(static_cast<SummonManager::TipoUnidade>(ArenaState::summonSelecionado), hex, owner);
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
