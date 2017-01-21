/*
 * Gear.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_GEAR_H_
#define SRC_GEAR_H_

#include <SpeedController.h>
#include <DigitalInput.h>

class Gear {
public:
	static Gear* getInstance();
	void process();
	void open();
	void close();

private:
	Gear();
	static Gear* INSTANCE;
	frc::SpeedController* gear_motor;
	frc::DigitalInput* LS_open;
	frc::DigitalInput* LS_close;
};

#endif /* SRC_GEAR_H_ */
