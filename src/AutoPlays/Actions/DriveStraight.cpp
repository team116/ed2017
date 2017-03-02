/*
 * DriveStraight.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/DriveStraight.h>
#include "Ports.h"

DriveStraight::DriveStraight(float dis, float s) {
	mobility = Mobility::getInstance();
	distance = dis;
	speed = fabs(s);

	setTimeout(fabs(dis) / 50 / speed);
}

void DriveStraight::start() {
	log->write(Log::INFO_LEVEL, "[Action] Starting Drive Straight. Distance: %f Speed %f Timeout: %f", distance, speed, getTimeout());
	mobility->StartDriveDistance(distance, speed);
}
void DriveStraight::process() {

}

void DriveStraight::end() {
	mobility->stopDriveDistance();
	log->write(Log::INFO_LEVEL, "[Action] Drive Straight Ended. Distance: %f Speed %f Timeout: %f", distance, speed, getTimeout());
}
bool DriveStraight::isFinished() {
	return mobility->isDriveDistanceDone();
}

