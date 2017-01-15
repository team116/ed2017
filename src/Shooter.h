/*
 * Shooter.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

class Shooter {
public:
	static Shooter* getInstance();

private:
	Shooter();
	static Shooter* INSTANCE;
};

#endif /* SRC_SHOOTER_H_ */
