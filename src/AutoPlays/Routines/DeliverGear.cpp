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
			addAction(new DriveStraight(109.3, 0.75));
			addAction(new TurnDegrees(15.2));
			addAction(new DriveStraight(69.0, 0.25));
			addAction(new DropGear());
			addAction(new DriveStraight(-12.0, 0.25));
			addAction(new CloseGearHolder());
		}
		else if (location == Utils::AutoLocation::MiddleForward) {
			frc::DriverStation::ReportError("Doing middle forward");
			addAction(new DriveStraight(72.0, 0.75));
			addAction(new DriveStraight(41.0, 0.25));
			addAction(new DropGear());
			addAction(new DriveStraight(-12.0, 0.25));
			addAction(new CloseGearHolder());
		}
		else if (location == Utils::AutoLocation::RightForward) {
			addAction(new DriveStraight(130.3, 0.75));
			addAction(new TurnDegrees(-15.2));
			addAction(new DriveStraight(66.5, 0.25));
			addAction(new DropGear());
			addAction(new DriveStraight(-12.0, 0.25));
			addAction(new CloseGearHolder());
		}
	//}
}

