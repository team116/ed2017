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
	intake_Motor = new VictorSP(10);
}

void Intake::process() {

}

void Intake::setSpeedIntake(float speed) {
	intake_Motor->Set(1.0);
}

Intake* Intake::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Intake();
	}

	return INSTANCE;
}
