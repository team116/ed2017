/*
 * SetShooterSpeed.cpp
 *
 *  Created on: Mar 18, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/SetShooterSpeed.h>

SetShooterSpeed::SetShooterSpeed(float speed) {
	sped = speed;
	shooter = Shooter::getInstance();
}

void SetShooterSpeed::start() {
	shooter->setShooterSpeed(sped);
}

void SetShooterSpeed::process() {

}

void SetShooterSpeed::end() {

}

bool SetShooterSpeed::isFinished() {
	return true;
}
