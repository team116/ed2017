/*
 * Mobility.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Mobility.h>
#include "Ports.h"

Mobility* Mobility::INSTANCE = nullptr;

const float MAX_SPEED =  155;// in/s
const float AVG_ACCELERATION = 96.5;// in/s^2
const float AVG_DECELERATION = -119.7;// in/s^2
const float POSITION_CONSTANT = 104.46;
const float DISTANCE_TO_FULL_SPEED = 104.8;// inches

Mobility::Mobility() {
	log = Log::getInstance();

	//Sensor Toggles
	use_left_drive_encoder = true;
	use_right_drive_encoder = true;
	use_gyro = true;


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
	drive_dist_time = 0.0;
	turn_deg_time = 0.0;
	is_turn_degrees_on = false;
	driving_straight = false;
	is_drive_distance_on = false;
	is_linear_accel_test = false;
	is_rotational_vel_test = false;


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

	drive_distance_timer = new Timer();
	turn_degrees_timer = new Timer();
}

void Mobility::process() {
	//DriverStation::ReportError("Gyro: " + std::to_string(gyro->PIDGet()));
	//frc::DriverStation::ReportError("Left Encoder: " + std::to_string(encoders->getLeftEncoderRates()));
	//frc::DriverStation::ReportError("Right Encoder: " + std::to_string(encoders->getRightEncoderRates()));
	if (is_turn_degrees_on) {
		processTurningDegrees();
	}
	if(is_drive_distance_on) {
		processDistance();
	}
}

void Mobility::processDistance() {
	if(is_linear_accel_test) {
		frc::DriverStation::ReportError("Time: " + std::to_string(drive_distance_timer->Get()));
		if(drive_distance_timer->HasPeriodPassed(drive_dist_time + 2.0)) {
			frc::DriverStation::ReportError("Linear Acceleration Test Complete. Extract data from log file");
			is_linear_accel_test = false;
			drive_distance_timer->Stop();
			drive_distance_timer->Reset();
			is_drive_distance_on = false;
		}
		else if(drive_distance_timer->Get() >= drive_dist_time) {
			stopDriveStraight();
			setStraightSpeed(0.0);
			setLeft(0.0);
			setRight(0.0);
			log->write(Log::INFO_LEVEL, "Linear Accel-end: %f", gyro->GetRawAccelY());
		}
		else {
			log->write(Log::INFO_LEVEL, "Linear Accel: %f", gyro->GetRawAccelY());
		}
	}
	else if(use_left_drive_encoder || use_right_drive_encoder) {
		if(distance_PID->OnTarget()) {
			disableDistancePID();
			is_drive_distance_on = false;
		}
	}
	else {
		if(drive_distance_timer->HasPeriodPassed(drive_dist_time) ) {
			frc::DriverStation::ReportError("Stopping drive dist");
			stopDriveStraight();
			setStraightSpeed(0.0);
			setLeft(0.0);
			setRight(0.0);
			is_drive_distance_on = false;
			drive_distance_timer->Stop();
			drive_distance_timer->Reset();
			drive_dist_time = 0.0;
		}
	}
}

void Mobility::processTurningDegrees() {
	if(is_rotational_vel_test) {
		if(turn_degrees_timer->HasPeriodPassed(turn_deg_time + 1.0)) {
			frc::DriverStation::ReportError("Rotational Acceleration Test Complete. Extract data from log file");
			is_rotational_vel_test = false;
			turn_degrees_timer->Stop();
			turn_degrees_timer->Reset();
			is_turn_degrees_on = false;
		}
		else if(turn_degrees_timer->HasPeriodPassed(turn_deg_time)) {
			setLeft(0);
			setRight(0);
			log->write(Log::INFO_LEVEL, "Rotational Velocity-end: %f", gyro->GetRate());
		}
		else {
			log->write(Log::INFO_LEVEL, "Rotational Velocity: %f", gyro->GetRate());
		}
	}
	else if(use_gyro) {
		if (rotation_PID->OnTarget()) {
			disableRotationPID();
			is_turn_degrees_on = false;
			setLeft(0);
			setRight(0);
		}
	}
	else {
		if(turn_degrees_timer->HasPeriodPassed(turn_deg_time)) {
			setLeft(0.0);
			setRight(0.0);
			is_turn_degrees_on = false;
			turn_degrees_timer->Stop();
			turn_degrees_timer->Reset();
			turn_deg_time = 0.0;
		}
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
	return !is_turn_degrees_on;
}

float Mobility::getNavXTemperature() {
	return gyro->GetTempC();
}

//Drive Distance
void Mobility::StartDriveDistance(float distance) {
	is_drive_distance_on = true;
	if(use_left_drive_encoder || use_right_drive_encoder) {
		encoders->DriveEncoderReset();
		distance_PID->SetSetpoint(distance);
		enableDistancePID();
	}
	else {
		drive_dist_time = calculateTimeForDistance(distance);
		DriverStation::ReportError("Starting drive distance without encoders: " + std::to_string(drive_dist_time));
		drive_distance_timer->Start();
		startDriveStraight();
		setStraightSpeed(1.0);
	}
}

void Mobility::startLinearAccelTest(float time) {
	is_drive_distance_on = true;
	is_linear_accel_test = true;
	drive_dist_time = time;
	drive_distance_timer->Reset();
	drive_distance_timer->Start();
	startDriveStraight();
	setStraightSpeed(1.0);
}

void Mobility::startRotationalVelTest(float time) {
	is_turn_degrees_on = true;
	is_rotational_vel_test = true;
	turn_deg_time = time;
	turn_degrees_timer->Reset();
	turn_degrees_timer->Start();
	setLeft(1.0);
	setRight(-1.0);
}

float Mobility::calculateTimeForDistance(float distance) {
	if(distance == 0)
		return 0.0;
	if(distance < 0.0)
		return -calculateTimeForDistance(-1 * distance);
	else {
		float limit = (AVG_DECELERATION * MAX_SPEED * MAX_SPEED - AVG_ACCELERATION * MAX_SPEED * MAX_SPEED) / (2 * AVG_ACCELERATION * AVG_DECELERATION);
		frc::DriverStation::ReportError("Limit: " + std::to_string(limit));
		if(distance < limit) {
			frc::DriverStation::ReportError("Case 1");
			return sqrt((-2 * distance * (AVG_ACCELERATION - AVG_DECELERATION)) / (AVG_ACCELERATION * AVG_DECELERATION));
		}
		else {
			frc::DriverStation::ReportError("Case 2");
			return (distance / MAX_SPEED ) - (MAX_SPEED / (2 * AVG_ACCELERATION)) - (MAX_SPEED / AVG_DECELERATION)
					+ (MAX_SPEED / AVG_ACCELERATION) + (MAX_SPEED / (2 * AVG_DECELERATION));
		}
	}
}

bool Mobility::isDriveDistanceDone() {
	return !is_drive_distance_on;
}

//Drive Straight
void Mobility::startDriveStraight() {
	frc::DriverStation::ReportError("Starting drive straight");
	if(use_gyro) {
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
	if(use_gyro) {
		disableRotationPID();
	}
}

float Mobility::getStraightSpeed() {
	return straight_speed;
}
void Mobility::setStraightSpeed(float speed) {
	straight_speed = speed;
	if(use_gyro) {
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
	is_turn_degrees_on = true;

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

void Mobility::enableLeftEncoder() {
	use_left_drive_encoder = true;
	encoders->enableLeftEncoder();
}

void Mobility::disableLeftEncoder() {
	use_left_drive_encoder = false;
	encoders->disableLeftEncoder();
}

bool Mobility::isLeftEncoderEnabled() {
	return encoders->isLeftEncoderEnabled();
}

void Mobility::enableRightEncoder() {
	use_right_drive_encoder = true;
	encoders->enableRightEncoder();
}

void Mobility::disableRightEncoder() {
	use_right_drive_encoder = false;
	encoders->disableRightEncoder();
}

bool Mobility::isRightEncoderEnabled() {
	return encoders->isRightEncoderEnabled();
}

void Mobility::enableGyro() {
	use_gyro = true;
}

void Mobility::disableGyro() {
	use_gyro = false;
}

bool Mobility::isGyroEnabled() {
	return use_gyro;
}

Mobility* Mobility::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Mobility();
	}

	return INSTANCE;
}
