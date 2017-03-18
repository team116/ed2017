/*
 * AimShooterVision.h
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ACTIONS_AIMSHOOTERVISION_H_
#define SRC_AUTOPLAYS_ACTIONS_AIMSHOOTERVISION_H_

#include <AutoPlays/Action.h>
#include <Vision.h>
#include <Shooter.h>

class AimShooterVision: public Action {
public:
	AimShooterVision();
	void start();

	void process();

	void end();

	bool isFinished();

private:
	Vision* vision;
	Shooter* shooter;
};

#endif /* SRC_AUTOPLAYS_ACTIONS_AIMSHOOTERVISION_H_ */
