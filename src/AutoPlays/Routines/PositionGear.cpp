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
			addAction(new DriveStraight(58.0, 0.85));
			float degrees = 50.0;
			if (color == Utils::Alliance::Blue) {
				addAction(new TurnDegrees(degrees));
			}
			else {
				addAction(new TurnDegrees(-degrees));
			}

			if(use_vision) {
				addAction(new DriveStraight(36.0, 0.85));
				addAction(new DriveToGearVision(true));
			}
			else {
				addAction(new DriveStraight(60.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
			}
	}
	else if (location == Utils::AutoLocation::Middle) {
			frc::DriverStation::ReportError("Doing middle forward");
			if(use_vision) {
				addAction(new DriveStraight(36.0, 0.75));
				addAction(new DriveToGearVision(true));
			}
			else {
				addAction(new DriveStraight(47.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
			}
	}
	else if (location == Utils::AutoLocation::LoadingStation) {
			addAction(new DriveStraight(65.0, 0.85));
			if (color == Utils::Alliance::Blue) {
				addAction(new TurnDegrees(-55.0));
			}
			else {
				addAction(new TurnDegrees(55.0));
			}

			if(use_vision) {
				addAction(new DriveStraight(24.0, 0.85));
				addAction(new DriveToGearVision(true));
			}
			else {
				addAction(new DriveStraight(45.0, 0.75));
				addAction(new DriveStraight(12.0, 0.25));
			}
	}
}
