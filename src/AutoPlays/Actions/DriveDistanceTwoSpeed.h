/*
 * DriveDistanceTwoSpeed.h
 *
 *  Created on: Mar 3, 2017
 *      Author: Will
 */

#ifndef SRC_AUTOPLAYS_ACTIONS_DRIVEDISTANCETWOSPEED_H_
#define SRC_AUTOPLAYS_ACTIONS_DRIVEDISTANCETWOSPEED_H_

#include <AutoPlays/Action.h>

#include "Mobility.h"

class DriveDistanceTwoSpeed: public Action {
public:
	DriveDistanceTwoSpeed(float dist1, float speed1, float dist2, float speed2);

	//Called once when the routine starts
	void start();

	//Called repeatedly while the routine runs
	void process();

	//Called once when the routine ends
	void end();

	//Returns whether or not the routine is finished
	bool isFinished();

private:
	Mobility* mobility;
	float distance1;
	float distance2;
	float speed1;
	float speed2;
};

#endif /* SRC_AUTOPLAYS_ACTIONS_DRIVEDISTANCETWOSPEED_H_ */
