/*
 * AzimuthEncoder.h
 *
 *  Created on: Feb 15, 2017
 *      Author: Emina Ermin
 */

#ifndef SRC_AZIMUTHENCODER_H_
#define SRC_AZIMUTHENCODER_H_

#include <AnalogPotentiometer.h>
#include <PIDSource.h>

class AzimuthEncoder : public frc::PIDSource {
public:
	AzimuthEncoder();
	float getAngle();
	void process();

	double PIDGet();

	void reset();

private:
	frc::AnalogPotentiometer* pot;
	float prev_angle;
	float full_rotations;

	float angle_offset;
};

#endif /* SRC_AZIMUTHENCODER_H_ */
