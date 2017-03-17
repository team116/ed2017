/*
 * DeliverGear.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/DeliverGear.h>
#include <AutoPlays/Routines/PositionGear.h>
#include "AutoPlays/Actions/TurnDegrees.h"
#include "AutoPlays/Actions/DriveStraight.h"
#include "AutoPlays/Actions/DropGear.h"
#include "AutoPlays/Actions/CloseGearHolder.h"
#include "AutoPlays/Actions/Wiggle.h"
#include <Vision.h>

DeliverGear::DeliverGear(Utils::Alliance color, Utils::AutoLocation location, bool use_vision) {
	//if (Vision::getInstance()->canSeeGearHook()) {
	addAction(new PositionGear(color, location, use_vision));
	if(use_vision) {
		addAction(new DriveStraight(8.0, 0.25));
	}
	else {
		addAction(new DriveStraight(2.0, 0.25));
		addAction(new Wiggle(color, location, 2.0));
	}
	addAction(new DropGear());
	addAction(new DriveStraight(-12.0, 0.25));
	addAction(new DriveStraight(-24.0, 0.75));
	addAction(new CloseGearHolder());
}

