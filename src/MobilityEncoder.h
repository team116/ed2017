/*
 * MobilityEncoders.h
 *
 *  Created on: Jan 23, 2017
 *      Author: amanzeb
 */

#ifndef SRC_MOBILITYENCODER_H_
#define SRC_MOBILITYENCODER_H_

#include <PIDSource.h>
#include <Encoder.h>

class MobilityEncoder: public frc::PIDSource {
public:
	MobilityEncoder();

	void SetPIDSourceType(frc::PIDSourceType source);
	frc::PIDSourceType GetPIDSourceType();
	double PIDGet();

	frc::Encoder* left_drive_encoder;
	frc::Encoder* right_drive_encoder;

	float getLeftEncoderRates();
	float getRightEncoderRates();


	void DriveEncoderReset();


private:
	frc::PIDSourceType pid_source;
};

#endif /* SRC_MOBILITYENCODER_H_ */
