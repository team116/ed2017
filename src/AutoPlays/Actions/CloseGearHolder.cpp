/*
 * CloseGearHolder.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/CloseGearHolder.h>

CloseGearHolder::CloseGearHolder() {
	gear = Gear::getInstance();
}
void CloseGearHolder::start() {
	gear->close();
	close_gear_timer->Start();
}
void CloseGearHolder::process() {

}
void CloseGearHolder::end() {

}
bool CloseGearHolder::isFinished() {
	if (close_gear_timer->HasPeriodPassed(0.5)) {
		return (true);
	}
	else {
		return (false);
	}
		close_gear_timer->Stop();
		close_gear_timer->Reset();

}
