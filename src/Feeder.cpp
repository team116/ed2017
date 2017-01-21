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
	feeder = new frc::VictorSP(RobotPorts::MOTOR_SHOOTER_FEEDER);
}

Feeder* Feeder::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Feeder();
	}

	return INSTANCE;
}
