/*
 * OI.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <OI.h>

OI* OI::INSTANCE = nullptr;

OI::OI() {
	// TODO Auto-generated constructor stub

}

OI* OI::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new OI();
	}

	return INSTANCE;
}
