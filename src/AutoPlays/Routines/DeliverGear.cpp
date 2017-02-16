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

DeliverGear::DeliverGear() {
	addAction(new DriveStraight(118.0));
	addAction(new TurnDegrees(15.0));
	addAction(new DropGear());
	addAction(new DriveStraight(-20.0));
}

