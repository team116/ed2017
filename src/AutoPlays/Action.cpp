/*
 * Action.cpp
 *
 *  Created on: Feb 20, 2017
 *      Author: Will
 */

#include "Action.h"

Action::Action() {
	log = Log::getInstance();
}

void Action::setTimeout(float time) {
	timeout = time;
}

float Action::getTimeout() {
	return timeout;
}
