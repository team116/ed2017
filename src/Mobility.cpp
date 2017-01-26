/*
 * Mobility.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Mobility.h>
#include "Ports.h"

Mobility* Mobility::INSTANCE = nullptr;

int Mobility::counter = 0;

Mobility::Mobility() {
	//Motor Controllers
	front_left = Utils::constructMotor(RobotPorts::MOTOR_LEFT_FRONT);
	front_right = Utils::constructMotor(RobotPorts::MOTOR_RIGHT_FRONT);
	back_right = Utils::constructMotor(RobotPorts::MOTOR_RIGHT_BACK);
	back_left = Utils::constructMotor(RobotPorts::MOTOR_LEFT_BACK);

	front_right->SetInverted(true);
	back_right->SetInverted(true);

	//Sensors
	gyro = new AHRS(SPI::Port::kMXP);
	encoders = new MobilityEncoders();


	//Initialize class variables to default value
	straight_speed = 0.0;
	turning_degrees = false;
	driving_straight = false;


	//PID controllers
	rotation_output = new MobilityRotationPID(front_left, front_right, back_left, back_right);
	rotation_output->Disable();
	rotation_PID = new frc::PIDController(0.03, 0.0001, 0.1, gyro, rotation_output);
	rotation_PID->Disable();
	rotation_PID->SetContinuous(true);
	rotation_PID->SetInputRange(-180, 180);
	rotation_PID->SetOutputRange(-1, 1);
	rotation_PID->SetPIDSourceType(PIDSourceType::kDisplacement);
	rotation_PID->SetAbsoluteTolerance(0.5);

	straight_output = new MobilityStraightOutput(front_left, front_right, back_left, back_right);
	straight_PID = new frc::PIDController(0.1, 0, 0.0001, encoders, straight_output);
	straight_PID->Disable();
	straight_PID->SetContinuous(false);
	straight_PID->SetInputRange(0, 650);
	straight_PID->SetOutputRange(-1.0, 1.0);
	straight_PID->SetPIDSourceType(PIDSourceType::kDisplacement);
	straight_PID->SetAbsoluteTolerance(0.5);

}

void Mobility::process() {
	// DriverStation::ReportError("Gyro: " + std::to_string(gyro->PIDGet()));
	if (turning_degrees) {
		processTurningDegrees();
	}

	DriverStation::ReportError("Left Encoder: " + std::to_string(encoders->getLeftEncoderRates()));
	DriverStation::ReportError("Right Encoder: " + std::to_string(encoders->getRightEncoderRates()));
}

void Mobility::processTurningDegrees() {
	if (rotation_PID->OnTarget()) {
		disableRotationPID();
		turning_degrees = false;
	}
}

float Mobility::getLeftEncoderRates() {
	return encoders->getLeftEncoderRates();
}

float Mobility::getRightEncoderRates() {
	return encoders->getRightEncoderRates();
}

float Mobility::getLeftSetValue() {
	return front_left->Get();
}

float Mobility::getRightSetValue() {
	return front_right->Get();
}

void Mobility::DriveDistance(float distance)
{
	straight_PID->SetSetpoint(distance);

}

//Drive Straight
void Mobility::startDriveStraight() {
	driving_straight = true;
	DriverStation::ReportError("Starting drive straight");
	rotation_PID->SetSetpoint(gyro->GetAngle());
	enableRotationPID();
}
bool Mobility::isDrivingStraight() {
	return driving_straight;
}
void Mobility::stopDriveStraight() {
	disableRotationPID();
	driving_straight = false;
}

float Mobility::getStraightSpeed() {
	return straight_speed;
}
void Mobility::setStraightSpeed(float speed) {
	straight_speed = speed;
	rotation_output->setForwardSpeed(speed);
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
	enableRotationPID();
}

void Mobility::disableRotationPID() {
	rotation_output->Disable();
	rotation_PID->Disable();
}

void Mobility::enableRotationPID() {
	rotation_output->Enable();
	rotation_PID->Enable();
}

Mobility* Mobility::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Mobility();
	}

	return INSTANCE;
}
