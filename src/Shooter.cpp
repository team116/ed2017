/*
 * Shooter.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Shooter.h>

Shooter* Shooter::INSTANCE = nullptr;

Shooter::Shooter() {
	// TODO Auto-generated constructor stub
	ball_holder = new VictorSP(6);
	shooter = new VictorSP(7);
	azimuth = new VictorSP(8);
	pitch = new VictorSP(9);
}

void Shooter::process() {

}

void Shooter::setSpeedPitch(float speed) {
	pitch->Set(speed);
}

void Shooter::setSpeedAzimuth(float speed) {
	azimuth->Set(speed);
}

void Shooter::setSpeedShooter(float speed) {
	shooter->Set(speed);
}

Shooter* Shooter::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Shooter();
	}

	return INSTANCE;
}
