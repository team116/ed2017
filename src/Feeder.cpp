/*
 * Feeder.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: carty
 */

#include <Feeder.h>
#include "Ports.h"

Feeder* Feeder::INSTANCE = nullptr;

Feeder::Feeder() {
	feeder = Utils::constructMotor(RobotPorts::MOTOR_SHOOTER_FEEDER);
	blender = Utils::constructMotor(RobotPorts::MOTOR_BLENDER);
}

void Feeder::setFeederSpeed(float speed){
	feeder->Set(speed);
}

void Feeder::setBlenderSpeed(float speed){
	blender->Set(speed);
}
float Feeder::getSpeed() {
	return feeder->Get();
}

Feeder* Feeder::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Feeder();
	}

	return INSTANCE;
}
