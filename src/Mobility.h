/*
 * Mobility.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_MOBILITY_H_
#define SRC_MOBILITY_H_

#include <AnalogGyro.h>
#include <VictorSP.h>

class Mobility {
public:
	static Mobility* getInstance();
	void process();
	void setLeft(float speed);
	void setRight(float speed);
	void setAngle(float angle);
	void setStraightSpeed(float speed);

private:
	Mobility();
	static Mobility* INSTANCE;
	VictorSP* front_left;
	VictorSP* front_right;
	VictorSP* back_right;
	VictorSP* back_left;
	AnalogGyro* gyro;
	float target_angle;
	float straight_speed;
};

#endif /* SRC_MOBILITY_H_ */
