/*
 * Mobility.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Mobility.h>

Mobility* Mobility::INSTANCE = nullptr;

Mobility::Mobility() {
	front_left = new VictorSP(0);
	front_right = new VictorSP(1);
	back_right = new VictorSP(2);
	back_left = new VictorSP(3);
}

void Mobility::process() {

}

void Mobility::setLeft(float speed) {
	front_left->Set(speed);
	back_left->Set(speed);

}

void Mobility::setRight(float speed) {
	front_right->Set(speed);
	back_right->Set(speed);
}

Mobility* Mobility::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Mobility();
	}

	return INSTANCE;
}
