/*
 * Intake.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_INTAKE_H_
#define SRC_INTAKE_H_

class Intake {
public:
	static Intake* getInstance();

private:
	Intake();
	static Intake* INSTANCE;
};

#endif /* SRC_INTAKE_H_ */
