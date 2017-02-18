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
const float AZIMUTH_ENCODER_PULSES = 360;
const float ENCODER_PER_AZIMUTH_REV = 5;

Shooter::Shooter() {
	use_shooter_azimuth_encoder = true;
	use_shooter_azimuth_limit_switch_encoder = true;
	use_shooter_speed_encoder = true;

	azimuth_current_angle = 0.0;

	shooter = new CANTalon(RobotPorts::MOTOR_SHOOTER_WHEEL);
	azimuth = Utils::constructMotor(RobotPorts::MOTOR_SHOOTER_AZIMUTH);
	target_azimuth_angle = 0;

	shooter_encoder = new frc::Encoder(RobotPorts::SHOOTER_ENCODER_1, RobotPorts::SHOOTER_ENCODER_2);
	azimuth_encoder = new frc::AnalogPotentiometer(RobotPorts::AZIMUTH_ENCODER);

	//FALSE IS PRESSED, TRUE IS NOT PRESSED
	azimuth_limit_switch = new frc::DigitalInput(RobotPorts::LS_SHOOTER_AZIMUTH);

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
	frc::DriverStation::ReportError("Limit Switch: " + std::to_string(azimuth_limit_switch->Get()) + " Azimuth: " + std::to_string(azimuth_encoder->Get()));
}

float Shooter::getShooterEncoderRate() {
	return shooter_encoder->GetRate();
}

float Shooter::getAzimuthPosition() {
	if(use_shooter_azimuth_encoder)
		return azimuth_encoder->Get();
	else
		return azimuth_current_angle;
}

float Shooter::getAzimuthSetValue() {
	return azimuth->Get();
}

float Shooter::getShooterSetValue() {
	return shooter->Get();
}

float Shooter::getSpeed() {
	return shooter->Get();
}

//True is pressed, False is not pressed
bool Shooter::getLimitSwitch() {
	return !azimuth_limit_switch->Get();
}

void Shooter::enableAzimuthPID() {
	azimuth_PID->Enable();
}

void Shooter::disableAzimuthPID() {
	azimuth_PID->Disable();
}

bool Shooter::isAzimuthPIDEnabled() {
	return azimuth_PID->IsEnabled();
}

void Shooter::setAzimuthAngle(float angle) {
	if(use_shooter_azimuth_encoder)
		azimuth_PID->SetSetpoint(angle);
	else {

	}
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

bool Shooter::isShooterPIDEnabled() {
	return shooter_PID->IsEnabled();
}

void Shooter::enableShooterAzimuthEncoder() {
	use_shooter_azimuth_encoder = true;
}

bool Shooter::isShooterAzimuthEncoderEnabled() {
	return use_shooter_azimuth_encoder;
}

void Shooter::disableShooterAzimuthEncoder() {
	use_shooter_azimuth_encoder = false;
}

void Shooter::enableShooterAzimuthLimitSwitch() {
	use_shooter_azimuth_limit_switch_encoder = true;
}

bool Shooter::isShooterAzimuthLimitSwitchEnabled() {
	return use_shooter_azimuth_limit_switch_encoder;
}

void Shooter::disableShooterAzimuthLimitSwitch() {
	use_shooter_azimuth_limit_switch_encoder = false;
}

void Shooter::enableShooterSpeedEncoder() {
	use_shooter_speed_encoder = true;
}

bool Shooter::isShooterSpeedEncoderEnabled() {
	return use_shooter_speed_encoder;
}

void Shooter::disableShooterSpeedEncoder() {
	use_shooter_speed_encoder = false;
}

Shooter* Shooter::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Shooter();
	}

	return INSTANCE;
}
