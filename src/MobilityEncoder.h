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
#include "Log.h"

class MobilityEncoder: public frc::PIDSource {
public:
	MobilityEncoder();

	Log* log;

	void SetPIDSourceType(frc::PIDSourceType source);
	frc::PIDSourceType GetPIDSourceType();
	double PIDGet();

	frc::Encoder* left_drive_encoder;
	frc::Encoder* right_drive_encoder;

	float getLeftEncoderRates();
	float getRightEncoderRates();

	void enableLeftEncoder();
	void disableLeftEncoder();
	bool isLeftEncoderEnabled();
	void enableRightEncoder();
	void disableRightEncoder();
	bool isRightEncoderEnabled();

	void DriveEncoderReset();

	virtual ~MobilityEncoder() {};

private:
	frc::PIDSourceType pid_source;

	bool use_left_enc;
	bool use_right_enc;
};

#endif /* SRC_MOBILITYENCODER_H_ */
