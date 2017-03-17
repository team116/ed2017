/*
] * PositionGear.cpp
 *
 *  Created on: Mar 5, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/PositionGear.h>
#include "AutoPlays/Actions/TurnDegrees.h"
#include "AutoPlays/Actions/DriveStraight.h"
#include "AutoPlays/Actions/DropGear.h"
#include "AutoPlays/Actions/CloseGearHolder.h"
#include "AutoPlays/Actions/Wiggle.h"
#include "AutoPlays/Actions/DriveToGearVision.h"
#include <Vision.h>

PositionGear::PositionGear(Utils::Alliance color, Utils::AutoLocation location, bool use_vision) {
	if (location == Utils::AutoLocation::Boiler) {
			addAction(new DriveStraight(58.0, 0.75));
			float degrees = 54.0;
			if (color == Utils::Alliance::Blue) {
				addAction(new TurnDegrees(degrees));
			}
			else {
				addAction(new TurnDegrees(-degrees));
			}

			if(use_vision) {
				addAction(new DriveToGearVision());
			}
			else {
				addAction(new DriveStraight(60.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
			}
	}
	else if (location == Utils::AutoLocation::Middle) {
			frc::DriverStation::ReportError("Doing middle forward");
			if(use_vision) {
				addAction(new DriveToGearVision());
				addAction(new DriveStraight(0.0, 0.5));
			}
			else {
				addAction(new DriveStraight(47.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
			}
	}
	else if (location == Utils::AutoLocation::LoadingStation) {
			addAction(new DriveStraight(64.0, 0.75));
			if (color == Utils::Alliance::Blue) {
				addAction(new TurnDegrees(-60.0));
			}
			else {
				addAction(new TurnDegrees(60.0));
			}

			if(use_vision) {
				addAction(new DriveToGearVision());
			}
			else {
				addAction(new DriveStraight(45.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
			}
	}
}
