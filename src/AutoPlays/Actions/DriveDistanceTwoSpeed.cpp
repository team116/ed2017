/*
 * DriveDistanceTwoSpeed.cpp
 *
 *  Created on: Mar 3, 2017
 *      Author: Will
 */

#include <AutoPlays/Actions/DriveDistanceTwoSpeed.h>

DriveDistanceTwoSpeed::DriveDistanceTwoSpeed(float dist1, float speed1, float dist2, float speed2) {
	mobility = Mobility::getInstance();

	distance1 = dist1;
	this->speed1 = speed1;
	distance2 = dist2;
	this->speed2 = speed2;

	setTimeout(fabs(distance1) / 50 / speed1 + fabs(distance2) / 50 / speed2);
}

void DriveDistanceTwoSpeed::start() {
	log->write(Log::INFO_LEVEL, "[Action] Starting Drive Straight. Distance1: %f Speed1 %f Distance2: %f Speed2: %f Timeout: %f", distance1, speed1, distance2, speed2, getTimeout());
	mobility->StartDriveDistance(distance1 + distance2, speed1);
}

void DriveDistanceTwoSpeed::process() {
	if(mobility->getDistanceError() <= distance2) {
		log->write(Log::INFO_LEVEL, "[Action] DriveDistanceTwoSpeed remaining error is %f, setting speed to %f", mobility->getDistanceError(), speed2);
		mobility->setDistancePIDOutputRange(-speed2, speed2);
	}
}

void DriveDistanceTwoSpeed::end() {
	mobility->stopDriveDistance();
	log->write(Log::INFO_LEVEL, "[Action] Drive Straight Two Speed Ended. Distance1: %f Speed1 %f Distance2: %f Speed2: %f Timeout: %f", distance1, speed1, distance2, speed2, getTimeout());
}

bool DriveDistanceTwoSpeed::isFinished() {
	return mobility->isDriveDistanceDone();
}
