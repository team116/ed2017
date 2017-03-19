/*
 * SetShooterSpeed.h
 *
 *  Created on: Mar 18, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ACTIONS_SETSHOOTERSPEED_H_
#define SRC_AUTOPLAYS_ACTIONS_SETSHOOTERSPEED_H_

#include <AutoPlays/Action.h>
#include <Shooter.h>

class SetShooterSpeed: public Action {
public:
	SetShooterSpeed(float speed);

	void start();

		void process();

		void end();

		bool isFinished();

private:
		Shooter* shooter;
		float sped;
};

#endif /* SRC_AUTOPLAYS_ACTIONS_SETSHOOTERSPEED_H_ */
