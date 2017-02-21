/*
 * Routine.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Will
 */

#include <AutoPlays/Routine.h>

void Routine::addAction(Action* action) {
	actions.push(action);
}

void Routine::start() {
	timeout_timer = new frc::Timer();
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
		bool timed_out = (current_action->getTimeout() > 0.0) && (timeout_timer->Get() >= current_action->getTimeout());
		if(current_action->isFinished() || timed_out) {
			current_action->end();
			if(!actions.empty()) {
				current_action = actions.front();
				actions.pop();
				current_action->start();
			}
			else {
				current_action = nullptr;
			}

			timeout_timer->Reset();
		}
		else {
			current_action->process();
		}
	}
}

void Routine::end() {
	if(current_action != nullptr) {
		current_action->end();
	}
	current_action = nullptr;

	timeout_timer->Stop();

}


bool Routine::isFinished() {
	return (actions.empty() && (current_action == nullptr));
}
