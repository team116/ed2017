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
	frc::DriverStation::ReportError("Starting Drive Straight: " + std::to_string(distance) + "," + std::to_string(speed));
	mobility->StartDriveDistance(distance, speed);
}
void DriveStraight::process() {

}

void DriveStraight::end() {
	frc::DriverStation::ReportError("Ending Drive Straight: " + std::to_string(distance) + "," + std::to_string(speed));
	mobility->stopDriveDistance();
}
bool DriveStraight::isFinished() {
	return mobility->isDriveDistanceDone();
}

