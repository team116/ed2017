/*
 * OI.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <OI.h>

OI* OI::INSTANCE = nullptr;

OI::OI() {
	// TODO Auto-generated constructor stub
	mobility = Mobility::getInstance();
	joy_one = new Joystick(0);
	joy_two = new Joystick(1);
}

void OI::process() {
	mobility->setLeft(joy_one->GetRawAxis(1) * -1);
	mobility->setRight(joy_two->GetRawAxis(1) * -1);
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
