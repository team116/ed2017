/*
 * ShootandCrossBaseline.cpp95
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/ShootandCrossBaseline.h>
#include "AutoPlays/Actions/TurnDegrees.h"
#include "AutoPlays/Actions/DriveStraight.h"
#include "AutoPlays/Actions/AimShooterVision.h"
#include "AutoPlays/Actions/ShootShooter.h"
#include <Vision.h>

ShootandCrossBaseline::ShootandCrossBaseline(Utils::Alliance color, Utils::AutoLocation location) {
	//if (Vision::getInstance()->canSeeHighGoal()) {
		if (color == Utils::Alliance::Blue) {
			if (location == Utils::AutoLocation::LeftTurntPositive) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(10.0));
				addAction(new TurnDegrees(-95.0));
				addAction(new DriveStraight(105.0));
			}
			else if (location == Utils::AutoLocation::MiddleTurntPositive) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(10.0));
				addAction(new TurnDegrees(-45.0));
				addAction(new DriveStraight(105.0));
			}
			else if (location == Utils::AutoLocation::RightTurntPositive) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(10.0));
				addAction(new TurnDegrees(-90.0));
				addAction(new DriveStraight(98.0));
			}
		}
		else if (color == Utils::Alliance::Red) {
			if (location == Utils::AutoLocation::LeftTurntNegative) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(10.0));
				addAction(new TurnDegrees(90.0));
				addAction(new DriveStraight(98.0));
			}
			else if (location == Utils::AutoLocation::MiddleTurntNegative) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(10.0));
				addAction(new TurnDegrees(45.0));
				addAction(new DriveStraight(110.0));
			}
			else if (location == Utils::AutoLocation::RightTurntNegative) {
				addAction(new AimShooterVision());
				addAction(new ShootShooter(10.0));
				addAction(new TurnDegrees(100.0));
				addAction(new DriveStraight(100.0));
			}
		}

	}

}

