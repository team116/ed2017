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
#include <Vision.h>

DeliverGear::DeliverGear(Utils::AutoLocation location) {
	//if (Vision::getInstance()->canSeeGearHook()) {
		if (location == Utils::AutoLocation::LeftForward) { 		//these numbers have all been calculated
			addAction(new DriveStraight(50.0, 0.75));
			addAction(new TurnDegrees(56.0));
			addAction(new DriveStraight(65.0, 0.75));
			addAction(new DriveStraight(12.0, 0.25));
			/*addAction(new DropGear());
			addAction(new DriveStraight(-12.0, 0.25));
			addAction(new DriveStraight(-24.0, 0.75));
			addAction(new CloseGearHolder());*/
		}
		else if (location == Utils::AutoLocation::MiddleForward) {
			frc::DriverStation::ReportError("Doing middle forward");
			addAction(new DriveStraight(49.0, 0.75));
			addAction(new DriveStraight(12.0, 0.25));
			/*addAction(new DropGear());
			addAction(new DriveStraight(-12.0, 0.25));
			addAction(new DriveStraight(-24.0, 0.75));
			addAction(new CloseGearHolder());*/
		}
		else if (location == Utils::AutoLocation::RightForward) {
			addAction(new DriveStraight(70.0, 0.75));
			addAction(new TurnDegrees(-60.0));
			addAction(new DriveStraight(45.0, 0.75));
			addAction(new DriveStraight(12.0, 0.25));
			/*addAction(new DropGear());
			addAction(new DriveStraight(-12.0, 0.25));
			addAction(new DriveStraight(-24.0, 0.75));
			addAction(new CloseGearHolder());*/
		}
	//}
}

