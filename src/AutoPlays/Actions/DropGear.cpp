/*
 * DropGear.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/DropGear.h>
#include <DriverStation.h>

DropGear::DropGear() {
	gear = Gear::getInstance();
	setTimeout(1.0);
}
void DropGear::start() {
	frc::DriverStation::ReportError("Opening gear");
	gear->open();
}
void DropGear::process() {

}
void DropGear::end() {
	frc::DriverStation::ReportError("Ending open gear");
}
bool DropGear::isFinished() {
	return false;
}
