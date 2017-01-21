/*
 * Shooter.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

#include <VictorSP.h>

class Shooter {
public:
	static Shooter* getInstance();
	void process();

	void setAzimuthSpeed(float speed);
	void setAzimuthAngle(float angle);

	void setShooterSpeed(float speed);

private:
	Shooter();
	static Shooter* INSTANCE;
	frc::VictorSP* shooter;
	frc::VictorSP* azimuth;
	float target_azimuth_angle;
};

#endif /* SRC_SHOOTER_H_ */
