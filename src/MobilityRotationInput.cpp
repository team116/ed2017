/*
 * MobilityRotationInput.cpp
 *
 *  Created on: Mar 14, 2017
 *      Author: Will
 */

#include "MobilityRotationInput.h"

MobilityRotationInput::MobilityRotationInput(AHRS* g) {
	// TODO Auto-generated constructor stub

	source = Source::Gyro;

	gyro = g;

	vision = Vision::getInstance();
}

void MobilityRotationInput::setSource(Source s) {
	source = s;
}

MobilityRotationInput::Source MobilityRotationInput::getSource() {
	return source;
}

double MobilityRotationInput::PIDGet() {
	switch(source) {
	case Source::Camera:
		if(vision->canSeeGearHook()) {
			NetworkTable::GetTable("Status/Mobility")->PutNumber("Rotation Input", vision->gearHookOffset() * -12.0);
			return vision->gearHookOffset() * -10.0;
		}
		else {
			NetworkTable::GetTable("Status/Mobility")->PutNumber("Rotation Input", 0.0);
			return 0.0;
		}
	case Source::Gyro:
		NetworkTable::GetTable("Status/Mobility")->PutNumber("Rotation Input", gyro->PIDGet());
		return gyro->PIDGet();
	}
}
