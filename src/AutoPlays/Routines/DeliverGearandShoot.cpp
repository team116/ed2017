/*
 * DeliverGearandShoot.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/DeliverGearandShoot.h>
#include "AutoPlays/Routines/DeliverGear.h"
#include "AutoPlays/Actions/TurnDegrees.h"
#include "AutoPlays/Actions/DriveStraight.h"
#include "AutoPlays/Actions/AimShooterVision.h"
#include "AutoPlays/Actions/AimShooterManual.h"
#include "AutoPlays/Actions/ShootShooter.h"
#include <Vision.h>

DeliverGearandShoot::DeliverGearandShoot(Utils::Alliance color, Utils::AutoLocation location, bool use_vision) {

	addAction(new DeliverGear(color, location, use_vision));

	if (location == Utils::AutoLocation::Boiler) {
		if (color == Utils::Alliance::Blue) {
			addAction(new TurnDegrees(170.0));
		}
		else if (color == Utils::Alliance::Red) {
			addAction(new TurnDegrees(-170.0));
		}

		addAction(new DriveStraight(100.0, 0.75));
	}
	else if (location == Utils::AutoLocation::Middle) {
		if (color == Utils::Alliance::Blue) {
			addAction(new TurnDegrees(-100.0));
		}
		else if (color == Utils::Alliance::Red) {
			addAction(new TurnDegrees(100.0));
		}
		addAction(new DriveStraight(98.0, 0.75));
	}

	if (use_vision) {
		addAction(new AimShooterVision());
	}
	else {
		addAction(new AimShooterManual());
	}

	addAction(new ShootShooter(0.5, 15.0));
}
