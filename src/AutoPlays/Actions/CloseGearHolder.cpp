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
	log->write(Log::INFO_LEVEL, "[Action] Starting Close Gear Holder. Timeout: %f", getTimeout());
	gear->close();
}
void CloseGearHolder::process() {

}
void CloseGearHolder::end() {
	log->write(Log::INFO_LEVEL, "[Action] Close Gear Holder Ended. Timeout: %f", getTimeout());
}
bool CloseGearHolder::isFinished() {
	return false;
}
