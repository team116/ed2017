/*
 * Wiggle.h
 *
 *  Created on: Mar 2, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ACTIONS_WIGGLE_H_
#define SRC_AUTOPLAYS_ACTIONS_WIGGLE_H_

#include <AutoPlays/Action.h>
#include <Timer.h>
#include <Mobility.h>

class Wiggle: public Action {
public:
	Wiggle();
	void start();

	void process();

	void end();

	bool isFinished();

private:
	Mobility* mobility;
	Timer* wiggle_timer;
	bool left_side;
};

#endif /* SRC_AUTOPLAYS_ACTIONS_WIGGLE_H_ */
