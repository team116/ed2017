/*
 * Action.h
 *
 *  Created on: Feb 10, 2017
 *      Author: Will
 */

#ifndef SRC_AUTOPLAYS_ACTION_H_
#define SRC_AUTOPLAYS_ACTION_H_

#include "Log.h"

class Action {
public:
	Action();

	//Called once when the routine starts
	virtual void start() = 0;

	//Called repeatedly while the routine runs
	virtual void process() = 0;

	//Called once when the routine ends
	virtual void end() = 0;

	//Returns whether or not the routine is finished
	virtual bool isFinished() = 0;

	void setTimeout(float);
	float getTimeout();

private:
	float timeout = -1.0;

protected:
	Log* log;
};


#endif /* SRC_AUTOPLAYS_ACTION_H_ */
