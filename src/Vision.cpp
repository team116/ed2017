/*
 * Vision.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Vision.h>

Vision* Vision::INSTANCE;

Vision::Vision() {
	// TODO Auto-generated constructor stub

}

void Vision::process() {

}

Vision* Vision::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Vision();
	}

	return INSTANCE;
}
