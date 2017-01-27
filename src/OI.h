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
#include <Gear.h>
class OI {
public:
	static OI* getInstance();
	void process();

private:
	OI();
	static OI* INSTANCE;
	Mobility* mobility;
	Gear* gear;
	frc::Joystick* joy_left;
	frc::Joystick* joy_right;
	frc::Joystick* button_box_1;
	frc::Joystick* button_box_2;
};

#endif /* SRC_OI_H_ */
