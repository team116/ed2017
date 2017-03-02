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
	log->write(Log::INFO_LEVEL, "[Action] Starting Drop Gear");
	gear->open();
}
void DropGear::process() {

}
void DropGear::end() {
	log->write(Log::INFO_LEVEL, "[Action] Ending Drop Gear");
}
bool DropGear::isFinished() {
	return false;
}
