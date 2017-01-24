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
	joy_left = new Joystick(OIPorts::JOYSTICK_LEFT);
	joy_right = new Joystick(OIPorts::JOYSTICK_RIGHT);
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
}

OI* OI::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new OI();
	}

	return INSTANCE;
}
