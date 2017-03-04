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
#include "AutoPlays/Actions/AimShooterManual.h"
#include "AutoPlays/Actions/ShootShooter.h"
#include "AutoPlays/Actions/Wiggle.h"
#include <Vision.h>

DeliverGearandShoot::DeliverGearandShoot(Utils::Alliance color, Utils::AutoLocation location) {
	//if (Vision::getInstance()->canSeeGearHook()) {
		if (color == Utils::Alliance::Blue) {
			if (location == Utils::AutoLocation::Boiler) {		//previously leftforward blue side
				addAction(new DriveStraight(50.0, 0.75));
				addAction(new TurnDegrees(56.0));
				addAction(new DriveStraight(65.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
				addAction(new Wiggle(2.0));
				addAction(new DropGear());
				addAction(new DriveStraight(-12.0, 0.25));
				addAction(new DriveStraight(-24.0, 0.75));
				addAction(new CloseGearHolder());
				addAction(new TurnDegrees(-10.0));		//test these values
				addAction(new DriveStraight(-100.0, 0.75));
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(15.0));
				addAction(new AimShooterManual());
			}
			else if (location == Utils::AutoLocation::Middle) {		//previously miffleforward blue side
				addAction(new DriveStraight(49.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
				addAction(new Wiggle(2.0));
				addAction(new DropGear());
				addAction(new CloseGearHolder());
				addAction(new DriveStraight(-12.0, 0.25));
				addAction(new TurnDegrees(45.0));
				addAction(new DriveStraight(-98.0, 0.75));
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(15.0));
				addAction(new AimShooterManual());
			}
			/*else if (location == Utils::AutoLocation::LoadingStation)  {		//previously rightforward blue side
				addAction(new DriveStraight(70.0, 0.75));
				addAction(new TurnDegrees(-60.0));
				addAction(new DriveStraight(45.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
				addAction(new Wiggle(2.0));
				addAction(new DropGear());
					addAction(new TurnDegrees(120.0));
					addAction(new DriveStraight(-192.0, 0.75));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
			}*/
		}
		else if (color == Utils::Alliance::Red) {
			/*if (location == Utils::AutoLocation::LoadingStation) {		//previously leftforward
				addAction(new DriveStraight(70.0, 0.75));
				addAction(new TurnDegrees(60.0));
				addAction(new DriveStraight(45.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
				addAction(new Wiggle(2.0));
				addAction(new DropGear());
					addAction(new TurnDegrees(-120));
					addAction(new DriveStraight(-192.0, 0.75));
					addAction(new AimShooterVision());
					addAction(new ShootShooter(15.0));
			}*/
			if (location == Utils::AutoLocation::Middle) {	//previously middleforward
				addAction(new DriveStraight(49.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
				addAction(new Wiggle(2.0));
				addAction(new DropGear());
				addAction(new CloseGearHolder());
				addAction(new DriveStraight(-12.0));
				addAction(new TurnDegrees(-45.0));
				addAction(new DriveStraight(-98.0, 0.75));
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(15.0));
				addAction(new AimShooterManual());
			}
			else if (location == Utils::AutoLocation::Boiler)  {		//previously right forward
				addAction(new DriveStraight(50.0, 0.75));
				addAction(new TurnDegrees(-56.0));
				addAction(new DriveStraight(65.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
				addAction(new Wiggle(2.0));
				addAction(new DropGear());
				addAction(new DriveStraight(-12.0, 0.25));
				addAction(new CloseGearHolder());
				addAction(new TurnDegrees(10.0));
				addAction(new DriveStraight(-100.0, 0.75));
				//addAction(new AimShooterVision());
				//addAction(new ShootShooter(15.0));
				addAction(new AimShooterManual());
			}
		}
	}


