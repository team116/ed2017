/*
 * Gear.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */


#include <Gear.h>
#include "Ports.h"

Gear* Gear::INSTANCE = nullptr;
const float Gear::LEFT_CLOSED_ANGLE = 0.0;
const float Gear::LEFT_OPEN_ANGLE = 30.0;
const float Gear::RIGHT_CLOSED_ANGLE = 360.0;
const float Gear::RIGHT_OPEN_ANGLE = 270.0;

Gear::Gear() {
	// TODO Auto-generated constructor stub
	servo_left = new Servo(RobotPorts::SERVO_GEAR_LEFT);
	servo_right = new Servo(RobotPorts::SERVO_GEAR_RIGHT);
}

void Gear::openLeft() {
	servo_left->SetAngle(LEFT_OPEN_ANGLE);
}

void Gear::closeLeft() {
	servo_left->SetAngle(LEFT_CLOSED_ANGLE);
}

void Gear::openRight() {
	servo_right->SetAngle(RIGHT_OPEN_ANGLE);
}

void Gear::closeRight() {
	servo_right->SetAngle(RIGHT_CLOSED_ANGLE);
}

void Gear::process() {

}

Gear* Gear::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Gear();
	}

	return INSTANCE;
}
