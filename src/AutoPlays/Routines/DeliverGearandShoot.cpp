/*
 * DeliverGearandShoot.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/DeliverGearandShoot.h>
#include "AutoPlays/Actions/TurnDegrees.h"
#include "AutoPlays/Actions/DriveStraight.h"
#include "AutoPlays/Actions/DropGear.h"
#include "AutoPlays/Actions/CloseGearHolder.h"
#include "AutoPlays/Actions/AimShooterVision.h"
#include "AutoPlays/Actions/ShootShooter.h"
#include <Vision.h>

DeliverGearandShoot::DeliverGearandShoot(Utils::Alliance color, Utils::AutoLocation location) {
	if (Vision::getInstance()->canSeeGearHook()) {
		if (color == Utils::Alliance::Blue) {
			if (location == Utils::AutoLocation::LeftForward) {
					addAction(new DriveStraight(98.0));
					addAction(new TurnDegrees(37.0));
					addAction(new DriveStraight(20.0));
					addAction(new DropGear());
					addAction(new DriveStraight(-15.0));
					addAction(new CloseGearHolder());
					addAction(new TurnDegrees(180.0));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
				}
				else if (location == Utils::AutoLocation::MiddleForward) {
					addAction(new DriveStraight(98.0));
					addAction(new DropGear());
					addAction(new DriveStraight(-15.0));
					addAction(new TurnDegrees(-135.0));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
				}
				else if (location == Utils::AutoLocation::RightForward)  {
					addAction(new DriveStraight(98.0));
					addAction(new TurnDegrees(-37.0));
					addAction(new DriveStraight(20.0));
					addAction(new DropGear());
					addAction(new DriveStraight(-15.0));
					addAction(new CloseGearHolder());
					addAction(new TurnDegrees(-80.0));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
				}
		}
		else if (color == Utils::Alliance::Red) {
			if (location == Utils::AutoLocation::LeftForward) {
					addAction(new DriveStraight(98.0));
					addAction(new TurnDegrees(37.0));
					addAction(new DriveStraight(20.0));
					addAction(new DropGear());
					addAction(new DriveStraight(-15.0));
					addAction(new CloseGearHolder());
					addAction(new TurnDegrees(80.0));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
			}
			else if (location == Utils::AutoLocation::MiddleForward) {
					addAction(new DriveStraight(98.0));
					addAction(new DropGear());
					addAction(new DriveStraight(-15.0));
					addAction(new TurnDegrees(125.0));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
			}
			else if (location == Utils::AutoLocation::RightForward)  {
					addAction(new DriveStraight(98.0));
					addAction(new TurnDegrees(-37.0));
					addAction(new DriveStraight(20.0));
					addAction(new DropGear());
					addAction(new DriveStraight(-15.0));
					addAction(new CloseGearHolder());
					addAction(new TurnDegrees(180.0));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
			}
		}
	}
}

