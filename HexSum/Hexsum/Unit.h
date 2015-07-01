/*
 * Unit.h
 *
 *  Created on: Jun 2, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_UNIT_H_
#define HEXSUM_UNIT_H_

#include "../GameObject.h"
#include "Player.h"
#include "Hex.h"
#include <vector>
#include "../Timer.h"


class Unit : public GameObject {
public:
	Unit(Hex* hex, Player* player);
	enum UnitState{
		IDLE,
		SELECTED
	};
	enum UnitType{
		MELEE,
		RANGED
	};
	enum Action{
		MOVE,
		ATTACK,
		PASS,
		SPECIAL_ABILITY
	};
	enum AnimationType {
		RESTING,
		MOVING,
		ATTACKING,
		CASTING,
		DAMAGE
	};
	virtual void Update(float);
	virtual void Render();
	virtual bool IsDead();
	virtual void NotifyCollision(GameObject &other);
	virtual bool Is(std::string type)=0;

	void MoveTo(Hex *hex);
	Hex *location;
	UnitState state;
	Player *owner;
	void EndTurn();
	virtual void BeginTurnSetup();
	void ShowMovimentRange();
	void ShowAttackRange();
	void ActionIntent(Action action);
	void ActionSetup();
	void HexClickedAcion();
	void TakeAction(Action action, Hex* hex);
	void MoveTowardHex(Hex* hex);
	virtual void SetAnimacao(AnimationType animationType);
	void AttackUnit(Unit *unit);
	void ReceiveDamage(int damage);
	virtual void PrepareSpecialAbility();
	virtual void PerformSpecialAbility(Hex* hex);

	AnimationType actualAnimation;
	Sprite spAtual;
	UnitType type;
	int hp, ap, atk, maxAP;
	int specialAbilityCost;
	vector<Hex*> highlightedHexs;
	bool highlightUnit;
	bool unHighlightUnit;
	bool firstAction;
	bool endTurnFlag;
	Hex* moveDestination;
	bool animating;
	bool facingRight;

	Sprite card;
	Sprite sprite_idle;
	Sprite sprite_attacking;
	Sprite sprite_walking;
	Sprite sprite_casting;
	Sprite sprite_damage;
};



#endif /* HEXSUM_UNIT_H_ */
