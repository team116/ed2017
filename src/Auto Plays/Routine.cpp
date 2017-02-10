/*
 * Routine.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Will
 */

#include "Routine.h"

void Routine::addAction(Action* action) {
	actions.push(action);
}

void Routine::start() {
	if(!actions.empty()) {
		current_action = actions.front();
		actions.pop();
		current_action->start();
	}
	else {
		current_action = nullptr;
	}
}

void Routine::process() {
	if(current_action != nullptr) {
		if(current_action->isFinished()) {
			current_action->end();
			if(!actions.empty()) {
				current_action = actions.front();
				actions.pop();
				current_action->start();
			}
			else {
				current_action = nullptr;
			}
		}
		else {
			current_action->process();
		}
	}
}

bool Routine::isFinished() {
	return (actions.empty() && (current_action == nullptr));
}
