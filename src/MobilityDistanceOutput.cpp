/*
 * MobilityStraightOutput.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: amanzeb
 */

#include <MobilityDistanceOutput.h>

MobilityDistanceOutput::MobilityDistanceOutput(frc::SpeedController* fl, frc::SpeedController* fr, frc::SpeedController* bl, frc::SpeedController* br) {
	front_left = fl;
	front_right = fr;
	back_left = bl;
	back_right = br;

	enabled = false;
}

void MobilityDistanceOutput::PIDWrite(double output) {
	if(!enabled)
		return;
	front_left->Set(output);
	front_right->Set(output);
	back_right->Set(output);
	back_left->Set(output);
}

void MobilityDistanceOutput::Enable() {
	enabled = true;
}

void MobilityDistanceOutput::Disable() {
	enabled = false;
}
