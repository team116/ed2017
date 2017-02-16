/*
 * DropGear.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/DropGear.h>

DropGear::DropGear() {
	gear = Gear::getInstance();
}
void DropGear::start() {
	gear->open();
}
void DropGear::process() {

}
void DropGear::end() {

}
bool DropGear::isFinished() {
	return gear->isOpen();
}
