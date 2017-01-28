/*
 * Diagnostics.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: Emina Ermin
 */

#include "Diagnostics.h"

Diagnostics* Diagnostics::INSTANCE = nullptr;

const int   ACCEL_VALUES_CUTOFF = 5;
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
	accel_values = new Queue();

	left_enc_error_count = 0;
	right_enc_error_count = 0;
}

void Diagnostics::process() {
	mobility->getLeftEncoderRates();
	mobility->getRightEncoderRates();
	if ((fabs(accel->GetX())) > ACCEL_THRESHOLD) {
		accel_values->Push(1);
	}
	else {
		accel_values->Push(0);
	}

	char text [255];
	snprintf(text, 255, "[%d,%d,%d,%d,%d,%d,%d,%d,%d,%d] LeftSpeed: %f LeftRate: %f Count: %d RightSpeed: %f RightRate: %f Count: %d",
			accel_values->Get(0),
			accel_values->Get(1),
			accel_values->Get(2),
			accel_values->Get(3),
			accel_values->Get(4),
			accel_values->Get(5),
			accel_values->Get(6),
			accel_values->Get(7),
			accel_values->Get(8),
			accel_values->Get(9),
			fabs(mobility->getLeftSetValue()),
			fabs(mobility->getLeftEncoderRates()),
			left_enc_error_count,
			fabs(mobility->getRightSetValue()),
			fabs(mobility->getRightEncoderRates()),
			right_enc_error_count);
	// frc::DriverStation::ReportError(text);

	for (int i = ACCEL_VALUES_CUTOFF; i < accel_values->Size(); i++) {
		if (accel_values->Get(i) == 1) {
			if ((fabs(mobility->getLeftSetValue()) > LEFT_SPEED_THRESHOLD)
				&& (fabs(mobility->getLeftEncoderRates()) < ENCODER_THRESHOLD)) {
				left_enc_error_count++;
				if (left_enc_error_count > 2) {
					frc::DriverStation::ReportError("Left mobility encoder error.");
				}
				break;
			}
			else {
				left_enc_error_count = 0;
			}

			if ((fabs(mobility->getRightSetValue()) > RIGHT_SPEED_THRESHOLD)
				&& (fabs(mobility->getRightEncoderRates()) < ENCODER_THRESHOLD)) {
				right_enc_error_count++;
				if (right_enc_error_count > 2) {
					frc::DriverStation::ReportError("Right mobility encoder error.");
				}
				break;
			}
			else {
				right_enc_error_count = 0;
			}
		}
	}

	/*frc::DriverStation::ReportError("Accel: " + std::to_string(accel->GetX()) + " Rate: "
			+ std::to_string(fabs(mobility->getLeftEncoderRates())) + " Set: "
			+ std::to_string(fabs(mobility->getLeftSetValue()))
			+ " Timer: " + std::to_string(left_enc_timer->Get()));*/

	/*if ((fabs(accel->GetX()) > ACCEL_THRESHOLD) && (fabs(mobility->getLeftSetValue()) > LEFT_SPEED_THRESHOLD)
			&& (fabs(mobility->getLeftEncoderRates()) < ENCODER_THRESHOLD)) {
		//frc::DriverStation::ReportError("Starting timer");
		left_enc_timer->Start();
	}
	else {
		//frc::DriverStation::ReportError("Stopping timer");
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
	} */
}

Diagnostics* Diagnostics::getInstance() {
	if (INSTANCE == nullptr) {
		INSTANCE = new Diagnostics();
	}

	return INSTANCE;
}

