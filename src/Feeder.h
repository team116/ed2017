/*
 * Feeder.h
 *
 *  Created on: Jan 21, 2017
 *      Author: carty
 */

#ifndef SRC_FEEDER_H_
#define SRC_FEEDER_H_

#include <VictorSP.h>

class Feeder {
public:
	static Feeder* getInstance();

	void setFeederSpeed(float speed);

private:
	Feeder();
	static Feeder* INSTANCE;

	frc::SpeedController* feeder;
};

#endif /* SRC_FEEDER_H_ */
