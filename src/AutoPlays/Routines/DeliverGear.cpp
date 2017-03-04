/*
 * DeliverGear.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/DeliverGear.h>
#include "AutoPlays/Actions/TurnDegrees.h"
#include "AutoPlays/Actions/DriveStraight.h"
#include "AutoPlays/Actions/DropGear.h"
#include "AutoPlays/Actions/CloseGearHolder.h"
#include "AutoPlays/Actions/Wiggle.h"
#include <Vision.h>

DeliverGear::DeliverGear(Utils::Alliance color, Utils::AutoLocation location) {
	//if (Vision::getInstance()->canSeeGearHook()) {
	if (location == Utils::AutoLocation::Boiler) {
		addAction(new DriveStraight(55.0, 0.75));
		float degrees = 56.0;
			if (color == Utils::Alliance::Blue) {
				addAction(new TurnDegrees(degrees));
			}
			else {
				addAction(new TurnDegrees(-degrees));
			}
		addAction(new DriveStraight(65.0, 0.75));
		addAction(new DriveStraight(12.0, 0.25));
		addAction(new Wiggle(2.0));
		addAction(new DropGear());
		addAction(new DriveStraight(-12.0, 0.25));
		addAction(new DriveStraight(-24.0, 0.75));
		addAction(new CloseGearHolder());
	}
	else if (location == Utils::AutoLocation::Middle) {
		frc::DriverStation::ReportError("Doing middle forward");
		addAction(new DriveStraight(49.0, 0.75));
		addAction(new DriveStraight(12.0, 0.25));
		addAction(new Wiggle(2.0));
		addAction(new DropGear());
		addAction(new DriveStraight(-12.0, 0.25));
		addAction(new DriveStraight(-24.0, 0.75));
		addAction(new CloseGearHolder());
	}
	else if (location == Utils::AutoLocation::LoadingStation) {
		addAction(new DriveStraight(70.0, 0.75));
			if (color == Utils::Alliance::Blue) {
				addAction(new TurnDegrees(-60.0));
			}
			else {
				addAction(new TurnDegrees(60.0));
			}
		addAction(new DriveStraight(45.0, 0.75));
		addAction(new DriveStraight(12.0, 0.25));
		addAction(new Wiggle(2.0));
		addAction(new DropGear());
		addAction(new DriveStraight(-12.0, 0.25));
		addAction(new DriveStraight(-24.0, 0.75));
		addAction(new CloseGearHolder());
	}
}

