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

	shooter_encoder = new Encoder(RobotPorts::SHOOTER_ENCODER_1, RobotPorts::SHOOTER_ENCODER_2);

	//PID STUFF
	shooter_PID = new frc::PIDController(0.01, 0.0, 0.0, shooter_encoder, shooter);
	shooter_PID->SetContinuous(false);
	shooter_PID->SetInputRange(0,9000.0);
	shooter_PID->SetOutputRange(-1, 1);
	shooter_PID->SetPIDSourceType(PIDSourceType::kRate);
	shooter_PID->SetAbsoluteTolerance(50);
	shooter_PID->Disable();
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

void Shooter::setAzimuthAngle(float angle) {
	azimuth->Set(angle);
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
