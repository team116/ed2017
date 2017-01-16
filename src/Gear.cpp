/*
 * Gear.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */


#include <Gear.h>

Gear* Gear::INSTANCE = nullptr;
const float Gear::CLOSED_ANGLE = 0.0;
const float Gear::OPEN_ANGLE = 30.0;


Gear::Gear() {
	// TODO Auto-generated constructor stub
	servo = new Servo(4);
}

void Gear::open() {
	servo->SetAngle(OPEN_ANGLE);
}

void Gear::close() {
	servo->SetAngle(CLOSED_ANGLE);
}

void Gear::process() {

}

Gear* Gear::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Gear();
	}

	return INSTANCE;
}
