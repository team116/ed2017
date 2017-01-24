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
}

void Feeder::setFeederSpeed(float speed){
	feeder->Set(speed);
}

Feeder* Feeder::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Feeder();
	}

	return INSTANCE;
}