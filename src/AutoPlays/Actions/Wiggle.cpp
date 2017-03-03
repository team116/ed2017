/*
 * Wiggle.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/Wiggle.h>


const float SPEED = 0.5;
const float PERIOD = 0.25;

Wiggle::Wiggle(float time) {
	mobility = Mobility::getInstance();
	wiggle_timer = new frc::Timer();
	left_side = false;

	setTimeout(time);

}
void Wiggle::start() {
	wiggle_timer->Start();
}
void Wiggle::process() {
	if (wiggle_timer->Get() >= PERIOD) {
		if (left_side == true) {
			mobility->setLeft(SPEED);
			mobility->setRight(0.0);
			left_side = false;
		}
		else {
			mobility->setLeft(0.0);
			mobility->setRight(SPEED);
			left_side = true;
		}
		wiggle_timer->Reset();
		wiggle_timer->Start();
	}

}
void Wiggle::end() {
	mobility->setLeft(0.0);
	mobility->setRight(0.0);
}
bool Wiggle::isFinished() {
	return false;
}
