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
	mobility->setLeft(joy_left->GetRawAxis(1) * -1);
	mobility->setRight(joy_right->GetRawAxis(1) * -1);
	/*if (joy_one->GetRawButton(1)) {
		mobility->setAngle()
	} */
}

OI* OI::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new OI();
	}

	return INSTANCE;
}
