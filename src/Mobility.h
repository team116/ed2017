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
#include <PIDController.h>
#include <MobilityRotationPID.h>

#include "..\navx\AHRS.h"

class Mobility {
public:
	static Mobility* getInstance();
	void process();
	void setLeft(float speed);
	void setRight(float speed);
	void setAngle(float angle);
	void setStraightSpeed(float speed);
	void setTurningDegrees(float degrees);
	float getStraightSpeed();

private:
	Mobility();
	static Mobility* INSTANCE;
	void processTurningDegrees();
	void startDriveStraight();
	void stopDriveStraight();
	PIDOutput* rotation_output;

	frc::VictorSP* front_left;
	frc::VictorSP* front_right;
	frc::VictorSP* back_right;
	frc::VictorSP* back_left;
	AHRS* gyro;
	frc::PIDController* rotation_PID;
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
