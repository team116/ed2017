/*
 * DropGear.h
 *
 *  Created on: Feb 15, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ACTIONS_DROPGEAR_H_
#define SRC_AUTOPLAYS_ACTIONS_DROPGEAR_H_

#include <AutoPlays/Action.h>
#include <Gear.h>

class DropGear: public Action {
public:
	DropGear();
	void start();

	void process();

	void end();

	bool isFinished();

private:
	Gear* gear;
};

#endif /* SRC_AUTOPLAYS_ACTIONS_DROPGEAR_H_ */
