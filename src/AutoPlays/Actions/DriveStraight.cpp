/*
 * DriveStraight.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/DriveStraight.h>

DriveStraight::DriveStraight(float dis) {
	mobility = Mobility::getInstance();
	distance = dis;
}

void DriveStraight::start() {
	mobility->StartDriveDistance(distance);
}
void DriveStraight::process() {

}

void DriveStraight::end() {

}
bool DriveStraight::isFinished() {
	return mobility->isDriveDistanceDone();
}

