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
	encoders = new MobilityEncoder();


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

	distance_output = new MobilityDistanceOutput(front_left, front_right, back_left, back_right);
	distance_PID = new frc::PIDController(0.1, 0, 0.0001, encoders, distance_output);
	distance_PID->Disable();
	distance_PID->SetContinuous(false);
	distance_PID->SetInputRange(0, 650);
	distance_PID->SetOutputRange(-1.0, 1.0);
	distance_PID->SetPIDSourceType(PIDSourceType::kDisplacement);
	distance_PID->SetAbsoluteTolerance(0.5);

}

void Mobility::process() {
	//DriverStation::ReportError("Gyro: " + std::to_string(gyro->PIDGet()));
	if (turning_degrees) {
		processTurningDegrees();
	}
	if(is_drive_distance_on) {
		processDistance();
	}

	//frc::DriverStation::ReportError("Left Encoder: " + std::to_string(encoders->getLeftEncoderRates()));
	//frc::DriverStation::ReportError("Right Encoder: " + std::to_string(encoders->getRightEncoderRates()));
}

void Mobility::processDistance() {
	if(distance_PID->OnTarget()) {
		disableDistancePID();
		is_drive_distance_on = false;
	}
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

//Drive Distance
void Mobility::StartDriveDistance(float distance) {
	is_drive_distance_on = true;
	encoders->DriveEncoderReset();
	distance_PID->SetSetpoint(distance);
	enableDistancePID();
}

bool Mobility::isDriveDistanceDone() {
	if(!is_drive_distance_on) {
	disableDistancePID();
	}
}

//Drive Straight
void Mobility::startDriveStraight() {
	driving_straight = true;
	frc::DriverStation::ReportError("Starting drive straight");
	frc::DriverStation::ReportError("Current gyro: " + std::to_string(gyro->GetYaw()));
	rotation_PID->SetSetpoint(gyro->GetYaw());
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

void Mobility::disableDistancePID() {
	distance_PID->Disable();
	distance_output->Disable();
}

void Mobility::enableDistancePID() {
	distance_PID->Enable();
	distance_output->Enable();
}

Mobility* Mobility::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Mobility();
	}

	return INSTANCE;
}
