/*
 * Mobility.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_MOBILITY_H_
#define SRC_MOBILITY_H_

#include <AnalogGyro.h>
#include <SpeedController.h>
#include <PIDController.h>
#include <MobilityRotationPID.h>
#include <MobilityEncoders.h>
#include <MobilityStraightOutput.h>

#include "../navx/AHRS.h"

class Mobility {
public:
	static Mobility* getInstance();

	void process();

	/**
	 * Sets the speed of the left motors
	 * speed -1 to 1, positive being forward and negative being reverse
	 */
	void setLeft(float speed);
	/**
	 * Sets the speed of the right motors
	 * Speed is from -1 to 1, positive being forward and negative being reverse
	 */
	void setRight(float speed);

	/**
	 * Starts the drive straight PID loop.
	 * The robot will lock onto the current angle of the robot until stopDriveStraight() is called
	 * Use setStraightSpeed(float) to adjust the speed of the robot while in Drive Straight mode
	 */
	void startDriveStraight();

	/**
	 * Stops the drive straight PID loop, allowing the robot to turn in any direction
	 */
	void stopDriveStraight();

	/**
	 * Returns true if Drive Straight is currently running, false if not
	 */
    bool isDrivingStraight();

	/**
	 * Sets the speed the robot should attempt to maintain while in drive straight mode
	 * Speed is from -1 to 1, positive being forward and negative being reverse
	 */
	void setStraightSpeed(float speed);

	/**
	 * Gets the speed the robot is currently set to maintain in drive straight mode
	 * Speed is from -1 to 1, positive being forward and negative being reverse
	 */
	float getStraightSpeed();

	/**
	 * Starts the turn degrees PID loop
	 * The robot will turn the specified amount of degrees
	 * NOTE this function will return before the robot has completed its turn
	 * Degrees ranges from -180 to 180
	 */
	void turnDegrees(float degrees);

	void setLeftDriveEncoder();
	void setRightDriveEncoder();

	void DriveDistance(float_t);

private:
	Mobility();
	static Mobility* INSTANCE;

	//Functions
	void processTurningDegrees();

	//Use these instead of directly enabling/disabling the PID controller and PID output
	void disableRotationPID();
	void enableRotationPID();

	MobilityEncoders* encoders;

	//Motor Controllers
	frc::SpeedController* front_left;
	frc::SpeedController* front_right;
	frc::SpeedController* back_right;
	frc::SpeedController* back_left;


	frc::PIDController* straight_PID;


	//Sensors
	AHRS* gyro;

	//PID Stuff
	MobilityRotationPID* rotation_output;
	frc::PIDController* rotation_PID;
	MobilityStraightOutput* straight_output;

	//Other variables
	float straight_speed;
	bool turning_degrees;
	bool driving_straight;

	static int counter;
};

#endif /* SRC_MOBILITY_H_ */
