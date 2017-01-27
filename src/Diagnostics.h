/*
 * Diagnostics.h
 *
 *  Created on: Jan 25, 2017
 *      Author: Emina Ermin
 */

#ifndef DIAGNOSTICS_H_
#define DIAGNOSTICS_H_
#include "Mobility.h"
#include <BuiltInAccelerometer.h>
#include <Timer.h>

class Diagnostics {
public:
	static Diagnostics* getInstance();
	void process();

private:
	Diagnostics();
	static Diagnostics* INSTANCE;

	Mobility* mobility;
	frc::BuiltInAccelerometer* accel;
	frc::Timer* left_enc_timer;
	frc::Timer* right_enc_timer;


};

#endif /* DIAGNOSTICS_H_ */
