/*
 * Shooter.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include "Shooter.h"
#include "Ports.h"

Shooter* Shooter::INSTANCE = nullptr;
const float AZIMUTH_ANGLE_TOLERANCE = 1.0;
const float AUTO_AZIMUTH_SPEED = 0.5;

Shooter::Shooter() {
	shooter = Utils::constructMotor(RobotPorts::MOTOR_SHOOTER_WHEEL);
	azimuth = Utils::constructMotor(RobotPorts::MOTOR_SHOOTER_AZIMUTH);
	target_azimuth_angle = 0;

	shooter_encoder = new frc::Encoder(RobotPorts::SHOOTER_ENCODER_1, RobotPorts::SHOOTER_ENCODER_2);
	azimuth_encoder = new frc::Encoder(RobotPorts::AZIMUTH_ENCODER_1, RobotPorts::AZIMUTH_ENCODER_2);

	//PID STUFF
	shooter_PID = new frc::PIDController(0.01, 0.0, 0.0, shooter_encoder, shooter);
	shooter_PID->SetContinuous(false);
	shooter_PID->SetInputRange(0,9000.0);
	shooter_PID->SetOutputRange(-1, 1);
	shooter_PID->SetPIDSourceType(frc::PIDSourceType::kRate);
	shooter_PID->SetAbsoluteTolerance(50);
	shooter_PID->Disable();

	azimuth_PID = new frc::PIDController(0.1, 0, 0, azimuth_encoder, azimuth);
	azimuth_PID->SetContinuous(false);
	azimuth_PID->SetInputRange(-180, 180);
	azimuth_PID->SetOutputRange(-1, 1);
	azimuth_PID->SetPIDSourceType(frc::PIDSourceType::kDisplacement);
	azimuth_PID->SetAbsoluteTolerance(0.5);
	azimuth_PID->Disable();
}

void Shooter::process() {

	float current_azimuth_angle = 0;

	float azimuth_angle_offset = target_azimuth_angle - current_azimuth_angle;

	if (azimuth_angle_offset > AZIMUTH_ANGLE_TOLERANCE) {
		azimuth->Set(AUTO_AZIMUTH_SPEED);
	}
	else if (azimuth_angle_offset > - AZIMUTH_ANGLE_TOLERANCE) {
		azimuth->Set(AUTO_AZIMUTH_SPEED);
	}
	else {
		azimuth->Set(0);
	}


}

void Shooter::enableAzimuthPID() {
	azimuth_PID->Enable();
}

void Shooter::disableAzimuthPID() {
	azimuth_PID->Disable();
}

void Shooter::setAzimuthAngle(float angle) {
	azimuth_PID->SetSetpoint(angle);
}

void Shooter::setAzimuthSpeed(float speed) {
	azimuth->Set(speed);
}

void Shooter::setShooterSpeed(float speed) {
	shooter->Set(speed);

}
void Shooter::setShooterRPM(float speed) {
	shooter_PID->SetSetpoint(speed);
}
void Shooter::enableShooterPID() {
	shooter_PID->Enable();
}
void Shooter::disableShooterPID() {
	shooter_PID->Disable();
}
Shooter* Shooter::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Shooter();
	}

	return INSTANCE;
}
