/*
 * Mobility.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Mobility.h>
#include "Ports.h"

Mobility* Mobility::INSTANCE = nullptr;
const float DRIVE_STRAIGHT_TOLERANCE = 5.0;
const float SPEED_ADJUSTMENT = 0.10;
static const float TURNING_SPEED = 5.0;

Mobility::Mobility() {
	front_left = new VictorSP(RobotPorts::MOTOR_LEFT_FRONT);
	front_right = new VictorSP(RobotPorts::MOTOR_RIGHT_FRONT);
	back_right = new VictorSP(RobotPorts::MOTOR_RIGHT_BACK);
	back_left = new VictorSP(RobotPorts::MOTOR_RIGHT_FRONT);
	gyro = new AnalogGyro(11);
	straight_speed = 0;
	acceptable_error = 0.5;
	current_angle = 0;
	degree_range=0;
	degrees=0;
	starting_degree=0;
	target_angle=0;
	target_degree=0;

}

void Mobility::process() {
	processDriveStraight();
	processTurningDegrees();

}

void Mobility::processTurningDegrees() {
	if (target_degree < -180 || (target_degree > 180 && target_degree > 0.0)) {
		setLeft(-TURNING_SPEED);
		setRight(TURNING_SPEED);
	}
	else {
		setLeft(TURNING_SPEED);
		setRight(-TURNING_SPEED);
	}
}

void Mobility::processDriveStraight() {
	float current_angle = gyro->GetAngle();

	float angle_offset = target_angle - current_angle;

	if (angle_offset > DRIVE_STRAIGHT_TOLERANCE) {
		// Too far to the right, need to turn left
		setLeft(straight_speed - SPEED_ADJUSTMENT);
		setRight(straight_speed + SPEED_ADJUSTMENT);
	}
	else if (angle_offset < -DRIVE_STRAIGHT_TOLERANCE) {
		// Too far to the left, need to turn right
		setLeft(straight_speed + SPEED_ADJUSTMENT);
		setRight(straight_speed - SPEED_ADJUSTMENT);
	}
	else {
		setLeft(SPEED_ADJUSTMENT);
		setRight(SPEED_ADJUSTMENT);
	}
}

void Mobility::setAngle(float angle) {
	target_angle = angle;
}

void Mobility::setStraightSpeed(float speed) {
	straight_speed = speed;

}

void Mobility::setLeft(float speed) {
	front_left->Set(speed);
	back_left->Set(speed);

}

void Mobility::setRight(float speed) {
	front_right->Set(speed);
	back_right->Set(speed);
}

void Mobility::setTurningDegrees(float degrees) {
	current_angle = degrees;

	target_degree = starting_degree + degrees;
}

Mobility* Mobility::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Mobility();
	}

	return INSTANCE;
}
