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
	climber = new frc::VictorSP(RobotPorts::MOTOR_CLIMBER);
}

void Climber::process() {

}

void Climber::moveClimber(float speed) {
	climber->Set(speed);
}
/*void Climber::climbUp(float speed) {
	climber->Set(1.0);
}

void Climber::climbDown(float speed) {
	climber->Set(-1.0);
}

void Climber::climbStop(float speed) {
	climber->Set(0.0);
} */

Climber* Climber::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Climber();
	}

	return INSTANCE;
}
