/*
 * Unit.cpp
 *
 *  Created on: Jun 8, 2015
 *      Author: Vitor
 */

#include "Unit.h"
#include "ArenaState.h"
#include "../InputManager.h"
#include "Constants.h"
#include "../Game.h"
#include "../StillAnimation.h"
#include "Tower.h"

Unit::Unit(Hex* hex, Player* player) {
	hasDivineShield=false;
	highlightUnit=true;
	unHighlightUnit=false;
	animating=false;
	moveDestination=NULL;
	endTurnFlag=false;
	owner=player;
	hex->isEmpty=false;
	hex->unit = this;
	location = hex;
	box.x = location->center.x-spAtual.GetWidth()/2;
	box.y = location->center.y-spAtual.GetHeight();
	box.w = spAtual.GetWidth();
	box.h = spAtual.GetHeight();
	state = UnitState::IDLE;
	location->Highlight(static_cast<Hex::Cor>((int)owner->color));
	//else
	//	location->Highlight(Hex::Cor::VERMELHO);
}
void Unit::MoveTo(Hex* hex) {
	SetAnimacao(AnimationType::MOVING);
	spAtual.SetFlipped(facingRight);
	moveDestination = hex;
	location->unit =NULL;
	location->isEmpty=true;
	location = hex;
	location->isEmpty=false;
	location->unit = this;
}
void Unit::ShowMovimentRange() {
	for (int i=0; i<ArenaState::grid->hex_directions.size(); i++) {
		if (ArenaState::grid->GetNeighbor(*location, i).isEmpty || ArenaState::grid->GetNeighbor(*location, i).isTower) {
			if (ArenaState::grid->GetNeighbor(*location, i).isEmpty) {
				ArenaState::grid->GetNeighbor(*location, i).Highlight(Constants::MOVE_RANGE);
				highlightedHexs.emplace_back(&ArenaState::grid->GetNeighbor(*location, i));
			}
			else if (ArenaState::grid->GetNeighbor(*location, i).isTower) {
				if (static_cast<Tower*>(ArenaState::grid->GetNeighbor(*location, i).tower)->owner == NULL) {
					ArenaState::grid->GetNeighbor(*location, i).Highlight(static_cast<Hex::Cor>((int)owner->color));
					highlightedHexs.emplace_back(&ArenaState::grid->GetNeighbor(*location, i));
				}
				else {
					if (static_cast<Tower*>(ArenaState::grid->GetNeighbor(*location, i).tower)->owner->color != owner->color) {
						ArenaState::grid->GetNeighbor(*location, i).Highlight(static_cast<Hex::Cor>((int)owner->color));
						highlightedHexs.emplace_back(&ArenaState::grid->GetNeighbor(*location, i));
					}
				}
			}
		}
	}
}

void Unit::ActionIntent(Action action) {
	if(!ArenaState::pause){
		if ((moveDestination == NULL && !animating) || action == Action::PASS) {
			if (!highlightUnit) {
				ActionSetup();
				switch (action) {
					case Action::MOVE:
						ShowMovimentRange();
						break;
					case Action::ATTACK:
						ShowAttackRange();
						break;
					case Action::PASS:
						TakeAction(action, nullptr);
						break;
					case Action::SPECIAL_ABILITY:
						PrepareSpecialAbility();
						break;
				}
			}
		}
	}
}
void Unit::CaptureTower(Hex* hex) {
	static_cast<Tower*>(hex->tower)->BeCaptured(owner);
}
void Unit::TakeAction(Action action, Hex* hex) {
	if(!ArenaState::pause){
		//if (!unHighlightUnit) { Descomentar para clicar no hex só se a parada tiver descido
		if (hex != NULL)
			if(hex->center.x > location->center.x)
				facingRight = true;
			else if(hex->center.x< location->center.x)
				facingRight = false;
			switch (action) {
				case Action::MOVE:
					if (ap >= 1) {
						if (hex->isEmpty) {
							MoveTo(hex);
							ap--;
						}
						else if (hex->isTower) {
							CaptureTower(hex);
							ap--;
						}
					}
					break;
				case Action::ATTACK:
					if (ap >= 2) {
						AttackUnit(static_cast<Unit*>(hex->unit));
						ap-=2;
					}
					else {
						std::cout<<"voce nao tem action points suficiente"<<std::endl;
					}
					break;
				case Action::PASS:
					unHighlightUnit=true;
					ap=0;
					break;
				case Action::SPECIAL_ABILITY:
					if (ap >= specialAbilityCost) {
						PerformSpecialAbility(hex);
						ap-= specialAbilityCost;
					}
					break;
				default:
					std::cout<<"action nao definida!!!!"<<std::endl;
					break;
			}

			ActionSetup();
			if (action != Action::PASS)
				for (int i =0; i<ArenaState::grid->size(); i++) {
					ArenaState::grid->At(i).height=ArenaState::grid->At(i).originalHeight;
				}
			if (ap <= 0 && moveDestination == NULL && !animating) {
				EndTurn();
			}
			else if (ap <= 0)
				endTurnFlag=true;
		//}
	}
}
void Unit::AttackUnit(Unit* unit) {
	if (unit->box.x > this->box.x) {
		facingRight=true;
		unit->facingRight=false;
	}
	else {
		facingRight=false;
		unit->facingRight=true;
	}
	SetAnimacao(AnimationType::ATTACKING);
	unit->ReceiveDamage(this->atk);
}
void Unit::ReceiveDamage(int damage) {
	SetAnimacao(AnimationType::DAMAGE);
	if (!hasDivineShield) {
		hp-=damage;
	}
	else {
		hp-=damage-1;
		hasDivineShield=false;
	}
	if (hp<=0) {
		ArenaState::turnLogic.RemoveUnit(this);
		location->isEmpty=true;
	}
}
void Unit::ActionSetup() {
	if (!unHighlightUnit && firstAction)
		unHighlightUnit=true;
	firstAction=false;
	ArenaState::grid->UnHighlightAll();
	for (int i=0; i< ArenaState::turnLogic.allUnits.size(); i++) {
		ArenaState::turnLogic.allUnits[i]->location->Highlight(static_cast<Hex::Cor>((int)ArenaState::turnLogic.allUnits[i]->owner->color));
	}
}
void Unit::EndTurn() {
	ArenaState::selectedInfoUnit = NULL;
	ArenaState::estadoRei = false;
	ArenaState::passou = true;

	if (ArenaState::selectedUnit == this)
		ArenaState::turnLogic.PassTurnToNextUnit();
}
void Unit::BeginTurnSetup() {
	highlightedHexs.clear();
	endTurnFlag=false;
	firstAction=true;
	highlightUnit=true;
	unHighlightUnit=false;
	ap = maxAP;
}
void Unit::Update(float dt){
	if (animating) {
		if (actualAnimation == AnimationType::MOVING) {
			if (moveDestination==NULL) {
				animating=false;
				spAtual = sprite_idle;
				if (endTurnFlag)
					EndTurn();
			}
		}
		else {
			if (spAtual.currentFrame == spAtual.frameCount-1) {
				animating=false;
				spAtual = sprite_idle;
				if (endTurnFlag)
					EndTurn();
			}
		}
	}
	spAtual.SetFlipped(facingRight);
	spAtual.Update(dt);
	if (unHighlightUnit) {
				location->height+=1.5;
				if (location->height >= 0) {
					unHighlightUnit=false;
					location->height=0;
				}
			}
	if (ArenaState::selectedUnit == this) {
		if (highlightUnit) {
			location->height-= 1.5;
			if (location->height <= -15) {
				highlightUnit=false;
				location->height=-15;
			}
		}
		if (InputManager::GetInstance().KeyPress(SDLK_x)) {
			ActionIntent(Action::MOVE);
		}
		if (InputManager::GetInstance().KeyPress(SDLK_c)){
			ActionIntent(Action::ATTACK);
		}
		if (InputManager::GetInstance().KeyPress(SDLK_z)){
			ActionIntent(Action::PASS);
		}
		if (InputManager::GetInstance().MousePress(1)) {
			for (int i=0; i<highlightedHexs.size(); i++) {
				if (highlightedHexs[i]->box.IsInside((float)InputManager::GetInstance().GetMouseX(), (float)InputManager::GetInstance().GetMouseY())) {
					switch (highlightedHexs[i]->color) {
						case Constants::MOVE_RANGE:
							TakeAction(Action::MOVE, highlightedHexs[i]);
							break;
						case Hex::ROXO:
							TakeAction(Action::MOVE, highlightedHexs[i]);
							break;
						case Hex::AZUL:
							TakeAction(Action::MOVE, highlightedHexs[i]);
							break;
						case Hex::VERMELHO:
							TakeAction(Action::MOVE, highlightedHexs[i]);
							break;
						case Hex::VERDE:
							TakeAction(Action::MOVE, highlightedHexs[i]);
							break;
						case Constants::ATTACK_UNIT:
							TakeAction(Action::ATTACK, highlightedHexs[i]);
							break;
						default:
							break;
					}
				}
			}
		}
	}
	if (moveDestination != NULL) {
		MoveTowardHex(moveDestination);
	}
	else {
		box.x = location->center.x-spAtual.GetWidth()/2;
		box.y = location->center.y-spAtual.GetHeight() + location->height;
	}
}

void Unit::SetAnimacao(AnimationType animationType){
	animating=true;
	actualAnimation=animationType;
	if (animationType == AnimationType::ATTACKING) {
		spAtual = sprite_attacking;
	}
	if (animationType == AnimationType::CASTING) {
		spAtual = sprite_casting;
	}
	if (animationType == AnimationType::DAMAGE) {
		spAtual = sprite_damage;
	}
	if (animationType == AnimationType::MOVING){
		spAtual = sprite_walking;
		if (Is("Soldier"))
			spAtual.SetFrame(25);
		else if (Is("Cleric"))
			spAtual.SetFrame(20);
	}
}

void Unit::MoveTowardHex(Hex* hex) {
	Point inicio(box.x+spAtual.GetWidth()/2, box.y+spAtual.GetHeight()/2+spAtual.GetHeight()/2);
	Point destino(hex->center.x, hex->center.y);
	float dist = sqrt((destino.x-inicio.x)*(destino.x-inicio.x) + (destino.y-inicio.y)*(destino.y-inicio.y));
	float yVel = (2*(destino.y-inicio.y)/ dist);
	float xVel = (2*(destino.x-inicio.x)/ dist);

	box.x += xVel;
	box.y += yVel;

	if (dist <= 5) {
		moveDestination=NULL;
		if (endTurnFlag)
			EndTurn();
	}
}
void Unit::Render() {
	spAtual.Render(box.x, box.y, 0);
}
bool Unit::IsDead() {
	if (hp<=0 && !animating) {
		location->unit = NULL;
		location->UnHighlight();
		Game::GetInstance()->GetCurrentState().AddObject(new StillAnimation(location->box.x+23, location->box.y-25, 0, Sprite("img/death.png",37 ,2, 19, 0.03), 1, true));
		return true;
	}
	return false;
}
void Unit::NotifyCollision(GameObject& other){}
void Unit::PrepareSpecialAbility(){}
void Unit::PerformSpecialAbility(Hex *hex){}
void Unit::ShowAttackRange() {
	if (type == UnitType::MELEE) {
		for (int i=0; i<ArenaState::grid->hex_directions.size(); i++) {
			if (ArenaState::grid->GetNeighbor(*location, i).isEmpty) {
				ArenaState::grid->GetNeighbor(*location, i).Highlight(Constants::ATTACK_RANGE);
			}
			else if (ArenaState::grid->GetNeighbor(*location, i).unit != NULL) {
				if (owner->color != static_cast<Unit*>(ArenaState::grid->GetNeighbor(*location, i).unit)->owner->color) {
					ArenaState::grid->GetNeighbor(*location, i).Highlight(Constants::ATTACK_UNIT);
					highlightedHexs.emplace_back(&ArenaState::grid->GetNeighbor(*location, i));
				}
			}
		}
	}
	else if (type == UnitType::RANGED){//TODO: Refatorar rs
		for (int i=0; i<ArenaState::grid->hex_directions.size(); i++) {
			bool rangeBlocked=false;
			if (!ArenaState::grid->GetNeighbor(*location, i).isEmpty)
				rangeBlocked=true;

			if (ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i).isEmpty && !rangeBlocked) {
				ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i).Highlight(Constants::ATTACK_RANGE);
			}
			else if (ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i).unit != NULL && !rangeBlocked) {
				if (owner->color != static_cast<Unit*>(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i).unit)->owner->color) {
					ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i).Highlight(Constants::ATTACK_UNIT);
					highlightedHexs.emplace_back(&ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i));
				}
			rangeBlocked=true;
			}
			else {
				rangeBlocked=true;
			}

			if (ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i).isEmpty && !rangeBlocked){
				ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i).Highlight(Constants::ATTACK_RANGE);
			}
			else if (ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i).unit != NULL && !rangeBlocked){
				if (owner->color != static_cast<Unit*>(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i).unit)->owner->color) {
					ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i).Highlight(Constants::ATTACK_UNIT);
					highlightedHexs.emplace_back(&ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i));
				}
				rangeBlocked=true;
			}
			else {
				rangeBlocked=true;
			}

			if (ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i), i).isEmpty && !rangeBlocked) {
				ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i), i).Highlight(Constants::ATTACK_RANGE);
			}
			else if (ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i), i).unit != NULL && !rangeBlocked) {
				if (owner->color != static_cast<Unit*>(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i), i).unit)->owner->color) {
					ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i), i).Highlight(Constants::ATTACK_UNIT);
					highlightedHexs.emplace_back(&	ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(ArenaState::grid->GetNeighbor(*location, i), i), i), i));
				}
			}
		}
	}
}
