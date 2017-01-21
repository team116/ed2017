/*
 * Mobility.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Mobility.h>
#include "Ports.h"

Mobility* Mobility::INSTANCE = nullptr;

Mobility::Mobility() {
	//Motor Controllers
	front_left = Utils::constructMotor(RobotPorts::MOTOR_LEFT_FRONT);
	front_right = Utils::constructMotor(RobotPorts::MOTOR_RIGHT_FRONT);
	back_right = Utils::constructMotor(RobotPorts::MOTOR_RIGHT_BACK);
	back_left = Utils::constructMotor(RobotPorts::MOTOR_RIGHT_FRONT);

	//Sensors
	gyro = new AHRS(SPI::kMXP);

	//Initialize class variables to default value
	straight_speed = 0.0;
	turning_degrees = false;

	//PID controllers
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

void Mobility::turnDegrees(float degrees) {
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
