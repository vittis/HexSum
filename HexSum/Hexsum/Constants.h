/*
 * Constants.h
 *
 *  Created on: Jun 5, 2015
 *      Author: Vitor
 */

#ifndef HEXSUM_CONSTANTS_H_
#define HEXSUM_CONSTANTS_H_

#include <utility>
#include "Hex.h"

class Constants {
public:
	class HexLayout {
	public:
		static constexpr float f0 = 1.5;
		static constexpr float f1 = 0;
		static constexpr float f2 = 0.866;
		static constexpr float f3 = 1.732;
	};
	static constexpr Hex::Cor MOVE_RANGE= Hex::VERDECLARO;
	static constexpr Hex::Cor ATTACK_RANGE= Hex::AMARELO;
	static constexpr Hex::Cor ATTACK_UNIT= Hex::LARANJA;
	static constexpr Hex::Cor SPECIAL_ABILITY_RANGE= Hex::CIANO;
	static constexpr int manaInicial=2;
	static constexpr int custoManaSoldier=4;
	static constexpr int custoManaArcher=3;
	static constexpr int custoManaCleric=6;
};



#endif /* HEXSUM_CONSTANTS_H_ */
