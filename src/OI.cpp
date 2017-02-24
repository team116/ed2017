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
const float BLENDER_SPEED = 1.0;
const float BLENDER_REVERSE_SPEED = -1.0;
const float FEEDER_SPEED = 1.0;
const float FEEDER_REVERSE_SPEED = -1.0;

const float SHOOT_BUTTON_TIME = 1.0;

OI::OI() {
	// TODO Auto-generated constructor stub

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
	if(mobility->isTurnDegreesDone() && mobility->isDriveDistanceDone()) {
		if (joy_left->GetRawButton(OIPorts::B_DRIVE_STRAIGHT)) {
			if (!mobility->isDrivingStraight()) {
				mobility->startDriveStraight();
			}
			mobility->setStraightSpeed(joy_left->GetRawAxis(OIPorts::AXIS_Y) * -1);
		}
		else if (joy_right->GetRawButton(OIPorts::B_DRIVE_STRAIGHT)) {
			if (!mobility->isDrivingStraight()) {
				mobility->startDriveStraight();
			}
			mobility->setStraightSpeed(joy_right->GetRawAxis(OIPorts::AXIS_Y) * -1);
		}
		else if(joy_right->GetRawButton(OIPorts::B_ROTATE)) {
			mobility->setLeft(joy_right->GetRawAxis(OIPorts::AXIS_Z));
			mobility->setRight(joy_right->GetRawAxis(OIPorts::AXIS_Z) * -1);
		}
		else if(joy_left->GetRawButton(OIPorts::B_ROTATE)) {
				mobility->setLeft(joy_left->GetRawAxis(OIPorts::AXIS_Z));
				mobility->setRight(joy_left->GetRawAxis(OIPorts::AXIS_Z) * -1);
			}
		else {
			if(mobility->isDrivingStraight()) {
				mobility->stopDriveStraight();
			}
			mobility->setLeft(joy_left->GetRawAxis(OIPorts::AXIS_Y) * -1);
			mobility->setRight(joy_right->GetRawAxis(OIPorts::AXIS_Y) * -1);
		}
	}



	if (button_box_2->GetRawButton(OIPorts::B_GEAR_RELEASE) && !gear->isOpen()) {
		gear->open();
		//frc::DriverStation::ReportError("Opening gear");

	}
	else if(!button_box_2->GetRawButton(OIPorts::B_GEAR_RELEASE) && gear->isOpen()) {
		gear->close();
		//frc::DriverStation::ReportError("Closing gear");
	}



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

	/*percent = (button_box_2->GetRawAxis(OIPorts::P_CLIMBER_SPEED));
	if(button_box_1->GetRawButton(OIPorts::S2_AUTO_AZIMUTH_TOGGLE) && (shooter->getAzimuthSpeed() != percent)) {
		shooter->setAzimuthSpeed(percent);
	}
	else if(!button_box_1->GetRawButton(OIPorts::S2_AUTO_AZIMUTH_TOGGLE) && (shooter->getAzimuthSpeed() != 0.0)) {
		shooter->setAzimuthSpeed(0.0);
	}*/



	percent = (-1 * button_box_1->GetRawAxis(OIPorts::P_SHOOTER_SPEED) * 0.4) + 0.6;
	float speed = percent * SHOOTER_SPEED;
	if(button_box_1->GetRawButton(OIPorts::S2_SHOOTER_WHEELS_TOGGLE) && (speed != shooter->getSpeed())) {
		//float speed = std::stof(SmartDashboard::GetString("DB/String 0", std::to_string(0.0)));
		shooter->setShooterSpeed(speed);
		//shooter->setShooterRPM(speed);
		//frc::DriverStation::ReportError("Shooter on " + std::to_string(speed));
	}
	else if (!button_box_1->GetRawButton(OIPorts::S2_SHOOTER_WHEELS_TOGGLE) && (00 != shooter->getSpeed())) {
		shooter->setShooterSpeed(0);
	    //frc::DriverStation::ReportError("Shooter off");
	}



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
			frc::DriverStation::ReportError("Blending forward");
		}
		else if (button_box_2->GetRawButton(OIPorts::S3_BLENDER_REVERSE) && (BLENDER_REVERSE_SPEED != feeder->getBlenderSpeed())) {
			feeder->setBlenderSpeed(BLENDER_REVERSE_SPEED);
			frc::DriverStation::ReportError("Blender reverse");
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



	if(button_box_1->GetRawButton(OIPorts::B_SHOOT) && (shoot_button_timer->Get() <= 0.0)) {
		shoot_button_timer->Start();
		if(feeder->getBlenderSpeed() != BLENDER_SPEED) {
			feeder->setBlenderSpeed(BLENDER_SPEED);
		}
		if(feeder->getFeederSpeed() != FEEDER_SPEED) {
			feeder->setFeederSpeed(FEEDER_SPEED);
		}
	}


	if(shoot_button_timer->Get() > SHOOT_BUTTON_TIME) {
		//frc::DriverStation::ReportError("Stopping timer: " + std::to_string(shoot_button_timer->Get()));
		shoot_button_timer->Stop();
		if(!button_box_1->GetRawButton(OIPorts::B_SHOOT)) {
			//frc::DriverStation::ReportError("Stopping shoot button");
			feeder->setBlenderSpeed(0.0);
			feeder->setFeederSpeed(0.0);
			shoot_button_timer->Reset();
		}
	}



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
		frc::DriverStation::ReportError("Stop");
		mobility->stopTrackGear();
	}

	/*if(button_box_2->GetRawButton(OIPorts::B_GEAR_AUTO_ALIGN) && !vision->isTurningToGearHook()) {
		frc::DriverStation::ReportError("Turn button");
		vision->turnToGearHook();
	}*/

	/*if (button_box_1->GetRawButton(OIPorts::MOBILITY_ROTATION_PID_SWITCH) && (!mobility->isRotationPIDEnabled())) {
		mobility->enableRotationPID();
	}
	else if(!button_box_1->GetRawButton(OIPorts::MOBILITY_ROTATION_PID_SWITCH) && (mobility->isRotationPIDEnabled())) {
		mobility->disableRotationPID();
	}
	if (button_box_1->GetRawButton(OIPorts::MOBILITY_DISTANCE_PID_SWITCH) && (!mobility->isDistancePIDEnabled())) {
		mobility->enableDistancePID();
	}
	else if (!button_box_1->GetRawButton(OIPorts::MOBILITY_DISTANCE_PID_SWITCH) && (mobility->isDistancePIDEnabled())) {
		mobility->disableDistancePID();
	}
	if (button_box_1->GetRawButton(OIPorts::SHOOTER_SPEED_PID_SWITCH) && (!shooter->isShooterPIDEnabled())) {
		shooter->enableShooterPID();
	}
	else if (!button_box_1->GetRawButton(OIPorts::SHOOTER_SPEED_PID_SWITCH) && (shooter->isShooterPIDEnabled())) {
		shooter->disableShooterPID();
	}
	if (button_box_1->GetRawButton(OIPorts::SHOOTER_AZIMUTH_ANGLE_PID_SWITCH) && (!shooter->isAzimuthPIDEnabled())) {
		shooter->enableAzimuthPID();
	}
	else if (!button_box_1->GetRawButton(OIPorts::SHOOTER_AZIMUTH_ANGLE_PID_SWITCH) && (shooter->isAzimuthPIDEnabled())) {
		shooter->disableAzimuthPID();
	}
	if(button_box_1->GetRawButton(OIPorts::MOBILITY_LEFT_ENCODER_SWITCH) && (!mobility->isLeftEncoderEnabled())) {
		mobility->enableLeftEncoder();
	}
	else if (!button_box_1->GetRawButton(OIPorts::MOBILITY_LEFT_ENCODER_SWITCH)&&(mobility->isLeftEncoderEnabled())) {
		mobility->disableLeftEncoder();
	}
	if (button_box_1->GetRawButton(OIPorts::MOBILITY_RIGHT_ENCODER_SWITCH)&&(!mobility->isRightEncoderEnabled())) {
		mobility->enableRightEncoder();
	}
	else if (!button_box_1->GetRawButton(OIPorts::MOBILITY_RIGHT_ENCODER_SWITCH)&&(mobility->isRightEncoderEnabled())) {
		mobility->disableRightEncoder();
	}
	if (button_box_1->GetRawButton(OIPorts::SHOOTER_AZIMUTH_ENCODER_SWITCH)&&(!shooter->isShooterAzimuthEncoderEnabled())) {
		shooter->enableShooterAzimuthEncoder();
	}
	else if (!button_box_1->GetRawButton(OIPorts::SHOOTER_AZIMUTH_ENCODER_SWITCH)&&(shooter->isShooterAzimuthEncoderEnabled())) {
		shooter->disableShooterAzimuthEncoder();
	}
	if (button_box_1->GetRawButton(OIPorts::SHOOTER_AZIMUTH_LIMIT_SWITCH)&&(!shooter->isShooterAzimuthLimitSwitchEnabled())) {
		shooter->enableShooterAzimuthLimitSwitch();
	}
	else if (!button_box_1->GetRawButton(OIPorts::SHOOTER_AZIMUTH_LIMIT_SWITCH)&&(shooter->isShooterAzimuthLimitSwitchEnabled())) {
		shooter->disableShooterAzimuthLimitSwitch();
	}
	if (button_box_1->GetRawButton(OIPorts::SHOOTER_SPEED_ENCODER_SWITCH)&&(!shooter->isShooterSpeedEncoderEnabled())) {
		shooter->enableShooterAzimuthLimitSwitch();
	}
	else if(!button_box_1->GetRawButton(OIPorts::SHOOTER_SPEED_ENCODER_SWITCH)&&(shooter->isShooterSpeedEncoderEnabled())) {
		shooter->disableShooterAzimuthLimitSwitch();
	}*/
}

OI* OI::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new OI();
	}

	return INSTANCE;
}
