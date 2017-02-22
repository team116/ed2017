/*
 * ShootShooter.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/ShootShooter.h>

ShootShooter::ShootShooter(float time) {
	shooter  = Shooter::getInstance();
	setTimeout(15.0);
}
void ShootShooter::start() {
	shooter->setShooterSpeed(100.0);
}
void ShootShooter::process() {

}
void ShootShooter::end() {

}
bool ShootShooter::isFinished() {

}
