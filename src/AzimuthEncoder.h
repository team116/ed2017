/*
 * AzimuthEncoder.h
 *
 *  Created on: Feb 15, 2017
 *      Author: Emina Ermin
 */

#ifndef SRC_AZIMUTHENCODER_H_
#define SRC_AZIMUTHENCODER_H_

#include <AnalogPotentiometer.h>

class AzimuthEncoder {
public:
	AzimuthEncoder();
	float getAngle();
	void process();

private:
	frc::AnalogPotentiometer* pot;
	float prev_angle;
	float full_rotations;
};

#endif /* SRC_AZIMUTHENCODER_H_ */
