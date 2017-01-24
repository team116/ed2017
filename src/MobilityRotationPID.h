/*
 * MobilityRotationPID.h
 *
 *  Created on: Jan 20, 2017
 *      Author: Emina Ermin
 */

#ifndef MOBILITYROTATIONPID_H_
#define MOBILITYROTATIONPID_H_

#include <PIDOutput.h>
#include <SpeedController.h>

class MobilityRotationPID: public frc::PIDOutput {
public:
	MobilityRotationPID(frc::SpeedController*, frc::SpeedController*, frc::SpeedController*, frc::SpeedController*);
	void PIDWrite(double output);

	void setForwardSpeed(float speed);

	void Enable();
	void Disable();

	virtual ~MobilityRotationPID(){};

private:
	float forward;

	bool enabled;

	frc::SpeedController* front_left;
	frc::SpeedController* front_right;
	frc::SpeedController* back_left;
	frc::SpeedController* back_right;
};

#endif /* MOBILITYROTATIONPID_H_ */
