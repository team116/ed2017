/*
 * Gear.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */


#include <Gear.h>
#include "Ports.h"

Gear* Gear::INSTANCE = nullptr;

Gear::Gear() {
	// TODO Auto-generated constructor stub
	gear_motor = Utils::constructMotor(RobotPorts::MOTOR_GEAR);
	LS_open = new frc::DigitalInput(RobotPorts::LS_GEAR_OPEN);
	LS_close = new frc::DigitalInput(RobotPorts::LS_GEAR_CLOSED);

	is_open = false;
}
void Gear::open() {
	gear_motor->Set(1.0);
	is_open = true;
}
void Gear::close() {
	gear_motor->Set(-1.0);
	is_open = false;
}
//numbers are subject to change
void Gear::process() {
	if (LS_open->Get()) {
		if (gear_motor->Get() > 0.0)
				gear_motor->Set(0.0);
	}
	if (LS_close->Get()) {
		if (gear_motor->Get() < 0.0)
			gear_motor->Set(0.0);
	}
}
bool Gear::isOpen() {
	return is_open;
}

Gear* Gear::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Gear();
	}

	return INSTANCE;
}
