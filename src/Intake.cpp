/*
 * Intake.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Intake.h>

Intake* Intake::INSTANCE = nullptr;

Intake::Intake() {
	// TODO Auto-generated constructor stub

}

Intake* Intake::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Intake();
	}

	return INSTANCE;
}
