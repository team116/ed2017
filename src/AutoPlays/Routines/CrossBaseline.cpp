/*
 * CrossBaseline.cpp
 *
 *  Created on: Feb 14, 2017
 *      Author: Steven
 */

#include <AutoPlays/Routines/CrossBaseline.h>
#include "AutoPlays/Actions/DriveStraight.h"

CrossBaseline::CrossBaseline() {
	addAction(new DriveStraight());
}

