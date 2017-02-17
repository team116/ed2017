/*
 * TurnDegrees.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/TurnDegrees.h>

TurnDegrees::TurnDegrees(float ang) {
	mobility =Mobility::getInstance();
	angle = ang;
}

void TurnDegrees::start() {
	mobility->turnDegrees(angle);
}

void TurnDegrees::process() {

}
void TurnDegrees::end() {

}
bool TurnDegrees::isFinished(){
	return mobility->isTurnDegreesDone();
}
