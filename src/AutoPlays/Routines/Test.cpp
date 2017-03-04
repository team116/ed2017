/*
 * Test.cpp
 *
 *  Created on: Mar 4, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/Test.h>
#include "AutoPlays/Actions/TurnDegrees.h"
#include "AutoPlays/Actions/DriveStraight.h"
#include "AutoPlays/Actions/DropGear.h"
#include "AutoPlays/Actions/CloseGearHolder.h"
#include "AutoPlays/Actions/Wiggle.h"

Test::Test(Utils::Alliance color, Utils::AutoLocation location) {
	addAction(new Wiggle(color, location, 2.0));
}

