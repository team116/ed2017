/*
 * Climber.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

#include <VictorSP.h>

class Climber {
public:
	static Climber* getInstance();

	void process();
	void moveClimber (float speed);

private:
	Climber();
	static Climber* INSTANCE;
	frc::VictorSP* climber;
};

#endif /* SRC_CLIMBER_H_ */
