/*
 * AzimuthEncoder.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: Emina Ermin
 */

#include <AzimuthEncoder.h>
#include <Ports.h>
#include <DriverStation.h>

const float UPPER_ANGLE = 310;
const float LOWER_ANGLE = 50;
const float ROT_PER_360 = 8.7777;

AzimuthEncoder::AzimuthEncoder() {
	// TODO Auto-generated constructor stub
	prev_angle = 0;
	full_rotations = 0;
	//pot = new frc::AnalogPotentiometer(RobotPorts::AZIMUTH_ENCODER, 360, 0);

	angle_offset = 0.0;

	reset();
}

void AzimuthEncoder::process() {
	frc::DriverStation::ReportError("Prev: " + std::to_string(prev_angle) + " Now: " + std::to_string(pot->Get()));
	if ((prev_angle > UPPER_ANGLE) && (pot->Get() < LOWER_ANGLE)) {
		frc::DriverStation::ReportError("Adding rotation");
		full_rotations++;
	}

	if ((prev_angle < LOWER_ANGLE) && (pot->Get() > UPPER_ANGLE)) {
		frc::DriverStation::ReportError("Subtracting rotation");
		full_rotations--;
	}

	prev_angle = pot->Get();
}


float AzimuthEncoder::getAngle() {
	return ((full_rotations / ROT_PER_360 * 360) + (pot->Get() / 5)) - angle_offset;
}

void AzimuthEncoder::reset() {
	angle_offset += getAngle();
}

double AzimuthEncoder::PIDGet() {
	return getAngle();
}
