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

}

Shooter* Shooter::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Shooter();
	}

	return INSTANCE;
}
