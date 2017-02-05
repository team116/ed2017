/*
 * Converter.cpp
 *
 *  Created on: Feb 5, 2017
 *      Author: Will
 */

#include "Converter.h"

Converter* Converter::INSTANCE = nullptr;

Converter::Converter() {

}

Converter* Converter::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Converter();
	}

	return INSTANCE;
}
