/*
 * StateData.h
 *
 *  Created on: 22/06/2015
 *      Author: Thiago
 */

#ifndef HEXSUM_STATEDATA_H_
#define HEXSUM_STATEDATA_H_

class StateData {
public:
	StateData();
	enum tipoRei {RED, BLUE, GREEN, PURPLE};
	enum tipoCampo {FLORESTA, NEVE, CASTELO};
	tipoRei rei1;
	tipoRei rei2;
	tipoCampo campo;
	void SetRei1(int rei1);
	void SetRei2(int rei2);
	void SetCampo(int campo);
};

#endif /* HEXSUM_STATEDATA_H_ */
