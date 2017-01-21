/*
 * MobilityRotationPID.cpp
 *
 *  Created on: Jan 20, 2017
 *      Author: Emina Ermin
 */

#include "MobilityRotationPID.h"

MobilityRotationPID::MobilityRotationPID() {
	// TODO Auto-generated constructor stub
}

void MobilityRotationPID::PIDWrite(double output) {
	Mobility::getInstance()->setLeft(output);
	Mobility::getInstance()->setRight(-output);
}
