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
#include <Vision.h>


DeliverGearandTravel::DeliverGearandTravel(Utils::AutoLocation location) {
	if (location == Utils::AutoLocation::LeftForward) {
				float degrees = 50.0;
				addAction(new DriveStraight(45.0, 0.75));
				addAction(new TurnDegrees(degrees));
				addAction(new DriveStraight(80.0, 0.75));
				addAction(new DriveStraight(30.0, 0.25));
				addAction(new DropGear());
				addAction(new DriveStraight(-12.0, 0.25));
				addAction(new DriveStraight(-24.0, 0.75));
				addAction(new CloseGearHolder());
				addAction(new TurnDegrees(-degrees));
				addAction(new DriveStraight(91.0));		//all estimated #s
				addAction(new TurnDegrees(90.0));
				addAction(new DriveStraight(95.0));
				addAction(new TurnDegrees(-90.0));
				addAction(new DriveStraight(120.0));
			}
			else if (location == Utils::AutoLocation::MiddleForward) {
				frc::DriverStation::ReportError("Doing middle forward");
				addAction(new DriveStraight(60.0, 0.75));
				addAction(new DriveStraight(15.0, 0.25));
				addAction(new DropGear());
				addAction(new DriveStraight(-12.0, 0.25));
				addAction(new DriveStraight(-24.0, 0.75));
				addAction(new CloseGearHolder());
				addAction(new TurnDegrees(50.0));		//all estimated from here
				addAction(new DriveStraight(95.0));
				addAction(new TurnDegrees(-50.0));
				addAction(new DriveStraight(120.0));
			}
			else if (location == Utils::AutoLocation::RightForward) {
				float degrees = -60.0;
				addAction(new DriveStraight(70.0, 0.75));
				addAction(new TurnDegrees(degrees));
				addAction(new DriveStraight(40.5, 0.75));
				addAction(new DriveStraight(30.5, 0.25));
				addAction(new DropGear());
				addAction(new DriveStraight(-12.0, 0.25));
				addAction(new DriveStraight(-24.0, 0.75));
				addAction(new CloseGearHolder());
				addAction(new TurnDegrees(-degrees));
				addAction(new DriveStraight(190.0));
			}

}

