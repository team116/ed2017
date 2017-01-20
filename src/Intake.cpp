/*
 * Intake.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Intake.h>
#include "Ports.h"

Intake* Intake::INSTANCE = nullptr;

Intake::Intake() {
	// TODO Auto-generated constructor stub
	intake_motor = new frc::VictorSP(RobotPorts::MOTOR_INTAKE);
}

void Intake::process() {

}

void Intake::setSpeedIntake(float speed) {
	intake_motor->Set(1.0);
}

Intake* Intake::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Intake();
	}

	return INSTANCE;
}
