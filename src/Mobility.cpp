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
	is_drive_distance_on = false;


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

	//LiveWindow::GetInstance()->AddActuator("Mobility", "Rotation PID", rotation_PID);

	areDriveEncodersEnabled = false;
	isGyroEnabled = true;
	drive_distance_start = new Timer();

}

void Mobility::process() {
	//DriverStation::ReportError("Gyro: " + std::to_string(gyro->PIDGet()));
	if (turning_degrees) {
		processTurningDegrees();
	}
	if(is_drive_distance_on) {
		processDistance();
	}

	//frc::DriverStation::ReportError("Left Rate: " + std::to_string(encoders->getLeftEncoderRates()));

	//frc::DriverStation::ReportError("Left Encoder: " + std::to_string(encoders->getLeftEncoderRates()));
	//frc::DriverStation::ReportError("Right Encoder: " + std::to_string(encoders->getRightEncoderRates()));
}

void Mobility::processDistance() {
	if(areDriveEncodersEnabled) {
		if(distance_PID->OnTarget()) {
			frc::DriverStation::ReportError("On Target, disaling");
			disableDistancePID();
			is_drive_distance_on = false;
		}
	}
	else {
		if(drive_distance_start->HasPeriodPassed(3) ) {
			Mobility::setLeft(0.0);
			Mobility::setRight(0.0);
			is_drive_distance_on = false;
			drive_distance_start->Stop();
			drive_distance_start->Reset();
		}
		else {
			Mobility::setLeft(1.0);
			Mobility::setRight(1.0);
		}
	}

}

void Mobility::processTurningDegrees() { //Here!
	if (rotation_PID->OnTarget()) {
		disableRotationPID();
		turning_degrees = false;
		setLeft(0);
		setRight(0);
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
bool Mobility::isTurnDegreesDone() {
	return rotation_PID->OnTarget();
}

float Mobility::getNavXTemperature() {
	return gyro->GetTempC();
}

//Drive Distance
void Mobility::StartDriveDistance(float distance) {
	is_drive_distance_on = true;
	if(areDriveEncodersEnabled) {
		encoders->DriveEncoderReset();
		distance_PID->SetSetpoint(distance);
		enableDistancePID();
	}
	else {
		drive_distance_start->Start();
	}
}

bool Mobility::isDriveDistanceDone() {
	return is_drive_distance_on;
}

//Drive Straight
void Mobility::startDriveStraight() {
	frc::DriverStation::ReportError("Starting drive straight");
	if(isGyroEnabled) {
		rotation_PID->SetSetpoint(gyro->GetYaw());
		enableRotationPID();
	}
	else {
		Mobility::setLeft(getStraightSpeed());
		Mobility::setRight(getStraightSpeed());
	}
	driving_straight = true;
}
bool Mobility::isDrivingStraight() {
	return driving_straight;
}

void Mobility::stopDriveStraight() {
	driving_straight = false;
	if(isGyroEnabled) {
		disableRotationPID();
	}
}

float Mobility::getStraightSpeed() {
	return straight_speed;
}
void Mobility::setStraightSpeed(float speed) {
	straight_speed = speed;
	if(isGyroEnabled) {
		rotation_output->setForwardSpeed(speed);
	}
	else {
		setLeft(speed);
		setRight(speed);
	}
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

	rotation_output->setForwardSpeed(0);
}

void Mobility::disableRotationPID() {
	rotation_output->Disable();
	rotation_PID->Disable();
}

void Mobility::enableRotationPID() {
	rotation_output->Enable();
	rotation_PID->Enable();
}

bool Mobility::isRotationPIDEnabled() {
	return rotation_PID->IsEnabled();
}

void Mobility::disableDistancePID() {
	distance_PID->Disable();
	distance_output->Disable();
}

void Mobility::enableDistancePID() {
	distance_PID->Enable();
	distance_output->Enable();
}

bool Mobility::isDistancePIDEnabled() {
	return distance_PID->IsEnabled();
}

Mobility* Mobility::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Mobility();
	}

	return INSTANCE;
}
