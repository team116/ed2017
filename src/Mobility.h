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
	void setTurningDegrees(float degrees);

private:
	Mobility();
	static Mobility* INSTANCE;

	void processDriveStraight();
	void processTurningDegrees();

	VictorSP* front_left;
	VictorSP* front_right;
	VictorSP* back_right;
	VictorSP* back_left;
	AnalogGyro* gyro;
	float target_angle;
	float straight_speed;

	float acceptable_error;
	float degrees;
	float starting_degree;
	float target_degree;
	float current_angle;
	float degree_range;
};

#endif /* SRC_MOBILITY_H_ */
