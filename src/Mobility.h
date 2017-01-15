/*
 * Mobility.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_MOBILITY_H_
#define SRC_MOBILITY_H_

class Mobility {
public:
	static Mobility* getInstance();
	void process();

private:
	Mobility();
	static Mobility* INSTANCE;
};

#endif /* SRC_MOBILITY_H_ */
