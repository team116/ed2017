/*
 * Climber.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Climber.h>
#include "Ports.h"

Climber* Climber::INSTANCE = nullptr;

Climber::Climber() {
	climber = Utils::constructMotor(RobotPorts::MOTOR_CLIMBER);
}

void Climber::process() {

}

void Climber::moveClimber(float speed) {
	climber->Set(speed);
}
float Climber::getSpeed() {
	return climber->Get();
}

Climber* Climber::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Climber();
	}

	return INSTANCE;
}
