/*
 * StateData.cpp
 *
 *  Created on: 22/06/2015
 *      Author: Thiago
 */

#include "StateData.h"
#include <stdio.h>

StateData::StateData() {

}

void StateData::SetRei1(int rei1) {
	switch(rei1) {
		case 1: this->rei1 = tipoRei::RED; break;
		case 2: this->rei1 = tipoRei::BLUE; break;
		case 3: this->rei1 = tipoRei::GREEN; break;
		case 4: this->rei1 = tipoRei::PURPLE; break;
	}
}

void StateData::SetRei2(int rei2) {
	switch(rei2) {
		case 1: this->rei2 = tipoRei::RED; break;
		case 2: this->rei2 = tipoRei::BLUE; break;
		case 3: this->rei2 = tipoRei::GREEN; break;
		case 4: this->rei2 = tipoRei::PURPLE; break;
	}
}

void StateData::SetCampo(int campo) {
	switch(campo) {
		case 1: this->campo = tipoCampo::FLORESTA; break;
		case 2: this->campo = tipoCampo::NEVE; break;
		case 3: this->campo = tipoCampo::CASTELO; break;
	}
}
