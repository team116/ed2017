/*
 * Mobility.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#include <VictorSP.h>
#ifndef SRC_MOBILITY_H_
#define SRC_MOBILITY_H_

class Mobility {
public:
	static Mobility* getInstance();
	void process();
	void setLeft(float speed);
	void setRight(float speed);

private:
	Mobility();
	static Mobility* INSTANCE;
	VictorSP* front_left;
	VictorSP* front_right;
	VictorSP* back_right;
	VictorSP* back_left;
};

#endif /* SRC_MOBILITY_H_ */
