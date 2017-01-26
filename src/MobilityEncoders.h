/*
 * MobilityEncoders.h
 *
 *  Created on: Jan 23, 2017
 *      Author: amanzeb
 */

#ifndef SRC_MOBILITYENCODERS_H_
#define SRC_MOBILITYENCODERS_H_

#include <PIDSource.h>
#include <Encoder.h>

class MobilityEncoders: public frc::PIDSource {
public:
	MobilityEncoders();

	void SetPIDSourceType(frc::PIDSourceType source);
	frc::PIDSourceType GetPIDSourceType();
	double PIDGet();

	frc::Encoder* left_drive_encoder;
	frc::Encoder* right_drive_encoder;
	float getLeftEncoderRates();
	float getRightEncoderRates();


	const float pulseperdistance = 250;
	void DriveEncoderReset();


private:
	frc::PIDSourceType pid_source;
};

#endif /* SRC_MOBILITYENCODERS_H_ */
