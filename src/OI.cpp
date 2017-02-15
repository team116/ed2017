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
const float SHOOTER_SPEED = 1.0;
const float INTAKE_SPEED = 1.0;
const float OPPOSITE_INTAKE_SPEED = -1.0;
const float BLENDER_SPEED = 1.0;
const float BLENDER_REVERSE_SPEED = -1.0;
const float FEEDER_SPEED = 1.0;
const float FEEDER_REVERSE_SPEED = -1.0;

OI::OI() {
	// TODO Auto-generated constructor stub

	mobility = Mobility::getInstance();
	gear = Gear::getInstance();
	climber = Climber::getInstance();
	shooter = Shooter::getInstance();
	intake = Intake::getInstance();
	feeder = Feeder::getInstance();
	joy_left = new frc::Joystick(OIPorts::JOYSTICK_LEFT);
	joy_right = new frc::Joystick(OIPorts::JOYSTICK_RIGHT);
	button_box_1 = new frc::Joystick(OIPorts::JOYSTICK_BUTTONS_1);
	button_box_2 = new frc::Joystick(OIPorts::JOYSTICK_BUTTONS_2);
}

void OI::process() {
	if (joy_left->GetRawButton(OIPorts::BUTTON_DRIVE_STRAIGHT)) {
		if (!mobility->isDrivingStraight()) {
			mobility->startDriveStraight();
		}
		mobility->setStraightSpeed(joy_left->GetRawAxis(OIPorts::AXIS_Y) * -1);
	}
	else if (joy_right->GetRawButton(OIPorts::BUTTON_DRIVE_STRAIGHT)) {
		if (!mobility->isDrivingStraight()) {
			mobility->startDriveStraight();
		}
		mobility->setStraightSpeed(joy_right->GetRawAxis(OIPorts::AXIS_Y) * -1);
	}
	else if(joy_right->GetRawButton(OIPorts::ROTATE_BUTTON)) {
		mobility->setLeft(joy_right->GetRawAxis(OIPorts::AXIS_Z));
		mobility->setRight(joy_right->GetRawAxis(OIPorts::AXIS_Z) * -1);
	}
	else if(joy_left->GetRawButton(OIPorts::ROTATE_BUTTON)) {
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
	if (button_box_1->GetRawButton(OIPorts::OPEN_GEAR_BUTTON) && !gear->isOpen()) {
		gear->open();
		frc::DriverStation::ReportError("Opening gear");

	}
	else if(!button_box_1->GetRawButton(OIPorts::OPEN_GEAR_BUTTON) && gear->isOpen()) {
		gear->close();
		frc::DriverStation::ReportError("Closing gear");
	}
	if(button_box_1->GetRawButton(OIPorts::CLIMBER_ON_SWITCH) && (CLIMB_SPEED != climber->getSpeed())) {
		//Percent from 0.2 to 1.0
		float percent = (-1 * button_box_1->GetRawAxis(OIPorts::AXIS_Z) * 0.4) + 0.6;
		climber->moveClimber(percent * CLIMB_SPEED);
		//frc::DriverStation::ReportError("Moving up");
	}
	else if(!button_box_1->GetRawButton(OIPorts::CLIMBER_ON_SWITCH) || (0.0 != climber->getSpeed())) {
		climber->moveClimber(0);
		//frc::DriverStation::ReportError("Stopped moving");
	}
	if(button_box_1->GetRawButton(OIPorts::SHOOTER_ON_SWITCH) && (SHOOTER_SPEED != shooter->getSpeed())) {
		shooter->setShooterRPM(SHOOTER_SPEED);
		//frc::DriverStation::ReportError("Shooter on");
	}
	else if (!button_box_1->GetRawButton(OIPorts::SHOOTER_ON_SWITCH) || (0.0 != shooter->getSpeed())) {
		shooter->setShooterRPM(0);
	    //frc::DriverStation::ReportError("Shooter off");
	}
	if (button_box_1->GetRawButton(OIPorts::INTAKE_ROLLER_IN) && (INTAKE_SPEED != intake->getSpeed())) {
		intake->setSpeedIntake(INTAKE_SPEED);
	    //frc::DriverStation::ReportError("Intaking");
	}
	else if (button_box_1->GetRawButton(OIPorts::INTAKE_ROLLER_OUT) && (OPPOSITE_INTAKE_SPEED != intake->getSpeed())) {
		intake->setSpeedIntake(OPPOSITE_INTAKE_SPEED);
	    //frc::DriverStation::ReportError("Opposite-intaking");
	}
	else if (!button_box_1->GetRawButton(OIPorts::INTAKE_ROLLER_IN) && (!button_box_1->GetRawButton(OIPorts::INTAKE_ROLLER_OUT))) {
		intake->setSpeedIntake(0);
	    //frc::DriverStation::ReportError("Intake and opposite-intake off");
	}

	if (button_box_1->GetRawButton(OIPorts::BLENDER_FORWARD_SWITCH) && (BLENDER_SPEED != feeder->getSpeed())) {
		feeder->setBlenderSpeed(BLENDER_SPEED);
		frc::DriverStation::ReportError("Blending forward");
	}
	else if (button_box_1->GetRawButton(OIPorts::BLENDER_REVERSE_SWITCH) && (BLENDER_REVERSE_SPEED != feeder->getSpeed())) {
		feeder->setBlenderSpeed(BLENDER_REVERSE_SPEED);
		frc::DriverStation::ReportError("Blender reverse");
	}
	else if (!button_box_1->GetRawButton(OIPorts::BLENDER_FORWARD_SWITCH) && (!button_box_1->GetRawButton(OIPorts::BLENDER_REVERSE_SWITCH))) {
		feeder->setBlenderSpeed(0);
		frc::DriverStation::ReportError("Blender off");
	}

	if (button_box_1->GetRawButton(OIPorts::FEEDER_FORWARD_SWITCH) && (FEEDER_SPEED != feeder->getSpeed())) {
		feeder->setFeederSpeed(FEEDER_SPEED);
		//frc::DriverStation::ReportError("Feeding forward");
	}
	else if (button_box_1->GetRawButton(OIPorts::FEEDER_REVERSE_SWITCH) && (FEEDER_REVERSE_SPEED != feeder->getSpeed())) {
		feeder->setFeederSpeed(FEEDER_REVERSE_SPEED);
		//frc::DriverStation::ReportError("Feeding reverse");
	}
	else if (!button_box_1->GetRawButton(OIPorts::FEEDER_FORWARD_SWITCH) && (!button_box_1->GetRawButton(OIPorts::FEEDER_REVERSE_SWITCH))) {
		feeder->setFeederSpeed(0);
		//frc::DriverStation::ReportError("Feeder off");
	}
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
