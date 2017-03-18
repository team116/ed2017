/*
 * MobilityRotationPID.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: Emina Ermin
 */

#include "MobilityRotationPID.h"
#include <DriverStation.h>
#include <networktables/NetworkTable.h>

MobilityRotationPID::MobilityRotationPID(frc::SpeedController* fl, frc::SpeedController* fr, frc::SpeedController* bl,
		frc::SpeedController* br) {
	forward = 0.0;
	front_left = fl;
	front_right = fr;
	back_left = bl;
	back_right = br;

	enabled = false;
}

void MobilityRotationPID::setForwardSpeed(float speed) {
	forward = speed;
}

void MobilityRotationPID::Enable() {
	enabled = true;
}

void MobilityRotationPID::Disable() {
	enabled = false;
}

void MobilityRotationPID::PIDWrite(double output) {
	if(!enabled) {
		return;
	}

	float leftSpeed = forward + output;
	float rightSpeed = forward - output;

	//frc::DriverStation::ReportError("Rotation Output: " + std::to_string(output) + " Left: " + std::to_string(leftSpeed) + " Right: " + std::to_string(rightSpeed));
	NetworkTable::GetTable("Status/Mobility")->PutNumber("Rotation Output Raw", output);
	NetworkTable::GetTable("Status/Mobility")->PutNumber("Rotation Output Left", leftSpeed);
	NetworkTable::GetTable("Status/Mobility")->PutNumber("Rotation Output Right", rightSpeed);

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

	front_left->Set(leftSpeed);
	back_left->Set(leftSpeed);

	front_right->Set(rightSpeed);
	back_right->Set(rightSpeed);
}
