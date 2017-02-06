/*
 * Shooter.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

#include <SpeedController.h>
#include <PIDController.h>
#include <Encoder.h>
#include <PIDController.h>
#include <Mobility.h>
#include <CANTalon.h>
#include <Servo.h>

class Shooter {
public:
	static Shooter* getInstance();
	void process();

	void setAzimuthSpeed(float speed);
	void setAzimuthAngle(float angle);
	void setShooterSpeed(float speed);
	void setShooterRPM(float speed);
	void enableShooterPID();
	void disableShooterPID();
	bool isShooterPIDEnabled();
	void enableAzimuthPID();
	void disableAzimuthPID();
	bool isAzimuthPIDEnabled();
	float getSpeed();
	float getAzimuthEncoderRate();
	float getShooterEncoderRate();
	float getAzimuthPosition();
	float getAzimuthSetValue();
	float getShooterSetValue();

private:
	Shooter();
	static Shooter* INSTANCE;
	CANTalon* shooter;
	frc::SpeedController* azimuth;
	frc::Encoder* shooter_encoder;
	frc::Encoder* azimuth_encoder;
	float target_azimuth_angle;
	frc::DigitalInput* azimuth_limit_switch;

	//PID stuff
	frc::PIDController* shooter_PID;
	frc::PIDController* azimuth_PID;

	void enableShooterAzimuthEncoder();
	void disableShooterAzimuthEncoder();
	void enableShooterAzimuthLimitSwitch();
	void disableShooterAzimuthLimitSwitch();
	void enableShooterSpeedEncoder();
	void disableShooterSpeedEncoder();

};

#endif /* SRC_SHOOTER_H_ */
