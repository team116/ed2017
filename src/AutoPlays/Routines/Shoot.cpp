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
	if (location == Utils::AutoLocation::Boiler) {
		addAction(new DriveStraight(-5.0));
		addAction(new AimShooterManual());
	}
	else if (location == Utils::AutoLocation::Middle) {
		addAction (new DriveStraight(-146.0));
		addAction(new AimShooterManual());
	}
	else if (location == Utils::AutoLocation::LoadingStation) {
		addAction(new DriveStraight(-243.0));
		addAction(new AimShooterManual());
	}
}
/*Shoot::Shoot(Utils::Alliance color, Utils::AutoLocation location) {		//numbers here may need to change
	//if (Vision::getInstance()->canSeeGearHook()) {
		if (color == Utils::Alliance::Blue) {
			if (location == Utils::AutoLocation::Boiler) {		//previously leftturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(15.0));
				addAction (new DriveStraight(-5.0));
				addAction(new AimShooterManual());
			}
			else if (location == Utils::AutoLocation::Middle) {		//previously middleturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(15.0));
				addAction (new DriveStraight(-146.0));
				addAction(new AimShooterManual());
			}
			else if (location == Utils::AutoLocation::LoadingStation) {		//previously rightturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(15.0));
				addAction(new DriveStraight(-243.0));
				addAction(new AimShooterManual());
			}
		}
		else if (color == Utils::Alliance::Red){
			if (location == Utils::AutoLocation::LoadingStation) {		//previously leftturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(15.0));
				addAction(new DriveStraight(-243.0));
				addAction(new AimShooterManual());
			}
			else if (location == Utils::AutoLocation::Middle) {	//previously middleturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(15.0));
				addAction(new DriveStraight(-146.0));
				addAction(new AimShooterManual());
			}
			else if (location == Utils::AutoLocation::Boiler) {		//previously rightturntpositive
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(15.0));
				addAction(new DriveStraight(-5.0));
				addAction(new AimShooterManual());
			}
		}
	}

*/
