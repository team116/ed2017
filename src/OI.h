/*
 * OI.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_OI_H_
#define SRC_OI_H_
#include <Joystick.h>
#include <Mobility.h>

class OI {
public:
	static OI* getInstance();
	void process();

private:
	OI();
	static OI* INSTANCE;
	Mobility* mobility;
	Joystick* joy_left;
	Joystick* joy_right;
};

#endif /* SRC_OI_H_ */
