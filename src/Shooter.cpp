/* * Shooter.cpp
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

	azimuth = Utils::constructMotor(RobotPorts::MOTOR_SHOOTER_AZIMUTH);
	target_azimuth_angle = 0;

	azimuth_auto_track = false;

	shooter = new ShooterSpeed();

	azimuth_encoder = new frc::AnalogPotentiometer(RobotPorts::AZIMUTH_ENCODER, 360.0, 0.0);
	//az_enc = new AzimuthEncoder();

	//FALSE IS PRESSED, TRUE IS NOT PRESSED
	azimuth_limit_switch = new frc::DigitalInput(RobotPorts::LS_SHOOTER_AZIMUTH);

	//PID STUFF
	/*shooter_PID = new frc::PIDController(0.01, 0.0, 0.0, shooter_encoder, shooter);
	shooter_PID->SetContinuous(false);
	shooter_PID->SetInputRange(0,9000.0);
	shooter_PID->SetOutputRange(-1, 1);
	shooter_PID->SetPIDSourceType(frc::PIDSourceType::kRate);
	shooter_PID->SetAbsoluteTolerance(50);
	shooter_PID->Disable();*/

	azimuth_PID = new frc::PIDController(0.1, 0, 0, azimuth_encoder, azimuth);
	azimuth_PID->SetContinuous(false);
	azimuth_PID->SetInputRange(-180, 180);
	azimuth_PID->SetOutputRange(-1, 1);
	azimuth_PID->SetPIDSourceType(frc::PIDSourceType::kDisplacement);
	azimuth_PID->SetAbsoluteTolerance(0.5);
	azimuth_PID->Disable();

	azimuth_vision_tracker = new AzimuthVisionTracker();
	azimuth_vision_PID = new frc::PIDController(0.1, 0.0, 0.0, azimuth_vision_tracker, azimuth);
	azimuth_vision_PID->SetContinuous(false);
	azimuth_vision_PID->SetInputRange(-1.0, 1.0);
	azimuth_vision_PID->SetOutputRange(-0.5, 0.5);
	azimuth_vision_PID->SetPIDSourceType(frc::PIDSourceType::kDisplacement);
	azimuth_vision_PID->SetAbsoluteTolerance(0.01);
	azimuth_vision_PID->SetSetpoint(0.0);
	azimuth_vision_PID->Disable();

	LiveWindow::GetInstance()->AddActuator("Shooter", "Azimuth Vision PID", azimuth_vision_PID);
}

void Shooter::process() {
	//az_enc->process();
	//frc::DriverStation::ReportError("Limit Switch: " + std::to_string(azimuth_limit_switch->Get()) + " Azimuth: " + std::to_string(azimuth_encoder->Get()) + " Speed: " + std::to_string(shooter->GetSpeed()));
	//frc::DriverStation::ReportError("Raw AZ: " + std::to_string(azimuth_encoder->Get()) + " Adjusted AZ: " + std::to_string(az_enc->getAngle()));
	//frc::DriverStation::ReportError("Shooter: " + std::to_string(shooter->PIDGet()));
}

float Shooter::getShooterEncoderRate() {
	return shooter->GetEncVel();
}

float Shooter::getAzimuthPosition() {
	if(use_shooter_azimuth_encoder)
		return azimuth_encoder->Get();
	else
		return azimuth_current_angle;
}

float Shooter::getAzimuthSpeed() {
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
	azimuth->Set(-speed);
}

void Shooter::setShooterSpeed(float speed) {
	shooter->Set(-speed);

}
void Shooter::setShooterRPM(float speed) {
	shooter->SetSetpoint(speed);
}
void Shooter::enableShooterPID() {
	shooter->SetControlMode(frc::CANSpeedController::ControlMode::kSpeed);
}
void Shooter::disableShooterPID() {
	shooter->SetControlMode(frc::CANSpeedController::ControlMode::kPercentVbus);
}

bool Shooter::isShooterPIDEnabled() {
	if(shooter->GetControlMode() == frc::CANSpeedController::kPercentVbus) {
		return false;
	}
	return true;
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

void Shooter::startAzimuthVisionTrack() {
	azimuth_vision_PID->Enable();
	azimuth_vision_PID->SetSetpoint(0.0);
}

void Shooter::stopAzimuthVisionTrack() {
	azimuth_vision_PID->Disable();
	azimuth->Set(0.0);
}

bool Shooter::isAzimuthVisionTrack() {
	return azimuth_vision_PID->IsEnabled();
}

Shooter::AzimuthVisionTracker::AzimuthVisionTracker() {
	vision = Vision::getInstance();
}

double Shooter::AzimuthVisionTracker::PIDGet() {
	if(vision->canSeeHighGoal()) {
		return vision->highGoalOffset();
	}
	else {
		return 0.0;
	}
}

Shooter::ShooterSpeed::ShooterSpeed() : CANTalon(RobotPorts::MOTOR_SHOOTER_WHEEL) {
	SetFeedbackDevice(CANTalon::FeedbackDevice::EncRising);
	ConfigEncoderCodesPerRev(1);
	//SetControlMode(CANSpeedController::ControlMode::kSpeed);
	//SelectProfileSlot(0);
}

double Shooter::ShooterSpeed::PIDGet() {
	return GetSpeed();
}

Shooter* Shooter::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Shooter();
	}

	return INSTANCE;
}
