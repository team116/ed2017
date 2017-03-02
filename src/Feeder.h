/*
 * Feeder.h
 *
 *  Created on: Jan 21, 2017
 *      Author: carty
 */

#ifndef SRC_FEEDER_H_
#define SRC_FEEDER_H_

#include <VictorSP.h>
#include <Servo.h>

class Feeder {
public:
	static Feeder* getInstance();

	//Feeder
	void setFeederSpeed(float speed);
	float getFeederSpeed();

	//Blender
	void setBlenderSpeed(float speed);
	float getBlenderSpeed();

	//Alligator the Agitator
	void setAgitatorAngle(float angle);
	float getAgitatorAngle();

private:
	Feeder();
	static Feeder* INSTANCE;
	frc::SpeedController* blender;

	frc::SpeedController* feeder;

	frc::Servo* alligator; //agitator
};

#endif /* SRC_FEEDER_H_ */
