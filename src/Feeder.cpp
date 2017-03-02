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

	alligator = new frc::Servo(RobotPorts::SERVO_AGITATOR);//agitator
}

void Feeder::setFeederSpeed(float speed){
	feeder->Set(-speed);
}

void Feeder::setBlenderSpeed(float speed){
	blender->Set(-speed);
}
float Feeder::getFeederSpeed() {
	return -feeder->Get();
}
float Feeder::getBlenderSpeed() {
	return -blender->Get();
}

void Feeder::setAgitatorAngle(float angle) {
	alligator->SetAngle(angle);
}

float Feeder::getAgitatorAngle() {
	return alligator->GetAngle();
}

Feeder* Feeder::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Feeder();
	}

	return INSTANCE;
}
