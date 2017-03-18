/*
 * ShootShooter.cpp
 *
 *  Created on: Feb 17, 2017
 *      Author: Steven
 */

#include <AutoPlays/Actions/ShootShooter.h>

ShootShooter::ShootShooter(float speed, float time) {
	shooter  = Shooter::getInstance();
	feeder = Feeder::getInstance();
	shooter_speed = speed;

	setTimeout(time);
}
void ShootShooter::start() {
	shooter->setShooterSpeed(shooter_speed);
	feeder->setBlenderSpeed(0.75);
	feeder->setFeederSpeed(0.5);
}
void ShootShooter::process() {

}
void ShootShooter::end() {
	shooter->setShooterSpeed(0.0);
	feeder->setBlenderSpeed(0.0);
	feeder->setFeederSpeed(0.0);
}
bool ShootShooter::isFinished() {
	return false;
}
