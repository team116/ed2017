/*
 * Climber.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_

class Climber {
public:
	static Climber* getInstance();

	void process();

private:
	Climber();
	static Climber* INSTANCE;
};

#endif /* SRC_CLIMBER_H_ */
