/*
 * Routine.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: Will
 */

#include <AutoPlays/Routine.h>
#include <DriverStation.h>

Routine::Routine() {
	log = Log::getInstance();
	timeout_timer = new frc::Timer();
	current_action = nullptr;
}

void Routine::addAction(Action* action) {
	actions.push(action);
}

void Routine::start() {
	timeout_timer = new frc::Timer();
	if(!actions.empty()) {
		log->write(Log::TRACE_LEVEL, "[Routine] Starting Routine with %d actions", actions.size());
		current_action = actions.front();
		actions.pop();
		current_action->start();
		timeout_timer->Start();
	}
	else {
		log->write(Log::WARNING_LEVEL, "[Routine] Routine is empty; Cannot start");
		current_action = nullptr;
	}
}

void Routine::process() {
	if(current_action != nullptr) {
		bool timed_out = (current_action->getTimeout() > 0.0) && (timeout_timer->Get() >= current_action->getTimeout());
		if(current_action->isFinished() || timed_out) {
			current_action->end();
			if(!actions.empty()) {
				log->write((timed_out ? Log::WARNING_LEVEL : Log::INFO_LEVEL), (timed_out ? "[Routine] Action timed out, moving to next action (%f actions left)" : "[Routine] Action finished, moving to next action (%f actions left)"), actions.size());
				current_action = actions.front();
				actions.pop();
				current_action->start();
			}
			else {
				log->write((timed_out ? Log::WARNING_LEVEL : Log::INFO_LEVEL), (timed_out ? "[Routine] Action timed out, no more actions" : "[Routine] Action finished, no more actions"));
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
	log->write(Log::TRACE_LEVEL, "[Routine] Routine Ended");
}


bool Routine::isFinished() {
	return (actions.empty() && (current_action == nullptr));
}
