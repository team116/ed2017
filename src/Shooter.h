/*
 * Shooter.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

#include <SpeedController.h>

class Shooter {
public:
	static Shooter* getInstance();
	void process();
	void setSpeedAzimuth(float speed);
	void setSpeedShooter(float speed);
	void setSpeedFeeder(float speed);
	void setAngleDirection(float angle);

private:
	Shooter();
	static Shooter* INSTANCE;
	frc::SpeedController* ball_holder;
	frc::SpeedController* shooter;
	frc::SpeedController* azimuth;
	float target_azimuth_angle;
};

#endif /* SRC_SHOOTER_H_ */
