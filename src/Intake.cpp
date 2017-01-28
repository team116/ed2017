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
	intake_motor = Utils::constructMotor(RobotPorts::MOTOR_INTAKE);
}

void Intake::process() {

}
float Intake::getSpeed() {
	return intake_motor->Get();
}
void Intake::setSpeedIntake(float speed) {
	intake_motor->Set(speed);
}

Intake* Intake::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Intake();
	}

	return INSTANCE;
}
