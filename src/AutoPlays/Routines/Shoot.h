/*
 * Shoot.h
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ROUTINES_SHOOT_H_
#define SRC_AUTOPLAYS_ROUTINES_SHOOT_H_

#include <AutoPlays/Routine.h>
#include <Ports.h>

class Shoot: public Routine {
public:
	Shoot(Utils::Alliance color, Utils::AutoLocation location);
};

#endif /* SRC_AUTOPLAYS_ROUTINES_SHOOT_H_ */
