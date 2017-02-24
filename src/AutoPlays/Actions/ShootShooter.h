/*
 * ShootShooter.h
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ACTIONS_SHOOTSHOOTER_H_
#define SRC_AUTOPLAYS_ACTIONS_SHOOTSHOOTER_H_

#include <AutoPlays/Action.h>
#include <Shooter.h>

class ShootShooter: public Action {
public:
	ShootShooter(float time);
	void start();

	void process();

	void end();

	bool isFinished();

private:
	Shooter* shooter;
};

#endif /* SRC_AUTOPLAYS_ACTIONS_SHOOTSHOOTER_H_ */
