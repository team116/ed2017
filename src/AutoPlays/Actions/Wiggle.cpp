/*
 * Wiggle.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/Wiggle.h>


const float SPEED = 0.5;
const float PERIOD = 0.25;

Wiggle::Wiggle(Utils::Alliance color, Utils::AutoLocation location, float time) {
	mobility = Mobility::getInstance();
	wiggle_timer = new frc::Timer();
	left_side = false;

	loc = location;
	colour = color;

	setTimeout(time);

}
void Wiggle::start() {
	log->write(Log::INFO_LEVEL, "[Action] Starting Wiggle. Timeout: %f", getTimeout());
	wiggle_timer->Reset();
	wiggle_timer->Start();
		if (loc == Utils::AutoLocation::Boiler) {
			if (colour == Utils::Alliance::Blue) {
				left_side = false;
				mobility->setLeft(0.0);
				mobility->setRight(SPEED);
			}
			else if (colour == Utils::Alliance::Red) {
				left_side = true;
				mobility->setLeft(SPEED);
				mobility->setRight(0.0);
			}
		}
		else if (loc == Utils::AutoLocation::Middle) {
			if (colour == Utils::Alliance::Blue) {
				left_side = true;
				mobility->setLeft(SPEED);
				mobility->setRight(0.0);
			}
			else if (colour == Utils::Alliance::Red) {
				left_side = true;
				mobility->setLeft(SPEED);
				mobility->setRight(0.0);
			}
		}
		else if (loc == Utils::AutoLocation::LoadingStation) {
			if (colour == Utils::Alliance::Blue) {
				left_side = true;
				mobility->setLeft(SPEED);
				mobility->setRight(0.0);
			}
			else if (colour == Utils::Alliance::Red) {
				left_side = false;
				mobility->setLeft(0.0);
				mobility->setRight(SPEED);
			}
		}
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
	log->write(Log::INFO_LEVEL, "[Action] Ended Wiggle. Timeout: %f", getTimeout());
}
bool Wiggle::isFinished() {
	return false;
}
