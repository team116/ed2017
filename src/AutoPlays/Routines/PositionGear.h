/*
 * PositionGear.h
 *
 *  Created on: Mar 5, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ROUTINES_POSITIONGEAR_H_
#define SRC_AUTOPLAYS_ROUTINES_POSITIONGEAR_H_

#include <AutoPlays/Routine.h>
#include <Ports.h>

class PositionGear: public Routine {
public:
	PositionGear(Utils::Alliance color, Utils::AutoLocation location, bool use_vision);
};

#endif /* SRC_AUTOPLAYS_ROUTINES_POSITIONGEAR_H_ */
