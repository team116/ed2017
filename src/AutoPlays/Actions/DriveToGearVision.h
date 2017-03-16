/*
 * DriveToGearVision.h
 *
 *  Created on: Mar 15, 2017
 *      Author: Will
 */

#ifndef SRC_AUTOPLAYS_ACTIONS_DRIVETOGEARVISION_H_
#define SRC_AUTOPLAYS_ACTIONS_DRIVETOGEARVISION_H_

#include <AutoPlays/Action.h>
#include "Vision.h"
#include "Mobility.h"

class DriveToGearVision: public Action {
public:
	DriveToGearVision();

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
	Vision* vision;
};

#endif /* SRC_AUTOPLAYS_ACTIONS_DRIVETOGEARVISION_H_ */
