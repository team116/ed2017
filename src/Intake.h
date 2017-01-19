/*
 * Intake.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */
#ifndef SRC_INTAKE_H_
#define SRC_INTAKE_H_
#include <VictorSP.h>

class Intake {
public:
	static Intake* getInstance();
	void process();
	void setSpeedIntake(float speed);

private:
	Intake();
	static Intake* INSTANCE;
	VictorSP* intake_motor;
};

#endif /* SRC_INTAKE_H_ */
