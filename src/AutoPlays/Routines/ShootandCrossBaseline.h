/*
 * ShootandCrossBaseline.h
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ROUTINES_SHOOTANDCROSSBASELINE_H_
#define SRC_AUTOPLAYS_ROUTINES_SHOOTANDCROSSBASELINE_H_

#include <AutoPlays/Routine.h>
#include <Ports.h>

class ShootandCrossBaseline: public Routine {
public:
	ShootandCrossBaseline(Utils::Alliance color, Utils::AutoLocation location);
};

#endif /* SRC_AUTOPLAYS_ROUTINES_SHOOTANDCROSSBASELINE_H_ */
