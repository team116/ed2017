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

private:
	Shooter();
	static Shooter* INSTANCE;
	frc::SpeedController* shooter;
	frc::SpeedController* azimuth;
	frc::Encoder* shooter_encoder;
	float target_azimuth_angle;

	//PID stuff
	frc::PIDController* shooter_PID;
};

#endif /* SRC_SHOOTER_H_ */
