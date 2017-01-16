/*
 * Climber.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Climber.h>

Climber* Climber::INSTANCE = nullptr;

Climber::Climber() {
	// TODO Auto-generated constructor stub
	climber = new VictorSP(5);
}

void Climber::process() {

}

void Climber::climbUp(float speed) {
	climber->Set(1.0);
}

void Climber::climbDown(float speed) {
	climber->Set(-1.0);
}

void Climber::climbStop(float speed) {
	climber->Set(0.0);
}

Climber* Climber::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Climber();
	}

	return INSTANCE;
}
