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
	climber_left = Utils::constructMotor(RobotPorts::MOTOR_CLIMBER_LEFT);
	climber_right = Utils::constructMotor(RobotPorts::MOTOR_CLIMBER_RIGHT);
}

void Climber::process() {

}

void Climber::moveClimber(float speed) {
	climber_left->Set(speed);
	climber_right->Set(-speed);
}
float Climber::getSpeed() {
	return climber_left->Get();
}

Climber* Climber::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Climber();
	}

	return INSTANCE;
}
