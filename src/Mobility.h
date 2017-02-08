/*
 * Mobility.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_MOBILITY_H_
#define SRC_MOBILITY_H_

#include <AnalogGyro.h>
#include <MobilityDistanceOutput.h>
#include <MobilityEncoder.h>
#include <SpeedController.h>
#include <PIDController.h>
#include <MobilityRotationPID.h>
#include "../navx/AHRS.h"
#include "Log.h"

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
	bool isTurnDegreesDone();

	void StartDriveDistance(float_t);
	bool isDriveDistanceDone();


	//Use these instead of directly enabling/disabling the PID controller and PID output
	void disableDistancePID();
	void enableDistancePID();
	bool isDistancePIDEnabled();

	void disableRotationPID();
	void enableRotationPID();
	bool isRotationPIDEnabled();


	float getGyroAngle();
	float getLeftEncoderRates();
	float getRightEncoderRates();

	float getLeftSetValue();
	float getRightSetValue();

	float getNavXTemperature();

	//Calibration
	//Logs the linear acceleration of the robot. Runs at full speed for the specified time
	void startLinearAccelTest(float);
	//Logs the rotational velocity of the robot. Runs at full rotation for the specified time
	void startRotationalVelTest(float);

	//Sensor Toggles
	void enableLeftEncoder();
	void disableLeftEncoder();
	bool isLeftEncoderEnabled();
	void enableRightEncoder();
	void disableRightEncoder();
	bool isRightEncoderEnabled();
	void enableGyro();
	void disableGyro();
	bool isGyroEnabled();

private:
	Mobility();
	static Mobility* INSTANCE;

	Log* log;

	//Functions
	void processTurningDegrees();
	float calculateTimeForDistance(float);

	MobilityEncoder* encoders;


	//Motor Controllers
	frc::SpeedController* front_left;
	frc::SpeedController* front_right;
	frc::SpeedController* back_right;
	frc::SpeedController* back_left;


	frc::PIDController* distance_PID;


	//Sensors
	AHRS* gyro;

	//PID Stuff
	MobilityRotationPID* rotation_output;
	frc::PIDController* rotation_PID;
	MobilityDistanceOutput* distance_output;


	//Other variables
	float straight_speed;
	bool is_turn_degrees_on;
	bool driving_straight;
	bool is_drive_distance_on;
	bool is_linear_accel_test;
	bool is_rotational_vel_test;

	void processDistance();

	//Sensor toggles
	bool use_left_drive_encoder;
	bool use_right_drive_encoder;
	bool use_gyro;


	//Manual stuff
	Timer* drive_distance_timer;
	float drive_dist_time;
	Timer* turn_degrees_timer;
	float turn_deg_time;
};

#endif /* SRC_MOBILITY_H_ */
