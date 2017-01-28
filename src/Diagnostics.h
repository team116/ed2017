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
#include "Queue.h"

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
	Queue* accel_values;

	int left_enc_error_count;
	int right_enc_error_count;

};

#endif /* DIAGNOSTICS_H_ */
