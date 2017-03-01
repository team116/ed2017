/*
 * CloseGearHolder.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/CloseGearHolder.h>
#include <DriverStation.h>

CloseGearHolder::CloseGearHolder() {
	gear = Gear::getInstance();

	setTimeout(0.5);
}
void CloseGearHolder::start() {
	frc::DriverStation::ReportError("Starting close gear holder");
	gear->close();
}
void CloseGearHolder::process() {

}
void CloseGearHolder::end() {
	frc::DriverStation::ReportError("Ending close gear holder");
}
bool CloseGearHolder::isFinished() {
	return false;
}
