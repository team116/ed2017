/*
 * DeliverGearandShoot.h
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ROUTINES_DELIVERGEARANDSHOOT_H_
#define SRC_AUTOPLAYS_ROUTINES_DELIVERGEARANDSHOOT_H_

#include <AutoPlays/Routine.h>
#include <Ports.h>

class DeliverGearandShoot: public Routine {
public:
	DeliverGearandShoot(Utils::Alliance color, Utils::AutoLocation location, bool use_vision);
};

#endif /* SRC_AUTOPLAYS_ROUTINES_DELIVERGEARANDSHOOT_H_ */
