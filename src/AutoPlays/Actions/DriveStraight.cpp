/*
 * DriveStraight.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/DriveStraight.h>
#include "Ports.h"

DriveStraight::DriveStraight(float dis, float s, float ultrasonic_distance) {
	mobility = Mobility::getInstance();
	distance = dis;
	speed = fabs(s);

	ultrasonic = ultrasonic_distance;

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
	if((ultrasonic >= 0.0) && mobility->isFrontDistanceValid()) {
		if(mobility->getFrontDistance() <= ultrasonic) {
			frc::DriverStation::ReportError("Ultrasonic is true, " + std::to_string(mobility->getFrontDistance()));
		}
		return mobility->isDriveDistanceDone() || (mobility->getFrontDistance() <= ultrasonic);
	}
	else {
		return mobility->isDriveDistanceDone();
	}
}

