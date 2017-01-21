/*
 * MobilityRotationPID.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: Emina Ermin
 */

#include "MobilityRotationPID.h"

MobilityRotationPID::MobilityRotationPID() {
	forward = 0.0;
}

void MobilityRotationPID::PIDWrite(double output) {
	forward = Mobility::getInstance()->getStraightSpeed();

	float leftSpeed = forward + output;
	float rightSpeed = forward - output;

	if (leftSpeed > 1.0) {
		leftSpeed = 1.0;
	}
	else if (leftSpeed < -1.0) {
		leftSpeed = -1.0;
	}

	if (rightSpeed > 1.0) {
		rightSpeed = 1.0;
	}
	else if (rightSpeed < -1.0) {
		rightSpeed = -1.0;
	}

	Mobility::getInstance()->setLeft(output);
	Mobility::getInstance()->setRight(-output);
}
