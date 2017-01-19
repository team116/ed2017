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
	void openLeft();
	void closeLeft();
	void openRight();
	void closeRight();

private:
	Gear();
	static Gear* INSTANCE;
	static const float LEFT_CLOSED_ANGLE;
	static const float LEFT_OPEN_ANGLE;
	static const float RIGHT_OPEN_ANGLE;
	static const float RIGHT_CLOSED_ANGLE;
	Servo* servo_left;
	Servo* servo_right;
};

#endif /* SRC_GEAR_H_ */
