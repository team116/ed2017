/*
 * Mobility.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Mobility.h>
#include "Ports.h"

Mobility* Mobility::INSTANCE = nullptr;
const float DRIVE_STRAIGHT_TOLERANCE = 5.0;
const float SPEED_ADJUSTMENT = 0.10;
static const float TURNING_SPEED = 5.0;

Mobility::Mobility() {
	front_left = new frc::VictorSP(RobotPorts::MOTOR_LEFT_FRONT);
	front_right = new frc::VictorSP(RobotPorts::MOTOR_RIGHT_FRONT);
	back_right = new frc::VictorSP(RobotPorts::MOTOR_RIGHT_BACK);
	back_left = new frc::VictorSP(RobotPorts::MOTOR_RIGHT_FRONT);
	gyro = new AHRS(SPI::kMXP);

	straight_speed = 0;
	acceptable_error = 0.5;
	current_angle = 0;
	degree_range = 0;
	degrees = 0;
	target_angle = 0;
	target_degree = 0;

	rotation_output = new MobilityRotationPID();
	rotation_PID = new frc::PIDController(1, 0, 0, gyro, rotation_output);
	rotation_PID->SetContinuous(true);
	rotation_PID->SetInputRange(-180, 180);
	rotation_PID->SetOutputRange(-1, 1);
	rotation_PID->SetPIDSourceType(PIDSourceType::kDisplacement);
	rotation_PID->SetAbsoluteTolerance(0.5);
	rotation_PID->Disable();
}

void Mobility::process() {

	if (turning_degrees) {
		processTurningDegrees();
	}

}

void Mobility::processTurningDegrees() {
	if (rotation_PID->OnTarget()) {
		rotation_PID->Disable();
		turning_degrees = false;
	}

}


void Mobility::startDriveStraight() {
	rotation_PID->SetSetpoint(gyro->GetRawGyroX());
	rotation_PID->Enable();
}

void Mobility::stopDriveStraight() {
	rotation_PID->Disable();
}

float Mobility::getStraightSpeed() {
	return straight_speed;
}
void Mobility::setStraightSpeed(float speed) {
	straight_speed = speed;
}

void Mobility::setLeft(float speed) {
	front_left->Set(speed);
	back_left->Set(speed);

}

void Mobility::setRight(float speed) {
	front_right->Set(speed);
	back_right->Set(speed);
}

void Mobility::setTurningDegrees(float degrees) {
	turning_degrees = true;

	gyro->Reset();
	rotation_PID->SetSetpoint(degrees);
	rotation_PID->Enable();
}

Mobility* Mobility::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Mobility();
	}

	return INSTANCE;
}
