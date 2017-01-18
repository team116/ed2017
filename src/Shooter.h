/*
 * Shooter.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#include <VictorSP.h>
#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

class Shooter {
public:
	static Shooter* getInstance();
	void process();
	void setSpeedAzimuth(float speed);
	void setSpeedShooter(float speed);
	void setSpeedFeeder(float speed);

private:
	Shooter();
	static Shooter* INSTANCE;
	VictorSP* ball_holder;
	VictorSP* shooter;
	VictorSP* azimuth;
};

#endif /* SRC_SHOOTER_H_ */
