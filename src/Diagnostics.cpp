/*
 * Diagnostics.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: Emina Ermin
 */

#include "Diagnostics.h"

const float ACCEL_THRESHOLD = 0.01;
const float LEFT_SPEED_THRESHOLD = 0.25;
const float RIGHT_SPEED_THRESHOLD = 0.25;
const float ENCODER_THRESHOLD = 0.01;

Diagnostics::Diagnostics() {
	// TODO Auto-generated constructor stub
	mobility = Mobility::getInstance();
	accel = new frc::BuiltInAccelerometer();

}

void Diagnostics::process() {
	mobility->getLeftEncoderRates();
	mobility->getRightEncoderRates();

	if ((fabs(accel->GetX()) > ACCEL_THRESHOLD) && (fabs(mobility->getLeftSetValue()) > LEFT_SPEED_THRESHOLD)) {
		if (fabs(mobility->getLeftEncoderRates()) < ENCODER_THRESHOLD) {
			// Left encoder broken
			frc::DriverStation::ReportError("Left Encoder Malfunctioning");
		}
	if ((fabs(accel->GetX()) > ACCEL_THRESHOLD) && (fabs(mobility->getRightSetValue()) > RIGHT_SPEED_THRESHOLD)) {
		if (fabs(mobility->getRightEncoderRates()) < ENCODER_THRESHOLD) {
			// Right encoder broken
			frc::DriverStation::ReportError("Right Encoder Malfunctioning");
		}
	}
	}
}



