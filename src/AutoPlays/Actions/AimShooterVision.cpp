/*
 * AimShooterVision.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/AimShooterVision.h>

AimShooterVision::AimShooterVision() {
	vision = Vision::getInstance();
	shooter = Shooter::getInstance();

	setTimeout(3.0);
}
void AimShooterVision::start() {
	shooter->startAzimuthVisionTrack();
}
void AimShooterVision::process() {		//can be a process to look for shooter

}
void AimShooterVision::end() {
	shooter->stopAzimuthVisionTrack();
}
bool AimShooterVision::isFinished() {		//bool for isfinished could be offsets (1 and -1)
	return shooter->isAzimuthVisionOnTarget();
}
