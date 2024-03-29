/*
 * DeliverGearandTravel.h
 *
 *  Created on: Mar 2, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ROUTINES_DELIVERGEARANDTRAVEL_H_
#define SRC_AUTOPLAYS_ROUTINES_DELIVERGEARANDTRAVEL_H_

#include <AutoPlays/Routine.h>
#include <Ports.h>

class DeliverGearandTravel : public Routine {
public:
	DeliverGearandTravel(Utils::Alliance color, Utils::AutoLocation location, bool use_vision);
};

#endif /* SRC_AUTOPLAYS_ROUTINES_DELIVERGEARANDTRAVEL_H_ */
