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
#include "AutoPlays/Actions/AimShooterManual.h"

ShootandCrossBaseline::ShootandCrossBaseline(Utils::Alliance color, Utils::AutoLocation location) {
	//if (Vision::getInstance()->canSeeHighGoal()) {		//need to add steps
		if (color == Utils::Alliance::Blue) {
			if (location == Utils::AutoLocation::Boiler) {		//previously leftturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(10.0));
				addAction (new DriveStraight(5.0));
				addAction(new AimShooterManual());
				addAction(new TurnDegrees(50.0));
				addAction(new DriveStraight(90.0));
			}
			else if (location == Utils::AutoLocation::Middle) {	//previously middleturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(10.0));
				addAction (new DriveStraight(146.0));
				addAction(new AimShooterManual());
				addAction(new TurnDegrees(50.0));
				addAction(new DriveStraight(90.0));
			}
			else if (location == Utils::AutoLocation::LoadingStation) {		//previously rightturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(10.0));
				addAction(new DriveStraight(243.0));
				addAction(new AimShooterManual());
				//addAction(new TurnDegrees(50 .0));
				addAction(new DriveStraight(90.0));
			}
		}
		else if (color == Utils::Alliance::Red) {
			if (location == Utils::AutoLocation::LeftTurntNegative) {	//previously leftturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(10.0));
				addAction(new DriveStraight(243.0));
				addAction(new AimShooterManual());
				addAction(new TurnDegrees(-50.0));
				addAction(new DriveStraight(90.0));
			}
			else if (location == Utils::AutoLocation::MiddleTurntNegative) {		//previously middleturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(10.0));
				addAction(new DriveStraight(146.0));
				addAction(new AimShooterManual());
				addAction(new TurnDegrees(-50.0));
				addAction(new DriveStraight(90.0));
			}
			else if (location == Utils::AutoLocation::RightTurntNegative) {		//previously rightturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(10.0));
				addAction(new DriveStraight(58.0));
				addAction(new AimShooterManual());
				addAction(new TurnDegrees(-50.0));
				addAction(new DriveStraight(90.0));
			}
		}

	}



