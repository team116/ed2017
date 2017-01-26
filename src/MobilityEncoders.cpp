/*
 * MobilityEncoders.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: amanzeb
 */

#include <MobilityEncoders.h>
#include <Ports.h>

MobilityEncoders::MobilityEncoders() {
	left_drive_encoder = new Encoder(RobotPorts::LEFT_DRIVE_ENCODER_1, RobotPorts::LEFT_DRIVE_ENCODER_2);
	right_drive_encoder = new Encoder(RobotPorts::RIGHT_DRIVE_ENCODER_1, RobotPorts::RIGHT_DRIVE_ENCODER_2);

	left_drive_encoder->SetDistancePerPulse(3.14 * 7.5 / (float) pulseperdistance);
	right_drive_encoder->SetDistancePerPulse(3.14 * 7.5 / (float) pulseperdistance);
}

void MobilityEncoders::SetPIDSourceType(frc::PIDSourceType source) {
	pid_source = source;
}

float MobilityEncoders::getLeftEncoderRates() {
	return left_drive_encoder->GetRate();
}

float MobilityEncoders::getRightEncoderRates() {
	return right_drive_encoder->GetRate();
}

double MobilityEncoders::PIDGet() {
	return ((left_drive_encoder->GetDistance() + right_drive_encoder->GetDistance()) / 2);
}

void MobilityEncoders::DriveEncoderReset() {
	left_drive_encoder->Reset();
	right_drive_encoder->Reset();
}

frc::PIDSourceType MobilityEncoders::GetPIDSourceType() {
	return pid_source;
}



