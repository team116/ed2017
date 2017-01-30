/*
 * MobilityEncoders.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: amanzeb
 */

#include <MobilityEncoder.h>
#include <Ports.h>

const float PULSE_PER_REV = 250;
const float WHEEL_DIAMETER = 7.5;

MobilityEncoder::MobilityEncoder() {
	left_drive_encoder = new frc::Encoder(RobotPorts::LEFT_DRIVE_ENCODER_1, RobotPorts::LEFT_DRIVE_ENCODER_2);
	right_drive_encoder = new frc::Encoder(RobotPorts::RIGHT_DRIVE_ENCODER_1, RobotPorts::RIGHT_DRIVE_ENCODER_2);

	left_drive_encoder->SetDistancePerPulse(3.14 * WHEEL_DIAMETER / (float) PULSE_PER_REV);
	right_drive_encoder->SetDistancePerPulse(3.14 * WHEEL_DIAMETER / (float) PULSE_PER_REV);

	pid_source = frc::PIDSourceType::kRate;
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
	return ((left_drive_encoder->GetDistance() + right_drive_encoder->GetDistance()) / 2);
}

void MobilityEncoder::DriveEncoderReset() {
	left_drive_encoder->Reset();
	right_drive_encoder->Reset();
}

frc::PIDSourceType MobilityEncoder::GetPIDSourceType() {
	return pid_source;
}



