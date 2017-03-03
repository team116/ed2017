/*
 * Wiggle.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/Wiggle.h>

Wiggle::Wiggle() {
	mobility = Mobility::getInstance();
	wiggle_timer = new frc::Timer();
	left_side = false;

	setTimeout(1.0);

}
void Wiggle::start() {
	wiggle_timer->Start();
}
void Wiggle::process() {
	if (wiggle_timer->Get() >= 0.25) {
		if (left_side == true) {
			mobility->setLeft(0.25);
			mobility->setRight(0.0);
			left_side = false;
		}
		else {
			mobility->setLeft(0.0);
			mobility->setRight(0.25);
			left_side = true;
		}
		wiggle_timer->Reset();
	}

}
void Wiggle::end() {
	mobility->setLeft(0.0);
	mobility->setRight(0.0);
}
bool Wiggle::isFinished() {
	return false;
}
