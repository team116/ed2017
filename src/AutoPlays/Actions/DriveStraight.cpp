/*
 * DriveStraight.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/DriveStraight.h>

DriveStraight::DriveStraight() {
	mobility = Mobility::getInstance();
}

void DriveStraight::start() {
	mobility->StartDriveDistance(118.0);
}
void DriveStraight::process() {

}

void DriveStraight::end() {

}
bool DriveStraight::isFinished() {
	return mobility->isDriveDistanceDone();
}

