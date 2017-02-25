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
	//if (Vision::getInstance()->canSeeGearHook()) {
		if (color == Utils::Alliance::Blue) {
			if (location == Utils::AutoLocation::LeftForward) {
					addAction(new DriveStraight(130.3, 0.75));
					addAction(new TurnDegrees(15.2));
					addAction(new DriveStraight(66.5, 0.25));
					addAction(new DropGear());
					addAction(new DriveStraight(-12.0, 0.25));
					addAction(new CloseGearHolder());
					addAction(new TurnDegrees(-10.0));
					addAction(new DriveStraight(-113.0, 0.75));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
				}
				else if (location == Utils::AutoLocation::MiddleForward) {
					addAction(new DriveStraight(70.0, 0.75));
					addAction(new DriveStraight(27.5, 0.25));
					addAction(new DropGear());
					addAction(new DriveStraight(-12.0, 0.25));
					addAction(new TurnDegrees(45.0));
					addAction(new DriveStraight(-98.0, 0.75));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
				}
				else if (location == Utils::AutoLocation::RightForward)  {
					addAction(new DriveStraight(130.3, 0.75));
					addAction(new TurnDegrees(-15.2));
					addAction(new DriveStraight(66.5, 0.25));
					addAction(new DropGear());
					addAction(new DriveStraight(-66.5, 0.25));
					addAction(new CloseGearHolder());
					addAction(new TurnDegrees(120.0));
					addAction(new DriveStraight(-192.0, 0.75));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
				}
		}
		else if (color == Utils::Alliance::Red) {
			if (location == Utils::AutoLocation::LeftForward) {
					addAction(new DriveStraight(130.3, 0.75));
					addAction(new TurnDegrees(15.2));
					addAction(new DriveStraight(66.5, 0.25));
					addAction(new DropGear());
					addAction(new DriveStraight(-66.5, 0.25));
					addAction(new CloseGearHolder());
					addAction(new TurnDegrees(-120));
					addAction(new DriveStraight(-192.0, 0.75));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
			}
			else if (location == Utils::AutoLocation::MiddleForward) {
					addAction(new DriveStraight(70.0, 0.75));
					addAction(new DriveStraight(28.3, 0.25));
					addAction(new DropGear());
					addAction(new DriveStraight(-12.0));
					addAction(new TurnDegrees(-45.0));
					addAction(new DriveStraight(-98.0, 0.75));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
			}
			else if (location == Utils::AutoLocation::RightForward)  {
					addAction(new DriveStraight(130.3, 0.75));
					addAction(new TurnDegrees(-15.2));
					addAction(new DriveStraight(66.5, 0.25));
					addAction(new DropGear());
					addAction(new DriveStraight(-12.0, 0.25));
					addAction(new CloseGearHolder());
					addAction(new TurnDegrees(10.0));
					addAction(new DriveStraight(-113.0, 0.75));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
			}
		}
	}


