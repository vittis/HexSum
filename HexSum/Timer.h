/*
 * Timer.h
 *
 *  Created on: 17/05/2015
 *      Author: Isaac
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer {
private:
	float time;

public:
	Timer();
	virtual ~Timer();
	void Update(float dt);
	void Restart();
	float Get();
};

#endif /* TIMER_H_ */
