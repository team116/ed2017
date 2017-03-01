/*
 * Shoot.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/Shoot.h>
#include "AutoPlays/Actions/TurnDegrees.h"
#include "AutoPlays/Actions/DriveStraight.h"
#include "AutoPlays/Actions/AimShooterVision.h"
#include "AutoPlays/Actions/AimShooterManual.h"
#include "AutoPlays/Actions/ShootShooter.h"

Shoot::Shoot(Utils::Alliance color, Utils::AutoLocation location) {
	//if (Vision::getInstance()->canSeeGearHook()) {
		if (color == Utils::Alliance::Blue) {
			if (location == Utils::AutoLocation::LeftTurntPositive) {
				addAction(new AimShooterVision());		//will needs to finish the aiming functions before this can work
				addAction(new ShootShooter(15.0));
			}
			else if (location == Utils::AutoLocation::MiddleTurntPositive) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(15.0));
			}
			else if (location == Utils::AutoLocation::RightTurntPositive) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(15.0));
			}
		}
		else {
			if (location == Utils::AutoLocation::LeftTurntNegative) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(15.0));
			}
			else if (location == Utils::AutoLocation::MiddleTurntNegative) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(15.0));
			}
			else if (location == Utils::AutoLocation::RightTurntNegative) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(15.0));
			}
		}
	}
}

