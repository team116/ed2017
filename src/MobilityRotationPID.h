/*
 * MobilityRotationPID.h
 *
 *  Created on: Jan 20, 2017
 *      Author: Emina Ermin
 */

#ifndef MOBILITYROTATIONPID_H_
#define MOBILITYROTATIONPID_H_

#include <PIDOutput.h>
#include <Mobility.h>

class MobilityRotationPID: public frc::PIDOutput {
public:
	MobilityRotationPID();
	void PIDWrite(double output);

	virtual ~MobilityRotationPID(){};

private:
	float forward;
};

#endif /* MOBILITYROTATIONPID_H_ */
