/*
 * TurnDegrees.h
 *
 *  Created on: Feb 15, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ACTIONS_TURNDEGREES_H_
#define SRC_AUTOPLAYS_ACTIONS_TURNDEGREES_H_

#include <AutoPlays/Action.h>
#include <Mobility.h>

class TurnDegrees: public Action {
public:
	TurnDegrees(float ang);

	void start();

	void process();

	void end();

	bool isFinished();

private:
	Mobility* mobility;
	float angle;
};

#endif /* SRC_AUTOPLAYS_ACTIONS_TURNDEGREES_H_ */
