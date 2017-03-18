/*
 * DriveToGearVision.cpp
 *
 *  Created on: Mar 15, 2017
 *      Author: Will
 */

#include <AutoPlays/Actions/DriveToGearVision.h>

const float SPEED1 = 0.35;
const float SPEED2 = 0.2;
const float SLOW_DISTANCE = 48.0;
const float STOP_DISTANCE = 22.0;

DriveToGearVision::DriveToGearVision() {
	// TODO Auto-generated constructor stub
	mobility = Mobility::getInstance();
	vision = Vision::getInstance();

	setTimeout(5.0);
}

void DriveToGearVision::start() {
	mobility->startTrackGear();
	if(vision->gearHookDistance() > SLOW_DISTANCE) {
		frc::DriverStation::ReportError("Speed 1");
		mobility->setStraightSpeed(SPEED1);
	}
	else {
		frc::DriverStation::ReportError("Speed 2");
		mobility->setStraightSpeed(SPEED2);
	}
}

void DriveToGearVision::process() {
	if((vision->gearHookDistance() <= SLOW_DISTANCE) && (mobility->getStraightSpeed() != SPEED2)) {
		frc::DriverStation::ReportError("Changing to speed 2");
		mobility->setStraightSpeed(SPEED2);
	}
}

bool DriveToGearVision::isFinished() {
	return ((vision->gearHookDistance() <= STOP_DISTANCE) && (vision->gearHookDistance() >= 0.0));
}

void DriveToGearVision::end() {
	mobility->stopTrackGear();
	mobility->setStraightSpeed(0.0);
	mobility->setLeft(0.0);
	mobility->setRight(0.0);
}
