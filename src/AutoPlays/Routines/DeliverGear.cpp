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

DeliverGear::DeliverGear(Utils::AutoLocation location) {		//allll this math needs to be checked
	if (Vision::getInstance()->canSeeGearHook()) {				//this is alllll rough ESTIMATES
		if (location == Utils::AutoLocation::LeftForward) {
			addAction(new DriveStraight(98.0));
			addAction(new TurnDegrees(37.0));
			addAction(new DriveStraight(30.0));
			addAction(new DropGear());
			addAction(new DriveStraight(-15.0));
			addAction(new CloseGearHolder());
		}
		else if (location == Utils::AutoLocation::MiddleForward) {
			addAction(new DriveStraight(99.0));
			addAction(new DropGear());
			addAction(new DriveStraight(-20.0));
			addAction(new CloseGearHolder());
		}
		else if (location == Utils::AutoLocation::RightForward) {
			addAction(new DriveStraight(98.0));
			addAction(new TurnDegrees(-37.0));
			addAction(new DriveStraight(30.0));
			addAction(new DropGear());
			addAction(new DriveStraight(-15.0));
			addAction(new CloseGearHolder());
		}
	}

}

