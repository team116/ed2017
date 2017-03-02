/*
 * Routine.h
 *
 *  Created on: Feb 10, 2017
 *      Author: Will
 */

#ifndef SRC_AUTOPLAYS_ROUTINE_H_
#define SRC_AUTOPLAYS_ROUTINE_H_

#include <AutoPlays/Action.h>
#include <queue>
#include <Timer.h>
#include "Log.h"

class Routine {
public:
	//Constructor. Make sure to push the actions into the action queue
	Routine();

	//Called once when the routine starts
	void start();

	//Called repeatedly while the routine runs
	void process();


	//Called once when the routine ends
	void end();

	//Returns whether or not the routine is finished
	bool isFinished();

	//Use this to add actions to this routine
	void addAction(Action* action);

private:
	//Queue of actions in chronological order
	std::queue<Action*> actions;
	Action* current_action;

	frc::Timer* timeout_timer;

protected:
	Log* log;
};


#endif /* SRC_AUTOPLAYS_ROUTINE_H_ */
