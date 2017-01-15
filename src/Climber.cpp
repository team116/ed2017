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

}

void Climber::process() {

}

Climber* Climber::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Climber();
	}

	return INSTANCE;
}
