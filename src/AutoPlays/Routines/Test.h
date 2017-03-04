/*
 * Test.h
 *
 *  Created on: Mar 4, 2017
 *      Author: Steven
 */

#ifndef SRC_AUTOPLAYS_ROUTINES_TEST_H_
#define SRC_AUTOPLAYS_ROUTINES_TEST_H_

#include <AutoPlays/Routine.h>
#include <Ports.h>

class Test: public Routine {
public:
	Test(Utils::Alliance color, Utils::AutoLocation location);
};

#endif /* SRC_AUTOPLAYS_ROUTINES_TEST_H_ */
