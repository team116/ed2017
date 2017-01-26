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

class Diagnostics {
public:
	Diagnostics();

	void process();

private:

	Mobility* mobility;
	BuiltInAccelerometer* accel;


};

#endif /* DIAGNOSTICS_H_ */
