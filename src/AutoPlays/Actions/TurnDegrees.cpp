/*
 * TurnDegrees.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/TurnDegrees.h>

TurnDegrees::TurnDegrees(float ang) {
	mobility = Mobility::getInstance();
	angle = ang;
	setTimeout(2.0); //Random guess
}

void TurnDegrees::start() {
	log->write(Log::DEBUG_LEVEL, "[Action] Starting Turn Degrees. Angle: %f", angle);
	mobility->turnDegrees(angle);
}

void TurnDegrees::process() {

}
void TurnDegrees::end() {
	mobility->stopTurnDegrees();
	log->write(Log::DEBUG_LEVEL, "[Action] Turn Degrees Ended. Angle: %f", angle);
}
bool TurnDegrees::isFinished(){
	return mobility->isTurnDegreesDone();
}
