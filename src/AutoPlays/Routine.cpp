/*
 * Routine.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Will
 */

#include <AutoPlays/Routine.h>
#include <DriverStation.h>

void Routine::addAction(Action* action) {
	actions.push(action);
	frc::DriverStation::ReportError("adding action");
}

void Routine::start() {
	timeout_timer = new frc::Timer();
	if(!actions.empty()) {
		frc::DriverStation::ReportError("starting routine");
		current_action = actions.front();
		actions.pop();
		current_action->start();
		timeout_timer->Start();
	}
	else {
		frc::DriverStation::ReportError("nothing to start");
		current_action = nullptr;
	}
}

void Routine::process() {
	if(current_action != nullptr) {
		frc::DriverStation::ReportError("timeout: " + std::to_string(current_action->getTimeout()) + " current: " + std::to_string(timeout_timer->Get()));
		bool timed_out = (current_action->getTimeout() > 0.0) && (timeout_timer->Get() >= current_action->getTimeout());
		frc::DriverStation::ReportError("Timed out: " + std::to_string(timed_out));
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
			timeout_timer->Start();
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
