/*
 * OI.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <OI.h>
#include "Ports.h"

OI* OI::INSTANCE = nullptr;

OI::OI() {
	// TODO Auto-generated constructor stub
	mobility = Mobility::getInstance();
	gear = Gear::getInstance();
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
}

OI* OI::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new OI();
	}

	return INSTANCE;
}
