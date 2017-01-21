/*
 * Climber.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

#include <SpeedController.h>

class Climber {
public:
	static Climber* getInstance();

	void process();
	void moveClimber (float speed);

private:
	Climber();
	static Climber* INSTANCE;
	frc::SpeedController* climber;
};

#endif /* SRC_CLIMBER_H_ */
