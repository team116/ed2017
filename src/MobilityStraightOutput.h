/*

 * MobilityStraightOutput.h
 *
 *  Created on: Jan 23, 2017
 *      Author: amanzeb
 */

#ifndef SRC_MOBILITYSTRAIGHTOUTPUT_H_
#define SRC_MOBILITYSTRAIGHTOUTPUT_H_

#include <PIDOutput.h>

class MobilityStraightOutput: public frc::PIDOutput {
public:
	MobilityStraightOutput(frc::SpeedController* fl, frc::SpeedController* fr, frc::SpeedController* br, frc::SpeedController* bl);

	void PIDWrite(double output);
	void Enable();
	void Disable();


private:
	frc::SpeedController* front_left;
	frc::SpeedController* front_right;
	frc::SpeedController* back_right;
	frc::SpeedController* back_left;

	bool enabled;
};

#endif /* SRC_MOBILITYSTRAIGHTOUTPUT_H_ */
