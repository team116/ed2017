/*
 * Gear.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#ifndef SRC_GEAR_H_
#define SRC_GEAR_H_

#include <Servo.h>

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
	frc::Servo* servo_left;
	frc::Servo* servo_right;
};

#endif /* SRC_GEAR_H_ */
