/*
 * DeliverGear.h
 *
 *  Created on: Feb 15, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ROUTINES_DELIVERGEAR_H_
#define SRC_AUTOPLAYS_ROUTINES_DELIVERGEAR_H_

#include <AutoPlays/Routine.h>
#include <Ports.h>
#include "AutoPlays/Actions/Wiggle.h"

class DeliverGear: public Routine {
public:
	DeliverGear(Utils::Alliance color, Utils::AutoLocation location, bool use_vision);
};

#endif /* SRC_AUTOPLAYS_ROUTINES_DELIVERGEAR_H_ */
