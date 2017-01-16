/*
 * Gear.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#include <Servo.h>

#ifndef SRC_GEAR_H_
#define SRC_GEAR_H_

class Gear {
public:
	static Gear* getInstance();
	void process();
	void open();
	void close();

private:
	Gear();
	static Gear* INSTANCE;
	static const float CLOSED_ANGLE;
	static const float OPEN_ANGLE;
	Servo* servo;
};

#endif /* SRC_GEAR_H_ */
