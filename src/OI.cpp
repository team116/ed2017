/*
 * OI.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <OI.h>
#include "Ports.h"

OI* OI::INSTANCE = nullptr;

const float CLIMB_SPEED = 1.0;
const float SHOOTER_SPEED = -1.0;
const float INTAKE_SPEED = 1.0;
const float OPPOSITE_INTAKE_SPEED = -1.0;
const float BLENDER_SPEED = 0.75;
const float BLENDER_REVERSE_SPEED = -0.75;
const float FEEDER_SPEED = 1.0;
const float FEEDER_REVERSE_SPEED = -1.0;

const float SHOOT_BUTTON_TIME = 1.0;

OI::OI() {
	// TODO Auto-generated constructor stub

	log = Log::getInstance();

	mobility = Mobility::getInstance();
	gear = Gear::getInstance();
	climber = Climber::getInstance();
	shooter = Shooter::getInstance();
	intake = Intake::getInstance();
	feeder = Feeder::getInstance();
	vision = Vision::getInstance();
	joy_left = new frc::Joystick(OIPorts::JOYSTICK_LEFT);
	joy_right = new frc::Joystick(OIPorts::JOYSTICK_RIGHT);
	button_box_1 = new frc::Joystick(OIPorts::JOYSTICK_BUTTONS_1);
	button_box_2 = new frc::Joystick(OIPorts::JOYSTICK_BUTTONS_2);
	button_box_3 = new frc::Joystick(OIPorts::JOYSTICK_BUTTONS_3);

	shoot_button_timer = new frc::Timer();
}

void OI::process() {

	//Make sure we're not doing an automated mobility thing
	if(mobility->isTurnDegreesDone() && mobility->isDriveDistanceDone()) {
		//Check left joystick drive straight button
		if (joy_left->GetRawButton(OIPorts::B_DRIVE_STRAIGHT)) {
			//If it isnt already driving straight, make it drive straight
			if (!mobility->isDrivingStraight()) {
				mobility->startDriveStraight();
			}

			//Set the straight speed according to this joystick
			mobility->setStraightSpeed(joy_left->GetRawAxis(OIPorts::AXIS_Y) * -1);
		}
		//Check right joystick drive straight button
		else if (joy_right->GetRawButton(OIPorts::B_DRIVE_STRAIGHT)) {
			//If it isnt already driving straight, make it drive straight
			if (!mobility->isDrivingStraight()) {
				mobility->startDriveStraight();
			}

			//Set the straight speed according to this joystick
			mobility->setStraightSpeed(joy_right->GetRawAxis(OIPorts::AXIS_Y) * -1);
		}
		//Check right joystick rotate button
		else if(joy_right->GetRawButton(OIPorts::B_ROTATE)) {
			mobility->setLeft(joy_right->GetRawAxis(OIPorts::AXIS_Z));
			mobility->setRight(joy_right->GetRawAxis(OIPorts::AXIS_Z) * -1);
		}
		//Check left joystick rotate button
		else if(joy_left->GetRawButton(OIPorts::B_ROTATE)) {
			mobility->setLeft(joy_left->GetRawAxis(OIPorts::AXIS_Z));
			mobility->setRight(joy_left->GetRawAxis(OIPorts::AXIS_Z) * -1);
		}
		//If we're not doing any of the fancy drive straight or rotate stuff, do normal driving
		else {
			//Disable drive straight if it's enabled (we know drive straight button isnt being pressed if we've made it to this else statement)
			if(mobility->isDrivingStraight()) {
				mobility->stopDriveStraight();
			}

			//Set both sides to the speeds of their corresponding joysticks
			//Multiply by -1 because y axis is flipped on these joysticks
			mobility->setLeft(joy_left->GetRawAxis(OIPorts::AXIS_Y) * -1);
			mobility->setRight(joy_right->GetRawAxis(OIPorts::AXIS_Y) * -1);
		}
	}



	//GEAR RELEASE
	if (button_box_2->GetRawButton(OIPorts::B_GEAR_RELEASE) && !gear->isOpen()) {
		gear->open();
		//frc::DriverStation::ReportError("Opening gear");

	}
	else if(!button_box_2->GetRawButton(OIPorts::B_GEAR_RELEASE) && gear->isOpen()) {
		gear->close();
		//frc::DriverStation::ReportError("Closing gear");
	}




	//CLIMBER
	float percent = (-1 * button_box_2->GetRawAxis(OIPorts::P_CLIMBER_SPEED) * 0.4) + 0.6;
	if(button_box_1->GetRawButton(OIPorts::S2_CLIMBER_TOGGLE) && ((CLIMB_SPEED * percent) != climber->getSpeed())) {
		//Percent from 0.2 to 1.0
		climber->moveClimber(percent * CLIMB_SPEED);
		//frc::DriverStation::ReportError("Moving up");
	}
	else if(!button_box_1->GetRawButton(OIPorts::S2_CLIMBER_TOGGLE) || (0.0 != climber->getSpeed())) {
		climber->moveClimber(0);
		//frc::DriverStation::ReportError("Stopped moving");
	}




	//SHOOTER
	//Get percent of shooter speed from shooter dial
	percent = (-1 * button_box_1->GetRawAxis(OIPorts::P_SHOOTER_SPEED) * 0.4) + 0.6;
	//Speed is the percent of our max speed constant
	float speed = percent * SHOOTER_SPEED;
	if(button_box_1->GetRawButton(OIPorts::S2_SHOOTER_WHEELS_TOGGLE) && (speed != shooter->getSpeed())) {
		//Reading speed from driverstation right now, ignoring the dial.
		//This is probably just for testing, but it lets us type in an exact speed manually
		speed = std::stof(SmartDashboard::GetString("DB/String 0", std::to_string(0.0)));
		shooter->setShooterSpeed(speed);
		//shooter->setShooterRPM(speed);
		//frc::DriverStation::ReportError("Shooter on " + std::to_string(speed));
	}
	else if (!button_box_1->GetRawButton(OIPorts::S2_SHOOTER_WHEELS_TOGGLE) && (00 != shooter->getSpeed())) {
		shooter->setShooterSpeed(0);
	    //frc::DriverStation::ReportError("Shooter off");
	}




	//INTAKE (3 states: forward, backwards, and off)
	if (button_box_2->GetRawButton(OIPorts::S3_INTAKE_REVERSE) && (INTAKE_SPEED != intake->getSpeed())) {
		intake->setSpeedIntake(INTAKE_SPEED);
	    //frc::DriverStation::ReportError("Intaking");
	}
	else if (button_box_2->GetRawButton(OIPorts::S3_INTAKE_FORWARD) && (OPPOSITE_INTAKE_SPEED != intake->getSpeed())) {
		intake->setSpeedIntake(OPPOSITE_INTAKE_SPEED);
	    //frc::DriverStation::ReportError("Opposite-intaking");
	}
	else if (intake->getSpeed() != 0.0) {
		intake->setSpeedIntake(0.0);
	    //frc::DriverStation::ReportError("Intake and opposite-intake off");
	}



	if(shoot_button_timer->Get() <= 0.0) {
		if (button_box_2->GetRawButton(OIPorts::S3_BLENDER_FORWARD) && (BLENDER_SPEED != feeder->getBlenderSpeed())) {
			feeder->setBlenderSpeed(BLENDER_SPEED);
			//frc::DriverStation::ReportError("Blending forward");
		}
		else if (button_box_2->GetRawButton(OIPorts::S3_BLENDER_REVERSE) && (BLENDER_REVERSE_SPEED != feeder->getBlenderSpeed())) {
			feeder->setBlenderSpeed(BLENDER_REVERSE_SPEED);
			//frc::DriverStation::ReportError("Blender reverse");
		}
		else if (feeder->getBlenderSpeed() != 0.0) {
			feeder->setBlenderSpeed(0.0);
			//frc::DriverStation::ReportError("Blender off");
		}

		if (button_box_2->GetRawButton(OIPorts::S3_LOADER_FORWARD) && (FEEDER_SPEED != feeder->getFeederSpeed())) {
			feeder->setFeederSpeed(FEEDER_SPEED);
			//frc::DriverStation::ReportError("Feeding forward");
		}
		else if (button_box_2->GetRawButton(OIPorts::S3_LOADER_REVERSE) && (FEEDER_REVERSE_SPEED != feeder->getFeederSpeed())) {
			feeder->setFeederSpeed(FEEDER_REVERSE_SPEED);
			//frc::DriverStation::ReportError("Feeding reverse");
		}
		else if (feeder->getFeederSpeed() != 0.0) {
			feeder->setFeederSpeed(0.0);
			//frc::DriverStation::ReportError("Feeder off");
		}

	}



	if(!shooter->isAzimuthVisionTrack()) {
		if(button_box_2->GetRawButton(OIPorts::B_AZIMUTH_LEFT)) {
			shooter->setAzimuthSpeed(-0.2);
		}
		else if(button_box_2->GetRawButton(OIPorts::B_AZIMUTH_RIGHT)) {
			shooter->setAzimuthSpeed(0.2);
		}
		else {
			shooter->setAzimuthSpeed(0.0);
		}
	}


	if(button_box_1->GetRawButton(OIPorts::S2_AUTO_AZIMUTH_TOGGLE) && !shooter->isAzimuthVisionTrack()) {
		shooter->startAzimuthVisionTrack();
	}
	else if(!button_box_1->GetRawButton(OIPorts::S2_AUTO_AZIMUTH_TOGGLE) && shooter->isAzimuthVisionTrack()) {
		shooter->stopAzimuthVisionTrack();
	}


	if(button_box_1->GetRawButton(OIPorts::B_SHOOT)) {
		//frc::DriverStation::ReportError("Time: " + std::to_string(shoot_button_timer->Get()));
		if(shoot_button_timer->Get() <= 0.0) {
			shoot_button_timer->Reset();
			shoot_button_timer->Start();
		}

		if(feeder->getFeederSpeed() != FEEDER_SPEED) {
			feeder->setFeederSpeed(FEEDER_SPEED);
		}


		if(shoot_button_timer->Get() >= 0.8) {
			if(feeder->getBlenderSpeed() != BLENDER_SPEED) {
				feeder->setBlenderSpeed(BLENDER_SPEED);
			}
			shoot_button_timer->Reset();
			shoot_button_timer->Start();
		}
		else if(shoot_button_timer->Get() >= 0.65) {
			//frc::DriverStation::ReportError(std::to_string(feeder->getBlenderSpeed()));
			if(feeder->getBlenderSpeed() != (BLENDER_REVERSE_SPEED)) {
				feeder->setBlenderSpeed(BLENDER_REVERSE_SPEED);
				//frc::DriverStation::ReportError("Flipping blender");
			}
		}
		else {
			if(feeder->getBlenderSpeed() != BLENDER_SPEED) {
				feeder->setBlenderSpeed(BLENDER_SPEED);
			}
		}
	}

	else {
		/*if(feeder->getBlenderSpeed() != 0.0) {
			feeder->setBlenderSpeed(0.0);
		}

		if(feeder->getFeederSpeed() != 0.0) {
			feeder->setFeederSpeed(0.0);
		}*/
		shoot_button_timer->Stop();
		shoot_button_timer->Reset();
		shoot_button_timer->Stop();
	}


	/*if(shoot_button_timer->Get() > SHOOT_BUTTON_TIME) {
		//frc::DriverStation::ReportError("Stopping timer: " + std::to_string(shoot_button_timer->Get()));
		shoot_button_timer->Stop();
		if(!button_box_1->GetRawButton(OIPorts::B_SHOOT)) {
			//frc::DriverStation::ReportError("Stopping shoot button");
			feeder->setBlenderSpeed(0.0);
			feeder->setFeederSpeed(0.0);
			shoot_button_timer->Reset();
		}
	}*/



	if(button_box_1->GetRawButton(OIPorts::S2_CAMERA_TOGGLE) && (NetworkTable::GetTable("CameraPublisher/GearCam")->GetString("settings", "") == "vision")) {
		NetworkTable::GetTable("CameraPublisher/GearCam")->PutString("settings", "human");
		NetworkTable::GetTable("CameraPublisher/ShooterCam")->PutString("settings", "human");
	}
	else if(!button_box_1->GetRawButton(OIPorts::S2_CAMERA_TOGGLE) && (NetworkTable::GetTable("CameraPublisher/GearCam")->GetString("settings", "") == "human")) {
		NetworkTable::GetTable("CameraPublisher/GearCam")->PutString("settings", "vision");
		NetworkTable::GetTable("CameraPublisher/ShooterCam")->PutString("settings", "vision");
	}


	if(joy_right->GetRawButton(OIPorts::B_TURN_TO_GEAR)) {
		if(vision->canSeeGearHook() && !mobility->isTrackingGear()) {
			frc::DriverStation::ReportError("Start");
			mobility->startTrackGear();
		}
	}
	else {
		//frc::DriverStation::ReportError("Stop");
		mobility->stopTrackGear();
	}

	/*if(button_box_2->GetRawButton(OIPorts::B_GEAR_AUTO_ALIGN) && !vision->isTurningToGearHook()) {
		frc::DriverStation::ReportError("Turn button");
		vision->turnToGearHook();
	}*/

	if (button_box_3->GetRawButton(OIPorts::MOBILITY_ROTATION_PID) && (!mobility->isRotationPIDEnabled())) {
		mobility->use_rotation_PID = true;
		log->write(Log::WARNING_LEVEL, "Enabled Mobility Rotation PID");
	}
	else if(!button_box_3->GetRawButton(OIPorts::MOBILITY_ROTATION_PID) && (mobility->isRotationPIDEnabled())) {
		mobility->use_rotation_PID = false;
		log->write(Log::WARNING_LEVEL, "Disabled Mobility Rotation PID");
	}
	if (button_box_3->GetRawButton(OIPorts::MOBILITY_DISTANCE_PID) && (!mobility->isDistancePIDEnabled())) {
		mobility->use_distance_PID = true;
		log->write(Log::WARNING_LEVEL, "Enabling Mobility Distance PID");
	}
	else if (!button_box_3->GetRawButton(OIPorts::MOBILITY_DISTANCE_PID) && (mobility->isDistancePIDEnabled())) {
		mobility->use_distance_PID = false;
		log->write(Log::WARNING_LEVEL, "Disabling Mobility Distance PID");
	}
	if (button_box_3->GetRawButton(OIPorts::SHOOTER_SPEED_PID) && (!shooter->isShooterPIDEnabled())) {
		shooter->enableShooterPID();
		log->write(Log::WARNING_LEVEL, "Enabling Shooter Speed PID");
	}
	else if (!button_box_3->GetRawButton(OIPorts::SHOOTER_SPEED_PID) && (shooter->isShooterPIDEnabled())) {
		shooter->disableShooterPID();
		log->write(Log::WARNING_LEVEL, "Disabling Shooter Speed PID");
	}
	if (button_box_3->GetRawButton(OIPorts::SHOOTER_AZIMUTH_ANGLE_PID) && (!shooter->isAzimuthPIDEnabled())) {
		shooter->enableAzimuthPID();
		log->write(Log::WARNING_LEVEL, "Enabling Shooter Azimuth Angle PID");
	}
	else if (!button_box_3->GetRawButton(OIPorts::SHOOTER_AZIMUTH_ANGLE_PID) && (shooter->isAzimuthPIDEnabled())) {
		shooter->disableAzimuthPID();
		log->write(Log::WARNING_LEVEL, "Disabling Shooter Azimuth Angle PID");
	}
	if(button_box_3->GetRawButton(OIPorts::MOBILITY_LEFT_ENCODER) && (!mobility->isLeftEncoderEnabled())) {
		mobility->enableLeftEncoder();
		log->write(Log::WARNING_LEVEL, "Enabling Mobility Left Encoder");
	}
	else if (!button_box_3->GetRawButton(OIPorts::MOBILITY_LEFT_ENCODER)&&(mobility->isLeftEncoderEnabled())) {
		mobility->disableLeftEncoder();
		log->write(Log::WARNING_LEVEL, "Disabling Mobility Left Encoder");
	}
	if (button_box_3->GetRawButton(OIPorts::MOBILITY_RIGHT_ENCODER)&&(!mobility->isRightEncoderEnabled())) {
		mobility->enableRightEncoder();
		log->write(Log::WARNING_LEVEL, "Enabling Mobility Right Encoder");
	}
	else if (!button_box_3->GetRawButton(OIPorts::MOBILITY_RIGHT_ENCODER)&&(mobility->isRightEncoderEnabled())) {
		mobility->disableRightEncoder();
		log->write(Log::WARNING_LEVEL, "Disabling Mobility Right Encoder");
	}
	if (button_box_3->GetRawButton(OIPorts::SHOOTER_AZIMUTH_ENCODER)&&(!shooter->isShooterAzimuthEncoderEnabled())) {
		shooter->enableShooterAzimuthEncoder();
		log->write(Log::WARNING_LEVEL, "Enabling Shooter Azimuth Encoder");
	}
	else if (!button_box_3->GetRawButton(OIPorts::SHOOTER_AZIMUTH_ENCODER)&&(shooter->isShooterAzimuthEncoderEnabled())) {
		shooter->disableShooterAzimuthEncoder();
		log->write(Log::WARNING_LEVEL, "Disabling Shooter Azimuth Encoder");
	}
	/*if (button_box_1->GetRawButton(OIPorts::SHOOTER_AZIMUTH_LIMIT_SWITCH)&&(!shooter->isShooterAzimuthLimitSwitchEnabled())) {
		shooter->enableShooterAzimuthLimitSwitch();
	}
	else if (!button_box_1->GetRawButton(OIPorts::SHOOTER_AZIMUTH_LIMIT_SWITCH)&&(shooter->isShooterAzimuthLimitSwitchEnabled())) {
		shooter->disableShooterAzimuthLimitSwitch();
	} */
	if (button_box_3->GetRawButton(OIPorts::SHOOTER_SPEED_ENCODER)&&(!shooter->isShooterSpeedEncoderEnabled())) {
		shooter->enableShooterSpeedEncoder();
		log->write(Log::WARNING_LEVEL, "Enabling Shooter Speed Encoder");
	}
	else if(!button_box_3->GetRawButton(OIPorts::SHOOTER_SPEED_ENCODER)&&(shooter->isShooterSpeedEncoderEnabled())) {
		shooter->disableShooterSpeedEncoder();
		log->write(Log::WARNING_LEVEL, "Disabling Shooter Speed Encoder");
	}
}

OI* OI::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new OI();
	}

	return INSTANCE;
}
