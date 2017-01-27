/*
 * Diagnostics.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: Emina Ermin
 */

#include "Diagnostics.h"

Diagnostics* Diagnostics::INSTANCE = nullptr;

const float ACCEL_THRESHOLD = 0.075;
const float LEFT_SPEED_THRESHOLD = 0.25;
const float RIGHT_SPEED_THRESHOLD = 0.25;
const float ENCODER_THRESHOLD = 0.01;
const float ENCODER_TIMEOUT = 0.1;
Diagnostics::Diagnostics() {
	// TODO Auto-generated constructor stub
	mobility = Mobility::getInstance();
	accel = new frc::BuiltInAccelerometer();
	left_enc_timer = new frc::Timer();
	right_enc_timer = new frc::Timer();

}

void Diagnostics::process() {
	mobility->getLeftEncoderRates();
	mobility->getRightEncoderRates();

	frc::DriverStation::ReportError("Accel: " + std::to_string(accel->GetX()) + " Rate: "
			+ std::to_string(fabs(mobility->getLeftEncoderRates())) + " Set: "
			+ std::to_string(fabs(mobility->getLeftSetValue()))
			+ " Timer: " + std::to_string(left_enc_timer->Get()));

	if ((fabs(accel->GetX()) > ACCEL_THRESHOLD) && (fabs(mobility->getLeftSetValue()) > LEFT_SPEED_THRESHOLD)
			&& (fabs(mobility->getLeftEncoderRates()) < ENCODER_THRESHOLD)) {
		frc::DriverStation::ReportError("Starting timer");
		left_enc_timer->Start();
	}
	else {
		frc::DriverStation::ReportError("Stopping timer");
		left_enc_timer->Stop();
		left_enc_timer->Reset();
	}
	if (left_enc_timer->HasPeriodPassed(ENCODER_TIMEOUT)) {
		// Left encoder broken
		frc::DriverStation::ReportError("Left Encoder Malfunctioning: "
				+ std::to_string(accel->GetX()) + " + "
				+ std::to_string(mobility->getLeftEncoderRates()));
	}
	if ((fabs(accel->GetX()) > ACCEL_THRESHOLD) && (fabs(mobility->getRightSetValue()) > RIGHT_SPEED_THRESHOLD)
			&& fabs(mobility->getRightEncoderRates()) < ENCODER_THRESHOLD) {
		right_enc_timer->Start();
	}
	else {
		right_enc_timer->Stop();
		right_enc_timer->Reset();
	}
	if (right_enc_timer->HasPeriodPassed(ENCODER_TIMEOUT)) {
		//Right encoder broken
		frc::DriverStation::ReportError("Right Encoder Malfunctioning: "
				+ std::to_string(accel->GetX()) + " + "
				+ std::to_string(mobility->getRightEncoderRates()));
	}
}

Diagnostics* Diagnostics::getInstance() {
	if (INSTANCE == nullptr) {
		INSTANCE = new Diagnostics();
	}

	return INSTANCE;
}

