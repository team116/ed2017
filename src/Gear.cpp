/*
 * Gear.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */


#include <Gear.h>

Gear* Gear::INSTANCE = nullptr;

Gear::Gear() {
	// TODO Auto-generated constructor stub

}

Gear* Gear::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Gear();
	}

	return INSTANCE;
}
