/*
 * MobilityEncoders.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: amanzeb
 */

#include <MobilityEncoder.h>
#include <Ports.h>
#include <DriverStation.h>

const float PULSE_PER_REV = 250;
const float WHEEL_DIAMETER = 7.5;

MobilityEncoder::MobilityEncoder() {
	log = Log::getInstance();

	left_drive_encoder = new frc::Encoder(RobotPorts::LEFT_DRIVE_ENCODER_1, RobotPorts::LEFT_DRIVE_ENCODER_2);
	right_drive_encoder = new frc::Encoder(RobotPorts::RIGHT_DRIVE_ENCODER_1, RobotPorts::RIGHT_DRIVE_ENCODER_2);

	left_drive_encoder->SetDistancePerPulse(3.14 * WHEEL_DIAMETER / (float) PULSE_PER_REV);
	right_drive_encoder->SetDistancePerPulse(3.14 * WHEEL_DIAMETER / (float) PULSE_PER_REV);

	pid_source = frc::PIDSourceType::kRate;

	use_left_enc = true;
	use_right_enc = true;
}

void MobilityEncoder::SetPIDSourceType(frc::PIDSourceType source) {
	pid_source = source;
}

float MobilityEncoder::getLeftEncoderRates() {
	return left_drive_encoder->GetRate();
}

float MobilityEncoder::getRightEncoderRates() {
	return right_drive_encoder->GetRate();
}

double MobilityEncoder::PIDGet() {
	if(use_left_enc && use_right_enc)
		return ((left_drive_encoder->GetDistance() + right_drive_encoder->GetDistance()) / 2);
	else if(use_left_enc && !use_right_enc)
		return left_drive_encoder->GetDistance();
	else if(!use_left_enc && use_right_enc)
		return right_drive_encoder->GetDistance();
	else {
		log->write(Log::WARNING_LEVEL, "All encoders disabled, can't return PIDGet");
		return 0.0;
	}
}

void MobilityEncoder::DriveEncoderReset() {
	left_drive_encoder->Reset();
	right_drive_encoder->Reset();
}

void MobilityEncoder::enableLeftEncoder() {
	use_left_enc = true;
}

void MobilityEncoder::disableLeftEncoder() {
	use_left_enc = false;
}

bool MobilityEncoder::isLeftEncoderEnabled() {
	return use_left_enc;
}

void MobilityEncoder::enableRightEncoder() {
	use_right_enc = true;
}

void MobilityEncoder::disableRightEncoder() {
	use_right_enc = false;
}

bool MobilityEncoder::isRightEncoderEnabled() {
	return use_right_enc;
}

frc::PIDSourceType MobilityEncoder::GetPIDSourceType() {
	return pid_source;
}



