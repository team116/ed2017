/*
 * DeliverGearandTravel.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/DeliverGearandTravel.h>
#include <AutoPlays/Routines/DeliverGear.h>
#include "AutoPlays/Actions/TurnDegrees.h"
#include "AutoPlays/Actions/DriveStraight.h"
#include "AutoPlays/Actions/DropGear.h"
#include "AutoPlays/Actions/CloseGearHolder.h"
#include "AutoPlays/Actions/Wiggle.h"
#include <Vision.h>


DeliverGearandTravel::DeliverGearandTravel(Utils::Alliance color, Utils::AutoLocation location, bool use_vision) {
	if (location == Utils::AutoLocation::Boiler){
		float degrees = 56.0;
		addAction(new DeliverGear(color, location, use_vision));
			if (color == Utils::Alliance::Blue) {
				addAction(new TurnDegrees(-degrees));
			}
			else if (color == Utils::Alliance::Red) {
				addAction(new TurnDegrees(degrees));
			}
		addAction(new DriveStraight(91.0));
		addAction(new TurnDegrees(90.0));
		addAction(new DriveStraight(95.0));
		addAction(new TurnDegrees(-90.0));
		addAction(new DriveStraight(120.0));
	}
	else if (location == Utils::AutoLocation::Middle) {
		frc::DriverStation::ReportError("Doing middle forward");
		float degrees = 50.0;
		addAction(new DriveStraight(49.0, 0.75));
		addAction(new DriveStraight(12.0, 0.25));
		addAction(new Wiggle(color, location, 2.0));
		addAction(new DropGear(true));
		addAction(new DriveStraight(-12.0, 0.25));
		addAction(new DriveStraight(-24.0, 0.75));
		addAction(new CloseGearHolder());
		addAction(new TurnDegrees(degrees));
		addAction(new DriveStraight(95.0));
		addAction(new TurnDegrees(-degrees));
		addAction(new DriveStraight(120.0));
	}
	else if (location == Utils::AutoLocation::LoadingStation) {
		float degrees = -60.0;
		addAction(new DriveStraight(70.0, 0.75));
			if (color == Utils::Alliance::Blue) {
				addAction(new TurnDegrees(-degrees));
			}
			else if (color == Utils::Alliance::Red) {
				addAction(new TurnDegrees(degrees));
			}
		addAction(new DriveStraight(190.0));
	}
/*
		else if (location == Utils::AutoLocation::LoadingStation) {		//previously right forward
			float degrees = -60.0;
			addAction(new DriveStraight(70.0, 0.75));
			addAction(new TurnDegrees(degrees));
			addAction(new DriveStraight(45.0, 0.75));
			addAction(new DriveStraight(12.0, 0.25));
			addAction(new Wiggle(2.0));
			addAction(new DropGear());
			addAction(new DriveStraight(-12.0, 0.25));
			addAction(new DriveStraight(-24.0, 0.75));
			addAction(new CloseGearHolder());
			addAction(new TurnDegrees(-degrees));
			addAction(new DriveStraight(190.0));
		}
	}
	else if (color == Utils::Alliance::Red) {
		if (location == Utils::AutoLocation::LoadingStation) {
			float degrees = 60.0;
			addAction(new DriveStraight(70.0, 0.75));
			addAction(new TurnDegrees(degrees));
			addAction(new DriveStraight(45.0, 0.75));
			addAction(new DriveStraight(12.0, 0.25));
			addAction(new Wiggle(2.0));
			addAction(new DropGear());
			addAction(new DriveStraight(-12.0, 0.25));
			addAction(new DriveStraight(-24.0, 0.75));
			addAction(new CloseGearHolder());
			addAction(new TurnDegrees(-degrees));
			addAction(new DriveStraight(190.0));


	}*/

}

