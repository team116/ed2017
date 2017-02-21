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
#include "AzimuthEncoder.h"
#include "Vision.h"

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
	float getShooterEncoderRate();
	float getAzimuthPosition();
	float getAzimuthSpeed();
	float getShooterSetValue();
	bool getLimitSwitch();

	void enableShooterAzimuthEncoder();
	void disableShooterAzimuthEncoder();
	void enableShooterAzimuthLimitSwitch();
	void disableShooterAzimuthLimitSwitch();
	void enableShooterSpeedEncoder();
	void disableShooterSpeedEncoder();
	bool isShooterAzimuthEncoderEnabled();
	bool isShooterAzimuthLimitSwitchEnabled();
	bool isShooterSpeedEncoderEnabled();

	void startAzimuthVisionTrack();
	void stopAzimuthVisionTrack();
	bool isAzimuthVisionTrack();

private:
	Shooter();
	class AzimuthVisionTracker : public PIDSource {
	public:
		AzimuthVisionTracker();
		double PIDGet();
		Vision* vision;
	};
	static Shooter* INSTANCE;

	CANTalon* shooter;
	frc::SpeedController* azimuth;
	frc::AnalogPotentiometer* azimuth_encoder;
	AzimuthEncoder* az_enc;
	float target_azimuth_angle;
	frc::DigitalInput* azimuth_limit_switch;

	//PID stuff
	//frc::PIDController* shooter_PID;
	frc::PIDController* azimuth_PID;
	frc::PIDController* azimuth_vision_PID;

	AzimuthVisionTracker* azimuth_vision_tracker;

	bool use_shooter_azimuth_encoder;
	bool use_shooter_azimuth_limit_switch_encoder;
	bool use_shooter_speed_encoder;

	bool azimuth_auto_track;

	//Manual stuff
	float azimuth_current_angle;//This is an approximation of the current azimuth angle

};

#endif /* SRC_SHOOTER_H_ */
