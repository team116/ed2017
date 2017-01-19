/*
 * Shooter.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Shooter.h>
#include "Ports.h"

Shooter* Shooter::INSTANCE = nullptr;
const float AZIMUTH_ANGLE_TOLERANCE = 1.0;
const float AUTO_AZIMUTH_SPEED = 0.5;

Shooter::Shooter() {
	// TODO Auto-generated constructor stub
	ball_holder = new VictorSP(RobotPorts::MOTOR_SHOOTER_FEEDER);
	shooter = new VictorSP(RobotPorts::MOTOR_SHOOTER_WHEEL);
	azimuth = new VictorSP(RobotPorts::MOTOR_SHOOTER_AZIMUTH);
}

void Shooter::process() {

	float current_azimuth_angle = 0;

	float azimuth_angle_offset = target_azimuth_angle - current_azimuth_angle;

	if (azimuth_angle_offset > AZIMUTH_ANGLE_TOLERANCE) {
		azimuth->Set(AUTO_AZIMUTH_SPEED);
	}
	else if (azimuth_angle_offset > - AZIMUTH_ANGLE_TOLERANCE) {
		azimuth->Set(AUTO_AZIMUTH_SPEED);
	}
	else {
		azimuth->Set(0);
	}


}

void Shooter::setAngleDirection(float angle) {
	azimuth->Set(angle);
}

void Shooter::setSpeedAzimuth(float speed) {
	azimuth->Set(speed);
}

void Shooter::setSpeedShooter(float speed) {
	shooter->Set(speed);
}

Shooter* Shooter::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Shooter();
	}

	return INSTANCE;
}
