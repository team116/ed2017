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
#include <Climber.h>
#include <Shooter.h>
#include <Intake.h>
#include <Feeder.h>
#include "Vision.h"
#include "Log.h"

class OI {
public:
	static OI* getInstance();
	void process();

private:
	OI();
	static OI* INSTANCE;

	Log* log;
	Mobility* mobility;
	Gear* gear;
	Climber* climber;
	Shooter* shooter;
	Intake* intake;
	Feeder* feeder;
	Vision* vision;
	frc::Joystick* joy_left;
	frc::Joystick* joy_right;
	frc::Joystick* button_box_1;
	frc::Joystick* button_box_2;
	frc::Joystick* button_box_3;

	frc::Timer* shoot_button_timer;
};

#endif /* SRC_OI_H_ */
