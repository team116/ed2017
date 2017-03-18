/*
 * MobilityRotationInput.h
 *
 *  Created on: Mar 14, 2017
 *      Author: Will
 */

#ifndef MOBILITYROTATIONINPUT_H_
#define MOBILITYROTATIONINPUT_H_

#include <PIDSource.h>
#include "../navx/AHRS.h"
#include "Vision.h"

class MobilityRotationInput: public frc::PIDSource {
public:
	MobilityRotationInput(AHRS* gyro);

	enum Source {
		Gyro,
		Camera
	};

	void setSource(Source s);
	Source getSource();

	double PIDGet();

private:
	Source source;

	AHRS* gyro;

	Vision* vision;
};

#endif /* MOBILITYROTATIONINPUT_H_ */
