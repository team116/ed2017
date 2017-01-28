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
OI::OI() {
	// TODO Auto-generated constructor stub
	mobility = Mobility::getInstance();
	gear = Gear::getInstance();
	climber = Climber::getInstance();
	shooter = Shooter::getInstance();
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
	if(button_box_1->GetRawButton(OIPorts::CLIMBER_UP_SWITCH) && (CLIMB_SPEED != climber->getSpeed())) {
		climber->moveClimber(CLIMB_SPEED);
		frc::DriverStation::ReportError("Moving up");
	}
	else if(!button_box_1->GetRawButton(OIPorts::CLIMBER_UP_SWITCH) || (0.0 != climber->getSpeed())) {
		climber->moveClimber(0);
		frc::DriverStation::ReportError("Stopped moving");
	}
	if(button_box_1->GetRawButton(OIPorts::SHOOTER_ON_SWITCH) && (SHOOTER_SPEED != shooter->getSpeed())) {
		shooter->setShooterRPM(SHOOTER_SPEED);
		frc::DriverStation::ReportError("Shooter on");
	}
	else if (!button_box_1->GetRawButton(OIPorts::SHOOTER_ON_SWITCH) || (0.0 != shooter->getSpeed())) {
		shooter->setShooterRPM(0);
	    frc::DriverStation::ReportError("Shooter off");
	}
}

OI* OI::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new OI();
	}

	return INSTANCE;
}
