/*
 * Climber.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#include <VictorSP.h>
#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

class Climber {
public:
	static Climber* getInstance();

	void process();
	void climbUp(float speed);
	void climbDown(float speed);
	void climbStop(float speed);

private:
	Climber();
	static Climber* INSTANCE;
	VictorSP* climber;
};

#endif /* SRC_CLIMBER_H_ */
