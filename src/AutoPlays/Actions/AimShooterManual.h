/*
 * AimShooterManual.h
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ACTIONS_AIMSHOOTERMANUAL_H_
#define SRC_AUTOPLAYS_ACTIONS_AIMSHOOTERMANUAL_H_

#include <AutoPlays/Action.h>
#include <Mobility.h>
#include <Shooter.h>

class AimShooterManual: public Action {
public:
	AimShooterManual();
	void start();

	void process();

	void end();

	bool isFinished();

private:
	Shooter* shooter;
};

#endif /* SRC_AUTOPLAYS_ACTIONS_AIMSHOOTERMANUAL_H_ */
