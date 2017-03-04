/*
 * Feeder.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: carty
 */

#include <Feeder.h>
#include "Ports.h"
#include <DriverStation.h>

Feeder* Feeder::INSTANCE = nullptr;

const float AGITATOR_PERIOD = 0.5;
const float AGITATOR_ANGLE_HIGH = 100.0;
const float AGITATOR_ANGLE_LOW = 80.0;

Feeder::Feeder() {
	feeder = Utils::constructMotor(RobotPorts::MOTOR_SHOOTER_FEEDER);
	blender = Utils::constructMotor(RobotPorts::MOTOR_BLENDER);

	alligator = new frc::Servo(RobotPorts::SERVO_AGITATOR);//agitator

	alligator_timer = new frc::Timer();
	run_alligator = false;
	alligator_high = false;
}

void Feeder::process() {
	if(run_alligator) {
		if(alligator_timer->Get() >= AGITATOR_PERIOD) {
			//frc::DriverStation::ReportError("Flipping alligator");
			if(alligator_high) {
				alligator->SetAngle(AGITATOR_ANGLE_LOW);
				alligator_high = false;
			}
			else {
				alligator->SetAngle(AGITATOR_ANGLE_HIGH);
				alligator_high = true;
			}

			alligator_timer->Reset();
			alligator_timer->Start();
		}
	}
}

void Feeder::setFeederSpeed(float speed){
	feeder->Set(-speed);
}

void Feeder::setBlenderSpeed(float speed){
	blender->Set(-speed);

	if((speed != 0.0) && !run_alligator) {
		run_alligator = true;
		alligator_timer->Reset();
		alligator_timer->Start();
		//frc::DriverStation::ReportError("Starting alligator");
	}
	else if((speed == 0) && run_alligator) {
		run_alligator = false;
		alligator_timer->Stop();
		alligator_timer->Reset();
		alligator_timer->Stop();
		//frc::DriverStation::ReportError("Stopping alligator");
	}
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
