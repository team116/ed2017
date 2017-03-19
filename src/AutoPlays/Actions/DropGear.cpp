/*
 * DropGear.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/DropGear.h>
#include <DriverStation.h>

const float DISTANCE = 16.0;

DropGear::DropGear(bool use_ultrasonic) {
	gear = Gear::getInstance();
	mobility = Mobility::getInstance();

	ultrasonic = use_ultrasonic;

	setTimeout(1.0);
}
void DropGear::start() {
	log->write(Log::INFO_LEVEL, "[Action] Starting Drop Gear. Timeout: %f", getTimeout());
	if(ultrasonic && mobility->isFrontDistanceValid())
	{
		if(mobility->getFrontDistance() <= DISTANCE) {
			gear->open();
		}
		else {
			setTimeout(0.0);
		}
	}
	else {
		gear->open();
	}
}
void DropGear::process() {

}
void DropGear::end() {
	log->write(Log::INFO_LEVEL, "[Action] Ending Drop Gear. Timeout: %f", getTimeout());
}
bool DropGear::isFinished() {
	return false;
}
