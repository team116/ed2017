/*
 * CrossBaseline.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/CrossBaseline.h>
#include "AutoPlays/Actions/DriveStraight.h"
#include "AutoPlays/Actions/TurnDegrees.h"

CrossBaseline::CrossBaseline(Utils::AutoLocation location) {
	if (location == Utils::AutoLocation::Boiler) {				//previously leftforward
		addAction(new DriveStraight(131.0));
	}
	else if (location == Utils::AutoLocation::Middle) {
		addAction(new DriveStraight(96.0));
	}
	else if (location == Utils::AutoLocation::LoadingStation) {		//previously rightforward
		addAction(new DriveStraight(131.0));
	}
}

