/*
 * Autonomous.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Autonomous.h>

Autonomous* Autonomous::INSTANCE = nullptr;

Autonomous::Autonomous() {
	// TODO Auto-generated constructor stub

}

Autonomous* Autonomous::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Autonomous();
	}

	return INSTANCE;
}
