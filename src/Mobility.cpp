/*
 * Mobility.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Mobility.h>
#include "Ports.h"

#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

Mobility* Mobility::INSTANCE = nullptr;

const float MAX_SPEED =  155;// in/s
const float AVG_ACCELERATION = 96.5;// in/s^2
const float AVG_DECELERATION = -119.7;// in/s^2
const float POSITION_CONSTANT = 104.46;
const float DISTANCE_TO_FULL_SPEED = 104.8;// inches
const float ONTARGET_TIME = 0.1;

const float ROT_P = 0.05;
const float ROT_I = 0.0;
const float ROT_D = 0.06;

//First num in point is distance in inches, second num in point is time in seconds
const float DISTANCES_TO_TIMES[][2] = {{0, 0}, {4.8125, 0.1}, {11.6666, 0.2}, {18.6875, 0.3}, {35.75, 0.4}, {41.4583, 0.5},
		{56.625, 0.6}, {65.5, 0.7}, {76.875, 0.8}, {95.0, 0.9}, {106.7083, 1.0}};
//First num in point is degrees, second num is time in seconds
const float DEGREES_TO_TIMES[][2] = {{0, 0}};

Mobility::Mobility() {
	log = Log::getInstance();

	//Sensor Toggles
	use_left_drive_encoder = true;
	use_right_drive_encoder = true;
	use_gyro = true;
	use_distance_PID = true;
	use_rotation_PID = true;


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

	//PID controllers
	rotation_output = new MobilityRotationPID(front_left, front_right, back_left, back_right);
	rotation_output->Disable();
	rotation_PID = new frc::PIDController(0.05, 0.0, 0.06, gyro, rotation_output);
	rotation_PID->Disable();
	rotation_PID->SetContinuous(true);
	rotation_PID->SetInputRange(-180, 180);
	rotation_PID->SetOutputRange(-1, 1);
	rotation_PID->SetPIDSourceType(PIDSourceType::kDisplacement);
	rotation_PID->SetAbsoluteTolerance(1.0);

	distance_output = new MobilityDistanceOutput();
	distance_PID = new frc::PIDController(0.15, 0, 0.3, encoders, distance_output);
	distance_PID->Disable();
	distance_PID->SetContinuous(false);
	distance_PID->SetInputRange(-650, 650);
	distance_PID->SetOutputRange(-1.0, 1.0);
	distance_PID->SetPIDSourceType(PIDSourceType::kDisplacement);
	distance_PID->SetAbsoluteTolerance(1.0);

	gear_track_input = new GearTracker();

	tracking_gear = false;

	LiveWindow::GetInstance()->AddActuator("Mobility", "Rotation PID", rotation_PID);

	drive_distance_timer = new Timer();
	turn_degrees_timer = new Timer();
}

void Mobility::process() {
	//DriverStation::ReportError("Gyro: " + std::to_string(gyro->PIDGet()));
	//frc::DriverStation::ReportError("Left Encoder: " + std::to_string(encoders->getLeftEncoderRates()) + " Right Encoder: "  + std::to_string(encoders->getRightEncoderRates()));
	if (is_turn_degrees_on) {
		processTurningDegrees();
	}
	if(is_drive_distance_on) {
		processDistance();
	}
}

void Mobility::processDistance() {
	if(use_left_drive_encoder || use_right_drive_encoder) {
		if(distance_PID->OnTarget()) {
			if(drive_distance_timer->Get() >= ONTARGET_TIME) {
				frc::DriverStation::ReportError("Drive dist done");
				stopDriveDistance();
				setStraightSpeed(0.0);
				setLeft(0.0);
				setRight(0.0);
				drive_distance_timer->Stop();
				drive_distance_timer->Reset();
			}
			else if(drive_distance_timer->Get() <= 0.0) {
				drive_distance_timer->Reset();
				drive_distance_timer->Start();
			}
			frc::DriverStation::ReportError("On Target");
		}
		else if(drive_distance_timer->Get() > 0.0) {
			drive_distance_timer->Stop();
			drive_distance_timer->Reset();
		}
	}
	else {
		if(drive_distance_timer->Get() >= (drive_dist_time + std::min(0.3f, drive_dist_time))) {
			frc::DriverStation::ReportError("Drive distance done");
			stopDriveStraight();
		}
		else if(drive_distance_timer->Get() >= drive_dist_time ) {
			frc::DriverStation::ReportError("Stopping drive dist");
			setStraightSpeed(0.0);
			setLeft(0.0);
			setRight(0.0);
		}
	}
}

float Mobility::getDistanceError() {
	return distance_PID->GetError();
}

void Mobility::processTurningDegrees() {
	if(use_gyro) {
		if (rotation_PID->OnTarget()) {
			if(turn_degrees_timer->Get() == 0) {
				turn_degrees_timer->Start();
			}
			else if(turn_degrees_timer->Get() >= ONTARGET_TIME) {
				stopTurnDegrees();
				frc::DriverStation::ReportError("Turn Degrees done");
			}
		}
		else if(turn_degrees_timer->Get() > 0) {
			turn_degrees_timer->Stop();
			turn_degrees_timer->Reset();
		}
	}
	else {
		if(turn_degrees_timer->HasPeriodPassed(turn_deg_time)) {
			stopTurnDegrees();
		}
	}
}

float Mobility::getLeftEncoderRates() {
	return encoders->getLeftEncoderRates();
}

float Mobility::getRightEncoderRates() {
	return encoders->getRightEncoderRates();
}

float Mobility::getGyroAngle() {
	return gyro->PIDGet();
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
void Mobility::StartDriveDistance(float distance, float speed) {
	is_drive_distance_on = true;
	if((use_left_drive_encoder || use_right_drive_encoder) && use_distance_PID) {
		startDriveStraight();
		encoders->DriveEncoderReset();
		distance_PID->SetOutputRange(-speed, speed);
		distance_PID->SetSetpoint(distance);
		enableDistancePID();
	}
	else {
		drive_dist_time = estimateTimeFromPoints(DISTANCES_TO_TIMES, ARRAY_SIZE(DISTANCES_TO_TIMES) , distance);
		DriverStation::ReportError("Starting drive distance without encoders: " + std::to_string(drive_dist_time));
		drive_distance_timer->Start();
		startDriveStraight();
		setStraightSpeed(1.0);
	}
}

void Mobility::setDistancePIDOutputRange(float min, float max) {
	distance_PID->SetOutputRange(min, max);
}

void Mobility::stopDriveDistance() {
	is_drive_distance_on = false;
	drive_distance_timer->Stop();
	drive_distance_timer->Reset();
	drive_dist_time = 0.0;
	stopDriveStraight();
	disableDistancePID();
	setLeft(0.0);
	setRight(0.0);
}

float Mobility::estimateTimeFromPoints(const float points[][2], int size, float distance) {
	frc::DriverStation::ReportError(std::to_string(points[1][0]) + "," + std::to_string(points[1][1]));
	frc::DriverStation::ReportError(std::to_string(size));
	for(int i = 0; i < size; i++) {
		if(points[i][0] == distance) {
			return points[i][1];
		}
		else if(points[i][0] > distance) {
			//Point with distance below target
			float lower_dist;
			float lower_time;
			//Point with distance above target
			float upper_dist = points[i][0];
			float upper_time = points[i][1];

			//If we're at the first point in the list, then the point before is just (0,0);
			if(i > 0) {
				lower_dist = points[i - 1][0];
				lower_time = points[i - 1][1];
			}
			else {
				lower_dist = 0.0;
				lower_time = 0.0;
			}

			//Rise over run
			float slope = (upper_time - lower_time) / (upper_dist - lower_dist);
			float y_intercept = upper_time - slope * upper_dist;
			//mx+b
			frc::DriverStation::ReportError("Drive Distance Time: " + std::to_string(slope * distance + y_intercept));
			return slope * distance + y_intercept;
		}
	}
	//Point with distance below target
	int lower_dist;
	int lower_time;
	//Point with distance above target
	int upper_dist = points[size][0];
	int upper_time = points[size][1];

	if(size > 0) {
		lower_dist = points[size - 1][0];
		lower_time = points[size - 1][1];
	}
	else {
		lower_dist = 0;
		lower_time = 0;
	}

	//Rise over run
	int slope = (upper_time - lower_time) / (upper_dist - lower_dist);
	int y_intercept = upper_time - slope * distance;
	//mx+b
	int time = slope * distance + y_intercept;

	log->write(Log::WARNING_LEVEL, "Distance farther than we have data for, this may be inaccurate. Distance: %f Time: %f", distance, time);
	return time;
}

bool Mobility::isDriveDistanceDone() {
	return !is_drive_distance_on;
}

//Drive Straight
void Mobility::startDriveStraight() {
	//frc::DriverStation::ReportError("Starting drive straight");
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
	if(degrees == 0)
		return;

	if(use_gyro && use_rotation_PID) {
		gyro->Reset();
		rotation_PID->SetSetpoint(degrees);
		enableRotationPID();

		rotation_output->setForwardSpeed(0);
	}
	else {
		turn_deg_time = estimateTimeFromPoints(DEGREES_TO_TIMES, ARRAY_SIZE(DEGREES_TO_TIMES), degrees);
		if(degrees < 0) {
			setLeft(-1.0);
			setRight(1.0);
		}
		else {
			setLeft(1.0);
			setRight(-1.0);
		}

		turn_degrees_timer->Reset();
		turn_degrees_timer->Start();
	}
}

void Mobility::stopTurnDegrees() {
	disableRotationPID();
	is_turn_degrees_on = false;
	setLeft(0);
	setRight(0);
	turn_degrees_timer->Stop();
	turn_degrees_timer->Reset();
	turn_deg_time = 0.0;
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

void Mobility::resetGyro() {
	gyro->Reset();
}

void Mobility::startTrackGear() {
	rotation_PID = new frc::PIDController(ROT_P, ROT_I, ROT_D, gear_track_input, rotation_output);
	tracking_gear = true;
}

bool Mobility::isTrackingGear() {
	return tracking_gear;
}

void Mobility::stopTrackGear() {
	rotation_PID = new frc::PIDController(ROT_P, ROT_I, ROT_D, gyro, rotation_output);
	tracking_gear = false;
}

Mobility* Mobility::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Mobility();
	}

	return INSTANCE;
}

Mobility::MobilityDistanceOutput::MobilityDistanceOutput() {
	enabled = false;
}

void Mobility::MobilityDistanceOutput::PIDWrite(double output) {
	if(!enabled)
		return;
	Mobility::getInstance()->setStraightSpeed(output);
}

void Mobility::MobilityDistanceOutput::Enable() {
	enabled = true;
}

void Mobility::MobilityDistanceOutput::Disable() {
	enabled = false;
}

Mobility::GearTracker::GearTracker() {
	vision = Vision::getInstance();
}

double Mobility::GearTracker::PIDGet() {
	if(vision->canSeeGearHook()) {
		return vision->gearHookOffset();
	}
	else {
		return 0.0;
	}
}
