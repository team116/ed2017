/*
 * AimShooterManual.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/AimShooterManual.h>

AimShooterManual::AimShooterManual(float speed) {
	shooter = Shooter::getInstance();
	setTimeout (10.0);
}
void AimShooterManual::start() {
	shooter->setShooterSpeed(speed);
}
void AimShooterManual::process() {

}
void AimShooterManual::end() {

}
bool AimShooterManual::isFinished() {

}
