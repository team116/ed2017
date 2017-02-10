/*
 * Routine.h
 *
 *  Created on: Feb 10, 2017
 *      Author: Will
 */

#ifndef SRC_AUTO_PLAYS_ROUTINE_H_
#define SRC_AUTO_PLAYS_ROUTINE_H_

#include "Action.h"

class Routine {
public:
	//Constructor. Make sure to push the actions into the action queue
	virtual Routine() = 0;

	//Called once when the routine starts
	void start();

	//Called repeatedly while the routine runs
	void process();

	//Returns whether or not the routine is finished
	bool isFinished();

	//Use this to add actions to this routine
	void addAction(Action* action);

private:
	//Queue of actions in chronological order
	std::queue<Action*> actions;
	Action* current_action;
};


#endif /* SRC_AUTO_PLAYS_ROUTINE_H_ */
