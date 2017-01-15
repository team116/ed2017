/*
 * Gear.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_GEAR_H_
#define SRC_GEAR_H_

class Gear {
public:
	static Gear* getInstance();
	void process();

private:
	Gear();
	static Gear* INSTANCE;
};

#endif /* SRC_GEAR_H_ */
