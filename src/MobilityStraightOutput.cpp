/*
 * MobilityStraightOutput.cpp
 *
 *  Created on: Jan 23, 2017
 *      Author: amanzeb
 */

#include <MobilityStraightOutput.h>

MobilityStraightOutput::MobilityStraightOutput(frc::SpeedController* fl, frc::SpeedController* fr, frc::SpeedController* bl, frc::SpeedController* br) {
	front_left = fl;
	front_right = fr;
	back_left = bl;
	back_right = br;

	enabled = false;
}

void MobilityStraightOutput::PIDWrite(double output) {
	if(!enabled)
		return;
	front_left->Set(output);
	front_right->Set(output);
	back_right->Set(output);
	back_left->Set(output);
}

void MobilityStraightOutput::Enable() {
	enabled = true;
}

void MobilityStraightOutput::Disable() {
	enabled = false;
}
