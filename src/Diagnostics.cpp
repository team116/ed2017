/*
 * Diagnostics.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: Emina Ermin
 */

#include "Diagnostics.h"
#include "Ports.h"


Diagnostics* Diagnostics::INSTANCE = nullptr;

const int   ACCEL_VALUES_CUTOFF = 5;
const float ACCEL_THRESHOLD = 0.075;
const float LEFT_SPEED_THRESHOLD = 0.25;
const float RIGHT_SPEED_THRESHOLD = 0.25;
const float ENCODER_THRESHOLD = 0.01;
const float ENCODER_TIMEOUT = 0.1;
const float AZIMUTH_SHOOTER_RATE_THRESHOLD = 0;
const float AZIMUTH_SHOOTER_POWER_THRESHOLD = 0.25;
const float SHOOTER_RATE_THRESHOLD = 0;
const float SHOOTER_POWER_THRESHOLD = 0.1;
const float TEMPERATURE_THRESHOLD = 50;
const float LEFT_AZIMUTH_LIMIT = -170;
const float RIGHT_AZIMUTH_LIMIT = 170;
const float PDP_AZIMUTH_THRESHOLD = 7;



Diagnostics::Diagnostics() {
	// TODO Auto-generated constructor stub
	mobility = Mobility::getInstance();
	accel = new frc::BuiltInAccelerometer();
	left_enc_timer = new frc::Timer();
	right_enc_timer = new frc::Timer();
	accel_values = new Queue();
	shooter = Shooter::getInstance();
	log = Log::getInstance();

	left_enc_error_count = 0;
	right_enc_error_count = 0;
	pdp = new frc::PowerDistributionPanel();
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
					if(SmartDashboard::GetString("Left Mobility Encoder Status", "working") == "working") {
						SmartDashboard::PutString("Left Mobility Encoder Status", "error");
					}
					log->write(Log::WARNING_LEVEL, "Left mobility encoder error.");
				}
				else {
					if(SmartDashboard::GetString("Left Mobility Encoder Status", "error") == "error") {
						SmartDashboard::PutString("Left Mobility Encoder Status", "working");
					}
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
					if(SmartDashboard::GetString("Right Mobility Encoder Status", "working") == "working") {
						SmartDashboard::PutString("Right Mobility Encoder Status", "error");
					}
					log->write(Log::WARNING_LEVEL, "Right mobility encoder error. Current rate: %f", mobility->getRightEncoderRates());
				}
				else {
					if(SmartDashboard::GetString("Right Mobility Encoder Status", "error") =="error") {
						SmartDashboard::PutString("Right Mobility Encoder Status", "working");
					}
				}
				break;
			}
			else {
				right_enc_error_count = 0;
			}
		}
	}


	//Start of shooter azimuth diagnostics
	/*if ((fabs(shooter->getAzimuthSetValue())) > AZIMUTH_SHOOTER_POWER_THRESHOLD
			&& fabs(shooter->getAzimuthEncoderRate()) <= AZIMUTH_SHOOTER_RATE_THRESHOLD) {
		log->write(Log::WARNING_LEVEL, "Azimuth encoder broken");
	}*/ //BROKEN becyase encoder is now analog and doesnt give rate



	if ((fabs(shooter->getShooterSetValue())) > SHOOTER_POWER_THRESHOLD
		&& fabs(shooter->getShooterEncoderRate()) <= SHOOTER_RATE_THRESHOLD) {
		log->write(Log::WARNING_LEVEL, "Shooter encoder broken");
	}

	if (shooter->getAzimuthPosition() < LEFT_AZIMUTH_LIMIT || shooter->getAzimuthPosition() > RIGHT_AZIMUTH_LIMIT) {
		log->write(Log::WARNING_LEVEL, "Shooter azimuth out of bounds");
	}

	//Temperature
	if (mobility->getNavXTemperature() > TEMPERATURE_THRESHOLD) {
		log->write(Log::WARNING_LEVEL, "Warning! Box is getting hot. Current temperature: %f", mobility->getNavXTemperature());
	}


	if (pdp->GetCurrent(RobotPorts::AZIMUTH_MOTOR_PDP) > PDP_AZIMUTH_THRESHOLD) {
		log->write(Log::WARNING_LEVEL, "PDP azimuth current is too high. PDP azimuth current: %f", pdp->GetCurrent(RobotPorts::AZIMUTH_MOTOR_PDP));
	}
}

Diagnostics* Diagnostics::getInstance() {
	if (INSTANCE == nullptr) {
		INSTANCE = new Diagnostics();
	}

	return INSTANCE;
}

