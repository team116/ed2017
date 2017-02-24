/*
 * DriveStraight.h
 *
 *  Created on: Feb 14, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_DRIVESTRAIGHT_H_
#define SRC_AUTOPLAYS_DRIVESTRAIGHT_H_

#include <AutoPlays/Action.h>
#include <Mobility.h>

class DriveStraight: public Action {
public:
	DriveStraight(float dis, float speed = 1.0);

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
	float distance;
	float speed;
};

#endif /* SRC_AUTOPLAYS_DRIVESTRAIGHT_H_ */
