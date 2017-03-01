/*
 * CloseGearHolder.h
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ACTIONS_CLOSEGEARHOLDER_H_
#define SRC_AUTOPLAYS_ACTIONS_CLOSEGEARHOLDER_H_

#include <AutoPlays/Action.h>
#include <Gear.h>
#include <Timer.h>

class CloseGearHolder: public Action {
public:
	CloseGearHolder();
	void start();

	void process();

	void end();

	bool isFinished();

private:
	Gear* gear;
	float close_gear_time;
};

#endif /* SRC_AUTOPLAYS_ACTIONS_CLOSEGEARHOLDER_H_ */
