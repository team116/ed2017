/*
 * Mobility.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Mobility.h>

Mobility* Mobility::INSTANCE = nullptr;

Mobility::Mobility() {

}

Mobility* Mobility::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Mobility();
	}

	return INSTANCE;
}
