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
	float getSpeed();
private:
	Climber();
	static Climber* INSTANCE;
	frc::SpeedController* climber_left;
	frc::SpeedController* climber_right;
};

#endif /* SRC_CLIMBER_H_ */
