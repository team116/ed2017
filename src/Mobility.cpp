/*
 * Mobility.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Mobility.h>

Mobility* Mobility::INSTANCE = nullptr;
const float DRIVE_STRAIGHT_TOLERANCE = 5.0;
const float SPEED_ADJUSTMENT = 0.10;

Mobility::Mobility() {
	front_left = new VictorSP(0);
	front_right = new VictorSP(1);
	back_right = new VictorSP(2);
	back_left = new VictorSP(3);
	gyro = new AnalogGyro(11);
	straight_speed = 0;
	target_angle = 0;
}

void Mobility::process() {

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

Mobility* Mobility::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Mobility();
	}

	return INSTANCE;
}
