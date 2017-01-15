/*
 * Autonomous.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_

class Autonomous {
public:
	static Autonomous* getInstance();

	void process();

private:
	Autonomous();
	static Autonomous* INSTANCE;
};

#endif /* SRC_AUTONOMOUS_H_ */
