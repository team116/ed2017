/*
 * Converter.cpp
 *
 *  Created on: Feb 5, 2017
 *      Author: Will
 */

#include "Converter.h"
#include "Ports.h"

Converter* Converter::INSTANCE = nullptr;

Converter::Converter() {
	is_open = false;
	servo_converter = new frc::Servo(RobotPorts::SERVO_CONVERTER);
}

void Converter::openServoConverter() {
	servo_converter->SetAngle(90);
	is_open = true;
}

void Converter::closeServoConverter() {
	servo_converter->SetAngle(0);
	is_open = false;
}

bool Converter::isOpen() {
	return is_open;
}

Converter* Converter::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Converter();
	}

	return INSTANCE;
}
